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
python3 'tools/extract_assets.py' '.../ffv.sfc'
```
Where `'.../ffv.sfc'` is the full filepath to the FFV ROM. This arguement is optional; if left out, the program will search for a FFV ROM in `base_rom` folder.

### Compilation

## Other Usage
For those who are porting SNES games to the PC, you may want to check out the following:
* Module `display`, which is the equivilent to the PPU compoment.

## License
This project is licensed under the [MIT License](https://github.com/brainWave4/ffv_snes_to_pc#MIT-1-ov-file).

## Acknowledgements

* [everything8215's Dissembly](https://github.com/everything8215/ff5) as a reference.
