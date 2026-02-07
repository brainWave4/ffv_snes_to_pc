def readFromBank(rommap, file):
    for h in range(0x100):
        for l in range(0x100):
            rommap.append(file.read(1))
        
def mismatchedHeaderTitle(title, rommap, addr):
    for i in range(len(title)):
        if rommap[addr + i] != title[i]:
            return True

    return False

def getRomMap(ext, filepath, header, title):
    print(f"Opening {ext} file...")

    rommap = []

    with open(filepath, 'rb') as file:
        readFromBank(rommap, file)

        if mismatchedHeaderTitle(header, rommap, 0xffc0):
            print(f"This is not a {title} Game.")
            return

        for b in range(1, 0x28):
            readFromBank(rommap, file)
    
    return rommap