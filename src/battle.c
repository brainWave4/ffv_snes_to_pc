// Bank Range: C2/0000 - C2/9FFF

#include <stdint.h>

// for ExecBtlGfx_ext
#include "btlgfx.h"

// for ExecSound_ext
#include "sound.h"

// TO: import RNGTbl (from field), AttackMessageTbl

// FUNCTION DECLARATIONS
void execBattle(void);
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

static void CheckAICondition(void);
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

// Address: _16AA
static void copyAbilityInfo(void) {
//         pha
//         jsr SelectCurrentProcSequence
//         pla
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         stz $0A
// :	lda f:BattleCmdProp,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//         cmp #$05     ;copy first 5 bytes
//         bne :-
//         iny          ;skip 4 on destination
//         iny
//         iny
//         iny
// :	lda f:BattleCmdProp,X
//         sta AttackInfo,Y
//         inx
//         iny
//         inc $0A
//         lda $0A
//         cmp #$08      ;copy remaining 3 bytes
//         bne :-
//         rts
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
//         sta CurrentChar
//         jsr CalculateCharOffset
//         longa
//         lda CharStruct::Status1,X	;includes status 2
//         cmp DisplayInfo::Status1
//         bne Differs
//         lda CharStruct::Status3,X	;includes status 4
//         cmp DisplayInfo::Status3
//         bne Differs
//         lda CharStruct::CurMP,X
//         cmp DisplayInfo::CurMP
//         bne Differs
//         shorta0
//         bra Matches
// Differs:	;disable commands as needed, and update displayinfo for menu
//         shorta0
//         jsr CheckDisablingStatus
//         bne Disabled
//         jsr DisableCommandsMagic
//         jsr ApplyBerserkStatus
//         bne Disabled
//         lda #$05		;C1 routine
//         jsr CallC1
//         lda #$06		;C1 routine
//         jsr CallC1
//         longa
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//         sta DisplayInfo::Status1
//         lda CharStruct::Status3,X
//         sta DisplayInfo::Status3
//         lda CharStruct::CurMP,X
//         sta DisplayInfo::CurMP
//         shorta0
//         bra Matches
// Disabled:	;if character has become disabled while their menu is open, close the menu
//         lda DisplayInfo::CurrentChar
//         sta MenuCurrentChar
//         lda GearChanged
//         beq :+
//         stz GearChanged
//         jsr ReplaceHands
//         jsr ApplyGear
// :	lda DisplayInfo::CurrentChar
//         sta MenuCurrentChar
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu
//         lda #$01	;C1 routine: close menu
//         jsr CallC1
// WaitMenu:
//         lda MenuDataC1::MenuOpen
//         bne WaitMenu	;ends up 0 eventually? via interrupts?
//         lda #$FF
//         sta DisplayInfo::CurrentChar
//         rts
// Matches:	;data either already matched or has been updated
//         lda ControllingA
//         beq Ret
//         lda DisplayInfo::CurrentChar
//         tax
//         lda ControlTarget,X
//         beq :+
//         tax
//         lda ActiveParticipants,X
//         bne Ret
// :	lda DisplayInfo::CurrentChar
//         sta MenuCurrentChar
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu2
//         lda #$01	;C1 routine: close menu
//         jsr CallC1
// WaitMenu2:
//         lda MenuDataC1::MenuOpen
//         bne WaitMenu2	;ends up 0 eventually? via interrupts?
//         lda #$80
//         sta MenuData::ActionFlag
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
//         cmp #$FF
//         beq NoCurrentChar
//         jmp ProcessMenuCommand
// NoCurrentChar:
//         lda ATBReadyQueue
//         cmp #$FF
//         bne NextReadyATB
//         rts		;no one else in queue either
// NextReadyATB:	;there's a character in the queue with ATB ready
//         pha
//         tdc
//         tax
// AdvanceQueue:	;advances all the queue elements up by one, there's a terminator $FF in the 5th slot
//         lda ATBReadyQueue+1,X
//         sta ATBReadyQueue,X
//         inx
//         cpx #$0004
//         bne AdvanceQueue
//         dec ATBReadyCount
//         pla
//         sta MenuCurrentChar
//         sta DisplayInfo::CurrentChar
//         jsr CalculateCharOffset
//         lda QuickTurns
//         beq DontStopTime
//         lda DisplayInfo::CurrentChar
//         cmp QuickCharIndex
//         beq DontStopTime
//         jsr GetTimerOffset  	;sets Y to Timer offset
//         lda CurrentTimer::ATB,Y
//         bne FinishEarly	;check if frozen char's ATB is ready
//         lda #$01		;increase ATB to 1 (no longer ready)
//         sta CurrentTimer::ATB,Y
//         sta EnableTimer::ATB,Y
//         bra FinishEarly
// DontStopTime:
//         jsr CheckDisablingStatus
//         beq NotDisabled
// FinishEarly:
//         lda #$FF
//         sta DisplayInfo::CurrentChar
//         rts
// NotDisabled:	;character's turn has just come up
//         stz MenuCurrentChar+1
//         jsr ApplyBerserkStatus
//         bne FinishEarly
//         jsr DisableCommandsMagic
//         lda #$01
//         sta ATBWaiting
//         lda ATBWaitTime
//         sta ATBWaitLeft
//         longa
//         ldx AttackerOffset
//         lda CharStruct::Status1,X	;includes 2
//         sta DisplayInfo::Status1
//         lda CharStruct::Status3,X	;includes 4
//         sta DisplayInfo::Status3
//         lda CharStruct::CurMP,X
//         sta DisplayInfo::CurMP
//         stz CharStruct::CmdStatus,X	;also damagemod
//         shorta0
//         jsr CheckControlTargetActive
//         lda #$01
//         sta FleeTickerActive	;can't start running until first atb
//         lda EncounterInfo::IntroFX
//         bpl NoCredits
//         stz MenuData::MenuOpen
//         rts
// NoCredits:
//         lda DisplayInfo::CurrentChar
//         jsr GetTimerOffset	;Y = Timer offset
//         lda EnableTimer::ATB,Y
//         beq TimerOff
//         lda #$FF
//         sta DisplayInfo::CurrentChar
//         jmp NoCurrentChar
// TimerOff:
//         tdc
//         jsr CallC1 	;C1 routine $00: open menu
// WaitMenu3:
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu3
//         rts
// ProcessMenuCommand:
//         stz ATBWaiting
//         jsr ProcessMenuCommandData
//         lda #$FF	;no current char
//         sta DisplayInfo::CurrentChar
//         rts
}

// Address: _190B
// Sets ControllingA and B variables to 1
// if control target is valid and active, 0 otherwise
// Logic is a bit strange but doesn't seem like
// they can ever be set to different values
static void checkControlTargetActive(void) {
//     stz ControllingA
//         lda DisplayInfo::CurrentChar
//         tax
//         lda ControlTarget,X
//         beq Finish
//         tay
//         lda ActiveParticipants,Y
//         beq Finish
//         lda #$01
//         sta ControllingA
// Finish:	sta ControllingB
//         rts
}

