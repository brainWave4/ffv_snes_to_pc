A small section designed for storing data. They are preserved even when the power turns off. They are mapped Bank 30-3F by 6000-7FFF, but for simplicity sake, they will be referred by $0000 onwards.

# Saves

There are four save slot save slots:
|From|To|Type|Section|
|---|---|---|---|
|$0000|$06FF|Set|Save Slot 1|
|$0700|$0DFF|Set|Save Slot 2|
|$0E00|$14FF|Set|Save Slot 3|
|$1500|$1BFF|Set|Save Slot 4|

The Save Slot 1 is structured further below. It's the same as List > 0xxx > 5xx - Bxx For Saving. As for the remaining save slot, they are also structured the same, just at a different offset.

## Character Slots
|From|To|Type|Section|
|---|---|---|---|
|$0000|$004F|Set|Character Slot 1|
|$0050|$009F|Set|Character Slot 2|
|$00A0|$00EF|Set|Character Slot 3|
|$00F0|$013F|Set|Character Slot 4|

For the first character:
|From|To|Type|Section|
|---|---|---|---|
|$00||Bitwise|ID, Gender, In party, Row|
|$01||ID|Job|
|$02||Value|Level|
|$03|$05|Value|Exp|
|$06|$07|Value|Current HP|
|$08|$09|Value|Max HP|
|$0A|$0B|Value|Current MP|
|$0C|$0D|Value|Max MP|
|$0E|$14|IDs|Equipments|
|$15||ID|Monster Caught|
|$16|$19|IDs|Commands|
|$1A|$1D|Bitwise|Status|
|$1E||Bitwise|Action (Defend, Guard etc) Flags|
|$1F||Bitwise|Damage Modifier|
|$20|$21|Bitwise|Innate Abilities|
|$22||Bitwise|Elemental Boosts|
|$23||Value|Equipment Weight|
|$24|$27|Set|Base Parameters|
|$28|$2B|Set|Current Parameters|
|$2C|$2F|Value|Evasion and Defence, by Physical and Magical (per Byte)|
|$30|$34|Bitwise|Elemental Properties|
|$35|$37|Bitwise|Status Resistances|
|$38|$39|Bitwise|Weapon and Equipment (per Byte) Properties|
|$3A||Value|Job Level|
|$3B|$3C|Value|ABP|
|$3D|$3F|Bitwise|Magic Level Progression|
|$40|$43|Bitwise|Equipment Category|
|$44|$45|Value|Attack|
|$46||Bitwise|Attack ID Reaction|
|$4A|$4D|Value|Freelancer Parameters|
|$4E|$4F|Bitwise|Freelancer Innate Abilities|

The parameters (using Base Parameters as an example) are structured:

|From|To|Type|Section|
|---|---|---|---|
|$24||Value|Strength|
|$25||Value|Agility|
|$26||Value|Stamina|
|$27||Value|Magic|

## Items

|From|To|Type|Section|
|---|---|---|---|
|$0140|$023F|ID|Current Items (per Byte)|
|$0240|$033F|Value|Number of said Items (per Byte)|

# Checksum
$1C00 is empty until $1FF0, which is a checksum to check for the save files' legitimacy.