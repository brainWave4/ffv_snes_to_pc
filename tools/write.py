import pathlib

FILE_CAR = "src/assets"
FILE_JP = "jp"

DICT_FILE = "file"
DICT_ADDR = "addr"
DICT_END = "addr_end"
DICT_HEADER = "bin_header"
DICT_PTR = "ptr_addr"
DICT_PTR_BANK = "ptr_bank"
DICT_DEPTH = "texture_depth"
DICT_WIDTH = "texture_width"
DICT_HEIGHT = "texture_height"
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

def byAddrRange(file, inner_f, rommap, addr):
    while addr < inner_f[DICT_END]:
        inner_f[DICT_FUNC](inner_f, rommap, addr, file)
        
        addr += 1

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

def byItemsTimesBytes(file, inner_f, rommap, addr):
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
        if DICT_HEADER in inner_f:
            file.write(inner_f[DICT_HEADER])

        byLoop(file, inner_f, rommap, addr)

    print(f"Written down {fullpath}")

def writeFilesTimesItems(item_count, filename, file_info, byLoop, inner_f, rommap, addr):
    for i in range(item_count):
        final_name = filename

        final_name += f"{item_count:03d}"
        
        writeToFile(final_name, file_info, byLoop, inner_f, rommap, addr)

def binaryData(rommap):
    file_info = {
        "folder": "data",
        "ext": ".bin"
    }

    for d in [
        {DICT_FILE: "map_anim_props", DICT_ADDR: 0x9d9b, DICT_END: 0xa18b},
        {DICT_FILE: "unknown_c0cf00", DICT_ADDR: 0xcf00, DICT_END: 0xd240},
        {DICT_FILE: "unknown_c0d240", DICT_ADDR: 0xd240, DICT_END: 0xd340},
        {DICT_FILE: "rng_table", DICT_ADDR: 0xfec0, DICT_END: 0xffc0},
        {DICT_FILE: "unknown_c32000", DICT_ADDR: 0x32000, DICT_END: 0x37e4d},
        {DICT_FILE: "cutscene_code", DICT_ADDR: 0x37e4d, DICT_END: 0x3a06f},
        {DICT_FILE: "sub_tilemaps", DICT_ADDR: 0xb0290, DICT_END: 0xdf9ff},
        {DICT_FILE: "map_pal_anim", DICT_ADDR: 0xdfa40, DICT_END: 0xdfb48},
        {DICT_FILE: "map_props", DICT_ADDR: 0xe9c00, DICT_END: 0xed000},
        {DICT_FILE: "world_tile_props", DICT_ADDR: 0xfea00, DICT_END: 0xff0c0},
        {DICT_FILE: "world_tilesets", DICT_ADDR: 0xff0c0, DICT_END: 0xff9c0},
        {DICT_FILE: "world_tile_attr", DICT_ADDR: 0xff9c0, DICT_END: 0xffcc0},
        {DICT_FILE: "monster_props", DICT_ADDR: 0x100000, DICT_END: 0x103000},
        {DICT_FILE: "battle_props", DICT_ADDR: 0x103000, DICT_END: 0x105000},
        {DICT_FILE: "monster_items", DICT_ADDR: 0x105000, DICT_END: 0x105600},
        {DICT_FILE: "monster_control", DICT_ADDR: 0x105600, DICT_END: 0x105c00},
        {DICT_FILE: "battle_groups_random", DICT_ADDR: 0x106800, DICT_END: 0x107000},
        {DICT_FILE: "battle_groups_events", DICT_ADDR: 0x107800, DICT_END: 0x107a00},
        {DICT_FILE: "battle_groups_world", DICT_ADDR: 0x107a00, DICT_END: 0x108000},
        {DICT_FILE: "battle_groups_sub", DICT_ADDR: 0x108000, DICT_END: 0x108400},
        {DICT_FILE: "battle_rates_world", DICT_ADDR: 0x108400, DICT_END: 0x1084c0},
        {DICT_FILE: "battle_rates_sub", DICT_ADDR: 0x108400, DICT_END: 0x108600},
        {DICT_FILE: "monster_release", DICT_ADDR: 0x108600, DICT_END: 0x108700},
        {DICT_FILE: "monster_pos", DICT_ADDR: 0x108900, DICT_END: 0x109900},
        {DICT_FILE: "monster_special_props", DICT_ADDR: 0x109900, DICT_END: 0x109c00},
        {DICT_FILE: "monster_stencil_small", DICT_ADDR: 0x100004, DICT_END: 0x10d334},
        {DICT_FILE: "monster_stencil_large", DICT_ADDR: 0x10d334, DICT_END: 0x10dbd4},
        {DICT_FILE: "misc_battle", DICT_ADDR: 0x10e003, DICT_END: 0x10e163},
        {DICT_FILE: "unknown_d0e220", DICT_ADDR: 0x10e220, DICT_END: 0x10e320},
        {DICT_FILE: "battle_bg_props", DICT_ADDR: 0x14ba21, DICT_END: 0x14bb31},
        {DICT_FILE: "sample_brr_33", DICT_ADDR: 0x14f000, DICT_END: 0x14fe7e},
        {DICT_FILE: "monster_graphics", DICT_ADDR: 0x150000, DICT_END: 0x183000},
        {DICT_FILE: "init_npc_switch", DICT_ADDR: 0x18e000, DICT_END: 0x18e080},
        {DICT_FILE: "sample_brr_2f", DICT_ADDR: 0x1bf800, DICT_END: 0x1bffa3}
    ]:
        inner_f = {
            DICT_FUNC: writeByte,
            DICT_END: d[DICT_END]
        }

        writeToFile(d[DICT_FILE], file_info, byAddrRange, inner_f, rommap, d[DICT_ADDR])

