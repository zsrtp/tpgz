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
file_names = ["goats", "ordon_gate_clip", "goats_2", "faron_twilight", "ems", "purple_mist", "forest_bit", "forest_2", "ookless", "eldin_twilight", "lanayru_gate_clip", "pillar_clip", "lakebed_1", "deku_toad", "karg", "lanayru_twilight", "boss_bug", "kb2", "kb2", "corotd", "gm", "dangoro", "kb1", "lakebed_bk_skip", "morpheel", "star_1", "mdh_tower", "mdh_bridge", "post_mdh", "iza_1_skip", "lh_cave", "camp", "ag", "poe_1_skip", "death_sword_skip", "stallord", "post_ag", "spr", "darkhammer", "spr_superjump", "spr_bk_lja", "spr_bk_lja", "blizzeta", "nf_bomb_boost", "grove_skip", "grove_boost", "tot", "tot_early_poe", "tot_statue_throws", "tot_early_hp", "tot_darknut", "dot_skip", "post_tot", "hotspring", "silver_rupee", "ice_puzzle", "hv_archery", "cits_1", "aeralfos_skip", "cits_2", "cits_poe_cycle", "fan_tower", "argorok", "star_2", "palace_1", "palace_2", "early_platform", "zant", "coo", "coo_10", "coo_20", "coo_30", "cats", "hc", "hc_darknut", "hc_tower", "beast_ganon", "horseback_ganon", ]

hundo_p = [{**default_entry, "id": i, "filename": file_names[i]} for i in range(78)]


hundo_p[1]["requirements"] = REQ_POS | REQ_CAM
hundo_p[1]["cam"]["target"] = 827.497559, 329.622986, -4532.90723
hundo_p[1]["cam"]["pos"] = 833.467468, 477.604675, -4241.97266
hundo_p[1]["angle"] = 498
hundo_p[1]["pos"] = 827.450012, 216.490097, -4533.90625
hundo_p[1]["counter"] = 10

hundo_p[5]["requirements"] = REQ_POS
hundo_p[5]["angle"] = 40758
hundo_p[5]["pos"] = -23524.6152, 250.0, -16220.166
hundo_p[5]["counter"] = 30

hundo_p[10]["requirements"] = REQ_POS | REQ_CAM
hundo_p[10]["cam"]["target"] = -63064.2148, -8969.97656, 71661.0781
hundo_p[10]["cam"]["pos"] = -62655.8125, -8900.91309, 71903.6328
hundo_p[10]["angle"] = 44248
hundo_p[10]["pos"] = -63026.2852, -9065.92578, 71680.3438
hundo_p[10]["counter"] = 15

hundo_p[16]["requirements"] = REQ_POS
hundo_p[16]["angle"] = 21504
hundo_p[16]["pos"] = -89100.00, -18811.2363, 39410.00

hundo_p[17]["requirements"] = REQ_POS | REQ_CAM
hundo_p[17]["cam"]["target"] = -92098.1797, -5398.54883, 22599.9102
hundo_p[17]["cam"]["pos"] = -92795.1328, -5302.87988, 22505.3359
hundo_p[17]["angle"] = 14957
hundo_p[17]["counter"] = 30

hundo_p[19]["requirements"] = REQ_POS
hundo_p[19]["angle"] = 27714
hundo_p[19]["pos"] = -13715.0712, 0.00, -14238.0654

hundo_p[23]["requirements"] = REQ_POS | REQ_CAM
hundo_p[23]["cam"]["target"] = 71.9835968, 1660.0, 2839.01587
hundo_p[23]["cam"]["pos"] = 71.9835968, 1719.93542, 2969.04565
hundo_p[23]["angle"] = 32767
hundo_p[23]["pos"] = 71.9835968, 1500.00, 2839.01587
hundo_p[23]["counter"] = 30

hundo_p[26]["requirements"] = REQ_POS | REQ_CAM
hundo_p[26]["cam"]["target"] = 25256.7285, -2919.95215, 2839.01587
hundo_p[26]["cam"]["pos"] = 10193.6064, 25254.7852, -2874.2627
hundo_p[26]["angle"] = 32025
hundo_p[26]["pos"] = 25254.6875, -3031.50854, 10222.1445
hundo_p[26]["counter"] = 15

