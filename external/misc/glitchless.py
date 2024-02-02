import struct

REQ_POS = 1
REQ_CAM = 2

default_entry = {
    "requirements": 0,
    "pos": (0.0,0.0,0.0),
    "angle": 0,
    "cam": {"pos":(0,0,0), "target": (0,0,0)},
    "counter": 0,
}

# order matters
file_names = [
    "faron_twilight",
    "forest",
    "diababa",
    "eldin_twilight",
    "post_twilight",
	"kb1",
	"mines",
	"dangoro",
	"lanayru_twilight",
    "escort",
    "lakebed",
    "toad",
	"mdh",
	"post_mdh",
	"post_ms",
	"ag",
	"death_sword",
	"post_ag",
	"spr",
	"darkhammer",
	"post_spr",
	"tot",
	"darknut",
	"post_tot",
	"hv_archery",
	"city",
	"aeralfos",
	"palace",
	"zant",
	"hc",
	"beast_ganon",
	"horseback_ganon",
]

hundo_p = [{**default_entry, "id": i, "filename": file_names[i]} for i in range(32)]

file = open("glitchless.bin", "wb")

for entry in hundo_p:
    print(entry)
    file.write(entry["requirements"].to_bytes(1, "big", signed=False))
    file.write(int(0).to_bytes(1, "big", signed=False)) # padding
    file.write(entry["angle"].to_bytes(2, "big", signed=False))
    file.write(struct.pack('>fff', *entry["pos"]))
    file.write(struct.pack('>fff', *entry["cam"]["pos"]))
    file.write(struct.pack('>fff', *entry["cam"]["target"]))
    file.write(entry["counter"].to_bytes(4, "big", signed=False))
    file.write(struct.pack(">32s", entry["filename"].encode("ascii")))
    file.write(int(0).to_bytes(4, "big", signed=False)) # padding
