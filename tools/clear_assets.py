import os

EXTS = ['.1bpp', '.2bpp', '.3bpp', '.4bpp', '.8bpp', '.bin', '.pal', '.txt']

def clear_in_file(path):
    for entry in os.listdir(path):
        fullpath = os.path.join(path, entry)

        if os.path.isdir(fullpath):
            clear_in_file(fullpath)
        else:
            ext = os.path.splitext(fullpath)[1]
            if ext in EXTS:
                os.remove(fullpath)
                print("Cleared " + fullpath)

clear_in_file("assets")