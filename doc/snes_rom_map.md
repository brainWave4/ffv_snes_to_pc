A ROM contains the data as well as the instruxtions of a game. Since FFV is a Hi-ROM, it is mapped at Bank C0-FF. However, if opened by a hex editor, the bank is offset at $00 instead.

# Bank C0
This bank covers Field.
|From|To|Type|Content|
|---|---|---|---|
|$9D9B|$A18A|Data|Map Animation Properties|
|$CF00|$D23F|Data|Unknown|
|$D240|$D33F|Data|Unknown|
|$D340|$D37F|Palette|Window|
|$D380|$D97F|4bpp|Window|
|$D980|$D9B7|Pointers|Overlay Properties|
|$D9B8|$DEFB|Data|Overlay Properties|
|$DF00|$E4FF|1bpp|Map Overlay|
|$F987|$FA9C|Pointers|Menu Texts (139 items)|
|$FA9D|$FE89|Text|Menu Texts|
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
|C3/0200|C3/7E4C|Data|Unknown||
|C3/7E4D|C3/A06E|Data|Cutscene Code||
|C3/A300|C3/B949|Data|Menu Tilemap & Cursor Data|Menu|
|C3/B94A|C3/B95F||Unused Space||
|C3/B960|C3/E9FF|Data|Menu Palettes|Menu|
|C3/BA00|C3/BAFF||Unused Space||
|C3/BB00|C3/E6FF|Data|Map Palettes (44 items x 256 bytes)||
|C3/E700|C3/EAFF||Unused Space||
|C3/EB00|C3/FDFF|1bpp|Big Fonts|Menu|
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
|C8/2220|C8/32FF|Pointers|Dialogs (2176 items)||
|CA/0000|CA/FFF4|Text|Dialogs|Field|
|CB/0290|CD/F9FE|Data|Sub Tilemaps||
|CD/FA40|CD/FBA7|Data|Map Palette Animation||
|CD/FE00|CD/FFFF|4bpp|Timer Font||
|CE/9C00|CE/CFFF|Data|Map Propertiess (26 items)||
|CE/D000|CE/F26F|Palette|Monsters||
|CF/D800|CF/DFFF|4bpp|Minimap||
|CF/EA00|CF/F0BF|Data|World Tile Propertiess (3*576)||
|CF/F0C0|CF/F9BF|Data|World Tileset (3*768)||
|CF/F9C0|CF/FCBF|Data|World Tile Attributes (3*256)||
|CF/FCC0|CF/FFBF|Palette|World (3*256)||
|D0/0000|D0/2FFF|Data|Monster Properties||
|D0/3000|D0/4FFF|Data|Battle Properties||
|D0/5000|D0/55FF|Data|Monster Item||
|D0/5600|D0/5BFF|Data|Monster Control||
|D0/5C00|D0/67FF|Text|Monster Names (384 items x 8 bytes)||
|D0/6800|D0/6FFF|Data|Random Battle Group||
|D0/7000|D0/7147|Pointers|Map Titles (163 items)||
|D0/7200|D0/7667|Text|Map Titles||
|D0/7800|D0/79FF|Data|Event Battle Group||
|D0/7A00|D0/7FFF|Data|World Battle Group||
|D0/8000|D0/83FF|Data|Sub Battle Group||
|D0/8400|D0/84BF|Data|World Battle Rate||
|D0/84C0|D0/853F|Data|Sub Battle Rate||
|D0/8600|D0/86FF|Data|Monster Release||
|D0/8700|D0/88FF|Text|Monster Special Attack Names (64 items x 8 bytes)||
|D0/8900|D0/98FF|Data|Monster Positions||
|D0/9900|D0/9BFF|Data|Monster Special Properties||
|D0/C800|D0/CFD8|Data|Song Script 41||
|D0/D004|D0/D333|Data|Monster Stencil Small||
|D0/D334|D0/DBD3|Data|Monster Stencil Large||
|D0/E003|D0/E162|Data|Misc Battle||
|D0/E220|D0/E31F|Data|Unknown||
|D0/E4CB|D0/EBE4|4bpp|"The End"||
|D0/F000|D0/F1D3|Pointers|Battle Dialogs (234 items)||
|D0/F1D4|D0/FEBB|Text|Battle Dialogs||
|D0/FEBC|D0/FFE0||Unused Space||
|D1/0000|D1/05FF|Data|Weapon Properties||
|D1/0600|D1/0A7F|Data|Armor Properties||
|D1/0A80|D1/0B7F|Data|Item Properties||
|D1/0B80|D1/137F|Data|Attack Properties||
|D1/1380|D1/1C7F|Text|Item Names (256 items x 9 bytes)||
|D1/1C80|D1/1E89|Text|Magic Names (87 items x 6 bytes)||
|D1/1E8A|D1/247A|Text|Attack Names (161 items x 9 bytes)||
|D1/247B|D1/247F||Unused Space||
|D1/2480|D1/257F|Data|Eqipment Types||
|D1/2580|D1/26BF|Data|Armor Element||
|D1/26C0|D1/287F|Data|Armor Status||
|D1/28B6|D1/2975|Text|Status Names (24 items x 8 bytes)||
|D1/2D00|D1/2D3F|Text|Shop Type Names (8 items x 8 bytes)||
|D1/3000|D1/320F|Data|Map Tresures||
|D1/3210|D1/35FF|Data|Treasure Properties||
|D1/39A9|D1/3BA8|Pointers|Battle Messages (256 items)||
|D1/3BA9|D1/3F0D|Text|Battle Messages||
|D1/3F0E|D1/3FFF||Unused Space||
|D1/4000|D1/41FF|Pointers|Item Descriptions (256 items)||
|D1/4100|D1/43FD|Text|Item Descriptions||
|D1/43FE|D1/4FFF||Unused Space||
|D1/52B5|D1/52BF||Unused Space||
|D1/542C|D1/54FF||Unused Space||
|D1/5500|D1/551D|Text|Character Names (5 items x 6 bytes)||
|D1/5532|D1/55FF||Unused Space||
|D1/5600|D1/56AF|Text|Job Names (22 items x 8 bytes)||
|D1/57E4|D1/57FF||Unused Space||
|D1/5800|D1/59DF|Text|Battle Command Names (96 items x 5 bytes)
|D1/5F80|D1/61FF||Unused Space||||
|D1/6200|D1/6307|Text|Passive Ability Names (33 items x 8 bytes)||
|D1/6452|D1/66FF||Unused Space||
|D1/6700|D1/6AB0|Text|Special Ability Names (105 items x 9 bytes)||
|D1/6F89|D1/6FFF||Unused Space||
|D1/7000|D1/713F|Data|Char Prop||
|D1/7140|D1/716B|Pointers|Job Descriptions (22 items)||
|D1/724A|D1/7336|Text|Job Descriptions||
|D1/716C|D1/7249|Pointers|Ability Descriptions (111 items)||
|D1/7337|D1/77B9|Text|Ability Descriptions||
|D1/77BA|D1/7F9F|Scr|Unused Space||
|D1/7F00|D1/979F|Scr|Graphic Attacks||
|D1/97A0|D1/9B9F|Scr|Weapons||
|D1/9BA0|D1/A39F|Scr|Weapon Hit||
|D1/A3A0|D1/AB9F|Palette|Attacks (32 items)||
|D1/ABA0|D1/BDFF|4bpp|Animals||
|D1/BE00|D1/BFFF|Scr|Animals||
|D1/C000|D1/D7FF|3bpp|Weapons||
|D1/D800|D1/EFFF|3bpp|Weapon Hit||
|D1/F000|D1/FFFF|2bpp|Small Fonts||
|D2/0000|D4/93FF|4bpp|Battle Characters (1536 items)||
|D4/9400|D4/97BF|4bpp|Dead Characters (192 items)||
|D4/97C0|D4/A3BF|3bpp|Battle Sprites||
|D4/A3C0|D4/B17F|Palette|Battle Characters (32 items)||
|D4/BA21|D4/BB30|Data|Battle Backgrounds Properties||
|D4/BB31|D4/C5B0|Palettes|Battle Backgrounds (32 items)||
|D4/C736|D4/C747|Pointers|Battle Background Flip||
|D4/C748|D4/C86C|Data|Battle Background Flip||
|D4/C86D|D4/C8A4|Pointers|Battle Background Tiles||
|D4/C8A5|D4/EFF0|Scr|Battle Background Tiles||
|D4/F000|D4/FE7D|Data|Sample BRR 33||
|D5/0000|D8/2FFF|Data|Monster Graphics||
|D8/41D5|D8/DE35|4bpp|Battle Backgrounds||
|D8/E000|D8/E07F|Data|Init NPC Switch||
|D9/0000|D9/7C4F|3bpp|Attacks||
|D9/9655|D9/9854|Palette|Attack Target||
|DA/0000|DB/39FF|4bpp|Map||
|DB/3A00|DB/4D7F|3bpp|Vehicle||
|DB/4D80|DB/7FFF|4bpp|World||
|DB/8000|DB/CFFF|4bpp|World Graphics||
|DB/D000|DB/F7FF|1bpp|Kanji||
|DB/F800|DB/FFA2|Data|Sample BRR 2F||
|DC/0000|DC/0021|Pointers|Map Bg3 Gfx||
|DC/0024|DC/2D83|2bpp|Map Bg3 Gfx||
|DC/2D84|DC/2E1F|Pointers|Map Gfx||
|DC/2E24|DF/99E3|4bpp|Map Gfx||
|DF/9B00|DF/FBFF|4bpp|Map Animations||
|DF/FC00|DF/FFFF|Palette|Map Sprites||
