A RAM is where the game stores variable for future use. It is mapped at Bank 7E-7F. It is also mirrored at Bank 00-3F and 80-BF, both by $0000 - $1FFFF, making the addresses interchangable for ease of access.

# Battle
|From|To|Type|Section|
|---|---|---|---|
|7E/0020||Integer|Temproary Attached Spell|
|7E/0021||Integer|Temproary Indicator to Skip Name|
|7E/0022||Integer|Temproary Party Targets, Monster AI when Charmed|
|7E/0023||Integer|Temproary Monster Targets|
|7E/0032|7E/0033|Integer|Attacker Offset|
|7E/0034|7E/0035|Integer|Spell Offset|
|7E/0036|7E/0037|Integer|Timer Offset|
|7E/0039||Integer|Attacker Offset 2|
|7E/003A|7E/003B|Integers|RNG|
|7E/0047||Index|Attacker's|
|7E/0048||Index|Target's|
|7E/0049||Integer|Target Offset|
|7E/004B||Integer|AI Offset|
|7E/004D||Bitwise|Attack Element (From Lowest: Fire, Ice, Lightning, Poison, Holy, Earth, Wind and Water)|
|7E/004E||Integer|Hit Percent|
|7E/004F||Integer|Evade Percent|
|7E/0050|7E/0051|Integer|Attack|
|7E/0052|7E/0053|Integer|Attack Multiplier|
|7E/0054|7E/0055|Integer|Defence|
|7E/0056|7E/0057|Flag|Attack Missed|
|7E/0057|7E/0059|Integers|Parameters for Various Purposes|
|7E/005A||Integer|Sword Block|
|7E/005B||Integer|Knife Block|
|7E/005C||Integer|Elf Cape|
|7E/005D||Integer|Shield Block|
|7E/005E||Integer|Blade Grasp|
|7E/005F||Integer|Critical Hit|
|7E/0060||Flag|Buffed by Spellblade|
|7E/0061||Flag|Is Target Killed|
|7E/0062||Flag|Does Attack Heal Instead|
|7E/0063||Flag|Targets Attacker|
|7E/0065||Integer|Monster Targets|
|7E/0066||Integer|Party Targets|
|7E/013B|7E/0142|IDs|Field Items Won|
|7E/04F0|7E/04F1|ID|Encounter Index|
|7E/04F2||ID|Terrain Type|

# Menu
# For Saving
These range of addresses are to be stored in a save slot address when saving the game.

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
|7E/0522||Bitwise|Equipment Elements|
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
|7E/053D|7E/053F|Bitwise|Magic Level Progression|
|7E/0540|7E/0543|Bitwise|Equipment Category|
|7E/0544|7E/0545|Integer|Attack|
|7E/0546||Bitwise|Previous Command|
|7E/0546||Bitwise|Previous Attack|
|7E/0546||Bitwise|Previous Item|
|7E/0546||Bitwise|Previous Element|
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

## Job Progression
|From|To|Type|Section|
|---|---|---|---|
|7E/0840|7E/0843|Bitwise|Jobs Unlocked|
|7E/0843|7E/0844|Integer|Character 1's Knight Lv, ABP|
|7E/0845|7E/0846|Integer|Character 1's Monk Lv, ABP|
|7E/0847|7E/0848|Integer|Character 1's Theif Lv, ABP|
|7E/0849|7E/084A|Integer|Character 1's Dragoon Lv, ABP|
|7E/084B|7E/084C|Integer|Character 1's Ninja Lv, ABP|
|7E/084D|7E/084E|Integer|Character 1's Samurai Lv, ABP|
|7E/084F|7E/0850|Integer|Character 1's Berserker Lv, ABP|
|7E/0851|7E/0852|Integer|Character 1's Ranger Lv, ABP|
|7E/0853|7E/0854|Integer|Character 1's Mystic Knight Lv, ABP|
|7E/0855|7E/0856|Integer|Character 1's White Mage Lv, ABP|
|7E/0857|7E/0858|Integer|Character 1's Black Mage Lv, ABP|
|7E/0859|7E/085A|Integer|Character 1's Time Mage Lv, ABP|
|7E/085B|7E/085C|Integer|Character 1's Summoner Lv, ABP|
|7E/085D|7E/085E|Integer|Character 1's Blue Mage Lv, ABP|
|7E/085F|7E/0860|Integer|Character 1's Red Mage Lv, ABP|
|7E/0861|7E/0862|Integer|Character 1's Beastmaster Lv, ABP|
|7E/0863|7E/0864|Integer|Character 1's Chemist Lv, ABP|
|7E/0865|7E/0866|Integer|Character 1's Geomancer Lv, ABP|
|7E/0867|7E/0868|Integer|Character 1's Bard Lv, ABP|
|7E/0869|7E/086A|Integer|Character 1's Dancer Lv, ABP|
|7E/086B|7E/086C|Integer|Character 1's Mime Lv, ABP|
|7E/086D|7E/086E|Integer|Character 1's Freelancer Lv, ABP (useless)|
|7E/086F|7E/089A|Integers|Character 2's Jobs Lv, ABP|
|7E/089B|7E/08C6|Integers|Character 3's Jobs Lv, ABP|
|7E/08C7|7E/08F2|Integers|Character 4's Jobs Lv, ABP|
|7E/08F3||Integer|Bart's Number of Abilities|
|7E/08F4||Integer|Lenna's Number of Abilities|
|7E/08F5||Integer|Galuf/Krile's Number of Abilities|
|7E/08F6||Integer|Faris's Number of Abilities|
|7E/08F7|7E/090A|Bitwise|Bart's Unlocked Abilities|
|7E/090B|7E/091E|Bitwise|Lenna's Unlocked Abilities|
|7E/091F|7E/0932|Bitwise|Galuf/Krile's Unlocked Abilities|
|7E/0933|7E/0946|Bitwise|Faris's Unlocked Abilities|

