#include <stdint.h>

//#include "btlgfx.h"
//#include "sound.h"

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
static void noActionAbility(void);
static void commandTable00(void);
static void itemCommand(void);
static void weaponItem(void);
static void prepMagicLamp(void);
static void commandTable02(void);
static void commandTable03(void);
static void commandTable05(void);
static void commandTable06(void);
static void commandTable07(void);
static void simpleFight(void);
static void commandTable08(void);
static void commandTable09(void);
static void commandTable0A(void);
static void commandTable0B(void);
static void commandTable0C(void);
static void commandTable2D(void);
static void commandTable2E(void);
static void commandTable0D(void);
static void commandTable0E(void);
static void commandTable0F(void);
static void commandTable10(void);
static void swordSlapCommand(void);
static void commandTable12(void);
static void commandTable13(void);
static void commandTable14(void);
static void commandTable15(void);
static void commandTable16(void);
static void commandTable18(void);
static void commandTable19(void);
static void commandTable17(void);
static void commandTable1A(void);
static void commandTable1B(void);
static void commandTable1C(void);
static void commandTable1D(void);
static void commandTable1E(void);
static void commandTable20(void);
static void commandTable21(void);
static void commandTable22(void);
static void commandTable24(void);
static void commandTable25(void);
static void commandTable28(void);
static void commandTable29(void);
static void commandTable2A(void);
static void commandTable2F(void);
static void commandTable30(void);
static void commandTable31(void);
static void commandTable32(void);
static void commandTable33(void);
static void commandTable34(void);

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

// Notes about Commands in Asm
//  - Most of FF5 uses a command value between $01-$56,
//    which matches the slots on the combat menu.
//  - This is then mapped to command table values $00-$34
//    via a rom table.
//  - Most of the time the difference is just -1, but
//    all magic types map to $2B.
//  - Everything after $2B shifts down accordingly

// Address: _04FB
// Used by Defend and Guard
static void noActionAbility(void) {
    // jsr GFXCmdAbilityAnim
    // lda ProcSequence
    // tax
    // stz AtkType,X
    // stz MultiTarget,X
    // stz TargetType,X
    // inc UnknownReaction
    // jmp FinishCommandNullTargets
}

// Address: _0511
// For commands $01 (Other) and $24 (Dummy01)
static void commandTable00(void) {
// CommandTable23:
//         lda AttackerIndex
//         cmp #$04		;monster check
//         bcc Party
// Monster:
//         sec
//         sbc #$04		;now monster index
//         asl
//         tax
//         lda f:_d0ee95,X	;*100
//         sta $0E
//         lda f:_d0ee95+1,X
//         sta $0F
//         tdc
//         tay
//         ldx $0E
// CopyGFXQueue:		;copy 100 bytes from monster ai to GFXQueue
//         lda MonsterAIScript,X
//         sta GFXQueue,Y
//         inx
//         iny
//         cpy #$0064
//         bne CopyGFXQueue
//         bra Continue
// Party:
//         jsr FindOpenGFXQueueSlot   ;next slot in X
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Cmd,X
//         stz GFXQueue::Type,X
//         stz GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
// Continue:
//         lda ProcSequence
//         tax
//         lda #$7E
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         inc UnknownReaction
//         lda ProcSequence
//         asl
//         tax
//         lda #$80		;first party member
//         sta CommandTargetBitmask,X
//         stz CommandTargetBitmask+1,X
//         inc ProcSequence
//         rts
}

// Address: _0570
// For commands $02 (Item) and $20 (Drink)
static void itemCommand(void) {
// CommandTable01:
// CommandTable1F:
//         stz SelectedItem
//         jsr SelectCurrentProcSequence	;$0C = ProcSequence*12
//         jsr GetTargets
//         ldx AttackerOffset
//         lda CharStruct::ActionFlag,X
//         and #$10	;weapon used as item
//         beq :+
//         jmp WeaponItem
// :       lda CharStruct::SelectedItem,X
//         cmp #$EF	;magic lamp
//         bne ConsumableItem
//         jsr PrepMagicLamp
//         jmp ConjureMagicLamp	;finishes up in Conjure routine
// ConsumableItem:
//         sta TempSpell
//         sec
//         sbc #$E0	;now consumable item index
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         ldy $0C		;ProcSequence*12
//         stz $0A
// :       lda f:ConsumableItemProp,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//         cmp #$05      	;copy 5 bytes
//         bne :-
//         iny           	;skip 4 in Attackinfo
//         iny
//         iny
//         iny
// :	lda f:ConsumableItemProp,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//         cmp #$08      	;copy remaining 3 bytes
//         bne :-
//         jsr CheckMultiTarget
//         bne TargetOK
//         ldy $0C		;ProcSequence*12
//         lda AttackInfo::MagicAtkType,Y
//         bpl _CheckRetarget
//         lda ProcSequence
//         tax
//         inc HitsInactive,X	;can hit dead targets
//         bra TargetOK
// _CheckRetarget:
//         jsr CheckRetarget
// TargetOK:
//         jsr BuildTargetBitmask
//         lda TempSpell
//         sta Temp+1
//         lda #$04
//         sta Temp
//         jsr GFXCmdAttackNameFromTemp
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$09		;command 9: item use
//         sta GFXQueue::Type,X
//         lda TempSpell
//         sta GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         ldy $0C		;ProcSequence*12
//         lda ProcSequence
//         tax
//         lda AttackInfo::MagicAtkType,Y
//         and #$7F
//         sta AtkType,X
//         lda TempTargetting
//         sta MultiTarget,X
//         beq Single
//         inc MultiTarget,X	;now proper number of targets if >1
//         lda #$80
// Single:	sta TargetType,X
//         jsr FinishCommand
//         jsr GFXCmdDamageNumbers
//         rts
}