hundo_p[33]["requirements"] = REQ_POS | REQ_CAM
hundo_p[33]["cam"]["target"] = -2047.97168, 130.16568, -587.317139
hundo_p[33]["cam"]["pos"] = -1779.00293, 213.707397, -584.686768
hundo_p[33]["angle"] = 49030
hundo_p[33]["pos"] = -2046.97168, 0.0, -587.304871
hundo_p[33]["counter"] = 10

hundo_p[39]["requirements"] = REQ_POS | REQ_CAM
hundo_p[39]["cam"]["target"] = 1529.35425, 466.16306, 3684.08252
hundo_p[39]["cam"]["pos"] = 1765.20581, 691.830688, 3662.42749
hundo_p[39]["angle"] = 50120
hundo_p[39]["pos"] = 1530.35, 359.56, 3683.99
hundo_p[39]["counter"] = 30

hundo_p[40]["requirements"] = REQ_POS
hundo_p[40]["angle"] = 32887
hundo_p[40]["pos"] = -2171.19, 973.96, -2384.89
hundo_p[40]["counter"] = 30

hundo_p[44]["requirements"] = REQ_POS
hundo_p[44]["cam"]["target"] = -9965.82617, 2176.59863, 4084.57056
hundo_p[44]["cam"]["pos"] = -10415.2363, 2212.92139, 4370.72852
hundo_p[44]["angle"] = 22306
hundo_p[44]["pos"] = -9966.6689, 2000.0, 4085.1082
hundo_p[44]["counter"] = 30

hundo_p[45]["requirements"] = REQ_POS
hundo_p[45]["cam"]["target"] = -1765.32605, 1180.38452, 4303.98584
hundo_p[45]["cam"]["pos"] = -1368.4314, 1347.8916, 4057.84863
hundo_p[45]["angle"] = 54947
hundo_p[45]["pos"] = -1764.4763, 1000.0, 4303.4585
hundo_p[45]["counter"] = 30

hundo_p[51]["requirements"] = REQ_POS | REQ_CAM
hundo_p[51]["cam"]["target"] = 1361.59766, -33.1954155, -1090.47632
hundo_p[51]["cam"]["pos"] = 1396.36316, 9.51973343, -719.644531
hundo_p[51]["angle"] = 33673
hundo_p[51]["pos"] = 1361.68408, -143.56076, -1089.4801

hundo_p[54]["requirements"] = REQ_POS | REQ_CAM
hundo_p[54]["cam"]["target"] = 961.308044, 203.885788, 4184.82471
hundo_p[54]["cam"]["pos"] = 1220.0835, 320.043884, 4269.48779
hundo_p[54]["angle"] = 45836
hundo_p[54]["pos"] = 962.257813, 100.0, 4185.1377
hundo_p[54]["counter"] = 30

hundo_p[56]["requirements"] = REQ_POS
hundo_p[56]["angle"] = 64520
hundo_p[56]["pos"] = 3125.57, -62.16, -9360.22
hundo_p[56]["counter"] = 30

hundo_p[57]["requirements"] = REQ_POS | REQ_CAM
hundo_p[57]["cam"]["target"] = 1313.54285, -234.203003, 5545.16846
hundo_p[57]["cam"]["pos"] = 1027.53259, -108.096123, 5605.23047
hundo_p[57]["angle"] = 16384
hundo_p[57]["pos"] = 1309.60645, -240.0, 5533.43848
hundo_p[57]["counter"] = 10

hundo_p[72]["requirements"] = REQ_POS | REQ_CAM
hundo_p[72]["cam"]["target"] = 5309.32373, 160.1, -3581.83423
hundo_p[72]["cam"]["pos"] = 4893.25391, 160.117676, -3524.51245
hundo_p[72]["angle"] = 17282
hundo_p[72]["pos"] = 5238.59, 0.00, -3575.74
hundo_p[72]["counter"] = 30

file = open("hundo.bin", "wb")

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