// Address: _1926
// copies command data from MenuData struct into CharStruct,
// and performs any other necessary processing
// Also handles gear changes, removing control when needed,
// consuming items when used, and action delays
static void processMenuCommandData(void) {
//         lda EncounterInfo::IntroFX
//         bpl :+		;check for credits demo
//         jsr SetupCreditsDemo
// :	lda DisplayInfo::CurrentChar
//         sta CurrentChar
//         lda GearChanged
//         beq :+
//         stz GearChanged
//         jsr ReplaceHands
//         jsr ApplyGear
// :	lda DisplayInfo::CurrentChar
//         jsr CalculateCharOffset
//         lda CharStruct::Status1,X
//         and #$C0	;dead/stone
//         bne ClearControl
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$78	;sleep/para/charm/berserk
//         bne ClearControl
//         lda CharStruct::Status3,X
//         and #$10	;stop
//         bne ClearControl
//         lda CharStruct::Status4,X
//         and #$80	;erased
//         beq :+
// ClearControl:
//         lda DisplayInfo::CurrentChar
//         tax
//         stz ControlTarget,X
//         bra ClearMenuData
// :	lda DisplayInfo::CurrentChar
//         cmp MenuData::CurrentChar
//         beq :+
//         lda EncounterInfo::IntroFX
//         bmi :+		;branch if credits fight
//         lda #$0D	;C1 Routine
//         jsr CallC1
// WaitForever:
//         bra WaitForever	;infinite loop?
// :	lda DisplayInfo::CurrentChar
//         tax
//         lda ControlTarget,X
//         beq NoControlTarget
//         tay
//         lda ActiveParticipants,Y
//         beq ClearMenuData
//         inc ControlCommand,X
//         sec
//         lda ControlTarget,X
//         sbc #$04
//         sta $0E		;monster index of control target
//         tay
//         lda DisplayInfo::CurrentChar
//         tax
//         clc
//         lda f:_d0eedb,X	;size of CharControl struct
//         adc MenuData::SelectedItem	;action 0-3
//         tax
//         lda CharControl::Actions,X
//         sta MonsterControlActions,Y
//         sec
//         lda $0E
//         asl
//         tax
//         lda MenuData::PartyTargets
//         sta ForcedTarget::Party,X
//         lda MenuData::MonsterTargets
//         sta ForcedTarget::Monster,X
// ClearMenuData:
//         lda #$80
//         sta MenuData::ActionFlag
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
//         tax
//         stx $2A
//         ldx #$028A   	;650, size of CharSpells struct
//         stx $2C
//         jsr Multiply_16bit	;not using the rom *650 table?
//         longa
//         clc
//         lda $2E		;CurrentChar * 650
//         adc #$2D34   	;CharSpells struct location
//         sta TempSpellOffset
//         shorta0
//         ldx AttackerOffset
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$18	;charm/berserk
//         bne CheckCommand
//         lda MenuData::Command
//         sta CharStruct::Command,X
//         lda MenuData::MonsterTargets
//         sta CharStruct::MonsterTargets,X
//         lda MenuData::PartyTargets
//         sta CharStruct::PartyTargets,X
//         lda MenuData::SelectedItem
//         sta CharStruct::SelectedItem,X
//         lda MenuData::ActionFlag
//         sta CharStruct::ActionFlag,X
//         and #$20	;magic
//         beq NotXMagic
//         lda MenuData::SelectedItem
//         tay
//         lda (TempSpellOffset),Y
//         sta CharStruct::SelectedItem,X
//         lda MenuData::ActionFlag
//         and #$08	;x-magic
//         beq NotXMagic
//         lda MenuData::SecondCommand
//         sta CharStruct::SecondCommand,X
//         lda MenuData::SecondMonsterTargets
//         sta CharStruct::SecondMonsterTargets,X
//         lda MenuData::SecondPartyTargets
//         sta CharStruct::SecondPartyTargets,X
//         lda MenuData::SecondSelectedItem
//         tay
//         lda (TempSpellOffset),Y
//         sta CharStruct::SecondSelectedItem,X
//         lda MenuData::SecondActionFlag
//         sta CharStruct::SecondActionFlag,X
//         bra CheckCommand
// NotXMagic:
//         stz CharStruct::SecondCommand,X
//         stz CharStruct::SecondMonsterTargets,X
//         stz CharStruct::SecondMonsterTargets,X	;**bug: PartyTargets
//         stz CharStruct::SecondSelectedItem,X
//         stz CharStruct::SecondActionFlag,X
// CheckCommand:
//         lda MenuData::Command
//         sta $24
//         lda #$08
//         sta $25
//         jsr Multiply_8bit
//         ldx $26		;command * 8
//         ldy AttackerOffset
//         lda f:BattleCmdProp+2,X
//         sta CharStruct::CmdStatus,Y
//         lda f:BattleCmdProp+3,X
//         sta CharStruct::DamageMod,Y
//         lda MenuData::Command
//         cmp #$2C	;first magic command
//         bcc NotMagicCommand
//         cmp #$4E	;after last magic command
//         bcs NotMagicCommand
//         lda CharStruct::ActionFlag,Y
//         ora #$01     	;costs MP
//         sta CharStruct::ActionFlag,Y
// NotMagicCommand:
//         lda MenuData::Command
//         tax
//         lda f:BattleCmdDelay,X
//         bmi CalculateDelay
//         pha
//         lda MenuData::Command
//         cmp #$11	;throw
//         beq Item
//         cmp #$20	;drink
//         beq Item
//         cmp #$1F	;mix
//         bne NotItem
// Mix:
//         lda MenuData::SecondSelectedItem
//         pha
//         tax
//         lda InventoryItems,X
//         ldx AttackerOffset
//         sta CharStruct::SecondSelectedItem,X
//         pla
//         jsr ConsumeItem
// Item:
//         lda MenuData::SelectedItem
//         pha
//         tax
//         lda InventoryItems,X
//         ldx AttackerOffset
//         sta CharStruct::SelectedItem,X
//         pla
//         jsr ConsumeItem
// NotItem:
//         pla
//         jmp Finish
// CalculateDelay:
//         lda MenuData::ActionFlag
//         and #$08	;XMagic
//         beq :+
//         jmp MagicDelay
// :	lda MenuData::ActionFlag
//         and #$40	;Item
//         bne ItemDelay
//         lda MenuData::ActionFlag
//         and #$20	;Magic
//         beq :+
//         jmp MagicDelay
// :	lda MenuData::ActionFlag
//         and #$10	;Weapon used as item
//         beq WeaponAttackDelay
//         jmp WeaponUseDelay
// WeaponAttackDelay:	;despite the calculation, I don't think any weapons have delay values
//         stz $0E
//         lda DisplayInfo::CurrentChar
//         sta $24
//         lda #$54     ;84, size of GearStats struct
//         sta $25
//         jsr Multiply_8bit
//         ldy $26
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         beq :+
//         lda RHWeapon::Targetting,Y
//         and #$03	;delay bits (delay/10)
//         tax
//         lda f:AttackDelayTbl,X
//         sta $0E		;attack delay
// :       ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//         beq :+
//         lda LHWeapon,Y
//         and #$03	;delay bits (delay/10)
//         tax
//         clc
//         lda f:AttackDelayTbl,X
//         adc $0E		;add other weapon's delay
//         sta $0E
// :	lda $0E		;attack delay
//         jmp Finish
// ItemDelay:
//         lda MenuData::SelectedItem
//         tax
//         lda InventoryItems,X
//         ldx AttackerOffset
//         sta CharStruct::SelectedItem,X
//         sec
//         sbc #$E0	;consumable item offset
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         lda f:ConsumableItemProp+2,X
//         and #$08
//         bne :+
//         lda MenuData::SelectedItem
//         jsr ConsumeItem
// :	lda f:ConsumableItemProp,X
//         and #$03	;delay bits (delay/10)
//         tax
//         lda f:AttackDelayTbl,X
//         bra Finish
// MagicDelay:
//         stz $0E
//         lda MenuData::SelectedItem
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         lda f:AttackProp,X
//         and #$03	;delay bits (delay/10)
//         tax
//         lda f:AttackDelayTbl,X
//         sta $0E		;attack delay
//         lda MenuData::ActionFlag
//         and #$08	;X-Magic
//         beq FinishMagic
//         lda MenuData::SecondSelectedItem
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         lda f:AttackProp,X
//         and #$03	;delay bits (delay/10)
//         tax
//         clc
//         lda f:AttackDelayTbl,X
//         adc $0E		;add other spell's delay
//         sta $0E
// FinishMagic:
//         lda $0E		;attack delay
//         bra Finish
// WeaponUseDelay:
//         lda DisplayInfo::CurrentChar
//         sta $24
//         lda #$54     	;84, size of GearStats struct
//         sta $25
//         jsr Multiply_8bit
//         ldy $26
//         lda MenuData::SelectedItem
//         beq :+
//         longa
//         tya
//         clc
//         adc #$000C	;shifts offset from RHWeapon to LHWeapon
//         tay
//         shorta0
// :	lda RHWeapon::ItemMagic,Y	;could be LHWeapon
//         and #$7F	;weapon magic to cast
//         beq Finish
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         lda f:AttackProp,X
//         and #$03	;delay bits (delay/10)
//         tax
//         lda f:AttackDelayTbl,X
// Finish:
//         pha
//         lda DisplayInfo::CurrentChar
//         jsr GetTimerOffset	;Y and $36 = timer offset
//         ldx AttackerOffset
//         pla
//         jsr HasteSlowMod	;adjusts delay
//         sta CurrentTimer::ATB,Y	;time until action fires
//         lda #$41		;flag indicating a queued action
//         sta EnableTimer::ATB,Y
//         lda #$80		;physical/other
//         sta MenuData::ActionFlag
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
//         rts
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
//         and #$08   	;berserk
//         beq Finish
//         lda EncounterInfo::IntroFX
//         bpl NotCredits
// Finish:	tdc
//         rts
//         								;
// NotCredits:
//         lda CharStruct::AlwaysStatus2,X
//         ora #$08   	;berserk
//         sta CharStruct::AlwaysStatus2,X
//         rts
}