// Addres: _0632
static void weaponItem(void) {
// stz TempHand
//         lda AttackerIndex
//         tax
//         lda f:_d0ed85,X	;size of one character's gear offset
//         tay
//         ldx AttackerOffset
//         lda CharStruct::SelectedItem,X
//         bne Left
//         lda CharStruct::RHWeapon,X
//         sta CharStruct::SelectedItem,X
//         sta SelectedItem
//         tax
//         lda RHWeapon::ItemMagic,Y
//         bra ItemReady
// Left:       inc TempHand
//         lda CharStruct::LHWeapon,X
//         sta CharStruct::SelectedItem,X
//         sta SelectedItem
//         tax
//         lda LHWeapon::ItemMagic,Y
// ItemReady:
//         sta TempItemMagic
//         and #$7F
//         txy 		;Y is now selected item
//         pha
//         pha
//         lda ProcSequence
//         tax
//         pla
//         sta AtkType,X
//         tya
//         sta Temp+1	;selected item
//         lda #$04
//         sta Temp
//         jsr GFXCmdAttackNameFromTemp
//         lda ProcSequence
//         tax
//         lda AtkType,X
//         ldy $0C		;ProcSequence*12
//         jsr CopyROMMagicInfo
//         jsr CheckMultiTarget
//         bne TargetOK
//         ldy $0C
//         lda AttackInfo::MagicAtkType,Y
//         bpl DontRetarget
//         lda ProcSequence
//         tax
//         inc HitsInactive,X
//         bra TargetOK
// DontRetarget:
//         jsr CheckRetarget
// TargetOK:
//         jsr BuildTargetBitmask
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC	;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$0A	;command 10: weapon used as item
//         sta GFXQueue::Type,X
//         pla
//         sta GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         lda ProcSequence
//         tax
//         lda AtkType,X
//         bpl :+
//         tdc
//         bra :++
// :	ldy $0C
//         lda AttackInfo::MagicAtkType,Y
//         and #$7F
// :	sta AtkType,X
//         lda TempTargetting
//         sta MultiTarget,X
//         beq :+
//         inc MultiTarget,X
//         lda #$80
// :	sta TargetType,X
//         jsr FinishCommand
//         jsr GFXCmdDamageNumbers
//         lda TempItemMagic
//         bpl Ret
// BreakOnUse:	;80h indicates item should now break
//         lda AttackerIndex
//         jsr ShiftMultiply_4
//         sta $0E
//         asl
//         clc
//         adc $0E
//         tay 		;Attacker index *12
//         lda TempHand
//         bne Left2
//         tdc
//         sta HandItems::ID,Y
//         sta HandItems::Level,Y
//         sta HandItems::MP,Y
//         lda #$38
//         sta HandItems::Targetting,Y
//         lda #$5A
//         sta HandItems::Flags,Y
//         lda #$AA
//         sta HandItems::Usable,Y
//         bra DoneHandItems
// Left2:	tdc
//         sta HandItems::ID+1,Y
//         sta HandItems::Level+1,Y
//         sta HandItems::MP+1,Y
//         lda #$38
//         sta HandItems::Targetting+1,Y
//         lda #$5A
//         sta HandItems::Flags+1,Y
//         lda #$AA
//         sta HandItems::Usable+1,Y
// DoneHandItems:
//         lda MessageBoxOffset
//         tay
//         lda #$50	;item shattered message
//         sta MessageBoxes,Y
//         lda MessageBoxOffset
//         sta $0E
//         asl
//         clc
//         adc $0E
//         tax 		;message box index *3
//         lda SelectedItem
//         sta MessageBoxData,X
//         stz MessageBoxData+1,X
//         stz MessageBoxData+2,X
//         jsr GFXCmdMessage
//         lda DisplayInfo::CurrentChar
//         pha
//         lda AttackerIndex
//         sta DisplayInfo::CurrentChar
//         sta CurrentChar
//         jsr ReplaceHands
//         pla
//         sta DisplayInfo::CurrentChar
//         jsr ApplyGear
// Ret:	rts
}

// Address: _0767
static void prepMagicLamp(void) {
// lda BattleData::MagicLamp
//         cmp #$0D	;<13, normal
//         bcc Continue
//         cmp #$20	;>=32, egg chop
//         bcs EggChop
//         lda #$0D	;chocobo
//         bra Continue
// EggChop:
//         lda #$0E	;egg chop
// Continue:
//         tax
//         lda f:_d0eee7,X
//         sta TempSpell
//         stz TempIsEffect
//         clc
//         lda BattleData::MagicLamp
//         adc #$01
//         bcc :+
//         lda #$FF	;cap at 255 uses
// :	sta BattleData::MagicLamp
//         rts
}

// Address: _0791
// For command $03 (Row)
static void commandTable02(void) {
        // lda #$03	;row ability
        // jsr CopyAbilityInfo
        // inc UnknownReaction
        // lda #$02
        // jsr GFXCmdAbilityAnim
        // jsr MagicAtkTypeSingleTarget
        // jmp FinishCommandNullTargets
}

// Address: _07A4
// Command $04 (Defend)
// Could've called noActionAbility(...) directly,
// but that depends whether the loaded
// could be parsed as an arguement.
static void commandTable03(void) {
        // lda #$03
        // jmp NoActionAbility
}

// Address: _07A9
// Command $06 (Guard)
// Same predicament as the above function.
static void commandTable05(void) {
        // lda #$05
        // jmp NoActionAbility
}

// Address: _07AE
// Command $07 (Kick)
static void commandTable06(void) {
        // lda #$07	;kick ability
        // jsr CopyAbilityInfo
        // jsr GetTargets
        // jsr BuildTargetBitmask
        // jsr CheckMultiTarget
        // lda #$07	;kick ability name
        // jsr GFXCmdAttackNameA
        // lda #$06	;kick anim
        // jsr GFXCmdAbilityAnim
        // jsr MagicAtkTypeMultiTarget
        // jsr FinishCommand
        // jmp GFXCmdDamageNumbers
}

// Address: _07CF
// Command $08 (BuildUp/Focus)
static void commandTable07(void) {
        // lda #$08	;ability name
        // jsr GFXCmdAttackNameA
        // lda #$07	;ability anim
        // jsr GFXCmdAbilityAnim
        // lda ProcSequence
        // tax
        // stz AtkType,X
        // stz MultiTarget,X
        // stz TargetType,X
        // jsr FinishCommandNullTargets
        // ldx AttackerOffset
        // lda #$4E	;Command, maps to CommandTable2C/SimpleFight
        // sta CharStruct::Command,X
        // lda #$10	;double M
        // sta CharStruct::DamageMod,X
        // lda #$4E
        // tax
        // lda f:BattleCmdDelay,X
        // pha
        // lda AttackerIndex
        // jsr GetTimerOffset
        // ldx AttackerOffset
        // pla
        // jsr HasteSlowMod
        // sta CurrentTimer::ATB,Y
        // lda #$41	;waiting for delayed action
        // sta EnableTimer::ATB,Y
        // inc DelayedFight
        // rts
}

// Address: _0814
// Command $4E (Simple Fight)
// No procs, used by Capture/BuildUp/etc.
static void simpleFight(void) {
//         jsr GetTargets
//         jsr CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//         sta CharStruct::PartyTargets,X
//         lda MonsterTargets
//         sta CharStruct::MonsterTargets,X
//         jsr BuildTargetBitmask
//         lda AttackerIndex
//         tax
//         lda f:_d0ed85,X	;size of combined gear stats struct
//         tax
//         stx $0E			;gear stats offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         jmp LH
// RH:
//         jsr SelectCurrentProcSequence
//         sty $14			;AttackInfo Offset
//         stz $12			;loop index
//         ldx $0E			;gear stats offset
// :	lda RHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//         cmp #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda RHWeapon::Properties,X
//         and #$04		;magic sword ok
//         bne __MSword
//         tdc
//         bra __DoneMSword
// __MSword:
//         ldx AttackerOffset
//         lda CharStruct::MSwordAnim,X
//         and #$7F		;clear high bit for right hand
// __DoneMSword:
//         pha
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$01		;ability/command animation
//         sta GFXQueue::Type,X
//         lda #$04		;fight
//         sta GFXQueue::Data1,X
//         pla 			;magic sword anim
//         sta GFXQueue::Data2,X
//         ldx $0E
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//         tax
//         pla
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         jsr FinishCommand
//         jsr GFXCmdDamageNumbers
// LH:
//         ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//         rts 			;no weapons (not even fists)
// :	jsr SelectCurrentProcSequence
//         sty $12			;AttackInfo Offset
//         stz $14			;loop index
//         ldx $0E			;gear stats offset
// :	lda LHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//         cmp #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda ProcSequence
//         tay
//         lda LHWeapon::AtkType,X
//         sta AtkType,Y
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$01		;ability/command animation
//         sta GFXQueue::Type,X
//         lda #$04		;fight
//         sta GFXQueue::Data1,X
//         stx $08			;GFXQueue offset
//         ldx $0E			;gear stats offset
//         lda LHWeapon::Properties,X
//         and #$04		;magic sword ok
//         bne __MSword2
//         lda #$80		;left hand
//         bra __DoneMSword2
// __MSword2:
//         ldx AttackerOffset
//         lda CharStruct::MSwordAnim,X
//         ora #$80		;left hand
// __DoneMSword2:
//         ldx $08			;GFXQueue offset
//         sta GFXQueue::Data2,X	;magic sword anim
//         lda ProcSequence
//         tax
//         stz MultiTarget,X
//         stz TargetType,X
//         jsr FinishCommand
//         jsr GFXCmdDamageNumbers
//         rts
}

