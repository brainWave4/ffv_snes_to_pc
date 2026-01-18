// Bank Range: C2/A000 - C2/FFFF, D0

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
static void func_a23b(void);
static void func_a247(void);
static void func_d230(void);
static void func_d25b(void);
static void func_d304(void);
static void func_d34c(void);
static void func_d37b(void);
static void func_d3db(void);
static void updateWindowColor(void);
static void func_d45f(void);
static void updateMonoStereoSetting(void);
static void func_d9fb(void);
static void updateJoypadConfig(void);
static void func_ffc2(void);

// These adresses are loaded before
// having valued stored there
static uint16_t addr_7e0034 = 0;

static uint16_t addr_7e008e;
static uint16_t addr_7e2100;
static uint8_t addr_7e0044;
static uint8_t addr_7e0045;
static uint8_t addr_7e0046;
static uint8_t addr_7e0047;
static uint8_t addr_7e0048;
static uint16_t addr_7e0039;
static uint16_t addr_7e00c7;

static uint8_t addr_7e4200;
static uint8_t addr_7e2101;
static uint8_t addr_7e2105;
static uint8_t addr_7e2106;
static uint8_t addr_7e2115;
static uint8_t addr_7e420b;
static uint16_t addr_7e420c;

// Address: _a016
// Execute Menu
// Q: What address is ($01c7)?
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
    addr_7e0039 = 0;

    // Load $(7e00)34 to Accumulator
    // AND Accumulator with #7
    // Arithmetic Shift Left
    // Transfer Accumulator to X
    // STore Accumulator to $c7 
    //  - Essentially, Address $c7 = ($34 & 7) << 1
    //  - $c7 is also involved in:
    //      - _c2a06b (show menu) (A is stored there)
    //      - _c2a2e9 (get next input) (A is also stored there)
    //      - ...
    //  - $c7 could be a bitmask
    addr_7e00c7 = addr_7e0034 & 7;
    addr_7e00c7 <<= 1;

    // Shorten Accumulator to 8-bit
    // Jump to ($01c7)
}

void updateJoypad(void) {}

void func_a006(void) {}

void func_a008(void) {}

// Address: _a11b
// Initiate Menu
// TODO: Copy bytes
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
    addr_7e008e = 0;

    // Shorten Accumulator to 8-bit
    // Load #$80 to Accumulator (A = 80 in hex number, 128 if converted to dec)
    // Store Accumulator to f:$002100
    addr_7e2100 = 128;

    // Store Zero to $44
    //  - Here, $44 is also involved in:
    //     - _c2a033 (menu command $00: main menu) (A is stored there)
    //     - _c2b25e
    //     - _c2ba7d
    //     - _c2bc5e
    //     - _c2cfdc (menu state $00: main menu)
    //     - _c2d851 (get list of available abilities)
    addr_7e0044 = 0;
    // Store Zero to $45
    //  - Seems to be a bitmask
    addr_7e0045 = 0;
    // Store Zero to $46
    //  - Here, $46 is also involved in:
    //     - _c2a2e9 (get next input) (X is stored there)
    //     - _c2a394 (init tutorial script) (A is stored there)
    addr_7e0046 = 0;
    // Store Zero to $47
    //  - Not used elsewhere here.
    addr_7e0047 = 0;
    // Store Zero to $48
    //  - Here, $48 is also involved in:
    //     - _c2a2e9 (get next input)
    //     - _c2a394 (init tutorial script) (A is stored there)
    addr_7e0048 = 0;

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
// TODO: Loop bytes
static void resetSpriteData(void) {
    // PusH Processor status register
    // Lengthen Accumulator to 16-bit
    // Load #$0220 to X
    
    // [LBL a174] STZ $01fe,x
    //  - Store Zero to ($01fe + x)
    // Decrement Index Register X x2
    //  - X -= 2
    // Branch to [LBL a174] if zero flag clear
    //  - Loop back if X > 0 still

    // Load #$0020 to X
    // Load #$aaaa to Accumulator
    // [LBL a181] STA $03fe,x
    //  - Store A to ($03fe + x)
    // Decrement Index Register X x2
    //  - X -= 2
    // Branch to [LBL a181] if zero flag clear
    //  - Loop back if X > 0 still

    // Pull Processor status Register
    // Return from Subroutine 
}

