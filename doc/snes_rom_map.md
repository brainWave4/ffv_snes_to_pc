A ROM contains the data as well as the instruxtions of a game. Since FFV is a Hi-ROM, it is mapped at Bank C0-FF. However, if opened by a hex editor, the bank is offset at $00 instead.

# Bank C0
This bank covers Field.
|From|To|Type|Content|
|---|---|---|---|
|$F987|$FA9C|Pointers|Menu Texts|
|$FA9D|$FE89|Text|Menu Texts (11 items, variable size)|
|$FEBB|$FEBF||Unused Space|
|$FEC0|$FFC0|Data|RNG Table ($FF bytes of items)|

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
|C8/2220|C8/32FF|Pointers|Dialogs||
|CA/0000|CA/FFF4|Text|Dialogs (2176 items, variable size)|Field|
|D0/5C00|D0/67FF|Text|Monster Names (384 items x 8 bytes)||
|D0/7000|D0/7147|Pointers|Map Titles||
|D0/7200|D0/7667|Text|Map Titles (163 items, variable size)||
|D0/8700|D0/88FF|Text|Monster Special Attack Names (64 items x 8 bytes)||
|D0/F000|D0/F1D3|Pointers|Battle Dialogs||
|D0/F1D4|D0/FEBB|Text|Battle Dialogs(234 items, variable size)||
|D0/FEBC|D0/FFE0||Unused Space||
|D1/1380|D1/1C7F|Text|Item Names (256 items x 9 bytes)||
|D1/1C80|D1/1E2F|Text|Magic Names (72 items x 6 bytes)||
|D1/1E30|D1/1E89|Text|Summon Attacks (15 items x 6 bytes)||
|D1/1E8A|D1/247A|Text|Attack Names (161 items x 9 bytes)||
|D1/247B|D1/2480||Unused Space||
|D1/28B6|D1/2975|Text|Status Names (24 items x 8 bytes)||
|D1/2D00|D1/2D3F|Text|Shop Type Names (8 items x 8 bytes)||
|D1/39A9|D1/3BA8|Pointers|Battle Messages||
|D1/3BA9|D1/3F0D|Text|Battle Messages (256 items, variable size)||
|D1/3F0E|D1/3FFF||Unused Space||
|D1/4000|D1/41FF|Pointers|Item Descriptions||
|D1/4100|D1/43FD|Text|Item Descriptions(256 items, var. size)||
|D1/43FE|D1/4FFF||Unused Space||
|D1/52B5|D1/52BF||Unused Space||
|D1/542C|D1/54FF||Unused Space||
|D1/5500|D1/551D|Text|Character Names (5 items x 6 bytes)||
|D1/5532|D1/55FF||Unused Space||
|D1/5600|D1/56AF|Text|Job Names (22 items x 8 bytes)||
|D1/57E4|D1/57FF||Unused Space||
|D1/5800|D1/59DF|Text|Battle Command Names (96 items x 5 bytes)
|D1/5F80|D1/61FF||Unused Space||||
|D1/6200|D1/6307|Text|Passive Ability Names (33 items x 8)||
|D1/6452|D1/66FF||Unused Space||
|D1/6700|D1/6AB0|Text|Special Ability Names (105 items x 9 bytes)||
|D1/6F89|D1/6FFF||Unused Space||
|D1/7140|D1/716B|Pointers|Job Descriptions||
|D1/724A|D1/7336|Text|Job Descriptions (22 items, variable size)||
|D1/7337|D1/77B9|Pointers|Ability Descriptions||
|D1/7337|D1/77B9|Text|Ability Descriptions (111 items, variable size)||
|D1/77BA|D1/7F9F||Unused Space||