// Address: _090B
// Command $09 (Mantra, or Chakra in GBA)
static void commandTable08(void) {
    // lda #$09	;mantra ability
    // jsr CopyAbilityInfo
    // lda #$09	;ability name
    // jsr GFXCmdAttackNameA
    // lda #$08	;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommandNullTargets
    // lda ProcSequence	;a second effect?
    // tax
    // stz AtkType,X		;no attack type
    // stz MultiTarget,X
    // stz TargetType,X
    // jsr FinishCommandNullTargets
    // jmp GFXCmdDamageNumbers
}

// Address: _0933
// Command $0A (Escape/Flee)
static void commandTable09(void) {
    // lda #$0A	;escape ability
    // jsr CopyAbilityInfo
    // inc UnknownReaction
    // lda #$0A	;ability name
    // jsr GFXCmdAttackNameA
    // lda #$09	;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommandNullTargets
    // jmp GFXCmdMessage
}

// Address: _094E
// Command $0B (Steal)
static void commandTable0A(void) {
    // lda #$0B	;steal ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr CheckRetarget
    // jsr BuildTargetBitmask
    // lda #$0B	;name
    // jsr GFXCmdAttackNameA
    // lda #$0A	;anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommand
    // jmp GFXCmdMessage
}

// Adddress: _096F
// Command $0C (Capture/Mug)
static void commandTable0B(void) {
    // stz ProcSequence	;overwriting entire sequence
    // stz NextGFXQueueSlot
    // lda #$0C		;ability name
    // jsr GFXCmdAttackNameA
    // jsr SimpleFight
    // lda #$0B		;steal ability
    // jsr CopyAbilityInfo
    // lda #$0A		;steal anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommand
    // jmp GFXCmdMessage
}

// Address: _0990
// Command $0D (Jump)
static void commandTable0C(void) {
// JumpCommand:
//          lda #$0D	;jump ability name
//          jsr GFXCmdAttackNameA
// Anim:			;routine is called here by command $52
//          lda #$0C	;jump ability anim (launch)
//          jsr GFXCmdAbilityAnim
//          lda ProcSequence
//          tax
//          stz AtkType,X
//          stz MultiTarget,X
//          stz TargetType,X
//          jsr FinishCommandNullTargets
//          inc UnknownReaction
//          ldx AttackerOffset
//          lda #$4F	;jump landing command, maps to CommandTable2D
//          sta CharStruct::Command,X
//          lda #$10	;jumping
//          sta CharStruct::CmdStatus,X
//          lda #$80	;auto hit
//          sta CharStruct::DamageMod,X
//          lda #$4F	;jump landing command
//          tax
//          lda f:BattleCmdDelay,X
//          pha
//          lda AttackerIndex
//          jsr GetTimerOffset
//          ldx AttackerOffset
//          pla
//          jsr HasteSlowMod
//          sta CurrentTimer::ATB,Y
//          lda #$41	;queued action
//          sta EnableTimer::ATB,Y
//          inc DelayedFight
//          rts
}

// Address: _09DD
// Command $4F (landing from Jump)
static void commandTable2D(void) {
//         lda #$2D	;jump landing anim
//         jsr GFXCmdAbilityAnim
//         jsr GetTargets
//         jsr CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//         sta CharStruct::PartyTargets,X
//         lda MonsterTargets
//         sta CharStruct::MonsterTargets,X
//         jsr BuildTargetBitmask
//         lda AttackerIndex
//         tax
//         lda f:_d0ed85,X	;size of combined gearstats struct
//         tax
//         stx $0E			;gear stats offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         jmp LH
// RH:	   jsr SelectCurrentProcSequence
//         stz $12
//         ldx $0E
// :	   lda RHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//         cmp #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//         tax
//         pla
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         jsr FinishCommand
//         jsr GFXCmdDamageNumbers
// LH:     ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//         jmp Finish
// :	   jsr SelectCurrentProcSequence
//         stz $12
//         ldx $0E			;gear stats offset
// :       lda LHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//         cmp #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda ProcSequence
//         tay
//         lda LHWeapon::AtkType,X
//         sta AtkType,Y
//         lda ProcSequence
//         tax
//         stz MultiTarget,X
//         stz TargetType,X
//         jsr FinishCommand
//         jsr GFXCmdDamageNumbers
// Finish:       inc UnknownReaction
//         rts
}

// Address: _0A7D
// Command $50 (forced Jump landing, via Interceptor Rocket)
static void commandTable2E(void) {
        // lda #$50		;jump intercepted
        // jsr CopyAbilityInfo
        // jsr GetTargets
        // jsr CheckRetarget
        // stz MonsterTargets
        // lda AttackerIndex
        // tax
        // tdc
        // jsr SetBit_X
        // sta PartyTargets	;target self
        // jsr BuildTargetBitmask
        // inc UnknownReaction
        // lda #$2E		;jump intercepted anim
        // jsr GFXCmdAbilityAnim
        // jsr MagicAtkTypeSingleTarget
        // jmp FinishCommand
}

// Address: _0AA4
// Command $0E (Dragon Sword/Lance)
static void commandTable0D(void) {
        // jsr GetTargets
        // jsr CheckRetarget
        // jsr BuildTargetBitmask
        // jsr CheckMultiTarget
        // lda #$0E		;ability name
        // jsr GFXCmdAttackNameA
        // lda #$0D		;ability anim
        // jsr GFXCmdAbilityAnim
        // jsr SelectCurrentProcSequence
        // lda #$71		;dragon sword hp drain
        // jsr CopyROMMagicInfo
        // jsr MagicAtkTypeSingleTarget
        // jsr FinishCommand
        // jsr GFXCmdDamageNumbers
        // jsr SelectCurrentProcSequence
        // lda #$72		;dragon sword mp drain
        // jsr CopyROMMagicInfo
        // jsr MagicAtkTypeSingleTarget
        // jsr FinishCommand
        // jmp GFXCmdDamageNumbers
}

// Address: _0ADC
// Command $0F (Smoke)
static void commandTable0E(void) {
    // lda #$0F		;smoke ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr BuildTargetBitmask
    // jsr CheckMultiTarget
    // lda #$0F		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$0E		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeMultiTarget
    // jmp FinishCommand
}

// Address: _0AFA
// Command $10 (Image)
static void commandTable0F(void){
    // lda #$10		;image ability
    // jsr CopyAbilityInfo
    // lda #$10		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$0F		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jmp FinishCommandNullTargets
}