// TODO: Loops, Byte copying
static void func_a18a(void) {
    // Push data Bank register
    // Push Processor status register
    // Shorten Accumulator to 8-bit

    // Load #$00 to Accumulator
    // Push Accumulator
    // Pull Data Bank Register

    // Load #$01 to Accumulator
    // Store Accumulator to $4200
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
    addr_7e2115 = 128;

    // Load #$0008 to X (X = $8)

    // [LBL a1ac] stz $210c,x
    // stz $210c,x
    //  - Yes, this is repeated twice
    //     - This ensures both the low and high bytes
    //       of the 16-bit addresss is set.
    //  - X is an index of the given address.
    //  - Store Zero to $7e210c + $8 (value of X)
    //  - But whereelse is $7e210c used?
    // Decrement Index Register X
    // Branch to [LBL alac], if not equal
    //  - loop back if X, after decrement, is not zero
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

// TODO: Loop
static void func_a1cf(void) {
    // PusH data Bank register
    // PusH Processor status register
    // Lengthen Accumulator (A) to 16-bit
    // Load $8e to A
    // Store A to f:$00420c
    addr_7e420c = addr_7e008e;

    // Load #$f547 to X
    // [LBL a1dc] lda $c00000,x
    //  - Load ($c00000 + X) to A
    // Branch to [LBL a1ed] if Equal
    //  - Equal is when X loops back to 0
    // Transfer A to Y
    // Increment X x2
    // Load #$0004 to A
    //  - 3 bytes to copy
    // MVN #$c0, #$00
    // Branch to [LBL a1dc]
    
    // [LBL a1ed] PulL Processor status register
    // PulL data Bank register
    // Return from Subroutine
}

// Unstarted
// This function seems to upload text.
static void func_a23b(void) {
    // Store A to ($e0 + y)
    //  - A and Y are inputs
    // CLear Carry flag
    // ADd $e4 to A
    // Increment Y by 2
    // ComPare Y with $e2
    //  - $e2 could be text length limit
    // Branch to [LBL _a23b] if not equal
    // ReTurn to Subroutine
}

// Unstarted
static void func_a247(void) {
    // PusH Processor status register
    // Lengthen A
    // Load #$d000 (53248) to X
    // Store X to $e0
    // Load #$0100 (256) to X
    // Store X to $e2
    // Load #$000c (53248) to X
    // Store X to $e4
    // Load $8e to Y
    // Load #$0000 to A (Weapon Properties)
    // Jump Subroute to _c2a23b
    //  - calls func_a23b(...)
    // Load #$01c0 (448) to X
    // Store X to $e2
    // Load #$0600 (1536) to A (Armor Properties)
    // Jump Subroute to _c2a23b
    // Load #$0008 to X
    // Store X to $e4
    // Load #$0200 to X
    // Store X to $e2
    // Load #$0a80 to A (Item Properties)
    // Jump Subroute to _c2a23b
    // Load #$d200 to X
    // Store X to $e0
    // Load #$0009 to X
    // Store X to $e4
    // Load $8e to Y
    // Load #$1380 to A (D1/1380 (item names))
    // Jump Subroute to _c2a23b
    // Load #$d400 to X
    // Store X to $e0
    // Load #$00ae to X
    // Store X to $e2
    // Load #$0006 to X
    // Store X to $e4
    // Load $8e to Y
    // Load #$1c80 to A (D1/1C80 (spell names))
    // Jump Subroute to _c2a23b
    // Load #$0200 to X
    // Store X to $e2
    // Load #$0009 to X
    // Store X to $e4
    // Jump Subroute to _c2a23b
    // Load #$d600 to X
    // Store X to $e0
    // Load #$00a2 to X
    // Store X to $e2
    // Load #$0005 to X
    // Store X to $e4
    // Load $e4 to Y
    // Load #$5800 to A (battle command names)
    // Jump Subroute to _c2a23b
    // Load #$0100 to X
    // Store X to $e2
    // Load $e8 to Y
    // Store Zero to $e4
    // Load $e8 to A
    // Jump Subroute to _c2a23b
    // Load #$0142 to X
    // Store X to $e2
    // Load #$0008 to X
    // Store X to $e4
    // Load #$6200 to A (passive ability names)
    // Jump Subroute to _c2a23b
    // PulL Processor status register
    // ReTurn from Subroutine
}

// Unstarted
static void func_d230(void) {
    // [LBL d230] PusH data Bank register
    // PusH Process status register

    // Lengthen A
    // Load #$2000 to X
    // Load $8e to A

    // [LBL d239] Decrement X by 2
    // Store Zero to ($9000 + X)
    // Branch to [LBL d239] if Not Equal
    //  - For this case, if X > 0 still
    // Store Zero to $7e

    // [LBL d242] Jump to SubRoutine _c2d298
    // Load $7e to A
    // Increment A
    // Store A to $7e
    // Compare A with #$0004
    // Branch to [LBL d242] if Not Equal

    // Jump to SubRoutine _c2d25b
    // Load #$efeb to X
    // Jump to SubRoutine _c2d9fb

    // PulL Processor status register
    // PulL data Bank register
    // ReTurn from Subroutine
}

// Unstarted
static void func_d25b(void) {
    // Load $8e to X
    
    // [LBL d25d] PusH X onto stack
    // Load ($c0ecc3 + x) to A
    // Store A to $e0
    // Load ($c0ecc5 + x) to A
    // Store A to $e2
    // Load ($c0ecc7 + x) to A
    // Store A to $e4
    // Load ($c0ecc9 + x) to A
    // PuaH A
    // Load ($c0eccb + x) to A
    // Pull value from stack to X
    // Jump to SubRoutine _c2d304
    //  - call func_d304(...)
    // Pull to A
    // CLear Carry flag
    // ADd #$000a to A
    // Transfer A to X
    // ComPare X with #$001e
    // Branch to [LBL d25d] if Not Equal
    
    // Jump to SubRoutine _c2d34c
    //  - call func_d34c(...)
    // Load #$b9a0 to X
    // Load #$9080 to Y
    // Load #$003f to A
    // MVN #$c3,#$7e
    // Return To Subroutine
}

// Q: What does DEC addr mean?
static void func_d304(void) {
    // PusH data Bank register
    // PusH Processor status register
    // Store $e8 to A

    // [LBL d308] PusH X
    // LoaD $e4 to A
    // Clear Cary flag
    // Add ($c00002 + X) to A
    // Transfer A to Y
    // Load $e0 to A
    // Clear Cary flag
    // Add ($c00000 + X) to A
    // Transfer A to X
    // Load $e2 to A
    // Add $8e to A
    // And A with #$00ff
    // Compare A with #$00d4
    // Branch to [LBL d33a] if EQual
    // Compare A with #$00d3
    // Branch to [LBL d332] if EQual
    // Load #$001f to A
    // MVN #$d2, #$7e
    // Branch to [LBL d340]
    // [LBL d332] Load #$001f to A
    // MVN #$d3, #$7e
    // Branch to [LBL d340]
    // [LBL d33a] Load #$001f to A
    // MVN #$d4, #$7e
    // [LBL d340] PulL X
    // INcrement X by 4
    // DEC $e8
    // Branch to [LBL d308] if Not Equal

    // PulL Processor status register
    // PulL data Bank register
    // Return To Subroutine
}

// Q: What does DEC addr mean?
static void func_d34c(void) {
    // Load $8e to X
    // [@d34e] PusH X
    // Transfer X to A
    // CLear Carry flag
    // Add #$0017 to A
    // Transfer A to X
    // CLear Carry flag
    // Add #$0007 to A
    // Transfer A to Y
    // Load #$0008 to A
    // Store $85 to A
    // [@d35f] Load ($9000 + x) to A
    // And A with #$00ff
    // Store A to ($9000 + y)
    // DEcrement X
    // DEcrement Y by 2
    // DEC $85
    // Branch to [@d35f] if Not Equal
    // PulL A
    // CLear Carry flag
    // Add #$0020 to A
    // Transfer A to X
    // Compare A with #$0800
    // Branch to [@d34e] is Not Equal
    // Return To Subroutine
}

// Unstarted
static void func_d37b(void) {
    // PusH data Bank
    // PusH Processor status
    // Lengthen A

    // Load #$efe2 to X
    // Jump to SubRoute func_d9fb(...)

    // PulL Processor status
    // PulL data Bank
    // ReTurn to Subroutine
}

// TODO: Move sets to data
static void func_d3db(void) {
    // PusH data Bank
    // PusH Processor status
    // Lengthen A

    // STore Zero to $7e
    // [@d3e1] Jump to SubRoutine func_d45f(...)
    // LoaD $7e to A
    // Increment A
    // Store A to $7e
    // Compare A to #$0004
    // Branch to [@d3e1] if Not Equal

    // LoaD #$b9e0 to X
    // LoaD #$7480 to Y
    // LoaD #$001f to A
    // MVN #$c3, #$7e

    // LoaD #$f867 to X
    // LoaD #$74c0 to Y
    // LoaD #$001f to A
    // MVN #$c0, #$7e

    // LoaD #$b960 to X
    // LoaD #$74e0 to Y
    // LoaD #$001f to A
    // MVN #$c3, #$7e

    // Jump to SubRoutine func_d42e(..)
    // LoaD #$eff4 to X
    // LoaD #$4300 to Y
    // LoaD #$0006 to A
    // MVN #$c0, #$00

    // Shorten A
    // STore Zero to $2121
    // LoaD #$01 to A
    // STore A to $420b

    // PulL Processor status
    // PulL data Bank
    // ReTurn to Subroutine
}

// Address: _d447
// Unstarted
static void updateWindowColor(void) {
    // PusH Processor status
    // Lengthen A

    // Load $8e to Y
    // [@d44c] Load $0971 (window color) to A
    // Store A to ($7302 + y)
    // Transfer Y to A
    // CLear Carry flag
    // Add #$0008 to A
    // Transfer A to Y
    // Compare A with #$0100
    // Branch to [@d44c] when Not Equal

    // PulL Processor status
    // ReTurn to Subroutine
}

// Unstarted
static void func_d45f(void) {
    // PusH data Bank
    // PusH Processor status
    // Shorten A

    // Jump to SubRoutine _c2d4c5
    //  - func_d4c5(..)
    // LoaD $80 to X
    // Load ($0500 + X) to A
    // And A with #$07
    // eXchange higher and lower Bytes in A
    // LoaD ($0501 + x) to A
    // And A with #$1f
    // LoaD $7e to Y
    // set flags based on ($051a + X) and A
    // Branch to [@d484] if oVerflow is Set
    // Branch to [@d47e] if PLus
    //  - as in if negative flag clear
    // LoaD #$15 to A

    // [@d47e] eXchange higher and lower Bytes in A
    // Jump to SubRoutine _c2d492
    //  - func_d492(..)
    // BRAnch to [@d48f]

    // [@d484] LoaD #$f807 to X
    //  - grayscale battle character palette ???
    // Lengthen A
    // Jump to SubRoutine _c2d4b4
    //  - func_d4b4(..)
    // MVN #$c0, #$7e

    // PulL Processor status
    // PulL data Bank
    // ReTurn to Subroutine
}

// Address: _f5a9
// Unstarted
static void updateMonoStereoSetting(void) {
    // PusH Processor status
    // Shorten A

    // Load f:$000973 to A
    // And A with #$02
    // Logical Shift A Right
    // CLear Carry flag
    // Add #$f3 to A
    //  - $f3 is stereo; $f4 is mono
    // Store A to f:$001d00
    // Jump to Subroutine Long ExecSound_ext

    // PulL Processor status
    // ReTurn to Subroutine
}

// TODO: Move bytes
static void func_d9fb(void) {
    // Load ($c00000 + X) to A
    //  - X is an input
    // Store A to f:$002116
    
    // Increment X by 2
    // Load #$4300 to Y
    // Load #$0006 to A
    // MVN #$c0, #$00
    
    // Shorten A
    // Load #$01 to A
    // Store A to $420b
    addr_7e420b = 1;

    // ReTurn to Subroutine
}

// Address: _ff7d
// Unstarted
static void updateJoypadConfig(void) {
    // PusH data Bank
    // PusH Direct page
    // PusH A
    // PusH X
    // PusH Y
    // PusH Processor status

    // Push Effect Address $0000 into stack
    // PulL data Bank
    // PulL data Bank
    // Lengthen A
    // Push Effect Address $0100 into stack
    // PulL Direct page
    // LoaD #$0416 to A
    //  - delay = 22 frames
    //  - rate = 4 frames
    // STore A to $18
    // STore Zero to $4d (single controller)
    // LoaD #$0000 to Y
    // Transfer Y to X

    // [@ff99] Load ($0975 + y) to A (joypad config)
    // Jump SubRoutine to func_ffc2(...)
    // Store A to ($26 + x)
    // INcrement Y
    // INcrement X by 2
    // ComPare Y to #$0007
    // Branch to [@ff99] if Not Equal

    // STore Zero to $0e
    // STore Zero to $14
    // STore Zero to $16
    // LoaD #$0101 to A
    // LoaD #$000c to X

    // [@ffb5] DEcrement X by 2
    // STore A to ($1a + x)
    // Branch to [@ffb5] if Not Equal

    // PulL Processor status
    // PulL Y
    // PulL X
    // PulL A
    // PulL Direct page
    // PulL data Bank
    // ReTurn to Subroutine
}

// Unstarted
static void func_ffc2(void) {
    // PusH X
    // And A with #$00fc
    // eXchange higher and lower Bytes of A
    // Load #$0000 to X

    // [@ffca] Shift A left
    // Branch to [@ffd7] if Carry Set
    // Increment X by 2
    // ComPare X with #$000c
    // Branch to [@ffca] if Not Equals

    // Load #$0000 to X
    // Load ($c0e7b8 + X) to A

    // PulL X
    // ReTurn to Subroute
}