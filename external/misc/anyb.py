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
    "ordon_gate_clip", 
    "ordon_gate_clip", 
    "goats", 
    "hugo", 
    "faron_twilight", 
    "ems", 
    "purple_mist",
    "forest_bit",
    "forest_escape",
    "lanayru_gate_clip",
    "pillar_clip",
    "lakebed_1",
    "deku_toad",
    "karg",
    "kb1",
    "eldin_twilight",
    "lanayru_twilight",
    "waterfall_sidehop",
    "iza",
    "spr_warp",
    "spr",
    "darkhammer",
    "lakebed_bk_skip",
    "onebomb",
    "mdh_tower",
    "mdh_bridge",
    "camp",
    "ag",
    "poe_1_skip",
    "death_sword_skip",
    "stallord",
    "stallord",
    "silver_rupee",
    "cits_early",
    "cits_1",
    "aeralfos_skip",
    "fan_tower",
    "argorok",
    "palace_1",
    "palace_2",
    "early_platform",
    "zant",
    "hc",
    "hc_tower",
    "beast_ganon",
    "horseback_ganon",
]

anyb_p = [{**default_entry, "id": i, "filename": file_names[i]} for i in range(46)]

# ordon gate clip
anyb_p[0]["requirements"] = REQ_POS | REQ_CAM
anyb_p[0]["pos"] = (827.450012, 216.490097, -4533.90625)
anyb_p[0]["angle"] = 498
anyb_p[0]["cam"]["pos"] = (833.467468, 477.604675, -4241.97266)
anyb_p[0]["cam"]["target"] = (827.497559, 329.622986, -4532.90723)
anyb_p[0]["counter"] = 10

# back in time
anyb_p[1]["requirements"] = REQ_POS | REQ_CAM
anyb_p[1]["pos"] = (466.622467, 319.770752, -11651.3867)
anyb_p[1]["angle"] = 52540
anyb_p[1]["cam"]["pos"] = (735.525391, 524.418701, -11576.4746)
anyb_p[1]["cam"]["target"] = (465.674622, 421.052704, -11651.0684)
anyb_p[1]["counter"] = 10

# hugo
anyb_p[3]["requirements"] = REQ_POS | REQ_CAM
anyb_p[3]["pos"] = (701.797302, 85.5212784, -5299.6123)
anyb_p[3]["angle"] = 63622
anyb_p[3]["cam"]["pos"] = (735.525391, 524.418701, -11576.4746)
anyb_p[3]["cam"]["target"] = (465.674622, 421.052704, -11651.0684)

# purple mist
anyb_p[6]["requirements"] = REQ_POS
anyb_p[6]["pos"] = (-23524.6152, 250.0, -16220.166)
anyb_p[6]["angle"] = 40758
anyb_p[6]["counter"] = 30

# forest escape
anyb_p[8]["requirements"] = REQ_POS | REQ_CAM
anyb_p[8]["pos"] = (-12433.6016, -235.969193, -17103.998)
anyb_p[8]["angle"] = 29553
anyb_p[8]["cam"]["pos"] = (-12552.8252, -53.5801048, -16729.5313)
anyb_p[8]["cam"]["target"] = (-12433.2979, -106.667023, -17104.9512)
anyb_p[8]["counter"] = 30

# lanayru gate clip
anyb_p[9]["requirements"] = REQ_POS | REQ_CAM
anyb_p[9]["pos"] = (-63026.2852, -9065.92578, 71680.3438)
anyb_p[9]["angle"] = 44248
anyb_p[9]["cam"]["pos"] = (-62655.8125, -8900.91309, 71903.6328)
anyb_p[9]["cam"]["target"] = (-63064.2148, -8969.97656, 71661.0781)
anyb_p[9]["counter"] = 15

# eldin twilight
anyb_p[15]["requirements"] = REQ_POS | REQ_CAM
anyb_p[15]["pos"] = (455.088379, -150.0, 11516.7227)
anyb_p[15]["angle"] = 6058
anyb_p[15]["cam"]["pos"] = (219.367218, -20.1253014, 11157.582)
anyb_p[15]["cam"]["target"] = (482.515137, -39.9999771, 11558.5283)
anyb_p[15]["counter"] = 10

# iza
anyb_p[18]["requirements"] = REQ_POS
anyb_p[18]["pos"] = (5979.97217, 150.0, -2748.34155)
anyb_p[18]["angle"] = 10114

# snowpeak messenger skip
anyb_p[19]["requirements"] = REQ_POS | REQ_CAM
anyb_p[19]["pos"] = (-9294.87988, 980.0, -11712.3838)
anyb_p[19]["angle"] = 346
anyb_p[19]["cam"]["pos"] = (-9309.65137, 1280.4469, -12130.7695)
anyb_p[19]["cam"]["target"] = (-9294.2207, 1180.0, -11692.3945)
anyb_p[19]["counter"] = 10

# spr
anyb_p[20]["requirements"] = REQ_POS
anyb_p[20]["pos"] = (0.0, -150.0, 6000.0)
anyb_p[20]["angle"] = 33768

# bk skip
anyb_p[22]["requirements"] = REQ_POS | REQ_CAM
anyb_p[22]["pos"] = (71.9835968, 1500.00, 2839.01587)
anyb_p[22]["angle"] = 32767
anyb_p[22]["cam"]["pos"] = (71.9835968, 1719.93542, 2969.04565)
anyb_p[22]["cam"]["target"] = (71.9835968, 1660.0, 2839.01587)
anyb_p[22]["counter"] = 30

# morpheel
anyb_p[23]["requirements"] = REQ_POS | REQ_CAM
anyb_p[23]["pos"] = (-1193.0, -23999.00, -770.0)
anyb_p[23]["angle"] = 10754
anyb_p[23]["counter"] = 20

# poe 1 skip
anyb_p[28]["requirements"] = REQ_POS | REQ_CAM
anyb_p[28]["pos"] = (-2046.97168, 0.0, -587.304871)
anyb_p[28]["angle"] = 49030
anyb_p[28]["cam"]["pos"] = (-1779.00293, 213.707397, -584.686768)
anyb_p[28]["cam"]["target"] = (-2047.97168, 130.16568, -587.317139)
anyb_p[28]["counter"] = 10

file = open("any_bite.bin", "wb")

for entry in anyb_p:
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