// Address: _1CB3
// Disables Magic and Commands when
// Status or MP prevents their use
static void disableCommandsMagic(void) {
//         tdc
//         tax
//         stx $16
//         lda Void
//         and #$40     	;void
//         beq :+
//         ldx #$0080
//         stx $16		;disables magic
// :	lda DisplayInfo::CurrentChar
//         jsr CalculateSpellOffset	;sets Y
//         longa
//         tdc
//         sta $12
//         sta $14
//         ldx AttackerOffset
//         lda CharStruct::CurMP,X
//         sta $0E		;current mp
//         lda CharStruct::Status3,X
//         ora CharStruct::AlwaysStatus3,X
//         sta $22		;status 3/4
//         lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//         sta $10		;status 1/2
//         and #$0400	;mute
//         beq :+
//         lda #$0080
//         sta $12		;disables magic
// :	lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//         and #$0020	;toad
//         beq :+
//         lda #$0080
//         sta $14		;disables magic
// :	tdc
//         tax
// DisableSpells:
//         lda CharSpells::Flags,Y
//         and #$0001	;skip mp/status checks
//         bne NextSpell
//         lda CharSpells::MP,Y
//         and #$00FF	;clear high part since it's an 8 bit field
//         cmp $0E		;current mp
//         beq CheckStatus
//         bcc CheckStatus
//         lda CharSpells::Flags,Y
//         ora #$0080
//         sta CharSpells::Flags,Y
//         bra NextSpell
// CheckStatus:
//         lda CharSpells::Flags,Y
//         and #$FF7F	;clear bit 80h in flags, disabled bit?
//         sta CharSpells::Flags,Y
//         lda CharSpells::ID,Y
//         and #$00FF
//         cmp #$0080	;blue magic
//         bcs NextSpell
//         lda CharSpells::Flags,Y
//         ora $12		;from mute
//         ora $14		;from toad
//         ora $16		;from void
//         sta CharSpells::Flags,Y
//         lda $16
//         bne NextSpell
//         lda $12
//         bne NextSpell
//         lda $14
//         beq NextSpell
//         lda CharSpells::ID,Y
//         and #$00FF
//         cmp #$0029	;toad spell
//         bne NextSpell
//         lda CharSpells::Flags,Y
//         and #$FF7F	;re-enable toad spell if toad status
//         sta CharSpells::Flags,Y
// NextSpell:
//         iny
//         inx
//         cpx #$0082	;130 spell slots
//         bne DisableSpells
//         shorta0
//         lda DisplayInfo::CurrentChar
//         sta $24
//         lda #$14	;20, size of CharCommands struct
//         sta $25
//         jsr Multiply_8bit
//         tdc
//         tax
//         stx $0E
//         ldy $26
//         longa
// DisableCommands:
//         lda CharCommands::ID,Y
//         and #$00FF
//         sta $12		;command id
//         beq DisableCommand
//         asl
//         tax
//         lda f:BattleCmdDisableStatus,X
//         and $10		;status 1/2
//         bne DisableCommand
//         lda $12		;command id
//         cmp #$0026	;show command
//         beq EnableCommand
//         lda $22		;status 3/4
//         and #$0100	;hidden
//         beq EnableCommand
// DisableCommand:
//         lda CharCommands::Flags,Y
//         ora #$0080	;disabled
//         sta CharCommands::Flags,Y
//         bra NextCommand
// EnableCommand:
//         lda CharCommands::Flags,Y
//         and #$FF7F	;enabled
//         sta CharCommands::Flags,Y
// NextCommand:
//         iny
//         inc $0E		;character index
//         lda $0E
//         cmp #$0004	;4 commands per character
//         bne DisableCommands
//         shorta0
//         rts
}

