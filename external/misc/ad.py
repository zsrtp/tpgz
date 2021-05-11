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
file_names = ["ordon_gate_clip", "ordon_gate_clip", "goats", "hugo", "faron_twilight", "ems", "purple_mist", "forest_bit", "forest_escape", "pillar_clip", "lakebed1", "deku_toad", "karg_flight", "forest2", "diababa", "eldin_twilight", "lanayru_twilight", "post_lanayru", "bk_skip", "morpheel", "mdh", "mountain", "mountain_umd", "spr1", "darkhammer", "spr_boost", "blizzeta", "ag", "poe_skip", "deathsword", "stallord", "early_ele", "gm", "dangoro", "silver_rupee", "city1", "aeralfos", "city2", "argorok", "faron_boost", "grove2", "tot", "darknut", "dot_skip", "palace1", "palace2", "early_platform", "zant", "hc", "beast_ganon", "horseback_ganon", ]

ad_p = [{**default_entry, "id": i, "filename": file_names[i]} for i in range(50)]

ad_p[0]["requirements"] = REQ_POS | REQ_CAM
ad_p[0]["pos"] = (827.450012, 216.490097, -4533.90625)
ad_p[0]["angle"] = 498
ad_p[0]["cam"]["pos"] = (833.467468, 477.604675, -4241.97266)
ad_p[0]["cam"]["target"] = (827.497559, 329.622986, -4532.90723)
ad_p[0]["counter"] = 10

ad_p[1]["requirements"] = REQ_POS | REQ_CAM
ad_p[1]["pos"] = (466.622467, 319.770752, -11651.3867)
ad_p[1]["angle"] = 52540
ad_p[1]["cam"]["pos"] = (735.525391, 524.418701, -11576.4746)
ad_p[1]["cam"]["target"] = (465.674622, 421.052704, -11651.0684)
ad_p[1]["counter"] = 10

ad_p[3]["requirements"] = REQ_POS | REQ_CAM
ad_p[3]["pos"] = (701.797302, 85.5212784, -5299.6123)
ad_p[3]["angle"] = 63622
ad_p[3]["cam"]["pos"] = (735.525391, 524.418701, -11576.4746)
ad_p[3]["cam"]["target"] = (465.674622, 421.052704, -11651.0684)

# purple mist
ad_p[6]["requirements"] = REQ_POS
ad_p[6]["pos"] = (-23524.6152, 250.0, -16220.166)
ad_p[6]["angle"] = 40758
ad_p[6]["counter"] = 30

# forest escape
ad_p[8]["requirements"] = REQ_POS | REQ_CAM
ad_p[8]["pos"] = (-12433.6016, -235.969193, -17103.998)
ad_p[8]["angle"] = 29553
ad_p[8]["cam"]["pos"] = (-12552.8252, -53.5801048, -16729.5313)
ad_p[8]["cam"]["target"] = (-12433.2979, -106.667023, -17104.9512)
ad_p[8]["counter"] = 30

# eldin twilight
ad_p[15]["requirements"] = REQ_POS | REQ_CAM
ad_p[15]["pos"] = (455.088379, -150.0, 11516.7227)
ad_p[15]["angle"] = 6058
ad_p[15]["cam"]["pos"] = (219.367218, -20.1253014, 11157.582)
ad_p[15]["cam"]["target"] = (482.515137, -39.9999771, 11558.5283)
ad_p[15]["counter"] = 10

# bk skip
ad_p[18]["requirements"] = REQ_POS | REQ_CAM
ad_p[18]["pos"] = (71.9835968, 1500.00, 2839.01587)
ad_p[18]["angle"] = 32767
ad_p[18]["cam"]["pos"] = (71.9835968, 1719.93542, 2969.04565)
ad_p[18]["cam"]["target"] = (71.9835968, 1660.0, 2839.01587)
ad_p[18]["counter"] = 30

# morpheel
ad_p[19]["requirements"] = REQ_POS | REQ_CAM
ad_p[19]["pos"] = (-1193.0, -23999.00, -770.0)
ad_p[19]["angle"] = 10754
ad_p[19]["counter"] = 20

# spr boost
ad_p[25]["requirements"] = REQ_POS | REQ_CAM
ad_p[25]["pos"] = (2019.5192, 200.00, -2865.9890)
ad_p[25]["angle"] = 16384
ad_p[25]["counter"] = 30

# poe 1 skip
ad_p[28]["requirements"] = REQ_POS | REQ_CAM
ad_p[28]["pos"] = (-2046.97168, 0.0, -587.304871)
ad_p[28]["angle"] = 49030
ad_p[28]["cam"]["pos"] = (-1779.00293, 213.707397, -584.686768)
ad_p[28]["cam"]["target"] = (-2047.97168, 130.16568, -587.317139)
ad_p[28]["counter"] = 10

# early ele
ad_p[31]["requirements"] = REQ_POS | REQ_CAM
ad_p[31]["pos"] = (1304.8733, -355.5959, -5385.2314)
ad_p[31]["angle"] = 45225
ad_p[31]["counter"] = 30

# dot skip
ad_p[43]["requirements"] = REQ_POS | REQ_CAM
ad_p[43]["cam"]["target"] = 1361.59766, -33.1954155, -1090.47632
ad_p[43]["cam"]["pos"] = 1396.36316, 9.51973343, -719.644531
ad_p[43]["angle"] = 33673
ad_p[43]["pos"] = 1361.68408, -143.56076, -1089.4801

file = open("ad.bin", "wb")

for entry in ad_p:
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
