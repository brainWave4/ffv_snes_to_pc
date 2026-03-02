// Bank Range: C2/A000 - C2/FFFF, D0
#include <stdint.h>

#include "menu.h"

// for subroute _c10009
#include "btlgfx.h"

// for ExecSound_ext
#include "sound.h"

static void mainMenu(void);
static void collectItemsAfterBattle(void);
static void shop(void);
static void initMenuSettings(void);
static void tutorial(void);
static void galufToKrile(void);
static void nameChange(void);
static void showMenu(void);
static void dma(void);
static void waitForVblank(void);
static void initMenu(void);
static void resetSpriteData(void);
static void func_c2a18a(void);
static void func_c2a1cf(void);
static void func_c2a1f0(void);
static void func_c2a23b(void);
static void func_c2a247(void);
static void getNextInput(void);
static void getPressedBtnIdx(void);
static void menuState14(void);
static void menuState0e(void);
static void menuState0f(void);
static void initTutorialScript(void);
static void menuState15(void);
static void menuState10Up(void);
static void menuState10Down(void);
static void menuState10Left(void);
static void menuState10Right(void);
static void menuState0D(void);
static void func_c2a4f3(void);
static void func_c2a519(void);
static void func_c2a54a(void);
static void func_c2a55f(void);
static void func_c2a5b5(void);
static void func_c2a5e6(void);
static void func_c2a607(void);
static void func_c2a618(void);
static void func_c2a67a(void);
static void func_c2a693(void);
static void func_c2a6b9(void);
static void func_c2a6de(void);
static void func_c2a6fc(void);
static void func_c2a780(void);
static void func_c2a79c(void);
static void func_c2a7fc(void);
static void func_c2a81d(void);
static void func_c2a826(void);
static void func_c2a848(void);
static void func_c2a85a(void);
static void func_c2a878(void);
static void func_c2a892(void);
static void func_c2a8cb(void);
static void func_c2a8f0(void);
static void func_c2a8fa(void);
static void func_c2a91c(void);
static void func_c2a925(void);
static void func_c2a935(void);
static void func_c2a948(void);
static void func_c2a958(void);
static void func_c2a965(void);
static void func_c2a96c(void);
static void func_c2a96f(void);
static void func_c2a9d9(void);
static void func_c2a9fd(void);
static void func_c2aa12(void);
static void func_c2aa35(void);
static void func_c2aa4e(void);
static void func_c2aa6e(void);
static void func_c2aa89(void);
static void func_c2aabb(void);
static void func_c2aad1(void);
static void func_c2aae9(void);
static void func_c2ab19(void);
static void func_c2ab20(void);
static void func_c2ab36(void);
static void func_c2ab4c(void);
static void func_c2ab91(void);
static void func_c2aba0(void);
static void func_c2abb2(void);
static void func_c2abc1(void);
static void func_c2abd1(void);
static void func_c2abdb(void);
static void func_c2abdf(void);
static void func_c2abf2(void);
static void func_c2ac01(void);
static void func_c2ac0e(void);
static void func_c2ac1e(void);
static void func_c2ac5e(void);
static void func_c2ac90(void);
static void func_c2acc3(void);
static void func_c2acd6(void);
static void func_c2acff(void);
static void func_c2ad3e(void);
static void func_c2ad5b(void);
static void func_c2adb0(void);
static void func_c2adcc(void);
static void func_c2addf(void);
static void func_c2ae11(void);
static void func_c2ae31(void);
static void func_c2ae47(void);
static void func_c2ae4b(void);
static void func_c2ae5c(void);
static void func_c2ae6b(void);
static void func_c2ae6f(void);
static void func_c2af1b(void);
static void func_c2af87(void);
static void func_c2af91(void);
static void func_c2b04f(void);
static void func_c2b079(void);
static void func_c2b0d6(void);
static void func_c2b106(void);
static void func_c2b154(void);
static void func_c2b16e(void);
static void func_c2b19a(void);
static void func_c2b1ca(void);
static void func_c2b1ec(void);
static void func_c2b257(void);
static void func_c2b25b(void);
static void func_c2b25e(void);
static void func_c2b2bd(void);;
static void func_c2b2fb(void);
static void rowAButtonPressed(void);
static void func_c2b3db(void);
static void func_c2b3e9(void);
static void rowBButtonPressed(void);
static void func_c2b429(void);
static void func_c2b480(void);
static void func_c2b48f(void);
static void func_c2b4a8(void);
static void func_c2b4d7(void);
static void func_c2b511(void);
static void func_c2b521(void);
static void func_c2b5ea(void);
static void func_c2b676(void);
static void func_c2b6b9(void);
static void func_c2b74b(void);
static void func_c2b752(void);
static void func_c2b796(void);
static void func_c2b7a0(void);
static void func_c2b7ad(void);
static void func_c2b7fc(void);
static void func_c2b811(void);
static void func_c2b845(void);
static void func_c2b84d(void);
static void func_c2b879(void);
static void func_c2b87c(void);
static void func_c2b8ae(void);
static void func_c2b91d(void);
static void func_c2b922(void);
static void func_c2b948(void);
static void func_c2b955(void);
static void func_c2b993(void);
static void func_c2b998(void);
static void func_c2ba05(void);
static void func_c2ba0a(void);
static void func_c2ba63(void);
static void func_c2ba7d(void);
static void func_c2bbfa(void);
static void func_c2bc27(void);
static void func_c2bc2a(void);
static void func_c2bc2d(void);
static void func_c2bc48(void);
static void func_c2bc5e(void);
static void func_c2bcd9(void);
static void func_c2bce0(void);
static void func_c2bd3d(void);
static void func_c2bd47(void);
static void func_c2bda5(void);
static void func_c2bdb5(void);
static void func_c2bdc6(void);
static void func_c2bdf3(void);
static void func_c2bdf6(void);
static void func_c2be2e(void);
static void func_c2be64(void);
static void func_c2bec8(void);
static void func_c2becd(void);
static void func_c2bef4(void);
static void saveToSlot(void);
static void loadFromSlot(void);
static void func_c2bf7d(void);
static void func_c2bf89(void);
static void func_c2c162(void);
static void func_c2c16a(void);
static void func_c2d230(void);
static void func_c2d25b(void);
static void func_c2d304(void);
static void func_c2d34c(void);
static void func_c2d37b(void);
static void func_c2d3db(void);
static void updateWindowColor(void);
static void func_c2d45f(void);
static void updateMonoStereoSetting(void);
static void func_c2d9fb(void);
static void func_c2e0c8(void);
static void func_c2f588(void);
static void updateJoypadInput(void);
static void func_c2fedo(void);
static void setControllerSettingsBattle(void);
static void setControllerSettingsField(void);
void updateJoypadConfig(void);
static void func_c2ffc2(void);

