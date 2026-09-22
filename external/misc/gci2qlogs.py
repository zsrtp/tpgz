#!/usr/bin/env python

import argparse, os, re, struct, sys

def main():
    parser = argparse.ArgumentParser(description="Parses out quest logs from a Twilight Princess GCI")
    parser.add_argument("gci", help="A valid twilight princess GCI file")
    gcibytes = None
    args = parser.parse_args()
    file_in = args.gci
    with open(file_in,"rb") as gcifile:
        gcibytes = bytearray(gcifile.read())
    
    qlog1 = gcibytes[0x4048:0x4AD4]
    qlog2 = gcibytes[0x4ADC:0x5568]
    qlog3 = gcibytes[0x5570:0x5FFC]

    with open("qlog1.bin", "wb") as outfile:
        outfile.write(qlog1)

    with open("qlog2.bin", "wb") as outfile:
        outfile.write(qlog2)

    with open("qlog3.bin", "wb") as outfile:
        outfile.write(qlog3)
    
if __name__ == "__main__":
    main()