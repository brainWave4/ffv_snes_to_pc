#include <stdint.h>

// FUNCTION DECLARATIONS
static void setupRegisters(void);
static uint8_t getRandBetween(uint8_t min, uint8_t max);
static void wipeDisplayStructures(void);
static void copyStatsWithBonuses(void);
static void copyDisplayDamage(void);
static void wipeActionData(void);
static uint8_t getRandom0_99(void);
static uint16_t getTargetBitmask(void);
static void checkMultiTarget(void);
static void removeInactiveTargets(void);
static void copyRomMagicInfo(void);
static void nextMessageBoxSet(void);
static void getItemsUsableY(void);
static void setupInventoryInfo(void);
static void applyPercentage(void);

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

// Address: _0218
// Wipes structures related to:
//  - Pending Animations
//  - Message Boxes
//  - Damage Displays
static void wipeDisplayStructures(void) {
    // _0218:
    //         ldx #$0090
    // WipeAnimBlocks:		;wipes Anim structure and blocking information after it, $3BCC-$3C5B
    //         stz ActionAnim0::Flags,X
    //         dex
    //         bpl WipeAnimBlocks
    //         txa 		;A now $FF
    //         ldx #$037F
    // WipeGFXQueueDamage:	;wipes GFXQueue structure and DisplayDamage after it with $FF, $384C-$3BCB
    //         sta GFXQueue,X
    //         dex
    //         bpl WipeGFXQueueDamage
    //         ldx #$005F
    // WipeMessagesTimers:	;wipes Message Boxes and Timer structures after them with $FF, $3C5F-$3E8D
    //         sta MessageBoxes,X
    //         dex
    //         bpl WipeMessagesTimers
    //         tdc
    //         ldx #$000F
    // WipeReflectCounters:	;wipes $7B49-7B58
    //         stz CounterReflecteeTable,X
    //         dex
    //         bpl WipeReflectCounters
    //         ldx #$002F
    // WipeMessageBoxData:	;wipes numbers used for message boxes, $3CBF-$3CEE
    //         stz MessageBoxData,X
    //         dex
    //         bpl WipeMessageBoxData
    //         rts
}

// Address: _0248
// Recalculate Stats+Level
// with Song
//   - X: Character Offset
static void copyStatsWithBonuses(void) {
//         phx
//         phy
//         tdc
//         tay
// AddCopyStats:			;adds/copies Str/Agi/Vit/Mag
//         clc
//         lda CharStruct::EquippedStr,X
//         adc CharStruct::BonusStr,X
//         cmp #$64		;100
//         bcc :+
//         lda #$63   		;cap at 99
// :	sta Strength,Y
//         inx
//         iny
//         cpy #$0004
//         bne AddCopyStats
//         ply
//         plx
//         clc
//         lda CharStruct::Level,X
//         adc CharStruct::BonusLevel,X
//         cmp #$64		;100
//         bcc :+
//         lda #$63   		;cap at 99
// :	sta Level
//         rt
}

// Address: _0276
// Params:
//  - A = character index
//  - $3C5D (TempDisplayDamage) = displayed damage
static void copyDisplayDamage(void) {
    // tax
    // lda f:_d0ed79,X	;party members after monsters
    // asl
    // tax
    // lda TempDisplayDamage
    // sta DisplayDamage,X
    // lda TempDisplayDamage+1
    // sta DisplayDamage+1,X
    // rts
}

// Address: _028A
static void wipeActionData(void) {
//         stz a:wTargetIndex	;**optimize: wastes a byte
//         ldx #$0133
// :	   stz $79F9,X	        ;clears memory $79F9 - $7B2C
//         dex
//         bpl :-
//         txa 		            ;now $FF
//         ldx #$0010
// :	   sta $7B2D,X	        ;sets memory $7B2D - $7B3D to $FF
//         dex
//         bpl :-
//         tdc
//         rt
}

// Address: _02A2
// Returns an integor between
// 0 and 99, inclusive
static uint8_t getRandom0_99(void) {
    // tdc
    // tax
    // lda #$63
    // jmp Random_X_A
    return getRandBetween(0, 99);
}

// Address: _02A9
// Combines MonsterTargets and PartyTargets into
// Bitmask PPPPMMMM MMMM0000 to match
// normal index order
static uint16_t getTargetBitmask(void) {
    // lda MonsterTargets
    // pha
    // and #$F0
    // lsr
    // lsr
    // lsr
    // lsr
    // ora PartyTargets
    // sta TempTargetBitmask
    // pla
    // and #$0F
    // asl
    // asl
    // asl
    // asl
    // sta TempTargetBitmask+1
    // rts
    return 0;
}

