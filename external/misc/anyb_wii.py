import struct
from enum import IntEnum, unique

REQ_POS = 1
REQ_CAM = 2

default_entry = {
    "requirements": 0,
    "pos": (0.0,0.0,0.0),
    "angle": 0,
    "cam": {"pos":(0,0,0), "target": (0,0,0)},
    "counter": 0,
}

class Requirements(IntEnum):
    POS = 1
    CAM = 2

# order matters
file_names = [
    "ordon_gate_clip",
    "ordon_gate_clip",
    "seam_clip",
    "goats",
    "hugo",
    "faron_twilight",
    "ems",
    "purple_mist",
    "bite",
    "kb1",
    "eldin_twilight",
    "bombhouse_skip",
    "epona_oob_to_flight_by_fowl",
    "kargarok_fight",
    "kargarok_flight",
    "lanayru_twilight",
    "waterfall_sidehop",
    "boss_bug",
    "iza",
    "plumm_oob",
    "enter_lakebed",
    "lakebed_1",
    "pot_push",
    "deku_toad",
    "lakebed_bk_skip",
    "morpheel",
    "mdh_tower",
    "mdh_bridge",
    "messenger_skip",
    "snowpeak_ruins_mbbb",
    "freezard_skip",
    "dark_hammer",
    "bulblin_camp",
    "ag",
    "poe_gate_skip",
    "early_boss_key",
    "death_sword",
    "stallord",
    "stallord",
    "early_city",
    "cits",
    "aeralfos_skip",
    "cits_2",
    "fan_tower",
    "argorok",
    "pot1",
    "stupidroom",
    "pot2",
    "pot_bk",
    "earlypf",
    "zant",
    "hc",
    "kb4",
    "darknut",
    "hc_aeralfos",
    "towerclimb",
    "beast_ganon",
    "horseback",
]

anyb_p = [{**default_entry, "id": i, "filename": file_names[i]} for i in range(len(file_names))]

file_dict = {}
for i, e in enumerate(file_names):
    if not e in file_dict:
        file_dict[e] = [i]
    else:
        file_dict[e].append(i)

def update_entry(filename, data, n = 1):
    count = sum(1 for entry in anyb_p if entry["filename"] == filename)
    if n <= count and n > 0:
        anyb_p[file_dict[filename][n - 1]] = {**anyb_p[file_dict[filename][n - 1]], **data}


# ordon gate clip
update_entry("ordon_gate_clip", n = 1, data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (827.450012, 216.490097, -4533.90625),
    'angle': 498,
    'cam': {'pos': (833.467468, 477.604675, -4241.97266), 'target': (827.497559, 329.622986, -4532.90723)},
    'counter': 10,
})

# back in time
update_entry("ordon_gate_clip", n = 2, data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (466.622467, 319.770752, -11651.3867),
    'angle': 52540,
    'cam': {'pos': (735.525391, 524.418701, -11576.4746), 'target': (465.674622, 421.052704, -11651.0684)},
    'counter': 10,
})

# seam clip
update_entry("seam_clip", data = {
    'requirements': Requirements.POS,
    'pos': (-46261.4805, -7473.1777, 98200.4141),
    'angle': 31612,
    'counter': 30,
})

# hugo
update_entry("hugo", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (701.797302, 85.5212784, -5299.6123),
    'angle': 63622,
    'cam': {'pos': (735.525391, 524.418701, -11576.4746), 'target': (465.674622, 421.052704, -11651.0684)},
})

# purple mist
update_entry("purple_mist", data = {
    'requirements': Requirements.POS,
    'pos': (-23524.6152, 250.0, -16220.166),
    'angle': 40758,
    'counter': 30,
})

update_entry("kb1", data = {
    'requirements': Requirements.POS,
    'pos': (-9717.6035, 337.0316, 97.9661),
    'angle': 16384,
    'counter': 30,
})

update_entry("boss_bug", data = {
    'requirements': Requirements.POS,
    'pos': (-87517.1562, -18789.2812, 38927.0820),
    'angle': 41851,
    'counter': 30,
})

