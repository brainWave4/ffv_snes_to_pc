// Bank Range: C2/0000 - C2/9FFF
#include <stdint.h>

#include "battle.h"

// for ExecBtlGfx_ext
#include "btlgfx.h"

// for ExecSound_ext
#include "sound.h"

// TODO: import RNGTbl (from field), AttackMessageTbl

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

static void copyAbilityInfo(void);
static void gfXCmdAbilityAnim(void);
static void gfxCmdAttackNameA(void);
static void magicAtkTypeSingleTarget(void);
static void magicAtkTypeMultiTarget(void);
static void finishCommand(void);
static void finishCommandNullTargets(void);
static void getTargets(void);
static void handleAtbMenu(void);
static void checkControlTargetActive(void);
static void processMenuCommandData(void);
static void consumeItem(void);
static void setupCreditsDemo(void);
static void checkDisablingStatus(void);
static void applyBerserkStatus(void);
static void disableCommandsMagic(void);
static void handleUncontrolledParty(void);
static void zombieAction(void);
static void charmAction(void);
static void berserkAction(void);
static void queueUncontrolledAction(void);
static void randomizeOrder(void);

static void updateTimers(void);
static void updateTimer(void);
static void globalTimers(void);
static void findEndedTimers(void);
static void applyTimerEffects(void);
static void dispatchTimerEffect(void);
static void timerEffectStop(void);
static void timerEffectPoison(void);
static void timerEffectReflect(void);
static void timerEffectCountdown(void);
static void timerEffectMute(void);
static void timerEffectHPLeak(void);
static void timerEffectOld(void);
static void timerEffectRegen(void);
static void timerEffectSing(void);
static void timerEffectParalyze(void);
static void timerEffectATB(void);
static void performAction(void);
static void atbWait(void);
static void resetAtbAll(void);
static void resetAtb(void);
static void clearQuick(void);
static void stopTimer(void);
static void startTimer(void);
static void getTimerDuration(void);
static void addTimerOffsetY(void);
static uint8_t durSpell(void);
static uint8_t durVit(void);
static uint8_t dur180mod(void);
static uint8_t dur110mod(void);
static void monsterAtb(void);

static void checkAICondition(void);
static void aiCondition00(void);
static void aiCondition01(void);
static void aiCondition02(void);
static void aiCondition03(void);
static void aiCondition04(void);
static void aiCondition05(void);
static void aiCondition06(void);
static void aiCondition07(void);
static void aiCondition08(void);
static void aiCondition09(void);
static void aiCondition0A(void);
static void aiCondition0B(void);
static void aiCondition0C(void);
static void aiCondition0D(void);
static void aiCondition0E(void);
static void aiCondition0F(void);
static void aiCondition10(void);
static void aiCondition11(void);
static void aiCondition12(void);

const uint8_t MIN_BYTE = 1;
const uint8_t MAX_BYTE = 255;

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
    //  Jump To Subroutine     SetupRegisters   (Call setUpRegisters())
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
    //  STore A to     f:hINIDISP       (Store accumulator to f:hINIDISP)
    //  STore A to     f:hHDMAEN        (Store accumulator to f:hHDMAEN)
    //  STore A to     f:hMDMAEN        (Store accumulator to f:hHDMAEN)
    //  STore A to     f:hNMITIMEN      (Store accumulator to f:hNMITIMEN)
    //         lda     $7cd8            (Load $7cd8 to Accumulator)
    //         bne     _002c            (Branch to _002c if zero flag is not clear)
    //         sei                      (Set Interrupt Flag)
    //  Jump To Subroutine     SetupRegisters   (Call setUpRegisters())
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
// :CoMPare A with #00
//         beq _Finish
//  CoMPare A with $3c
//         beq _Finish
//         pha
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda RNGPointer
//         eor #01
//  STore A to RNGPointer
//  Transfer A to X
//         lda $3a,X
//  Transfer A to X
//         pla
//         sec
//         sbc $3c
//  CoMPare A with #$ff
//         bne :+
//         lda f:RNGTbl,X
//         bra _Finish
// :
//         inc
//  STore A to Divisor
//         stz Divisor+1
//         lda f:RNGTbl,X
//  Transfer A to X
//         stx Dividend
//         longi
//  Jump To Subroutine Division
//         shorti
//         clc
//         lda Remainder
//         adc $3c
// _Finish:
//         pha
//         lda RNGPointer
//  Transfer A to X
//         inc $3a,X
//         longi
//         pla
//  Return To Subroutine
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
    //  DEcrement X
    //         bpl WipeAnimBlocks
    // Transfer X to A 		;A now $FF
    //         ldx #$037F
    // WipeGFXQueueDamage:	;wipes GFXQueue structure and DisplayDamage after it with $FF, $384C-$3BCB
    //  STore A to GFXQueue,X
    //  DEcrement X
    //         bpl WipeGFXQueueDamage
    //         ldx #$005F
    // WipeMessagesTimers:	;wipes Message Boxes and Timer structures after them with $FF, $3C5F-$3E8D
    //  STore A to MessageBoxes,X
    //  DEcrement X
    //         bpl WipeMessagesTimers
    //  Transfer Direct page to aCcumulator
    //         ldx #$000F
    // WipeReflectCounters:	;wipes $7B49-7B58
    //         stz CounterReflecteeTable,X
    //  DEcrement X
    //         bpl WipeReflectCounters
    //         ldx #$002F
    // WipeMessageBoxData:	;wipes numbers used for message boxes, $3CBF-$3CEE
    //         stz MessageBoxData,X
    //  DEcrement X
    //         bpl WipeMessageBoxData
    //  Return To Subroutine
}

// Address: _0248
// Recalculate Stats+Level
// with Song
//   - X: Character Offset
static void copyStatsWithBonuses(void) {
//         phx
//         phy
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// AddCopyStats:			;adds/copies Str/Agi/Vit/Mag
//         clc
//         lda CharStruct::EquippedStr,X
//         adc CharStruct::BonusStr,X
//  CoMPare A with #$64		;100
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
//  CoMPare A with #$64		;100
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
//  DEcrement X
//         bpl :-
// Transfer X to A 		            ;now $FF
//         ldx #$0010
// :	   sta $7B2D,X	        ;sets memory $7B2D - $7B3D to $FF
//  DEcrement X
//         bpl :-
//  Transfer Direct page to aCcumulator
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
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $0E
// Loop:
//         lda ActiveParticipants,X
//         beq Inactive
//         ldy $0E
//         lda CharStruct::Status1,Y
//  AND A with #$C0	;dead/stone
//         bne Inactive
//         lda CharStruct::Status4,Y
//  AND A with #$81	;erased/hiding
//         beq Next
// Inactive:
//         phx
//         cpx #$0004	;monster check
//         bcs Monster
//         lda PartyTargets
//  Jump To Subroutine ClearBit_X
//  STore A to PartyTargets
//         bra NextPLX
// Monster:
// Transfer X to A
//         sec
//         sbc #$04	;monster index
//  Transfer A to X
//         lda MonsterTargets
//  Jump To Subroutine ClearBit_X
//  STore A to MonsterTargets
// NextPLX:
//         plx
// Next:
//         longa
//         clc
//         lda $0E
//         adc #$0080	;next CharStruct offset
//  STore A to $0E
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
//  Jump To Subroutine ShiftMultiply_8	;Size of Magic Data
//  Transfer A to X
//         shorta0
//         stz $3D
// CopyFirst5:
//         lda f:AttackProp,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $3D
//         lda $3D
//  CoMPare A with #$05
//         bne CopyFirst5
//         iny 			;AttackInfo has 4 bytes that
//         iny 			;don't apply to magic
//         iny
//         iny
// CopyLast3:
//         lda f:AttackProp,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $3D
//         lda $3D
//  CoMPare A with #$08
//         bne CopyLast3
//  Return To Subroutine
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
//  AND A with #$20
//         beq RetZero
//         lda #$AA		;usable for none
//         bra Ret
// RetZero:
//         lda #$00		;usable for all
//         bra Ret
// Equipment:		;**optimize: this whole section is basically a copy of the GetItemUsableA $455E subroutine
//         lda Temp,Y
//  A Shift Left
//  A Shift Left
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         									;:
// :	lda f:EquipTypeTbl,X
//  STore A to TempEquippable,Y
//         inx
//         iny
//         cpy #$0004
//         bne :-
//         									;.
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  Transfer A to Y
//         lda #$AA
//  STore A to $0E
//         									;:
// DetermineEquippableLoop:
//         lda CharEquippable::Weapons,X
//  AND A with TempEquippable::Weapons,Y
//         bne Match
//         lda CharEquippable::Weapons+1,X
//  AND A with TempEquippable::Weapons+1,Y
//         bne Match
//         lda CharEquippable::Armor,X
//  AND A with TempEquippable::Armor,Y
//         bne Match
//         lda CharEquippable::Armor+1,X
//  AND A with TempEquippable::Armor+1,Y
//         beq NextChar
// Match:
// Transfer X to A
//         lsr
//         lsr
//         bne Check1
//         									;.
//         lda $0E
//  AND A with #$7F		;clear first character bit
//  STore A to $0E
//         bra NextChar
// Check1:
//  CoMPare A with #$01
//         bne Check2
//         lda $0E
//  AND A with #$DF		;clear second character bit
//  STore A to $0E
//         bra NextChar
// Check2:
//  CoMPare A with #$02
//         bne Other
//         lda $0E
//  AND A with #$F7         	;clear third character bit
//  STore A to $0E
//         bra NextChar
// Other:
//         lda $0E
//  AND A with #$FD		;clear fourth character bit
//  STore A to $0E
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
//  CoMPare A with #$E0
//         bcs Consumable		;>$E0 is consumable
//  CoMPare A with #$80
//         bcc Weapon		;<$80 is a weapon
// Armor:				;otherwise it's armor
//         sec
//         sbc #$80		;remove the armor offset
//         longa
//  A Shift Left
//  A Shift Left
//  STore A to $0E
//  A Shift Left
//         clc
//         adc $0E			;armor *12 (size of equipment struct)
//  Transfer A to X
//         shorta0
//         lda f:ArmorProp,X
//  AND A with #$08		;target enemy?
//         beq ItemZero
//         lda f:ArmorProp+2,X
//  AND A with #$3F		;mask to equip info
//  STore A to Temp,Y
//         lda #$5A
//  STore A to InventoryFlags,Y
//         bra Ret
// ItemZero:	;or armor targettng bit 08h
//         lda #$80		;not usable
//  STore A to Temp,Y
//         lda #$5A
//  STore A to InventoryFlags,Y
//         bra Ret
// Weapon:
//         longa
//  A Shift Left
//  A Shift Left
//  STore A to $0E
//  A Shift Left
//         clc
//         adc $0E         	;weapon *12
//  Transfer A to X
//         shorta0
//         lda f:WeaponProp+4,X
//  AND A with #$80
//  Jump To Subroutine ShiftDivide_32	;shift to 04h bit
//  STore A to InventoryFlags,Y
//         lda f:WeaponProp,X
//  STore A to InventoryTargetting,Y
//         lda f:WeaponProp+2,X
//         pha
//  AND A with #$C0		;flag bits from equipment type(? and throwable)
//         ora #$1A		;set some more bits (??)
//         ora InventoryFlags,Y	;keep existing bits (double grip)
//  STore A to InventoryFlags,Y
//         pla
//  AND A with #$3F		;mask to just equip info
//  STore A to Temp,Y
//         bra Ret
// Consumable:
//         sec
//         sbc #$E0
//         longa
//  A Shift Left
//  A Shift Left
//  A Shift Left
//  Transfer A to X
//         shorta0
//         lda f:ConsumableItemProp,X
//  STore A to InventoryTargetting,Y
//         lda f:ConsumableItemProp+2,X
//  STore A to InventoryFlags,Y
//         lda #$40		;consumable
//  STore A to Temp,Y
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
//  DEcrement X
//         bpl :-
//         ldx #$0064		;100
//         stx $12
//         ldx $2E			;previous multiply result (low bytes)
//         stx $0E
//         lda $30			;(high bytes)
//  STore A to $10
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
//  STore A to $1A
//         lda $1C
//         sbc $14
//  STore A to $1C
//         bcs :+
//         lda $1A
//         adc $12
//  STore A to $1A
//         lda $1C
//         adc $14
//  STore A to $1C
//         clc
// :	rol $16
//         rol $18
//  DEcrement X
//         bne :--
//         shorta0
// ;division ends here
//         clc
//         lda $16		;quotient, input/100
//         adc $08		;base value
//  STore A to $08		;adjusted value
//         lda $17		;high byte of above
//         adc $09
//  STore A to $09
//         sec 		;checks against 9999
//         lda $08
//         sbc $0A		;9999 low byte
//         lda $09
//         sbc $0B		;9999 high byte
//         bcc Ret
//         lda $0A		;caps at 9999
//  STore A to $08
//         lda $0B
//  STore A to $09
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
//  CoMPare A with #$04		;monster check
//         bcc Party
// Monster:
//         sec
//         sbc #$04		;now monster index
//  A Shift Left
//  Transfer A to X
//         lda f:_d0ee95,X	;*100
//  STore A to $0E
//         lda f:_d0ee95+1,X
//  STore A to $0F
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $0E
// CopyGFXQueue:		;copy 100 bytes from monster ai to GFXQueue
//         lda MonsterAIScript,X
//  STore A to GFXQueue,Y
//         inx
//         iny
//         cpy #$0064
//         bne CopyGFXQueue
//         bra Continue
// Party:
//  Jump To Subroutine FindOpenGFXQueueSlot   ;next slot in X
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Cmd,X
//         stz GFXQueue::Type,X
//         stz GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
// Continue:
//         lda ProcSequence
//  Transfer A to X
//         lda #$7E
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         inc UnknownReaction
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda #$80		;first party member
//  STore A to CommandTargetBitmask,X
//         stz CommandTargetBitmask+1,X
//         inc ProcSequence
//  Return To Subroutine
}

// Address: _0570
// For commands $02 (Item) and $20 (Drink)
static void itemCommand(void) {
// CommandTable01:
// CommandTable1F:
//         stz SelectedItem
//  Jump To Subroutine SelectCurrentProcSequence	;$0C = ProcSequence*12
//  Jump To Subroutine GetTargets
//         ldx AttackerOffset
//         lda CharStruct::ActionFlag,X
//  AND A with #$10	;weapon used as item
//         beq :+
//         jmp WeaponItem
// :       lda CharStruct::SelectedItem,X
//  CoMPare A with #$EF	;magic lamp
//         bne ConsumableItem
//  Jump To Subroutine PrepMagicLamp
//         jmp ConjureMagicLamp	;finishes up in Conjure routine
// ConsumableItem:
//  STore A to TempSpell
//         sec
//         sbc #$E0	;now consumable item index
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         ldy $0C		;ProcSequence*12
//         stz $0A
// :       lda f:ConsumableItemProp,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//  CoMPare A with #$05      	;copy 5 bytes
//         bne :-
//         iny           	;skip 4 in Attackinfo
//         iny
//         iny
//         iny
// :	lda f:ConsumableItemProp,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//  CoMPare A with #$08      	;copy remaining 3 bytes
//         bne :-
//  Jump To Subroutine CheckMultiTarget
//         bne TargetOK
//         ldy $0C		;ProcSequence*12
//         lda AttackInfo::MagicAtkType,Y
//         bpl _CheckRetarget
//         lda ProcSequence
//  Transfer A to X
//         inc HitsInactive,X	;can hit dead targets
//         bra TargetOK
// _CheckRetarget:
//  Jump To Subroutine CheckRetarget
// TargetOK:
//  Jump To Subroutine BuildTargetBitmask
//         lda TempSpell
//  STore A to Temp+1
//         lda #$04
//  STore A to Temp
//  Jump To Subroutine GFXCmdAttackNameFromTemp
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$09		;command 9: item use
//  STore A to GFXQueue::Type,X
//         lda TempSpell
//  STore A to GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         ldy $0C		;ProcSequence*12
//         lda ProcSequence
//  Transfer A to X
//         lda AttackInfo::MagicAtkType,Y
//  AND A with #$7F
//  STore A to AtkType,X
//         lda TempTargetting
//  STore A to MultiTarget,X
//         beq Single
//         inc MultiTarget,X	;now proper number of targets if >1
//         lda #$80
// Single:	sta TargetType,X
//  Jump To Subroutine FinishCommand
//  Jump To Subroutine GFXCmdDamageNumbers
//  Return To Subroutine
}