// Address: $7e0500 - $7e0aff
Save current_save;

// These adresses are loaded before
// having valued stored there
static uint16_t addr_7e0034 = 0;

// Address: $306000 - $307bff
static Save[4] saves;

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

// _a000 is ExecMenu_ext
// Branches to _a016 execMenu(..)
// Could have called it directly by
//   making the function public.

// UpdateJoypad_ext
//  - Jump SubRoutine to _ff7d updateJoypadConfig(..)
//  - ReTurn to subroutine Long
// Could have called it directly by
//   making the function public.

// _a006
// Branches to func_c2a00a(..)
// Could have called it directly by
//   making the function public.

// _a008
// Branches to func_c2a00f(..)
// Could have called it directly by
//   making the function public.

void func_c2a00a(void) {
    setControllerSettingsBattle();
    updateJoypadInput();
}

void func_c2a00f(void) {
    setControllerSettingsField();
    updateJoypadInput();
}

// _a012
//  - Jump SubRoutine to updateJoypadInput(..)
//  - ReTurn to subroutine Long
// Could have called it directly by
//   making the function public.

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

// CommonReturn
//  - Jump SubRoutine to func_c2b2bd(..)
//  - Then move onto _a030
//     - Essentially does nothing
//  - Could've called the first function directly

// Address: _a030
//  - Shorten A
//  - Return To subroutine Long

// Address: _a033
// Menu Command $00
// Unstarted
static void mainMenu(void) {
    // LoaD $35 to A
    // STore A to $44

    // LoaD #$01 A
    // BRAnch to _a06b
    //  - showMenu(..)
    //  - Input: A
}

