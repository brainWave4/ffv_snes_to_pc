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