// Addres: _0632
static void weaponItem(void) {
// stz TempHand
//         lda AttackerIndex
//  Transfer A to X
//         lda f:_d0ed85,X	;size of one character's gear offset
//  Transfer A to Y
//         ldx AttackerOffset
//         lda CharStruct::SelectedItem,X
//         bne Left
//         lda CharStruct::RHWeapon,X
//  STore A to CharStruct::SelectedItem,X
//  STore A to SelectedItem
//  Transfer A to X
//         lda RHWeapon::ItemMagic,Y
//         bra ItemReady
// Left:       inc TempHand
//         lda CharStruct::LHWeapon,X
//  STore A to CharStruct::SelectedItem,X
//  STore A to SelectedItem
//  Transfer A to X
//         lda LHWeapon::ItemMagic,Y
// ItemReady:
//  STore A to TempItemMagic
//  AND A with #$7F
//         txy 		;Y is now selected item
//         pha
//         pha
//         lda ProcSequence
//  Transfer A to X
//         pla
//  STore A to AtkType,X
//  Transfer Y to A
//  STore A to Temp+1	;selected item
//         lda #$04
//  STore A to Temp
//  Jump To Subroutine GFXCmdAttackNameFromTemp
//         lda ProcSequence
//  Transfer A to X
//         lda AtkType,X
//         ldy $0C		;ProcSequence*12
//  Jump To Subroutine CopyROMMagicInfo
//  Jump To Subroutine CheckMultiTarget
//         bne TargetOK
//         ldy $0C
//         lda AttackInfo::MagicAtkType,Y
//         bpl DontRetarget
//         lda ProcSequence
//  Transfer A to X
//         inc HitsInactive,X
//         bra TargetOK
// DontRetarget:
//  Jump To Subroutine CheckRetarget
// TargetOK:
//  Jump To Subroutine BuildTargetBitmask
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC	;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$0A	;command 10: weapon used as item
//  STore A to GFXQueue::Type,X
//         pla
//  STore A to GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         lda ProcSequence
//  Transfer A to X
//         lda AtkType,X
//         bpl :+
//  Transfer Direct page to aCcumulator
//         bra :++
// :	ldy $0C
//         lda AttackInfo::MagicAtkType,Y
//  AND A with #$7F
// :	sta AtkType,X
//         lda TempTargetting
//  STore A to MultiTarget,X
//         beq :+
//         inc MultiTarget,X
//         lda #$80
// :	sta TargetType,X
//  Jump To Subroutine FinishCommand
//  Jump To Subroutine GFXCmdDamageNumbers
//         lda TempItemMagic
//         bpl Ret
// BreakOnUse:	;80h indicates item should now break
//         lda AttackerIndex
//  Jump To Subroutine ShiftMultiply_4
//  STore A to $0E
//  A Shift Left
//         clc
//         adc $0E
//  Transfer A to Y 		;Attacker index *12
//         lda TempHand
//         bne Left2
//  Transfer Direct page to aCcumulator
//  STore A to HandItems::ID,Y
//  STore A to HandItems::Level,Y
//  STore A to HandItems::MP,Y
//         lda #$38
//  STore A to HandItems::Targetting,Y
//         lda #$5A
//  STore A to HandItems::Flags,Y
//         lda #$AA
//  STore A to HandItems::Usable,Y
//         bra DoneHandItems
// Left2:	tdc
//  STore A to HandItems::ID+1,Y
//  STore A to HandItems::Level+1,Y
//  STore A to HandItems::MP+1,Y
//         lda #$38
//  STore A to HandItems::Targetting+1,Y
//         lda #$5A
//  STore A to HandItems::Flags+1,Y
//         lda #$AA
//  STore A to HandItems::Usable+1,Y
// DoneHandItems:
//         lda MessageBoxOffset
//  Transfer A to Y
//         lda #$50	;item shattered message
//  STore A to MessageBoxes,Y
//         lda MessageBoxOffset
//  STore A to $0E
//  A Shift Left
//         clc
//         adc $0E
//  Transfer A to X 		;message box index *3
//         lda SelectedItem
//  STore A to MessageBoxData,X
//         stz MessageBoxData+1,X
//         stz MessageBoxData+2,X
//  Jump To Subroutine GFXCmdMessage
//         lda DisplayInfo::CurrentChar
//         pha
//         lda AttackerIndex
//  STore A to DisplayInfo::CurrentChar
//  STore A to CurrentChar
//  Jump To Subroutine ReplaceHands
//         pla
//  STore A to DisplayInfo::CurrentChar
//  Jump To Subroutine ApplyGear
// Ret:	rts
}

// Address: _0767
static void prepMagicLamp(void) {
// lda BattleData::MagicLamp
//  CoMPare A with #$0D	;<13, normal
//         bcc Continue
//  CoMPare A with #$20	;>=32, egg chop
//         bcs EggChop
//         lda #$0D	;chocobo
//         bra Continue
// EggChop:
//         lda #$0E	;egg chop
// Continue:
//  Transfer A to X
//         lda f:_d0eee7,X
//  STore A to TempSpell
//         stz TempIsEffect
//         clc
//         lda BattleData::MagicLamp
//         adc #$01
//         bcc :+
//         lda #$FF	;cap at 255 uses
// :	sta BattleData::MagicLamp
//  Return To Subroutine
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
//  Jump To Subroutine GetTargets
//  Jump To Subroutine CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//  STore A to CharStruct::PartyTargets,X
//         lda MonsterTargets
//  STore A to CharStruct::MonsterTargets,X
//  Jump To Subroutine BuildTargetBitmask
//         lda AttackerIndex
//  Transfer A to X
//         lda f:_d0ed85,X	;size of combined gear stats struct
//  Transfer A to X
//         stx $0E			;gear stats offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         jmp LH
// RH:
//  Jump To Subroutine SelectCurrentProcSequence
//         sty $14			;AttackInfo Offset
//         stz $12			;loop index
//         ldx $0E			;gear stats offset
// :	lda RHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda RHWeapon::Properties,X
//  AND A with #$04		;magic sword ok
//         bne __MSword
//  Transfer Direct page to aCcumulator
//         bra __DoneMSword
// __MSword:
//         ldx AttackerOffset
//         lda CharStruct::MSwordAnim,X
//  AND A with #$7F		;clear high bit for right hand
// __DoneMSword:
//         pha
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/command animation
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//         pla 			;magic sword anim
//  STore A to GFXQueue::Data2,X
//         ldx $0E
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//  Transfer A to X
//         pla
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//  Jump To Subroutine FinishCommand
//  Jump To Subroutine GFXCmdDamageNumbers
// LH:
//         ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//  Return To Subroutine 			;no weapons (not even fists)
// :	jsr SelectCurrentProcSequence
//         sty $12			;AttackInfo Offset
//         stz $14			;loop index
//         ldx $0E			;gear stats offset
// :	lda LHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/command animation
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//         stx $08			;GFXQueue offset
//         ldx $0E			;gear stats offset
//         lda LHWeapon::Properties,X
//  AND A with #$04		;magic sword ok
//         bne __MSword2
//         lda #$80		;left hand
//         bra __DoneMSword2
// __MSword2:
//         ldx AttackerOffset
//         lda CharStruct::MSwordAnim,X
//         ora #$80		;left hand
// __DoneMSword2:
//         ldx $08			;GFXQueue offset
//  STore A to GFXQueue::Data2,X	;magic sword anim
//         lda ProcSequence
//  Transfer A to X
//         stz MultiTarget,X
//         stz TargetType,X
//  Jump To Subroutine FinishCommand
//  Jump To Subroutine GFXCmdDamageNumbers
//  Return To Subroutine
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
//   Jump To Subroutine GFXCmdAttackNameA
// Anim:			;routine is called here by command $52
//          lda #$0C	;jump ability anim (launch)
//   Jump To Subroutine GFXCmdAbilityAnim
//          lda ProcSequence
//   Transfer A to X
//          stz AtkType,X
//          stz MultiTarget,X
//          stz TargetType,X
//   Jump To Subroutine FinishCommandNullTargets
//          inc UnknownReaction
//          ldx AttackerOffset
//          lda #$4F	;jump landing command, maps to CommandTable2D
//   STore A to CharStruct::Command,X
//          lda #$10	;jumping
//   STore A to CharStruct::CmdStatus,X
//          lda #$80	;auto hit
//   STore A to CharStruct::DamageMod,X
//          lda #$4F	;jump landing command
//   Transfer A to X
//          lda f:BattleCmdDelay,X
//          pha
//          lda AttackerIndex
//   Jump To Subroutine GetTimerOffset
//          ldx AttackerOffset
//          pla
//   Jump To Subroutine HasteSlowMod
//   STore A to CurrentTimer::ATB,Y
//          lda #$41	;queued action
//   STore A to EnableTimer::ATB,Y
//          inc DelayedFight
//   Return To Subroutine
}

// Address: _09DD
// Command $4F (landing from Jump)
static void commandTable2D(void) {
//         lda #$2D	;jump landing anim
//  Jump To Subroutine GFXCmdAbilityAnim
//  Jump To Subroutine GetTargets
//  Jump To Subroutine CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//  STore A to CharStruct::PartyTargets,X
//         lda MonsterTargets
//  STore A to CharStruct::MonsterTargets,X
//  Jump To Subroutine BuildTargetBitmask
//         lda AttackerIndex
//  Transfer A to X
//         lda f:_d0ed85,X	;size of combined gearstats struct
//  Transfer A to X
//         stx $0E			;gear stats offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         jmp LH
// RH:	   jsr SelectCurrentProcSequence
//         stz $12
//         ldx $0E
// :	   lda RHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//  Transfer A to X
//         pla
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//  Jump To Subroutine FinishCommand
//  Jump To Subroutine GFXCmdDamageNumbers
// LH:     ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//         jmp Finish
// :	   jsr SelectCurrentProcSequence
//         stz $12
//         ldx $0E			;gear stats offset
// :       lda LHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;gear stats offset
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//         lda ProcSequence
//  Transfer A to X
//         stz MultiTarget,X
//         stz TargetType,X
//  Jump To Subroutine FinishCommand
//  Jump To Subroutine GFXCmdDamageNumbers
// Finish:       inc UnknownReaction
//  Return To Subroutine
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
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stz $0E			;target bits
// TargetActiveMonsters:
//         lda ActiveParticipants+4,X
//         beq Next
//         lda $0E
//  Jump To Subroutine SetBit_X  		;add as target if active
//  STore A to $0E
// Next:	inx
//         cpx #$0008		;8 monsters
//         bne TargetActiveMonsters
//         ldx AttackerOffset
//         lda $0E			;target bits
//  STore A to CharStruct::MonsterTargets,X
//         lda EncounterIndex+1
//         beq ItemFlag
//         lda EncounterIndex
//  CoMPare A with #$BF		;sandworm fight
//         bne ItemFlag
//         lda $0E
//  AND A with #$FC		;exclude "real" sandworm
//  STore A to CharStruct::MonsterTargets,X
// ItemFlag:
//         lda #$40		;item
//  STore A to CharStruct::ActionFlag,X
//         jmp ItemCommand
// Weapon:
//         lda #$11		;throw ability
//  Jump To Subroutine CopyAbilityInfo
//  Jump To Subroutine GetTargets
//  Jump To Subroutine CheckRetarget
//  Jump To Subroutine BuildTargetBitmask
//         lda #$11		;ability name
//  Jump To Subroutine GFXCmdAttackNameA
//         lda #$10		;ability anim
//  Jump To Subroutine GFXCmdAbilityAnim
//  Jump To Subroutine MagicAtkTypeSingleTarget
//  Jump To Subroutine FinishCommand
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
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda Level
//  Jump To Subroutine Random_X_A		;0..Level
//         bne :+
//  Transfer Direct page to aCcumulator 		;0 mystidian rabbit
//         bra Chosen
// :CoMPare A with #$05
//         bcs :+
//         lda #$01	;<5 squirrel
//         bra Chosen
// :CoMPare A with #$0A
//         bcs :+
//         lda #$02	;<10 bee swarm
//         bra Chosen
// :CoMPare A with #$14
//         bcs :+
//         lda #$03	;<20 nightingale
//         bra Chosen
// :CoMPare A with #$1E
//         bcs :+
//         lda #$04	;<30 momonga
//         bra Chosen
// :CoMPare A with #$28
//         bcs :+
//         lda #$05	;<40 falcon
//         bra Chosen
// :CoMPare A with #$32
//         bcs :+
//         lda #$06	;<50 skunk
//         bra Chosen
// :CoMPare A with #$3C
//         bcs :+
//         lda #$07	;<60 wild boar
//         bra Chosen
// :	lda #$08	;otherwise unicorn
// Chosen:
//  STore A to TempSpell
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// :	lda f:SpecialAbilityAttackProp,X
//  STore A to Temp,Y
//         inx
//         iny
//         cpy #$0008	;copy 8 bytes magic info
//         bne :-
//         stz PartyTargets
//         stz MonsterTargets
//         lda Temp	;targetting byte in magic info
//         bne Targetting
//         lda AttackerIndex
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to PartyTargets	;default to targetting self
//         bra TargetSet
// Targetting:
//  AND A with #$08		;target enemy
//         bne TargetEnemy
//         lda #$F0
//  STore A to PartyTargets	;entire party
//         bra TargetSet
// TargetEnemy:
//         lda Temp
//  AND A with #$40		;hits all targets
//         bne TargetAll
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump To Subroutine Random_X_A    	;0..7 random monster
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to MonsterTargets
//         bra TargetSet
// TargetAll:
//         lda #$FF
//  STore A to MonsterTargets
// TargetSet:
//         stz TempAttachedSpell	;CastSpell routine params
//         stz TempSkipNaming
//         lda #$01		;animals are effect magic
//  STore A to TempIsEffect
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
//  Jump To Subroutine GFXCmdAttackNameA
//         stz $22			;index for attack loop
// AttackLoop:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump To Subroutine Random_X_A 		;0..7 random monster
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//         ldx AttackerOffset
//  STore A to CharStruct::MonsterTargets,X
//         stz CharStruct::PartyTargets,X
//         ldx AttackerOffset
//         lda CharStruct::MonsterTargets,X
//  STore A to MonsterTargets
//         lda CharStruct::PartyTargets,X
//  STore A to PartyTargets
//  Jump To Subroutine CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//  STore A to CharStruct::PartyTargets,X
//         lda MonsterTargets
//  STore A to CharStruct::MonsterTargets,X
//         pha
//  AND A with #$F0
//         lsr
//         lsr
//         lsr
//         lsr
//         ora CharStruct::PartyTargets,X
//  STore A to TempTargetBitmask
//         pla
//  AND A with #$0F
//  A Shift Left
//  A Shift Left
//  A Shift Left
//  A Shift Left
//  STore A to TempTargetBitmask+1
//         lda AttackerIndex
//  Transfer A to X
//         lda f:_d0ed85,X	;combined size of gearstats structs
//  Transfer A to X
//         stx $0E			;gearstats offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         jmp LH
// RH:Jump To Subroutine SelectCurrentProcSequence
//         sty $14			;AttackInfo offset
//         stz $12
//         ldx $0E			;gearstats offset
// :	lda RHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//         bne :-
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/command anim
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//         stz GFXQueue::Data2,X	;right hand, no msword anim
//         ldx $0E			;gearstats offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//  Transfer A to X
//         pla
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
// LH:     ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//         jmp Finish
// :Jump To Subroutine SelectCurrentProcSequence
//         sty $12
//         stz $14
//         ldx $0E		;gearstats offset
// :	lda LHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//  CoMPare A with #$0C	;copy 12 bytes weapon data
//         bne :-
//         ldx $0E		;gearstats offset
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/command anim
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//         lda #$80		;left hand, no msword anim
//  STore A to GFXQueue::Data2,X
//         lda ProcSequence
//  Transfer A to X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
// Finish:	inc $22			;attack loop index
//         lda $22
//  CoMPare A with #$04		;4 attacks
//         beq Ret
//         jmp AttackLoop
// Ret:	rts
}