// Address: _1DC4
// Manage the ATB timer used for
// zombie/charm/berserk party members
// and set up their action when it is ready
//  ** bug: should probably check for death too (this is why berserkers always attack when they get up)
static void handleUncontrolledParty(void) {
//         tdc
//         tax
//         stx $3D		;char index, used in subroutines also
//         stx $3F		;char offset
// Loop:
//         ldx $3D
//         lda UncontrolledATB,X
//         beq ActionReady
//         ldx $3F
//         lda CharStruct::Status3,X
//         and #$10	;stop
//         bne Next
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$60	;sleep/paralyze
//         bne Next
//         ldx $3D
//         dec UncontrolledATB,X
//         bra Next
// ActionReady:
//         ldx $3F		;char offset
//         lda #$01
//         sta CharStruct::CmdCancelled,X
//         lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//         and #$02	;zombie
//         beq :+
//         jsr ZombieAction
//         bra Next
// :	lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$10	;charm
//         beq :+
//         jsr CharmAction
//         bra Next
// :	lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$08	;berserk
//         beq Next
//         jsr BerserkAction
// Next:
//         ldx $3F		;char offset
//         jsr NextCharOffset
//         stx $3F
//         inc a:$003D	;char index ; TODO: dont know why this is being done?
//         lda a:$003D
//         cmp #$04	;4 characters
//         bne Loop
//         rts
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
//         and #$0F			;white magic
//         ora CharStruct::EnableSpells+1,X	;black and time magic
//         beq Fight
//         jsr Random_0_99
//         cmp #$32	;50% chance of spell
//         bcc Magic
// Fight:
//         ldx $3F		;char offset
//         lda #$80
//         sta CharStruct::ActionFlag,X
//         lda #$05	;fight
//         sta CharStruct::Command,X
//         stz CharStruct::MonsterTargets,X
//         stz CharStruct::SelectedItem,X
//         stz CharStruct::SecondActionFlag,X
//         stz CharStruct::SecondCommand,X
//         stz CharStruct::SecondMonsterTargets,X
//         stz CharStruct::SecondPartyTargets,X
//         stz CharStruct::SecondSelectedItem,X
//         phx
//         tdc
//         tax
//         lda #$03
//         jsr Random_X_A    ;0..3
//         tax
//         tdc
//         jsr SetBit_X
//         plx
//         sta CharStruct::PartyTargets,X	;fight random party member
//         jmp _QueueUncontrolledAction
// Magic:
//         lda $3D		;char index
//         tax
//         stx $2A
//         ldx #$028A ; TODO: fixme .sizeof(CharSpells)	;650, size of CharSpells struct
//         stx $2C
//         jsr Multiply_16bit    ;**optimize: use rom table instead
//         ldx $2E
//         stx SpellOffsetRandom
//         stz $0E
// FindAnySpell:		;checks if any spells are learned
//         lda CharSpells::ID+18,X	;starts at first white spell
//         cmp #$46		;Quick spell
//         beq NextSpell
//         cmp #$FF		;empty spell slot
//         bne TryRandomSpell
// NextSpell:
//         inx
//         inc $0E
//         lda $0E
//         cmp #$36
//         bne FindAnySpell
//         bra Fight		;no spells, hit something instead
// TryRandomSpell:
//         ldx #$0012		;first white spell
//         lda #$47		;last time spell
//         jsr Random_X_A  	;random white/black/time spell
//         longa
//         adc SpellOffsetRandom
//         tax
//         shorta0
//         lda CharSpells::ID,X
//         cmp #$FF		;empty spell slot
//         beq TryRandomSpell	;keep trying until we hit a known spell
//         cmp #$46		;quick spell
//         beq TryRandomSpell	;is no good either
//         pha 			;holds known random spell
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         lda f:AttackProp,X
//         sta TempTargetting	;temp area
//         tdc
//         tay
//         sty $16			;target bits
//         lda TempTargetting
//         bne CheckTargetting
// TargetSelf:
//         longa
//         lda $3F			;Char Offset
//         jsr ShiftDivide_128	;char index (could've just loaded that)
//         tax
//         shorta0
//         jsr SetBit_X     	;target self if no targetting info
//         sta $16
//         bra TargetReady
// CheckTargetting:
//         and #$40		;hits all
//         bne TargetsAll
//         lda TempTargetting
//         and #$08		;targets enemy by default
//         bne TargetsEnemy
// TargetsOther:			;assumed to normally target party, now targets monsters
//         tdc
//         tax
//         lda #$07
//         jsr Random_X_A	     	;random monster 0..7
//         tax
//         tdc
//         jsr SetBit_X
//         sta $17			;monster target
//         bra TargetReady
// TargetsEnemy:			;normally targets enemy, now targets party
//         tdc
//         tax
//         lda #$03
//         jsr Random_X_A    	;random party 0..3
//         tax
//         tdc
//         jsr SetBit_X
//         sta $16			;party target
//         bra TargetReady
// TargetsAll:
//         lda TempTargetting
//         and #$08		;targets enemy by default
//         bne :+
//         lda #$FF
//         sta $17
//         bra TargetReady
// :	lda #$F0		;target all party members
//         sta $16
// TargetReady:
//         ldx $3F			;char Offset
//         pla 			;random known spell
//         sta CharStruct::SelectedItem,X
//         lda $16			;party targets
//         sta CharStruct::PartyTargets,X
//         lda $17			;monster targets
//         sta CharStruct::MonsterTargets,X
//         lda #$21		;magic + costs mp
//         sta CharStruct::ActionFlag,X
//         lda #$2C		;first magic command
//         sta CharStruct::Command,X
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
//         jsr GlobalTimers
// :	   tdc
//         tax
//         dec
//         									;:
// :	sta RandomOrder,X
//         inx
//         cpx #$000C
//         bne :-
//         									;.
//         tdc
//         tay 			;slot for writing
// _RandomizeOrder:
//         tdc
//         tax 			;slot for reading
//         lda #$0B
//         jsr Random_X_A		;0..11
//         sta $0E
//         ldx #$0000
//         									;:
// CheckValueInUse:		;see if we've used this number yet
//         lda $0E
//         cmp RandomOrder,X
//         beq _Next		;already used, try another
//         inx
//         cpx #$000C
//         bne CheckValueInUse
//         									;.
//         sta RandomOrder,Y	;if not, save it
//         iny 			;and select next writing slot
//         									;:
//  _Next:
//         cpy #$000C		;12 combatant slots
//         bne _RandomizeOrder
//         									;.
//         rts
}

// Address: _200B
// Updates Status/ATB timers for all combatants
// may skip updates depending on stop/etc.
static void updateTimers(void) {
//         jsr GlobalTimers
//         tdc
//         tax
//         stx $0A     		;char index
// Loop:	tdc
//         tay
//         sty $0C     		;timer index
//         lda $0A
//         jsr GetTimerOffset
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
// :       jsr UpdateTimer 	;first timer is stop
//         lda $08			;check if stop active
//         bne NextChar  		;don't process other timers if stopped
//         ldy #$0008  		;process 8 more status timers
// :       jsr UpdateTimer
//         dey
//         bne :-
//         jsr UpdateTimer 	;one more status timer (paralyze)
//         lda $08			;check if paralyze active
//         bne NextChar
//         jsr UpdateTimer  	;advance ATB timer if not paralyzed
// NextChar:
//         inc $0A     		;next char index
//         lda $0A
//         cmp #$0C		;12 combatants
//         bne Loop
//         rts
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
//         sta EnableTimer,X
// TimerActive:
//         lda $0C
//         bne :+		;doesn't branch anywhere regardless
// :       inc $08    	;timer triggered flag
// Finish:
//         ply 		;restore original Y
//         inx 		;next timer (in offset)
//         inc $0C		;next timer index
//         rts
}

// Decreases global status timers,
// then flags and reset those that trigger
// sets ProcessTimer to indicate that status
// should be updated this tick
static void globalTimers(void) {
//         tdc
//         tax
// DecTimer:
//         lda GlobalTimer,X
//         beq Triggered
//         dec GlobalTimer,X
//         stz ProcessTimer,X
//         bra :+
// Triggered:
//         lda #$01
//         sta ProcessTimer,X		;flag timer for processing
//         lda f:TimerDurTbl,X		;reset timer from rom
//         sta GlobalTimer,X
//         							;:
// :	inx
//         cpx #$000B			;11 timers
//         bne DecTimer
//         rts
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
//         tdc
//         tax
//         stx $08			;timer index
//         tay
// :	sta TimerEnded,Y
//         iny
//         cpy #$000B
//         bne :-
// TimerLoop:	;for each timer, loop finds the first character for whom that timer ended, checking in a "random" order
//         tdc
//         tax
//         stx $0A			;char count
//         ldx $08			;timer index
//         lda RandomOrderIndex,X
//         pha 			;original RandomOrderIndex
// CharLoop:	;searches characters in a "random" order
//         ldx $08			;timer index
//         lda RandomOrderIndex,X
//         tax
//         lda RandomOrder,X
//         sta $0C			;char index
//         tax
//         lda PauseTimerChecks,X
//         bne NextChar
//         lda CurrentlyReacting
//         bne :+
//         lda QuickTimeFrozen,X
//         bne NextChar
// :	lda $0C			;char index
//         jsr GetTimerOffset      ;Y = Timer Offset
//         tya
//         clc
//         adc $08
//         tax 			;timer offset + index
//         lda EnableTimer,X
//         bpl NextChar		;80h must be set to contiue
//         lda $0C
//         tay
//         lda ActiveParticipants,Y
//         beq NextChar
//         lda $08			;timer index
//         cmp #$01		;poison
//         beq PoisonCountRegen
//         cmp #$03		;countdown
//         beq PoisonCountRegen
//         cmp #$07		;regen
//         bne EndTimer
// PoisonCountRegen:	;skips ending timer for these status if they're also erased/hidden/jumping
//         phx 		;timer offset + index
//         ldx $08
//         lda RandomOrderIndex,X
//         tax
//         lda RandomOrder,X
//         longa
//         jsr ShiftMultiply_128
//         tax
//         shorta0
//         lda CharStruct::Status4,X
//         and #$81	;erased or hidden
//         bne NextCharPLX
//         lda CharStruct::CmdStatus,X
//         and #$10	;jumping
//         beq EndTimerPLX
// NextCharPLX:
//         plx
//         bra NextChar
// EndTimerPLX:
//         plx 		;timer offset + index
// EndTimer:		;sets flag that timer has ended, so effects can be applied later
//         pla
//         lda EnableTimer,X
//         and #$7E	;clear $81
//         sta EnableTimer,X
//         ldx $08		;timer index
//         phx
//         lda #$01	;flag that we found someone timer ended for
//         sta TimerEnded,X
//         lda RandomOrderIndex,X
//         tax
//         lda RandomOrder,X
//         plx 		;timer index
//         sta TimerReadyChar,X	;which character had their timer end
//         bra NextTimer	;don't check any more characters for this timer
// NextChar:	;this character's timer didn't end or isn't eligable,
//         	;keep looking until all have been checked or one is found
//         ldx $08		;timer index
//         inc RandomOrderIndex,X
//         lda RandomOrderIndex,X
//         cmp #$0C	;reset index at 12
//         bne :+
//         stz RandomOrderIndex,X
// :       inc $0A        	;char count
//         lda $0A
//         cmp #$0C	;12 chars
//         beq :+
//         jmp CharLoop
// :       pla 		;original RandomOrderIndex
//         sta RandomOrderIndex,X
// NextTimer:
//         inc $08        	;next timer index
//         lda $08
//         cmp #$0B	;11 timers
//         beq Ret
//         jmp TimerLoop
// Ret:	rts
}

