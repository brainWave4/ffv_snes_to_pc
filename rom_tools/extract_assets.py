import pathlib
import sys

filepath = ""
EXT_SFC = ".sfc"

if len(sys.argv) < 2:
    directory_path = pathlib.Path("base_rom")
    files_sorted = sorted((p for p in directory_path.iterdir() if p.is_file() and p.suffix == EXT_SFC), key=lambda p: p.name)
    
    if files_sorted:
        filepath = files_sorted[0]
        checkSfc()
    else:
        print("No '.sfc' file in the 'base_rom' folder.")
else:
    filepath = pathlib.Path(sys.argv[1])

    if not filepath.isFile() and filepath.suffix == EXT_SFC:
        checkSfc()
    else:
        print("Error: Arguement 1 should be a filepath that ends with '.sfc'")

def checkSfc():
    print("There is a '.sfc' file.")