// Address: _0DA2
// Command $19 (Observe/Check)
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
// Command $1A (Analyze/Scan)
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
//  AND A with #$FE		;last bit is a song
//         ora MagicBits+9		;1st byte of summons
//         bne PickRandomSummon
// ;no summons known
//         lda #$18
//  Jump To Subroutine GFXCmdAttackNameA
//         lda MessageBoxOffset
//  Transfer A to X
//         lda #$1D		;message
//  STore A to MessageBoxes,X
//         lda ProcSequence
//  Transfer A to X
//         lda #$7E		;always miss
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda #$0D		;ability animation
//  Jump To Subroutine GFXCmdAbilityAnim
//  Jump To Subroutine FinishCommandNullTargets
//  Jump To Subroutine GFXCmdMessage
//         jmp Ret
// PickRandomSummon:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $0E
//         lda #$0E
//  Jump To Subroutine Random_X_A    	;0..14
//         clc
//         adc #$48		;offset of first summon
//  STore A to TempSpell
//         stz TempIsEffect
//         lsr
//         ror $0E
//         lsr
//         ror $0E
//         lsr
//         ror $0E
//  Transfer A to Y 			;MagicBits offset
//         lda $0E
//  Jump To Subroutine ShiftDivide_32
//  Transfer A to X 			;MagicBits spell
//         lda MagicBits,Y
//  Jump To Subroutine SelectBit_X
//         beq PickRandomSummon	;don't know this one, try again
// MagicLamp:			;Magic Lamp use jumps in here
//         stz PartyTargets
//         stz MonsterTargets
//         lda TempSpell
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// :	lda f:AttackProp,X
//  STore A to Temp,Y
//         inx
//         iny
//         cpy #$0008		;copy 8 bytes magic data
//         bne :-
//         lda Temp		;targetting
//         bne FindTargets
// ;no targetting data, target self
//         lda AttackerIndex
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to PartyTargets
//         bra TargetSet
// FindTargets:
//  AND A with #$40		;hits all
//         bne TargetAll
//         lda Temp		;targetting
//  AND A with #$08		;enemy by default
//         bne SingleEnemy
// SingleAlly:			;hardcoded for phoenix, targets first dead ally
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  Transfer A to Y
// :	lda CharStruct::Status1,X
//  AND A with #$80		;dead
//         bne DeadAlly
//  Jump To Subroutine NextCharOffset
//         iny
//         cpy #$0004		;4 chars
//         bne :-
//         lda #$80		;defaults to first member if none dead
//         bra SetAlly
// DeadAlly:
//         tyx
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
// SetAlly:
//  STore A to PartyTargets	;target single dead ally
//         bra TargetSet
// SingleEnemy:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump To Subroutine Random_X_A 		;0..7 random monster
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to MonsterTargets
//         bra TargetSet
// TargetAll:
//         lda Temp		;targetting
//  AND A with #$08		;enemy by default
//         bne AllEnemy
//         lda #$F0
//  STore A to PartyTargets	;all allies
//         bra TargetSet
// AllEnemy:
//         lda #$FF
//  STore A to MonsterTargets	;all enemies
// TargetSet:
//         stz TempAttachedSpell	;params for CastSpell
//         stz TempSkipNaming
//  Jump To Subroutine CastSpell
//         lda TempAttachedSpell
//         beq Ret
//         lda TempAttachedSpell	;second spell, for phoenix summon
//  STore A to TempSpell
//         stz TempIsEffect
//         lda TempMonsterTargets
//  STore A to MonsterTargets
//         lda TempPartyTargets
//  STore A to PartyTargets
//         inc TempSkipNaming	;2nd spell has no label and diff anim
//  Jump To Subroutine CastSpell
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
//  STore A to ReleasedMonsterID
//         pha
//         lda #$FF		;no monster caught
//  STore A to CharStruct::CaughtMonster,X
//         pla
//  Transfer A to X
//         lda f:MonsterRelease,X
//  STore A to TempSpell
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// :  	lda f:AttackProp,X
//  STore A to TempMagicInfo,Y
//         inx
//         iny
//         cpy #$0008		;8 bytes magic data
//         bne :-
//  Jump To Subroutine SelectCurrentProcSequence
//  Transfer Direct page to aCcumulator
//  Transfer A to X
// :	lda TempMagicInfo,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         cpx #$0005		;copy first 5 bytes
//         bne :-
//         iny 			;increment dest pointer by 4
//         iny
//         iny
//         iny
// :	lda TempMagicInfo,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         cpx #$0008		;then copy remaining 3 bytes
//         bne :-
//         stz MonsterTargets
//         stz PartyTargets
//         lda TempMagicInfo::Targetting
//         bne Targetting
//         lda AttackerIndex
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to PartyTargets	;default to attacker if no targetting
//         bra TargetSet
// Targetting:
//  AND A with #$40		;all targets
//         bne TargetAll
//         lda TempMagicInfo::Targetting
//  AND A with #$08		;enemy by default
//         bne TargetEnemy
// TargetParty:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump To Subroutine Random_X_A		;0..3 random party
//  CoMPare A with AttackerIndex
//         beq TargetParty	;pick again if attacker chosen
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to PartyTargets
//         bra TargetSet
// TargetEnemy:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump To Subroutine Random_X_A	      	;0..7 random monster
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to MonsterTargets
//         bra TargetSet
// TargetAll:
//         lda TempMagicInfo::Targetting
//  AND A with #$08		;enemy by default
//         bne TargetAllEnemy
//         lda #$F0
//  STore A to PartyTargets
//         bra TargetSet
// TargetAllEnemy:
//         lda #$FF
//  STore A to MonsterTargets
// TargetSet:
//  Jump To Subroutine CheckMultiTarget
//         bne Multi
//         lda TempMagicInfo::AtkType
//         bpl _CheckRetarget
//         lda ProcSequence
//  Transfer A to X
//         inc HitsInactive,X
//         bra TargetOK
// _CheckRetarget:
//  Jump To Subroutine CheckRetarget
//         bra TargetOK
// Multi:
//  Jump To Subroutine RemoveInactiveTargets
//  Jump To Subroutine CheckMultiTarget
// TargetOK:
//  Jump To Subroutine BuildTargetBitmask
//         lda TempSpell
//  STore A to Temp+1		;attack id
//         stz Temp		;string table 0
//  Jump To Subroutine GFXCmdAttackNameFromTemp
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Data2,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$00		;attack animation
//  STore A to GFXQueue::Type,X
//         lda Temp+1		;attack id
//  STore A to GFXQueue::Data1,X
//         lda ProcSequence
//  Transfer A to X
//         lda TempMagicInfo::AtkType
//  AND A with #$7F		;remove flag bit
//  STore A to AtkType,X
//         lda TempTargetting	;number of targets minus 1
//  STore A to MultiTarget,X
//         beq :+
//         inc MultiTarget,X	;number of targets (but 1 target -> 0)
//         lda #$80		;multi target
// :	sta TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//  STore A to TargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  STore A to TargetBitmask+1,X
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
//         lda AttackerIndex
//  STore A to $24
//         lda #$14
//  STore A to $25
//  Jump To Subroutine Multiply_8bit     	;Index * 20, size of CharCommands
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $26			;CharCommands offset
// FindCmd:
//         lda CharCommands::ID,X
//  CoMPare A with #$1E		;release
//         beq Found
//         inx
//         iny
//         cpy #$0004		;4 command slots
//         bne FindCmd
//         beq CopyStats
// Found:
//         lda #$1D		;catch
//  STore A to CharCommands::ID,X
//         lda #$28		;target selectable + enemy default
//  STore A to CharCommands::Targetting,X
//         inx
//         iny
//         bra FindCmd		;keep going, could have multiple copies
// CopyStats:	;backs up attacker's stats so it can load monster stats instead, they will be restored later
//         ldx AttackerOffset
//         lda CharStruct::Level,X
//  STore A to SavedCharStats::Level
//         lda CharStruct::MonsterAttack,X
//  STore A to SavedCharStats::MonsterAttack
//         lda CharStruct::MonsterM,X
//  STore A to SavedCharStats::MonsterM
//         lda CharStruct::EquippedMag,X
//  STore A to SavedCharStats::EquippedMag
//         lda CharStruct::CharRow,X
//  STore A to SavedCharStats::CharRow
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// CopyStatus:
//         lda CharStruct::Status1,X
//  STore A to SavedCharStats::Status1,Y
//         stz CharStruct::Status1,X	;clear status for released mon
//         inx
//         iny
//         cpy #$0009		;9 bytes of status/passives
//         bne CopyStatus
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx AttackerOffset
// CopyMSword:
//         lda CharStruct::MSwordElemental1,X
//  STore A to SavedCharStats::MSwordElemental1,Y
//         stz CharStruct::MSwordElemental1,X	;clear all msword
//         inx
//         iny
//         cpy #$0006		;6 bytes msword elements/status
//         bne CopyMSword
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx AttackerOffset
// CopyMisc:
//         lda CharStruct::AlwaysStatus1,X
//  STore A to SavedCharStats::AlwaysStatus1,Y
//         stz CharStruct::AlwaysStatus1,X
//         inx
//         iny
//         cpy #$000B		;11 bytes always status/bonuses/etc
//         bne CopyMisc
//         lda ReleasedMonsterID
//         longa
//  Jump To Subroutine ShiftMultiply_32
//  Transfer A to X
//         shorta0
//         ldy AttackerOffset
//         lda CharStruct::CharRow,Y
//  AND A with #$7F		;always front row
//  STore A to CharStruct::CharRow,Y
//         lda f:MonsterProp + 31,X
//  STore A to CharStruct::Level,Y
//         lda f:MonsterProp + 1,X
//  STore A to CharStruct::MonsterAttack,Y
//         lda f:MonsterProp + 2,X
//  STore A to CharStruct::MonsterM,Y
//         lda f:MonsterProp + 5,X
//  STore A to CharStruct::EquippedMag,Y
//         lda #$01
//  STore A to WasMonsterReleased	;causes stats to be restored later
//  Return To Subroutine
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
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda Level
//  Jump To Subroutine Random_X_A 	;0..Level
//  CoMPare A with #$0B
//         bcs :+
//  Transfer Direct page to aCcumulator          	;<11, 0
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
//  STore A to $0E		;terrain spell slot 0-3
//         lda TerrainType
//  Jump To Subroutine ShiftMultiply_4
//         clc
//         adc $0E
//  Transfer A to X
//         lda f:TerrainAttackTbl,X
//  STore A to TempSpell
//         lda TempSpell	;pointless load?
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// :	lda f:SpecialAbilityAttackProp,X
//  STore A to Temp,Y
//         inx
//         iny
//         cpy #$0008	;copy 8 bytes spell data
//         bne :-
//         stz PartyTargets
//         stz MonsterTargets
//         lda Temp		;targetting byte
//         bne Targetting
//         lda AttackerIndex	;default to attacker
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to PartyTargets
//         bra TargetSet
// Targetting:
//  AND A with #$08	;target enemy by default
//         bne TargetEnemy
//         lda Temp
//  AND A with #$40	;target all
//         bne TargetAllParty
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump To Subroutine Random_X_A 	;0..3 random party
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to PartyTargets
//         bra TargetSet
// TargetAllParty:
//         lda #$F0
//  STore A to PartyTargets
//         bra TargetSet
// TargetEnemy:
//         lda Temp
//  AND A with #$40	;target all
//         bne TargetAllEnemy
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07	;0..7 random monster
//  Jump To Subroutine Random_X_A
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to MonsterTargets
//         bra TargetSet
// TargetAllEnemy:
//         lda #$FF
//  STore A to MonsterTargets
// TargetSet:
//         stz TempAttachedSpell
//         stz TempSkipNaming
//         lda #$01
//  STore A to TempIsEffect
//         jmp CastSpell
}

// Address: _125E
// Command $25 (Hide)
static void commandTable24(void) {
//         ldx AttackerOffset
//         lda CharStruct::Status4,X
//         ora #$01	;hidden
//  STore A to CharStruct::Status4,X
//         lda #$25	;hide ability name
//  Jump To Subroutine GFXCmdAttackNameA
//         lda #$24	;hide ability anim
//  Jump To Subroutine GFXCmdAbilityAnim
//         lda ProcSequence
//  Transfer A to X
//         stz AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         inc UnknownReaction
//  Jump To Subroutine FinishCommandNullTargets
//         lda AttackerIndex
//  STore A to $24
//         lda #$14	;20, size of CharCommands struct
//  STore A to $25
//  Jump To Subroutine Multiply_8bit
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $26
// FindHideCommands:
//         lda CharCommands::ID,X
//  CoMPare A with #$25	;hide command
//         beq Found
//         inx
//         iny
//         cpy #$0004	;4 command slots
//         bne FindHideCommands
//         beq Ret
// Found:	lda #$26	;show command
//  STore A to CharCommands::ID,X
//         lda #$08	;target enemy?
//  STore A to CharCommands::Targetting,X
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
//  AND A with #$FE	;clear hidden
//  STore A to CharStruct::Status4,X
//         lda #$26	;show ability name
//  Jump To Subroutine GFXCmdAttackNameA
//         lda #$25	;show ability anim
//  Jump To Subroutine GFXCmdAbilityAnim
//         lda ProcSequence
//  Transfer A to X
//         stz AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         inc UnknownReaction
//  Jump To Subroutine FinishCommandNullTargets
//         lda AttackerIndex
//  STore A to $24
//         lda #$14	;20, size of CharCommands struct
//  STore A to $25
//  Jump To Subroutine Multiply_8bit
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $26
// FindShowCommands:
//         lda CharCommands::ID,X
//  CoMPare A with #$26	;show command
//         beq Found
//         inx
//         iny
//         cpy #$0004	;4 command slots
//         bne FindShowCommands
//         beq Ret
// Found:
//         lda #$25
//  STore A to CharCommands::ID,X
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
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump To Subroutine Random_X_A		;0..3 random dance
//  STore A to TempDance
//         ldx AttackerOffset
//         lda CharStruct::ArmorProperties,X
//  AND A with #$04		;sword dance up
//         beq DanceCheck
//  Jump To Subroutine Random_0_99
//         lsr
//         bcs NotSwordDance	;50% chance of sword dance
//         lda #$03		;sword dance
//  STore A to TempDance
//         bra DanceCheck
// NotSwordDance:
//  Jump To Subroutine Random_0_99
//         lsr
//         stz TempDance
//         rol TempDance		;50% chance of 0 or 1
// DanceCheck:
//         lda TempDance
//  CoMPare A with #$03		;sword dance
//         beq SwordDance
//  Jump To Subroutine GetTargets
//  Jump To Subroutine CheckRetarget
//  Jump To Subroutine BuildTargetBitmask
//  Jump To Subroutine CheckMultiTarget
//         clc
//         lda TempDance
//         adc #$79		;offset to dance strings
//  STore A to Temp+1		;string id / ability id
//         stz Temp		;string table
//  Jump To Subroutine GFXCmdAttackNameFromTemp
//         lda #$29		;dance anim
//  Jump To Subroutine GFXCmdAbilityAnim
//  Jump To Subroutine SelectCurrentProcSequence
//         lda Temp+1		;ability id
//  Jump To Subroutine CopyROMMagicInfo
//  Jump To Subroutine MagicAtkTypeSingleTarget
//  Jump To Subroutine FinishCommand
//         jmp GFXCmdDamageNumbers
// SwordDance:
//         lda #$7D		;sword dance ability
//  STore A to Temp+1		;string id / ability id
//         stz Temp		;string table
//  Jump To Subroutine GFXCmdAttackNameFromTemp
//         lda #$29		;dance anim
//  Jump To Subroutine GFXCmdAbilityAnim
//         lda ProcSequence
//  Transfer A to X
//         lda #$7F		;do nothing
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//  Jump To Subroutine FinishCommandNullTargets
//  Jump To Subroutine GFXCmdDamageNumbers
//         ldx AttackerOffset
//         lda CharStruct::DamageMod,X
//         ora #$D0		;auto hit, damage*2, M*2
//  STore A to CharStruct::DamageMod,X
//         jmp SimpleFight
}