static void applyTimerEffects(void) {
//         tdc
//         tax
//         stx ProcessingTimer
// Loop:
//         ldx ProcessingTimer
//         lda TimerEnded,X
//         beq NextTimer
//         inc RandomOrderIndex,X
//         lda RandomOrderIndex,X
//         cmp #$0C		;12 chars
//         bne :+
//         stz RandomOrderIndex,X
// :	    lda TimerReadyChar,X
//         jsr GetTimerOffset    	;sets Y to timer offset
//         lda TimerReadyChar,X
//         jsr CalculateCharOffset
//         lda ProcessingTimer
//         beq TimerEffect    	;timer 0 is stop, skips below check
//         lda EnableTimer,Y	;bits 80h and 01 are cleared prev
//         bne NextTimer    	;skip effect if any other bits set
// TimerEffect:
//         jsr DispatchTimerEffect
// NextTimer:
//         inc ProcessingTimer
//         lda ProcessingTimer
//         cmp #$0B		;11 timers
//         bne Loop
//         rts
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
//         sta EnableTimer::Poison,Y
//         lda InitialTimer::Poison,Y
//         sta CurrentTimer::Poison,Y
//         jsr WipeDisplayStructures
//         longa
//         ldx AttackerOffset
//         lda CharStruct::MaxHP,X
//         jsr ShiftDivide_16
//         bne :+
//         inc 				;min 1 damage
// :	sta $0E				;poison tick damage
//         sec
//         lda CharStruct::CurHP,X
//         sbc $0E				;poison tick damage
//         bcs :+
//         tdc 				;min 0 hp
// :	sta CharStruct::CurHP,X
//         shorta0
//         lda TimerReadyChar::Poison
//         ldx $0E				;poison tick damage
//         stx TempDisplayDamage
//         jsr CopyDisplayDamage
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
//         and #$02	;zombie
//         bne Ret
//         lda TimerReadyChar::Countdown
//         jsr KillCharacter
//         lda MonsterDead
//         beq Ret
//         lda #$07	;C1 routine: condemn death animation
//         jsr CallC1
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
//         sta EnableTimer::Old,Y
//         lda InitialTimer::Old,Y
//         sta CurrentTimer::Old,Y
//         ldx AttackerOffset
//         stz $0E
// StatsLoop:		;applies to all 4 main stats
//         lda CharStruct::BaseStr,X
//         dec
//         beq :+		;**bug: wraps 0 stats to 255
//         sta CharStruct::BaseStr,X
// :	lda CharStruct::EquippedStr,X
//         dec
//         beq :+
//         sta CharStruct::EquippedStr,X
// :	inx
//         inc $0E
//         lda $0E
//         cmp #$04	;4 stats
//         bne StatsLoop
//         ldx ProcessingTimer
//         lda TimerReadyChar,X
//         cmp #$04	;monster check
//         bcc Ret
//         ldx AttackerOffset
//         lda CharStruct::Level,X
//         dec
//         beq :+
//         sta CharStruct::Level,X
// :	lda CharStruct::MonsterAttack,X
//         dec
//         bpl Ret	;bug? only decreases attack if above 128
//         sta CharStruct::MonsterAttack,X
// Ret:	rts
}

static void timerEffectRegen(void) {
//         lda #$01
//         sta EnableTimer::Regen,Y
//         lda InitialTimer::Regen,Y
//         cmp #$1E
//         bcs :+
//         lda #$1E	;max 30 ticks if it was slower
//         sta InitialTimer::Regen,Y
// :	sta CurrentTimer::Regen,Y
//         jsr WipeDisplayStructures
//         ldx AttackerOffset
//         jsr CopyStatsWithBonuses
//         lda Level
//         sta $24
//         lda Vitality
//         sta $25
//         jsr Multiply_8bit
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//         and #$02	;zombie
//         bne Ret
//         longa
//         lda $26
//         jsr ShiftDivide_16
//         tax
//         bne :+
//         inc 		;min 1
// :	sta $0E
//         ldx AttackerOffset
//         clc
//         adc CharStruct::CurHP,X
//         bcs :+
//         cmp CharStruct::MaxHP,X
//         bcc :++
// :	lda CharStruct::MaxHP,X	;cap at maxhp
// :	sta CharStruct::CurHP,X
//         shorta0
//         lda $0F
//         ora #$80       		;flag to display as healing
//         sta $0F
//         lda TimerReadyChar::Regen
//         ldx $0E
//         stx TempDisplayDamage
//         jsr CopyDisplayDamage
//         lda #$09	;C1 routine: display regen/poison damage
//         jsr CallC1
// Ret:	rts
}

static void timerEffectSing(void) {
//         lda #$01
//         sta EnableTimer::Sing,Y
//         lda InitialTimer::Sing,Y
//         sta CurrentTimer::Sing,Y
//         tdc
//         tay
//         ldx AttackerOffset
//         lda CharStruct::Song,X
//         beq Ret
// FindSong:		;Y = song stat index
//         asl
//         bcs :+
//         iny
//         bra FindSong
// :       sty $12		;song stat index
//         tdc
//         tax
//         stx $0E		;target
//         lda #$04
//         sta $10		;after last target
//         lda TimerReadyChar::Sing
//         cmp #$04	;monster check? monsters can sing?
//         bcc ApplySong
//         lda #$04
//         sta $0E		;target
//         lda #$0C
//         sta $10		;last target +1
//         ldx #$0180	;**bug: should be $0200 for first monster
// ApplySong:
//         stx $14		;char offset
//         longa
//         txa
//         clc
//         adc $12		;adjust offset by song stat
//         tax
//         shorta0
// CharLoop:
//         ldy $0E		;target
//         lda ActiveParticipants,Y
//         beq Next
//         clc
//         lda CharStruct::BonusStr,X	;different stats depending on X
//         inc
//         cmp #$64	;don't apply changes at 100 and up
//         bcs Next
//         sta CharStruct::BonusStr,X
// Next:
//         jsr NextCharOffset
//         stx $14		;char offset
//         inc $0E		;next target
//         lda $0E
//         cmp $10		;last target +1
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
//         jsr CheckBattleEnd
//         lda BattleOver
//         bne GoRet
//         lda TimerReadyChar::ATB
//         sta AttackerIndex
//         jsr GetTimerOffset
//         tyx
//         lda EnableTimer::Paralyze,X
//         bne GoRet
//         lda EnableTimer::ATB,X
//         beq :+
//         jmp PerformAction      	;action is ready, do it
// :	lda TimerReadyChar::ATB
//         cmp #$04	;monster check
//         bcs Monster
//         tdc
//         tax
// SearchTurnQueue:	;find character in turn queue
//         lda ATBReadyQueue,X
//         cmp TimerReadyChar::ATB
//         beq GoRet	;character already in turn queue
//         inx
//         cpx #$0004
//         bne SearchTurnQueue
//         lda TimerReadyChar::ATB
//         jsr CheckDisablingStatus
//         bne GoRet
//         ldx ATBReadyCount
//         lda TimerReadyChar::ATB
//         sta ATBReadyQueue,X
//         inc ATBReadyCount
// GoRet:	jmp Ret
// Monster:
//         jsr MonsterATB
// Ret:	rts
}

