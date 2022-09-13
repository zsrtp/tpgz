#!/usr/bin/python3

"""
Generates the metadata file for the any% save files.
"""

import sys
import argparse
import copy
from enum import IntEnum, unique
import struct


@unique
class Platform(IntEnum):
    GCN = 0
    WII = 1


class Requirements(IntEnum):
    POS = 1
    CAM = 2


def main(args=None):
    parser = argparse.ArgumentParser(
        sys.argv[0], description="A tool to generate the metadata file for the any% save files.")
    parser.add_argument(
        "-p", "--platform", type=str.upper, choices=[e.name for e in Platform], default=Platform.GCN.name, help="The platform to generate for.")
    args = parser.parse_args()

    args.platform = Platform[args.platform]

    default_entry = {
        "requirements": 0,
        "pos": (0.0, 0.0, 0.0),
        "angle": 0,
        "cam": {"pos": (0, 0, 0), "target": (0, 0, 0)},
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

    if args.platform is Platform.WII:
        file_names = [
            "ordon_gate_clip",
            "bit",
            "goats",
            "hugo",
            "ems",
            "purple_mist",
            "forest_temple_1",
            "early_gale",
            "deku_like_skip",
            "diababa",
            "mailman_skip",
            "lanayru_gate_clip",
            "kargarok_fight",
            "kargarok_flight",
            "eldin_twilight",
            "bombhouse_skip",
            "zora_text_skip",
            "midna_dive",
            "lakebed_1",
            "jake",
            "lanayru_twilight",
            "waterfall_sidehop",
            "boss_bug",
            "iza",
            "deku_toad",
            "morpheel",
            "mdh_tower",
            "mdh_bridge",
            "bublin_camp",
            "ag",
            "poe_1_skip",
            "death_sword",
            "stallord",
            "spr",
            "spr_boost",
            "spr_freezard",
            "darkhammer",
            "early_city",
            "cits",
            "arealfos",
            "cits_2",
            "cits_tower",
            "argarok",
            "palace_1",
            "palace_2",
            "early_platform",
            "zant",
            "hyrule_castle",
            "darknut",
            "tower_climb",
            "beast_ganon",
            "horseback_ganon",
        ]

    any_p = [{**copy.deepcopy(default_entry), "id": i, "filename": name}
             for i, name in enumerate(file_names)]

    file_dict = {e: i for i, e in enumerate(file_names)}

    def update_entry(filename, data):
        if filename in file_names:
            any_p[file_dict[filename]] = {**any_p[file_dict[filename]], **data}

    # ordon gate clip
    update_entry("ordon_gate_clip", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (827.450012, 216.490097, -4533.90625),
        'angle': 498,
        'cam': {
            'pos': (833.467468, 477.604675, -4241.97266),
            'target': (827.497559, 329.622986, -4532.90723)
        },
        'counter': 10
    })

    # back in time
    update_entry("bit", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (466.622467, 319.770752, -11651.3867),
        'angle': 52540,
        'cam': {
            'pos': (735.525391, 524.418701, -11576.4746),
            'target': (465.674622, 421.052704, -11651.0684)
        },
        'counter': 10
    })

    # hugo
    update_entry("hugo", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (701.797302, 85.5212784, -5299.6123),
        'angle': 63622,
        'cam': {
            'pos': (735.525391, 524.418701, -11576.4746),
            'target': (465.674622, 421.052704, -11651.0684)
        },
    })

    # purple mist
    update_entry("purple_mist", {
        'requirements': Requirements.POS,
        'pos': (-23524.6152, 250.0, -16220.166),
        'angle': 40758,
        'counter': 30
    })

    # forest escape
    update_entry("forest_escape", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (-12433.6016, -235.969193, -17103.998),
        'angle': 29553,
        'cam': {
            'pos': (-12552.8252, -53.5801048, -16729.5313),
            'target': (-12433.2979, -106.667023, -17104.9512)
        },
        'counter': 30
    })

    # gorge void
    update_entry("gorge_void", {
        'requirements': Requirements.POS,
        'pos': (-9704.47266, -7200.0, 58475.5195),
        'angle': 54288,
    })

    # rupee roll
    update_entry("rupee_roll", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (-11130.208, -5700.0, 56423.1953),
        'angle': 31571,
        'cam': {
            'pos': (-11178.1504, -5506.71338, 56843.1797),
            'target': (-11124.4697, -5589.99902, 56373.5195)
        },
        'counter': 15
    })

    # lanayru gate clip
    update_entry("lanayru_gate_clip", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (-63026.2852, -9065.92578, 71680.3438),
        'angle': 44248,
        'cam': {
            'pos': (-62655.8125, -8900.91309, 71903.6328),
            'target': (-63064.2148, -8969.97656, 71661.0781)
        },
        'counter': 15
    })

    # eldin twilight
    update_entry("eldin_twilight", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (455.088379, -150.0, 11516.7227),
        'angle': 6058,
        'cam': {
            'pos': (219.367218, -20.1253014, 11157.582),
            'target': (482.515137, -39.9999771, 11558.5283)
        },
        'counter': 10
    })

    # boss bug
    update_entry("boss_bug", {
        'requirements': Requirements.POS,
        'pos': (-89100.00, -18811.2363, 39410.00),
        'angle': 21504,
    })

    # iza
    update_entry("iza", {
        'requirements': Requirements.POS,
        'pos': (5979.97217, 150.0, -2748.34155),
        'angle': 10114,
    })

    # norgor
    update_entry("norgor", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (173.71, -186.52, -3633.71),
        'angle': 46568,
        'cam': {
            'pos': (501.768982, -5.045784, -3586.1145),
            'target': (174.411758, -70.5306549, -3668.91406)
        },
        'counter': 15
    })

    # snowpeak messenger skip
    update_entry("spr_warp", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (-9294.87988, 980.0, -11712.3838),
        'angle': 346,
        'cam': {
            'pos': (-9309.65137, 1280.4469, -12130.7695),
            'target': (-9294.2207, 1180.0, -11692.3945)
        },
        'counter': 10
    })

    # spr
    update_entry("spr", {
        'requirements': Requirements.POS,
        'pos': (0.0, -150.0, 6000.0),
        'angle': 33768,
    })

    # bk skip
    update_entry("lakebed_bk_skip", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (71.9835968, 1500.00, 2839.01587),
        'angle': 32767,
        'cam': {
            'pos': (71.9835968, 1719.93542, 2969.04565),
            'target': (71.9835968, 1660.0, 2839.01587)
        },
        'counter': 30
    })

    # morpheel
    update_entry("morpheel", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (-1193.0, -23999.00, -770.0),
        'angle': 10754,
        '10754': 20
    })

    # poe 1 skip
    update_entry("poe_1_skip", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (-2046.97168, 0.0, -587.304871),
        'angle': 49030,
        'cam': {
            'pos': (-1779.00293, 213.707397, -584.686768),
            'target': (-2047.97168, 130.16568, -587.317139)
        },
        'counter': 10
    })

    # city 1
    update_entry("cits_1", {
        'requirements': Requirements.POS | Requirements.CAM,
        'pos': (1309.60645, -240.0, 5533.43848),
        'angle': 16384,
        'cam': {
            'pos': (1027.53259, -108.096123, 5605.23047),
            'target': (1313.54285, -234.203003, 5545.16846)
        },
        'counter': 10
    })

    # Wii specific entries

    update_entry("early_gale", {
        'requirements': Requirements.POS,
        'pos': (-3000, 4302.1, 5084.73),
        'angle': 32768,
        'counter': 10
    })

    # update_entry("spr_boost", {
    #     'requirements': Requirements.POS,
    #     'pos': (2100.9147, 0.0366, -1984.2080),
    #     'angle': 49152,
    #     'counter': 50
    # })

    update_entry("midna_dive", {
        'requirements': Requirements.POS,
        'pos': (-89349.5132, -18829.6895, 39521.6523),
        'angle': 31044,
        'counter': 10
    })

    file = open("any.bin", "wb")

    for entry in any_p:
        print(entry)
        file.write(entry["requirements"].to_bytes(1, "big", signed=False))
        file.write(int(0).to_bytes(1, "big", signed=False))  # padding
        file.write(entry["angle"].to_bytes(2, "big", signed=False))
        file.write(struct.pack('>fff', *entry["pos"]))
        file.write(struct.pack('>fff', *entry["cam"]["pos"]))
        file.write(struct.pack('>fff', *entry["cam"]["target"]))
        file.write(entry["counter"].to_bytes(4, "big", signed=False))
        file.write(struct.pack(">32s", entry["filename"].encode("ascii")))
        file.write(int(0).to_bytes(4, "big", signed=False))  # padding


if __name__ == "__main__":
    main(sys.argv)