update_entry("plumm_oob", data = {
    'requirements': Requirements.POS,
    'pos': (-104271.3750, -18470.0, 52661.7812),
    'angle': 45103,
    'counter': 30,
})

update_entry("mdh_tower", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (25362.3184, -3028.7673, 10060.8379),
    'angle': 29327,
    'counter': 30,
})

update_entry("mdh_bridge", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (27436.0391, 1300.0, 6575.3115),
    'angle': 32768,
    'counter': 30,
})

update_entry("freezard_skip", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (-125.9265, 33.8123, -3688.0295),
    'angle': 32768,
    'counter': 30,
})

update_entry("dark_hammer", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (0.7448, 0.0, 1330.9711),
    'angle': 32768,
    'counter': 20,
})

# forest escape
update_entry("forest_escape", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (-12433.6016, -235.969193, -17103.998),
    'angle': 29553,
    'cam': {'pos': (-12552.8252, -53.5801048, -16729.5313), 'target': (-12433.2979, -106.667023, -17104.9512)},
    'counter': 30,
})

# lanayru gate clip
update_entry("lanayru_gate_clip", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (-63026.2852, -9065.92578, 71680.3438),
    'angle': 44248,
    'cam': {'pos': (-62655.8125, -8900.91309, 71903.6328), 'target': (-63064.2148, -8969.97656, 71661.0781)},
    'counter': 15,
})

# eldin twilight
update_entry("eldin_twilight", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (455.088379, -150.0, 11516.7227),
    'angle': 6058,
    'cam': {'pos': (219.367218, -20.1253014, 11157.582), 'target': (482.515137, -39.9999771, 11558.5283)},
    'counter': 10,
})

# epona oob to lanayru
update_entry("epona_oob_to_flight_by_fowl", data = {
    'requirements': Requirements.POS,
    'pos': (16501.3535, 3304.0415, 34706.0977),
    'angle': 61639,
    'counter': 10,
})

# iza
update_entry("iza", data = {
    'requirements': Requirements.POS,
    'pos': (5979.97217, 150.0, -2748.34155),
    'angle': 10114,
})

# snowpeak messenger skip
update_entry("messenger_skip", data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (-9294.87988, 980.0, -11712.3838),
    'angle': 346,
    'cam': {'pos': (-9309.65137, 1280.4469, -12130.7695), 'target': (-9294.2207, 1180.0, -11692.3945)},
    'counter': 10,
})

# spr
update_entry("spr", data = {
    'requirements': Requirements.POS,
    'pos': (0.0, 150.0, 6000.0),
    'angle': 33768,
})

# morpheel
update_entry('morpheel', data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (-1193.0, -23999.00, -770.0),
    'angle': 10754,
    'counter': 20,
})

# poe 1 skip
update_entry('poe_1_skip', data = {
    'requirements': Requirements.POS | Requirements.CAM,
    'pos': (-2046.97168, 0.0, -587.304871),
    'angle': 49030,
    'cam': {'pos': (-1779.00293, 213.707397, -584.686768), 'target': (-2047.97168, 130.16568, -587.317139)},
    'counter': 10,
})

# elh bomb boost
update_entry('enter_lakebed', data = {
    'requirements': Requirements.POS,
    'pos': (-87645.3203, -21052.0078, 38436.0898),
    'angle': 45767,
    'counter': 10,
})

# pot push
update_entry('pot_push', data = {
    'requirements': Requirements.POS,
    'pos': (7296.9878, -50.0000, -0.6072),
    'angle': 16374,
    'counter': 20,
})

# lakebed bk skip
update_entry('lakebed_bk_skip', data = {
    'requirements': Requirements.POS,
    'pos': (63.3586, 1500.0000, 3139.0151),
    'angle': 32727,
    'counter': 10,
})

# light sword
update_entry('pot2', data = {
    'requirements': Requirements.POS,
    'pos': (250.0000, -200.0000, 11000.0000),
    'angle': 0,
    'counter': 10,
}) 

# kb4
update_entry('kb4', data = {
    'requirements': Requirements.POS,
    'pos': (-8593.0000, 52.0000, -4873.0000),
    'angle': 24354,
    'counter': 20,
})               

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
