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

                if char_index == 0xff:
                    file.write("　")
                else:
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
        {DICT_FILE: "monster_names", DICT_ADDR: {"b": 0x10, "h": 0x5c, "l": 0}, DICT_ITEMS: 384, DICT_BYTES: 8}
    ]

    text(rommap, FILE_JP, textsFixedBytes)

def everything(rommap):
    textJp(rommap)