// Address: _0B0F
// Command $11 (Throw)
//   ** optimize: use SandwormBattle instead of
//      checking encounter
static void commandTable10(void) {
//         ldx AttackerOffset
//         lda CharStruct::SelectedItem,X
//         bpl Weapon		;otherwise, a scroll
//         tdc
//         tax
//         stz $0E			;target bits
// TargetActiveMonsters:
//         lda ActiveParticipants+4,X
//         beq Next
//         lda $0E
//         jsr SetBit_X  		;add as target if active
//         sta $0E
// Next:	inx
//         cpx #$0008		;8 monsters
//         bne TargetActiveMonsters
//         ldx AttackerOffset
//         lda $0E			;target bits
//         sta CharStruct::MonsterTargets,X
//         lda EncounterIndex+1
//         beq ItemFlag
//         lda EncounterIndex
//         cmp #$BF		;sandworm fight
//         bne ItemFlag
//         lda $0E
//         and #$FC		;exclude "real" sandworm
//         sta CharStruct::MonsterTargets,X
// ItemFlag:
//         lda #$40		;item
//         sta CharStruct::ActionFlag,X
//         jmp ItemCommand
// Weapon:
//         lda #$11		;throw ability
//         jsr CopyAbilityInfo
//         jsr GetTargets
//         jsr CheckRetarget
//         jsr BuildTargetBitmask
//         lda #$11		;ability name
//         jsr GFXCmdAttackNameA
//         lda #$10		;ability anim
//         jsr GFXCmdAbilityAnim
//         jsr MagicAtkTypeSingleTarget
//         jsr FinishCommand
//         jmp GFXCmdDamageNumbers
}

// Address: _0B6F
// Command $12 (Sword Slap / Mineuchi)
// sets a variable which is never checked then
// issues a regular fight command
static void swordSlapCommand(void) {
    // lda #$12		;ability name
    // jsr GFXCmdAttackNameA
    // inc SwordSlap		;not checked anywhere
    // jmp FightCommand
}

// Address: _0B7A
// Command $13 (Gil Toss)
static void commandTable12(void) {
    // lda #$13		;gil toss ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr BuildTargetBitmask
    // jsr CheckMultiTarget
    // lda #$13		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$12		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeMultiTarget
    // jsr FinishCommand
    // jmp GFXCmdDamageNumbers
}

// Address: _0B9B
// Command $14 (Slash / Samurai's Iainuki)
static void commandTable13(void) {
    // lda #$14	;slash ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr BuildTargetBitmask
    // jsr CheckMultiTarget
    // inc UnknownReaction
    // lda #$14	;ability name
    // jsr GFXCmdAttackNameA
    // lda #$13	;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeMultiTarget
    // jsr FinishCommand
    // jmp GFXCmdDamageNumbers
}

// Address: _0BBF
// Command $15 (Animals)
//  ** optimize: rewrite to remove repeated bra's
static void commandTable14(void) {
//         tdc
//         tax
//         lda Level
//         jsr Random_X_A		;0..Level
//         bne :+
//         tdc 		;0 mystidian rabbit
//         bra Chosen
// :       cmp #$05
//         bcs :+
//         lda #$01	;<5 squirrel
//         bra Chosen
// :       cmp #$0A
//         bcs :+
//         lda #$02	;<10 bee swarm
//         bra Chosen
// :       cmp #$14
//         bcs :+
//         lda #$03	;<20 nightingale
//         bra Chosen
// :       cmp #$1E
//         bcs :+
//         lda #$04	;<30 momonga
//         bra Chosen
// :       cmp #$28
//         bcs :+
//         lda #$05	;<40 falcon
//         bra Chosen
// :       cmp #$32
//         bcs :+
//         lda #$06	;<50 skunk
//         bra Chosen
// :       cmp #$3C
//         bcs :+
//         lda #$07	;<60 wild boar
//         bra Chosen
// :	lda #$08	;otherwise unicorn
// Chosen:
//         sta TempSpell
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         tdc
//         tay
// :	lda f:SpecialAbilityAttackProp,X
//         sta Temp,Y
//         inx
//         iny
//         cpy #$0008	;copy 8 bytes magic info
//         bne :-
//         stz PartyTargets
//         stz MonsterTargets
//         lda Temp	;targetting byte in magic info
//         bne Targetting
//         lda AttackerIndex
//         tax
//         tdc
//         jsr SetBit_X
//         sta PartyTargets	;default to targetting self
//         bra TargetSet
// Targetting:
//         and #$08		;target enemy
//         bne TargetEnemy
//         lda #$F0
//         sta PartyTargets	;entire party
//         bra TargetSet
// TargetEnemy:
//         lda Temp
//         and #$40		;hits all targets
//         bne TargetAll
//         tdc
//         tax
//         lda #$07
//         jsr Random_X_A    	;0..7 random monster
//         tax
//         tdc
//         jsr SetBit_X
//         sta MonsterTargets
//         bra TargetSet
// TargetAll:
//         lda #$FF
//         sta MonsterTargets
// TargetSet:
//         stz TempAttachedSpell	;CastSpell routine params
//         stz TempSkipNaming
//         lda #$01		;animals are effect magic
//         sta TempIsEffect
//         jmp CastSpell
}

// Address: _0C67
// Command $16 (Aim)
static void commandTable15(void) {
    // lda #$16		;ability name
    // jsr GFXCmdAttackNameA
    // jmp FightCommand
}

// Address: _0C6F
// Command $17 (X-Fight / Rapid Fire)
//  ** optimize: lots to trim in the targetting code
//	             could also use BuildTargetBitmask
//               instead of duplicating all its code here
static void commandTable16(void) {
//         lda #$17		;ability name
//         jsr GFXCmdAttackNameA
//         stz $22			;index for attack loop
// AttackLoop:
//         tdc
//         tax
//         lda #$07
//         jsr Random_X_A 		;0..7 random monster
//         tax
//         tdc
//         jsr SetBit_X
//         ldx AttackerOffset
//         sta CharStruct::MonsterTargets,X
//         stz CharStruct::PartyTargets,X
//         ldx AttackerOffset
//         lda CharStruct::MonsterTargets,X
//         sta MonsterTargets
//         lda CharStruct::PartyTargets,X
//         sta PartyTargets
//         jsr CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//         sta CharStruct::PartyTargets,X
//         lda MonsterTargets
//         sta CharStruct::MonsterTargets,X
//         pha
//         and #$F0
//         lsr
//         lsr
//         lsr
//         lsr
//         ora CharStruct::PartyTargets,X
//         sta TempTargetBitmask
//         pla
//         and #$0F
//         asl
//         asl
//         asl
//         asl
//         sta TempTargetBitmask+1
//         lda AttackerIndex
//         tax
//         lda f:_d0ed85,X	;combined size of gearstats structs
//         tax
//         stx $0E			;gearstats offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         jmp LH
// RH:       jsr SelectCurrentProcSequence
//         sty $14			;AttackInfo offset
//         stz $12
//         ldx $0E			;gearstats offset
// :	lda RHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//         cmp #$0C		;copy 12 bytes weapon data
//         bne :-
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$01		;ability/command anim
//         sta GFXQueue::Type,X
//         lda #$04		;fight
//         sta GFXQueue::Data1,X
//         stz GFXQueue::Data2,X	;right hand, no msword anim
//         ldx $0E			;gearstats offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//         tax
//         pla
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//         asl
//         tax
//         lda TempTargetBitmask
//         sta CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//         sta CommandTargetBitmask+1,X
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
// LH:     ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//         jmp Finish
// :       jsr SelectCurrentProcSequence
//         sty $12
//         stz $14
//         ldx $0E		;gearstats offset
// :	lda LHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//         cmp #$0C	;copy 12 bytes weapon data
//         bne :-
//         ldx $0E		;gearstats offset
//         lda ProcSequence
//         tay
//         lda LHWeapon::AtkType,X
//         sta AtkType,Y
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$01		;ability/command anim
//         sta GFXQueue::Type,X
//         lda #$04		;fight
//         sta GFXQueue::Data1,X
//         lda #$80		;left hand, no msword anim
//         sta GFXQueue::Data2,X
//         lda ProcSequence
//         tax
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//         asl
//         tax
//         lda TempTargetBitmask
//         sta CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//         sta CommandTargetBitmask+1,X
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
// Finish:	inc $22			;attack loop index
//         lda $22
//         cmp #$04		;4 attacks
//         beq Ret
//         jmp AttackLoop
// Ret:	rts
}

