#include <stdint.h>

// FUNCTION DECLARATIONS
static void setupRegisters(void);

// Address: $09c0
uint16_t battleCount = 0;

// FUNCTION DEFINITIONS

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