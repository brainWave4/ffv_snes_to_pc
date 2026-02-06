import pathlib

FILE_CAR = "src/assets"
FILE_TXT = "txt"
FILE_JP = "jp"

EXT_TXT = ".txt"

DICT_FILE = "file"
DICT_ADDR = "addr"
DICT_ITEMS = "items"
DICT_BYTES = "bytes"

kana = "バばビびブぶベべボぼガがギぎグぐゲげゴごザざジじズずゼぜゾぞダだヂぢヅづデでドどヴパぱピぴプぷペぺポぽ０１２３４５６７８９ｍｈｐハはヒひフふヘへホほカかキきクくケけコこサさシしスすセせソそタたチちツつテてトとウうアあイいエえオおナなニにヌぬネねノのマまミみムむメめモもラらリりルるレれロろヤやユゆヨよワわンんヲをッっャゃュゅョょァーィ…ゥ！ェ？ォ"

def incrementAddr(addr):
    addr["l"] += 1

    if addr["l"] >= 0x100:
        addr["l"] = 0
        addr["h"] += 1

        if addr["h"] >= 0x100:
            addr["h"] = 0
            addr["b"] += 1

def writeTextFixedBytes(lang, file, rommap, addr, item_count, byte_count):
    fullpath = pathlib.Path(FILE_CAR) / FILE_TXT / lang / (file + EXT_TXT)

    with open (fullpath, 'w') as file:
        for i in range(item_count):
            for j in range(byte_count):
                char_index = int.from_bytes(rommap[addr["b"]][addr["h"]][addr["l"]])

                if char_index < 0xCD:
                    offset = 0x20
                    char = kana[char_index - offset]
                    file.write(char)
                
                incrementAddr(addr)
            
            file.write("\n")

def text(rommap, lang, textsFixedBytes):
    for d in textsFixedBytes:
        writeTextFixedBytes(lang, d[DICT_FILE], rommap, d[DICT_ADDR], d[DICT_ITEMS], d[DICT_BYTES])

def textJp(rommap):
    textsFixedBytes = [
        {DICT_FILE: "monster_names", DICT_ADDR: {"b": 0x10, "h": 0x5c, "l": 0}, DICT_ITEMS: 384, DICT_BYTES: 8},
        {DICT_FILE: "monster_specials", DICT_ADDR: {"b": 0x10, "h": 0x87, "l": 0}, DICT_ITEMS: 64, DICT_BYTES: 8},
        {DICT_FILE: "item_names", DICT_ADDR: {"b": 0x11, "h": 0x13, "l": 0x80}, DICT_ITEMS: 256, DICT_BYTES: 9},
        {DICT_FILE: "magic_names", DICT_ADDR: {"b": 0x11, "h": 0x1c, "l": 0x80}, DICT_ITEMS: 72, DICT_BYTES: 6},
        {DICT_FILE: "summon_attacks", DICT_ADDR: {"b": 0x11, "h": 0x1e, "l": 0x30}, DICT_ITEMS: 15, DICT_BYTES: 6},
        {DICT_FILE: "attack_names", DICT_ADDR: {"b": 0x11, "h": 0x1e, "l": 0x8a}, DICT_ITEMS: 161, DICT_BYTES: 9},
        {DICT_FILE: "status_names", DICT_ADDR: {"b": 0x11, "h": 0x28, "l": 0xb6}, DICT_ITEMS: 24, DICT_BYTES: 8},
        {DICT_FILE: "shop_types", DICT_ADDR: {"b": 0x11, "h": 0x2d, "l": 0}, DICT_ITEMS: 8, DICT_BYTES: 8},
        {DICT_FILE: "char_names", DICT_ADDR: {"b": 0x11, "h": 0x55, "l": 0}, DICT_ITEMS: 5, DICT_BYTES: 6},
        {DICT_FILE: "job_names", DICT_ADDR: {"b": 0x11, "h": 0x56, "l": 0}, DICT_ITEMS: 22, DICT_BYTES: 8},
        {DICT_FILE: "battle_commands", DICT_ADDR: {"b": 0x11, "h": 0x58, "l": 0}, DICT_ITEMS: 96, DICT_BYTES: 5},
        {DICT_FILE: "passive_abilities", DICT_ADDR: {"b": 0x11, "h": 0x62, "l": 0}, DICT_ITEMS: 33, DICT_BYTES: 8},
        {DICT_FILE: "special_abilities", DICT_ADDR: {"b": 0x11, "h": 0x56, "l": 0}, DICT_ITEMS: 105, DICT_BYTES: 9}
    ]

    text(rommap, FILE_JP, textsFixedBytes)

def everything(rommap):
    textJp(rommap)