// Address: _0DA2
// Command $19 (Observe)
static void commandTable18(void) {
    // lda #$19		;observe ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr CheckRetarget
    // jsr BuildTargetBitmask
    // lda #$19		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$18		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommand
    // jmp GFXCmdMessage
}

// Address: _0DC3
// Command $1A (Analyze)
static void commandTable19(void) {
    // lda #$1A		;observe ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr CheckRetarget
    // jsr BuildTargetBitmask
    // lda #$1A		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$19		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommand
    // jmp GFXCmdMess
}

// Address: _0DE4
// Command $18 (Conjure)
static void commandTable17(void) {
// ConjureCommand:
//         lda MagicBits+10	;2nd byte of summons
//         and #$FE		;last bit is a song
//         ora MagicBits+9		;1st byte of summons
//         bne PickRandomSummon
// ;no summons known
//         lda #$18
//         jsr GFXCmdAttackNameA
//         lda MessageBoxOffset
//         tax
//         lda #$1D		;message
//         sta MessageBoxes,X
//         lda ProcSequence
//         tax
//         lda #$7E		;always miss
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda #$0D		;ability animation
//         jsr GFXCmdAbilityAnim
//         jsr FinishCommandNullTargets
//         jsr GFXCmdMessage
//         jmp Ret
// PickRandomSummon:
//         tdc
//         tax
//         stx $0E
//         lda #$0E
//         jsr Random_X_A    	;0..14
//         clc
//         adc #$48		;offset of first summon
//         sta TempSpell
//         stz TempIsEffect
//         lsr
//         ror $0E
//         lsr
//         ror $0E
//         lsr
//         ror $0E
//         tay 			;MagicBits offset
//         lda $0E
//         jsr ShiftDivide_32
//         tax 			;MagicBits spell
//         lda MagicBits,Y
//         jsr SelectBit_X
//         beq PickRandomSummon	;don't know this one, try again
// MagicLamp:			;Magic Lamp use jumps in here
//         stz PartyTargets
//         stz MonsterTargets
//         lda TempSpell
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         tdc
//         tay
// :	lda f:AttackProp,X
//         sta Temp,Y
//         inx
//         iny
//         cpy #$0008		;copy 8 bytes magic data
//         bne :-
//         lda Temp		;targetting
//         bne FindTargets
// ;no targetting data, target self
//         lda AttackerIndex
//         tax
//         tdc
//         jsr SetBit_X
//         sta PartyTargets
//         bra TargetSet
// FindTargets:
//         and #$40		;hits all
//         bne TargetAll
//         lda Temp		;targetting
//         and #$08		;enemy by default
//         bne SingleEnemy
// SingleAlly:			;hardcoded for phoenix, targets first dead ally
//         tdc
//         tax
//         tay
// :	lda CharStruct::Status1,X
//         and #$80		;dead
//         bne DeadAlly
//         jsr NextCharOffset
//         iny
//         cpy #$0004		;4 chars
//         bne :-
//         lda #$80		;defaults to first member if none dead
//         bra SetAlly
// DeadAlly:
//         tyx
//         tdc
//         jsr SetBit_X
// SetAlly:
//         sta PartyTargets	;target single dead ally
//         bra TargetSet
// SingleEnemy:
//         tdc
//         tax
//         lda #$07
//         jsr Random_X_A 		;0..7 random monster
//         tax
//         tdc
//         jsr SetBit_X
//         sta MonsterTargets
//         bra TargetSet
// TargetAll:
//         lda Temp		;targetting
//         and #$08		;enemy by default
//         bne AllEnemy
//         lda #$F0
//         sta PartyTargets	;all allies
//         bra TargetSet
// AllEnemy:
//         lda #$FF
//         sta MonsterTargets	;all enemies
// TargetSet:
//         stz TempAttachedSpell	;params for CastSpell
//         stz TempSkipNaming
//         jsr CastSpell
//         lda TempAttachedSpell
//         beq Ret
//         lda TempAttachedSpell	;second spell, for phoenix summon
//         sta TempSpell
//         stz TempIsEffect
//         lda TempMonsterTargets
//         sta MonsterTargets
//         lda TempPartyTargets
//         sta PartyTargets
//         inc TempSkipNaming	;2nd spell has no label and diff anim
//         jsr CastSpell
// Ret:	rts

// ConjureMagicLamp := CommandTable17::MagicLamp   ; Definition needed to jump to here
}

// Address: _0EE0
// Command $1B (Tame/Calm)
static void commandTable1A(void) {
    // lda #$1B		;tame ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr CheckRetarget
    // jsr BuildTargetBitmask
    // lda #$1B		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$1A		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jmp FinishCommand
}

// Address: _0EFE
// Command $1C (Control)
static void commandTable1B(void) {
    // lda #$1C		;control ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr CheckRetarget
    // jsr BuildTargetBitmask
    // lda #$1C		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$1B		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommand
    // jmp GFXCmdMessage
}

// Address: _0F1F
// Command $1D (Catch)
static void commandTable1C(void) {
    // lda #$1D		;catch ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr CheckRetarget
    // jsr BuildTargetBitmask
    // lda #$1D		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$1C		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommand
    // jmp GFXCmdMessage
}

