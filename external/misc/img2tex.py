from PIL import Image
import struct
import argparse
import re
import functools
import io
#import syaz0

formats = {
    'RGBA8': 0,
    'CMPR': 1
}

def size_type(string):
    pattern = re.compile("([0-9]+)[xX]([0-9]+)")
    matching = re.fullmatch(pattern, string)
    if matching is None:
        msg = "%r is not a valid size" % string
        raise argparse.ArgumentTypeError(msg)
    size = tuple(int(g) for g in matching.groups())
    if size[0] % 4 != 0 or size[1] % 4 != 0:
        msg = "The new size \"%dx%d\" must be a multiple of 4" % size
        raise argparse.ArgumentTypeError(msg)
    return size

def write_header(out_file, image, format):
    out_file.write(struct.pack(">4s", "TEX0".encode("ascii"))) # channel count
    out_file.write(formats[format].to_bytes(4, 'big', signed=False))
    out_file.write(image.width.to_bytes(4, 'big', signed=False))
    out_file.write(image.height.to_bytes(4, 'big', signed=False))

def write_tile(out_file, chn1, chn2):
    for j in range(4):
        for i in range(4):
            pos = (i, j)
            val1 = chn1.getpixel(pos)
            val2 = chn2.getpixel(pos)
            out_file.write(struct.pack(">BB", val1, val2))

def write_raw(out_file, image):
    # We save each 4x4 tile one at a time.
    for j in range(image.height // 4):
        for i in range(image.width // 4):
            tile = image.crop((i * 4, j * 4, (i + 1) * 4, (j + 1) * 4))
            chnR, chnG, chnB, chnA = tile.split()
            write_tile(out_file, chnA, chnR)
            write_tile(out_file, chnG, chnB)

def toRGB565(r, g, b):
    return (int(r * 31 / 255) << 11) | (int(g * 63 / 255) << 5) | (int(b * 31 / 255))

def quantize_tile(out_file, img):
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

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Converts an image into a texture file.')
    parser.add_argument('-V', '--version', action='version', version='%(prog)s 0.2')
    parser.add_argument('image_file', type=argparse.FileType('rb'),
                        help='Path to the image file')
    parser.add_argument('out_tex', type=argparse.FileType('wb'), nargs='?', default="out.tex",
                        help='Name of the output file')
    parser.add_argument('-r', '--resize', type=size_type, metavar='WxH',
                        help='Resizes the image to a width/height of W/H')
    parser.add_argument('-f', '--format', choices=formats.keys(), default='RGBA8',
                        help='Format to save the picture in')
    params = parser.parse_args()

    # We fetch the picture, and make sure that it has a valid size
    image = Image.open(params.image_file).convert('RGBA')
    if not params.resize is None:
        image = image.resize(params.resize)
    if image.width % 4 != 0 or image.height % 4 != 0:
        raise RuntimeError("image size has to be a multiple of 4")
    if params.format == "CMPR" and (image.width % 8 != 0 and image.height % 8 != 0):
        raise RuntimeError("image size has to be a multiple of 8 when using CMPR")
    buffer = io.BytesIO()

    write_header(buffer, image, params.format)

    if params.format == "RGBA8":
        write_raw(buffer, image)
    elif params.format == "CMPR":
        write_cmpr(buffer, image)
    #params.out_tex.write(syaz0.compress(buffer.getvalue()))
    params.out_tex.write(buffer.getvalue())
