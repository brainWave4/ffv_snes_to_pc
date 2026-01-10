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
static void resetSpriteData(void);
static void func_a18a(void);
static void func_a1cf(void);
static void func_a247(void);
static void func_d230(void);
static void func_d37b(void);
static void func_d3db(void);
static void updateWindowColor(void);
static void updateMonoStereoSetting(void);
static void updateJoypadConfig(void);

static uint16_t addr_7e008e = 0;
static uint16_t addr_7e2100 = 128;
static uint16_t addr_7e0039 = 0;
static uint16_t addr_7e00c7 = 0;
static uint8_t addr_7e0044 = 0;
static uint8_t addr_7e0045 = 0;
static uint8_t addr_7e0048 = 0;

static uint8_t addr_7e4200 = 0;
static uint8_t addr_7e2101 = 0;
static uint8_t addr_7e2105 = 0;
static uint8_t addr_7e2106 = 0;
static uint8_t addr_7e2115 = 0;

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

    // Load $(7e00)34 to Accumulator
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
    //  - Perhaps addr_1f00 is an array of pointers to functions?

    // Store Zero to $8e
    //  - Here, $8e is also involved in func_a1cf(...)
    //  - Could be set when defined directly.

    // Shorten Accumulator to 8-bit
    // Load #$80 to Accumulator (A = 80 in hex number, 128 if converted to dec)
    // Store Accumulator to f:$002100
    //  - Could be set when defined directly,
    //    even if the value is not a zero.

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
    //  - Could be also set when defined directly.
    // Store Zero to $46
    //  - Here, $46 is also involved in:
    //     - _c2a2e9 (get next input) (X is stored there)
    //     - _c2a394 (init tutorial script) (A is stored there)
    //  - Could be also set when defined directly.
    // Store Zero to $47
    //  - Not used elsewhere here.
    //  - Could be defined directly when set elsewhere.
    // Store Zero to $48
    //  - Here, $48 is also involved in:
    //     - _c2a2e9 (get next input)
    //     - _c2a394 (init tutorial script) (A is stored there)
    //  - Could be also set when defined directly.

    // Jump to subroutine _a18a
    func_a18a();

    // Jump to subroutine _d230
    func_d230();

    // Jump to subroutine _d37b
    func_d37b();

    // Jump to subroutine _d3db
    func_d3db();

    // Jump to subroutine _a247
    func_a247();

    // Jump to subroutine _a1cf
    func_a1cf();

    // Jump to subroutine _ff7d
    updateJoypadConfig();

    // Jump to subroutine _d447
    updateWindowColor();

    // Jump to subroutine _f5a9
    updateMonoStereoSetting();

    // Jump to subroutine _a16e
    resetSpriteData();

    // Lengthen Accumulator to 16-bits
    // Load #$f573 to X
    //  .byte   $00,$00,$00,$00
    //  .byte   $00,$00,$00,$01
    //  .byte   $18,$00,$30,$7e
    //  .byte   $00,$10,$01,$00
    //  .byte   $01,$00,$00,$00
    //  .byte   $00,$00,$00,$00
    // Load #$750f to Y
    //  - Address _750f is also used for storing,
    //    but only that one byte.
    // Load #$0017 to A
    //  - $17-1 bytes to copy
    //  - $16 bytes to copy
    //  - 22 bytes to copy
    // MVN #$c0, #$7e
    //  - Copy 22 bytes from #$c0f573 to #$7e750f

    // Return from Subroutine 
}

// Address: _a16e
static void resetSpriteData(void) {
    // PusH Processor status register
    // Lengthen Accumulator to 16-bit
    // Load #$0220 to X
    // [LBL a174] STZ $01fe,x
    // Decrement Index Register X x2
    // Branch to [LBL a174] if zero flag clear
    // Load #$0020 to X
    // Load #$aaaa to Accumulator
    // [LBL a181] STA $03fe,x
    // Decrement Index Register X x2
    // Branch to [LBL a181] if zero flag clear
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
    //  - Could NOT set when defined directly.
    //     - This is because func_a18a(...) is
    //       also called by another function.
    addr_7e4200 = 1;

    // Load #$01 to Accumulator
    // Store Accumulator to $2101
    addr_7e2101 = 1;

    // Load #$00 to Accumulator (mode 0)
    // Store Accumulator to $2105
    addr_7e2105 = 0;
    // Store Accumulator to $2106
    addr_7e2106 = 0;

    // Load #$80 to Accumulator
    //  - $80 = 128
    // Store Accumulator to $2115
    addr_7e2115 = 0;

    // Load #$0008 to X (X = $8)

    // [LBL a1ac] stz $210c,x
    // stz $210c,x (done twice)
    //  - Store Zero to $08210c
    // Decrement Index Register X
    // Branch to [LBL alac], if not equal
    for(uint x = 8; x > 0; x--){

    }

    // Lengthen Accumulator to 16-bit
    // Load #$f53b to X
    //  .byte   $02,$0a,$12,$1a,$77,$77
    //  .byte   $00,$00,$00,$00,$00,$00
    // Load #$2107 to Y
    // Load #$0005 to Accumulator
    // MVN #$c0, #$00
    //  - copy 4 bytes from #$c0f53b to #$002107

    // Load #$212c to Y
    // Load #$0005 to A
    // MVN #$c0, #$00
    //  - copy 4 bytes from #$c0f53b to #$00212c

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

// Address: _d447
static void updateWindowColor(void) {}

// Address: _f549
static void updateMonoStereoSetting(void) {}

// Address: _ff7d
static void updateJoypadConfig(void) {}