// Address: _0F40
// Command $1E (Release)
static void commandTable1D(void) {
//         ldx AttackerOffset
//         lda CharStruct::CaughtMonster,X
//         sta ReleasedMonsterID
//         pha
//         lda #$FF		;no monster caught
//         sta CharStruct::CaughtMonster,X
//         pla
//         tax
//         lda f:MonsterRelease,X
//         sta TempSpell
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         tdc
//         tay
// :  	lda f:AttackProp,X
//         sta TempMagicInfo,Y
//         inx
//         iny
//         cpy #$0008		;8 bytes magic data
//         bne :-
//         jsr SelectCurrentProcSequence
//         tdc
//         tax
// :	lda TempMagicInfo,X
//         sta AttackInfo,Y
//         inx
//         iny
//         cpx #$0005		;copy first 5 bytes
//         bne :-
//         iny 			;increment dest pointer by 4
//         iny
//         iny
//         iny
// :	lda TempMagicInfo,X
//         sta AttackInfo,Y
//         inx
//         iny
//         cpx #$0008		;then copy remaining 3 bytes
//         bne :-
//         stz MonsterTargets
//         stz PartyTargets
//         lda TempMagicInfo::Targetting
//         bne Targetting
//         lda AttackerIndex
//         tax
//         tdc
//         jsr SetBit_X
//         sta PartyTargets	;default to attacker if no targetting
//         bra TargetSet
// Targetting:
//         and #$40		;all targets
//         bne TargetAll
//         lda TempMagicInfo::Targetting
//         and #$08		;enemy by default
//         bne TargetEnemy
// TargetParty:
//         tdc
//         tax
//         lda #$03
//         jsr Random_X_A		;0..3 random party
//         cmp AttackerIndex
//         beq TargetParty	;pick again if attacker chosen
//         tax
//         tdc
//         jsr SetBit_X
//         sta PartyTargets
//         bra TargetSet
// TargetEnemy:
//         tdc
//         tax
//         lda #$07
//         jsr Random_X_A	      	;0..7 random monster
//         tax
//         tdc
//         jsr SetBit_X
//         sta MonsterTargets
//         bra TargetSet
// TargetAll:
//         lda TempMagicInfo::Targetting
//         and #$08		;enemy by default
//         bne TargetAllEnemy
//         lda #$F0
//         sta PartyTargets
//         bra TargetSet
// TargetAllEnemy:
//         lda #$FF
//         sta MonsterTargets
// TargetSet:
//         jsr CheckMultiTarget
//         bne Multi
//         lda TempMagicInfo::AtkType
//         bpl _CheckRetarget
//         lda ProcSequence
//         tax
//         inc HitsInactive,X
//         bra TargetOK
// _CheckRetarget:
//         jsr CheckRetarget
//         bra TargetOK
// Multi:
//         jsr RemoveInactiveTargets
//         jsr CheckMultiTarget
// TargetOK:
//         jsr BuildTargetBitmask
//         lda TempSpell
//         sta Temp+1		;attack id
//         stz Temp		;string table 0
//         jsr GFXCmdAttackNameFromTemp
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Data2,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$00		;attack animation
//         sta GFXQueue::Type,X
//         lda Temp+1		;attack id
//         sta GFXQueue::Data1,X
//         lda ProcSequence
//         tax
//         lda TempMagicInfo::AtkType
//         and #$7F		;remove flag bit
//         sta AtkType,X
//         lda TempTargetting	;number of targets minus 1
//         sta MultiTarget,X
//         beq :+
//         inc MultiTarget,X	;number of targets (but 1 target -> 0)
//         lda #$80		;multi target
// :	sta TargetType,X
//         lda ProcSequence
//         asl
//         tax
//         lda TempTargetBitmask
//         sta CommandTargetBitmask,X
//         sta TargetBitmask,X
//         lda TempTargetBitmask+1
//         sta CommandTargetBitmask+1,X
//         sta TargetBitmask+1,X
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
//         lda AttackerIndex
//         sta $24
//         lda #$14
//         sta $25
//         jsr Multiply_8bit     	;Index * 20, size of CharCommands
//         tdc
//         tay
//         ldx $26			;CharCommands offset
// FindCmd:
//         lda CharCommands::ID,X
//         cmp #$1E		;release
//         beq Found
//         inx
//         iny
//         cpy #$0004		;4 command slots
//         bne FindCmd
//         beq CopyStats
// Found:
//         lda #$1D		;catch
//         sta CharCommands::ID,X
//         lda #$28		;target selectable + enemy default
//         sta CharCommands::Targetting,X
//         inx
//         iny
//         bra FindCmd		;keep going, could have multiple copies
// CopyStats:	;backs up attacker's stats so it can load monster stats instead, they will be restored later
//         ldx AttackerOffset
//         lda CharStruct::Level,X
//         sta SavedCharStats::Level
//         lda CharStruct::MonsterAttack,X
//         sta SavedCharStats::MonsterAttack
//         lda CharStruct::MonsterM,X
//         sta SavedCharStats::MonsterM
//         lda CharStruct::EquippedMag,X
//         sta SavedCharStats::EquippedMag
//         lda CharStruct::CharRow,X
//         sta SavedCharStats::CharRow
//         tdc
//         tay
// CopyStatus:
//         lda CharStruct::Status1,X
//         sta SavedCharStats::Status1,Y
//         stz CharStruct::Status1,X	;clear status for released mon
//         inx
//         iny
//         cpy #$0009		;9 bytes of status/passives
//         bne CopyStatus
//         tdc
//         tay
//         ldx AttackerOffset
// CopyMSword:
//         lda CharStruct::MSwordElemental1,X
//         sta SavedCharStats::MSwordElemental1,Y
//         stz CharStruct::MSwordElemental1,X	;clear all msword
//         inx
//         iny
//         cpy #$0006		;6 bytes msword elements/status
//         bne CopyMSword
//         tdc
//         tay
//         ldx AttackerOffset
// CopyMisc:
//         lda CharStruct::AlwaysStatus1,X
//         sta SavedCharStats::AlwaysStatus1,Y
//         stz CharStruct::AlwaysStatus1,X
//         inx
//         iny
//         cpy #$000B		;11 bytes always status/bonuses/etc
//         bne CopyMisc
//         lda ReleasedMonsterID
//         longa
//         jsr ShiftMultiply_32
//         tax
//         shorta0
//         ldy AttackerOffset
//         lda CharStruct::CharRow,Y
//         and #$7F		;always front row
//         sta CharStruct::CharRow,Y
//         lda f:MonsterProp + 31,X
//         sta CharStruct::Level,Y
//         lda f:MonsterProp + 1,X
//         sta CharStruct::MonsterAttack,Y
//         lda f:MonsterProp + 2,X
//         sta CharStruct::MonsterM,Y
//         lda f:MonsterProp + 5,X
//         sta CharStruct::EquippedMag,Y
//         lda #$01
//         sta WasMonsterReleased	;causes stats to be restored later
//         rts
}

// Address: _1125
// Command $1F (Combine/Mix)
static void commandTable1E(void) {
    // ldx AttackerOffset
    // lda CharStruct::MonsterTargets,X
    // sta MonsterTargets
    // lda CharStruct::PartyTargets,X
    // sta PartyTargets
    // lda CharStruct::SelectedItem,X
    // sec
    // sbc #$E0	;remove consumable item offset from item id
    // tax
    // stx $0E		;first item consumable index
    // ldx AttackerOffset
    // lda CharStruct::SecondSelectedItem,X
    // sec
    // sbc #$E0	;remove consumable item offset from item id
    // sta $24
    // lda #$0C
    // sta $25
    // jsr Multiply_8bit    	;item*12
    // longa
    // clc
    // lda $26			;second item * 12
    // adc $0E			;+ first item
    // tax
    // shorta0
    // lda f:MixComboTbl,X
    // sta TempSpell
    // stz TempAttachedSpell
    // stz TempSkipNaming
    // lda #$01
    // sta TempIsEffect
    // jmp CastSpell
}

// Address: _1169
// Command $21 (Pray/Recover)
static void commandTable20(void) {
    // lda #$21		;recover ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr BuildTargetBitmask
    // jsr CheckMultiTarget
    // lda #$21		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$20		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeMultiTarget
    // jsr FinishCommand
    // jmp GFXCmdDamageNumbers
}

// Address: _118A
// Command $22 (Revive)
static void commandTable21(void) {
    // lda #$22		;revive ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr BuildTargetBitmask
    // jsr CheckMultiTarget
    // lda ProcSequence
    // tax
    // inc HitsInactive,X
    // lda #$22		;ability name
    // jsr GFXCmdAttackNameA
    // lda #$21		;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeMultiTarget
    // jsr FinishCommand
    // jmp GFXCmdDamageNumbers
}

