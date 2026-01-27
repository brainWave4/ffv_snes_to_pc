# ROM

A ROM contains the data as well as the instruxtions of a game. Since FFV is a Hi-ROM, it is mapped at Bank C0-FF.

|From|To|Type|Section|Module|
|---|---|---|---|---|
|C0/0000|C0/FFFF|Instr|Field|Field|
|C1/0000|C1/FFFF|Instr|Battle Graphics|Btlgfx|
|C2/0000|C2/9FFF|Instr|Battle|Battle|
|C2/A000|C2/FFFF|Instr|Menu|Menu|
|C3/0000|C3/FFFF|Instr|Cutscene|Cutscene|
|C4/0000|C4/FFFF|Instr|Sound|Sound|

# RAM

A RAM is where the game stores variable for future use. It is mapped at Bank 7E-7F.

## Battle
## Menu
## Character Stats
For Character 1:
|From|To|Type|Section|
|---|---|---|---|
|7E/0500||Bitwise|ID, Gender, In party, Row|
|7E/0501||ID|Job|
|7E/0502||Integer|Level|
|7E/0503|7E/0505|Integer|Exp|
|7E/0506|7E/0507|Integer|Current HP|
|7E/0508|7E/0509|Integer|Max HP|
|7E/050A|7E/050B|Integer|Current MP|
|7E/050C|7E/050D|Integer|Max MP|
|7E/050E||ID|Head Equipment|
|7E/050F||ID|Body Equipment|
|7E/0510||ID|Accessory Equipment|
|7E/0511||ID|Shield (right hand)|
|7E/0512||ID|Shield (left hand)|
|7E/0513||ID|Weapon (right hand)|
|7E/0514||ID|Weapon (left hand)|
|7E/0515||ID|Monster Caught|
|7E/0516||ID|Command 1|
|7E/0517||ID|Command 2|
|7E/0518||ID|Command 3|
|7E/0519||ID|Command 4|
|7E/051A||Bitwise|Status 1|
|7E/051B||Bitwise|Status 2|
|7E/051C||Bitwise|Status 3|
|7E/051D||Bitwise|Status 4|

For the rest:
|From|To|Type|Section|
|---|---|---|---|
|7E/0550|7E/059F|Set|Character 2 Stats|
|7E/05A0|7E/05EF|Set|Character 3 Stats|
|7E/05F0|7E/063F|Set|Character 4 Stats|

They are structured the same as Character 1.

## Items
|From|To|Type|Section|
|---|---|---|---|
|7E/0640|7E/073F|IDs|Up to 256 kinds of Items|
|7E/0740|7E/038F|Integers|Number of said Items|

## Jobs and other Progression

# SRAM

A small section designed for storing data. They are preserved even when the power turns off. They are mapped Bank 30-3F by 6000-7FFF, but for simplicity sake, they will be referred by $0000 onwards.

## Saves
Here is how the first save slot is structured:
|From|To|Type|Section|
|---|---|---|---|
|$0000|$004F|Set|Character Slot 1|
|$0050|$009F|Set|Character Slot 2|
|$00A0|$00EF|Set|Character Slot 3|
|$00F0|$013F|Set|Character Slot 4|
|$0140|$023F|IDs|Current Items|
|$0240|$033F|Integers|Number of said Items|
|$0447|$0449|Integer|Gil|
|$05D8||Integer|Map X Position|
|$05D9||Integer|Map Y Position|

For the remaining save slots:
|From|To|Type|Section|
|---|---|---|---|
|$0700|$0D00|Set|Save Slot 2|
|$0E00|$1400|Set|Save Slot 3|
|$1500|$1B00|Set|Save Slot 4|

They are structured the same as Save Slot 1.

### Character Slots
For the first character:
|From|To|Type|Section|
|---|---|---|---|
|$00||Bitwise|ID, Gender, In party, Row|
|$01||ID|Job|
|$02||Integer|Level|
|$03|$05|Integer|Exp|
|$06|$07|Integer|Current HP|
|$08|$09|Integer|Max HP|
|$0A|$0B|Integer|Current MP|
|$0C|$0D|Integer|Max MP|
|$0E||ID|Head Equipment|
|$0F||ID|Body Equipment|
|$10||ID|Accessory Equipment|
|$11||ID|Shield (right hand)|
|$12||ID|Shield (left hand)|
|$13||ID|Weapon (right hand)|
|$14||ID|Weapon (left hand)|
|$15||ID|Monster Caught|
|$16||ID|Command 1|
|$17||ID|Command 2|
|$18||ID|Command 3|
|$19||ID|Command 4|
|$1A|$1D|Bitwise|Status|
|$24||Integer|Strength|
|$25||Integer|Agility|
|$26||Integer|Vitality|
|$27||Integer|Magic Power|
|$3A||Integer|Job Level|
|$3B|$3C|Integer|Ability Points|

The remaining characters share the same structure.

## Checksum
$1C00 is empty until $1FF0, which is a checksum to check for the save files' legitimacy.