For an integer used for a Job's Lv and ABP, the highest 4 bits are used for the former while the remaining 12 bits are used for the latter.

Jobs Lv and ABP for the rest of the characters are ordered the same as Character 1's.

## Game Progression
|From|To|Type|Section|
|---|---|---|---|
|7E/0947|7E/0949|Integer|Gil
|7E/094A|7E/094D|Integer|Time Played (in Frames)
|7E/094E|7E/094F|Integer|Number of Enemies Defeated
|7E/0950|7E/096F|Integer|Magic Unlocked

## Config
|From|To|Type|Section|
|---|---|---|---|
|7E/0970||Integer|Command Set, Message Speed, Battle Mode, Battle Speed|
|7E/0971|7E/0972|Integer|Window Color (in 555 RBG)|
|7E/0973||Bitwise|Re-Equip, Sound, Cursor, Gauge Display|
|7E/0974||Bitwise|Controller(Normal/Custom, Single/Multi)|
|7E/0975||Bitwise|Button Configure A|
|7E/0976||Bitwise|Button Configure B|
|7E/0977||Bitwise|Button Configure X|
|7E/0978||Bitwise|Button Configure Y|
|7E/0979||Bitwise|Button Configure L|
|7E/097A||Bitwise|Button Configure R|
|7E/097B||Bitwise|Button Configure Select|
|7E/097C||Bitwise|Character 1 (1P/2P)|
|7E/097D||Bitwise|Character 2 (1P/2P)|
|7E/097E||Bitwise|Character 3 (1P/2P)|
|7E/097F||Bitwise|Character 4 (1P/2P)|
|7E/0980||Bitwise|Character 1 Shortcut Commands Placement|
|7E/0981||Bitwise|Character 2 Shortcut Commands Placement|
|7E/0982||Bitwise|Character 3 Shortcut Commands Placement|
|7E/0983||Bitwise|Character 4 Shortcut Commands Placement|

## Names
|From|To|Type|Section|
|---|---|---|---|
|7E/0990|7E/0995|Text|Bartz's|
|7E/0996|7E/099B|Text|Lenna's|
|7E/099C|7E/09A1|Text|Galuf's|
|7E/09A2|7E/09A7|Text|Faris's|
|7E/09A8|7E/09B3|Text|Krile's|

## Battle Progression
|From|To|Type|Section|
|---|---|---|---|
|7E/09B4||Integer|Magic Lamp|
|7E/09B5||Integer|Number of Escapes|
|7E/09B6||Integer|Wonder Rod Magic|
|7E/09C0|7E/09C1|Integer|Total Number of Battles|
|7E/09C2|7E/09C3|Integer|Total Times Saves|
|7E/09C4||Integer|Battle Results|
|7E/09C5|7E/09D3|Bitwises|Battle Events|

## Field

|From|To|Type|Section|
|---|---|---|---|
|7E/09D4|7E/0A13|Bitwises|Treasures Opened|
|7E/0A14|7E/0AD3|Bitwises|Events Cleared|
|7E/0AD4|7E/0AD5|ID|Current Town/Dungeon|
|7E/0AD6|7E/0AD7|ID|Current World|
|7E/0AD8||Integer|Player's X Position|
|7E/0AD9||Integer|Player's Y Position|
|7E/0ADA||Integer|Character Representing Player|
|7E/0ADB||Integer|Player's Facing Direction|
|7E/0ADC||Integer|Current Vehicle|
|7E/0ADD||ID|Chocobo Settings|
|7E/0ADE||Integer|Chocobo's Height (highest bit toggles visibility)|
|7E/0ADF||Integer|Chocobo's X Position|
|7E/0AE0||Integer|Chocobo's Y Position|
|7E/0AE1|7E/0AE4|Integers|Black Chocobo|
|7E/0AE5|7E/0AE8|Integers|Hiryuu|
|7E/0AE9|7E/0AEC|Integers|Submarine|
|7E/0AED|7E/0AF0|Integers|Steamship|
|7E/0AF1|7E/0AF4|Integers|Airship|
|7E/0AF5|7E/0AF6|ID|Teleport Map|
|7E/0AF7||Integer|Teleport Map X|
|7E/0AF8||Integer|Teleport Map Y|
|7E/0AF9||Integer|Random Number Seed|
|7E/0AFA||Integer|Walking Speed|
|7E/0AFB||Integer|Enable Timer|
|7E/0AFC|7E/0AFD|Integer|Timed Events Timer|
|7E/0AFE|7E/0AFF|Integer|Timed Events End|

All Vehicles (Black Chocobo, Hiryuu, Submarine, Steamship and Airship) are structured the same as Chocobo.

# Music

|From|To|Type|Section|
|---|---|---|---|
|7E/1D00||Integer|Music Data|