// Called when character's turn is up,
// perform their queued action
static void performAction(void) {
//         jsr ProcessTurn
//         lda DelayedFight
//         bne Ret
//         lda AttackerIndex
//         cmp #$04	;monster check
//         bcs _ResetATB
//         ldx AttackerOffset
//         lda CharStruct::CmdStatus,X
//         and #$E0	;clear many flags (jump/flirt/others?)
//         sta CharStruct::CmdStatus,X
//         stz CharStruct::DamageMod,X
//         lda CharStruct::Status1,X
//         ora CharStruct::AlwaysStatus1,X
//         and #$02	;zombie
//         bne Uncontrolled
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$18	;charm/berserk
//         beq _ResetATB
// Uncontrolled:
//         lda AttackerIndex
//         jsr GetTimerOffset
//         tdc
//         sta EnableTimer::ATB,Y
//         inc
//         sta CurrentTimer::ATB,Y
//         lda AttackerIndex
//         tax
//         lda UncontrolledATB,X
//         and #$7F	;max 127
//         sta UncontrolledATB,X
// _ResetATB:
//         inc CheckQuick
//         lda AttackerIndex
//         jsr ResetATB
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
//         sta ATBWaitLeft
//         bne Ret
// DoneWaiting:
//         tdc
//         sta ATBWaiting
// Ret:	rts
}

// Updates ATB for all combatants and
// sets them active if present
static void resetAtbAll(void) {
//         tdc
//         tax
//         tay
//         stx $0E			;char index
// ResetATBLoop:
//         lda $0E
//         jsr ResetATB
//         lda $0E
//         jsr CalculateCharOffset
//         lda $0E
//         cmp #$04		;monster check
//         bcs Monster
//         ldx AttackerOffset
//         lda CharStruct::CharRow,X
//         and #$40		;not present
//         beq SetActive
//         bne Next
// Monster:
//         sec
//         lda $0E
//         sbc #$04
//         tax 			;monster index
//         lda InitialMonsters,X
//         beq Next
// SetActive:
//         ldx $0E
//         lda #$01
//         sta ActiveParticipants,X
// Next:
//         inc $0E			;char index
//         lda $0E
//         cmp #$0C		;12 participants
//         bne ResetATBLoop
//         									;.
//         rts
}

// Initialize ATB (A: character index 0-12)
static void resetAtb(void) {
//         pha
//         jsr GetTimerOffset	;Y and $36 = timer offset
//         pla
//         jsr CalculateCharOffset
//         jsr CopyStatsWithBonuses
//         lda CharStruct::EqWeight,X
//         jsr ShiftDivide_8	;weight/8
//         clc
//         adc #$78     		;+120
//         sec
//         sbc Agility    	;-agi
//         beq :+
//         bcs :++
// :	lda #$01     		;min 1
// :       jsr HasteSlowMod
//         sta CurrentTimer::ATB,Y
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
//         sta CurrentTimer::ATB,Y
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
//         jsr ClearQuick
//         ply
//         bra EnableATB
// Quick:										;:
//         lda #$01
//         sta CurrentTimer::ATB,Y
// EnableATB:
//         lda #$01
//         sta EnableTimer::ATB,Y
//         rts
}

// Unfreezes time for everyone
static void clearQuick(void) {
//         tdc
//         tax
// :	    stz QuickTimeFrozen,X
//         inx
//         cpx #$000C		;12 combatants
//         bne :-
//         rts
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
//         sta AISkipDeadCheck
//         sec
//         lda AttackerIndex
//         sbc #$04
//         sta MonsterIndex
//         jsr ShiftMultiply_16
//         tax
//         stx MonsterOffset16
//         asl
//         tax
//         stx MonsterOffset32
//         tdc
//         tay
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
//         asl
//         tax
//         lda f:_d0ee95,X
//         sta $0E
//         lda f:_d0ee95+1,X
//         sta $0F
//         tdc
//         tay
//         ldx $0E		;MonsterIndex *100
//         lda #$FF
// :	sta MonsterAIScript,X
//         inx
//         iny
//         cpy #$0064	;init 100 bytes to $FF
//         bne :-
//         lda AttackerIndex
//         jsr CalculateCharOffset
//         ldx AttackerOffset
//         lda #$2C       	;magic
//         sta CharStruct::Command,X
//         lda #$21	;magic + costs mp
//         sta CharStruct::ActionFlag,X
//         ldx AttackerOffset
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$08	;berserk
//         beq CheckCharm
//         lda #$01
//         sta CharStruct::CmdCancelled,X
//         lda #$80	;monster fight
//         sta AIBuffer
//         lda #$FF	;end of list
//         sta AIBuffer+1
//         jsr DispatchAICommands
//         jmp GoFinish
// CheckCharm:
//         lda CharStruct::Status2,X
//         ora CharStruct::AlwaysStatus2,X
//         and #$10	;charm
//         beq CheckFlirt
// TryRandomAction:
//         ldx AttackerOffset
//         lda #$01
//         sta CharStruct::CmdCancelled,X
//         tdc
//         tax
//         lda #$03
//         jsr Random_X_A 	;0..3
//         tax
//         stx $0E
//         lda MonsterIndex
//         asl
//         tax
//         longa
//         lda BattleMonsterID,X
//         jsr ShiftMultiply_4
//         clc
//         adc $0E		;random number 0..3
//         tax 		;offset into control actions table
//         shorta0
//         lda f:MonsterControl,X
//         cmp #$FF
//         beq TryRandomAction	;no action in this slot, try again
//         sta AIBuffer
//         lda #$FF	;end of list
//         sta AIBuffer+1
//         inc TempCharm
//         jsr DispatchAICommands
//         bra GoFinish
// CheckFlirt:								;
//         lda CharStruct::CmdStatus,X
//         and #$08	;flirt
//         beq CheckControl
//         lda #$51	;throbbing command
//         sta CharStruct::Command,X
//         lda #$80	;other
//         sta CharStruct::ActionFlag,X
//         bra GoFinish
// CheckControl:
//         lda CharStruct::Status4,X
//         and #$20	;control
//         bne Control
//         lda CharStruct::Status2,X
//         and #$40	;sleep
//         bne Sleep
//         bra Normal
// Control:
//         tdc
//         tay
// :	lda ControlTarget,Y
//         cmp AttackerIndex
//         beq FoundController
//         iny
//         bra :-
// FoundController:
//         lda ControlCommand,Y
//         bne _ControlCommand
// Sleep:	;or controlled without a command
//         stz CharStruct::Command,X
//         lda #$80	;action complete?
//         sta CharStruct::ActionFlag,X
//         bra GoFinish
// _ControlCommand:
//         tdc
//         sta ControlCommand,Y
//         lda MonsterIndex
//         tax
//         lda MonsterControlActions,X
//         sta AIBuffer
//         lda #$FF	;end of list
//         sta AIBuffer+1
//         jsr DispatchAICommands
// GoFinish:
//         jmp Finish
// Normal:
//         lda MonsterIndex
//         tax
//         lda AIActiveConditionSet,X
//         sta AICurrentActiveCondSet
//         lda MonsterIndex
//         asl
//         tax
//         longa
//         clc
//         lda f:_d0eea5,X	;*1620, size of MonsterAI struct
//         adc #MonsterAI
//         sta AIOffset
//         shorta0
//         stz AICurrentCheckedSet
// CheckAIConditions:
//         lda AICurrentCheckedSet
//         tax
//         lda f:_d0eec9,X	;size of a MonsterAI condition
//         tay
//         sty AIConditionOffset
//         stz AICheckIndex
// CheckSingleCondition:
//         ldy AIConditionOffset
//         lda (AIOffset),Y
//         beq AIActions		;0 always succeeds
//         cmp #$FE		;indicates end of condition set
//         beq AIActions
//         jsr CheckAICondition
//         lda AIConditionMet
//         beq NextConditionSet
//         longa
//         clc
//         lda AIConditionOffset
//         adc #$0004		;next condition in set
//         sta AIConditionOffset
//         shorta0
//         inc AICheckIndex
//         bra CheckSingleCondition
// NextConditionSet:	;failed a condition in this set, check next set of conditions
//         inc AICurrentCheckedSet
//         lda AICurrentCheckedSet
//         cmp #$0A		;10 conditions max
//         bne CheckAIConditions
// AIActions:
//         longa
//         clc
//         lda AIOffset
//         adc #$00AA	;advances from Conditions to Actions
//         sta AIOffset
//         shorta0
//         lda AICurrentActiveCondSet
//         cmp AICurrentCheckedSet
//         beq ConditionOK	;matches so don't need to change things
//         lda MonsterIndex
//         tax
//         lda AICurrentCheckedSet
//         sta AIActiveConditionSet,X	;checked cond is now current
//         lda MonsterIndex
//         asl
//         tay
//         lda AICurrentCheckedSet
//         asl
//         tax
//         lda f:_d0eeb5,X
//         sta AICurrentOffset,Y
//         lda f:_d0eeb5+1,X
//         sta AICurrentOffset+1,Y
// ConditionOK:
//         jsr ProcessAIScript
// Finish:
//         ldx MonsterOffset16
//         lda MonsterMagic,X
//         longa
//         jsr ShiftMultiply_8
//         tax
//         shorta0
//         lda f:AttackProp,X
//         and #$03       	;delay values
//         tax
//         lda f:AttackDelayTbl,X
//         pha
//         lda AttackerIndex
//         jsr GetTimerOffset
//         pla
//         sta CurrentTimer::ATB,Y    ;**bug? doesn't adjust for haste/slow
//         lda #$41	;pending action
//         sta EnableTimer::ATB,Y
//         lda MonsterIndex
//         asl
//         tax
//         stz ForcedTarget::Party,X
//         stz ForcedTarget::Monster,X
//         rts
}

