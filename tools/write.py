import pathlib

FILE_CAR = "src/assets"
FILE_TXT = "txt"
FILE_JP = "jp"

EXT_TXT = ".txt"

DICT_FILE = "file"
DICT_BANK = "bank"
DICT_HIGH = "high"
DICT_LOW = "low"
DICT_ITEMS = "items"
DICT_BYTES = "bytes"

def incrementAddr(bank, high, low):
    low += 1
    
    if low >= 0x100:
        low = 0
        high += 1

        if high >= 0x100:
            high = 0
            bank += 1

def writeTextFixedBytes(lang, file, rommap, addr_b, addr_h, addr_l, item_count, byte_count):
    fullpath = pathlib.Path(FILE_CAR) / FILE_TXT / lang / (file + EXT_TXT)
    
    with open (fullpath, 'w') as file:
        for i in range(item_count):
            for j in range(byte_count):
                file.write(rommap[addr_b][addr_h][addr_l])
                incrementAddr(addr_b, addr_h, addr_l)

def text(rommap, lang, textsFixedBytes):
    for d in textsFixedBytes:
        writeTextFixedBytes(lang, d[DICT_FILE], rommap, d[DICT_BANK], d[DICT_HIGH], d[DICT_LOW], d[DICT_ITEMS], d[DICT_BYTES])

def textJp(rommap):
    textsFixedBytes = [
        {DICT_FILE: "monster_names", DICT_BANK: 0x10, DICT_HIGH: 0x5c, DICT_LOW: 0, DICT_ITEMS: 384, DICT_BYTES: 8}
    ]

    text(rommap, FILE_JP, textsFixedBytes)

def everything(rommap):
    textJp(rommap)