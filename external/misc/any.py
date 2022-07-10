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
    "ems", 
    "purple_mist", 
    "forest_bit", 
    "forest_escape", 
    "gorge_void", 
    "rupee_roll", 
    "lanayru_gate_clip", 
    "pillar_clip", 
    "lakebed_1", 
    "deku_toad", 
    "karg", 
    "eldin_twilight", 
    "lanayru_twilight", 
    "waterfall_sidehop", 
    "boss_bug", 
    "iza", 
    "norgor", 
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
    "cits_early", 
    "cits_1", 
    "aeralfos_skip", 
    "cits_2", 
    "fan_tower", 
    "argorok", 
    "palace_1", 
    "palace_2", 
    "early_platform", 
    "zant", 
    "hc", 
    "darknut", 
    "hc_tower", 
    "beast_ganon", 
    "horseback_ganon",
]

any_p = [{**default_entry, "id": i, "filename": file_names[i]} for i in range(49)]

# ordon gate clip
any_p[0]["requirements"] = REQ_POS | REQ_CAM
any_p[0]["pos"] = (827.450012, 216.490097, -4533.90625)
any_p[0]["angle"] = 498
any_p[0]["cam"]["pos"] = (833.467468, 477.604675, -4241.97266)
any_p[0]["cam"]["target"] = (827.497559, 329.622986, -4532.90723)
any_p[0]["counter"] = 10

# back in time
any_p[1]["requirements"] = REQ_POS | REQ_CAM
any_p[1]["pos"] = (466.622467, 319.770752, -11651.3867)
any_p[1]["angle"] = 52540
any_p[1]["cam"]["pos"] = (735.525391, 524.418701, -11576.4746)
any_p[1]["cam"]["target"] = (465.674622, 421.052704, -11651.0684)
any_p[1]["counter"] = 10

# hugo
any_p[3]["requirements"] = REQ_POS | REQ_CAM
any_p[3]["pos"] = (701.797302, 85.5212784, -5299.6123)
any_p[3]["angle"] = 63622
any_p[3]["cam"]["pos"] = (735.525391, 524.418701, -11576.4746)
any_p[3]["cam"]["target"] = (465.674622, 421.052704, -11651.0684)

# purple mist
any_p[5]["requirements"] = REQ_POS
any_p[5]["pos"] = (-23524.6152, 250.0, -16220.166)
any_p[5]["angle"] = 40758
any_p[5]["counter"] = 30

# forest escape
any_p[7]["requirements"] = REQ_POS | REQ_CAM
any_p[7]["pos"] = (-12433.6016, -235.969193, -17103.998)
any_p[7]["angle"] = 29553
any_p[7]["cam"]["pos"] = (-12552.8252, -53.5801048, -16729.5313)
any_p[7]["cam"]["target"] = (-12433.2979, -106.667023, -17104.9512)
any_p[7]["counter"] = 30

# gorge void
any_p[8]["requirements"] = REQ_POS
any_p[8]["pos"] = (-9704.47266, -7200.0, 58475.5195)
any_p[8]["angle"] = 54288

# rupee roll
any_p[9]["requirements"] = REQ_POS | REQ_CAM
any_p[9]["pos"] = (-11130.208, -5700.0, 56423.1953)
any_p[9]["angle"] = 31571
any_p[9]["cam"]["pos"] = (-11178.1504, -5506.71338, 56843.1797)
any_p[9]["cam"]["target"] = (-11124.4697, -5589.99902, 56373.5195)
any_p[9]["counter"] = 15

# lanayru gate clip
any_p[10]["requirements"] = REQ_POS | REQ_CAM
any_p[10]["pos"] = (-63026.2852, -9065.92578, 71680.3438)
any_p[10]["angle"] = 44248
any_p[10]["cam"]["pos"] = (-62655.8125, -8900.91309, 71903.6328)
any_p[10]["cam"]["target"] = (-63064.2148, -8969.97656, 71661.0781)
any_p[10]["counter"] = 15

# eldin twilight
any_p[15]["requirements"] = REQ_POS | REQ_CAM
any_p[15]["pos"] = (455.088379, -150.0, 11516.7227)
any_p[15]["angle"] = 6058
any_p[15]["cam"]["pos"] = (219.367218, -20.1253014, 11157.582)
any_p[15]["cam"]["target"] = (482.515137, -39.9999771, 11558.5283)
any_p[15]["counter"] = 10

# boss bug
any_p[18]["requirements"] = REQ_POS
any_p[18]["pos"] = (-89100.00, -18811.2363, 39410.00)
any_p[18]["angle"] = 21504

# iza
any_p[19]["requirements"] = REQ_POS
any_p[19]["pos"] = (5979.97217, 150.0, -2748.34155)
any_p[19]["angle"] = 10114

# norgor
any_p[20]["requirements"] = REQ_POS | REQ_CAM
any_p[20]["pos"] = (173.71, -186.52, -3633.71)
any_p[20]["angle"] = 46568
any_p[20]["cam"]["pos"] = (501.768982, -5.045784, -3586.1145)
any_p[20]["cam"]["target"] = (174.411758, -70.5306549, -3668.91406)
any_p[20]["counter"] = 15

# snowpeak messenger skip
any_p[21]["requirements"] = REQ_POS | REQ_CAM
any_p[21]["pos"] = (-9294.87988, 980.0, -11712.3838)
any_p[21]["angle"] = 346
any_p[21]["cam"]["pos"] = (-9309.65137, 1280.4469, -12130.7695)
any_p[21]["cam"]["target"] = (-9294.2207, 1180.0, -11692.3945)
any_p[21]["counter"] = 10

# spr
any_p[22]["requirements"] = REQ_POS
any_p[22]["pos"] = (0.0, -150.0, 6000.0)
any_p[22]["angle"] = 33768

# bk skip
any_p[24]["requirements"] = REQ_POS | REQ_CAM
any_p[24]["pos"] = (71.9835968, 1500.00, 2839.01587)
any_p[24]["angle"] = 32767
any_p[24]["cam"]["pos"] = (71.9835968, 1719.93542, 2969.04565)
any_p[24]["cam"]["target"] = (71.9835968, 1660.0, 2839.01587)
any_p[24]["counter"] = 30

# morpheel
any_p[25]["requirements"] = REQ_POS | REQ_CAM
any_p[25]["pos"] = (-1193.0, -23999.00, -770.0)
any_p[25]["angle"] = 10754
any_p[25]["counter"] = 20

# poe 1 skip
any_p[30]["requirements"] = REQ_POS | REQ_CAM
any_p[30]["pos"] = (-2046.97168, 0.0, -587.304871)
any_p[30]["angle"] = 49030
any_p[30]["cam"]["pos"] = (-1779.00293, 213.707397, -584.686768)
any_p[30]["cam"]["target"] = (-2047.97168, 130.16568, -587.317139)
any_p[30]["counter"] = 10

# city 1
any_p[35]["requirements"] = REQ_POS | REQ_CAM
any_p[35]["pos"] = (1309.60645, -240.0, 5533.43848)
any_p[35]["angle"] = 16384
any_p[35]["cam"]["pos"] = (1027.53259, -108.096123, 5605.23047)
any_p[35]["cam"]["target"] = (1313.54285, -234.203003, 5545.16846)
any_p[35]["counter"] = 10

file = open("any.bin", "wb")

for entry in any_p:
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
