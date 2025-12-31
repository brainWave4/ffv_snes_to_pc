#include <stdint.h>

// FUNCTION DECLARATIONS
static void setupRegisters(void);
static uint8_t getRandBetween(uint8_t min, uint8_t max);

// Address: $09c0
uint16_t battleCount = 0;

// FUNCTION DEFINITIONS

// Address: _0000, _0003
// Execute Battle
void execBattle(void) {
    // _0003:  php                      (Push Processor flags stack)
    //         longai                   (Lengthen Accumulator and XY Indexes to 16-bits)
    //         phb                      (Push data Bank register)
    //         phd                      (Push Direct page register)
    //         pha                      (Push Accumulator)
    //         phx                      (Push X Index)
    //         phy                      (Push Y Index)
    //         lda     #0               (load #0 onto Accumulator)
    //         shorta                   (Shorten Accumulator to 8-bits)
    //         longi                    (Set Indexes to 16-bits)
    //         jsr     SetupRegisters   (Call setUpRegisters())
    setupRegisters();

    //         longa                    (Set Accumulator to 16-bits)
    //         clc                      (Clear Carry Flag)
    //         lda     $09c0            (Load $09c0 into Accumulator; battle count)
    //         adc     #1               (Add #1 to Accumator; increment battle count)
    //         bcc     _0023            (Branch to _0023 is carry flag is clear)
    //         lda     #$ffff           (Load #$ffff to Accumulator)
    // _0023:  sta     $09c0            (Store accumulator to $09c0)
    if (battleCount < 0xffff) ++battleCount;

    //         shorta0                  (Set Accumulator to 8-bits)
    //         stz     $7cd8            (Store Zero to $7cd8)
    // _002c:  jsr     StartBattle      (Call startBattle())
    //         lda     #0               (load #0 onto Accumulator)
    //         sta     f:hINIDISP       (Store accumulator to f:hINIDISP)
    //         sta     f:hHDMAEN        (Store accumulator to f:hHDMAEN)
    //         sta     f:hMDMAEN        (Store accumulator to f:hHDMAEN)
    //         sta     f:hNMITIMEN      (Store accumulator to f:hNMITIMEN)
    //         lda     $7cd8            (Load $7cd8 to Accumulator)
    //         bne     _002c            (Branch to _002c if zero flag is not clear)
    //         sei                      (Set Interrupt Flag)
    //         jsr     SetupRegisters   (Call setUpRegisters())
    //         longai                   (Set Accumulator and XY Indexes to 16-bits)
    //         ply                      (Pull Y Index)
    //         plx                      (Pull X Index)
    //         pla                      (Pull Accumulator)
    //         pld                      (Pull Direct page register)
    //         plb                      (Pull data Bank register)
    //         plp                      (Pull Processor flags)
    //         rtl                      (Return to previously saved address, from subroutine Long)
}

// Address: _0053
static void setupRegisters(void) {
    // lda #0           (Load #0 onto Accumulator)
    // pha              (Push Accumulator)
    // plb              (Pull data Bank register)
    // sta hNMITIMEN    (Store Accumulator to hNMITIMEN)
    // ldx #$0000       (Load #$0000 onto X)
    // phx              (Push X)
    // pld              (Pull Direct Page Register)
    // lda #$80         (Load #$80 onto Accumulator)
    // sta hINIDISP     (Store Accumulator to hINIDISP)
    // lda #$7e         (Load #$7E onto Accumulator)
    // pha              (Push Accumulator)
    // plb              (Pull data Bank register)
    // rts              (Return to previously saved address, from subroutine)
}

// Address: _0069
// All this function does is to
// call another from another section.

// Address: _006E
// Calls Audio Section to changes Music
//  - Could've called it directly instead
//    with the given Music ID as a parameter.

// Address: _007C
// Generates a random number between 2 given numbers,
// Inclusive.
//  - C has rand(), but it must include <stdlib.h>
//  - Furthermore, rand() generates a fixed pattern
//  - TODO: Implement random table
// Input: Minimum Value, Maximum Value
// Output: Result
static uint8_t getRandBetween(uint8_t min, uint8_t max) {
// _007C:  shorti
//         stx $3c
//         cpx #$ff
//         bne :+
//         bra _Finish
// :       cmp #00
//         beq _Finish
//         cmp $3c
//         beq _Finish
//         pha
//         tdc
//         tax
//         lda RNGPointer
//         eor #01
//         sta RNGPointer
//         tax
//         lda $3a,X
//         tax
//         pla
//         sec
//         sbc $3c
//         cmp #$ff
//         bne :+
//         lda f:RNGTbl,X
//         bra _Finish
// :
//         inc
//         sta Divisor
//         stz Divisor+1
//         lda f:RNGTbl,X
//         tax
//         stx Dividend
//         longi
//         jsr Division
//         shorti
//         clc
//         lda Remainder
//         adc $3c
// _Finish:
//         pha
//         lda RNGPointer
//         tax
//         inc $3a,X
//         longi
//         pla
//         rts
    uint8_t diff = max - min;
    uint8_t randDiff = diff;
    
    //randDiff = rand() % diff;

    return min + randDiff;
}

// Address: _00D2, _00F1
// Multiplications for various bit sizes

// Address: _010C
// Division with both
// Quotient and Remainder for outputs
// There are no scanrios that requires both.

// Block of Hidden Message
// Not used in-game

// Address: _01B1, _01BA
// Multiplication and Division
// In Powers of 2
// Done by Shifting

// Address: _01C3
// Count number of set bits
// in 8-bit Accumulator (A),
// store in X

// Address: _01D1
// Uses a rom table to
// clear a single bit in A
// determined by X

// Address: _01D6
// Uses a rom table to
// set a single bit in A
// determined by X

// Address: _01DB
// Uses a rom table to
// select a single bit from A
// determined by X

// Address: _01E0
// Get next character's offset
// Primarily used to iterate through character structures

// Address: _01EC
// Calculate a character's offset
//  - Not actually used during attack type routines
//  - But it's used in other combat code

// Address: _01F8
// Offset into CharSpells struct for
// current character

// Address: _0207
// Get Timer Offset from ROM
// TODO: Investigate what Timer Offset represents.