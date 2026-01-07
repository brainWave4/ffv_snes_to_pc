#include <stdint.h>

// for subroute _c10009
#include "btlgfx.h"

// for ExecSound_ext
#include "sound.h"

void execMenu(void);
void updateJoypad(void);
void func_a006(void);
void func_a008(void);
static void initMenu(void);
static void func_a16e(void);
static void func_a18a(void);
static void func_a1cf(void);
static void func_a247(void);
static void func_d230(void);
static void func_d37b(void);
static void func_d3db(void);
static void func_d447(void);
static void func_f549(void);
static void func_ff7d(void);

static uint16_t add_39 = 0;
static uint16_t add_c7 = 0;
static uint8_t add_44 = 0;
static uint8_t add_45 = 0;
static uint8_t add_48 = 0;

// Address: _a016
// Execute Menu
void execMenu(void) {
    // Jump to subroutine InitMenu
    initMenu();
    
    // Store Zero to $39
    //  - $39 is also involved in:
    //    - here
    //      - _c2a06b (show menu)
    //      - _c2b8ae (A is stored there)
    //      - _c2ba7d
    //      - _c2bc5e
    //      - _c2bd47
    //      - _c2bf2e
    //      - _c2c56b
    //      - _c2c803 (menu state $05)
    //    - field
    //      - GiveGil (_0efe)
    //      - CalcGil
    //      - HexToDec
    //      - EventCmd_ad
    //      - CalcInnPrice
    //      - _c0bf3f (calculate gp [event])
    //  - in field, $39 seems to be involved with Gil
    //  - Perhaps it's only involved in Gil
    //    multiplication in tens.
    //  - Could be set when defined directly.

    // Load $34 to Accumulator
    // AND Accumulator with #7
    // Arithmetic Shift Left
    // Transfer Accumulator to X
    // STore Accumulator to $c7 
    //  - Essentially, $c7 = ($34 && 7) << 1
    //  - $c7 is also involved in:
    //      - _c2a06b (show menu) (A is stored there)
    //      - _c2a2e9 (get next input) (A is also stored there)
    //      - ...

    // Shorten Accumulator to 8-bit
    // Jump to ($01c7)
}

void updateJoypad(void) {}

void func_a006(void) {}

void func_a008(void) {}

// Address: _a11b
// Initiate Menu
static void initMenu(void) {
    // Lengthen Accumulator and Indexes to 16-bit
    // Load #$0100 to Accumulator
    // Transfer Accumulator to Direct Page Register (Set direct page to #$0100)
    // Load #$f533 to X (set as source data address)
    //  - The addres contains Interrupt Jump Code
    // Load #$1f00 to Y (set as destination data address)
    // Load #$0007 to Accumulator (6 bytes to copy)
    // MoVe (Copy [6] bytes of) memories from $c0(f533) to $7e(1f00)

    // Store Zero to $8e
    // Shorten Accumulator to 8-bit
    // Load #$80 to Accumulator
    // Store Accumulator to f:$002100

    // Store Zero to $44
    //  - Here, $44 is also involved in:
    //     - _c2a033 (menu command $00: main menu) (A is stored there)
    //     - _c2b25e
    //     - _c2ba7d
    //     - _c2bc5e
    //     - _c2cfdc (menu state $00: main menu)
    //     - _c2d851 (get list of available abilities)
    //  - Could be set when defined directly.
    // Store Zero to $45
    //  - Seems to be a bitmask
    // Store Zero to $46
    //  - Here, $46 is also involved in:
    //     - _c2a2e9 (get next input) (X is stored there)
    //     - _c2a394 (init tutorial script) (A is stored there)
    // Store Zero to $47
    //  - Not used elsewhere here.
    // Store Zero to $48
    //  - Here, $48 is also involved in:
    //     - _c2a2e9 (get next input)
    //     - _c2a394 (init tutorial script) (A is stored there)
    // Jump to subroutine _a18a
    // Jump to subroutine _d230
    // Jump to subroutine _d37b
    // Jump to subroutine _d3db
    // Jump to subroutine _a247
    // Jump to subroutine _a1cf
    // Jump to subroutine _ff7d (Update Joypad Config)
    // Jump to subroutine _d447 (Update Window Color)
    // Jump to subroutine _f5a9 (Update Mono/Stereo Setting)
    // Jump to subroutine _a16e (Reset Sprite Data)

    // Lengthen Accumulator to 16-bits
    // Load #$f573 to X
    // Load #$750f to Y
    // Load #$0017 to A
    // MoVe memory #$c0 to #$7e in increasing order

    // Return from Subroutine 
}

// Reset Sprite Data
static void func_a16e(void) {
    // PusH Processor status register
    // Lengthen Accumulator to 16-bit
    // Load #$0220 to X
    // [LBL a174] STZ $01fe,x
    // Decrement Index Register X x2
    // Branch to [LBL a174] if (what is?) not equal
    // Load #$0020 to X
    // Load #$aaaa to Accumulator
    // [LBL a181] STA $03fe,x
    // Decrement Index Register X x2
    // Branch to [LBL a181] if (what is?) not equal
    // Pull Processor status Register
    // Return from Subroutine 
}

static void func_a18a(void) {
    // Push data Bank register
    // Push Processor status register
    // Shorten Accumulator to 8-bit
    // Load #$00 to Accumulator
    // Push Accumulator
    // Pull Data Bank Register
    // Load #$01 to Accumulator
    // Store Accumulator to $4200
    // Load #$01 to Accumulator
    // Store Accumulator to $2101
    // Load #$00 to Accumulator (mode 0)
    // Store Accumulator to $2105
    // Store Accumulator to $2106
    // Load #$80 to Accumulator
    // Store Accumulator to $2115
    // Load #$0008 to X
    // [LBL a1ac] stz $210c,x
    // stz $210c,x (done twice?)
    // Decrement Index Register X
    // Branch to [LBL alac], if not equal
    // Lengthen Accumulator to 16-bit
    // Load #$f53b to X
    // Load #$2107 to Y
    // Load #$0005 to Accumulator
    // MVN #$c0, #$00
    // Load #$212c to Y
    // Load #$0005 to A
    // MVN #$c0, #$00
    // PulL Processor status register
    // PulL data Bank register
    // Return from Subroutine
}

static void func_a1cf(void) {
    // PusH data Bank register
    // PusH Processor status register
    // Lengthen Accumulator (A) to 16-bit
    // Load $8e to A
    // Store A to f:$00420c
    // Load #$f547 to X
    // [LBL a1dc] lda $c00000,x
    // Branch to [LBL a1ed] if Equal
    // Transfer A to Y
    // Increment X x2
    // Load #$0004 to A
    // MVN #$c0, #$00
    // Branch to [LBL a1dc]
    // [LBL a1ed] PulL Processor status register
    // PulL data Bank register
    // Return from Subroutine
}

static void func_a247(void) {}

static void func_d230(void) {}

static void func_d37b(void) {}

static void func_d3db(void) {}

// Update Window Color
static void func_d447(void) {}

// Update Mono/Stereo Setting
static void func_f549(void) {}

// Update Joypad Config
static void func_ff7d(void) {}