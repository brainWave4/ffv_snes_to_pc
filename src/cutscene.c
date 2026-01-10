// for ExecSound_ext
#include "sound.h"

void showCutscene(uint8_t id);
void decomp(void);

// Address: 000f
// A: cutscene id
void showCutscene(uint8_t id) {}

// Address: 0053
// Decompress
// ++$04f0/$d0: source
// ++$04f3/$d3: destination
void decomp(void) {}