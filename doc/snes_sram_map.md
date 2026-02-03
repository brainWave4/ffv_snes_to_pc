A small section designed for storing data. They are preserved even when the power turns off. They are mapped Bank 30-3F by 6000-7FFF, but for simplicity sake, they will be referred by $0000 onwards.

# Saves
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

It looks structured the same as RAM > Character Stats - Field.

As for the remaining save slots:
|From|To|Type|Section|
|---|---|---|---|
|$0700|$0D00|Set|Save Slot 2|
|$0E00|$1400|Set|Save Slot 3|
|$1500|$1B00|Set|Save Slot 4|

They are structured the same as Save Slot 1.

## Character Slots
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
|$16|$19|IDs|Commands|
|$1A|$1D|Bitwises|Status|
|$1E||Bitwise|Action (Defend, Guard etc) Flags|
|7$1F||Bitwise|Damage Modifier|
|$20|$21|Bitwise|Innate Abilities|
|$22||Bitwise|Elemental Boosts|
|$23||Integer|Equipment Weight|
|$24|$27|Integers|Base Parameters (of Strength, Agility, Stamina and Magic)|
|$28|$2B|Integers|Current Parameters|
|$2C|$2F|Integers|Evasion and Defence, by Physical and Magical|
|$30|$34|Bitwises|Elemental Properties|
|$35|$37|Bitwises|Status Resistances|
|$38|$39|Bitwises|Weapon and Equipment Properties|
|$3A||Integer|Job Level|
|$3B|$3C|Integer|ABP|

The remaining characters share the same structure.

# Checksum
$1C00 is empty until $1FF0, which is a checksum to check for the save files' legitimacy.