// Address: _11B2
// Command $23 (Gaia/Terrain)
static void commandTable22(void) {
//         tdc
//         tax
//         lda Level
//         jsr Random_X_A 	;0..Level
//         cmp #$0B
//         bcs :+
//         tdc          	;<11, 0
//         bra Chosen
// :	cmp #$15
//         bcs :+
//         lda #$01     	;<21, 1
//         bra Chosen
// :	cmp #$33
//         bcs :+
//         lda #$02     	;<50, 2
//         bra Chosen
// :	lda #$03     	;otherwise 3
// Chosen:
//         sta $0E		;terrain spell slot 0-3
//         lda TerrainType
//         jsr ShiftMultiply_4
//         clc
//         adc $0E
//         tax
//         lda f:TerrainAttackTbl,X
//         sta TempSpell
//         lda TempSpell	;pointless load?
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         tdc
//         tay
// :	lda f:SpecialAbilityAttackProp,X
//         sta Temp,Y
//         inx
//         iny
//         cpy #$0008	;copy 8 bytes spell data
//         bne :-
//         stz PartyTargets
//         stz MonsterTargets
//         lda Temp		;targetting byte
//         bne Targetting
//         lda AttackerIndex	;default to attacker
//         tax
//         tdc
//         jsr SetBit_X
//         sta PartyTargets
//         bra TargetSet
// Targetting:
//         and #$08	;target enemy by default
//         bne TargetEnemy
//         lda Temp
//         and #$40	;target all
//         bne TargetAllParty
//         tdc
//         tax
//         lda #$03
//         jsr Random_X_A 	;0..3 random party
//         tax
//         tdc
//         jsr SetBit_X
//         sta PartyTargets
//         bra TargetSet
// TargetAllParty:
//         lda #$F0
//         sta PartyTargets
//         bra TargetSet
// TargetEnemy:
//         lda Temp
//         and #$40	;target all
//         bne TargetAllEnemy
//         tdc
//         tax
//         lda #$07	;0..7 random monster
//         jsr Random_X_A
//         tax
//         tdc
//         jsr SetBit_X
//         sta MonsterTargets
//         bra TargetSet
// TargetAllEnemy:
//         lda #$FF
//         sta MonsterTargets
// TargetSet:
//         stz TempAttachedSpell
//         stz TempSkipNaming
//         lda #$01
//         sta TempIsEffect
//         jmp CastSpell
}

// Address: _125E
// Command $25 (Hide)
static void commandTable24(void) {
//         ldx AttackerOffset
//         lda CharStruct::Status4,X
//         ora #$01	;hidden
//         sta CharStruct::Status4,X
//         lda #$25	;hide ability name
//         jsr GFXCmdAttackNameA
//         lda #$24	;hide ability anim
//         jsr GFXCmdAbilityAnim
//         lda ProcSequence
//         tax
//         stz AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         inc UnknownReaction
//         jsr FinishCommandNullTargets
//         lda AttackerIndex
//         sta $24
//         lda #$14	;20, size of CharCommands struct
//         sta $25
//         jsr Multiply_8bit
//         tdc
//         tay
//         ldx $26
// FindHideCommands:
//         lda CharCommands::ID,X
//         cmp #$25	;hide command
//         beq Found
//         inx
//         iny
//         cpy #$0004	;4 command slots
//         bne FindHideCommands
//         beq Ret
// Found:	lda #$26	;show command
//         sta CharCommands::ID,X
//         lda #$08	;target enemy?
//         sta CharCommands::Targetting,X
//         inx
//         iny
//         bra FindHideCommands
// Ret:	rts
}

// Address: _12B3
// Command $26 (Show)
static void commandTable25(void) {
//         ldx AttackerOffset
//         lda CharStruct::Status4,X
//         and #$FE	;clear hidden
//         sta CharStruct::Status4,X
//         lda #$26	;show ability name
//         jsr GFXCmdAttackNameA
//         lda #$25	;show ability anim
//         jsr GFXCmdAbilityAnim
//         lda ProcSequence
//         tax
//         stz AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         inc UnknownReaction
//         jsr FinishCommandNullTargets
//         lda AttackerIndex
//         sta $24
//         lda #$14	;20, size of CharCommands struct
//         sta $25
//         jsr Multiply_8bit
//         tdc
//         tay
//         ldx $26
// FindShowCommands:
//         lda CharCommands::ID,X
//         cmp #$26	;show command
//         beq Found
//         inx
//         iny
//         cpy #$0004	;4 command slots
//         bne FindShowCommands
//         beq Ret
// Found:
//         lda #$25
//         sta CharCommands::ID,X
//         stz CharCommands::Targetting,X
//         inx
//         iny
//         bra FindShowCommands
// Ret:	rts
}

// Address: _1306
// Command $29 (Flirt)
static void commandTable28(void) {
    // lda #$29	;flirt ability
    // jsr CopyAbilityInfo
    // jsr GetTargets
    // jsr CheckRetarget
    // jsr BuildTargetBitmask
    // lda #$29	;ability name
    // jsr GFXCmdAttackNameA
    // lda #$28	;ability anim
    // jsr GFXCmdAbilityAnim
    // jsr MagicAtkTypeSingleTarget
    // jsr FinishCommand
    // jsr GFXCmdDamageNumbers
    // lda MessageBoxOffset
    // tax
    // lda #$27	;message
    // sta MessageBoxes,X
    // jmp GFXCmdMessage
}

// Address: _1333
// Command $2A (Dance)
static void commandTable29(void) {
//         stz ProcSequence	;reset command sequence (no procs)
//         stz NextGFXQueueSlot
//         tdc
//         tax
//         lda #$03
//         jsr Random_X_A		;0..3 random dance
//         sta TempDance
//         ldx AttackerOffset
//         lda CharStruct::ArmorProperties,X
//         and #$04		;sword dance up
//         beq DanceCheck
//         jsr Random_0_99
//         lsr
//         bcs NotSwordDance	;50% chance of sword dance
//         lda #$03		;sword dance
//         sta TempDance
//         bra DanceCheck
// NotSwordDance:
//         jsr Random_0_99
//         lsr
//         stz TempDance
//         rol TempDance		;50% chance of 0 or 1
// DanceCheck:
//         lda TempDance
//         cmp #$03		;sword dance
//         beq SwordDance
//         jsr GetTargets
//         jsr CheckRetarget
//         jsr BuildTargetBitmask
//         jsr CheckMultiTarget
//         clc
//         lda TempDance
//         adc #$79		;offset to dance strings
//         sta Temp+1		;string id / ability id
//         stz Temp		;string table
//         jsr GFXCmdAttackNameFromTemp
//         lda #$29		;dance anim
//         jsr GFXCmdAbilityAnim
//         jsr SelectCurrentProcSequence
//         lda Temp+1		;ability id
//         jsr CopyROMMagicInfo
//         jsr MagicAtkTypeSingleTarget
//         jsr FinishCommand
//         jmp GFXCmdDamageNumbers
// SwordDance:
//         lda #$7D		;sword dance ability
//         sta Temp+1		;string id / ability id
//         stz Temp		;string table
//         jsr GFXCmdAttackNameFromTemp
//         lda #$29		;dance anim
//         jsr GFXCmdAbilityAnim
//         lda ProcSequence
//         tax
//         lda #$7F		;do nothing
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         jsr FinishCommandNullTargets
//         jsr GFXCmdDamageNumbers
//         ldx AttackerOffset
//         lda CharStruct::DamageMod,X
//         ora #$D0		;auto hit, damage*2, M*2
//         sta CharStruct::DamageMod,X
//         jmp SimpleFight
}

// Address: _13CE
// Command $2B (Mimic)
static void commandTable2A(void) {
//         tdc
//         tay
//         ldx AttackerOffset
// :	lda SavedAction,Y
//         sta CharStruct::ActionFlag,X
//         inx
//         iny
//         cpy #$000A	;copy 10 bytes action data
//         bne :-
//         ldx AttackerOffset
//         lda CharStruct::ActionFlag,X
//         and #$FE	;clear "costs mp" bit
//         sta CharStruct::ActionFlag,X
//         lda CharStruct::Command,X
//         jmp DispatchCommand_CommandReady
}