def texture(rommap):
    file_info = {
        "folder": "textures",
        "ext": ".1bpp"
    }

    for d in [
        {DICT_FILE: "map_overlay", DICT_ADDR: 0xdf00, DICT_DEPTH: 1, DICT_WIDTH: 128, DICT_HEIGHT: 10},
        {DICT_FILE: "big_fonts", DICT_ADDR: 0x3eb00, DICT_DEPTH: 1, DICT_WIDTH: 8, DICT_HEIGHT: 608}
    ]:
        d[DICT_BYTES] = d[DICT_WIDTH] * d[DICT_DEPTH] * d[DICT_HEIGHT]
        
        file_size = d[DICT_BYTES] + 14 + 8
        
        # BMP File Header
        header = b'BM'
        header += file_size.to_bytes(4, 'little')
        header += (54 + 8).to_bytes(8, 'big')

        # DIB Header
        header += (40).to_bytes(4, 'little')
        header += d[DICT_WIDTH].to_bytes(4, 'little')
        header += d[DICT_HEIGHT].to_bytes(4, 'little')
        header += b'\x01\x00'
        header += d[DICT_DEPTH].to_bytes(2, 'little')
        header += b'\x00\x00\x00\x00'
        header += b'\x00\x00\x00\x00'
        header += b'\x00\x00\x00\x00'
        header += b'\x00\x00\x00\x00'
        header += b'\x02\x00\x00\x00'
        header += b'\x00\x00\x00\x00'

        # Base Palette
        header += b'\x00\x00\x00\x00'
        header += b'\xff\xff\xff\x00'

        inner_f = {
            DICT_FUNC: writeByte,
            DICT_HEADER: header,
            DICT_BYTES: d[DICT_BYTES]
        }
        writeToFile(d[DICT_FILE], file_info, byBytes, inner_f, rommap, d[DICT_ADDR])