// Address: _02C2
// Returns with number of targets minus 1 in
// A and $2620 (TempTargetting)
// Notably, 0 if single target
static void checkMultiTarget(void) {
    // lda MonsterTargets
    // ora PartyTargets
    // jsr CountSetBits
    // dex
    // txa
    // sta TempTargetting
    // rts
}

// Address: _02CF
static void removeInactiveTargets(void) {
//         stz NoValidTargets
//         tdc
//         tax
//         stx $0E
// Loop:
//         lda ActiveParticipants,X
//         beq Inactive
//         ldy $0E
//         lda CharStruct::Status1,Y
//         and #$C0	;dead/stone
//         bne Inactive
//         lda CharStruct::Status4,Y
//         and #$81	;erased/hiding
//         beq Next
// Inactive:
//         phx
//         cpx #$0004	;monster check
//         bcs Monster
//         lda PartyTargets
//         jsr ClearBit_X
//         sta PartyTargets
//         bra NextPLX
// Monster:
//         txa
//         sec
//         sbc #$04	;monster index
//         tax
//         lda MonsterTargets
//         jsr ClearBit_X
//         sta MonsterTargets
// NextPLX:
//         plx
// Next:
//         longa
//         clc
//         lda $0E
//         adc #$0080	;next CharStruct offset
//         sta $0E
//         shorta0
//         inx
//         cpx #$000C	;12 battle participants
//         bne Loop
//         lda PartyTargets
//         ora MonsterTargets
//         bne Ret
//         inc NoValidTargets
// Ret:	rts
}

// Address: _0324
// Copies magic data for spell in A from
// ROM to AttackInfo (offset Y)
static void copyRomMagicInfo(void) {
//         longa
//         jsr ShiftMultiply_8	;Size of Magic Data
//         tax
//         shorta0
//         stz $3D
// CopyFirst5:
//         lda f:AttackProp,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $3D
//         lda $3D
//         cmp #$05
//         bne CopyFirst5
//         iny 			;AttackInfo has 4 bytes that
//         iny 			;don't apply to magic
//         iny
//         iny
// CopyLast3:
//         lda f:AttackProp,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $3D
//         lda $3D
//         cmp #$08
//         bne CopyLast3
//         rts
}

// Address: _0356
// Advances the current message box offets to
// the next set of messgae boxes.
// For multi-commands like X-Magic/Dualcast
static void nextMessageBoxSet(void) {
    // clc
    // lda MessageBoxOffset
    // adc #$18		;+24, next message box set
    // sta MessageBoxOffset
    // clc
    // lda MessageBoxDataOffset
    // adc #$0C		;+12, next message box data set
    // sta MessageBoxDataOffset
    // rts
}

// Address: _0369
// (Y:index into in-battle inventory)
// (Returns A: bitmask depending on
// equipment type and some character properties)
//  - Format seems to be 2 bits per character,
//    00 for usable and 10 for not
static void getItemsUsableY(void) {
//         lda Temp,Y
//         bpl :+
//         lda #$AA		;usable for none
//         jmp Ret
// :	and #$40		;Consumable
//         beq Equipment
//         lda InventoryFlags,Y
//         and #$20
//         beq RetZero
//         lda #$AA		;usable for none
//         bra Ret
// RetZero:
//         lda #$00		;usable for all
//         bra Ret
// Equipment:		;**optimize: this whole section is basically a copy of the GetItemUsableA $455E subroutine
//         lda Temp,Y
//         asl
//         asl
//         tax
//         tdc
//         tay
//         									;:
// :	lda f:EquipTypeTbl,X
//         sta TempEquippable,Y
//         inx
//         iny
//         cpy #$0004
//         bne :-
//         									;.
//         tdc
//         tax
//         tay
//         lda #$AA
//         sta $0E
//         									;:
// DetermineEquippableLoop:
//         lda CharEquippable::Weapons,X
//         and TempEquippable::Weapons,Y
//         bne Match
//         lda CharEquippable::Weapons+1,X
//         and TempEquippable::Weapons+1,Y
//         bne Match
//         lda CharEquippable::Armor,X
//         and TempEquippable::Armor,Y
//         bne Match
//         lda CharEquippable::Armor+1,X
//         and TempEquippable::Armor+1,Y
//         beq NextChar
// Match:
//         txa
//         lsr
//         lsr
//         bne Check1
//         									;.
//         lda $0E
//         and #$7F		;clear first character bit
//         sta $0E
//         bra NextChar
// Check1:
//         cmp #$01
//         bne Check2
//         lda $0E
//         and #$DF		;clear second character bit
//         sta $0E
//         bra NextChar
// Check2:
//         cmp #$02
//         bne Other
//         lda $0E
//         and #$F7         	;clear third character bit
//         sta $0E
//         bra NextChar
// Other:
//         lda $0E
//         and #$FD		;clear fourth character bit
//         sta $0E
// NextChar:
//         inx
//         inx
//         inx
//         inx
//         cpx #$0010			;4 bytes * 4 characters
//         bne DetermineEquippableLoop
//         lda $0E
// Ret:	rts
}

