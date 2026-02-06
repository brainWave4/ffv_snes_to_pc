def readToAddr(file, b_arr):
    for h in range(0x100):
        h_arr = [];
        
        for l in range(0x100):
            h_arr.append(file.read(1))
        
        b_arr.append(h_arr)
        
def mismatchedHeaderTitle(title, rommap, starting_l):
    for i in range(len(title)):
        if rommap[0][0xff][starting_l + i] != title[i]:
            return True

    return False

def getRomMap(ext, filepath, header, title):
    print(f"Opening {ext} file...")

    rommap = [[]]

    with open(filepath, 'rb') as file:
        readToAddr(file, rommap[0])

        if mismatchedHeaderTitle(header, rommap, 0xc0):
            print(f"This is not a {title} Game.")
            return

        for b in range(1, 0x28):
            b_arr = []
            readToAddr(file, b_arr)
            rommap.append(b_arr)
    
    return rommap