// Address: _13CE
// Command $2B (Mimic)
static void commandTable2A(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx AttackerOffset
// :	lda SavedAction,Y
//  STore A to CharStruct::ActionFlag,X
//         inx
//         iny
//         cpy #$000A	;copy 10 bytes action data
//         bne :-
//         ldx AttackerOffset
//         lda CharStruct::ActionFlag,X
//  AND A with #$FE	;clear "costs mp" bit
//  STore A to CharStruct::ActionFlag,X
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
//  STore A to TempEffect
// WeaponEffectCommand:	;called here for other weapon effects
//         stz $0E		;hand
//         stz NextGFXQueueSlot
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne :+
//         lda #$80	;left hand
//  STore A to $0E
// :	jsr FindOpenGFXQueueSlot
//         stz GFXQueue::Flag
//         lda #$FC	;exec graphics command
//  STore A to GFXQueue::Cmd
//         lda #$01	;ability/command anim
//  STore A to GFXQueue::Type
//         lda #$04	;fight
//  STore A to GFXQueue::Data1
//         lda $0E		;hand (0 for RH, 80 for LH)
//  STore A to GFXQueue::Data2
//         lda #$7E	;always miss
//  STore A to AtkType
//         stz MultiTarget
//         stz TargetType
//         stz CommandTargetBitmask
//         stz CommandTargetBitmask+1
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
//         lda #$FF
//  STore A to a:wMonsterTargets	;**optimize: wasted bytes
//         stz a:wPartyTargets
//         lda TempEffect
//  STore A to TempSpell
//         lda #$01
//  STore A to TempIsEffect
//  STore A to TempSkipNaming
//         stz TempAttachedSpell
//  Jump To Subroutine CastSpell
//         ldx AttackerOffset
//         lda CharStruct::Command,X
//  CoMPare A with #$0C	;capture/mug
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
//  STore A to MonsterTargets
//         lda CharStruct::PartyTargets,X
//  STore A to PartyTargets
//  Jump To Subroutine CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//  STore A to CharStruct::PartyTargets,X
//         lda MonsterTargets
//  STore A to CharStruct::MonsterTargets,X
//         pha
//  AND A with #$F0
//         lsr
//         lsr
//         lsr
//         lsr
//         ora CharStruct::PartyTargets,X
//  STore A to TempTargetBitmask
//         pla
//  AND A with #$0F
//  A Shift Left
//  A Shift Left
//  A Shift Left
//  A Shift Left
//  STore A to TempTargetBitmask+1
//         lda AttackerIndex
//  Transfer A to X
//         lda f:_d0ed85,X	;size of one character's gear structs
//  Transfer A to X
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
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//         bne :-
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/command animation
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//         stz GFXQueue::Data2,X	;right hand, no msword
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//  Transfer A to X
//         pla
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
//  Jump To Subroutine SelectCurrentProcSequence
//         sty $14
//         stz $12
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::Properties,X
//  AND A with #$02		;command instead of attack
//         beq LH
//         lda RHWeapon::Param3,X
//  CoMPare A with #$55		;this command
//         bne LH
// :	lda RHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes data for 2nd attack
//         bne :-
//         lda #$80
//  STore A to ActionAnimShift	;flag for later anim manipulation
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Cmd,X
//         stz GFXQueue::Type,X
//         stz GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::AtkType,X
//         pha
//         lda ProcSequence
//  Transfer A to X
//         pla
//  STore A to AtkType,X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
// LH:       ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         bne :+
//         jmp Ret
// :Jump To Subroutine SelectCurrentProcSequence
//         sty $12
//         stz $14
//         ldx $0E			;GearStruct offset
// :   	lda LHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//         bne :-
//         ldx $0E			;GearStruct offset
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;command/ability anim
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//         lda #$80		;left hand, no msword
//  STore A to GFXQueue::Data2,X
//         lda ProcSequence
//  Transfer A to X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
//  Jump To Subroutine SelectCurrentProcSequence
//         sty $12
//         stz $14
//         ldx $0E
//         lda LHWeapon::Properties,X
//  AND A with #$02		;command instead of attack
//         beq Ret
//         lda LHWeapon::Param3,X
//  CoMPare A with #$55		;this command
//         bne Ret
// :	lda LHWeapon,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $14
//         lda $14
//  CoMPare A with #$0C		;copy 12 bytes weapon data for 2nd atk
//         bne :-
//         lda ActionAnimShift
//         ora #$40
//  STore A to ActionAnimShift
//         ldx $0E
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//  Jump To Subroutine FindOpenGFXQueueSlot
//         stz GFXQueue::Flag,X
//         stz GFXQueue::Cmd,X
//         stz GFXQueue::Type,X
//         stz GFXQueue::Data1,X
//         stz GFXQueue::Data2,X
//         lda ProcSequence
//  Transfer A to X
//         stz MultiTarget,X
//         stz TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//         inc ProcSequence
//  Jump To Subroutine GFXCmdDamageNumbers
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

// Address: _16AA
static void copyAbilityInfo(void) {
//         pha
//  Jump To Subroutine SelectCurrentProcSequence
//         pla
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         stz $0A
// :	lda f:BattleCmdProp,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//  CoMPare A with #$05     ;copy first 5 bytes
//         bne :-
//         iny          ;skip 4 on destination
//         iny
//         iny
//         iny
// :	lda f:BattleCmdProp,X
//  STore A to AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//  CoMPare A with #$08      ;copy remaining 3 bytes
//         bne :-
//  Return To Subroutine
}

// Address: _16E1
// Displays an ability or command animation
// creates Action $00,FC,01,<A>,00
static void gfXCmdAbilityAnim(void) {
    // pha
    // jsr FindOpenGFXQueueSlot
    // stz GFXQueue::Flag,X
    // lda #$FC	;exec graphics command
    // sta GFXQueue::Cmd,X
    // lda #$01	;ability/command anim
    // sta GFXQueue::Type,X
    // pla
    // sta GFXQueue::Data1,X
    // stz GFXQueue::Data2,X
    // rts
}

// Address: _16FA
// Displays an Attack name from String Table 1
// creates Action $00,FC,04,01,<A>
static void gfxCmdAttackNameA(void) {
    // sta Temp+1
    // lda #$01
    // sta Temp
    // jmp GFXCmdAttackNameFromTemp
}

// Address: _1705
static void magicAtkTypeSingleTarget(void) {
    // lda ProcSequence
    // tax
    // ldy $0C
    // lda AttackInfo::MagicAtkType,Y
    // and #$7F
    // sta AtkType,X
    // stz MultiTarget,X
    // stz TargetType,X
    // rts
}

// Address: _171A
static void magicAtkTypeMultiTarget(void) {
    // lda ProcSequence
    // tax
    // ldy $0C
    // lda AttackInfo::MagicAtkType,Y
    // and #$7F
    // sta AtkType,X
    // lda TempTargetting
    // inc 	;unconditional, so always considered multitarget
    // sta MultiTarget,X
    // lda #$80	;multi target
    // sta TargetType,X
    // rts
}

// Address: _1735
// Copies command targetting to final locations and
// advances ProcSequence
static void finishCommand(void) {
    // lda ProcSequence
    // asl
    // tax
    // lda TempTargetBitmask
    // sta CommandTargetBitmask,X
    // sta TargetBitmask,X
    // lda TempTargetBitmask+1
    // sta CommandTargetBitmask+1,X
    // sta TargetBitmask+1,X
    // inc ProcSequence
    // rts
}

// Address: _1750
// wipes command targetting and advances ProcSequence
static void finishCommandNullTargets(void) {
    // lda ProcSequence
    // asl
    // tax
    // stz CommandTargetBitmask,X
    // stz CommandTargetBitmask+1,X
    // inc ProcSequence
    // rts
}

// Address: _175F
static void getTargets(void) {
    // ldx AttackerOffset
    // lda CharStruct::PartyTargets,X
    // sta PartyTargets
    // lda CharStruct::MonsterTargets,X
    // sta MonsterTargets
    // rts
}

// Address: _176C
static void handleAtbMenu(void) {
//         lda MenuData::MenuOpen
//         bne MenuOpen
//         jmp MenuClosed
// MenuOpen:	;checks if current display info for status/mp matches what's in CharStruct
//         lda DisplayInfo::CurrentChar
//  STore A to CurrentChar
//  Jump To Subroutine CalculateCharOffset
//         longa
//         lda CharStruct::Status1,X	;includes status 2
//  CoMPare A with DisplayInfo::Status1
//         bne Differs
//         lda CharStruct::Status3,X	;includes status 4
//  CoMPare A with DisplayInfo::Status3
//         bne Differs
//         lda CharStruct::CurMP,X
//  CoMPare A with DisplayInfo::CurMP
//         bne Differs
//         shorta0
//         bra Matches
// Differs:	;disable commands as needed, and update displayinfo for menu
//         shorta0
//  Jump To Subroutine CheckDisablingStatus
//         bne Disabled
//  Jump To Subroutine DisableCommandsMagic
//  Jump To Subroutine ApplyBerserkStatus
//         bne Disabled
//         lda #$05		;C1 routine
//  Jump To Subroutine CallC1
//         lda #$06		;C1 routine
//  Jump To Subroutine CallC1
//         longa
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//  STore A to DisplayInfo::Status1
//         lda CharStruct::Status3,X
//  STore A to DisplayInfo::Status3
//         lda CharStruct::CurMP,X
//  STore A to DisplayInfo::CurMP
//         shorta0
//         bra Matches
// Disabled:	;if character has become disabled while their menu is open, close the menu
//         lda DisplayInfo::CurrentChar
//  STore A to MenuCurrentChar
//         lda GearChanged
//         beq :+
//         stz GearChanged
//  Jump To Subroutine ReplaceHands
//  Jump To Subroutine ApplyGear
// :	lda DisplayInfo::CurrentChar
//  STore A to MenuCurrentChar
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu
//         lda #$01	;C1 routine: close menu
//  Jump To Subroutine CallC1
// WaitMenu:
//         lda MenuDataC1::MenuOpen
//         bne WaitMenu	;ends up 0 eventually? via interrupts?
//         lda #$FF
//  STore A to DisplayInfo::CurrentChar
//  Return To Subroutine
// Matches:	;data either already matched or has been updated
//         lda ControllingA
//         beq Ret
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//         lda ControlTarget,X
//         beq :+
//  Transfer A to X
//         lda ActiveParticipants,X
//         bne Ret
// :	lda DisplayInfo::CurrentChar
//  STore A to MenuCurrentChar
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu2
//         lda #$01	;C1 routine: close menu
//  Jump To Subroutine CallC1
// WaitMenu2:
//         lda MenuDataC1::MenuOpen
//         bne WaitMenu2	;ends up 0 eventually? via interrupts?
//         lda #$80
//  STore A to MenuData::ActionFlag
//         stz MenuData::Command
//         stz MenuData::MonsterTargets
//         stz MenuData::PartyTargets
//         stz MenuData::SelectedItem
//         stz MenuData::SecondActionFlag
//         stz MenuData::SecondCommand
//         stz MenuData::SecondMonsterTargets
//         stz MenuData::SecondPartyTargets
//         stz MenuData::SecondSelectedItem
//         bra MenuClosed
// Ret:	rts
// MenuClosed:								;
//         lda DisplayInfo::CurrentChar
//  CoMPare A with #$FF
//         beq NoCurrentChar
//         jmp ProcessMenuCommand
// NoCurrentChar:
//         lda ATBReadyQueue
//  CoMPare A with #$FF
//         bne NextReadyATB
//  Return To Subroutine		;no one else in queue either
// NextReadyATB:	;there's a character in the queue with ATB ready
//         pha
//  Transfer Direct page to aCcumulator
//  Transfer A to X
// AdvanceQueue:	;advances all the queue elements up by one, there's a terminator $FF in the 5th slot
//         lda ATBReadyQueue+1,X
//  STore A to ATBReadyQueue,X
//         inx
//         cpx #$0004
//         bne AdvanceQueue
//         dec ATBReadyCount
//         pla
//  STore A to MenuCurrentChar
//  STore A to DisplayInfo::CurrentChar
//  Jump To Subroutine CalculateCharOffset
//         lda QuickTurns
//         beq DontStopTime
//         lda DisplayInfo::CurrentChar
//  CoMPare A with QuickCharIndex
//         beq DontStopTime
//  Jump To Subroutine GetTimerOffset  	;sets Y to Timer offset
//         lda CurrentTimer::ATB,Y
//         bne FinishEarly	;check if frozen char's ATB is ready
//         lda #$01		;increase ATB to 1 (no longer ready)
//  STore A to CurrentTimer::ATB,Y
//  STore A to EnableTimer::ATB,Y
//         bra FinishEarly
// DontStopTime:
//  Jump To Subroutine CheckDisablingStatus
//         beq NotDisabled
// FinishEarly:
//         lda #$FF
//  STore A to DisplayInfo::CurrentChar
//  Return To Subroutine
// NotDisabled:	;character's turn has just come up
//         stz MenuCurrentChar+1
//  Jump To Subroutine ApplyBerserkStatus
//         bne FinishEarly
//  Jump To Subroutine DisableCommandsMagic
//         lda #$01
//  STore A to ATBWaiting
//         lda ATBWaitTime
//  STore A to ATBWaitLeft
//         longa
//         ldx AttackerOffset
//         lda CharStruct::Status1,X	;includes 2
//  STore A to DisplayInfo::Status1
//         lda CharStruct::Status3,X	;includes 4
//  STore A to DisplayInfo::Status3
//         lda CharStruct::CurMP,X
//  STore A to DisplayInfo::CurMP
//         stz CharStruct::CmdStatus,X	;also damagemod
//         shorta0
//  Jump To Subroutine CheckControlTargetActive
//         lda #$01
//  STore A to FleeTickerActive	;can't start running until first atb
//         lda EncounterInfo::IntroFX
//         bpl NoCredits
//         stz MenuData::MenuOpen
//  Return To Subroutine
// NoCredits:
//         lda DisplayInfo::CurrentChar
//  Jump To Subroutine GetTimerOffset	;Y = Timer offset
//         lda EnableTimer::ATB,Y
//         beq TimerOff
//         lda #$FF
//  STore A to DisplayInfo::CurrentChar
//         jmp NoCurrentChar
// TimerOff:
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine CallC1 	;C1 routine $00: open menu
// WaitMenu3:
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu3
//  Return To Subroutine
// ProcessMenuCommand:
//         stz ATBWaiting
//  Jump To Subroutine ProcessMenuCommandData
//         lda #$FF	;no current char
//  STore A to DisplayInfo::CurrentChar
//  Return To Subroutine
}

// Address: _190B
// Sets ControllingA and B variables to 1
// if control target is valid and active, 0 otherwise
// Logic is a bit strange but doesn't seem like
// they can ever be set to different values
static void checkControlTargetActive(void) {
//     stz ControllingA
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//         lda ControlTarget,X
//         beq Finish
//  Transfer A to Y
//         lda ActiveParticipants,Y
//         beq Finish
//         lda #$01
//  STore A to ControllingA
// Finish:	sta ControllingB
//  Return To Subroutine
}

// Address: _1926
// copies command data from MenuData struct into CharStruct,
// and performs any other necessary processing
// Also handles gear changes, removing control when needed,
// consuming items when used, and action delays
static void processMenuCommandData(void) {
//         lda EncounterInfo::IntroFX
//         bpl :+		;check for credits demo
//  Jump To Subroutine SetupCreditsDemo
// :	lda DisplayInfo::CurrentChar
//  STore A to CurrentChar
//         lda GearChanged
//         beq :+
//         stz GearChanged
//  Jump To Subroutine ReplaceHands
//  Jump To Subroutine ApplyGear
// :	lda DisplayInfo::CurrentChar
//  Jump To Subroutine CalculateCharOffset
//         lda CharStruct::Status1,X
//  AND A with #$C0	;dead/stone
//         bne ClearControl
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$78	;sleep/para/charm/berserk
//         bne ClearControl
//         lda CharStruct::Status3,X
//  AND A with #$10	;stop
//         bne ClearControl
//         lda CharStruct::Status4,X
//  AND A with #$80	;erased
//         beq :+
// ClearControl:
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//         stz ControlTarget,X
//         bra ClearMenuData
// :	lda DisplayInfo::CurrentChar
//  CoMPare A with MenuData::CurrentChar
//         beq :+
//         lda EncounterInfo::IntroFX
//         bmi :+		;branch if credits fight
//         lda #$0D	;C1 Routine
//  Jump To Subroutine CallC1
// WaitForever:
//         bra WaitForever	;infinite loop?
// :	lda DisplayInfo::CurrentChar
//  Transfer A to X
//         lda ControlTarget,X
//         beq NoControlTarget
//  Transfer A to Y
//         lda ActiveParticipants,Y
//         beq ClearMenuData
//         inc ControlCommand,X
//         sec
//         lda ControlTarget,X
//         sbc #$04
//  STore A to $0E		;monster index of control target
//  Transfer A to Y
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//         clc
//         lda f:_d0eedb,X	;size of CharControl struct
//         adc MenuData::SelectedItem	;action 0-3
//  Transfer A to X
//         lda CharControl::Actions,X
//  STore A to MonsterControlActions,Y
//         sec
//         lda $0E
//  A Shift Left
//  Transfer A to X
//         lda MenuData::PartyTargets
//  STore A to ForcedTarget::Party,X
//         lda MenuData::MonsterTargets
//  STore A to ForcedTarget::Monster,X
// ClearMenuData:
//         lda #$80
//  STore A to MenuData::ActionFlag
//         stz MenuData::Command
//         stz MenuData::MonsterTargets
//         stz MenuData::PartyTargets
//         stz MenuData::SelectedItem
//         stz MenuData::SecondActionFlag
//         stz MenuData::SecondCommand
//         stz MenuData::SecondMonsterTargets
//         stz MenuData::SecondPartyTargets
//         stz MenuData::SecondSelectedItem
//         bra CopyCommands
// NoControlTarget:
//         lda ControllingB
//         bne ClearMenuData	;controlling with no target
// CopyCommands:
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//         stx $2A
//         ldx #$028A   	;650, size of CharSpells struct
//         stx $2C
//  Jump To Subroutine Multiply_16bit	;not using the rom *650 table?
//         longa
//         clc
//         lda $2E		;CurrentChar * 650
//         adc #$2D34   	;CharSpells struct location
//  STore A to TempSpellOffset
//         shorta0
//         ldx AttackerOffset
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$18	;charm/berserk
//         bne CheckCommand
//         lda MenuData::Command
//  STore A to CharStruct::Command,X
//         lda MenuData::MonsterTargets
//  STore A to CharStruct::MonsterTargets,X
//         lda MenuData::PartyTargets
//  STore A to CharStruct::PartyTargets,X
//         lda MenuData::SelectedItem
//  STore A to CharStruct::SelectedItem,X
//         lda MenuData::ActionFlag
//  STore A to CharStruct::ActionFlag,X
//  AND A with #$20	;magic
//         beq NotXMagic
//         lda MenuData::SelectedItem
//  Transfer A to Y
//         lda (TempSpellOffset),Y
//  STore A to CharStruct::SelectedItem,X
//         lda MenuData::ActionFlag
//  AND A with #$08	;x-magic
//         beq NotXMagic
//         lda MenuData::SecondCommand
//  STore A to CharStruct::SecondCommand,X
//         lda MenuData::SecondMonsterTargets
//  STore A to CharStruct::SecondMonsterTargets,X
//         lda MenuData::SecondPartyTargets
//  STore A to CharStruct::SecondPartyTargets,X
//         lda MenuData::SecondSelectedItem
//  Transfer A to Y
//         lda (TempSpellOffset),Y
//  STore A to CharStruct::SecondSelectedItem,X
//         lda MenuData::SecondActionFlag
//  STore A to CharStruct::SecondActionFlag,X
//         bra CheckCommand
// NotXMagic:
//         stz CharStruct::SecondCommand,X
//         stz CharStruct::SecondMonsterTargets,X
//         stz CharStruct::SecondMonsterTargets,X	;**bug: PartyTargets
//         stz CharStruct::SecondSelectedItem,X
//         stz CharStruct::SecondActionFlag,X
// CheckCommand:
//         lda MenuData::Command
//  STore A to $24
//         lda #$08
//  STore A to $25
//  Jump To Subroutine Multiply_8bit
//         ldx $26		;command * 8
//         ldy AttackerOffset
//         lda f:BattleCmdProp+2,X
//  STore A to CharStruct::CmdStatus,Y
//         lda f:BattleCmdProp+3,X
//  STore A to CharStruct::DamageMod,Y
//         lda MenuData::Command
//  CoMPare A with #$2C	;first magic command
//         bcc NotMagicCommand
//  CoMPare A with #$4E	;after last magic command
//         bcs NotMagicCommand
//         lda CharStruct::ActionFlag,Y
//         ora #$01     	;costs MP
//  STore A to CharStruct::ActionFlag,Y
// NotMagicCommand:
//         lda MenuData::Command
//  Transfer A to X
//         lda f:BattleCmdDelay,X
//         bmi CalculateDelay
//         pha
//         lda MenuData::Command
//  CoMPare A with #$11	;throw
//         beq Item
//  CoMPare A with #$20	;drink
//         beq Item
//  CoMPare A with #$1F	;mix
//         bne NotItem
// Mix:
//         lda MenuData::SecondSelectedItem
//         pha
//  Transfer A to X
//         lda InventoryItems,X
//         ldx AttackerOffset
//  STore A to CharStruct::SecondSelectedItem,X
//         pla
//  Jump To Subroutine ConsumeItem
// Item:
//         lda MenuData::SelectedItem
//         pha
//  Transfer A to X
//         lda InventoryItems,X
//         ldx AttackerOffset
//  STore A to CharStruct::SelectedItem,X
//         pla
//  Jump To Subroutine ConsumeItem
// NotItem:
//         pla
//         jmp Finish
// CalculateDelay:
//         lda MenuData::ActionFlag
//  AND A with #$08	;XMagic
//         beq :+
//         jmp MagicDelay
// :	lda MenuData::ActionFlag
//  AND A with #$40	;Item
//         bne ItemDelay
//         lda MenuData::ActionFlag
//  AND A with #$20	;Magic
//         beq :+
//         jmp MagicDelay
// :	lda MenuData::ActionFlag
//  AND A with #$10	;Weapon used as item
//         beq WeaponAttackDelay
//         jmp WeaponUseDelay
// WeaponAttackDelay:	;despite the calculation, I don't think any weapons have delay values
//         stz $0E
//         lda DisplayInfo::CurrentChar
//  STore A to $24
//         lda #$54     ;84, size of GearStats struct
//  STore A to $25
//  Jump To Subroutine Multiply_8bit
//         ldy $26
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         beq :+
//         lda RHWeapon::Targetting,Y
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//  STore A to $0E		;attack delay
// :       ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         beq :+
//         lda LHWeapon,Y
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         clc
//         lda f:AttackDelayTbl,X
//         adc $0E		;add other weapon's delay
//  STore A to $0E
// :	lda $0E		;attack delay
//         jmp Finish
// ItemDelay:
//         lda MenuData::SelectedItem
//  Transfer A to X
//         lda InventoryItems,X
//         ldx AttackerOffset
//  STore A to CharStruct::SelectedItem,X
//         sec
//         sbc #$E0	;consumable item offset
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         lda f:ConsumableItemProp+2,X
//  AND A with #$08
//         bne :+
//         lda MenuData::SelectedItem
//  Jump To Subroutine ConsumeItem
// :	lda f:ConsumableItemProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//         bra Finish
// MagicDelay:
//         stz $0E
//         lda MenuData::SelectedItem
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         lda f:AttackProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//  STore A to $0E		;attack delay
//         lda MenuData::ActionFlag
//  AND A with #$08	;X-Magic
//         beq FinishMagic
//         lda MenuData::SecondSelectedItem
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         lda f:AttackProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         clc
//         lda f:AttackDelayTbl,X
//         adc $0E		;add other spell's delay
//  STore A to $0E
// FinishMagic:
//         lda $0E		;attack delay
//         bra Finish
// WeaponUseDelay:
//         lda DisplayInfo::CurrentChar
//  STore A to $24
//         lda #$54     	;84, size of GearStats struct
//  STore A to $25
//  Jump To Subroutine Multiply_8bit
//         ldy $26
//         lda MenuData::SelectedItem
//         beq :+
//         longa
//  Transfer Y to A
//         clc
//         adc #$000C	;shifts offset from RHWeapon to LHWeapon
//  Transfer A to Y
//         shorta0
// :	lda RHWeapon::ItemMagic,Y	;could be LHWeapon
//  AND A with #$7F	;weapon magic to cast
//         beq Finish
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         lda f:AttackProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
// Finish:
//         pha
//         lda DisplayInfo::CurrentChar
//  Jump To Subroutine GetTimerOffset	;Y and $36 = timer offset
//         ldx AttackerOffset
//         pla
//  Jump To Subroutine HasteSlowMod	;adjusts delay
//  STore A to CurrentTimer::ATB,Y	;time until action fires
//         lda #$41		;flag indicating a queued action
//  STore A to EnableTimer::ATB,Y
//         lda #$80		;physical/other
//  STore A to MenuData::ActionFlag
//         stz MenuData::Command
//         stz MenuData::CurrentChar
//         stz MenuData::MonsterTargets
//         stz MenuData::PartyTargets
//         stz MenuData::SelectedItem
//         stz MenuData+7
//         stz MenuData::SecondActionFlag
//         stz MenuData::SecondCommand
//         stz MenuData+10
//         stz MenuData::SecondMonsterTargets
//         stz MenuData::SecondPartyTargets
//         stz MenuData::SecondSelectedItem
//  Return To Subroutine
}

// Address: _1C36
// subtracts 1 from item quantity of item in A
// blanks out inventory slot if qty is now 0
static void consumeItem(void) {
    // tax
    // lda InventoryQuantities,X
    // dec
    // sta InventoryQuantities,X
    // bne Ret
    // stz InventoryItems,X
    // stz InventoryTargetting,X
    // lda #$5A
    // sta InventoryFlags,X
    // lda #$AA
    // sta InventoryUsable,X
    // rts
}

// Address: _1C51
// Initializes some values when a
// battle during the credits happens
// This range is used by C1 graphics code but
// unsure what it does
static void setupCreditsDemo(void) {
    // lda #$80	;physical/other
    // sta MenuData::ActionFlag
    // sta MenuData::MonsterTargets
    // lda #$54	;job-specific animation (credits)
    // sta MenuData::Command
    // stz MenuData::PartyTargets
    // stz MenuData::SelectedItem
    // stz MenuData::SecondActionFlag
    // stz MenuData::SecondCommand
    // stz MenuData::SecondMonsterTargets
    // stz MenuData::SecondPartyTargets
    // stz MenuData::SecondSelectedItem
    // rts
}

// Address: _1C74
// Returns >0 if
// character has a status that
// prevents them from taking Action
static void checkDisablingStatus(void) (
    // ldx AttackerOffset
    // lda CharStruct::Status1,X
    // ora CharStruct::AlwaysStatus1,X
    // and #$C2   	;dead/stone/zombie
    // bne Ret
    // lda CharStruct::Status2,X
    // ora CharStruct::AlwaysStatus2,X
    // and #$78   	;sleep/para/Charm/Berserk
    // bne Ret
    // lda CharStruct::Status3,X
    // and #$10   	;stop
    // bne Ret
    // lda CharStruct::Status4,X
    // and #$84   	;erased/singing
    // bne Ret
    // tdc
    // rts
)

// Address: _1C9A
// Make Berserk ability have Berserk Status
static void applyBerserkStatus(void) {
//         ldx AttackerOffset
//         lda CharStruct::Passives2,X
//  AND A with #$08   	;berserk
//         beq Finish
//         lda EncounterInfo::IntroFX
//         bpl NotCredits
// Finish:	tdc
//  Return To Subroutine
//         								;
// NotCredits:
//         lda CharStruct::AlwaysStatus2,X
//         ora #$08   	;berserk
//  STore A to CharStruct::AlwaysStatus2,X
//  Return To Subroutine
}

// Address: _1CB3
// Disables Magic and Commands when
// Status or MP prevents their use
static void disableCommandsMagic(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $16
//         lda Void
//  AND A with #$40     	;void
//         beq :+
//         ldx #$0080
//         stx $16		;disables magic
// :	lda DisplayInfo::CurrentChar
//  Jump To Subroutine CalculateSpellOffset	;sets Y
//         longa
//  Transfer Direct page to aCcumulator
//  STore A to $12
//  STore A to $14
//         ldx AttackerOffset
//         lda CharStruct::CurMP,X
//  STore A to $0E		;current mp
//         lda CharStruct::Status3,X
//         ora CharStruct::AlwaysStatus3,X
//  STore A to $22		;status 3/4
//         lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//  STore A to $10		;status 1/2
//  AND A with #$0400	;mute
//         beq :+
//         lda #$0080
//  STore A to $12		;disables magic
// :	lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//  AND A with #$0020	;toad
//         beq :+
//         lda #$0080
//  STore A to $14		;disables magic
// :	tdc
//  Transfer A to X
// DisableSpells:
//         lda CharSpells::Flags,Y
//  AND A with #$0001	;skip mp/status checks
//         bne NextSpell
//         lda CharSpells::MP,Y
//  AND A with #$00FF	;clear high part since it's an 8 bit field
//  CoMPare A with $0E		;current mp
//         beq CheckStatus
//         bcc CheckStatus
//         lda CharSpells::Flags,Y
//         ora #$0080
//  STore A to CharSpells::Flags,Y
//         bra NextSpell
// CheckStatus:
//         lda CharSpells::Flags,Y
//  AND A with #$FF7F	;clear bit 80h in flags, disabled bit?
//  STore A to CharSpells::Flags,Y
//         lda CharSpells::ID,Y
//  AND A with #$00FF
//  CoMPare A with #$0080	;blue magic
//         bcs NextSpell
//         lda CharSpells::Flags,Y
//         ora $12		;from mute
//         ora $14		;from toad
//         ora $16		;from void
//  STore A to CharSpells::Flags,Y
//         lda $16
//         bne NextSpell
//         lda $12
//         bne NextSpell
//         lda $14
//         beq NextSpell
//         lda CharSpells::ID,Y
//  AND A with #$00FF
//  CoMPare A with #$0029	;toad spell
//         bne NextSpell
//         lda CharSpells::Flags,Y
//  AND A with #$FF7F	;re-enable toad spell if toad status
//  STore A to CharSpells::Flags,Y
// NextSpell:
//         iny
//         inx
//         cpx #$0082	;130 spell slots
//         bne DisableSpells
//         shorta0
//         lda DisplayInfo::CurrentChar
//  STore A to $24
//         lda #$14	;20, size of CharCommands struct
//  STore A to $25
//  Jump To Subroutine Multiply_8bit
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $0E
//         ldy $26
//         longa
// DisableCommands:
//         lda CharCommands::ID,Y
//  AND A with #$00FF
//  STore A to $12		;command id
//         beq DisableCommand
//  A Shift Left
//  Transfer A to X
//         lda f:BattleCmdDisableStatus,X
//  AND A with $10		;status 1/2
//         bne DisableCommand
//         lda $12		;command id
//  CoMPare A with #$0026	;show command
//         beq EnableCommand
//         lda $22		;status 3/4
//  AND A with #$0100	;hidden
//         beq EnableCommand
// DisableCommand:
//         lda CharCommands::Flags,Y
//         ora #$0080	;disabled
//  STore A to CharCommands::Flags,Y
//         bra NextCommand
// EnableCommand:
//         lda CharCommands::Flags,Y
//  AND A with #$FF7F	;enabled
//  STore A to CharCommands::Flags,Y
// NextCommand:
//         iny
//         inc $0E		;character index
//         lda $0E
//  CoMPare A with #$0004	;4 commands per character
//         bne DisableCommands
//         shorta0
//  Return To Subroutine
}

// Address: _1DC4
// Manage the ATB timer used for
// zombie/charm/berserk party members
// and set up their action when it is ready
//  ** bug: should probably check for death too (this is why berserkers always attack when they get up)
static void handleUncontrolledParty(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $3D		;char index, used in subroutines also
//         stx $3F		;char offset
// Loop:
//         ldx $3D
//         lda UncontrolledATB,X
//         beq ActionReady
//         ldx $3F
//         lda CharStruct::Status3,X
//  AND A with #$10	;stop
//         bne Next
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$60	;sleep/paralyze
//         bne Next
//         ldx $3D
//         dec UncontrolledATB,X
//         bra Next
// ActionReady:
//         ldx $3F		;char offset
//         lda #$01
//  STore A to CharStruct::CmdCancelled,X
//         lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//  AND A with #$02	;zombie
//         beq :+
//  Jump To Subroutine ZombieAction
//         bra Next
// :	lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$10	;charm
//         beq :+
//  Jump To Subroutine CharmAction
//         bra Next
// :	lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$08	;berserk
//         beq Next
//  Jump To Subroutine BerserkAction
// Next:
//         ldx $3F		;char offset
//  Jump To Subroutine NextCharOffset
//         stx $3F
//         inc a:$003D	;char index ; TODO: dont know why this is being done?
//         lda a:$003D
//  CoMPare A with #$04	;4 characters
//         bne Loop
//  Return To Subroutine
}

// Address: _1E2F
// Params
//  - X = Char Offset
//  - $3D = Char index
// Sets up a fight command targetting
// a Random party member
static void zombieAction(void) {
    // lda #$80
    // sta CharStruct::ActionFlag,X
    // lda #$05	;fight
    // sta CharStruct::Command,X
    // stz CharStruct::MonsterTargets,X
    // stz CharStruct::SelectedItem,X
    // stz CharStruct::SecondActionFlag,X
    // stz CharStruct::SecondCommand,X
    // stz CharStruct::SecondMonsterTargets,X
    // stz CharStruct::SecondPartyTargets,X
    // stz CharStruct::SecondSelectedItem,X
    // phx
    // tdc
    // tax
    // lda #$03
    // jsr Random_X_A  ;0..3
    // tax
    // tdc
    // jsr SetBit_X
    // plx
    // sta CharStruct::PartyTargets,X	;fight random party member
    // jmp QueueUncontrolledAction
}

// Addres: _1E62
// Params:
//  - X = Char Offset
//  - $3D = Char index
//  - $3F = Char Offset
// 50% chance:
//  - sets up a fight command targetting a
//    random party member
//	- picks a random known white/black/time spell and
//    casts with inverted targetting
static void charmAction(void) {
//         lda CharStruct::EnableSpells,X
//  AND A with #$0F			;white magic
//         ora CharStruct::EnableSpells+1,X	;black and time magic
//         beq Fight
//  Jump To Subroutine Random_0_99
//  CoMPare A with #$32	;50% chance of spell
//         bcc Magic
// Fight:
//         ldx $3F		;char offset
//         lda #$80
//  STore A to CharStruct::ActionFlag,X
//         lda #$05	;fight
//  STore A to CharStruct::Command,X
//         stz CharStruct::MonsterTargets,X
//         stz CharStruct::SelectedItem,X
//         stz CharStruct::SecondActionFlag,X
//         stz CharStruct::SecondCommand,X
//         stz CharStruct::SecondMonsterTargets,X
//         stz CharStruct::SecondPartyTargets,X
//         stz CharStruct::SecondSelectedItem,X
//         phx
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump To Subroutine Random_X_A    ;0..3
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//         plx
//  STore A to CharStruct::PartyTargets,X	;fight random party member
//         jmp _QueueUncontrolledAction
// Magic:
//         lda $3D		;char index
//  Transfer A to X
//         stx $2A
//         ldx #$028A ; TODO: fixme .sizeof(CharSpells)	;650, size of CharSpells struct
//         stx $2C
//  Jump To Subroutine Multiply_16bit    ;**optimize: use rom table instead
//         ldx $2E
//         stx SpellOffsetRandom
//         stz $0E
// FindAnySpell:		;checks if any spells are learned
//         lda CharSpells::ID+18,X	;starts at first white spell
//  CoMPare A with #$46		;Quick spell
//         beq NextSpell
//  CoMPare A with #$FF		;empty spell slot
//         bne TryRandomSpell
// NextSpell:
//         inx
//         inc $0E
//         lda $0E
//  CoMPare A with #$36
//         bne FindAnySpell
//         bra Fight		;no spells, hit something instead
// TryRandomSpell:
//         ldx #$0012		;first white spell
//         lda #$47		;last time spell
//  Jump To Subroutine Random_X_A  	;random white/black/time spell
//         longa
//         adc SpellOffsetRandom
//  Transfer A to X
//         shorta0
//         lda CharSpells::ID,X
//  CoMPare A with #$FF		;empty spell slot
//         beq TryRandomSpell	;keep trying until we hit a known spell
//  CoMPare A with #$46		;quick spell
//         beq TryRandomSpell	;is no good either
//         pha 			;holds known random spell
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         lda f:AttackProp,X
//  STore A to TempTargetting	;temp area
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         sty $16			;target bits
//         lda TempTargetting
//         bne CheckTargetting
// TargetSelf:
//         longa
//         lda $3F			;Char Offset
//  Jump To Subroutine ShiftDivide_128	;char index (could've just loaded that)
//  Transfer A to X
//         shorta0
//  Jump To Subroutine SetBit_X     	;target self if no targetting info
//  STore A to $16
//         bra TargetReady
// CheckTargetting:
//  AND A with #$40		;hits all
//         bne TargetsAll
//         lda TempTargetting
//  AND A with #$08		;targets enemy by default
//         bne TargetsEnemy
// TargetsOther:			;assumed to normally target party, now targets monsters
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump To Subroutine Random_X_A	     	;random monster 0..7
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to $17			;monster target
//         bra TargetReady
// TargetsEnemy:			;normally targets enemy, now targets party
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump To Subroutine Random_X_A    	;random party 0..3
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump To Subroutine SetBit_X
//  STore A to $16			;party target
//         bra TargetReady
// TargetsAll:
//         lda TempTargetting
//  AND A with #$08		;targets enemy by default
//         bne :+
//         lda #$FF
//  STore A to $17
//         bra TargetReady
// :	lda #$F0		;target all party members
//  STore A to $16
// TargetReady:
//         ldx $3F			;char Offset
//         pla 			;random known spell
//  STore A to CharStruct::SelectedItem,X
//         lda $16			;party targets
//  STore A to CharStruct::PartyTargets,X
//         lda $17			;monster targets
//  STore A to CharStruct::MonsterTargets,X
//         lda #$21		;magic + costs mp
//  STore A to CharStruct::ActionFlag,X
//         lda #$2C		;first magic command
//  STore A to CharStruct::Command,X
//         stz CharStruct::SecondActionFlag,X
//         stz CharStruct::SecondCommand,X
//         stz CharStruct::SecondMonsterTargets,X
//         stz CharStruct::SecondPartyTargets,X
//         stz CharStruct::SecondSelectedItem,X
// _QueueUncontrolledAction:
//         jmp QueueUncontrolledAction
}

// Address: _1F80
// Params:
// - X = Char Offset
// - $3D = Char index
// Sets up a fight command targetting a
// random party member
static void berserkAction(void) {
    // lda #$80
    // sta CharStruct::ActionFlag,X
    // lda #$05	;fight
    // sta CharStruct::Command,X
    // stz CharStruct::PartyTargets,X
    // stz CharStruct::SelectedItem,X
    // stz CharStruct::SecondActionFlag,X
    // stz CharStruct::SecondCommand,X
    // stz CharStruct::SecondMonsterTargets,X
    // stz CharStruct::SecondPartyTargets,X
    // stz CharStruct::SecondSelectedItem,X
    // phx
    // tdc
    // tax
    // lda #$07
    // jsr Random_X_A	;0..7 random monster
    // tax
    // tdc
    // jsr SetBit_X
    // plx
    // sta CharStruct::MonsterTargets,X
    // jmp QueueUncontrolledAction
}

// Param $3D = char index
// Sets character's queued action to fire
// on the next ATB tick, and reset their
// uncontrolled ATB for their next turn
static void queueUncontrolledAction(void) {
    //     lda $3D		;char index
    //     jsr ResetATB   	;also sets Y = timer offset
    //     lda $3D
    //     tax
    //     lda CurrentTimer::ATB,Y
    //     cmp #$7F
    //     bcc :+
    //     lda #$7F	;max ATB 127
    // :   sta UncontrolledATB,X
    //     lda #$01	;action on next ATB tick
    //     sta CurrentTimer::ATB,Y
    //     lda #$41    	;waiting for delayed action
    //     sta EnableTimer::ATB,Y
    //     rts
}

// Address: _1FD2
// Randomizes a table of combatant numbers,
// also initializes global timers
static void randomizeOrder(void) {
//         lda CurrentlyReacting
//         bne :+
//  Jump To Subroutine GlobalTimers
// :	   tdc
//  Transfer A to X
//         dec
//         									;:
// :	sta RandomOrder,X
//         inx
//         cpx #$000C
//         bne :-
//         									;.
//  Transfer Direct page to aCcumulator
//  Transfer A to Y 			;slot for writing
// _RandomizeOrder:
//  Transfer Direct page to aCcumulator
//  Transfer A to X 			;slot for reading
//         lda #$0B
//  Jump To Subroutine Random_X_A		;0..11
//  STore A to $0E
//         ldx #$0000
//         									;:
// CheckValueInUse:		;see if we've used this number yet
//         lda $0E
//  CoMPare A with RandomOrder,X
//         beq _Next		;already used, try another
//         inx
//         cpx #$000C
//         bne CheckValueInUse
//         									;.
//  STore A to RandomOrder,Y	;if not, save it
//         iny 			;and select next writing slot
//         									;:
//  _Next:
//         cpy #$000C		;12 combatant slots
//         bne _RandomizeOrder
//         									;.
//  Return To Subroutine
}

// Address: _200B
// Updates Status/ATB timers for all combatants
// may skip updates depending on stop/etc.
static void updateTimers(void) {
//  Jump To Subroutine GlobalTimers
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $0A     		;char index
// Loop:	tdc
//  Transfer A to Y
//         sty $0C     		;timer index
//         lda $0A
//  Jump To Subroutine GetTimerOffset
//         tyx 			;X = Timer Offset
//         ldy $0A
//         lda ActiveParticipants,Y
//         beq NextChar
//         lda PauseTimerChecks,Y
//         bne NextChar
//         lda CurrentlyReacting
//         bne :+
//         lda QuickTimeFrozen,Y
//         bne NextChar
// :Jump To Subroutine UpdateTimer 	;first timer is stop
//         lda $08			;check if stop active
//         bne NextChar  		;don't process other timers if stopped
//         ldy #$0008  		;process 8 more status timers
// :Jump To Subroutine UpdateTimer
//         dey
//         bne :-
//  Jump To Subroutine UpdateTimer 	;one more status timer (paralyze)
//         lda $08			;check if paralyze active
//         bne NextChar
//  Jump To Subroutine UpdateTimer  	;advance ATB timer if not paralyzed
// NextChar:
//         inc $0A     		;next char index
//         lda $0A
//  CoMPare A with #$0C		;12 combatants
//         bne Loop
//  Return To Subroutine
}

// Advances a status/atb timer if
// that status is supposed to be checked this tick
// sets up for the next call to check the next timer
// Params: 
//  - $0C = timer index
//  - X = timer offset
// Output: $08 = timer triggered
static void updateTimer(void) {
//         stz $08    	;timer triggered flag
//         phy
//         ldy $0C		;timer index
//         lda ProcessTimer,Y	;should process this timer this tick?
//         beq Finish
//         cpy #$000A	;ProcessTimer::ATB
//         beq :+
//         lda CurrentlyReacting
//         bne Finish
// :	lda EnableTimer,X	;is it enabled?
//         beq Finish
//         bmi TimerActive  	;check the 80h timer flag
//         lda CurrentTimer,X
//         beq FlagTimer
//         dec CurrentTimer,X
//         lda CurrentTimer,X
//         bne TimerActive
// FlagTimer:		;flag EnableTimer when CurrentTimer hits 0
//         lda EnableTimer,X
//         ora #$81
//  STore A to EnableTimer,X
// TimerActive:
//         lda $0C
//         bne :+		;doesn't branch anywhere regardless
// :       inc $08    	;timer triggered flag
// Finish:
//         ply 		;restore original Y
//         inx 		;next timer (in offset)
//         inc $0C		;next timer index
//  Return To Subroutine
}

// Decreases global status timers,
// then flags and reset those that trigger
// sets ProcessTimer to indicate that status
// should be updated this tick
static void globalTimers(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
// DecTimer:
//         lda GlobalTimer,X
//         beq Triggered
//         dec GlobalTimer,X
//         stz ProcessTimer,X
//         bra :+
// Triggered:
//         lda #$01
//  STore A to ProcessTimer,X		;flag timer for processing
//         lda f:TimerDurTbl,X		;reset timer from rom
//  STore A to GlobalTimer,X
//         							;:
// :	inx
//         cpx #$000B			;11 timers
//         bne DecTimer
//  Return To Subroutine
}

// Attempts to find one character for
// each timer for whom that timer has ended
// (EnableTimer bit 80h)
// Check is in a fixed random order that's
// set up at battle init
// but subsequent runs will continue after
// the last character checked for each timer so
// it's somewhat fair
static void findEndedTimers(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $08			;timer index
//  Transfer A to Y
// :	sta TimerEnded,Y
//         iny
//         cpy #$000B
//         bne :-
// TimerLoop:	;for each timer, loop finds the first character for whom that timer ended, checking in a "random" order
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $0A			;char count
//         ldx $08			;timer index
//         lda RandomOrderIndex,X
//         pha 			;original RandomOrderIndex
// CharLoop:	;searches characters in a "random" order
//         ldx $08			;timer index
//         lda RandomOrderIndex,X
//  Transfer A to X
//         lda RandomOrder,X
//  STore A to $0C			;char index
//  Transfer A to X
//         lda PauseTimerChecks,X
//         bne NextChar
//         lda CurrentlyReacting
//         bne :+
//         lda QuickTimeFrozen,X
//         bne NextChar
// :	lda $0C			;char index
//  Jump To Subroutine GetTimerOffset      ;Y = Timer Offset
//  Transfer Y to A
//         clc
//         adc $08
//  Transfer A to X 			;timer offset + index
//         lda EnableTimer,X
//         bpl NextChar		;80h must be set to contiue
//         lda $0C
//  Transfer A to Y
//         lda ActiveParticipants,Y
//         beq NextChar
//         lda $08			;timer index
//  CoMPare A with #$01		;poison
//         beq PoisonCountRegen
//  CoMPare A with #$03		;countdown
//         beq PoisonCountRegen
//  CoMPare A with #$07		;regen
//         bne EndTimer
// PoisonCountRegen:	;skips ending timer for these status if they're also erased/hidden/jumping
//         phx 		;timer offset + index
//         ldx $08
//         lda RandomOrderIndex,X
//  Transfer A to X
//         lda RandomOrder,X
//         longa
//  Jump To Subroutine ShiftMultiply_128
//  Transfer A to X
//         shorta0
//         lda CharStruct::Status4,X
//  AND A with #$81	;erased or hidden
//         bne NextCharPLX
//         lda CharStruct::CmdStatus,X
//  AND A with #$10	;jumping
//         beq EndTimerPLX
// NextCharPLX:
//         plx
//         bra NextChar
// EndTimerPLX:
//         plx 		;timer offset + index
// EndTimer:		;sets flag that timer has ended, so effects can be applied later
//         pla
//         lda EnableTimer,X
//  AND A with #$7E	;clear $81
//  STore A to EnableTimer,X
//         ldx $08		;timer index
//         phx
//         lda #$01	;flag that we found someone timer ended for
//  STore A to TimerEnded,X
//         lda RandomOrderIndex,X
//  Transfer A to X
//         lda RandomOrder,X
//         plx 		;timer index
//  STore A to TimerReadyChar,X	;which character had their timer end
//         bra NextTimer	;don't check any more characters for this timer
// NextChar:	;this character's timer didn't end or isn't eligable,
//         	;keep looking until all have been checked or one is found
//         ldx $08		;timer index
//         inc RandomOrderIndex,X
//         lda RandomOrderIndex,X
//  CoMPare A with #$0C	;reset index at 12
//         bne :+
//         stz RandomOrderIndex,X
// :       inc $0A        	;char count
//         lda $0A
//  CoMPare A with #$0C	;12 chars
//         beq :+
//         jmp CharLoop
// :       pla 		;original RandomOrderIndex
//  STore A to RandomOrderIndex,X
// NextTimer:
//         inc $08        	;next timer index
//         lda $08
//  CoMPare A with #$0B	;11 timers
//         beq Ret
//         jmp TimerLoop
// Ret:	rts
}

static void applyTimerEffects(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx ProcessingTimer
// Loop:
//         ldx ProcessingTimer
//         lda TimerEnded,X
//         beq NextTimer
//         inc RandomOrderIndex,X
//         lda RandomOrderIndex,X
//  CoMPare A with #$0C		;12 chars
//         bne :+
//         stz RandomOrderIndex,X
// :	    lda TimerReadyChar,X
//  Jump To Subroutine GetTimerOffset    	;sets Y to timer offset
//         lda TimerReadyChar,X
//  Jump To Subroutine CalculateCharOffset
//         lda ProcessingTimer
//         beq TimerEffect    	;timer 0 is stop, skips below check
//         lda EnableTimer,Y	;bits 80h and 01 are cleared prev
//         bne NextTimer    	;skip effect if any other bits set
// TimerEffect:
//  Jump To Subroutine DispatchTimerEffect
// NextTimer:
//         inc ProcessingTimer
//         lda ProcessingTimer
//  CoMPare A with #$0B		;11 timers
//         bne Loop
//  Return To Subroutine
}

// Uses a jump table to call an
// appropriate timer effect routine
// Params:
// - Y = timer offset (used in the effect routines)
static void dispatchTimerEffect(void) {
    // lda ProcessingTimer
    // asl
    // tax
    // lda f:TimerEffectJumpTable,X
    // sta $08
    // lda f:TimerEffectJumpTable+1,X
    // sta $09
    // lda #$c2 ; Load from bank C2
    // sta $0A
    // jml [$0008]

    // TimerEffectJumpTable
    // .word $21E3, $21EE, $222A, $2235, $224E, $2259, $2264, $22AD, $2319, $237C, $238F
}

// Address: _21E3
static void timerEffectStop(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status3,X
    // and #$EF	;clear stop
    // sta CharStruct::Status3,X
    // rts
}

// Address: _21EE
static void timerEffectPoison(void) {
//         lda #$01
//  STore A to EnableTimer::Poison,Y
//         lda InitialTimer::Poison,Y
//  STore A to CurrentTimer::Poison,Y
//  Jump To Subroutine WipeDisplayStructures
//         longa
//         ldx AttackerOffset
//         lda CharStruct::MaxHP,X
//  Jump To Subroutine ShiftDivide_16
//         bne :+
//         inc 				;min 1 damage
// :	sta $0E				;poison tick damage
//         sec
//         lda CharStruct::CurHP,X
//         sbc $0E				;poison tick damage
//         bcs :+
//  Transfer Direct page to aCcumulator 				;min 0 hp
// :	sta CharStruct::CurHP,X
//         shorta0
//         lda TimerReadyChar::Poison
//         ldx $0E				;poison tick damage
//         stx TempDisplayDamage
//  Jump To Subroutine CopyDisplayDamage
//         lda #$09	;C1 routine: display regen/poison damage
//         jmp CallC1
}

static void timerEffectReflect(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status3,X
    // and #$7F	;clear reflect
    // sta CharStruct::Status3,X
    // rts
}

static void timerEffectCountdown(void) {
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//  AND A with #$02	;zombie
//         bne Ret
//         lda TimerReadyChar::Countdown
//  Jump To Subroutine KillCharacter
//         lda MonsterDead
//         beq Ret
//         lda #$07	;C1 routine: condemn death animation
//  Jump To Subroutine CallC1
// Ret:	   rts
}

static void timerEffectMute(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status2,X
    // and #$FB	;clear mute
    // sta CharStruct::Status2,X
    // rts
}

static void timerEffectHPLeak(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status4,X
    // and #$F7	;clear hp leak
    // sta CharStruct::Status4,X
    // rts
}

static void timerEffectOld(void) {
//         lda #$01
//  STore A to EnableTimer::Old,Y
//         lda InitialTimer::Old,Y
//  STore A to CurrentTimer::Old,Y
//         ldx AttackerOffset
//         stz $0E
// StatsLoop:		;applies to all 4 main stats
//         lda CharStruct::BaseStr,X
//         dec
//         beq :+		;**bug: wraps 0 stats to 255
//  STore A to CharStruct::BaseStr,X
// :	lda CharStruct::EquippedStr,X
//         dec
//         beq :+
//  STore A to CharStruct::EquippedStr,X
// :	inx
//         inc $0E
//         lda $0E
//  CoMPare A with #$04	;4 stats
//         bne StatsLoop
//         ldx ProcessingTimer
//         lda TimerReadyChar,X
//  CoMPare A with #$04	;monster check
//         bcc Ret
//         ldx AttackerOffset
//         lda CharStruct::Level,X
//         dec
//         beq :+
//  STore A to CharStruct::Level,X
// :	lda CharStruct::MonsterAttack,X
//         dec
//         bpl Ret	;bug? only decreases attack if above 128
//  STore A to CharStruct::MonsterAttack,X
// Ret:	rts
}

static void timerEffectRegen(void) {
//         lda #$01
//  STore A to EnableTimer::Regen,Y
//         lda InitialTimer::Regen,Y
//  CoMPare A with #$1E
//         bcs :+
//         lda #$1E	;max 30 ticks if it was slower
//  STore A to InitialTimer::Regen,Y
// :	sta CurrentTimer::Regen,Y
//  Jump To Subroutine WipeDisplayStructures
//         ldx AttackerOffset
//  Jump To Subroutine CopyStatsWithBonuses
//         lda Level
//  STore A to $24
//         lda Vitality
//  STore A to $25
//  Jump To Subroutine Multiply_8bit
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//  AND A with #$02	;zombie
//         bne Ret
//         longa
//         lda $26
//  Jump To Subroutine ShiftDivide_16
//  Transfer A to X
//         bne :+
//         inc 		;min 1
// :	sta $0E
//         ldx AttackerOffset
//         clc
//         adc CharStruct::CurHP,X
//         bcs :+
//  CoMPare A with CharStruct::MaxHP,X
//         bcc :++
// :	lda CharStruct::MaxHP,X	;cap at maxhp
// :	sta CharStruct::CurHP,X
//         shorta0
//         lda $0F
//         ora #$80       		;flag to display as healing
//  STore A to $0F
//         lda TimerReadyChar::Regen
//         ldx $0E
//         stx TempDisplayDamage
//  Jump To Subroutine CopyDisplayDamage
//         lda #$09	;C1 routine: display regen/poison damage
//  Jump To Subroutine CallC1
// Ret:	rts
}

static void timerEffectSing(void) {
//         lda #$01
//  STore A to EnableTimer::Sing,Y
//         lda InitialTimer::Sing,Y
//  STore A to CurrentTimer::Sing,Y
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx AttackerOffset
//         lda CharStruct::Song,X
//         beq Ret
// FindSong:		;Y = song stat index
//  A Shift Left
//         bcs :+
//         iny
//         bra FindSong
// :       sty $12		;song stat index
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         stx $0E		;target
//         lda #$04
//  STore A to $10		;after last target
//         lda TimerReadyChar::Sing
//  CoMPare A with #$04	;monster check? monsters can sing?
//         bcc ApplySong
//         lda #$04
//  STore A to $0E		;target
//         lda #$0C
//  STore A to $10		;last target +1
//         ldx #$0180	;**bug: should be $0200 for first monster
// ApplySong:
//         stx $14		;char offset
//         longa
// Transfer X to A
//         clc
//         adc $12		;adjust offset by song stat
//  Transfer A to X
//         shorta0
// CharLoop:
//         ldy $0E		;target
//         lda ActiveParticipants,Y
//         beq Next
//         clc
//         lda CharStruct::BonusStr,X	;different stats depending on X
//         inc
//  CoMPare A with #$64	;don't apply changes at 100 and up
//         bcs Next
//  STore A to CharStruct::BonusStr,X
// Next:
//  Jump To Subroutine NextCharOffset
//         stx $14		;char offset
//         inc $0E		;next target
//         lda $0E
//  CoMPare A with $10		;last target +1
//         bne CharLoop
// Ret:	rts
}

static void timerEffectParalyze(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status2,X
    // and #$DF	;clear paralyze
    // sta CharStruct::Status2,X
    // ldx ProcessingTimer
    // lda TimerReadyChar,X
    // jmp ResetATB
}

static void timerEffectATB(void) {
//  Jump To Subroutine CheckBattleEnd
//         lda BattleOver
//         bne GoRet
//         lda TimerReadyChar::ATB
//  STore A to AttackerIndex
//  Jump To Subroutine GetTimerOffset
//         tyx
//         lda EnableTimer::Paralyze,X
//         bne GoRet
//         lda EnableTimer::ATB,X
//         beq :+
//         jmp PerformAction      	;action is ready, do it
// :	lda TimerReadyChar::ATB
//  CoMPare A with #$04	;monster check
//         bcs Monster
//  Transfer Direct page to aCcumulator
//  Transfer A to X
// SearchTurnQueue:	;find character in turn queue
//         lda ATBReadyQueue,X
//  CoMPare A with TimerReadyChar::ATB
//         beq GoRet	;character already in turn queue
//         inx
//         cpx #$0004
//         bne SearchTurnQueue
//         lda TimerReadyChar::ATB
//  Jump To Subroutine CheckDisablingStatus
//         bne GoRet
//         ldx ATBReadyCount
//         lda TimerReadyChar::ATB
//  STore A to ATBReadyQueue,X
//         inc ATBReadyCount
// GoRet:	jmp Ret
// Monster:
//  Jump To Subroutine MonsterATB
// Ret:	rts
}

// Called when character's turn is up,
// perform their queued action
static void performAction(void) {
//  Jump To Subroutine ProcessTurn
//         lda DelayedFight
//         bne Ret
//         lda AttackerIndex
//  CoMPare A with #$04	;monster check
//         bcs _ResetATB
//         ldx AttackerOffset
//         lda CharStruct::CmdStatus,X
//  AND A with #$E0	;clear many flags (jump/flirt/others?)
//  STore A to CharStruct::CmdStatus,X
//         stz CharStruct::DamageMod,X
//         lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//  AND A with #$02	;zombie
//         bne Uncontrolled
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$18	;charm/berserk
//         beq _ResetATB
// Uncontrolled:
//         lda AttackerIndex
//  Jump To Subroutine GetTimerOffset
//  Transfer Direct page to aCcumulator
//  STore A to EnableTimer::ATB,Y
//         inc
//  STore A to CurrentTimer::ATB,Y
//         lda AttackerIndex
//  Transfer A to X
//         lda UncontrolledATB,X
//  AND A with #$7F	;max 127
//  STore A to UncontrolledATB,X
// _ResetATB:
//         inc CheckQuick
//         lda AttackerIndex
//  Jump To Subroutine ResetATB
//         stz CheckQuick
// Ret:	rts
}

// Waits when a character's turn arrives
// (amount depending on battle speed setting)
static void atbWait(void) {
//         lda ATBWaiting
//         beq Ret
//         lda ATBWaitLeft
//         beq DoneWaiting
//         dec
//  STore A to ATBWaitLeft
//         bne Ret
// DoneWaiting:
//  Transfer Direct page to aCcumulator
//  STore A to ATBWaiting
// Ret:	rts
}

// Updates ATB for all combatants and
// sets them active if present
static void resetAtbAll(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  Transfer A to Y
//         stx $0E			;char index
// ResetATBLoop:
//         lda $0E
//  Jump To Subroutine ResetATB
//         lda $0E
//  Jump To Subroutine CalculateCharOffset
//         lda $0E
//  CoMPare A with #$04		;monster check
//         bcs Monster
//         ldx AttackerOffset
//         lda CharStruct::CharRow,X
//  AND A with #$40		;not present
//         beq SetActive
//         bne Next
// Monster:
//         sec
//         lda $0E
//         sbc #$04
//  Transfer A to X 			;monster index
//         lda InitialMonsters,X
//         beq Next
// SetActive:
//         ldx $0E
//         lda #$01
//  STore A to ActiveParticipants,X
// Next:
//         inc $0E			;char index
//         lda $0E
//  CoMPare A with #$0C		;12 participants
//         bne ResetATBLoop
//         									;.
//  Return To Subroutine
}

// Initialize ATB (A: character index 0-12)
static void resetAtb(void) {
//         pha
//  Jump To Subroutine GetTimerOffset	;Y and $36 = timer offset
//         pla
//  Jump To Subroutine CalculateCharOffset
//  Jump To Subroutine CopyStatsWithBonuses
//         lda CharStruct::EqWeight,X
//  Jump To Subroutine ShiftDivide_8	;weight/8
//         clc
//         adc #$78     		;+120
//         sec
//         sbc Agility    	;-agi
//         beq :+
//         bcs :++
// :	lda #$01     		;min 1
// :Jump To Subroutine HasteSlowMod
//  STore A to CurrentTimer::ATB,Y
//         lda EncounterInfo::IntroFX
//         bpl NotCredits		;80h indicates a credits demo battle
//         ldx AttackerOffset
//         cpx #$0200		;monster
//         bcs CreditsMonster
//         lda #$01		;party member gets turn immediately
//         bra CreditsParty
// CreditsMonster:
//         lda #$FF		;monster turn as late as possible
// CreditsParty:
//  STore A to CurrentTimer::ATB,Y
// NotCredits:
//         lda CheckQuick
//         beq EnableATB
//         lda QuickTurns
//         beq EnableATB
//         lda CurrentlyReacting
//         bne EnableATB
//         dec QuickTurns
//         lda QuickTurns
//         bne Quick
//         phy
//  Jump To Subroutine ClearQuick
//         ply
//         bra EnableATB
// Quick:										;:
//         lda #$01
//  STore A to CurrentTimer::ATB,Y
// EnableATB:
//         lda #$01
//  STore A to EnableTimer::ATB,Y
//  Return To Subroutine
}

// Unfreezes time for everyone
static void clearQuick(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
// :	    stz QuickTimeFrozen,X
//         inx
//         cpx #$000C		;12 combatants
//         bne :-
//  Return To Subroutine
}

// Stop Timer (X: #timer; A: Target index 0-12)
static void stopTimer(void) {
    // phx
    // jsr GetTimerOffset
    // plx
    // jsr AddTimerOffsetY
    // tdc
    // sta EnableTimer,Y
    // rts
}

// Start Timer (X: #timer; A: Participant index)
static void startTimer(void) {
    // phx
    // pha
    // jsr GetTimerOffset
    // pla
    // jsr CalculateCharOffset
    // jsr CopyStatsWithBonuses
    // plx
    // jsr GetTimerDuration	;also sets up Y
    // ldx AttackerOffset	;not actually attacker, in this case
    // jsr HasteSlowMod
    // sta CurrentTimer,Y
    // sta InitialTimer,Y
    // lda #$01
    // sta EnableTimer,Y
    // stz StatusFixedDur
    // rts
}

// Get Timer Duration (X - #timer; $3ED7 - IsItem):
// A = return duration
// sets up and jumps to a jump table entry that
// sets the correct duration
// also sets up Y as the correct timer offset
static void getTimerDuration(void) {
    // jsr AddTimerOffsetY      ;Y = X + TimerOffset
    // txa
    // asl
    // clc
    // adc StatusFixedDur     ;uses alternate fixed status duration
    // asl
    // tax
    // lda f:TimerDurationJumpTable,X
    // sta $08
    // lda f:TimerDurationJumpTable+1,X
    // sta $09
    // lda #$c2 ;.b #bank(TimerDurationJumpTable)
    // sta $0A
    // jmp [$0008]		;jump to table address

    // TimerDurationJumpTable

    // .word DurSpell, Dur120a, DurVit, DurVit, DurSpell
    // .word Dur120b, DurSpell, Dur49, DurSpell, Dur180mod
    // .word DurSpell, Dur180, Dur10, Dur10, Dur110mod
    // .word Dur110mod, Dur30, Dur30, DurSpellmod, Dur120mod

    // .word $2572, $2576, $2579, $2579, $2572
    //       $2584, $2572, $2587, $2572, $258A
    //       $2572, $259A, $259D, $259D, $25A0
    //       $25A0, $25AF, $25AF, $25B2, $25C3

}

// (X): Y = X + $36 Timer Offset)
static void addTimerOffsetY(void) {
    // txa
    // longa
    // clc
    // adc TimerOffset
    // tay
    // shorta0
    // rts
}

// Address: _2572
// Duration = Spell Duration
static uint8_t durSpell(uint8_t value) {
    // LoaD StatusDuration to A
    // Return To Subroutine
    return value;
}

// Address: _2576
// Duration = 120
// Similar to durSpell(..), but with a direct value as the input.

// Duration = Attacker's Vitality + 20
// TODO: Update formula to include Vitality
static uint8_t durVit(void) {
    // CLear Carry Flag
    // LoaD Vitality to A
    // ADd A with #$14 (#20) and Carry
    uint8_t sum = 20;

    // Branch to next label if Carry Clear
    // LoaD #$FF (max #255) to A
    // [LBL] Return To Subroutine
    if (sum > MAX_BYTE) return MAX_BYTE;

    return sum;
}

// Address: _2584
// Duration = 120
// Similar of durSpell(..)

// Address: _2587
// Duration = 49
// Similar to durSpell(..)

// Duration = 180 - Attacker's Magic Power / 2
// TODO: Update formula with Magic Power
static uint8_t dur180mod(uint8_t base) {
    // Load MagicPower to A
    // (L)Shift A Right
    // Store A to $0E
    // SEt Carry
    // Load #$B4 (#180) to A
    // SuBtract $0E from A with Carry
    uint8_t total = base;

    // Branch to next label if Carry Set
    // LoaD #$01 to A
    // [LBL] Return To Subroutine
    if (total < MIN_BYTE) return MIN_BYTE;

    return total;
}

// Address: _259A
// Duration = 180
// Similar to durSpell(..)

// Address: _259D
// Duration = 10
// Similar to durSpell(..)

// Duration = 110 - Attacker's Magic Power, min 30
// TODO: Update formula with Magic Power
static uint8_t dur110mod(void) {
//     sec
//     lda #$6E	;110
//     sbc MagicPower
//     bcc :+
//     cmp #$1E	;min 30
//     bcs :++
// :	lda #$1E	;min 30
// :	rts
    uint8_t total = 110;

    if (total < 30) return 30;

    return total;
}

// Address: _25AF
// Duration = 30
// Similar to durSpell(..)

// Duration = Spell Duration - Attacker's Magic Power / 2
// Similar to dur180mod(..), but with starting value pointing to spell duration

// Duration = 120 - Attacker's Magic Power / 2
// Similar to dur180mod(..), with with different starting value

// Queues up a monster's action when
// their ATB is ready
static void monsterAtb(void) {
//         lda #$01
//  STore A to AISkipDeadCheck
//         sec
//         lda AttackerIndex
//         sbc #$04
//  STore A to MonsterIndex
//  Jump To Subroutine ShiftMultiply_16
//  Transfer A to X
//         stx MonsterOffset16
//  A Shift Left
//  Transfer A to X
//         stx MonsterOffset32
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         sty TempCharm
//         ldx MonsterOffset16
//         lda #$FF
// :	sta MonsterMagic,X
//         inx
//         iny
//         cpy #$0010	;init 16 byte monster magic struct
//         bne :-
//         							;
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to X
//         lda f:_d0ee95,X
//  STore A to $0E
//         lda f:_d0ee95+1,X
//  STore A to $0F
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $0E		;MonsterIndex *100
//         lda #$FF
// :	sta MonsterAIScript,X
//         inx
//         iny
//         cpy #$0064	;init 100 bytes to $FF
//         bne :-
//         lda AttackerIndex
//  Jump To Subroutine CalculateCharOffset
//         ldx AttackerOffset
//         lda #$2C       	;magic
//  STore A to CharStruct::Command,X
//         lda #$21	;magic + costs mp
//  STore A to CharStruct::ActionFlag,X
//         ldx AttackerOffset
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$08	;berserk
//         beq CheckCharm
//         lda #$01
//  STore A to CharStruct::CmdCancelled,X
//         lda #$80	;monster fight
//  STore A to AIBuffer
//         lda #$FF	;end of list
//  STore A to AIBuffer+1
//  Jump To Subroutine DispatchAICommands
//         jmp GoFinish
// CheckCharm:
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//  AND A with #$10	;charm
//         beq CheckFlirt
// TryRandomAction:
//         ldx AttackerOffset
//         lda #$01
//  STore A to CharStruct::CmdCancelled,X
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump To Subroutine Random_X_A 	;0..3
//  Transfer A to X
//         stx $0E
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to X
//         longa
//         lda BattleMonsterID,X
//  Jump To Subroutine ShiftMultiply_4
//         clc
//         adc $0E		;random number 0..3
//  Transfer A to X 		;offset into control actions table
//         shorta0
//         lda f:MonsterControl,X
//  CoMPare A with #$FF
//         beq TryRandomAction	;no action in this slot, try again
//  STore A to AIBuffer
//         lda #$FF	;end of list
//  STore A to AIBuffer+1
//         inc TempCharm
//  Jump To Subroutine DispatchAICommands
//         bra GoFinish
// CheckFlirt:								;
//         lda CharStruct::CmdStatus,X
//  AND A with #$08	;flirt
//         beq CheckControl
//         lda #$51	;throbbing command
//  STore A to CharStruct::Command,X
//         lda #$80	;other
//  STore A to CharStruct::ActionFlag,X
//         bra GoFinish
// CheckControl:
//         lda CharStruct::Status4,X
//  AND A with #$20	;control
//         bne Control
//         lda CharStruct::Status2,X
//  AND A with #$40	;sleep
//         bne Sleep
//         bra Normal
// Control:
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// :	lda ControlTarget,Y
//  CoMPare A with AttackerIndex
//         beq FoundController
//         iny
//         bra :-
// FoundController:
//         lda ControlCommand,Y
//         bne _ControlCommand
// Sleep:	;or controlled without a command
//         stz CharStruct::Command,X
//         lda #$80	;action complete?
//  STore A to CharStruct::ActionFlag,X
//         bra GoFinish
// _ControlCommand:
//  Transfer Direct page to aCcumulator
//  STore A to ControlCommand,Y
//         lda MonsterIndex
//  Transfer A to X
//         lda MonsterControlActions,X
//  STore A to AIBuffer
//         lda #$FF	;end of list
//  STore A to AIBuffer+1
//  Jump To Subroutine DispatchAICommands
// GoFinish:
//         jmp Finish
// Normal:
//         lda MonsterIndex
//  Transfer A to X
//         lda AIActiveConditionSet,X
//  STore A to AICurrentActiveCondSet
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to X
//         longa
//         clc
//         lda f:_d0eea5,X	;*1620, size of MonsterAI struct
//         adc #MonsterAI
//  STore A to AIOffset
//         shorta0
//         stz AICurrentCheckedSet
// CheckAIConditions:
//         lda AICurrentCheckedSet
//  Transfer A to X
//         lda f:_d0eec9,X	;size of a MonsterAI condition
//  Transfer A to Y
//         sty AIConditionOffset
//         stz AICheckIndex
// CheckSingleCondition:
//         ldy AIConditionOffset
//         lda (AIOffset),Y
//         beq AIActions		;0 always succeeds
//  CoMPare A with #$FE		;indicates end of condition set
//         beq AIActions
//  Jump To Subroutine CheckAICondition
//         lda AIConditionMet
//         beq NextConditionSet
//         longa
//         clc
//         lda AIConditionOffset
//         adc #$0004		;next condition in set
//  STore A to AIConditionOffset
//         shorta0
//         inc AICheckIndex
//         bra CheckSingleCondition
// NextConditionSet:	;failed a condition in this set, check next set of conditions
//         inc AICurrentCheckedSet
//         lda AICurrentCheckedSet
//  CoMPare A with #$0A		;10 conditions max
//         bne CheckAIConditions
// AIActions:
//         longa
//         clc
//         lda AIOffset
//         adc #$00AA	;advances from Conditions to Actions
//  STore A to AIOffset
//         shorta0
//         lda AICurrentActiveCondSet
//  CoMPare A with AICurrentCheckedSet
//         beq ConditionOK	;matches so don't need to change things
//         lda MonsterIndex
//  Transfer A to X
//         lda AICurrentCheckedSet
//  STore A to AIActiveConditionSet,X	;checked cond is now current
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to Y
//         lda AICurrentCheckedSet
//  A Shift Left
//  Transfer A to X
//         lda f:_d0eeb5,X
//  STore A to AICurrentOffset,Y
//         lda f:_d0eeb5+1,X
//  STore A to AICurrentOffset+1,Y
// ConditionOK:
//  Jump To Subroutine ProcessAIScript
// Finish:
//         ldx MonsterOffset16
//         lda MonsterMagic,X
//         longa
//  Jump To Subroutine ShiftMultiply_8
//  Transfer A to X
//         shorta0
//         lda f:AttackProp,X
//  AND A with #$03       	;delay values
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//         pha
//         lda AttackerIndex
//  Jump To Subroutine GetTimerOffset
//         pla
//  STore A to CurrentTimer::ATB,Y    ;**bug? doesn't adjust for haste/slow
//         lda #$41	;pending action
//  STore A to EnableTimer::ATB,Y
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to X
//         stz ForcedTarget::Party,X
//         stz ForcedTarget::Monster,X
//  Return To Subroutine
}

static void checkAICondition(void) {
    //  CoMPare A with #$13         ($12 is last valid condition)
    //  Branch to next label if Carry Clear
    //  Transfer DireCt page to A   (always succeed	if invalid)
    //  [LBL] STore A to $0E		(condition to check)
    //  Accumulator Shift Left
    //  Transfer A to X
    //  LoaD f:AICondition,X to A
    //  STore A to $08
    //  LoaD f:AICondition+1,X to A
    //  Store A to $09
    //  LoaD #$C2 to A
    //  STore A to $0A
    //  Increment Y
    //  LoaD (AIOffset),Y to A
    //  STore A to AIParam1
    //  Increment Y
    //  LoaD (AIOffset),Y to A
    //  STore A to AIParam2
    //  Increment Y
    //  LoaD (AIOffset),Y to A
    //  STore A to AIParam3
    //  STore Zero to AIConditionMet
    //  LoaD AISkipDeadCheck to A
    //  Branch to [Jump] if Not Equal
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::CurHP,X to A
    //  OR A with CharStruct::CurHP+1,X
    //  Branch to [Dead] if EQuals
    //  LoaD CharStruct::Status1,X to A
    //  AND A with #$C0     (dead or stone)
    //  Branch to [NotDead] if EQuals
    //  [Dead] LoaD $0E to A
    //  Compare A with #$0F (condition: dead)
    //  Branch to [Jump] if EQuals
    //  Return To Subroutine

    //  [NotDead] LoaD $0E to A
    //  CoMPare A with #$0F (auto-fail condition: dead if not dead)
    //  Branch to Jump if Not Equals
    //  Return To Subroutine

    //  [Jump] JuMp Long to [$0008] (AICondition table)

    // AICondition table
    // %generatejumptable(AICondition,$12)
    // vanilla values:
    // .word $283A, $283E, $289D, $28DB, $28EB, $291F, $2939, $29B1
    // .word $2A29, $2A63, $2A9D, $2AD2, $2B19, $2B2A, $2B6F, $2B87
    // .word $2B93, $2BC0, $2BFD
}

// Address: _283A
// AI Condition $00: Always Succeed
static void aiCondition00(void) {
    // INCrement AIConditionMet
    // Return To Subroutine
}

// Address: _283E
// AI Condition 01: Check Status
// Param1: AITarget routine
// Param2: Status offset (0-3 for status 1-4)
// Param3: Status bits
// if checking for death status,
// also succeed if hp is 0 (though this behavior is bugged)
static void aiCondition01(void) {
    //  LoaD AIParam1 to A
    //  Jump to SubRoutine GetAITarget	(populates list of targets to check)
    //  LoaD AIParam2 to A
    //  Transfer A to X
    //  STore X to $0E
    //  Transfer DireCt page to A
    //  Transfer A to Y
    //  [Loop] Lengthen A
    //  Load AITargetOffsets,Y to A
    //  CoMPare A with #$FFFF	(end of list or no target found)
    //  Branch to [TargetFound] if Not Equals
    //  Shorten A
    //  BRAnch to [Finish]
    //  [TargetFound]
    //  STore A to $10		(target offset)
    //  CLear Carry flag
    //  ADd $0E to A with Carry		(status offset)
    //  Transfer A to X
    //  Shorten A
    //  LoaD CharStruct::Status1,X to A	;could be status 1-4 depending
    //  OR A with CharStruct::AlwaysStatus1,X	;on status offset
    //  AND A with AIParam3
    //  Branch to [Match] if Not Equals
    //  LoaD $0E to A
    //  Branch to [Next] if Not Equals
    //  LoaD AIParam3 to A
    //  Branch to [Next] if PLus
    //  LoaD $10 to A			;if asked to check death status
    //  LoaD CharStruct::CurHP,X to A	;also succeed if hp is 0
    //  OR A with CharStruct::CurHP,X	;**bug: should be high byte $2007
    //  Branch to [Next] if Not Equals
    //  [Match] INCrement AIConditionMet
    //  [Next] INcrement Y by 2
    //  ComPare Y with #$0018	;12 characters * 2 bytes
    //  Branch to [Loop] if Not Equals
    //  [Finish] LoaD AIMultiTarget to A
    //  Branch to [Ret] if Equals
    //  LoaD AITargetCount to A
    //  CoMPare A with AIConditionMet
    //  Branch to [Ret] if Equals
    //  Store Zero to AIConditionMet
    //  [Ret] Return To Subroutine
}

// AI Condition 02: HP less than value
// Param1: AITarget routine
// Param2: HP (low byte)
// Param3: HP (high byte)
static void aiCondition02(void) {
    //  LoaD AIParam1 to A
    //  Jump to SubRoutine GetAITarget
    //  Transfer DireCt page to A
    //  Transfer A to Y
    //  [Loop] Lengthen A
    //  LoaD AITargetOffsets,Y to A
    //  Transfer A to X
    //  CoMPare A with #$FFFF   (end of list or no target found)
    //  Branch to [FinishMode] if EQuals
    //  LoaD CharStruct::CurHP,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Next] if Carry Set
    //  INCrement AIConditionMet
    //  [Next] Transfer DireCt page to A
    //  Shorten A
    //  Increment Y by 2
    //  ComPare Y with #$0018	(12 characters * 2 bytes)
    //  Branch to [Loop] if Not Equal
    //  Branch to [Finish]  (not needed; resetting mode is harmless)
    //  [FinishMode] Shorten A		(need to fix A back to 8 bit)
    //  [Finish] (fail if any targets failed) LoaD AIMultiTarget to A
    //  Branch to Ret if EQuals
    //  LoaD AITargetCount to A
    //  CoMPare A with AIConditionMet
    //  Branch to Ret if EQuals
    //  STore Zero to AIConditionMet
    //  [Ret] Return To Subroutine
}

// AI Condition 03: Check Variable
// Param2: Var to check (0-3)
// Param3: Value
static void aiCondition03(void) {
    //  LoaD AIParam2 to A
    //  Transfer A to X
    //  LoaD AIVars,X to A
    //  CoMPare A with AIParam3
    //  Branch to [Fail] if Not Equals
    //  Increment AIConditionMet
    //  [Fail] Return To Subroutine
}

// AI Condition 04: Alone
// Param2:
//  - if 0, succeeds when completely alone
//	- if non-0, succeeds when all active monsters are the same
static void aiCondition04(void) {
    //  LoaD AIParam2 to A
    //  Branch to [CheckSame] if Not Equals
    //  LoaD MonstersVisible to A
    //  Jump To Subroutine [CountSetBits]
    //  DEcrement X
    //  Branch to [Met] if EQuals
    //  Return To Subroutine

    //  [CheckSame] LoaD MonsterIndex to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD BattleMonsterID,X to A
    //  STore A to $0E
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  [Loop]	lda ActiveParticipants+4,Y
    //  Branch to [Next] if EQuals
    //  Transfer Y to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD BattleMonsterID,X to A
    //  CoMPare A with $0E
    //  Brach to [Fail] if Not Equals
    //  [Next] INcrement Y
    //  ComPare Y with #$0008
    //  Branch to [Loop] if Not Equals
    //  [Met] Increment AIConditionMet
    //  [Fail] Return To Subroutine
}

// AI Condition 05: Compare Visible Monsters
// Param1:
//  - if 0, succeeds if visible monsters match
//    provided value
//	- if non-0, succeeds if they do not match
//Param3: Monster Bits (1 bit per monster)
static void aiCondition05(void) {
    //  LoaD AIParam1 to A
    //  Branch to [CheckMatch] if Equals
    //  LoaD MonstersVisible to A
    //  CoMPare A with AIParam3
    //  Branch to [Met] if Not Equals
    //  Return To Subroutine

    //  [CheckMatch] LoaD MonstersVisible to A
    //  CoMPare A with AIParam3
    //  Branch to [Fail] if Not Equals
    //  [Met] Increment AIConditionMet
    //  [Fail] Return To Subroutine
}

// AI Condition 06: Reaction to Command and/or Element
// Param1: if set, inverts test so
//         a match fails the condition, and
//         ignores element when checking commands
// Param2: Command (post-remap values)
//	       Command $07, normally BuildUp, is used
//         as a flag to skip the command check and
//         just check element
// Param3: Element (ignored if zero)
static void aiCondition06(void) {
    //  LoaD AttackerOffset to X
    //  LoaD ReactionFlags to A
    //  AND A with #$01
    //  Branch to [Reaction2] if Not Equals	(Check 2nd set of reactions instead)
    //  LoaD AIParam2 to A	(command)
    //  CoMPare A with #$07	(used as a flag to skip command check)
    //  Branch to [SkipCmdCheck1] if EQuals
    //  LoaD AIParam1 to A	(invert checks)
    //  Branch to [CheckCmdMatch1] if EQuals
    //  LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction1Command,X
    //  Branch to [Met] if Not Equals	(if param1 is >0, succeed when no cmd match)
    //  Return To Subroutine

    //  [CheckCmdMatch1] LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction1Command,X
    //  Branch to [Fail] if Not Equals	(if param1 is 0, fail when no cmd match)

    //  [SkipCmdCheck1]		(command match or command $07 override)
    //  LoaD lda AIParam1 to A
    //  Branch to [CheckElemMatch1] if EQuals
    //  LoaD lda AIParam3	;element to A
    //  AND A with CharStruct::Reaction1Element,X
    //  Branch to [Met] if EQuals	(if param1 is >0, succeed when no elem match)
    //  Return To Subroutine	(only reachable via the $07 override)
    //  [CheckElemMatch1] LoaD AIParam3 to A
    //  Branch to [Met] if EQuals	(succeed when element is 0)
    //  AND A with CharStruct::Reaction1Element,X
    //  Branch to [Met] if Not Equals	(or when any element matches)
    //  Return To Subroutine

    //  [Reaction2]     (same logic as above, but react to the second stored command)
    //  LoaD AIParam2 to A
    //  CoMPare A with #$07
    //  Branch to SkipCmdCheck2 if EQuals
    //  LoaD AIParam1 to A
    //  Branch to CheckCmdMatch2 if EQuals
    //  LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction2Command,X
    //  Branch to [Met] if Not Equals
    //  Return To Subroutine

    //  [CheckCmdMatch2] LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction2Command,X
    //  Branch to [Fail] if Not Equals

    //  [SkipCmdCheck2] LoaD AIParam1 to A
    //  Branch to CheckElemMatch2 if EQuals
    //  LoaD AIParam3 to A
    //  AND A with CharStruct::Reaction2Element,X
    //  Branch to [Met] if EQuals
    //  Return To Subroutine

    //  [CheckElemMatch2] LoaD AIParam3 to A
    //  Branch to [Met] if EQuals
    //  AND A with CharStruct::Reaction2Element,X
    //  Branch to [Fail] if EQuals
    //  [Met] INCrement AIConditionMet
    //  [Fail] Return To Subroutine
}

// AI Condition $07: Reaction to Command and/or Category
// Param1: if set, inverts test so a match fails
//         the condition, and ignores category when
//         checking commands
// Param2: Command (post-remap values)
//         Command $07, normally BuildUp, is used
//         as a flag to skip the command check and
//         just check category
// Param3: Category (ignored if zero)
static void aiCondition07(void) {
    //  LoaD AttackerOffset to X
    //  LoaD ReactionFlags to A
    //  AND A with #$01
    //  Branch to [Reaction2] if Not Equals	(Check 2nd set of reactions instead)
    //  LoaD AIParam2 to A	(command)
    //  CoMPare A with #$07	(used as a flag to skip command check)
    //  Branch to [SkipCmdCheck1] if EQuals
    //  LoaD AIParam1 to A	(invert checks if set)
    //  Branch to [CheckCmdMatch1] if EQuals
    //  LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction1Command,X
    //  Branch to  [Met] if Not Equals	(if param1 is >0, succeed when no cmd match)
    //  Return To Subroutine

    //  [CheckCmdMatch1] LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction1Command,X
    //  Branch to [Fail] if Not Equals	(if param1 is 0, fail when no cmd match)

    //  [SkipCmdCheck1]		(command match or command $07 override)
    //  LoaD AIParam1 to A
    //  Branch to [CheckCatMatch1] if EQuals
    //  LoaD AIParam3 to A	(category)
    //  AND A with CharStruct::Reaction1Category,X
    //  Branch to [Met] if EQuals	(if param1 >0, succeed when no category match)
    //  Return To Subroutine

    //  [CheckCatMatch1] LoaD AIParam3 to A
    //  Branch to [Met] if EQuals	(succeed when category is 0)
    //  AND A with CharStruct::Reaction1Category,X
    //  Branch to [Met] if Not Equals	(or when any category matches)
    //  Return To Subroutine

    //  [Reaction2]     (same logic as above, but react to the second stored command)
    //  LoaD AIParam2 to A
    //  CoMPare A with #$07	(used as a flag to skip command check)
    //  Branch to [SkipCmdCheck2] if EQuals
    //  LoaD AIParam1 to A
    //  Branch to [CheckCmdMatch2] if EQuals
    //  LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction2Command,X
    //  Branch to [Met] if Not Equals
    //  Return To Subroutine

    //  [CheckCmdMatch2] LoaD AIParam2 to A
    //  CoMPare A with CharStruct::Reaction2Command,X
    //  Branch to [Fail] if Not Equals
    //  [SkipCmdCheck2] LoaD AIParam1 to A
    //  Branch to [CheckCatMatch2] if EQuals
    //  LoaD AIParam3 to A
    //  AND A with CharStruct::Reaction2Category,X
    //  Branch to [Met] if EQuals
    //  Return To Subroutine

    //  [CheckCatMatch2] LoaD AIParam3 to A
    //  Branch to [Met] if EQuals
    //  AND A with CharStruct::Reaction2Category,X
    //  Branch to [Fail] if EQuals
    //  [Met] INCrement AIConditionMet
    //  [Fail] Return To Subroutine
}

// AI Condition $08: Reaction to Magic
// Param1: if set, inverts test so a match
//         fails the condition
// Param2: Spell
static void aiCondition08(void) {
    //  LoaD AttackerOffset to X
    //  LoaD ReactionFlags to A
    //  AND A with #$01	;check second set of reactions
    //  Branch to [Reaction2] if Not Equals
    //  LoaD AIParam1 to A
    //  Branch to [CheckMatch1] if EQuals
    //  LoaD CharStruct::Reaction1Magic,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Met] if Not Equals
    //  Return To Subroutine

    //  [CheckMatch1] LoaD CharStruct::Reaction1Magic,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Met] if EQuals
    //  Return To Subroutine

    //  [Reaction2] LoaD AIParam1 to A
    //  Branch to [CheckMatch2] if EQuals
    //  LoaD CharStruct::Reaction2Magic,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Met] if Not Equals
    //  Return To Subroutine

    //  [CheckMatch2] LoaD CharStruct::Reaction2Magic,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Fail] if Not Equals
    //  [MET] INCrement AIConditionMet
    //  [Fail] Return To Subroutine
}

// AI Condition $09: Reaction to Item
// Param1: if set, inverts test so a match
//         fails the condition
// Param2: Item
static void aiCondition09(void) {
    //  LoaD AttackerOffset to X
    //  LoaD ReactionFlags to A
    //  AND A with #$01	;check second set of reactions
    //  Branch to [Reaction2] if Not Equals
    //  LoaD AIParam1 to A
    //  Branch to [CheckMatch1] if EQuals
    //  LoaD CharStruct::Reaction1Item,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Met] if Not Equals
    //  Return To Subroutine

    //  [CheckMatch1] LoaD CharStruct::Reaction1Item,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Met] if EQuals
    //  Return To Subroutine

    //  [Reaction2] LoaD AIParam1 to A
    //  Branch to [CheckMatch2] if EQuals
    //  LoaD CharStruct::Reaction2Item,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Met] if Not Equals
    //  Return To Subroutine

    //  [CheckMatch2] LoaD CharStruct::Reaction2Item,X to A
    //  CoMPare A with AIParam2
    //  Branch to [Fail] if Not Equals
    //  [MET] INCrement AIConditionMet
    //  [FAIL] Return To Subroutine 
}

// AI Condition $0A: Reaction to Targetting
// Param3: if 0, succeeds when attack was single target
//	       if non-0, succeeds when attack was multi target
static void aiCondition0A(void) {
    //  LoaD ReactionFlags to A
    //  AND A with #$01	    (check second set of reactions)
    //  Branch to [Reaction2] if Not Equals
    //  LoaD ldx AttackerOffset to X
    //  LoaD lda CharStruct::Reaction1Targets,X to A
    //  Jump To Subroutine CountSetBits
    //  DEcrement X 		(targets -1)
    //  Branch to [Fail] if MInus	(fail for 0 targets)
    //  JuMP to CheckInvert

    //  [Reaction2] LoaD AttackerOffset to X
    //  LoaD CharStruct::Reaction2Targets,X to A
    //  Jump To Subroutine CountSetBits
    //  DEcrement X 		(targets -1)
    //  Branch to [Fail] if MInus	(fail for 0 targets)
    //  Jump To Subroutine CheckInvert

    //  [FAIL] Return To Subroutine 

    //  [CheckInvert] LoaD AIParam3 to A	(inverts)
    //  Branch to [Invert] if Not Equals
    //  Transfer X to A
    //  Branch to [Fail2] if Not Equals	(fail for >1 targets)
    //  Branch to [Met] if EQuals	    (succeed for exactly 1 target)

    //  [Invert] Transfer X to A
    //  Branch to [Fail2] if EQuals	    (fail for exactly 1 target)

    //  [MET] INCrement AIConditionMet

    //  [Fail2] Return To Subroutine
}

// Address: _2AD2
// AI Condition 0B: Check CharStruct param
// Param1: AITarget routine
// Param2: Offset within CharStruct to check
// Param3: Value for success
static void aiCondition0B(void) {
//         lda AIParam1
//  Jump To Subroutine GetAITarget	;populates list of targets to check
//         lda AIParam2
//  Transfer A to X
//         stx $0E		;Offset within CharStruct
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// Loop:	longa
//         lda AITargetOffsets,Y
//  CoMPare A with #$FFFF	;end of list or no target found
//         bne TargetFound
//         shorta0
//         bra Finish
// TargetFound:
//         clc
//         adc $0E		;Offset within CharStruct
//  Transfer A to X
//         shorta0
//         lda CharStruct::CharRow,X	;check any single CharStruct byte
//  CoMPare A with AIParam3		;compare with provided value
//         bne :+
//         inc AIConditionMet
// :	iny
//         iny
//         cpy #$0018	;12 characters * 2 bytes
//         bne Loop
// Finish:			;fail if any targets failed
//         lda AIMultiTarget
//         beq Ret
//         lda AITargetCount
//  CoMPare A with AIConditionMet
//         beq Ret
//         stz AIConditionMet
// Ret:	rts
}

// Address: _2B19
static void aiCondition0C(void) {}

// Address: _2B2A
static void aiCondition0D(void) {}

// Address: _2B6F
static void aiCondition0E(void) {}

// Address: _2B87
static void aiCondition0F(void) {}

// Address: _2B93
static void aiCondition10(void) {}

// Address: _2BC0
static void aiCondition11(void) {}

// Address: _2BFD
static void aiCondition12(void) {}