from PIL import Image, ImageFont, ImageDraw
from textures import Formats, write_tex
import struct
import argparse
import re

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

def write_header(out_buf, font):
    out_buf.write(struct.pack(">4s", "FNT0".encode("ascii"))) # channel count
    out_buf.write(struct.pack(">f", font['base_size'])) # base_size
    out_buf.write(struct.pack(">ff", font['metrics'][0], font['metrics'][1])) # (ascend, descend)

def write_glyphs(out_buf, font):
    out_buf.write(len(font['glyphs']).to_bytes(4, 'big', signed=False)) # glyphs count
    for i in range(len(font['glyphs'])):
        out_buf.write(struct.pack(">ff", font['glyphs'][i]['offset'], font['glyphs'][i]['width']))
        out_buf.write(struct.pack(">ffff", *font['glyphs'][i]['tex_coords']))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Converts a font into a .fnt file.')
    parser.add_argument('-V', '--version', action='version', version='%(prog)s 0.2')
    parser.add_argument('font_file', type=argparse.FileType('rb'),
                        help='Path to the font file')
    parser.add_argument('out_fnt', type=argparse.FileType('wb'), nargs='?', default="out.fnt",
                        help='Name of the output file')
    parser.add_argument('-s', '--size', type=size_type, metavar='WxH', default="256x256",
                        help='Set the resolution of the font to a width/height of W/H')
    parser.add_argument('-F', '--font-size', type=int, default=18,
                        help='Font size (in points)')
    parser.add_argument('-f', '--format', type=str, choices=[name for name, _ in Formats.__members__.items()], 
                        default='I8', help='Format to save the font in')
    params = parser.parse_args()

    if params.format in ["RGBA8"] and (params.size[0] % 4 != 0 or params.size[1] % 4 != 0):
        raise RuntimeError("Size has to be a multiple of 4 when using RGBA8")
    if params.format in ["CMPR", "I8"] and (params.size[0] % 8 != 0 and params.size[1] % 8 != 0):
        raise RuntimeError("Size has to be a multiple of 8 when using CMPR or I8 formats")

    image = Image.new('RGBA', params.size, (0,0,0,0))
    draw = ImageDraw.Draw(image)

    ftf = ImageFont.FreeTypeFont(params.font_file, params.font_size)
    asc, dsc = ftf.getmetrics()
    pos = (0, asc)
    default_glyph = {
        'offset': 0,
        'width': 0,
        'tex_coords' : (0, 0, 0, 0),
    }
    glyphs = [{**default_glyph} for i in range(256)]
    for i in range(256):
        bbox = ftf.getbbox(chr(i), anchor="ls")
        glyph_width = bbox[2] - bbox[0]
        glyph_offset = (bbox[0], bbox[1])
        if pos[0] + glyph_width + 1 > params.size[0]:
            pos = (0, pos[1] + asc + dsc + 1)
        if pos[1] + asc + dsc > params.size[1]:
            raise RuntimeError("The resolution is too small to fit all the glyphs! Try to reduce the font size")

        draw.text((pos[0] - bbox[0], pos[1]), chr(i), font=ftf, anchor="ls")
        glyphs[i]['offset'] = bbox[0]
        glyphs[i]['width'] = glyph_width
        glyphs[i]['tex_coords'] = ((pos[0]) / params.size[0], (pos[1] - asc) / params.size[1], (pos[0] + glyph_width) / params.size[0], (pos[1] + dsc) / params.size[1])

        pos = (pos[0] + glyph_width + 1, pos[1])
    font = {
        'metrics': (asc, dsc),
        'base_size': params.font_size,
        'glyphs': [*glyphs],
    }

    write_header(params.out_fnt, font)
    write_glyphs(params.out_fnt, font)
    write_tex(params.out_fnt, image, Formats[params.format])