static void CheckAICondition(void) {
//     cmp #$13	;$12 is last valid condition
//         bcc :+
//         tdc 		;always succeed	(if invalid)
// :	sta $0E		;condition to check
//         asl
//         tax
//         lda f:AICondition,X
//         sta $08
//         lda f:AICondition+1,X
//         sta $09
//         lda #$C2    ;.b #bank(AICondition)
//         sta $0A
//         iny
//         lda (AIOffset),Y
//         sta AIParam1
//         iny
//         lda (AIOffset),Y
//         sta AIParam2
//         iny
//         lda (AIOffset),Y
//         sta AIParam3
//         stz AIConditionMet
//         lda AISkipDeadCheck
//         bne Jump
//         ldx AttackerOffset
//         lda CharStruct::CurHP,X
//         ora CharStruct::CurHP+1,X
//         beq Dead
//         lda CharStruct::Status1,X
//         and #$C0	;dead or stone
//         beq NotDead
// Dead:
//         lda $0E
//         cmp #$0F	;condition: dead
//         beq Jump
//         rts

// NotDead:
//         lda $0E
//         cmp #$0F	;auto-fail condition: dead if not dead
//         bne Jump
//         rts

// Jump:       jml [$0008]	;jump to AICondition table

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
    // inc AIConditionMet
    // rts
}

// Address: _283E
// AI Condition 01: Check Status
// Param1: AITarget routine
// Param2: Status offset (0-3 for status 1-4)
// Param3: Status bits
// if checking for death status,
// also succeed if hp is 0 (though this behavior is bugged)
static void aiCondition01(void) {
//         lda AIParam1
//         jsr GetAITarget	;populates list of targets to check
//         lda AIParam2
//         tax
//         stx $0E
//         tdc
//         tay
// Loop:	longa
//         lda AITargetOffsets,Y
//         cmp #$FFFF	;end of list or no target found
//         bne TargetFound
//         shorta0
//         bra Finish
// TargetFound:
//         sta $10		;target offset
//         clc
//         adc $0E		;status offset
//         tax
//         shorta0
//         lda CharStruct::Status1,X	;could be status 1-4 depending
//         ora CharStruct::AlwaysStatus1,X	;on status offset
//         and AIParam3
//         bne Match
//         lda $0E
//         bne Next
//         lda AIParam3
//         bpl Next
//         ldx $10			;if asked to check death status
//         lda CharStruct::CurHP,X	;also succeed if hp is 0
//         ora CharStruct::CurHP,X	;**bug: should be high byte $2007
//         bne Next
// Match:       inc AIConditionMet
// Next:	iny
//         iny
//         cpy #$0018	;12 characters * 2 bytes
//         bne Loop
// Finish:			;fail if any targets failed
//         lda AIMultiTarget
//         beq Ret
//         lda AITargetCount
//         cmp AIConditionMet
//         beq Ret
//         stz AIConditionMet
// Ret:	rts
}

// AI Condition 02: HP less than value
// Param1: AITarget routine
// Param2: HP (low byte)
// Param3: HP (high byte)
static void aiCondition02(void) {
//         lda AIParam1
//         jsr GetAITarget
//         tdc
//         tay
// Loop:	longa
//         lda AITargetOffsets,Y
//         tax
//         cmp #$FFFF	;end of list or no target found
//         beq FinishMode
//         lda CharStruct::CurHP,X
//         cmp AIParam2
//         bcs Next
//         inc AIConditionMet
// Next:	tdc
//         shorta
//         iny
//         iny
//         cpy #$0018	;12 characters * 2 bytes
//         bne Loop
//         bra Finish	;not needed (resetting mode is harmless)
// FinishMode:		;need to fix A back to 8 bit
//         shorta0
// Finish:			;fail if any targets failed
//         lda AIMultiTarget
//         beq Ret
//         lda AITargetCount
//         cmp AIConditionMet
//         beq Ret
//         stz AIConditionMet
// Ret:	rts
}

// AI Condition 03: Check Variable
// Param2: Var to check (0-3)
// Param3: Value
static void aiCondition03(void) {
//         lda AIParam2
//         tax
//         lda AIVars,X
//         cmp AIParam3
//         bne Fail
//         inc AIConditionMet
// Fail:	rts
}

// AI Condition 04: Alone
// Param2:
//  - if 0, succeeds when completely alone
//	- if non-0, succeeds when all active monsters are the same
static void aiCondition04(void) {
//         lda AIParam2
//         bne CheckSame
//         lda MonstersVisible
//         jsr CountSetBits
//         dex
//         beq Met
//         rts

// CheckSame:
//         lda MonsterIndex
//         asl
//         tax
//         lda BattleMonsterID,X
//         sta $0E
//         tdc
//         tay
// Loop:	lda ActiveParticipants+4,Y
//         beq Next
//         tya
//         asl
//         tax
//         lda BattleMonsterID,X
//         cmp $0E
//         bne Fail
// Next:	iny
//         cpy #$0008
//         bne Loop
// Met:
//         inc AIConditionMet
// Fail:	rts
}