// Address: _a03b
// Menu Command $01
// Unstarted
static void collectItemsAfterBattle(void) {
    // LoaD #$0a to A
    // BRAnch to _a06b
    //  - showMenu(..)
    //  - Input: A
}

// Address: _a03f
// Menu Command $02
// Unstarted
static void shop(void) {
    // LoaD #$06 to A
    // BRAnch to _a06b
    //  - showMenu(..)
}

// Address: _a043
// Menu Command $03
// Unstarted
static void initMenuSettings(void) {
    // Jump to SubRoutine _a1f0
    func_c2a1f0();

    // Jump to SubRoutine _ff7d
    updateJoypadConfig();

    // Jump to SubRoutine _d447
    updateWindowColor();

    // Jump to SubRoutine _f5a9
    updateMonoStereoSetting();

    // LoaD #$0c to A
    // BRAnch to _a06b
    //  - showMenu(..)
}

// Address: _a053
// Menu Command $04
// Unstarted
static void tutorial(void) {
    // LoaD #$80 to A
    // TeSt A Bits for zero flags
    //  - Enable Tutorial Mode
    // STore Zero to $49 (clear pause counter)
    // STore Zero to $4a
    // Jump to SubRoutine _a394
    //  - init tutorial script

    // LoaD #$01 to A
    // BRAnch to _a06b
    //  - showMenu(..)
}

// Address: _a062
// Menu Command $06
// Unstarted
// Tramsfer Galuf's stats to Krile
static void galufToKrile(void) {
    // Store Zero to $35
    // Jump to SubRoutine _c2d958

    // BRAnch to _c2a030
    //  - This function only shortens A
}

// Address: _a069
// Menu Command $05
// Unstarted
// Returns: Immediate value #$0d
static void nameChange(void) {
    // Load #$0d to A
}

// Address: _a06b
// Unstarted
// Input: uint8_t (previously stored in A)
static void showMenu(void) {
    // Shorten A
    // Store A to $43 (Menu State)

    // Load #$7e to A
    // PusH A
    // PulL data Bank
    // Lengthen A

    // Jump to SubRoutine _c2c16a
    //  - func_c2c16a(..)
    // Jump to SubRoutine _c2a16e
    //  - resetSpriteData(..)

    // Load $43 (Menu State) to A
    // AND A with #$00ff
    // DECrement A
    // A Shift Left
    // Transfer A to X
    // Load ($c0e60e + X) to A
    //  - $c0e60e is within Shape Mask Section
    // STore A to $c7
    // Push (E) Relative addr [@a08f]-1
    // JuMP to ($01c7)
    //  - the address stored in $7e01c7

    // [@a08f] Lengthen A
    // Load $43 (Menu State) to A
    // AND A with #$00ff
    // CoMPare A with #$000c
    // Branch to [@a0a2] if Not Equal
    // LoaD $39 to A
    // Jump to _c2a030 if EQual
    //  - This function only shortens A

    // [@a0a2] Shorten A
    // LoaD #$00 to A
    // PusH A
    // PulL data Bank
    // STore Zero to $2121
    //  - The Address is for CGADD
    // Lengthen A
    // STore Zero to $2102
    //  - OAMADDL
    // STore Zero to $2116
    //  - VMADDL

    // LoaD #$f5b2 to X
    //  - 02 04 00 02 00 20 02 (sprite data)
    //  - Part of From Address, $c0f5b2
    // Jump to SubRoutine _c2a0f6
    //  - dma(..)

    // LoaD #$f5b9 to X
    //  - 02 22 00 73 7E 00 02 (color palettes)
    // Jump to SubRoutine _c2a0f6

    // LoaD #$f58b to X
    //  - 01 18 00 30 7E 00 40 (vram)
    // Jump to SubRoutine _c2a0f6

    // Shorten A
    // LoaD #$04 to A
    // STore A to $ca
    // LoaD #$00 to A
    // STore A to $7e7511
    
    // Jump to SubRoutine _c2a106
    //  - waitForVblank(..)
    // LoaD $7e750e to A
    // STore A to $420c

    // LoaD $4210 to A
    // LoaD #$81 to A
    // STore A to $4200

    // LoaD #$00 to A
    // STore A to $7e7522
    // STore A to $7e7525

    // LoaD A to #$03
    // STore A to $7e7513

    // JuMP to _c2a2e9
    //  - getNextInput(..)
}

