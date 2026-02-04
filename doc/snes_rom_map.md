A ROM contains the data as well as the instruxtions of a game. Since FFV is a Hi-ROM, it is mapped at Bank C0-FF.

# Bank C0
This bank covers Field.

# Bank C1
This bank covers Battle Graphics. They are to be put into Btlgfx Module.

# Bank C2
This bank covers 2 sections: One for battling, and another for menus.

## $0000 - $9FFF Battle
|From|To|Type|Section|
|---|---|---|---|---|
|$0148|$01B0|Text|Hidden Message|
|$04FB|$200A|Instr|Commands|
|$200B|$27BE|Instr|Timer|
|$27BF|$3E7E|Instr|AI|

## $A000 - $FFFF Menu

# Bank C3
This bank covers Cutscenes

# Banks C4 - C6
This range of bank covers Audio. They are to be put into Sound Module.

# Banks C7 - DF