def palette(rommap):
    file_info = {
        "folder": "pal",
        "ext": ".pal"
    }

    for d in [
        {DICT_FILE: "window", DICT_ADDR: 0xd340, DICT_ITEMS: 1, DICT_BYTES: 0x40},
        {DICT_FILE: "map", DICT_ADDR: 0x3bb00, DICT_ITEMS: 256, DICT_BYTES: 44},
        {DICT_FILE: "monster", DICT_ADDR: 0xed000, DICT_ITEMS: 1, DICT_BYTES: 0x2270},
        {DICT_FILE: "world", DICT_ADDR: 0xffcc0, DICT_ITEMS: 256, DICT_BYTES: 3},
        {DICT_FILE: "attack", DICT_ADDR: 0x11a3a0, DICT_ITEMS: 16, DICT_BYTES: 128},
        {DICT_FILE: "battle_char", DICT_ADDR: 0x14a3c0, DICT_ITEMS: 32, DICT_BYTES: 110},
        {DICT_FILE: "battle_bg", DICT_ADDR: 0x14bb31, DICT_ITEMS: 32, DICT_BYTES: 84},
        {DICT_FILE: "attack_target", DICT_ADDR: 0x199655, DICT_ITEMS: 1, DICT_BYTES: 0x1f0},
        {DICT_FILE: "map_sprites", DICT_ADDR: 0x1ffc00, DICT_ITEMS: 32, DICT_BYTES: 32}
    ]:

        inner_f = {
            DICT_FUNC: writeByte,
            DICT_BYTES: d[DICT_BYTES]
        }
        
        if d[DICT_ITEMS] > 1:
            writeFilesTimesItems(d[DICT_ITEMS], d[DICT_FILE], file_info, byBytes, inner_f, rommap, d[DICT_ADDR])
        else:
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
        writeToFile(d[DICT_FILE], file_info, byItemsTimesBytes, inner_f, rommap, d[DICT_ADDR])

def textJp(rommap):
    import text_table_sfc as text_table

    textsPtrs = [
        {DICT_FILE: "menu_text", DICT_ADDR: 0xfa9d, DICT_PTR: 0xf987, DICT_PTR_BANK: 0, DICT_ITEMS: 139, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "dialogs", DICT_ADDR: 0xa0000, DICT_PTR: 0x82220, DICT_PTR_BANK: 0xa, DICT_ITEMS: 2176, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "map_titles", DICT_ADDR: 0x107200, DICT_PTR: 0x107000, DICT_PTR_BANK: 0x10, DICT_ITEMS: 163, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "battle_dialogs", DICT_ADDR: 0x10f1d4, DICT_PTR: 0x10f000, DICT_PTR_BANK: 0x10, DICT_ITEMS: 234, DICT_TEXT: text_table.text[1]},
        {DICT_FILE: "battle_messages", DICT_ADDR: 0x113ba9, DICT_PTR: 0x1139a9, DICT_PTR_BANK: 0x11, DICT_ITEMS: 256, DICT_TEXT: text_table.text[1]},
        {DICT_FILE: "item_descriptions", DICT_ADDR: 0x114100, DICT_PTR: 0x114000, DICT_PTR_BANK: 0x11, DICT_ITEMS: 256, DICT_TEXT: text_table.text[2]},
        {DICT_FILE: "job_descriptions", DICT_ADDR: 0x11724a, DICT_PTR: 0x117140, DICT_PTR_BANK: 0x11, DICT_ITEMS: 22, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "ability_descriptions", DICT_ADDR: 0x117337, DICT_PTR: 0x11716c, DICT_PTR_BANK: 0x11, DICT_ITEMS: 111, DICT_TEXT: text_table.text[0]},
    ]

    textsFixedBytes = [
        {DICT_FILE: "monster_names", DICT_ADDR: 0x105c00, DICT_ITEMS: 384, DICT_BYTES: 8, DICT_TEXT: text_table.text[0]},
        {DICT_FILE: "monster_specials", DICT_ADDR: 0x108700, DICT_ITEMS: 64, DICT_BYTES: 8, DICT_TEXT: text_table.text[1]},
        {DICT_FILE: "item_names", DICT_ADDR: 0x111380, DICT_ITEMS: 256, DICT_BYTES: 9, DICT_TEXT: text_table.text[2]},
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
    binaryData(rommap)
    texture(rommap)
    palette(rommap)
    textJp(rommap)