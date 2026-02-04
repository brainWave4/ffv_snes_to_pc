A ROM contains the data as well as the instruxtions of a game. Since FFV is a Hi-ROM, it is mapped at Bank C0-FF.

# Bank C0
This bank covers Field.

# Bank C1
This bank covers Battle Graphics. They are to be put into Btlgfx Module.

# Bank C2
This bank covers 2 sections: One for battling, and another for menus. They are to be put into respective modules.

## $0000 - $9FFF Battle
|From|To|Type|Content|
|---|---|---|---|
|$0148|$01B0|Text|Hidden Message|
|$04FB|$200A|Instr|Commands|
|$200B|$27BE|Instr|Timer|
|$27BF|$3E7E|Instr|AI|

## $A000 - $FFFF Menu

# Bank C3
This bank covers Cutscenes
|From|To|Type|Content|Module|
|---|---|---|---|---|
|C3/A300|C3/B949|Data|Menu Tilemap & Cursor Data|Menu|
|C3/B94A|C3/B95F||Unused Space||
|C3/B960|C3/E9FF|Data|Menu Palettes|Menu|
|C3/BA00|C3/BAFF||Unused Space||
|C3/BB00|C3/E6FF|Data|Map Palettes (44 items x 256 bytes)||
|C3/E700|C3/EAFF||Unused Space||
|C3/EB00|C3/FDFF|1bpp|Kana Graphics|Menu|
|C3/FE00|C3/FFFF||Unused Space||

# Banks C4 - C6
This range of bank covers Audio. They are to be put into Sound Module.
|From|To|Type|Content|
|---|---|---|---|
|C4/0000|C4/064C|Instr|Sound Code|
|C4/064D|C4/1E3E|SPC|SPC Engine|
|C4/1E3F|C4/1F4E|Data|Sound Effect BRR Data|
|C4/1F4F|C4/1F70|Data|Sound Effect BRR Pointers|
|C4/1F71|C4/1F82|Data|Sound Effect ADSR Values|
|C4/1F83|C4/1F94|Data|Sound Effect Pitch Multipliers|
|C4/1F95|C4/3B96|Data|Sound Effect Scripts|
|C4/3B97|C4/3C6E|Data|Pointers to BGM Data|
|C4/3C6F|C4/3CD7|Data|Pointers to Instrument BRRs|
|C4/3CD8|C5/3D1D||Instrument Loop Values (35 items x 2 bytes)|
|C4/3D1E|C5/3D63||Instrument Pitch Multipliers (35 items x 2 bytes)|
|C4/3D64|C5/3DA9||Instrument ADSRs (35 items x 2 bytes)|
|C4/3DAA|C5/46A9||Instruments used in BGMs (72 items x 35 bytes)|
|C4/46AA|C5/E5E7||Instrument BRRs (35 items, varying size)|
|C5/E5E8|C6/FE75||BGMs (72 items, varying size)|
|C6/FE76|C6/FFFF||Unused Space|

# Banks C7 - DF
This range covers the rest of the data. Which module they are to be put into varies.

|From|To|Type|Content|Module|
|---|---|---|---|---|
|CA/0000|CA/FFFF|Text|Dialogs (2176 items, variable size)|Field|