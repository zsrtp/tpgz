#!/usr/bin/python3
import sys
import struct
import yaml

REQ_BITS = {"POS": 1, "CAM": 2}
DEFAULT_POS = [0.0, 0.0, 0.0]


def requirements_to_int(names):
    value = 0
    for name in names:
        value |= REQ_BITS[name]
    return value


def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <input.yml> <output.bin>", file=sys.stderr)
        sys.exit(1)

    with open(sys.argv[1]) as f:
        entries = yaml.safe_load(f) or []

    with open(sys.argv[2], "wb") as out:
        for e in entries:
            cam = e.get("cam", {})
            out.write(requirements_to_int(e.get("requirements", [])).to_bytes(1, "big", signed=False))
            out.write((0).to_bytes(1, "big", signed=False))  # padding
            out.write(int(e.get("angle", 0)).to_bytes(2, "big", signed=False))
            out.write(struct.pack(">fff", *e.get("pos", DEFAULT_POS)))
            out.write(struct.pack(">fff", *cam.get("pos", DEFAULT_POS)))
            out.write(struct.pack(">fff", *cam.get("target", DEFAULT_POS)))
            out.write(int(e.get("counter", 0)).to_bytes(4, "big", signed=False))
            out.write(struct.pack(">32s", e["filename"].encode("ascii")))
            out.write((0).to_bytes(4, "big", signed=False))  # padding


if __name__ == "__main__":
    main()