// Address: _03FA
// (sets up equipment type, targetting, and
// usable bytes for one item in battle inventory)
// (A: item#)
// (Y: inventory offset to write data about item)
// Returns with EquipmentType low bytes in Temp ($2620),
// $40 there if it's a consumable, $80 if unusable
// TODO: find a better way to access into the
// D1 item data because I didnt know how the translation
// from asar to ca65 would work
static void setupInventoryInfo(void) {
//         beq ItemZero
//         cmp #$E0
//         bcs Consumable		;>$E0 is consumable
//         cmp #$80
//         bcc Weapon		;<$80 is a weapon
// Armor:				;otherwise it's armor
//         sec
//         sbc #$80		;remove the armor offset
//         longa
//         asl
//         asl
//         sta $0E
//         asl
//         clc
//         adc $0E			;armor *12 (size of equipment struct)
//         tax
//         shorta0
//         lda f:ArmorProp,X
//         and #$08		;target enemy?
//         beq ItemZero
//         lda f:ArmorProp+2,X
//         and #$3F		;mask to equip info
//         sta Temp,Y
//         lda #$5A
//         sta InventoryFlags,Y
//         bra Ret
// ItemZero:	;or armor targettng bit 08h
//         lda #$80		;not usable
//         sta Temp,Y
//         lda #$5A
//         sta InventoryFlags,Y
//         bra Ret
// Weapon:
//         longa
//         asl
//         asl
//         sta $0E
//         asl
//         clc
//         adc $0E         	;weapon *12
//         tax
//         shorta0
//         lda f:WeaponProp+4,X
//         and #$80
//         jsr ShiftDivide_32	;shift to 04h bit
//         sta InventoryFlags,Y
//         lda f:WeaponProp,X
//         sta InventoryTargetting,Y
//         lda f:WeaponProp+2,X
//         pha
//         and #$C0		;flag bits from equipment type(? and throwable)
//         ora #$1A		;set some more bits (??)
//         ora InventoryFlags,Y	;keep existing bits (double grip)
//         sta InventoryFlags,Y
//         pla
//         and #$3F		;mask to just equip info
//         sta Temp,Y
//         bra Ret
// Consumable:
//         sec
//         sbc #$E0
//         longa
//         asl
//         asl
//         asl
//         tax
//         shorta0
//         lda f:ConsumableItemProp,X
//         sta InventoryTargetting,Y
//         lda f:ConsumableItemProp+2,X
//         sta InventoryFlags,Y
//         lda #$40		;consumable
//         sta Temp,Y
// Ret: 	rts
}

// Address: _0491
// Utility routine used for the +% HP/MP passives on level up
// Inputs:
//  - $2E: 4 byte multiply result (value * percentage)
//  - $08: 2 byte base value
//  - $0A: 2 byte cap (generally 999 or 9999)
// Output:
//  - $08: 2 byte value (value*percentage/100)+Base, capped
static void applyPercentage(void) {
//         ldx #$000F
// :	    stz $0E,X		;clear $0E-1D
//         dex
//         bpl :-
//         ldx #$0064		;100
//         stx $12
//         ldx $2E			;previous multiply result (low bytes)
//         stx $0E
//         lda $30			;(high bytes)
//         sta $10
// ;32 bit division routine
// ;Dividend: 	$0E-11
// ;Divisor: 	$12-15
// ;Quotient: 	$16-19
// ;Remainder: 	$1A-1C
// ;**optimize: make this a general purpose subroutine, duplicate at $57FE
//         longa
//         clc
//         ldx #$0020
// :	rol $0E
//         rol $10
//         rol $1A
//         rol $1C
//         sec
//         lda $1A
//         sbc $12
//         sta $1A
//         lda $1C
//         sbc $14
//         sta $1C
//         bcs :+
//         lda $1A
//         adc $12
//         sta $1A
//         lda $1C
//         adc $14
//         sta $1C
//         clc
// :	rol $16
//         rol $18
//         dex
//         bne :--
//         shorta0
// ;division ends here
//         clc
//         lda $16		;quotient, input/100
//         adc $08		;base value
//         sta $08		;adjusted value
//         lda $17		;high byte of above
//         adc $09
//         sta $09
//         sec 		;checks against 9999
//         lda $08
//         sbc $0A		;9999 low byte
//         lda $09
//         sbc $0B		;9999 high byte
//         bcc Ret
//         lda $0A		;caps at 9999
//         sta $08
//         lda $0B
//         sta $09
// Ret:	rts
}