// Address: _a0f6
// Direct Memory Access
// Unstarted
// +X: address of dma parameters (+$C00000)
static void dma(void) {
    // LoaD #$4300 to Y
    // LoaD #$0006 to A
    // MVN #$c0, #$00
    // LoaD #$0001 to 1
    // STore A to $420b
    // Return to Subroutine
}

// Address: _a106
// Unstarted
static void waitForVblank(void) {
    // PusH Processor status
    // Shorten A

    // [@a109] LoaD f:$004210 to A
    // Branch to [@a109] if MInus
    //  - negative flag is set
    // [@a10f] LoaD f:$004210 to A
    // Branch to [@a109] if PLus
    //  - negative flasg clear
    // [@a10f] LoaD f:$004210 to A

    // PulL Processor status
    // ReTurn to Subroutine
}

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
    //  - Here, $8e is also involved in func_c2a1cf(...)
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
    func_c2a18a();

    // Jump to subroutine _d230
    func_c2d230();

    // Jump to subroutine _d37b
    func_c2d37b();

    // Jump to subroutine _d3db
    func_c2d3db();

    // Jump to subroutine _a247
    func_c2a247();

    // Jump to subroutine _a1cf
    func_c2a1cf();

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
    //  - $17+1 bytes to copy
    //  - $18 bytes to copy
    //  - 24 bytes to copy
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
static void func_c2a18a(void) {
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
    //  - copy 6 bytes from #$c0f53b to #$002107

    // Load #$212c to Y
    // Load #$0005 to A
    // MVN #$c0, #$00
    //  - copy 6 bytes from #$c0f53b to #$00212c

    // PulL Processor status register
    // PulL data Bank register
    // Return from Subroutine
}

// TODO: Loop
static void func_c2a1cf(void) {
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
    //  - 5 bytes to copy
    // MVN #$c0, #$00
    // Branch to [LBL a1dc]
    
    // [LBL a1ed] PulL Processor status register
    // PulL data Bank register
    // Return from Subroutine
}

// Unstarted
static void func_c2a1f0(void) {}

