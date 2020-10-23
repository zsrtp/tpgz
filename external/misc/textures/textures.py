from enum import Enum, unique
from PIL import Image
import struct
import re
import functools
import io
#import syaz0


@unique
class Formats(Enum):
    RGBA8 = 0
    CMPR = 1
    I8 = 2


def write_header(out_file, image: Image, format: Formats):
    out_file.write(struct.pack(">4s", "TEX0".encode("ascii"))) # channel count
    out_file.write(format.value.to_bytes(4, 'big', signed=False))
    out_file.write(image.width.to_bytes(4, 'big', signed=False))
    out_file.write(image.height.to_bytes(4, 'big', signed=False))

def write_tile(out_file, chn):
    for j in range(8):
        for i in range(8):
            pos = (i, j)
            val = chn.getpixel(pos)
            out_file.write(struct.pack(">B", val))

def write_tile2(out_file, chn1, chn2):
    for j in range(4):
        for i in range(4):
            pos = (i, j)
            val1 = chn1.getpixel(pos)
            val2 = chn2.getpixel(pos)
            out_file.write(struct.pack(">BB", val1, val2))

def write_raw(out_file, image):
    image = image.convert('RGBA')
    # We save each 4x4 tile one at a time.
    for j in range(image.height // 4):
        for i in range(image.width // 4):
            tile = image.crop((i * 4, j * 4, (i + 1) * 4, (j + 1) * 4))
            chnR, chnG, chnB, chnA = tile.split()
            write_tile2(out_file, chnA, chnR)
            write_tile2(out_file, chnG, chnB)

def write_i8(out_file, image):
    image = image.convert(mode="L", dither=None)
    # We save each 4x4 tile one at a time.
    for j in range(image.height // 8):
        for i in range(image.width // 8):
            tile = image.crop((i * 8, j * 8, (i + 1) * 8, (j + 1) * 8))
            write_tile(out_file, tile)

def toRGB565(r, g, b):
    return (int(r * 31 / 255) << 11) | (int(g * 63 / 255) << 5) | (int(b * 31 / 255))

def quantize_tile(out_file, img):
    img = img.convert('RGBA')
    has_transparency = any(pixel[3] == 0 for pixel in (img.getdata()))
    lst = img.quantize(2).getpalette()[:2*3]
    palette = [tuple(lst[i:i + 3]) for i in range(0, len(lst), 3)]
    if not ((has_transparency and toRGB565(*palette[0]) <= toRGB565(*palette[1])) or ((not has_transparency) and toRGB565(*palette[0]) > toRGB565(*palette[1]))):
        tmp = palette[0]
        palette[0] = palette[1]
        palette[1] = tmp
    out_file.write(toRGB565(*palette[0]).to_bytes(2, 'big', signed=False))
    out_file.write(toRGB565(*palette[1]).to_bytes(2, 'big', signed=False))
    if (has_transparency):
        palette.append(tuple((palette[0][i] + palette[1][i]) // 2 for i in range(3)))
    else:
        palette.append(tuple((palette[0][i] * 2 + palette[1][i]) // 3 for i in range(3)))
        palette.append(tuple((palette[1][i] * 2 + palette[0][i]) // 3 for i in range(3)))
    for j in range(4):
        row = list()
        for i in range(4):
            pixel = img.getpixel((i, j))
            distances = [sum(abs(pixel[a] - palette[k][a]) for a in range(len(palette[k]))) for k in range(len(palette))]
            chnA = pixel[3]
            min_palette = distances.index(min(distances))
            if chnA == 0:
                min_palette = 3
            row.append(min_palette)
        out_file.write(functools.reduce(lambda x, y: x | y, ((int(row[i]) & 0x3) << ((4 - (i + 1)) * 2) for i in range(4))).to_bytes(1, 'big', signed=False))

def write_cmpr(out_file, image):
    for v in range(image.height // 8):
        for u in range(image.width // 8):
            for j in range(2):
                for i in range(2):
                    tile = image.crop((u * 8 + i * 4, v * 8 + j * 4, u * 8 + (i + 1) * 4, v * 8 + (j + 1) * 4))
                    quantize_tile(out_file, tile)

def write_tex(out_buf, img: Image, fmt: Formats):
    buffer = io.BytesIO()

    write_header(out_buf, img, fmt)

    if fmt == Formats.RGBA8:
        write_raw(buffer, img)
    elif fmt == Formats.CMPR:
        write_cmpr(buffer, img)
    elif fmt == Formats.I8:
        write_i8(buffer, img)
    #out_buf.write(syaz0.compress(buffer.getvalue()))
    out_buf.write(buffer.getvalue())
