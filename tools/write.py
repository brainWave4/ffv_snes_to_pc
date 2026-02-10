import pathlib

FILE_CAR = "src/assets"
FILE_JP = "jp"

DICT_FILE = "file"
DICT_ADDR = "addr"
DICT_PTR = "ptr_addr"
DICT_PTR_BANK = "ptr_bank"
DICT_FUNC = "def"
DICT_ITEMS = "items"
DICT_BYTES = "bytes"
DICT_TEXT = "text"
DICT_RULE = "special_rule"

def writeByte(inner_f, rommap, addr_i, file):
    file.write(rommap[addr_i])

def writeText(inner_f, rommap, addr_i, file):
    cur_val = int.from_bytes(rommap[addr_i])

    match inner_f[DICT_RULE]:
        case "pause_s":
            file.write("[PAUSE ")
            file.write(str(cur_val))
            file.write("s]")
            
            inner_f[DICT_RULE] = ""
        case "str_i":
            text_table = inner_f[DICT_TEXT]["texts"]
            char = text_table[inner_f["prev"]][cur_val]

            file.write(char)

            inner_f[DICT_RULE] = ""
        case "times_then_dec":
            text_table = inner_f[DICT_TEXT]["texts"]
            char = text_table[inner_f["prev"]]

            for i in range(cur_val):
                file.write(char)
            
            inner_f[DICT_RULE] = ""
        case _:
            dict_text = inner_f[DICT_TEXT]
            text_table = dict_text["texts"]
            text_rules = dict_text["rules"]

            if cur_val in text_rules:
                inner_f[DICT_RULE] = text_rules[cur_val]
                inner_f["prev"] = cur_val
            else:
                char = text_table[cur_val]
                file.write(char)

def byBytes(file, inner_f, rommap, addr):
    for i in range(inner_f[DICT_BYTES]):
        addr_i = addr + i
        inner_f[DICT_FUNC](inner_f, rommap, addr_i, file)

def byPointers(file, inner_f, rommap, addr):
    checkpoints = []

    for i in range(inner_f[DICT_ITEMS]):
        addr_ptr_a = inner_f[DICT_PTR] + i * 2
        addr_ptr_b = addr_ptr_a + 1

        target_addr = int.from_bytes(rommap[addr_ptr_b])
        target_addr *= 0x100
        target_addr += int.from_bytes(rommap[addr_ptr_a])
        target_addr += inner_f[DICT_PTR_BANK] * 0x10000
        
        checkpoints.append(target_addr)

    for c in checkpoints:
        while addr < c:
            inner_f[DICT_FUNC](inner_f, rommap, addr, file)
            addr += 1
        file.write("\n")

def byFixedBytes(file, inner_f, rommap, addr):
    byte_count = inner_f[DICT_BYTES]

    for i in range(inner_f[DICT_ITEMS]):
        for j in range(byte_count):
            addr_i = addr + i * byte_count + j
            inner_f[DICT_FUNC](inner_f, rommap, addr_i, file)
        
        file.write("\n")

def writeToFile(filename, file_info, byLoop, inner_f, rommap, addr):
    folder = file_info["folder"]
    ext = file_info["ext"]
    fullpath = pathlib.Path(FILE_CAR) / folder / (filename + ext)
    
    writemode = 'w' if inner_f[DICT_FUNC] == writeText else 'wb'
    
    with open (fullpath, writemode) as file:
        byLoop(file, inner_f, rommap, addr)

    print(f"Written down {fullpath}")

def palette(rommap):
    file_info = {
        "folder": "pal",
        "ext": ".pal"
    }

    for d in [
        {DICT_FILE: "map", DICT_ADDR: 0xd340, DICT_BYTES: 40}
    ]:
        inner_f = {
            DICT_FUNC: writeByte,
            DICT_BYTES: d[DICT_BYTES]
        }
        writeToFile(d[DICT_FILE], file_info, byBytes, inner_f, rommap, d[DICT_ADDR])

