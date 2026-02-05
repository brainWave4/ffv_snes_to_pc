# FFV SNES to PC (WIP)

This is a reverse engineer of Final Fantasy V, porting from SNES/Super Famicon to PC. It'll be as definite as you want it to be.

## Dependencies

* [Python 3](https://www.python.org/) for extracting assets.
* You also need to be able to compile C Projects.

## Compiling the Game

### Extracting Assets

For copyright reasons, not everything is implemented on this project. To get the rest of the content, they are to be extracted from the base ROM.

To extract the assets, open Command Prompt or Terminal on the project folder and type:
```
python3 '...\extract_assets.py' '...\ffv.sfc'
```
where, for the following arguements:
* `'...\extract_assets.py'` (in the `rom_tools` folder) is the full filepath, in quotations.
* `'...\ffv.sfc'` is the full filepath to the FFV ROM. This arguement is optional; if left out, the program will search for a FFV ROM in `base_rom` folder.

### Compilation

## Acknowledgements

* [everything8215's Dissembly](https://github.com/everything8215/ff5) as a reference.