// AI Condition 05: Compare Visible Monsters
// Param1:
//  - if 0, succeeds if visible monsters match
//    provided value
//	- if non-0, succeeds if they do not match
//Param3: Monster Bits (1 bit per monster)
static void aiCondition05(void) {
//         lda AIParam1
//         beq CheckMatch
//         lda MonstersVisible
//         cmp AIParam3
//         bne Met
//         rts

// CheckMatch:
//         lda MonstersVisible
//         cmp AIParam3
//         bne Fail
// Met:    inc AIConditionMet
// Fail:	rts
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
//         ldx AttackerOffset
//         lda ReactionFlags
//         and #$01
//         bne Reaction2	;Check 2nd set of reactions instead
//         lda AIParam2	;command
//         cmp #$07	;used as a flag to skip command check
//         beq SkipCmdCheck1
//         lda AIParam1	;invert checks
//         beq CheckCmdMatch1
//         lda AIParam2
//         cmp CharStruct::Reaction1Command,X
//         bne Met	;if param1 is >0, succeed when no cmd match
//         rts

// CheckCmdMatch1:
//         lda AIParam2
//         cmp CharStruct::Reaction1Command,X
//         bne Fail	;if param1 is 0, fail when no cmd match
// SkipCmdCheck1:		;command match or command $07 override
//         lda AIParam1
//         beq CheckElemMatch1
//         lda AIParam3	;element
//         and CharStruct::Reaction1Element,X
//         beq Met	;if param1 is >0, succeed when no elem match
//         rts	;(only reachable via the $07 override)
// CheckElemMatch1:
//         lda AIParam3
//         beq Met	;succeed when element is 0
//         and CharStruct::Reaction1Element,X
//         bne Met	;or when any element matches
//         rts

// Reaction2:	;same logic as above, but react to the second stored command
//         lda AIParam2
//         cmp #$07
//         beq SkipCmdCheck2
//         lda AIParam1
//         beq CheckCmdMatch2
//         lda AIParam2
//         cmp CharStruct::Reaction2Command,X
//         bne Met
//         rts

// CheckCmdMatch2:
//         lda AIParam2
//         cmp CharStruct::Reaction2Command,X
//         bne Fail
// SkipCmdCheck2:
//         lda AIParam1
//         beq CheckElemMatch2
//         lda AIParam3
//         and CharStruct::Reaction2Element,X
//         beq Met
//         rts

// CheckElemMatch2:
//         lda AIParam3
//         beq Met
//         and CharStruct::Reaction2Element,X
//         beq Fail
// Met:       inc AIConditionMet
// Fail:	rts
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
//         ldx AttackerOffset
//         lda ReactionFlags
//         and #$01
//         bne Reaction2	;Check 2nd set of reactions instead
//         lda AIParam2	;command
//         cmp #$07	;used as a flag to skip command check
//         beq SkipCmdCheck1
//         lda AIParam1	;invert checks if set
//         beq CheckCmdMatch1
//         lda AIParam2
//         cmp CharStruct::Reaction1Command,X
//         bne Met	;if param1 is >0, succeed when no cmd match
//         rts

// CheckCmdMatch1:
//         lda AIParam2
//         cmp CharStruct::Reaction1Command,X
//         bne Fail	;if param1 is 0, fail when no cmd match
// SkipCmdCheck1:		;command match or command $07 override
//         lda AIParam1
//         beq CheckCatMatch1
//         lda AIParam3	;category
//         and CharStruct::Reaction1Category,X
//         beq Met	;if param1 >0, succeed when no category match
//         rts

// CheckCatMatch1:
//         lda AIParam3
//         beq Met	;succeed when category is 0
//         and CharStruct::Reaction1Category,X
//         bne Met	;or when any category matches
//         rts

// Reaction2:	;same logic as above, but react to the second stored command
//         lda AIParam2
//         cmp #$07	;used as a flag to skip command check
//         beq SkipCmdCheck2
//         lda AIParam1
//         beq CheckCmdMatch2
//         lda AIParam2
//         cmp CharStruct::Reaction2Command,X
//         bne Met
//         rts

// CheckCmdMatch2:
//         lda AIParam2
//         cmp CharStruct::Reaction2Command,X
//         bne Fail
// SkipCmdCheck2:
//         lda AIParam1
//         beq CheckCatMatch2
//         lda AIParam3
//         and CharStruct::Reaction2Category,X
//         beq Met
//         rts

// CheckCatMatch2:
//         lda AIParam3
//         beq Met
//         and CharStruct::Reaction2Category,X
//         beq Fail
// Met:       inc AIConditionMet
// Fail:	rts
}

// AI Condition $08: Reaction to Magic
// Param1: if set, inverts test so a match
//         fails the condition
// Param2: Spell
static void aiCondition08(void) {
//         ldx AttackerOffset
//         lda ReactionFlags
//         and #$01	;check second set of reactions
//         bne Reaction2
//         lda AIParam1
//         beq CheckMatch1
//         lda CharStruct::Reaction1Magic,X
//         cmp AIParam2
//         bne Met
//         rts

// CheckMatch1:
//         lda CharStruct::Reaction1Magic,X
//         cmp AIParam2
//         beq Met
//         rts

// Reaction2:
//         lda AIParam1
//         beq CheckMatch2
//         lda CharStruct::Reaction2Magic,X
//         cmp AIParam2
//         bne Met
//         rts

// CheckMatch2:
//         lda CharStruct::Reaction2Magic,X
//         cmp AIParam2
//         bne Fail
// Met:       inc AIConditionMet
// Fail:	rts
}

// AI Condition $09: Reaction to Item
// Param1: if set, inverts test so a match
//         fails the condition
// Param2: Item
static void aiCondition09(void) {
//         ldx AttackerOffset
//         lda ReactionFlags
//         and #$01	;check second set of reactions
//         bne Reaction2
//         lda AIParam1
//         beq CheckMatch1
//         lda CharStruct::Reaction1Item,X
//         cmp AIParam2
//         bne Met
//         rts

// CheckMatch1:
//         lda CharStruct::Reaction1Item,X
//         cmp AIParam2
//         beq Met
//         rts

// Reaction2:
//         lda AIParam1
//         beq CheckMatch2
//         lda CharStruct::Reaction2Item,X
//         cmp AIParam2
//         bne Met
//         rts

// CheckMatch2:
//         lda CharStruct::Reaction2Item,X
//         cmp AIParam2
//         bne Fail
// Met:       inc AIConditionMet
// Fail:	rts
}

// AI Condition $0A: Reaction to Targetting
// Param3: if 0, succeeds when attack was single target
//	       if non-0, succeeds when attack was multi target
static void aiCondition0A(void) {
//         lda ReactionFlags
//         and #$01	;check second set of reactions
//         bne Reaction2
//         ldx AttackerOffset
//         lda CharStruct::Reaction1Targets,X
//         jsr CountSetBits
//         dex 		;targets -1
//         bmi Fail	;fail for 0 targets
//         jmp CheckInvert
// Reaction2:
//         ldx AttackerOffset
//         lda CharStruct::Reaction2Targets,X
//         jsr CountSetBits
//         dex 		;targets -1
//         bmi Fail	;fail for 0 targets
//         jsr CheckInvert
// Fail:	rts
// CheckInvert:
//         lda AIParam3	;inverts
//         bne Invert
//         txa
//         bne Fail2	;fail for >1 targets
//         beq Met	;succeed for exactly 1 target
// Invert:
//         txa
//         beq Fail2	;fail for exactly 1 target
// Met:       inc AIConditionMet
// Fail2:	rts
}

// Address: _2AD2
// AI Condition 0B: Check CharStruct param
// Param1: AITarget routine
// Param2: Offset within CharStruct to check
// Param3: Value for success
static void aiCondition0B(void) {
//         lda AIParam1
//         jsr GetAITarget	;populates list of targets to check
//         lda AIParam2
//         tax
//         stx $0E		;Offset within CharStruct
//         tdc
//         tay
// Loop:	longa
//         lda AITargetOffsets,Y
//         cmp #$FFFF	;end of list or no target found
//         bne TargetFound
//         shorta0
//         bra Finish
// TargetFound:
//         clc
//         adc $0E		;Offset within CharStruct
//         tax
//         shorta0
//         lda CharStruct::CharRow,X	;check any single CharStruct byte
//         cmp AIParam3		;compare with provided value
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
//         cmp AIConditionMet
//         beq Ret
//         stz AIConditionMet
// Ret:	rts
}