def text(rommap, lang, textsPtrs, textsFixedBytes):
    file_info = {
        "folder": "txt/" + lang,
        "ext": ".txt"
    }

    for d in textsPtrs:
        inner_f = {
            DICT_FUNC: writeText,
            DICT_PTR: d[DICT_PTR],
            DICT_PTR_BANK: d[DICT_PTR_BANK],
            DICT_ITEMS: d[DICT_ITEMS],
            DICT_TEXT: d[DICT_TEXT],
            DICT_RULE: ""
        }
        writeToFile(d[DICT_FILE], file_info, byPointers, inner_f, rommap, d[DICT_ADDR])
    
    for d in textsFixedBytes:
        inner_f = {
            DICT_FUNC: writeText,
            DICT_ITEMS: d[DICT_ITEMS],
            DICT_BYTES: d[DICT_BYTES],
            DICT_TEXT: d[DICT_TEXT],
            DICT_RULE: ""
        }
        writeToFile(d[DICT_FILE], file_info, byFixedBytes, inner_f, rommap, d[DICT_ADDR])

def textJp(rommap):
    import text_table_sfc as text_table

    textsPtrs = [
        {DICT_FILE: "menu_text", DICT_ADDR: 0xfa9d, DICT_PTR: 0xf987, DICT_PTR_BANK: 0, DICT_ITEMS: 139, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "dialogs", DICT_ADDR: 0xa0000, DICT_PTR: 0x82220, DICT_PTR_BANK: 0xa, DICT_ITEMS: 2176, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "map_titles", DICT_ADDR: 0x107200, DICT_PTR: 0x107000, DICT_PTR_BANK: 0x10, DICT_ITEMS: 163, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "battle_dialogs", DICT_ADDR: 0x10f1d4, DICT_PTR: 0x10f000, DICT_PTR_BANK: 0x10, DICT_ITEMS: 234, DICT_TEXT: text_table.text[1]},
        {DICT_FILE: "battle_messages", DICT_ADDR: 0x113ba9, DICT_PTR: 0x1139a9, DICT_PTR_BANK: 0x11, DICT_ITEMS: 256, DICT_TEXT: text_table.text[1]},
        {DICT_FILE: "item_descriptions", DICT_ADDR: 0x114100, DICT_PTR: 0x114000, DICT_PTR_BANK: 0x11, DICT_ITEMS: 256, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "job_descriptions", DICT_ADDR: 0x11724a, DICT_PTR: 0x117140, DICT_PTR_BANK: 0x11, DICT_ITEMS: 22, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "ability_descriptions", DICT_ADDR: 0x117337, DICT_PTR: 0x11716c, DICT_PTR_BANK: 0x11, DICT_ITEMS: 111, DICT_TEXT: text_table.text[0]},
    ]

    textsFixedBytes = [
        {DICT_FILE: "monster_names", DICT_ADDR: 0x105c00, DICT_ITEMS: 384, DICT_BYTES: 8, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "monster_specials", DICT_ADDR: 0x108700, DICT_ITEMS: 64, DICT_BYTES: 8, DICT_TEXT: text_table.text[1]},
        {DICT_FILE: "item_names", DICT_ADDR: 0x111380, DICT_ITEMS: 256, DICT_BYTES: 9, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "magic_names", DICT_ADDR: 0x111c80, DICT_ITEMS: 87, DICT_BYTES: 6, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "attack_names", DICT_ADDR: 0x111e8a, DICT_ITEMS: 161, DICT_BYTES: 9, DICT_TEXT: text_table.text[1]},
        {DICT_FILE: "status_names", DICT_ADDR: 0x1128b6, DICT_ITEMS: 24, DICT_BYTES: 8, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "shop_types", DICT_ADDR: 0x112d00, DICT_ITEMS: 8, DICT_BYTES: 8, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "char_names", DICT_ADDR: 0x115500, DICT_ITEMS: 5, DICT_BYTES: 6, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "job_names", DICT_ADDR: 0x115600, DICT_ITEMS: 22, DICT_BYTES: 8, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "battle_commands", DICT_ADDR: 0x115800, DICT_ITEMS: 96, DICT_BYTES: 5, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "passive_abilities", DICT_ADDR: 0x116200, DICT_ITEMS: 33, DICT_BYTES: 8, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "special_abilities", DICT_ADDR: 0x115600, DICT_ITEMS: 105, DICT_BYTES: 9, DICT_TEXT: text_table.text[1]}
    ]

    text(rommap, FILE_JP, textsPtrs, textsFixedBytes)

def everything(rommap):
    palette(rommap)
    textJp(rommap)