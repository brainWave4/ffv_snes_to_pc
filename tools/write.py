import pathlib

FILE_CAR = "src/assets"
FILE_TXT = "txt"
FILE_JP = "jp"

EXT_TXT = ".txt"

DICT_FILE = "file"
DICT_ADDR = "addr"
DICT_PTR = "ptr_addr"
DICT_FUNC = "def"
DICT_ITEMS = "items"
DICT_BYTES = "bytes"

dict_char = {}

def writeText(rommap, addr_i, file):
    char_index = int.from_bytes(rommap[addr_i])

    if char_index in dict_char:
        char = dict_char[char_index]
        file.write(char)
    else:
        print(f"Missing char: index {char_index}")

def byPointers(file, inner_f, rommap, addr):
    checkpoints = []

    for i in range(inner_f[DICT_ITEMS]):
        addr_ptr_a = inner_f[DICT_PTR] + i * 2
        addr_ptr_b = addr_ptr_a + 1

        target_addr = int.from_bytes(rommap[addr_ptr_b])
        target_addr *= 0x100
        target_addr += int.from_bytes(rommap[addr_ptr_a])
        
        checkpoints.append(target_addr)
    
    print(checkpoints)

    for c in checkpoints:
        while addr < c:
            inner_f[DICT_FUNC](rommap, addr, file)
            addr += 1
        file.write("\n")

def byFixedBytes(file, inner_f, rommap, addr):
    byte_count = inner_f[DICT_BYTES]

    for i in range(inner_f[DICT_ITEMS]):
        for j in range(byte_count):
            addr_i = addr + i * byte_count + j
            inner_f[DICT_FUNC](rommap, addr_i, file)
        
        file.write("\n")

def writeToFile(lang, filename, byLoop, inner_f, rommap, addr):
    ext = {writeText: EXT_TXT}[inner_f[DICT_FUNC]]
    fullpath = pathlib.Path(FILE_CAR) / FILE_TXT / lang / (filename + ext)
    
    with open (fullpath, 'w') as file:
        byLoop(file, inner_f, rommap, addr)

    print(f"Written down {fullpath}")

def text(rommap, lang, textsPtrs, textsFixedBytes):
    for d in textsPtrs:
        inner_f = {
            DICT_FUNC: writeText,
            DICT_PTR: d[DICT_PTR],
            DICT_ITEMS: d[DICT_ITEMS]
        }
        writeToFile(lang, d[DICT_FILE], byPointers, inner_f, rommap, d[DICT_ADDR])
    
    for d in textsFixedBytes:
        inner_f = {
            DICT_FUNC: writeText,
            DICT_ITEMS: d[DICT_ITEMS],
            DICT_BYTES: d[DICT_BYTES]
        }
        writeToFile(lang, d[DICT_FILE], byFixedBytes, inner_f, rommap, d[DICT_ADDR])

def textJp(rommap):
    kana = "バばビびブぶベべボぼガがギぎグぐゲげゴごザざジじズずゼぜゾぞダだヂぢヅづデでドどヴパぱピぴプぷペぺポぽ０１２３４５６７８９ｍｈｐハはヒひフふヘへホほカかキきクくケけコこサさシしスすセせソそタたチちツつテてトとウうアあイいエえオおナなニにヌぬネねノのマまミみムむメめモもラらリりルるレれロろヤやユゆヨよワわンんヲをッっャゃュゅョょァーィ…ゥ！ェ？ォ％／：「」。ＡＢＸＹＬＲＥＨＭＰＳＣＴ←→＋"
    for i in range(len(kana)):
        dict_char[0x20 + i] = kana[i]
    
    icons = ["[sw]", "[wh]", "[bk]", "[tm]", "[dg]", "[sp]", "[ax]", "[kt]", "[rd]", "[sf]", "[bw]", "[hp]", "[wp]", "[bl]", "[sh]", "[hm]", "[ar]", "[rl]", "Ｕ"]
    for i in range(len(icons)):
        dict_char[0xE3 + i] = icons[i]

    dict_char[0xFE] = "　"
    dict_char[0xFF] = ""

    textsPtrs = [
        {DICT_FILE: "menu_text", DICT_ADDR: 0xfa9d, DICT_PTR: 0xf987, DICT_ITEMS: 139}
    ]

    textsFixedBytes = [
        {DICT_FILE: "monster_names", DICT_ADDR: 0x105c00, DICT_ITEMS: 384, DICT_BYTES: 8},
        {DICT_FILE: "monster_specials", DICT_ADDR: 0x108700, DICT_ITEMS: 64, DICT_BYTES: 8},
        {DICT_FILE: "item_names", DICT_ADDR: 0x111380, DICT_ITEMS: 256, DICT_BYTES: 9},
        {DICT_FILE: "magic_names", DICT_ADDR: 0x111c80, DICT_ITEMS: 72, DICT_BYTES: 6},
        {DICT_FILE: "summon_attacks", DICT_ADDR: 0x111e30, DICT_ITEMS: 15, DICT_BYTES: 6},
        {DICT_FILE: "attack_names", DICT_ADDR: 0x111e8a, DICT_ITEMS: 161, DICT_BYTES: 9},
        {DICT_FILE: "status_names", DICT_ADDR: 0x1128b6, DICT_ITEMS: 24, DICT_BYTES: 8},
        {DICT_FILE: "shop_types", DICT_ADDR: 0x112d00, DICT_ITEMS: 8, DICT_BYTES: 8},
        {DICT_FILE: "char_names", DICT_ADDR: 0x115500, DICT_ITEMS: 5, DICT_BYTES: 6},
        {DICT_FILE: "job_names", DICT_ADDR: 0x115600, DICT_ITEMS: 22, DICT_BYTES: 8},
        {DICT_FILE: "battle_commands", DICT_ADDR: 0x115800, DICT_ITEMS: 96, DICT_BYTES: 5},
        {DICT_FILE: "passive_abilities", DICT_ADDR: 0x116200, DICT_ITEMS: 33, DICT_BYTES: 8},
        {DICT_FILE: "special_abilities", DICT_ADDR: 0x115600, DICT_ITEMS: 105, DICT_BYTES: 9}
    ]

    text(rommap, FILE_JP, textsPtrs, textsFixedBytes)

def everything(rommap):
    textJp(rommap)