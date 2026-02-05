import pathlib
import sys

EXT_SFC = ".sfc"

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

def checkSfc(filepath):
    print("Opening '.sfc' file...")

    rommap = [[]]

    with open(filepath, 'rb') as file:
        readToAddr(file, rommap[0])

        HEADER_TITLE = [
            b'F', b'I', b'N', b'A', b'L', b' ', b'F',
            b'A', b'N', b'T', b'A', b'S', b'Y', b' ',
            b'5', b' ', b' ', b' ', b' ', b' ', b' '
        ]
        if mismatchedHeaderTitle(HEADER_TITLE, rommap, 0xc0):
            print("This is not a FFV Game.")
            return

        for b in range(1, 0x28):
            b_arr = []
            readToAddr(file, b_arr)
            rommap.append(b_arr)

if len(sys.argv) < 2:
    directory_path = pathlib.Path("base_rom")
    files_sorted = sorted((p for p in directory_path.iterdir() if p.is_file() and p.suffix == EXT_SFC), key=lambda p: p.name)
    
    if files_sorted:
        checkSfc(files_sorted[0])
    else:
        print("No '.sfc' file in the 'base_rom' folder.")
else:
    filepath = pathlib.Path(sys.argv[1])

    if not filepath.isFile() and filepath.suffix == EXT_SFC:
        checkSfc(filepath)
    else:
        print("Error: Arguement 1 should be a filepath that ends with '.sfc'")