// Unstarted
// This function seems to upload text.
static void func_c2a23b(void) {
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
static void func_c2a247(void) {
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
    //  - calls func_c2a23b(...)
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

// Address: _a2e9
// Unstarted
static void getNextInput(void) {
    // Shorten A
    // Lenghten Indexes
    
    // Jump to SubRoutine _c2e66f
    // Jump to SubRoutine _c2fc2f
    // PEA $7e7e
    // PulL data Bank
    // PulL data Bank
    // BIT test A with $45
    // Branch to [@a301] if MInus
    //  - if in tutorial mode
    // Jump to SubRoutine _c2a33a
    //  - getPressedBtnIdx(..)
    // BRAnch to [@a320]

    // [@a301] LoaD $49 to X
    //  - decrement pause counter
    // Branch to [@a30c] is MInus
    // DEcrement X
    // STore X to $49
    // LoaD $8e to A
    // BRAnch to [@a320]

    // [@a30c] LoaD $48 to A
    // Branch to [@a314] if Not Equal
    //  - branch if tutorial script pointer is valid
    // Load #$08 to A
    //  - exit menu
    // BRAnch to [@a320]

    // [@a314] LoaD [$46] (tutorial script) to A
    // LoaD $46 to X
    // INcrement X
    // STore X to $46
    // LoaD #$000f to X
    // STore X to $49

    // [@a320] STore $4b to A
    // BIT test with #$10
    // Branch to [@a328] if EQual
    //  - if not a pause
    // LoaD #$07 to A
    //  - pause command

    // [@a328] Lengthen A
    // AND A with #$000f
    // A Shift Left
    // Transfer A to X
    // Load ($c0e628 + X to A)
    // STore A to $c7
    // Shorten A
    // Jump to ($01c7)
}

// Address: _a33a
// Unstarted
static void getPressedBtnIdx(void) {
    // PusH Proccessor
    // Lengthen A
    // LoaD $8e to X

    // [@a33f] LoaD $0a to A (buttons pressed)
    // AND A with ($c0e7d2 + X) (button mask)
    // Branch to [@a34f] if Not Equals
    //  - if buttons are pressed
    // INcrement X by 3 (next button)
    // ComPare X with #$0012
    // Branch to [@a33f] if Not Equals

    // [@a34f] LoaD ($c0e7d4 + X) to A (button index)
    // AND A with #$00ff

    // PulL Processor
    // Return To Subroutine
}

// Address: _a358
// Pause (tutorial)
static void menuState14(void) {}

// Address: _a36a
// A button pressed
static void menuState0e(void) {}

// Address: _a378
// B button pressed
static void menuState0f(void) {}

// Address: _a394
static void initTutorialScript(void) {}

// Address: _a441
// Exit menu (tutorial)
static void menuState15(void) {}

// Address: _a45e
// Move cursor up
static void menuState10Up(void) {}

// Address: _a466
// Move cursor down
static void menuState10Down(void) {}

// Address: _a46e
// Move cursor left
static void menuState10Left(void) {}

// Address: _a476
// Move cursor right
static void menuState10Right(void) {}

// Address: _a4f0
// Name change
static void menuState0D(void) {}

static void func_c2a4f3(void) {}

static void func_c2a519(void) {}

static void func_c2a54a(void) {}

static void func_c2a55f(void) {}

static void func_c2a5b5(void) {}

static void func_c2a5e6(void) {}

static void func_c2a607(void) {}

static void func_c2a618(void) {}

static void func_c2a67a(void) {}

static void func_c2a693(void) {}

static void func_c2a6b9(void) {}

static void func_c2a6de(void) {}

static void func_c2a6fc(void) {}

static void func_c2a780(void) {}

static void func_c2a79c(void) {}

static void func_c2a7fc(void) {}

static void func_c2a81d(void) {}

static void func_c2a826(void) {}

static void func_c2a848(void) {}

static void func_c2a85a(void) {}

static void func_c2a878(void) {}

static void func_c2a892(void) {}

static void func_c2a8cb(void) {}

static void func_c2a8f0(void) {}

static void func_c2a8fa(void) {}

static void func_c2a91c(void) {}

static void func_c2a925(void) {}

static void func_c2a935(void) {}

static void func_c2a948(void) {}

static void func_c2a958(void) {}

static void func_c2a965(void) {}

static void func_c2a96c(void) {}

static void func_c2a96f(void) {}

static void func_c2a9d9(void) {}

static void func_c2a9fd(void) {}

static void func_c2aa12(void) {}

static void func_c2aa35(void) {}

static void func_c2aa4e(void) {}

static void func_c2aa6e(void) {}

static void func_c2aa89(void) {}

static void func_c2aabb(void) {}

static void func_c2aad1(void) {}

static void func_c2aae9(void) {}

static void func_c2ab19(void) {}

static void func_c2ab20(void) {}

static void func_c2ab36(void) {}

static void func_c2ab4c(void) {}

static void func_c2ab91(void) {}

static void func_c2aba0(void) {}

static void func_c2abb2(void) {}

static void func_c2abc1(void) {}

static void func_c2abd1(void) {}

static void func_c2abdb(void) {}

static void func_c2abdf(void) {}

static void func_c2abf2(void) {}

static void func_c2ac01(void) {}

static void func_c2ac0e(void) {}

static void func_c2ac1e(void) {}

static void func_c2ac5e(void) {}

static void func_c2ac90(void) {}

static void func_c2acc3(void) {}

static void func_c2acd6(void) {}

static void func_c2acff(void) {}

static void func_c2ad3e(void) {}

static void func_c2ad5b(void) {}

static void func_c2adb0(void) {}

static void func_c2adcc(void) {}

static void func_c2addf(void) {}

static void func_c2ae11(void) {}

static void func_c2ae31(void) {}

static void func_c2ae47(void) {}

static void func_c2ae4b(void) {}

static void func_c2ae5c(void) {}

static void func_c2ae6b(void) {}

static void func_c2ae6f(void) {}

static void func_c2af1b(void) {}

static void func_c2af87(void) {}

static void func_c2af91(void) {}

static void func_c2b04f(void) {}

static void func_c2b079(void) {}

static void func_c2b0d6(void) {}

static void func_c2b106(void) {}

static void func_c2b154(void) {}

static void func_c2b16e(void) {}

static void func_c2b19a(void) {}

static void func_c2b1ca(void) {}

static void func_c2b1ec(void) {}

static void func_c2b257(void) {}

static void func_c2b25b(void) {}

static void func_c2b25e(void) {}

// Unstarted
static void func_c2b2bd(void) {}

static void func_c2b2fb(void) {}

// Address: _b302
static void rowAButtonPressed(void) {}

static void func_c2b3db(void) {}

static void func_c2b3e9(void) {}

// Address: _b40c
static void rowBButtonPressed(void) {}

static void func_c2b429(void) {}

static void func_c2b480(void) {}

static void func_c2b48f(void) {}

static void func_c2b4a8(void) {}

static void func_c2b4d7(void) {}

static void func_c2b511(void) {}

static void func_c2b521(void) {}

static void func_c2b5ea(void) {}

static void func_c2b676(void) {}

static void func_c2b6b9(void) {}

static void func_c2b74b(void) {}

static void func_c2b752(void) {}

static void func_c2b796(void) {}

static void func_c2b7a0(void) {}

static void func_c2b7ad(void) {}

static void func_c2b7fc(void) {}

static void func_c2b811(void) {}

static void func_c2b845(void) {}

static void func_c2b84d(void) {}

static void func_c2b879(void) {}

static void func_c2b87c(void) {}

static void func_c2b8ae(void) {}

static void func_c2b91d(void) {}

static void func_c2b922(void) {}

static void func_c2b948(void) {}

static void func_c2b955(void) {}

static void func_c2b993(void) {}

static void func_c2b998(void) {}

static void func_c2ba05(void) {}

static void func_c2ba0a(void) {}

static void func_c2ba63(void) {}

static void func_c2ba7d(void) {}

static void func_c2bbfa(void) {}

static void func_c2bc27(void) {}

static void func_c2bc2a(void) {}

static void func_c2bc2d(void) {}

static void func_c2bc48(void) {}

static void func_c2bc5e(void) {}

static void func_c2bcd9(void) {}

static void func_c2bce0(void) {}

static void func_c2bd3d(void) {}

static void func_c2bd47(void) {}

static void func_c2bda5(void) {}

static void func_c2bdb5(void) {}

static void func_c2bdc6(void) {}

static void func_c2bdf3(void) {}

static void func_c2bdf6(void) {}

static void func_c2be2e(void) {}

static void func_c2be64(void) {}

static void func_c2bec8(void) {}

static void func_c2becd(void) {}

static void func_c2bef4(void) {}

// Address: _bef7
// Unstarted
static void saveToSlot(void) {
    // PusH Process status register
    // Lengthen A

    // INCrement value in $09c2
    // Jump to SubRoutine _c2bf7d
    //  - func_c2bf7d(..)
    //  - get pointer to save slot in sram
    // PusH X
    // Transfer A to Y
    // LoaD #$0500 to X
    // Load #$05ff to A ($600 bytes to copy)
    // PusH data Bank
    // PusH Y
    // MVN #$00, #$30
    //  - $00 is the bank mirrored from $7e RAM
    //  - $30 is the bank where SRAM is mapped

    // PulL Y
    // PulL data Bank
    // Store Y to $fc

    // Jump to SubRoutine _c2f588
    //  - func_c2f588(..)
    // PulL X
    // STore A to ($307ff0 + X)

    // LoaD #$e41b to A
    // STore A to ($307ff8 + X)

    // LoaD $6f to A
    // AND A with #$0003
    // STore A to $307fe0

    // Jump to SubRoutine _c2e0c8
    //  - func_c2e0c8(..)

    // PulL Process status register
    // Return To Subroutine
}

// Address: _bf2e
// Unstarted
static void loadFromSlot(void) {
    // Load $55 to A
    // CoMPare A with #$01
    // Jump to _c2bf89 if Not Equal
    //  - func_c2bf89(..)

    // Load $2d13 to A
    // Branch to [@bf47] if Not Equal

    // Jump to SubRoutine to _c2bef7
    //  - saveToSlot(..)

    // Jump to SubRoutine to _c2b2bd
    //  - func_c2b2bd(..)

    // Load #$0b to A
    // Jump to SubRoutine to _c2a06b
    //  - showMenu(..)
    //  - Input: A

    // [@bf47] Jump to SubRoutine _c2a1f0
    //  - func_c2a1f0(..)
    //  - init config settings

    // Load $094a to A
    // PusH A
    // PusH Process status register
    // Lengthen A

    // Jump to SubRoutine _c2bf7d
    //  - func_c2bf7d(..)
    //  - get pointer to save slot in sram
    // Transfer A to X
    // LoaD #$0500 to Y
    // LoaD #$05ff to A ($600 bytes to copy)
    // PusH data Bank
    // MVN #$30, #$00
    //  - load sram
    
    // PulL data Bank
    // PulL Processor
    // PulL A
    // CLear Carry flag

    // Add $0af9 to A
    //  - Update Random
    // STore A to $0af9

    // LoaD $6f to A
    // STore A to $62

    // Lengthen A
    // Load #$0001 to A
    // STore A to $39

    // Jump to SubRoutine _c2ff7d
    //  - updateJoypadConfig(..)
    // Jump to SubRoutine _c2f5a9
    //  - updateMonoStereoSetting(..)
    // Jump to SubRoutine CommonReturn
    //  - exit menu
}

// Unstarted
// Get Pointer to Save Slot in SRAM
static void func_c2bf7d(void) {
    // Load $6f to A
    // And A with #$0003 (save slot)
    // A Shift Left
    // Transfer A to X
    // Load ($c0f8ef + X) to A
    //  - Pointer to Save Slot in SRAM
    // Return To Subroutine
}

// Unstarted
static void func_c2bf89(void) {}

// Unstarted
static void func_c2c162(void) {
    // Load $5b to A
    // CLear Carry flag
    // ADd #$04 to A (with Carry)
    // JuMP to _c2a47c
}

// Unstarted
// TODO: MVN
static void func_c2c16a(void) {
    // PusH data Bank
    // LoaD $43 (menu state) to A
    // A aND with #$00ff
    // DECrement A
    // A Shift Left
    // Transfer A to X
    // LoaD ($c0f5e7 + X) to A
    // Transfer A to X
    // LoaD #$2bdc to Y
    // LoaD #$0017 to A (24 bytes to copy)
    // MVN #$c0, #$7e
    //  - To: $7e2bdc
    // LoaD $8e to X

    // [@c183] Load ($c0f5cf + X) to A
    //  - mvn destination address (+$7E0000)
    // STore A to $e6
    // PusH X
    // LoaD ($c0e7e7 + X) to A (jump address)
    // STore A to $c7
    // LoaD ($2bdc + X) to A (pointer to data)
    // PER [@c199] -1
    // JuMP to ($01c7)

    // [@c199] PulL X
    // INcrement X by 2
    // ComPare X with #$0018
    // Branch to [@c183] if Not Equal

    // PulL data Bank
    // Jump to SubRoutine _c2a18a
    //  - func_c2a18a(..)

    // Return To Subroutine
}

// Unstarted
static void func_c2d230(void) {
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
static void func_c2d25b(void) {
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
    //  - call func_c2d304(...)
    // Pull to A
    // CLear Carry flag
    // ADd #$000a to A
    // Transfer A to X
    // ComPare X with #$001e
    // Branch to [LBL d25d] if Not Equal
    
    // Jump to SubRoutine _c2d34c
    //  - call func_c2d34c(...)
    // Load #$b9a0 to X
    // Load #$9080 to Y
    // Load #$003f to A
    // MVN #$c3,#$7e
    // Return To Subroutine
}

// Q: What does DEC addr mean?
static void func_c2d304(void) {
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
static void func_c2d34c(void) {
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
static void func_c2d37b(void) {
    // PusH data Bank
    // PusH Processor status
    // Lengthen A

    // Load #$efe2 to X
    // Jump to SubRoute func_c2d9fb(...)

    // PulL Processor status
    // PulL data Bank
    // ReTurn to Subroutine
}

// TODO: Move sets to data
static void func_c2d3db(void) {
    // PusH data Bank
    // PusH Processor status
    // Lengthen A

    // STore Zero to $7e
    // [@d3e1] Jump to SubRoutine func_c2d45f(...)
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

    // Jump to SubRoutine func_c2d42e(..)
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
static void func_c2d45f(void) {
    // PusH data Bank
    // PusH Processor status
    // Shorten A

    // Jump to SubRoutine _c2d4c5
    //  - func_c2d4c5(..)
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
    //  - func_c2d492(..)
    // BRAnch to [@d48f]

    // [@d484] LoaD #$f807 to X
    //  - grayscale battle character palette ???
    // Lengthen A
    // Jump to SubRoutine _c2d4b4
    //  - func_c2d4b4(..)
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
static void func_c2d9fb(void) {
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

static void func_c2e0c8(void) {}

// Unstarted
static void func_c2f588(void) {}

// Address: _fe5b
// Unstarted
static void updateJoypadInput(void) {
    // PusH Processor status
    // Lengthen A
    // Push A
    // PusH Processor status
    // PusH X
    // PusH Y
    // PusH data Bank
    // PusH Direct page
    // Shorten A
    // Lengthen Indexes

    // Load #$00 to A
    // PusH A
    // PulL data Bank
    // Push Effective Address $0100
    // PulL Direct page
    // LoaD #$01 to A

    // [@fe72] BIT $4212
    // Branch to [@fe72] if Not Equal
    // LoaD #$0000 to Y
    // LoaD $4d to A
    // Branch to [@fe97] if EQual
    // LoaD $0974 to A
    // AND A with #$80
    // Branch to [@fe97] if EQual
    //  - If single controller
    // LoaD $010d to A
    // Lengthen A
    // AND A with #$0003
    // Transfer A to X
    // LoaD ($097c + X) to A
    //  - character assigned to controller
    // AND A with #$00ff
    // Branch to [@fe97] if EQual
    // INcrement Y

    // [@fe97] Lengthen A
    // STore Y to $12
    // Transfer Y to A
    // A Shift Left
    // Transfer A to X
    // Load ($4218 + X) to A
    // STore A to $06
    // AND A with #$000f
    // Branch to [@feaa] if EQual
    // STore Zero to $06

    // [@feaa] Load ($14 + X) to A
    // STore A to $0e
    // Jump to SubRoutine _c2fed0
    //  - func_c2fedo(..)
    // LoaD $12 to A
    // A Shift Left
    // Transfer A to X
    // LoaD $0e to A
    // STore A to ($14 + X)
    // PulL Direct page (it's the previous)
    // LoaD $010a to A
    // STore A to $00
    // LoaD $0108 to A
    // STore A to $02
    // LoaD $0106 to A
    // STore A to $04

    // PulL data Bank
    // PulL Y
    // PulL X
    // PulL Processor status
    // PulL A
    // PulL Processor status
    // ReTurn to Subroutine
}

static void func_c2fedo(void) {}

// Address: _ff56
// Unstarted
static void setControllerSettingsBattle(void) {
    // PusH Processor status
    // Lengthen A
    // Push A
    
    // Load #$0310 to A
    //  - Delay = 16 frames
    //  - Rate = 3 frames
    // Store A to f:$000118 (Repeat Settings)
    // Store A to f:$00014d (Allow Multiple Controllers)

    // PulL A
    // PulL Processor status
    // ReTurn to Subroutine
}

// Address: _ff68
// Unstarted
static void setControllerSettingsField(void) {
    // PusH Processor status
    // Lengthen A
    // Push A
    
    // Load #$0416 to A
    //  - Delay = 22 frames
    //  - Rate = 4 frames
    // Store A to f:$000118 (Repeat Settings)
    // Load #$0000 to A
    // Store A to f:$00014d (Single Controller)

    // PulL A
    // PulL Processor status
    // ReTurn to Subroutine
}

// Address: _ff7d
// Unstarted
void updateJoypadConfig(void) {
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
    // Jump SubRoutine to func_c2ffc2(...)
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
static void func_c2ffc2(void) {
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