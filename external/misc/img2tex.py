from PIL import Image
from textures import Formats, write_tex
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

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Converts an image into a texture file.')
    parser.add_argument('-V', '--version', action='version', version='%(prog)s 0.2')
    parser.add_argument('image_file', type=argparse.FileType('rb'),
                        help='Path to the image file')
    parser.add_argument('out_tex', type=argparse.FileType('wb'), nargs='?', default="out.tex",
                        help='Name of the output file')
    parser.add_argument('-r', '--resize', type=size_type, metavar='WxH',
                        help='Resizes the image to a width/height of W/H')
    parser.add_argument('-f', '--format', type=str, choices=[name for name, _ in Formats.__members__.items()], 
                        default='RGBA8', help='Format to save the picture in')
    params = parser.parse_args()

    # We fetch the picture, and make sure that it has a valid size
    image = Image.open(params.image_file).convert('RGBA')
    if not params.resize is None:
        image = image.resize(params.resize)
    if params.format in ["RGBA8"] and (image.width % 4 != 0 or image.height % 4 != 0):
        raise RuntimeError("image size has to be a multiple of 4 when using RGBA8")
    if params.format in ["CMPR", "I8"] and (image.width % 8 != 0 and image.height % 8 != 0):
        raise RuntimeError("image size has to be a multiple of 8 when using CMPR or I8 formats")

    write_tex(params.out_tex, image, Formats[params.format])