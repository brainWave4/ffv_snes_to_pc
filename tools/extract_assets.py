import pathlib
import sys

import rom

EXT_SFC = ".sfc"

HEADER_TITLE = [
    b'F', b'I', b'N', b'A', b'L', b' ', b'F',
    b'A', b'N', b'T', b'A', b'S', b'Y', b' ',
    b'5', b' ', b' ', b' ', b' ', b' ', b' '
]
title = "FFV"

rommap = False

if len(sys.argv) < 2:
    directory_path = pathlib.Path("base_rom")
    files_sorted = sorted((p for p in directory_path.iterdir() if p.is_file() and p.suffix == EXT_SFC), key=lambda p: p.name)
    
    if files_sorted:
        rommap = rom.getRomMap(EXT_SFC, files_sorted[0], HEADER_TITLE, title)
    else:
        print(f"No {EXT_SFC} file in the 'base_rom' folder.")
else:
    filepath = pathlib.Path(sys.argv[1])

    if not filepath.isFile() and filepath.suffix == EXT_SFC:
        rommap = rom.getRomMap(EXT_SFC, filepath, HEADER_TITLE, title)
    else:
        print(f"Error: Arguement 1 should be a filepath that ends with {EXT_SFC}")

if rommap:
    import write
    write.everything(rommap)