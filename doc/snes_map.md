# ROM

A ROM contains the data as well as the instruxtions of a game. Since FFV is a Hi-ROM, it is mapped at Bank C0-FF.

|From|To|Type|Section|Module|
|---|---|---|---|---|
|C0/0000|C0/FFFF|Instr|Field|Field|
|C1/0000|C1/FFFF|Instr|Battle Graphics|Btlgfx|
|C2/0000|C2/9FFF|Instr|Battle (General)|Battle|
|C2/0148|C2/01B0|Text|Hidden Message||
|C2/04FB|C2/200A|Instr|Commands|Battle|
|C2/200B|C2/27BE|Instr|Timer|Battle|
|C2/27BF|C2/3E7E|Instr|AI|Battle|
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
|7E/051E||Bitwise|Action (Defend, Guard etc) Flags|
|7E/051F||Bitwise|Damage Modifier|
|7E/0520|7E/0521|Bitwise|Innate Abilities|
|7E/0522||Bitwise|Elemental Boosts|
|7E/0523||Integer|Equipment Weight|
|7E/0524||Integer|Base Strength|
|7E/0525||Integer|Base Agility|
|7E/0526||Integer|Base Stamina|
|7E/0527||Integer|Base Magic|
|7E/0528||Integer|Current Strength|
|7E/0529||Integer|Current Agility|
|7E/052A||Integer|Current Stamina|
|7E/052B||Integer|Current Magic|
|7E/052C||Integer|Evade Chance|
|7E/052D||Integer|Defense|
|7E/052E||Integer|Magic Evade Chance|
|7E/052F||Integer|Magic Defense|
|7E/0530||Bitwise|Elemental Absorb|
|7E/0531||Bitwise|Elemental Evasion|
|7E/0532||Bitwise|Elemental Immunity|
|7E/0533||Bitwise|Elemental Resistance|
|7E/0534||Bitwise|Elemental Weakness|
|7E/0535||Bitwise|Status Resistance 1|
|7E/0536||Bitwise|Status Resistance 2|
|7E/0537||Bitwise|Status Resistance 3|
|7E/0538||Bitwise|Weapon Properties|
|7E/0539||Bitwise|Equipment Properties|
|7E/053A||Integer|Job Level|
|7E/053B|7E/053C|Integer|ABP|
|7E/053D|7E/053F|Bitwise|Magic used|
|7E/0540|7E/0543|Bitwise|Equipment Category|
|7E/0544|7E/0545|Integer|Attack|
|7E/0546||Bitwise|Attack ID Reaction|
|7E/054A||Integer|Freelancer Strength|
|7E/054B||Integer|Freelancer Agility|
|7E/054C||Integer|Freelancer Stamina|
|7E/054D||Integer|Freelancer Magic|
|7E/054E|7E/054F|Bitwise|Freelancer Innate Abilities|

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

It looks structured the same as RAM > Character Stats - Jobs and other Progression.

As for the remaining save slots:
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
|$0E|$14|IDs|Equipments|
|$15||ID|Monster Caught|
|$16|$19||IDs|Commands|
|$1A|$1D|Bitwises|Status|
|$1E||Bitwise|Action (Defend, Guard etc) Flags|
|7$1F||Bitwise|Damage Modifier|
|$20|$21|Bitwise|Innate Abilities|
|$22||Bitwise|Elemental Boosts|
|$23||Integer|Equipment Weight|
|$24|$27||Integers|Base Parameters (of Strength, Agility, Stamina and Magic)|
|$28|$2B||Integers|Current Parameters|
|$2C|$2F||Integers|Evasion and Defence, by Physical and Magical|
|$30|$34|Bitwises|Elemental Properties|
|$35|$37|Bitwises|Status Resistances|
|$38|$39|Bitwises|Weapon and Equipment Properties|
|$3A||Integer|Job Level|
|$3B|$3C|Integer|ABP|

The remaining characters share the same structure.

## Checksum
$1C00 is empty until $1FF0, which is a checksum to check for the save files' legitimacy.