// Address: _13EF
// Command $51
// Flirt Throbbing
// (null command with a message)
static void commandTable2F(void) {
    // jsr FindOpenGFXQueueSlot
    // stz GFXQueue::Flag,X
    // stz GFXQueue::Cmd,X
    // stz GFXQueue::Type,X
    // stz GFXQueue::Data1,X
    // stz GFXQueue::Data2,X
    // lda ProcSequence
    // tax
    // stz AtkType,X
    // stz MultiTarget,X
    // stz TargetType,X
    // jsr FinishCommandNullTargets
    // lda MessageBoxOffset
    // tax
    // lda #$28	;message to display
    // sta MessageBoxes,X
    // jmp GFXCmdMessage
}

// Address: _141D
// Command $52
// Jump with a different name
static void commandTable30(void) {
    // lda #$52	;command name
    // jsr GFXCmdAttackNameA
    // jmp CommandTable0C::Anim
}

// Address: _1425
// Command $53
// Handles weapons that cast effect spells
// Wind Slash by default, but
// can be called mid-routine for other effects like
// Earthquake
static void commandTable31(void) {
//         lda #$4B	;wind slash spell effect
//         sta TempEffect
// WeaponEffectCommand:	;called here for other weapon effects
//         stz $0E		;hand
//         stz NextGFXQueueSlot
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne :+
//         lda #$80	;left hand
//         sta $0E
// :	jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag
//         lda #$FC	;exec graphics command
//         sta GFXQueue::Cmd
//         lda #$01	;ability/command anim
//         sta GFXQueue::Type
//         lda #$04	;fight
//         sta GFXQueue::Data1
//         lda $0E		;hand (0 for RH, 80 for LH)
//         sta GFXQueue::Data2
//         lda #$7E	;always miss
//         sta AtkType
//         stz MultiTarget
//         stz TargetType
//         stz CommandTargetBitmask
//         stz CommandTargetBitmask+1
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
//         lda #$FF
//         sta a:wMonsterTargets	;**optimize: wasted bytes
//         stz a:wPartyTargets
//         lda TempEffect
//         sta TempSpell
//         lda #$01
//         sta TempIsEffect
//         sta TempSkipNaming
//         stz TempAttachedSpell
//         jsr CastSpell
//         ldx AttackerOffset
//         lda CharStruct::Command,X
//         cmp #$0C	;capture/mug
//         bne Ret	;removes return address from stack for capture
//         plx 		;likely unreachable since capture cancels procs
// Ret:	rts
}

// Address: _1490
// Command $54
// Job-specific attack animation
// likely for credits demo?
static void commandTable32(void) {
    // ldx AttackerOffset
    // clc
    // lda CharStruct::Job,X
    // adc #$30
    // jsr GFXCmdAbilityAnim
    // lda #$7F	;null attack
    // sta AtkType
    // stz MultiTarget
    // stz TargetType
    // lda #$08	;first monster
    // sta CommandTargetBitmask
    // sta TargetBitmask
    // stz CommandTargetBitmask+1
    // stz TargetBitmask+1
    // inc UnknownReaction
    // rts
}

// Address: _14B8
// Command $55
// For Double Lance
// Attacks twice per hand if
// hand's weapon has this command proc
static void commandTable33(void) {
//         stz ProcSequence	;cancels any other procs
//         stz NextGFXQueueSlot
//         ldx AttackerOffset
//         lda CharStruct::MonsterTargets,X
//         sta MonsterTargets
//         lda CharStruct::PartyTargets,X
//         sta PartyTargets
//         jsr CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//         sta CharStruct::PartyTargets,X
//         lda MonsterTargets
//         sta CharStruct::MonsterTargets,X
//         pha
//         and #$F0
//         lsr
//         lsr
//         lsr
//         lsr
//         ora CharStruct::PartyTargets,X
//         sta TempTargetBitmask
//         pla
//         and #$0F
//         asl
//         asl
//         asl
//         asl
//         sta TempTargetBitmask+1
//         lda AttackerIndex
//         tax
//         lda f:_d0ed85,X	;size of one character's gear structs
//         tax
//         stx $0E			;GearStruct offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         jmp LH
// RH:	jsr SelectCurrentProcSequence
//         sty $14
//         stz $12
//         ldx $0E
// :      	lda RHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//         cmp #$0C		;copy 12 bytes weapon data
//         bne :-
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$01		;ability/command animation
//         sta GFXQueue::Type,X
//         lda #$04		;fight
//         sta GFXQueue::Data1,X
//         stz GFXQueue::Data2,X	;right hand, no msword
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//         tax
//         pla
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//         asl
//         tax
//         lda TempTargetBitmask
//         sta CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//         sta CommandTargetBitmask+1,X
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
//         jsr SelectCurrentProcSequence
//         sty $14
//         stz $12
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::Properties,X
//         and #$02		;command instead of attack
//         beq LH
//         lda RHWeapon::Param3,X
//         cmp #$55		;this command
//         bne LH
// :	lda RHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//         cmp #$0C		;copy 12 bytes data for 2nd attack
//         bne :-
//         lda #$80
//         sta ActionAnimShift	;flag for later anim manipulation
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Cmd,X
//         stz GFXQueue::Type,X
//         stz GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//         tax
//         pla
//         sta AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//         asl
//         tax
//         lda TempTargetBitmask
//         sta CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//         sta CommandTargetBitmask+1,X
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
// LH:       ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//         jmp Ret
// :       jsr SelectCurrentProcSequence
//         sty $12
//         stz $14
//         ldx $0E			;GearStruct offset
// :   	lda LHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//         cmp #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;GearStruct offset
//         lda ProcSequence
//         tay
//         lda LHWeapon::AtkType,X
//         sta AtkType,Y
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//         sta GFXQueue::Cmd,X
//         lda #$01		;command/ability anim
//         sta GFXQueue::Type,X
//         lda #$04		;fight
//         sta GFXQueue::Data1,X
//         lda #$80		;left hand, no msword
//         sta GFXQueue::Data2,X
//         lda ProcSequence
//         tax
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//         asl
//         tax
//         lda TempTargetBitmask
//         sta CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//         sta CommandTargetBitmask+1,X
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
//         jsr SelectCurrentProcSequence
//         sty $12
//         stz $14
//         ldx $0E
//         lda LHWeapon::Properties,X
//         and #$02		;command instead of attack
//         beq Ret
//         lda LHWeapon::Param3,X
//         cmp #$55		;this command
//         bne Ret
// :	lda LHWeapon,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//         cmp #$0C		;copy 12 bytes weapon data for 2nd atk
//         bne :-
//         lda ActionAnimShift
//         ora #$40
//         sta ActionAnimShift
//         ldx $0E
//         lda ProcSequence
//         tay
//         lda LHWeapon::AtkType,X
//         sta AtkType,Y
//         jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Cmd,X
//         stz GFXQueue::Type,X
//         stz GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         lda ProcSequence
//         tax
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//         asl
//         tax
//         lda TempTargetBitmask
//         sta CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//         sta CommandTargetBitmask+1,X
//         inc ProcSequence
//         jsr GFXCmdDamageNumbers
// Ret:	rts
}

// Address: _16A2
// Command $56
// Earthquake weapon effect
static void commandTable34(void) {
    // lda #$4A	;earthquake
    // sta TempEffect
    // jmp CommandTable31::WeaponEffectCommand
}