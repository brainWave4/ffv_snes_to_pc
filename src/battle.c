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
    //  PusH Processor flags stack
    //  Lengthen Accumulator AND A with XY Indexes to 16-bits
    //  PusH data Bank register
    //  PusH Direct page register
    //  PusH Accumulator
    //  PusH X Index
    //  Push Y Index
    //  LoaD #0 onto Accumulator
    //  Shorten Accumulator to 8-bits
    //  Lengthen Indexes to 16-bits
    //  Jump to SubRoutine SetupRegisters   (Call setUpRegisters())
    setupRegisters();

    //  Lengthen A to 16-bits
    //  CLear Carry flag
    //  LoaD $09c0 to A
    //  ADd #1 to accumulator with Carry
    //  Branch to [0023] if Carry Clear
    //  LoaD #$ffff to A
    //  [0023] Store A to $09c0
    if (battleCount < 0xffff) ++battleCount;

    //  Clear A, then Shorten
    //  Store Zero to $7cd8

    //  [002c] Jump to SubRoutine StartBattle      (Call startBattle())
    //  LoaD #0 to A
    //  STore A to f:hINIDISP
    //  STore A to f:hHDMAEN
    //  STore A to f:hMDMAEN
    //  STore A to f:hNMITIMEN
    //  LoaD $7cd8 to A
    //  Branch to [002c] if Not Equals
    //  SEt Interrupt flag
    //  Jump to SubRoutine SetupRegisters   (Call setUpRegisters())
    //  Lenghten Accumulator AND A with XY Indexes to 16-bits
    //  PulL Y Index
    //  PulL X Index
    //  PulL Accumulator
    //  PulL Direct page register
    //  PulL data Bank register
    //  PulL Processor flags
    //  Return To previously saved address, from subroutine Long
}

// Address: _0053
static void setupRegisters(void) {
    //  LoaD #0 to Accumulator
    //  PusH Accumulator
    //  PulL data Bank register
    //  STore Accumulator to hNMITIMEN
    //  LoaD #$0000 to X
    //  PusH X
    //  PulL Direct page register
    //  LoaD #$80 to Accumulator
    //  STore Accumulator to hINIDISP
    //  LoaD #$7E to Accumulator
    //  PusH Accumulator
    //  PulL data Bank register
    //  Return to SubRoutine
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
    //  Shorten Indexes
    //  STore X to $3c
    //  ComPare X with #$ff
    //  Branch to next label if Not Equals
    //  BRAnch to [Finish]
    //  [LBL] CoMPare A with #00
    //  Branch to [Finish] if EQuals
    //  CoMPare A with $3c
    //  Branch to [Finish] if EQuals
    //  PusH A
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD RNGPointer to A
    //  Exclusive OR A with #01
    //  STore A to RNGPointer
    //  Transfer A to X
    //  LoaD $3a,X to A
    //  Transfer A to X
    //  PulL A
    //  SEt Carry flag
    //  SuBtract $3c from A with Carry
    //  CoMPare A with #$ff
    //  Branch to next label if Not Equals
    //  LoaD f:RNGTbl,X to A
    //  BRAnch to [Finish]
    //  [LBL] INCrement A
    //  STore A to Divisor
    //  Store Zero to Divisor+1
    //  LoaD f:RNGTbl,X to A
    //  Transfer A to X
    //  STore X to Dividend
    //  Lengthen Indexes
    //  Jump to SubRoutine Division
    //  Shorten Indexes
    //  CLear Carry
    //  LoaD Remainder to A
    //  AdD $3c to A with Carry
    //  [Finish] PusH A
    //  LoaD RNGPointer to A
    //  Transfer A to X
    //  INCrement $3a,X
    //  Lengthen Indexes
    //  PulL A
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
    //  LoaD #$0090 to X

    //  [WipeAnimBlocks]		(wipes Anim structure AND A with blocking information after it, $3BCC-$3C5B)
    //  Store Zero to ActionAnim0::Flags,X
    //  DEcrement X
    //  Branch to [WipeAnimBlocks] if PLus
    //  Transfer X to A 		(A now $FF)
    //  LoaD #$037F to X

    //  [WipeGFXQueueDamage]	(wipes GFXQueue structure AND A with DisplayDamage after it with $FF, $384C-$3BCB)
    //  STore A to GFXQueue,X
    //  DEcrement X
    //  Branch to [WipeGFXQueueDamage] if PLus
    //  LoaD #$005F to X

    //  [WipeMessagesTimers]	(wipes Message Boxes AND A with Timer structures after them with $FF, $3C5F-$3E8D)
    //  STore A to MessageBoxes,X
    //  DEcrement X
    //  Branch to [WipeMessagesTimers] if PLus
    //  Transfer Direct page to aCcumulator
    //  LoaD #$000F to X

    //  [WipeReflectCounters]	(wipes $7B49-7B58)
    //  Store Zero to CounterReflecteeTable,X
    //  DEcrement X
    //  Branch to [WipeReflectCounters] if PLus
    //  LoaD #$002F to X

    //  [WipeMessageBoxData]	(wipes numbers used for message boxes, $3CBF-$3CEE)
    //  Store Zero to MessageBoxData,X
    //  DEcrement X
    //  Branch to [WipeMessageBoxData] if PLus
    //  Return To Subroutine
}

// Address: _0248
// Recalculate Stats+Level
// with Song
//   - X: Character Offset
static void copyStatsWithBonuses(void) {
    //  PusH X
    //  PusH Y
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  [AddCopyStats]			        (adds/copies Str/Agi/Vit/Mag)
    //  CLear Carry
    //  LoaD CharStruct::EquippedStr,X to A
    //  ADd CharStruct::BonusStr,X to A with Carry
    //  CoMPare A with #$64		        (100)
    //  Branch to next label if Carry Clear
    //  LoaD #$63 to A   		        (cap at 99)
    //  [LBL] STore A to Strength,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0004
    //  Branch to [AddCopyStats] if Not Equals
    //  PulL Y
    //  PulL X
    //  CLear Carry
    //  LoaD CharStruct::Level,X to A
    //  ADd CharStruct::BonusLevel,X to A with Carry
    //  CoMPare A with #$64		        (100)
    //  Branch to next label if Carry Clear
    //  LoaD #$63 to A   		        (cap at 99)
    //  [LBL] STore A to Level
    //  Return to SubRoutine
}

// Address: _0276
// Params:
//  - A = character index
//  - $3C5D (TempDisplayDamage) = displayed damage
static void copyDisplayDamage(void) {
    // Transfer A to X
    // LoaD f:_d0ed79,X to A	(party members after monsters)
    // A Shift Left
    // Transfer A to X
    // LoaD TempDisplayDamage to A
    // STore A to DisplayDamage,X
    // LoaD TempDisplayDamage+1 to A
    // STore A to DisplayDamage+1,X
    // Return to SubRoutine
}

// Address: _028A
static void wipeActionData(void) {
    //  Store Zero to a:wTargetIndex	    (**optimize: wastes a byte)
    //  LoaD #$0133 to X

    //  [LBL] STore Zero to $79F9,X	        (clears memory $79F9 - $7B2C)
    //  DEcrement X
    //  Branch to previous label if PLus
    //  Transfer X to A 		            (now $FF)
    //  LoaD #$0010 to X

    // 	[LBL] STore A to $7B2D,X	        (sets memory $7B2D - $7B3D to $FF)
    //  DEcrement X
    //  Branch to previous label if PLus
    //  Transfer Direct page to aCcumulator
    //  Return To Subroutine
}

// Address: _02A2
// Returns an integor between
// 0 and 99, inclusive
static uint8_t getRandom0_99(void) {
    // Transfer Direct page to aCcumulator
    // Transfer A to X
    // LoaD #$63 to A
    // JuMP to Random_X_A
    return getRandBetween(0, 99);
}

// Address: _02A9
// Combines MonsterTargets and PartyTargets into
// Bitmask PPPPMMMM MMMM0000 to match
// normal index order
static uint16_t getTargetBitmask(void) {
    // LoaD MonsterTargets to A
    // PusH A
    // AND A with #$F0
    // Logical Shift Right A
    // Logical Shift Right A
    // Logical Shift Right A
    // Logical Shift Right A
    // OR A with PartyTargets
    // STore A to TempTargetBitmask
    // PulL A
    // AND A with #$0F
    // A Shift Left
    // A Shift Left
    // A Shift Left
    // A Shift Left
    // STore A to TempTargetBitmask+1
    // Return to SubRoutine
    return 0;
}

// Address: _02C2
// Returns with number of targets minus 1 in
// A and $2620 (TempTargetting)
// Notably, 0 if single target
static void checkMultiTarget(void) {
    // LoaD MonsterTargets to A
    // OR A with PartyTargets
    // Jump to SubRoutine CountSetBits
    // DEcrement X
    // Transfer X to A
    // STore A to TempTargetting
    // Return to SubRoutine
}

// Address: _02CF
static void removeInactiveTargets(void) {
    //  Store Zero to NoValidTargets
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  STore X to $0E

    //  [Loop] LoaD ActiveParticipants,X to A
    //  Branch to [Inactive] if EQuals
    //  LoaD $0E to Y
    //  LoaD CharStruct::Status1,Y to A
    //  AND A with #$C0	;dead/stone
    //  Branch to [Inactive] if Not Equals
    //  LoaD CharStruct::Status4,Y to A
    //  AND A with #$81	;erased/hiding
    //  Branch to [Next] if EQuals

    //  [Inactive] PusH X
    //  ComPare X with #$0004	(monster check)
    //  Branch to [Monster] if Carry Set
    //  LoaD PartyTargets
    //  Jump to SubRoutine ClearBit_X
    //  STore A to PartyTargets
    //  BRAnch to [NextPLX]

    //  [Monster] Transfer X to A
    //  SEt Carry flag
    //  SuBtract #$04 from A with Carry	(monster index)
    //  Transfer A to X
    //  LoaD MonsterTargets
    //  Jump to SubRoutine ClearBit_X
    //  STore A to MonsterTargets

    //  [NextPLX] PulL X

    //  [Next]Lengthen A
    //  CLear Carry
    //  LoaD $0E to A
    //  ADd #$0080 to A with Carry	(next CharStruct offset)
    //  STore A to $0E
    //  Clear A, then Shorten
    //  INcrement X
    //  ComPare X with #$000C	(12 battle participants)
    //  Branch to [Loop] if Not Equals
    //  LoaD PartyTargets to A
    //  OR A with MonsterTargets
    //  Branch to [Ret] if Not Equals
    //  INCrement NoValidTargets

    //  [Ret] Return To Subroutine
}

// Address: _0324
// Copies magic data for spell in A from
// ROM to AttackInfo (offset Y)
static void copyRomMagicInfo(void) {
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8	(Size of Magic Data)
    //  Transfer A to X
    //  Clear A, then Shorten
    //  Store Zero to $3D

    //  [CopyFirst5] LoaD f:AttackProp,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $3D
    //  LoaD $3D to A
    //  CoMPare A with #$05
    //  Branch to [CopyFirst5] if Not Equals
    //  INcrement Y by 4 			(AttackInfo has 4 bytes that don't apply to magic)

    //  [CopyLast3] LoaD f:AttackProp,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $3D
    //  LoaD $3D to A
    //  CoMPare A with #$08
    //  Branch to [CopyLast3] if Not Equals
    //  Return To Subroutine
}

// Address: _0356
// Advances the current message box offets to
// the next set of messgae boxes.
// For multi-commands like X-Magic/Dualcast
static void nextMessageBoxSet(void) {
    // CLear Carry flag
    // LoaD MessageBoxOffset to A
    // ADd #$18 to A with Carry	    (+24, next message box set)
    // STore A to MessageBoxOffset
    // CLear Carry flag
    // LoaD MessageBoxDataOffset to A
    // ADd #$0C to A with Carry		(+12, next message box data set)
    // STore A to MessageBoxDataOffset
    // Return to SubRoutine
}

// Address: _0369
// (Y:index into in-battle inventory)
// (Returns A: bitmask depending on
// equipment type and some character properties)
//  - Format seems to be 2 bits per character,
//    00 for usable and 10 for not
static void getItemsUsableY(void) {
    //  LoaD Temp,Y to A
    //  Branch to next label if PLus
    //  LoaD #$AA to A		(usable for none)
    //  JuMP to [Ret]

    //  [LBL] AND A with #$40		(Consumable)
    //  Branch to [Equipment] if EQuals
    //  LoaD InventoryFlags,Y to A
    //  AND A with #$20
    //  Branch to [Ret] if EQuals
    //  LoaD #$AA to A		(usable for none)
    //  BRAnch to [Ret]

    //  [RetZero] LoaD #$00 to A		(usable for all)
    //  BRAnch to [Ret]

    //  [Equipment] 		**optimize: this whole section is basically a copy of the GetItemUsableA $455E subroutine
    //  LoaD Temp,Y to A
    //  A Shift Left
    //  A Shift Left
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [LBL] lda f:EquipTypeTbl,X to A
    //  STore A to TempEquippable,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0004
    //  Branch to previous label if Not Equals

    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  Transfer A to Y
    //  LoaD #$AA to A
    //  STore A to $0E

    //  [DetermineEquippableLoop] LoaDCharEquippable::Weapons,X to A
    //  AND A with TempEquippable::Weapons,Y
    //  Branch to [Match] if Not Equals
    //  LoaD CharEquippable::Weapons+1,X to A
    //  AND A with TempEquippable::Weapons+1,Y
    //  Branch to [Match] if Not Equals
    //  LoaD CharEquippable::Armor,X to A
    //  AND A with TempEquippable::Armor,Y
    //  Branch to [Match] if Not Equals
    //  LoaD CharEquippable::Armor+1,X to A
    //  AND A with TempEquippable::Armor+1,Y
    //  Branch to [NextChar] if EQuals

    //  [Match] Transfer X to A
    //  Logical Shift Right A x2
    //  Branch to [Check1] if Not Equals

    //  LoaD $0E to A
    //  AND A with #$7F		;clear first character bit
    //  STore A to $0E
    //  BRAnch to [NextChar]

    //  [Check1] CoMPare A with #$01
    //  Branch to [Check2] if Not Equals
    //  LoaD $0E to A
    //  AND A with #$DF		;clear second character bit
    //  STore A to $0E
    //  BRAnch to NextChar

    //  [Check2] CoMPare A with #$02
    //  Branch to [Other] if Not Equals
    //  LoaD $0E to A
    //  AND A with #$F7         	;clear third character bit
    //  STore A to $0E
    //  BRAnch to NextChar

    //  [Other] LoaD $0E to A
    //  AND A with #$FD		;clear fourth character bit
    //  STore A to $0E

    //  [NextChar] INcrement X by 4
    //  ComPare X with #$0010			;4 bytes * 4 characters
    //  Branch to [DetermineEquippableLoop] if Not Equals
    //  LoaD $0E to A

    //  [Ret] Return To Subroutine
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
    //  Branch to [ItemZero] if EQuals
    //  CoMPare A with #$E0
    //  Branch to [Consumable] if Carry Set		(>$E0 is consumable)
    //  CoMPare A with #$80
    //  Branch to [Weapon] if Clear Carry		(<$80 is a weapon)

    //  [Armor]				(otherwise it's armor)
    //  SEt Carry flag
    //  SuBtract #$80 from A with Carry		(remove the armor offset)
    //  Lengthen A
    //  A Shift Left
    //  A Shift Left
    //  STore A to $0E
    //  A Shift Left
    //  CLear Carry
    //  ADd $0E to A with Carry			(armor *12 (size of equipment struct))
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:ArmorProp,X to A
    //  AND A with #$08		(target enemy?)
    //  Branch to [ItemZero] if EQuals
    //  LoaD f:ArmorProp+2,X to A
    //  AND A with #$3F		(mask to equip info)
    //  STore A to Temp,Y
    //  LoaD #$5A to A
    //  STore A to InventoryFlags,Y
    //  BRAnch to [Ret]

    //  [ItemZero]	(or armor targettng bit 08h)
    //  LoaD #$80 to A		(not usable)
    //  STore A to Temp,Y
    //  LoaD #$5A to A
    //  STore A to InventoryFlags,Y
    //  BRAnch to [Ret]

    //  [Weapon] Lengthen A
    //  A Shift Left
    //  A Shift Left
    //  STore A to $0E
    //  A Shift Left
    //  CLear Carry
    //  ADd $0E to A with Carry         	(weapon *12)
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:WeaponProp+4,X to A
    //  AND A with #$80
    //  Jump to SubRoutine ShiftDivide_32	;shift to 04h bit
    //  STore A to InventoryFlags,Y
    //  LoaD f:WeaponProp,X to A
    //  STore A to InventoryTargetting,Y
    //  LoaD f:WeaponProp+2,X to A
    //  PusH A
    //  AND A with #$C0		;flag bits from equipment type(? AND A with throwable)
    //  OR A with #$1A		;set some more bits (??)
    //  OR A with InventoryFlags,Y	;keep existing bits (double grip)
    //  STore A to InventoryFlags,Y
    //  PulL A
    //  AND A with #$3F		;mask to just equip info
    //  STore A to Temp,Y
    //  BRAnch to [Ret]

    //  [Consumable] SEt Carry flag
    //  SuBtract #$E0 from A with Carry
    //  Lengthen A
    //  A Shift Left
    //  A Shift Left
    //  A Shift Left
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:ConsumableItemProp,X to A
    //  STore A to InventoryTargetting,Y
    //  LoaD f:ConsumableItemProp+2,X to A
    //  STore A to InventoryFlags,Y
    //  LoaD #$40 to A		(consumable)
    //  STore A to Temp,Y

    //  [Ret] Return To Subroutine
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
    //  LoaD #$000F to X

    // 	[LBL] STore Zero to $0E,X		(clear $0E-1D)
    //  DEcrement X
    //  Branch to previous label if PLus
    //  LoaD #$0064 to X
    //  STore X to $12
    //  LoaD $2E to X			(previous multiply result (low bytes))
    //  STore X to $0E
    //  LoaD $30 to A			(high bytes)
    //  STore A to $10

    //  32 bit division routine
    //  Dividend: 	$0E-11
    //  Divisor: 	$12-15
    //  Quotient: 	$16-19
    //  Remainder: 	$1A-1C
    //  **optimize: make this a general purpose subroutine, duplicate at $57FE
    //  Lengthen A
    //  CLear Carry
    //  LoaD #$0020 to X

    //  [LBL] ROtate $0E, $10, $1A and $1C Left
    //  SEt Carry flag
    //  LoaD $1A to A
    //  SuBtract $12 to A with Carry
    //  STore A to $1A
    //  LoaD $1C to A
    //  SuBtract $14 to A with Carry
    //  STore A to $1C
    //  Branch to next label if Carry Set
    //  LoaD $1A to A
    //  ADd $12 to A with Carry
    //  STore A to $1A
    //  LoaD $1C to A
    //  ADd $14 to A with Carry
    //  STore A to $1C
    //  CLear Carry

    //  [LBL] ROtate $16 and $18 Left
    //  DEcrement X
    //  Branch to previous label if Not Equals
    //  Clear A, then Shorten

    //  ;division ends here
    //  CLear Carry
    //  LoaD $16 to A		(quotient, input/100)
    //  ADd $08 to A with Carry		(;base value)
    //  STore A to $08		(adjusted value)
    //  LoaD $17 to A		(high byte of above)
    //  ADd $09 to A with Carry
    //  STore A to $09
    //  SEt Carry flag 		(checks against 9999)
    //  LoaD $08 to A
    //  SuBtract $0A to A with Carry		(9999 low byte)
    //  LoaD $09 to A
    //  SuBtract $0B to A with Carry		(9999 high byte)
    //  Branch to [Ret] if Carry Clear
    //  LoaD $0A to A		(caps at 9999)
    //  STore A to $08
    //  LoaD $0B to A
    //  STore A to $09

    //  [Ret] Return To Subroutine
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
    // Jump to SubRoutine GFXCmdAbilityAnim
    // LoaD ProcSequence to A
    // Transfer A to X
    // STore Zero to AtkType,X
    // STore Zero to MultiTarget,X
    // STore Zero to TargetType,X
    // INCrement UnknownReaction
    // JuMP to FinishCommandNullTargets
}

// Address: _0511
// For commands $01 (Other) and $24 (Dummy01)
static void commandTable00(void) {
    //  [CommandTable23] LoaD AttackerIndex to A
    //  CoMPare A with #$04		(monster check)
    //  Branch to Party if Carry Clear

    //  [Monster] SEt Carry flag
    //  SuBtract #$04 from A with Carry		(now monster index)
    //  A Shift Left
    //  Transfer A to X
    //  LoaD f:_d0ee95,X to A	(*100)
    //  STore A to $0E
    //  LoaD f:_d0ee95+1,X to A
    //  STore A to $0F
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD $0E to X

    //  [CopyGFXQueue]		(copy 100 bytes from monster ai to GFXQueue)
    //  LoaD MonsterAIScript,X to A
    //  STore A to GFXQueue,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0064
    //  Branch to [CopyGFXQueue] if Not Equals
    //  BRAnch to [Continue]

    //  [Party] Jump to SubRoutine FindOpenGFXQueueSlot   (next slot in X)
    //  Store Zero to GFXQueue::Flag,X
    //  Store Zero to GFXQueue::Cmd,X
    //  Store Zero to GFXQueue::Type,X
    //  Store Zero to GFXQueue::Data1,X
    //  Store Zero to GFXQueue::Data2,X

    //  [Continue] LoaD ProcSequence to A
    //  Transfer A to X
    //  LoaD #$7E to A
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  INCrement UnknownReaction
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD #$80 to A		(first party member)
    //  STore A to CommandTargetBitmask,X
    //  Store Zero to CommandTargetBitmask+1,X
    //  INCrement ProcSequence
    //  Return To Subroutine
}

// Address: _0570
// For commands $02 (Item) and $20 (Drink)
static void itemCommand(void) {
    //  [CommandTable01]
    //  [CommandTable1F]
    //  Store Zero to SelectedItem
    //  Jump to SubRoutine SelectCurrentProcSequence	;$0C = ProcSequence*12
    //  Jump to SubRoutine GetTargets
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::ActionFlag,X to A
    //  AND A with #$10	;weapon used as item
    //  Branch to next label if EQuals
    //  JuMP to [WeaponItem]

    //  [LBL] LoaD CharStruct::SelectedItem,X
    //  CoMPare A with #$EF	(magic lamp)
    //  Branch to [ConsumableItem] if Not Equals
    //  Jump to SubRoutine PrepMagicLamp
    //  JuMP to ConjureMagicLamp	(finishes up in Conjure routine)

    //  [ConsumableItem] STore A to TempSpell
    //  SEt Carry flag
    //  SuBtract #$E0 from A with Carry (now consumable item index)
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8

    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD $0C to Y		(ProcSequence*12)
    //  Store Zero to $0A

    //  [LBL] LoaD f:ConsumableItemProp,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $0A
    //  LoaD $0A to A
    //  CoMPare A with #$05      	(copy 5 bytes)
    //  Branch to previous label if Not Equals
    //  INcrement Y by 4          	(skip 4 in Attackinfo)

    // 	[LBL] lda f:ConsumableItemProp,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $0A
    //  LoaD $0A to A
    //  CoMPare A with #$08      	;copy remaining 3 bytes
    //  Branch to previous label if Not Equals
    //  Jump to SubRoutine CheckMultiTarget
    //  Branch to [TargetOK] if Not Equals
    //  LoaD $0C to Y		(ProcSequence*12)
    //  LoaD AttackInfo::MagicAtkType,Y to A
    //  Branch to [_CheckRetarget] if PLus
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  INCrement HitsInactive,X	;can hit dead targets
    //  BRAnch to [TargetOK]

    //  [_CheckRetarget]
    //  Jump to SubRoutine CheckRetarget

    //  [TargetOK] Jump to SubRoutine BuildTargetBitmask
    //  LoaD TempSpell to A
    //  STore A to Temp+1
    //  LoaD #$04 to A
    //  STore A to Temp
    //  Jump to SubRoutine GFXCmdAttackNameFromTemp
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$09 to A		(commAND A with 9: item use)
    //  STore A to GFXQueue::Type,X
    //  LoaD TempSpell to A
    //  STore A to GFXQueue::Data1,X
    //  Store Zero to GFXQueue::Data2,X
    //  LoaD $0C to Y		(ProcSequence*12)
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  LoaD AttackInfo::MagicAtkType,Y to A
    //  AND A with #$7F
    //  STore A to AtkType,X
    //  LoaD TempTargetting to A
    //  STore A to MultiTarget,X
    //  Branch to [Single] if EQuals
    //  INCrement MultiTarget,X	;now proper number of targets if >1
    //  LoaD #$80 to A

    //  [Single] STore A to TargetType,X
    //  Jump to SubRoutine FinishCommand
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  Return To Subroutine
}

// Addres: _0632
static void weaponItem(void) {
    //  STore Zero to TempHand
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  LoaD f:_d0ed85,X to A	(size of one character's gear offset)
    //  Transfer A to Y
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::SelectedItem,X to A
    //  Branch to [Left] if Not Equals
    //  LoaD CharStruct::RHWeapon,X to A
    //  STore A to CharStruct::SelectedItem,X
    //  STore A to SelectedItem
    //  Transfer A to X
    //  LoaD RHWeapon::ItemMagic,Y to A
    //  BRAnch to ItemReady

    //  [Left] INCrement TempHand
    //  LoaD CharStruct::LHWeapon,X to A
    //  STore A to CharStruct::SelectedItem,X
    //  STore A to SelectedItem
    //  Transfer A to X
    //  LoaD LHWeapon::ItemMagic,Y to A

    //  [ItemReady] STore A to TempItemMagic
    //  AND A with #$7F
    //  Transfer X to Y 		(Y is now selected item)
    //  PusH A
    //  PusH A
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  PulL A
    //  STore A to AtkType,X
    //  Transfer Y to A
    //  STore A to Temp+1	(selected item)
    //  LoaD #$04 to A
    //  STore A to Temp
    //  Jump to SubRoutine GFXCmdAttackNameFromTemp
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  LoaD AtkType,X to A
    //  LoaD $0C to Y		(ProcSequence*12)
    //  Jump to SubRoutine CopyROMMagicInfo
    //  Jump to SubRoutine CheckMultiTarget
    //  Branch to [TargetOK] if Not Equals
    //  LoaD $0C to Y
    //  LoaD AttackInfo::MagicAtkType,Y to A
    //  Branch to [DontRetarget] if PLus
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  INCrement HitsInactive,X
    //  BRAnch to [TargetOK]

    //  [DontRetarget]
    //  Jump to SubRoutine CheckRetarget

    //  [TargetOK] Jump to SubRoutine BuildTargetBitmask
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A	(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$0A to A	(commAND A with 10: weapon used as item)
    //  STore A to GFXQueue::Type,X
    //  PulL A
    //  STore A to GFXQueue::Data1,X
    //  Store Zero to GFXQueue::Data2,X
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  LoaD AtkType,X to A
    //  Branch to next label if PLus
    //  Transfer Direct page to aCcumulator
    //  BRAnch to second next label

    //  [LBL] LoaD ldy $0C
    //  LoaD AttackInfo::MagicAtkType,Y to A
    //  AND A with #$7F

    //  [LBL] STore A to AtkType,X
    //  LoaD TempTargetting to A
    //  STore A to MultiTarget,X
    //  Branch to next label if EQuals
    //  INCrement MultiTarget,X
    //  LoaD #$80 to A

    //  [LBL] STore A to TargetType,X
    //  Jump to SubRoutine FinishCommand
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  LoaD TempItemMagic to A
    //  Branch to [Ret] if PLus

    //  [BreakOnUse]	(80h indicates item should now break)
    //  LoaD  AttackerIndex to A
    //  Jump to SubRoutine ShiftMultiply_4
    //  STore A to $0E
    //  A Shift Left
    //  CLear Carry
    //  ADd $0E to A with Carry
    //  Transfer A to Y 		;Attacker index *12
    //  LoaD TempHand to A
    //  Branch to [Left2] if Not Equals
    //  Transfer Direct page to aCcumulator
    //  STore A to HandItems::ID,Y
    //  STore A to HandItems::Level,Y
    //  STore A to HandItems::MP,Y
    //  LoaD #$38 to A
    //  STore A to HandItems::Targetting,Y
    //  LoaD #$5A to A
    //  STore A to HandItems::Flags,Y
    //  LoaD #$AA to A
    //  STore A to HandItems::Usable,Y
    //  BRAnch to DoneHandItems

    //  [Left2] Transfer Direct page to aCcumulator
    //  STore A to HandItems::ID+1,Y
    //  STore A to HandItems::Level+1,Y
    //  STore A to HandItems::MP+1,Y
    //  LoaD #$38 to A
    //  STore A to HandItems::Targetting+1,Y
    //  LoaD #$5A to A
    //  STore A to HandItems::Flags+1,Y
    //  LoaD #$AA to A
    //  STore A to HandItems::Usable+1,Y
    //  [DoneHandItems] LoaD MessageBoxOffset to A
    //  Transfer A to Y
    //  LoaD #$50 to A	(item shattered message)
    //  STore A to MessageBoxes,Y
    //  LoaD MessageBoxOffset to A
    //  STore A to $0E
    //  A Shift Left
    //  CLear Carry
    //  ADd $0E to A with Carry
    //  Transfer A to X 		(message box index *3)
    //  LoaD SelectedItem to A
    //  STore A to MessageBoxData,X
    //  Store Zero to MessageBoxData+1,X
    //  Store Zero to MessageBoxData+2,X
    //  Jump to SubRoutine GFXCmdMessage
    //  LoaD DisplayInfo::CurrentChar to A
    //  PusH A
    //  LoaD AttackerIndex to A
    //  STore A to DisplayInfo::CurrentChar
    //  STore A to CurrentChar
    //  Jump to SubRoutine ReplaceHands
    //  PulL A
    //  STore A to DisplayInfo::CurrentChar
    //  Jump to SubRoutine ApplyGear

    //  [Ret] Return To Subroutine
}

// Address: _0767
static void prepMagicLamp(void) {
    //  LoaD BattleData::MagicLamp to A
    //  CoMPare A with #$0D	;<13, normal
    //  Branch to [Continue] if Carry Clear
    //  CoMPare A with #$20	;>=32, egg chop
    //  Branch to EggChop if Carry Set
    //  LoaD #$0D to A	(chocobo)
    //  BRAnch to [Continue]

    //  [EggChop] LoaD #$0E to A	(egg chop)

    //  [Continue] Transfer A to X
    //  LoaD f:_d0eee7,X to A
    //  STore A to TempSpell
    //  Store Zero to TempIsEffect
    //  CLear Carry
    //  LoaD BattleData::MagicLamp to A
    //  ADd #$01 to A with Carry
    //  Branch to next label if Carry Clear
    //  LoaD #$FF to A	(cap at 255 uses)

    //  [LBL] STore A to BattleData::MagicLamp
    //  Return To Subroutine
}

// Address: _0791
// For command $03 (Row)
static void commandTable02(void) {
    // LoaD #$03 to A	(row ability)
    // Jump to SubRoutine CopyAbilityInfo
    // INCrement UnknownReaction
    // LoaD #$02 to A
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // JuMP to FinishCommandNullTargets
}

// Address: _07A4
// Command $04 (Defend)
// Could've called noActionAbility(...) directly,
// but that depends whether the loaded
// could be parsed as an arguement.
static void commandTable03(void) {
    // LoaD #$03 to A
    // JuMP to NoActionAbility
}

// Address: _07A9
// Command $06 (Guard)
// Same predicament as the above function.
static void commandTable05(void) {
    // LoaD #$05 to A
    // JuMP to NoActionAbility
}

// Address: _07AE
// Command $07 (Kick)
static void commandTable06(void) {
    // LoaD #$07 to A	(kick ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget
    // LoaD #$07 to A	(kick ability name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // LoaD #$06 to A	(kick anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeMultiTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdDamageNumbers
}

// Address: _07CF
// Command $08 (BuildUp/Focus)
static void commandTable07(void) {
    // LoaD #$08 to A	(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // LoaD #$07 to A	(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // LoaD ProcSequence to A
    // Transfer A to X
    // STore Zero to AtkType,X
    // STore Zero to MultiTarget,X
    // STore Zero to TargetType,X
    // Jump to SubRoutine FinishCommandNullTargets
    // ldx AttackerOffset to X
    // LoaD #$4E to A	(Command, maps to CommandTable2C/SimpleFight)
    // STore A to CharStruct::Command,X
    // LoaD #$10 to A	(double M)
    // STore A to CharStruct::DamageMod,X
    // LoaD #$4E to A
    // Transfer A to X
    // LoaD f:BattleCmdDelay,X to A
    // PusH A
    // LoaD AttackerIndex to A
    // Jump to SubRoutine GetTimerOffset
    // ldx AttackerOffset to X
    // PulL A
    // Jump to SubRoutine HasteSlowMod
    // STore A to CurrentTimer::ATB,Y
    // LoaD #$41 to A	(waiting for delayed action)
    // STore A to EnableTimer::ATB,Y
    // INCrement DelayedFight
    // Return to SubRoutine
}

// Address: _0814
// Command $4E (Simple Fight)
// No procs, used by Capture/BuildUp/etc.
static void simpleFight(void) {
    //  Jump to SubRoutine GetTargets
    //  Jump to SubRoutine CheckRetarget
    //  LoaD AttackerOffset to X
    //  LoaD PartyTargets to A
    //  STore A to CharStruct::PartyTargets,X
    //  LoaD MonsterTargets to A
    //  STore A to CharStruct::MonsterTargets,X
    //  Jump to SubRoutine BuildTargetBitmask
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  LoaD f:_d0ed85,X to A	(size of combined gear stats struct)
    //  Transfer A to X
    //  STore X to $0E			(gear stats offset)
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::RHWeapon,X to A
    //  Branch to [RH] if Not Equals
    //  JuMP to [LH]

    //  [RH] Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $14			(AttackInfo Offset)
    //  Store Zero to $12			(loop index)
    //  LoaD $0E to X			(gear stats offset)

    //  [LBL] LoaD RHWeapon,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $12
    //  LoaD $12 to A
    //  CoMPare A with #$0C		(copy 12 bytes weapon data)
    //  Branch to previous label if Not Equals
    //  LoaD $0E to X			(gear stats offset)
    //  LoaD RHWeapon::Properties,X to A
    //  AND A with #$04		(magic sword ok)
    //  Branch to [__MSword] if Not Equals
    //  Transfer Direct page to aCcumulator
    //  BRAnch to [__DoneMSword]

    //  [__MSword] LoaD AttackerOffset to X
    //  LoaD CharStruct::MSwordAnim,X to A
    //  AND A with #$7F		(clear high bit for right hand)

    //  [__DoneMSword] PusH A
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$01 to A		(ability/commAND A with animation)
    //  STore A to GFXQueue::Type,X
    //  LoaD #$04 to A		(fight)
    //  STore A to GFXQueue::Data1,X
    //  PulL A 			(magic sword anim)
    //  STore A to GFXQueue::Data2,X
    //  LoaD $0E to X
    //  LoaD RHWeapon::AtkType,X to A
    //  PusH A
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  PulL A
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  Jump to SubRoutine FinishCommand
    //  Jump to SubRoutine GFXCmdDamageNumbers

    //  [LH] LoaD AttackerOffset to X
    //  LoaD CharStruct::LHWeapon,X to A
    //  Branch to next label if Not Equals
    //  Return To Subroutine 			(no weapons; not even fists)

    //  [LBL] Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $12			(AttackInfo Offset)
    //  Store Zero to $14			(loop index)
    //  LoaD $0E to X			(gear stats offset)
    //  [LBL] LoaD LHWeapon,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $14
    //  LoaD $14 to A
    //  CoMPare A with #$0C		(copy 12 bytes weapon data)
    //  Branch to previous label if Not Equals
    //  LoaD $0E to X			(gear stats offset)
    //  LoaD ProcSequence to A
    //  Transfer A to Y
    //  LoaD LHWeapon::AtkType,X to A
    //  STore A to AtkType,Y
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$01 to A		(ability/command animation)
    //  STore A to GFXQueue::Type,X
    //  LoaD #$04 to A		(fight)
    //  STore A to GFXQueue::Data1,X
    //  STore X to $08			(GFXQueue offset)
    //  LoaD $0E to X			(gear stats offset)
    //  LoaD LHWeapon::Properties,X to A
    //  AND A with #$04		(magic sword ok)
    //  Branch to [__MSword2] if Not Equals
    //  LoaD #$80 to A		(left hand)
    //  BRAnch to [__DoneMSword2]

    //  [__MSword2] LoaD AttackerOffset to X
    //  LoaD CharStruct::MSwordAnim,X to A
    //  OR A with #$80		(left hand)

    //  [__DoneMSword2] LoaD $08 to X			(GFXQueue offset)
    //  STore A to GFXQueue::Data2,X	(magic sword anim)
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  Jump to SubRoutine FinishCommand
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  Return To Subroutine
}

// Address: _090B
// Command $09 (Mantra, or Chakra in GBA)
static void commandTable08(void) {
    // LoaD #$09 to A	(mantra ability)
    // Jump to SubRoutine CopyAbilityInfo
    // LoaD #$09 to A	(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // LoaD #$08 to A	(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommandNullTargets
    // LoaD ProcSequence to A	(a second effect?)
    // Transfer A to X
    // STore Zero to AtkType,X		(no attack type)
    // STore Zero to MultiTarget,X
    // STore Zero to TargetType,X
    // Jump to SubRoutine FinishCommandNullTargets
    // JuMP to GFXCmdDamageNumbers
}

// Address: _0933
// Command $0A (Escape/Flee)
static void commandTable09(void) {
    // LoaD #$0A to A	(escape ability)
    // Jump to SubRoutine CopyAbilityInfo
    // INCrement UnknownReaction
    // LoaD #$0A to A	(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // LoaD #$09 to A	(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommandNullTargets
    // JuMP to GFXCmdMessage
}

// Address: _094E
// Command $0B (Steal)
static void commandTable0A(void) {
    // LoaD #$0B to A	(steal ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // LoaD #$0B to A	(name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // LoaD #$0A to A	(anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Adddress: _096F
// Command $0C (Capture/Mug)
static void commandTable0B(void) {
    // STore Zero to ProcSequence	(overwriting entire sequence)
    // STore Zero to NextGFXQueueSlot
    // LoaD #$0C to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // Jump to SubRoutine SimpleFight
    // LoaD #$0B to A		(steal ability)
    // Jump to SubRoutine CopyAbilityInfo
    // LoaD #$0A to A		(steal anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Address: _0990
// Command $0D (Jump)
static void commandTable0C(void) {
    //  [JumpCommand]
    //  LoaD #$0D to A	(jump ability name)
    //  Jump to SubRoutine GFXCmdAttackNameA

    //  [Anim]			(routine is called here by command $52)
    //  LoaD #$0C to A	(jump ability anim ,launch)
    //  Jump to SubRoutine GFXCmdAbilityAnim
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  Jump to SubRoutine FinishCommandNullTargets
    //  INCrement UnknownReaction
    //  LoaD AttackerOffset to X
    //  LoaD #$4F to A	(jump landing command, maps to CommandTable2D)
    //  STore A to CharStruct::Command,X
    //  LoaD #$10 to A	(jumping)
    //  STore A to CharStruct::CmdStatus,X
    //  LoaD #$80 to A	(auto hit)
    //  STore A to CharStruct::DamageMod,X
    //  LoaD #$4F to A	(jump landing command)
    //  Transfer A to X
    //  LoaD f:BattleCmdDelay,X to A
    //  PusH A
    //  LoaD AttackerIndex to A
    //  Jump to SubRoutine GetTimerOffset
    //  LoaD AttackerOffset to X
    //  PulL A
    //  Jump to SubRoutine HasteSlowMod
    //  STore A to CurrentTimer::ATB,Y
    //  LoaD #$41 to A	(queued action)
    //  STore A to EnableTimer::ATB,Y
    //  INCrement DelayedFight
    //  Return To Subroutine
}

// Address: _09DD
// Command $4F (landing from Jump)
static void commandTable2D(void) {
    //  LoaD #$2D to A	(jump landing anim)
    //  Jump to SubRoutine GFXCmdAbilityAnim
    //  Jump to SubRoutine GetTargets
    //  Jump to SubRoutine CheckRetarget
    //  LoaD AttackerOffset to X
    //  LoaD PartyTargets to A
    //  STore A to CharStruct::PartyTargets,X
    //  LoaD MonsterTargets to A
    //  STore A to CharStruct::MonsterTargets,X
    //  Jump to SubRoutine BuildTargetBitmask
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  LoaD f:_d0ed85,X to A	(size of combined gearstats struct)
    //  Transfer A to X
    //  STore X to $0E			(gear stats offset)
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::RHWeapon,X to A
    //  Branch RH if Not Equals
    //  JuMP to [LH]

    //  [RH] Jump to SubRoutine SelectCurrentProcSequence
    //  Store Zero to $12
    //  LoaD $0E to X

    //  [LBL] LoaD RHWeapon,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $12
    //  LoaD $12 to A
    //  CoMPare A with #$0C		(copy 12 bytes weapon data)
    //  Branch to previous label if Not Equals
    //  LoaD $0E to X			(gear stats offset)
    //  LoaD RHWeapon::AtkType,X to A
    //  PusH A
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  PulL A
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  Jump to SubRoutine FinishCommand
    //  Jump to SubRoutine GFXCmdDamageNumbers

    //  [LH] LoaD AttackerOffset to X
    //  LoaD CharStruct::LHWeapon,X to A
    //  Branch to next label if Not Equals
    //  JuMP to [Finish]

    //  [LBL] Jump to SubRoutine SelectCurrentProcSequence
    //  Store Zero to $12
    //  LoaD $0E			(gear stats offset)

    //  [LBL] LoaD LHWeapon,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $12
    //  LoaD $12 to A
    //  CoMPare A with #$0C		(copy 12 bytes weapon data)
    //  Branch to previous label if Not Equals
    //  LoaD $0E to X			(gear stats offset)
    //  LoaD ProcSequence to A
    //  Transfer A to Y
    //  LoaD LHWeapon::AtkType,X to A
    //  STore A to AtkType,Y
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  Jump to SubRoutine FinishCommand
    //  Jump to SubRoutine GFXCmdDamageNumbers

    //  [Finish] INCrement UnknownReaction
    //  Return To Subroutine
}

// Address: _0A7D
// Command $50 (forced Jump landing, via Interceptor Rocket)
static void commandTable2E(void) {
    // LoaD #$50 to A		(jump intercepted)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // STore Zero to MonsterTargets
    // LoaD AttackerIndex to A
    // Transfer A to X
    // Transfer Direct page to aCcumulator
    // Jump to SubRoutine SetBit_X
    // STore A to PartyTargets	(target self)
    // Jump to SubRoutine BuildTargetBitmask
    // INCrement UnknownReaction
    // LoaD #$2E to A		(jump intercepted anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // JuMP to FinishCommand
}

// Address: _0AA4
// Command $0E (Dragon Sword/Lance)
static void commandTable0D(void) {
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget
    
    // LoaD #$0E to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$0D to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine SelectCurrentProcSequence

    // LoaD #$71 to A		(hp drain)
    // Jump to SubRoutine CopyROMMagicInfo
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // Jump to SubRoutine GFXCmdDamageNumbers
    // Jump to SubRoutine SelectCurrentProcSequence

    // LoaD #$72 to A		(mp drain)
    // Jump to SubRoutine CopyROMMagicInfo
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdDamageNumbers
}

// Address: _0ADC
// Command $0F (Smoke)
static void commandTable0E(void) {
    // LoaD #$0F to A		(smoke ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget

    // LoaD #$0F to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$0E to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeMultiTarget
    // JuMP to FinishCommand
}

// Address: _0AFA
// Command $10 (Image)
static void commandTable0F(void){
    // LoaD #$10 to A		(image ability)
    // Jump to SubRoutine CopyAbilityInfo

    // LoaD #$10 to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$0F to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // JuMP to FinishCommandNullTargets
}

// Address: _0B0F
// Command $11 (Throw)
//   ** optimize: use SandwormBattle instead of
//      checking encounter
static void commandTable10(void) {
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::SelectedItem,X to A
    //  Branch to [Weapon] if PLus		(otherwise, a scroll)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  Store Zero to $0E			(target bits)

    //  [TargetActiveMonsters] LoaD ActiveParticipants+4,X to A
    //  Branch to [Next] if EQuals
    //  LoaD $0E to A
    //  Jump to SubRoutine SetBit_X  		(add as target if active)
    //  STore A to $0E
    //  [Next] INcrement X
    //  ComPare X with #$0008		(8 monsters)
    //  Branch to TargetActiveMonsters if Not Equals
    //  LoaD AttackerOffset to X
    //  LoaD $0E to A			(target bits)
    //  STore A to CharStruct::MonsterTargets,X
    //  LoaD EncounterIndex+1 to A
    //  Branch to [ItemFlag] if EQuals
    //  LoaD EncounterIndex to A
    //  CoMPare A with #$BF		(sandworm fight)
    //  Branch to [ItemFlag] if Not Equals
    //  LoaD $0E to A
    //  AND A with #$FC		(exclude "real" sandworm)
    //  STore A to CharStruct::MonsterTargets,X

    //  [ItemFlag] LoaD #$40 to A		(item)
    //  STore A to CharStruct::ActionFlag,X
    //  JuMP to ItemCommand

    //  [Weapon] LoaD #$11 to A		(throw ability)
    //  Jump to SubRoutine CopyAbilityInfo
    //  Jump to SubRoutine GetTargets
    //  Jump to SubRoutine CheckRetarget
    //  Jump to SubRoutine BuildTargetBitmask
    //  LoaD #$11 to A		(ability name)
    //  Jump to SubRoutine GFXCmdAttackNameA
    //  LoaD #$10 to A		(ability anim)
    //  Jump to SubRoutine GFXCmdAbilityAnim
    //  Jump to SubRoutine MagicAtkTypeSingleTarget
    //  Jump to SubRoutine FinishCommand
    //  JuMP to GFXCmdDamageNumbers
}

// Address: _0B6F
// Command $12 (Sword Slap / Mineuchi)
// sets a variable which is never checked then
// issues a regular fight command
static void swordSlapCommand(void) {
    // LoaD #$12 to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // INCrement SwordSlap		(not checked anywhere)
    // JuMP to FightCommand
}

// Address: _0B7A
// Command $13 (Gil Toss/ Samurai's Zeninage)
static void commandTable12(void) {
    // LoaD #$13 to A		(gil toss ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget

    // LoaD #$13 to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$12 to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeMultiTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdDamageNumbers
}

// Address: _0B9B
// Command $14 (Slash / Samurai's Iainuki)
static void commandTable13(void) {
    // LoaD #$14 to A	(slash ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget
    // INCrement UnknownReaction

    // LoaD #$14 to A	(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$13 to A	(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeMultiTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdDamageNumbers
}

// Address: _0BBF
// Command $15 (Animals)
//  ** optimize: rewrite to remove repeated bra's
static void commandTable14(void) {
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD Level to A
    //  Jump to SubRoutine Random_X_A		(0..Level)
    //  Branch to next label if Not Equals
    //  Transfer Direct page to aCcumulator 		(0 mystidian rabbit)
    //  BRAnch to [Chosen]

    //  [LBL] CoMPare A with #$05
    //  Branch to next label if Carry Set
    //  LoaD #$01 to A	(<5 squirrel)
    //  BRAnch to [Chosen]
    //  [LBL] CoMPare A with #$0A
    //  Branch to next label if Carry Set
    //  LoaD #$02 to A	(<10 bee swarm)
    //  BRAnch to [Chosen]
    //  [LBL] CoMPare A with #$14
    //  Branch to next label if Carry Set
    //  LoaD #$03 to A	(<20 nightingale)
    //  BRAnch to [Chosen]
    //  [LBL] CoMPare A with #$1E
    //  Branch to next label if Carry Set
    //  LoaD #$04 to A	(<30 momonga)
    //  BRAnch to [Chosen]
    //  [LBL] CoMPare A with #$28
    //  Branch to next label if Carry Set
    //  LoaD #$05 to A	(<40 falcon)
    //  BRAnch to [Chosen]
    //  [LBL] CoMPare A with #$32
    //  Branch to next label if Carry Set
    //  LoaD #$06 to A	(<50 skunk)
    //  BRAnch to [Chosen]
    //  [LBL] CoMPare A with #$3C
    //  Branch to next label if Carry Set
    //  LoaD #$07 to A	(<60 wild boar)
    //  BRAnch to [Chosen]
    //  [LBL] LoaD #$08 to A	(otherwise unicorn)

    //  [Chosen]
    //  STore A to TempSpell
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [LBL] LoaD f:SpecialAbilityAttackProp,X to A
    //  STore A to Temp,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0008	(copy 8 bytes magic info)
    //  Branch to previous label if Not Equals
    //  Store Zero to PartyTargets
    //  Store Zero to MonsterTargets
    //  LoaD Temp to A	(targetting byte in magic info)
    //  Branch to [Targetting] if Not Equals
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to PartyTargets	;default to targetting self
    //  BRAnch to [TargetSet]

    //  [Targetting]
    //  AND A with #$08		(target enemy)
    //  Branch to [TargetEnemy] if Not Equals
    //  LoaD #$F0 to A
    //  STore A to PartyTargets	;entire party
    //  BRAnch to [TargetSet]

    //  [TargetEnemy]
    //  LoaD Temp to A
    //  AND A with #$40		(hits all targets)
    //  Branch to [TargetAll] if Not Equals
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$07 to A
    //  Jump to SubRoutine Random_X_A    	(0..7 random monster)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to MonsterTargets
    //  BRAnch to [TargetSet]

    //  [TargetAll]
    //  LoaD #$FF to A
    //  STore A to MonsterTargets

    //  [TargetSet]
    //  Store Zero to TempAttachedSpell	(CastSpell routine params)
    //  Store Zero to TempSkipNaming
    //  LoaD #$01 to A		(animals are effect magic)
    //  STore A to TempIsEffect
    //  JuMP to CastSpell
}

// Address: _0C67
// Command $16 (Aim)
static void commandTable15(void) {
    // Load #$16 to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA
    // JuMP to FightCommand
}

// Address: _0C6F
// Command $17 (X-Fight / Rapid Fire)
//  ** optimize: lots to trim in the targetting code
//	             could also use BuildTargetBitmask
//               instead of duplicating all its code here
static void commandTable16(void) {
//         lda #$17		;ability name
//  Jump to SubRoutine GFXCmdAttackNameA
//  Store Zero to $22			;index for attack loop
// AttackLoop:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump to SubRoutine Random_X_A 		;0..7 random monster
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//         ldx AttackerOffset
//  STore A to CharStruct::MonsterTargets,X
//  Store Zero to CharStruct::PartyTargets,X
//         ldx AttackerOffset
//         lda CharStruct::MonsterTargets,X
//  STore A to MonsterTargets
//         lda CharStruct::PartyTargets,X
//  STore A to PartyTargets
//  Jump to SubRoutine CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//  STore A to CharStruct::PartyTargets,X
//         lda MonsterTargets
//  STore A to CharStruct::MonsterTargets,X
//  PusH A
//  AND A with #$F0
//         Logical Shift Right A
//         Logical Shift Right A
//         Logical Shift Right A
//         Logical Shift Right A
//         OR A with CharStruct::PartyTargets,X
//  STore A to TempTargetBitmask
//  PulL A
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
//  STore X to $0E			;gearstats offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         JuMP to LH
// RH:Jump to SubRoutine SelectCurrentProcSequence
//  STore Y to $14			;AttackInfo offset
//  Store Zero to $12
//         ldx $0E			;gearstats offset
//  [LBL] lda RHWeapon,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//  Branch to previous label if Not Equals
//  Jump to SubRoutine FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/commAND A with anim
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//  Store Zero to GFXQueue::Data2,X	;right hand, no msword anim
//         ldx $0E			;gearstats offset
//         lda RHWeapon::AtkType,X
//  PusH A
//         lda ProcSequence
//  Transfer A to X
//  PulL A
//  STore A to AtkType,X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
// LH:     ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//  Branch to next label if Not Equals
//         JuMP to Finish
// :Jump to SubRoutine SelectCurrentProcSequence
//  STore Y to $12
//  Store Zero to $14
//         ldx $0E		;gearstats offset
//  [LBL] lda LHWeapon,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $14
//         lda $14
//  CoMPare A with #$0C	;copy 12 bytes weapon data
//  Branch to previous label if Not Equals
//         ldx $0E		;gearstats offset
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//  Jump to SubRoutine FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/commAND A with anim
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//         lda #$80		;left hand, no msword anim
//  STore A to GFXQueue::Data2,X
//         lda ProcSequence
//  Transfer A to X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
// Finish:	inc $22			;attack loop index
//         lda $22
//  CoMPare A with #$04		;4 attacks
//  Branch to [Ret] if EQuals
//         JuMP to AttackLoop
// [Ret] Return To Subroutine
}

// Address: _0DA2
// Command $19 (Observe/Check)
static void commandTable18(void) {
    // lda #$19		;observe ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // lda #$19		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$18		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Address: _0DC3
// Command $1A (Analyze/Scan)
static void commandTable19(void) {
    // lda #$1A		;observe ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // lda #$1A		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$19		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMess
}

// Address: _0DE4
// Command $18 (Conjure)
static void commandTable17(void) {
// ConjureCommand:
//         lda MagicBits+10	;2nd byte of summons
//  AND A with #$FE		;last bit is a song
//         OR A with MagicBits+9		;1st byte of summons
//         bne PickRandomSummon
// ;no summons known
//         lda #$18
//  Jump to SubRoutine GFXCmdAttackNameA
//         lda MessageBoxOffset
//  Transfer A to X
//         lda #$1D		;message
//  STore A to MessageBoxes,X
//         lda ProcSequence
//  Transfer A to X
//         lda #$7E		;always miss
//  STore A to AtkType,X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//         lda #$0D		;ability animation
//  Jump to SubRoutine GFXCmdAbilityAnim
//  Jump to SubRoutine FinishCommandNullTargets
//  Jump to SubRoutine GFXCmdMessage
//         JuMP to Ret
// PickRandomSummon:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  STore X to $0E
//         lda #$0E
//  Jump to SubRoutine Random_X_A    	;0..14
//  CLear Carry
//         adc #$48		;offset of first summon
//  STore A to TempSpell
//  Store Zero to TempIsEffect
//         Logical Shift Right A
//         ror $0E
//         Logical Shift Right A
//         ror $0E
//         Logical Shift Right A
//         ror $0E
//  Transfer A to Y 			;MagicBits offset
//         lda $0E
//  Jump to SubRoutine ShiftDivide_32
//  Transfer A to X 			;MagicBits spell
//         lda MagicBits,Y
//  Jump to SubRoutine SelectBit_X
//         beq PickRandomSummon	;don't know this one, try again
// MagicLamp:			;Magic Lamp use jumps in here
//  Store Zero to PartyTargets
//  Store Zero to MonsterTargets
//         lda TempSpell
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//  [LBL] lda f:AttackProp,X
//  STore A to Temp,Y
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0008		;copy 8 bytes magic data
//  Branch to previous label if Not Equals
//         lda Temp		;targetting
//         bne FindTargets
// ;no targetting data, target self
//         lda AttackerIndex
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to PartyTargets
//  BRAnch to TargetSet
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
//  [LBL] lda CharStruct::Status1,X
//  AND A with #$80		;dead
//         bne DeadAlly
//  Jump to SubRoutine NextCharOffset
//  INcrement Y
//  ComPare Y with #$0004		;4 chars
//  Branch to previous label if Not Equals
//         lda #$80		;defaults to first member if none dead
//  BRAnch to SetAlly
// DeadAlly:
//         tyx
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
// SetAlly:
//  STore A to PartyTargets	;target single dead ally
//  BRAnch to TargetSet
// SingleEnemy:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump to SubRoutine Random_X_A 		;0..7 random monster
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to MonsterTargets
//  BRAnch to TargetSet
// TargetAll:
//         lda Temp		;targetting
//  AND A with #$08		;enemy by default
//         bne AllEnemy
//         lda #$F0
//  STore A to PartyTargets	;all allies
//  BRAnch to TargetSet
// AllEnemy:
//         lda #$FF
//  STore A to MonsterTargets	;all enemies
// TargetSet:
//  Store Zero to TempAttachedSpell	;params for CastSpell
//  Store Zero to TempSkipNaming
//  Jump to SubRoutine CastSpell
//         lda TempAttachedSpell
//  Branch to [Ret] if EQuals
//         lda TempAttachedSpell	;second spell, for phoenix summon
//  STore A to TempSpell
//  Store Zero to TempIsEffect
//         lda TempMonsterTargets
//  STore A to MonsterTargets
//         lda TempPartyTargets
//  STore A to PartyTargets
//  INCrement TempSkipNaming	;2nd spell has no label AND A with diff anim
//  Jump to SubRoutine CastSpell
// [Ret] Return To Subroutine

// ConjureMagicLamp := CommandTable17::MagicLamp   ; Definition needed to jump to here
}

// Address: _0EE0
// Command $1B (Tame/Calm)
static void commandTable1A(void) {
    // lda #$1B		;tame ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // lda #$1B		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$1A		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // JuMP to FinishCommand
}

// Address: _0EFE
// Command $1C (Control)
static void commandTable1B(void) {
    // lda #$1C		;control ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // lda #$1C		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$1B		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Address: _0F1F
// Command $1D (Catch)
static void commandTable1C(void) {
    // lda #$1D		;catch ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // lda #$1D		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$1C		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Address: _0F40
// Command $1E (Release)
static void commandTable1D(void) {
//         ldx AttackerOffset
//         lda CharStruct::CaughtMonster,X
//  STore A to ReleasedMonsterID
//  PusH A
//         lda #$FF		;no monster caught
//  STore A to CharStruct::CaughtMonster,X
//  PulL A
//  Transfer A to X
//         lda f:MonsterRelease,X
//  STore A to TempSpell
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
// :  	lda f:AttackProp,X
//  STore A to TempMagicInfo,Y
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0008		;8 bytes magic data
//  Branch to previous label if Not Equals
//  Jump to SubRoutine SelectCurrentProcSequence
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  [LBL] lda TempMagicInfo,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  ComPare X with #$0005		;copy first 5 bytes
//  Branch to previous label if Not Equals
//  INcrement Y 			;increment dest pointer by 4
//  INcrement Y
//  INcrement Y
//  INcrement Y
//  [LBL] lda TempMagicInfo,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  ComPare X with #$0008		;then copy remaining 3 bytes
//  Branch to previous label if Not Equals
//  Store Zero to MonsterTargets
//  Store Zero to PartyTargets
//         lda TempMagicInfo::Targetting
//         bne Targetting
//         lda AttackerIndex
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to PartyTargets	;default to attacker if no targetting
//  BRAnch to TargetSet
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
//  Jump to SubRoutine Random_X_A		;0..3 random party
//  CoMPare A with AttackerIndex
//         beq TargetParty	;pick again if attacker chosen
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to PartyTargets
//  BRAnch to TargetSet
// TargetEnemy:
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07
//  Jump to SubRoutine Random_X_A	      	;0..7 random monster
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to MonsterTargets
//  BRAnch to TargetSet
// TargetAll:
//         lda TempMagicInfo::Targetting
//  AND A with #$08		;enemy by default
//         bne TargetAllEnemy
//         lda #$F0
//  STore A to PartyTargets
//  BRAnch to TargetSet
// TargetAllEnemy:
//         lda #$FF
//  STore A to MonsterTargets
// TargetSet:
//  Jump to SubRoutine CheckMultiTarget
//         bne Multi
//         lda TempMagicInfo::AtkType
//         bpl _CheckRetarget
//         lda ProcSequence
//  Transfer A to X
//  INCrement HitsInactive,X
//  BRAnch to TargetOK
// _CheckRetarget:
//  Jump to SubRoutine CheckRetarget
//  BRAnch to TargetOK
// Multi:
//  Jump to SubRoutine RemoveInactiveTargets
//  Jump to SubRoutine CheckMultiTarget
// TargetOK:
//  Jump to SubRoutine BuildTargetBitmask
//         lda TempSpell
//  STore A to Temp+1		;attack id
//  Store Zero to Temp		;string table 0
//  Jump to SubRoutine GFXCmdAttackNameFromTemp
//  Jump to SubRoutine FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag,X
//  Store Zero to GFXQueue::Data2,X
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
//  Branch to next label if EQuals
//  INCrement MultiTarget,X	;number of targets (but 1 target -> 0)
//         lda #$80		;multi target
//  [LBL] STore A to TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//  STore A to TargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  STore A to TargetBitmask+1,X
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
//         lda AttackerIndex
//  STore A to $24
//         lda #$14
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit     	;Index * 20, size of CharCommands
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $26			;CharCommands offset
// FindCmd:
//         lda CharCommands::ID,X
//  CoMPare A with #$1E		;release
//         beq Found
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0004		;4 command slots
//         bne FindCmd
//         beq CopyStats
// Found:
//         lda #$1D		;catch
//  STore A to CharCommands::ID,X
//         lda #$28		;target selectable + enemy default
//  STore A to CharCommands::Targetting,X
//  INcrement X
//  INcrement Y
//  BRAnch to FindCmd		;keep going, could have multiple copies
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
//  Store Zero to CharStruct::Status1,X	;clear status for released mon
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0009		;9 bytes of status/passives
//         bne CopyStatus
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx AttackerOffset
// CopyMSword:
//         lda CharStruct::MSwordElemental1,X
//  STore A to SavedCharStats::MSwordElemental1,Y
//  Store Zero to CharStruct::MSwordElemental1,X	;clear all msword
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0006		;6 bytes msword elements/status
//         bne CopyMSword
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx AttackerOffset
// CopyMisc:
//         lda CharStruct::AlwaysStatus1,X
//  STore A to SavedCharStats::AlwaysStatus1,Y
//  Store Zero to CharStruct::AlwaysStatus1,X
//  INcrement X
//  INcrement Y
//  ComPare Y with #$000B		;11 bytes always status/bonuses/etc
//         bne CopyMisc
//         lda ReleasedMonsterID
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_32
//  Transfer A to X
//  Clear A, then Shorten
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
    // STore A to MonsterTargets
    // lda CharStruct::PartyTargets,X
    // STore A to PartyTargets
    // lda CharStruct::SelectedItem,X
    // sec
    // sbc #$E0	;remove consumable item offset from item id
    // Transfer A to X
    // stx $0E		;first item consumable index
    // ldx AttackerOffset
    // lda CharStruct::SecondSelectedItem,X
    // sec
    // sbc #$E0	;remove consumable item offset from item id
    // STore A to $24
    // lda #$0C
    // STore A to $25
    // Jump to SubRoutine Multiply_8bit    	;item*12
    // Lengthen A
    // CLear Carry flag
    // lda $26			;second item * 12
    // adc $0E			;+ first item
    // Transfer A to X
    // Clear A, then Shorten
    // lda f:MixComboTbl,X
    // STore A to TempSpell
    // STore Zero to TempAttachedSpell
    // STore Zero to TempSkipNaming
    // lda #$01
    // STore A to TempIsEffect
    // JuMP to CastSpell
}

// Address: _1169
// Command $21 (Pray/Recover)
static void commandTable20(void) {
    // lda #$21		;recover ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget
    // lda #$21		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$20		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeMultiTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdDamageNumbers
}

// Address: _118A
// Command $22 (Revive)
static void commandTable21(void) {
    // lda #$22		;revive ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget
    // lda ProcSequence
    // Transfer A to X
    // inc HitsInactive,X
    // lda #$22		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$21		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeMultiTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdDamageNumbers
}

// Address: _11B2
// Command $23 (Gaia/Terrain)
static void commandTable22(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda Level
//  Jump to SubRoutine Random_X_A 	;0..Level
//  CoMPare A with #$0B
//  Branch to next label if Carry Set
//  Transfer Direct page to aCcumulator          	;<11, 0
//  BRAnch to Chosen
// :	cmp #$15
//  Branch to next label if Carry Set
//         lda #$01     	;<21, 1
//  BRAnch to Chosen
// :	cmp #$33
//  Branch to next label if Carry Set
//         lda #$02     	;<50, 2
//  BRAnch to Chosen
//  [LBL] lda #$03     	;otherwise 3
// Chosen:
//  STore A to $0E		;terrain spell slot 0-3
//         lda TerrainType
//  Jump to SubRoutine ShiftMultiply_4
//  CLear Carry
//         adc $0E
//  Transfer A to X
//         lda f:TerrainAttackTbl,X
//  STore A to TempSpell
//         lda TempSpell	;pointless load?
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//  [LBL] lda f:SpecialAbilityAttackProp,X
//  STore A to Temp,Y
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0008	;copy 8 bytes spell data
//  Branch to previous label if Not Equals
//  Store Zero to PartyTargets
//  Store Zero to MonsterTargets
//         lda Temp		;targetting byte
//         bne Targetting
//         lda AttackerIndex	;default to attacker
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to PartyTargets
//  BRAnch to TargetSet
// Targetting:
//  AND A with #$08	;target enemy by default
//         bne TargetEnemy
//         lda Temp
//  AND A with #$40	;target all
//         bne TargetAllParty
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump to SubRoutine Random_X_A 	;0..3 random party
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to PartyTargets
//  BRAnch to TargetSet
// TargetAllParty:
//         lda #$F0
//  STore A to PartyTargets
//  BRAnch to TargetSet
// TargetEnemy:
//         lda Temp
//  AND A with #$40	;target all
//         bne TargetAllEnemy
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$07	;0..7 random monster
//  Jump to SubRoutine Random_X_A
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to MonsterTargets
//  BRAnch to TargetSet
// TargetAllEnemy:
//         lda #$FF
//  STore A to MonsterTargets
// TargetSet:
//  Store Zero to TempAttachedSpell
//  Store Zero to TempSkipNaming
//         lda #$01
//  STore A to TempIsEffect
//         JuMP to CastSpell
}

// Address: _125E
// Command $25 (Hide)
static void commandTable24(void) {
//         ldx AttackerOffset
//         lda CharStruct::Status4,X
//         OR A with #$01	;hidden
//  STore A to CharStruct::Status4,X
//         lda #$25	;hide ability name
//  Jump to SubRoutine GFXCmdAttackNameA
//         lda #$24	;hide ability anim
//  Jump to SubRoutine GFXCmdAbilityAnim
//         lda ProcSequence
//  Transfer A to X
//  Store Zero to AtkType,X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//  INCrement UnknownReaction
//  Jump to SubRoutine FinishCommandNullTargets
//         lda AttackerIndex
//  STore A to $24
//         lda #$14	;20, size of CharCommands struct
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $26
// FindHideCommands:
//         lda CharCommands::ID,X
//  CoMPare A with #$25	;hide command
//         beq Found
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0004	;4 command slots
//         bne FindHideCommands
//  Branch to [Ret] if EQuals
// Found:	lda #$26	;show command
//  STore A to CharCommands::ID,X
//         lda #$08	;target enemy?
//  STore A to CharCommands::Targetting,X
//  INcrement X
//  INcrement Y
//  BRAnch to FindHideCommands
// [Ret] Return To Subroutine
}

// Address: _12B3
// Command $26 (Show)
static void commandTable25(void) {
//         ldx AttackerOffset
//         lda CharStruct::Status4,X
//  AND A with #$FE	;clear hidden
//  STore A to CharStruct::Status4,X
//         lda #$26	;show ability name
//  Jump to SubRoutine GFXCmdAttackNameA
//         lda #$25	;show ability anim
//  Jump to SubRoutine GFXCmdAbilityAnim
//         lda ProcSequence
//  Transfer A to X
//  Store Zero to AtkType,X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//  INCrement UnknownReaction
//  Jump to SubRoutine FinishCommandNullTargets
//         lda AttackerIndex
//  STore A to $24
//         lda #$14	;20, size of CharCommands struct
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx $26
// FindShowCommands:
//         lda CharCommands::ID,X
//  CoMPare A with #$26	;show command
//         beq Found
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0004	;4 command slots
//         bne FindShowCommands
//  Branch to [Ret] if EQuals
// Found:
//         lda #$25
//  STore A to CharCommands::ID,X
//  Store Zero to CharCommands::Targetting,X
//  INcrement X
//  INcrement Y
//  BRAnch to FindShowCommands
// [Ret] Return To Subroutine
}

// Address: _1306
// Command $29 (Flirt)
static void commandTable28(void) {
    // lda #$29	;flirt ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask
    // lda #$29	;ability name
    // Jump to SubRoutine GFXCmdAttackNameA
    // lda #$28	;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // Jump to SubRoutine GFXCmdDamageNumbers
    // lda MessageBoxOffset
    // Transfer A to X
    // lda #$27	;message
    // STore A to MessageBoxes,X
    // JuMP to GFXCmdMessage
}

// Address: _1333
// Command $2A (Dance)
static void commandTable29(void) {
//  Store Zero to ProcSequence	;reset command sequence (no procs)
//  Store Zero to NextGFXQueueSlot
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump to SubRoutine Random_X_A		;0..3 random dance
//  STore A to TempDance
//         ldx AttackerOffset
//         lda CharStruct::ArmorProperties,X
//  AND A with #$04		;sword dance up
//         beq DanceCheck
//  Jump to SubRoutine Random_0_99
//         Logical Shift Right A
//         bcs NotSwordDance	;50% chance of sword dance
//         lda #$03		;sword dance
//  STore A to TempDance
//  BRAnch to DanceCheck
// NotSwordDance:
//  Jump to SubRoutine Random_0_99
//         Logical Shift Right A
//  Store Zero to TempDance
//         rol TempDance		;50% chance of 0 or 1
// DanceCheck:
//         lda TempDance
//  CoMPare A with #$03		;sword dance
//         beq SwordDance
//  Jump to SubRoutine GetTargets
//  Jump to SubRoutine CheckRetarget
//  Jump to SubRoutine BuildTargetBitmask
//  Jump to SubRoutine CheckMultiTarget
//  CLear Carry
//         lda TempDance
//         adc #$79		;offset to dance strings
//  STore A to Temp+1		;string id / ability id
//  Store Zero to Temp		;string table
//  Jump to SubRoutine GFXCmdAttackNameFromTemp
//         lda #$29		;dance anim
//  Jump to SubRoutine GFXCmdAbilityAnim
//  Jump to SubRoutine SelectCurrentProcSequence
//         lda Temp+1		;ability id
//  Jump to SubRoutine CopyROMMagicInfo
//  Jump to SubRoutine MagicAtkTypeSingleTarget
//  Jump to SubRoutine FinishCommand
//         JuMP to GFXCmdDamageNumbers
// SwordDance:
//         lda #$7D		;sword dance ability
//  STore A to Temp+1		;string id / ability id
//  Store Zero to Temp		;string table
//  Jump to SubRoutine GFXCmdAttackNameFromTemp
//         lda #$29		;dance anim
//  Jump to SubRoutine GFXCmdAbilityAnim
//         lda ProcSequence
//  Transfer A to X
//         lda #$7F		;do nothing
//  STore A to AtkType,X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//  Jump to SubRoutine FinishCommandNullTargets
//  Jump to SubRoutine GFXCmdDamageNumbers
//         ldx AttackerOffset
//         lda CharStruct::DamageMod,X
//         OR A with #$D0		;auto hit, damage*2, M*2
//  STore A to CharStruct::DamageMod,X
//         JuMP to SimpleFight
}

// Address: _13CE
// Command $2B (Mimic)
static void commandTable2A(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//         ldx AttackerOffset
//  [LBL] lda SavedAction,Y
//  STore A to CharStruct::ActionFlag,X
//  INcrement X
//  INcrement Y
//  ComPare Y with #$000A	;copy 10 bytes action data
//  Branch to previous label if Not Equals
//         ldx AttackerOffset
//         lda CharStruct::ActionFlag,X
//  AND A with #$FE	;clear "costs mp" bit
//  STore A to CharStruct::ActionFlag,X
//         lda CharStruct::Command,X
//         JuMP to DispatchCommand_CommandReady
}

// Address: _13EF
// Command $51
// Flirt Throbbing
// (null command with a message)
static void commandTable2F(void) {
    // Jump to SubRoutine FindOpenGFXQueueSlot
    // STore Zero to GFXQueue::Flag,X
    // STore Zero to GFXQueue::Cmd,X
    // STore Zero to GFXQueue::Type,X
    // STore Zero to GFXQueue::Data1,X
    // STore Zero to GFXQueue::Data2,X
    // lda ProcSequence
    // Transfer A to X
    // STore Zero to AtkType,X
    // STore Zero to MultiTarget,X
    // STore Zero to TargetType,X
    // Jump to SubRoutine FinishCommandNullTargets
    // lda MessageBoxOffset
    // Transfer A to X
    // lda #$28	;message to display
    // STore A to MessageBoxes,X
    // JuMP to GFXCmdMessage
}

// Address: _141D
// Command $52
// Jump with a different name
static void commandTable30(void) {
    // lda #$52	;commAND A with name
    // Jump to SubRoutine GFXCmdAttackNameA
    // JuMP to CommandTable0C::Anim
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
//  Store Zero to $0E		;hand
//  Store Zero to NextGFXQueueSlot
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//  Branch to next label if Not Equals
//         lda #$80	;left hand
//  STore A to $0E
// :	jsr FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag
//         lda #$FC	;exec graphics command
//  STore A to GFXQueue::Cmd
//         lda #$01	;ability/commAND A with anim
//  STore A to GFXQueue::Type
//         lda #$04	;fight
//  STore A to GFXQueue::Data1
//         lda $0E		;hAND A with (0 for RH, 80 for LH)
//  STore A to GFXQueue::Data2
//         lda #$7E	;always miss
//  STore A to AtkType
//  Store Zero to MultiTarget
//  Store Zero to TargetType
//  Store Zero to CommandTargetBitmask
//  Store Zero to CommandTargetBitmask+1
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
//         lda #$FF
//  STore A to a:wMonsterTargets	;**optimize: wasted bytes
//  Store Zero to a:wPartyTargets
//         lda TempEffect
//  STore A to TempSpell
//         lda #$01
//  STore A to TempIsEffect
//  STore A to TempSkipNaming
//  Store Zero to TempAttachedSpell
//  Jump to SubRoutine CastSpell
//         ldx AttackerOffset
//         lda CharStruct::Command,X
//  CoMPare A with #$0C	;capture/mug
//         bne Ret	;removes return address from stack for capture
//  PulL X 		;likely unreachable since capture cancels procs
// [Ret] Return To Subroutine
}

// Address: _1490
// Command $54
// Job-specific attack animation
// likely for credits demo?
static void commandTable32(void) {
    // ldx AttackerOffset
    // CLear Carry flag
    // lda CharStruct::Job,X
    // adc #$30
    // Jump to SubRoutine GFXCmdAbilityAnim
    // lda #$7F	;null attack
    // STore A to AtkType
    // STore Zero to MultiTarget
    // STore Zero to TargetType
    // lda #$08	;first monster
    // STore A to CommandTargetBitmask
    // STore A to TargetBitmask
    // STore Zero to CommandTargetBitmask+1
    // STore Zero to TargetBitmask+1
    // inc UnknownReaction
    // Return to SubRoutine
}

// Address: _14B8
// Command $55
// For Double Lance
// Attacks twice per hAND A with if
// hand's weapon has this command proc
static void commandTable33(void) {
//  Store Zero to ProcSequence	;cancels any other procs
//  Store Zero to NextGFXQueueSlot
//         ldx AttackerOffset
//         lda CharStruct::MonsterTargets,X
//  STore A to MonsterTargets
//         lda CharStruct::PartyTargets,X
//  STore A to PartyTargets
//  Jump to SubRoutine CheckRetarget
//         ldx AttackerOffset
//         lda PartyTargets
//  STore A to CharStruct::PartyTargets,X
//         lda MonsterTargets
//  STore A to CharStruct::MonsterTargets,X
//  PusH A
//  AND A with #$F0
//         Logical Shift Right A
//         Logical Shift Right A
//         Logical Shift Right A
//         Logical Shift Right A
//         OR A with CharStruct::PartyTargets,X
//  STore A to TempTargetBitmask
//  PulL A
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
//  STore X to $0E			;GearStruct offset
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//         bne RH
//         JuMP to LH
// RH:	jsr SelectCurrentProcSequence
//  STore Y to $14
//  Store Zero to $12
//         ldx $0E
// :      	lda RHWeapon,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//  Branch to previous label if Not Equals
//  Jump to SubRoutine FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag,X
//         lda #$FC		;exec graphics command
//  STore A to GFXQueue::Cmd,X
//         lda #$01		;ability/commAND A with animation
//  STore A to GFXQueue::Type,X
//         lda #$04		;fight
//  STore A to GFXQueue::Data1,X
//  Store Zero to GFXQueue::Data2,X	;right hand, no msword
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::AtkType,X
//  PusH A
//         lda ProcSequence
//  Transfer A to X
//  PulL A
//  STore A to AtkType,X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
//  Jump to SubRoutine SelectCurrentProcSequence
//  STore Y to $14
//  Store Zero to $12
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::Properties,X
//  AND A with #$02		;commAND A with instead of attack
//         beq LH
//         lda RHWeapon::Param3,X
//  CoMPare A with #$55		;this command
//         bne LH
//  [LBL] lda RHWeapon,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $12
//         lda $12
//  CoMPare A with #$0C		;copy 12 bytes data for 2nd attack
//  Branch to previous label if Not Equals
//         lda #$80
//  STore A to ActionAnimShift	;flag for later anim manipulation
//  Jump to SubRoutine FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag,X
//  Store Zero to GFXQueue::Cmd,X
//  Store Zero to GFXQueue::Type,X
//  Store Zero to GFXQueue::Data1,X
//  Store Zero to GFXQueue::Data2,X
//         ldx $0E			;GearStruct offset
//         lda RHWeapon::AtkType,X
//  PusH A
//         lda ProcSequence
//  Transfer A to X
//  PulL A
//  STore A to AtkType,X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
// LH:       ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//  Branch to next label if Not Equals
//         JuMP to Ret
// :Jump to SubRoutine SelectCurrentProcSequence
//  STore Y to $12
//  Store Zero to $14
//         ldx $0E			;GearStruct offset
// :   	lda LHWeapon,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $14
//         lda $14
//  CoMPare A with #$0C		;copy 12 bytes weapon data
//  Branch to previous label if Not Equals
//         ldx $0E			;GearStruct offset
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//  Jump to SubRoutine FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag,X
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
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
//  Jump to SubRoutine SelectCurrentProcSequence
//  STore Y to $12
//  Store Zero to $14
//         ldx $0E
//         lda LHWeapon::Properties,X
//  AND A with #$02		;commAND A with instead of attack
//  Branch to [Ret] if EQuals
//         lda LHWeapon::Param3,X
//  CoMPare A with #$55		;this command
//         bne Ret
//  [LBL] lda LHWeapon,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $14
//         lda $14
//  CoMPare A with #$0C		;copy 12 bytes weapon data for 2nd atk
//  Branch to previous label if Not Equals
//         lda ActionAnimShift
//         OR A with #$40
//  STore A to ActionAnimShift
//         ldx $0E
//         lda ProcSequence
//  Transfer A to Y
//         lda LHWeapon::AtkType,X
//  STore A to AtkType,Y
//  Jump to SubRoutine FindOpenGFXQueueSlot
//  Store Zero to GFXQueue::Flag,X
//  Store Zero to GFXQueue::Cmd,X
//  Store Zero to GFXQueue::Type,X
//  Store Zero to GFXQueue::Data1,X
//  Store Zero to GFXQueue::Data2,X
//         lda ProcSequence
//  Transfer A to X
//  Store Zero to MultiTarget,X
//  Store Zero to TargetType,X
//         lda ProcSequence
//  A Shift Left
//  Transfer A to X
//         lda TempTargetBitmask
//  STore A to CommandTargetBitmask,X
//         lda TempTargetBitmask+1
//  STore A to CommandTargetBitmask+1,X
//  INCrement ProcSequence
//  Jump to SubRoutine GFXCmdDamageNumbers
// [Ret] Return To Subroutine
}

// Address: _16A2
// Command $56
// Earthquake weapon effect
static void commandTable34(void) {
    // lda #$4A	;earthquake
    // STore A to TempEffect
    // JuMP to CommandTable31::WeaponEffectCommand
}

// Address: _16AA
static void copyAbilityInfo(void) {
//  PusH A
//  Jump to SubRoutine SelectCurrentProcSequence
//  PulL A
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//  Store Zero to $0A
//  [LBL] lda f:BattleCmdProp,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $0A
//         lda $0A
//  CoMPare A with #$05     ;copy first 5 bytes
//  Branch to previous label if Not Equals
//  INcrement Y          ;skip 4 on destination
//  INcrement Y
//  INcrement Y
//  INcrement Y
//  [LBL] lda f:BattleCmdProp,X
//  STore A to AttackInfo,Y
//  INcrement X
//  INcrement Y
//  INCrement $0A
//         lda $0A
//  CoMPare A with #$08      ;copy remaining 3 bytes
//  Branch to previous label if Not Equals
//  Return To Subroutine
}

// Address: _16E1
// Displays an ability or command animation
// creates Action $00,FC,01,<A>,00
static void gfXCmdAbilityAnim(void) {
    // PusH A
    // Jump to SubRoutine FindOpenGFXQueueSlot
    // STore Zero to GFXQueue::Flag,X
    // lda #$FC	;exec graphics command
    // STore A to GFXQueue::Cmd,X
    // lda #$01	;ability/commAND A with anim
    // STore A to GFXQueue::Type,X
    // PulL A
    // STore A to GFXQueue::Data1,X
    // STore Zero to GFXQueue::Data2,X
    // Return to SubRoutine
}

// Address: _16FA
// Displays an Attack name from String Table 1
// creates Action $00,FC,04,01,<A>
static void gfxCmdAttackNameA(void) {
    // STore A to Temp+1
    // lda #$01
    // STore A to Temp
    // JuMP to GFXCmdAttackNameFromTemp
}

// Address: _1705
static void magicAtkTypeSingleTarget(void) {
    // lda ProcSequence
    // Transfer A to X
    // ldy $0C
    // lda AttackInfo::MagicAtkType,Y
    // AND A with #$7F
    // STore A to AtkType,X
    // STore Zero to MultiTarget,X
    // STore Zero to TargetType,X
    // Return to SubRoutine
}

// Address: _171A
static void magicAtkTypeMultiTarget(void) {
    // lda ProcSequence
    // Transfer A to X
    // ldy $0C
    // lda AttackInfo::MagicAtkType,Y
    // AND A with #$7F
    // STore A to AtkType,X
    // lda TempTargetting
    // inc 	;unconditional, so always considered multitarget
    // STore A to MultiTarget,X
    // lda #$80	;multi target
    // STore A to TargetType,X
    // Return to SubRoutine
}

// Address: _1735
// Copies command targetting to final locations and
// advances ProcSequence
static void finishCommand(void) {
    // lda ProcSequence
    // A Shift Left
    // Transfer A to X
    // lda TempTargetBitmask
    // STore A to CommandTargetBitmask,X
    // STore A to TargetBitmask,X
    // lda TempTargetBitmask+1
    // STore A to CommandTargetBitmask+1,X
    // STore A to TargetBitmask+1,X
    // inc ProcSequence
    // Return to SubRoutine
}

// Address: _1750
// wipes command targetting and advances ProcSequence
static void finishCommandNullTargets(void) {
    // lda ProcSequence
    // A Shift Left
    // Transfer A to X
    // STore Zero to CommandTargetBitmask,X
    // STore Zero to CommandTargetBitmask+1,X
    // inc ProcSequence
    // Return to SubRoutine
}

// Address: _175F
static void getTargets(void) {
    // ldx AttackerOffset
    // lda CharStruct::PartyTargets,X
    // STore A to PartyTargets
    // lda CharStruct::MonsterTargets,X
    // STore A to MonsterTargets
    // Return to SubRoutine
}

// Address: _176C
static void handleAtbMenu(void) {
//         lda MenuData::MenuOpen
//         bne MenuOpen
//         JuMP to MenuClosed
// MenuOpen:	;checks if current display info for status/mp matches what's in CharStruct
//         lda DisplayInfo::CurrentChar
//  STore A to CurrentChar
//  Jump to SubRoutine CalculateCharOffset
//         Lengthen A
//         lda CharStruct::Status1,X	;includes status 2
//  CoMPare A with DisplayInfo::Status1
//         bne Differs
//         lda CharStruct::Status3,X	;includes status 4
//  CoMPare A with DisplayInfo::Status3
//         bne Differs
//         lda CharStruct::CurMP,X
//  CoMPare A with DisplayInfo::CurMP
//         bne Differs
//  Clear A, then Shorten
//  BRAnch to Matches
// Differs:	;disable commands as needed, AND A with update displayinfo for menu
//  Clear A, then Shorten
//  Jump to SubRoutine CheckDisablingStatus
//         bne Disabled
//  Jump to SubRoutine DisableCommandsMagic
//  Jump to SubRoutine ApplyBerserkStatus
//         bne Disabled
//         lda #$05		;C1 routine
//  Jump to SubRoutine CallC1
//         lda #$06		;C1 routine
//  Jump to SubRoutine CallC1
//         Lengthen A
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//  STore A to DisplayInfo::Status1
//         lda CharStruct::Status3,X
//  STore A to DisplayInfo::Status3
//         lda CharStruct::CurMP,X
//  STore A to DisplayInfo::CurMP
//  Clear A, then Shorten
//  BRAnch to Matches
// Disabled:	;if character has become disabled while their menu is open, close the menu
//         lda DisplayInfo::CurrentChar
//  STore A to MenuCurrentChar
//         lda GearChanged
//  Branch to next label if EQuals
//  Store Zero to GearChanged
//  Jump to SubRoutine ReplaceHands
//  Jump to SubRoutine ApplyGear
//  [LBL] lda DisplayInfo::CurrentChar
//  STore A to MenuCurrentChar
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu
//         lda #$01	;C1 routine: close menu
//  Jump to SubRoutine CallC1
// WaitMenu:
//         lda MenuDataC1::MenuOpen
//         bne WaitMenu	;ends up 0 eventually? via interrupts?
//         lda #$FF
//  STore A to DisplayInfo::CurrentChar
//  Return To Subroutine
// Matches:	;data either already matched or has been updated
//         lda ControllingA
//  Branch to [Ret] if EQuals
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//         lda ControlTarget,X
//  Branch to next label if EQuals
//  Transfer A to X
//         lda ActiveParticipants,X
//         bne Ret
//  [LBL] lda DisplayInfo::CurrentChar
//  STore A to MenuCurrentChar
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu2
//         lda #$01	;C1 routine: close menu
//  Jump to SubRoutine CallC1
// WaitMenu2:
//         lda MenuDataC1::MenuOpen
//         bne WaitMenu2	;ends up 0 eventually? via interrupts?
//         lda #$80
//  STore A to MenuData::ActionFlag
//  Store Zero to MenuData::Command
//  Store Zero to MenuData::MonsterTargets
//  Store Zero to MenuData::PartyTargets
//  Store Zero to MenuData::SelectedItem
//  Store Zero to MenuData::SecondActionFlag
//  Store Zero to MenuData::SecondCommand
//  Store Zero to MenuData::SecondMonsterTargets
//  Store Zero to MenuData::SecondPartyTargets
//  Store Zero to MenuData::SecondSelectedItem
//  BRAnch to MenuClosed
// [Ret] Return To Subroutine
// MenuClosed:								;
//         lda DisplayInfo::CurrentChar
//  CoMPare A with #$FF
//         beq NoCurrentChar
//         JuMP to ProcessMenuCommand
// NoCurrentChar:
//         lda ATBReadyQueue
//  CoMPare A with #$FF
//         bne NextReadyATB
//  Return To Subroutine		;no one else in queue either
// NextReadyATB:	;there's a character in the queue with ATB ready
//  PusH A
//  Transfer Direct page to aCcumulator
//  Transfer A to X
// AdvanceQueue:	;advances all the queue elements up by one, there's a terminator $FF in the 5th slot
//         lda ATBReadyQueue+1,X
//  STore A to ATBReadyQueue,X
//  INcrement X
//  ComPare X with #$0004
//         bne AdvanceQueue
//         dec ATBReadyCount
//  PulL A
//  STore A to MenuCurrentChar
//  STore A to DisplayInfo::CurrentChar
//  Jump to SubRoutine CalculateCharOffset
//         lda QuickTurns
//         beq DontStopTime
//         lda DisplayInfo::CurrentChar
//  CoMPare A with QuickCharIndex
//         beq DontStopTime
//  Jump to SubRoutine GetTimerOffset  	;sets Y to Timer offset
//         lda CurrentTimer::ATB,Y
//         bne FinishEarly	;check if frozen char's ATB is ready
//         lda #$01		;increase ATB to 1 (no longer ready)
//  STore A to CurrentTimer::ATB,Y
//  STore A to EnableTimer::ATB,Y
//  BRAnch to FinishEarly
// DontStopTime:
//  Jump to SubRoutine CheckDisablingStatus
//         beq NotDisabled
// FinishEarly:
//         lda #$FF
//  STore A to DisplayInfo::CurrentChar
//  Return To Subroutine
// NotDisabled:	;character's turn has just come up
//  Store Zero to MenuCurrentChar+1
//  Jump to SubRoutine ApplyBerserkStatus
//         bne FinishEarly
//  Jump to SubRoutine DisableCommandsMagic
//         lda #$01
//  STore A to ATBWaiting
//         lda ATBWaitTime
//  STore A to ATBWaitLeft
//         Lengthen A
//         ldx AttackerOffset
//         lda CharStruct::Status1,X	;includes 2
//  STore A to DisplayInfo::Status1
//         lda CharStruct::Status3,X	;includes 4
//  STore A to DisplayInfo::Status3
//         lda CharStruct::CurMP,X
//  STore A to DisplayInfo::CurMP
//  Store Zero to CharStruct::CmdStatus,X	;also damagemod
//  Clear A, then Shorten
//  Jump to SubRoutine CheckControlTargetActive
//         lda #$01
//  STore A to FleeTickerActive	;can't start running until first atb
//         lda EncounterInfo::IntroFX
//         bpl NoCredits
//  Store Zero to MenuData::MenuOpen
//  Return To Subroutine
// NoCredits:
//         lda DisplayInfo::CurrentChar
//  Jump to SubRoutine GetTimerOffset	;Y = Timer offset
//         lda EnableTimer::ATB,Y
//         beq TimerOff
//         lda #$FF
//  STore A to DisplayInfo::CurrentChar
//         JuMP to NoCurrentChar
// TimerOff:
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine CallC1 	;C1 routine $00: open menu
// WaitMenu3:
//         lda MenuDataC1::MenuOpen
//         beq WaitMenu3
//  Return To Subroutine
// ProcessMenuCommand:
//  Store Zero to ATBWaiting
//  Jump to SubRoutine ProcessMenuCommandData
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
//  STore Zero to ControllingA
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//         lda ControlTarget,X
//         beq Finish
//  Transfer A to Y
//         lda ActiveParticipants,Y
//         beq Finish
//         lda #$01
//  STore A to ControllingA
// Finish: STore A to ControllingB
//  Return To Subroutine
}

// Address: _1926
// copies command data from MenuData struct into CharStruct,
// and performs any other necessary processing
// Also handles gear changes, removing control when needed,
// consuming items when used, and action delays
static void processMenuCommandData(void) {
//         lda EncounterInfo::IntroFX
//  Branch to next label if PLus		;check for credits demo
//  Jump to SubRoutine SetupCreditsDemo
//  [LBL] lda DisplayInfo::CurrentChar
//  STore A to CurrentChar
//         lda GearChanged
//  Branch to next label if EQuals
//  Store Zero to GearChanged
//  Jump to SubRoutine ReplaceHands
//  Jump to SubRoutine ApplyGear
//  [LBL] lda DisplayInfo::CurrentChar
//  Jump to SubRoutine CalculateCharOffset
//         lda CharStruct::Status1,X
//  AND A with #$C0	;dead/stone
//         bne ClearControl
//         lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
//  AND A with #$78	;sleep/para/charm/berserk
//         bne ClearControl
//         lda CharStruct::Status3,X
//  AND A with #$10	;stop
//         bne ClearControl
//         lda CharStruct::Status4,X
//  AND A with #$80	;erased
//  Branch to next label if EQuals
// ClearControl:
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//  Store Zero to ControlTarget,X
//  BRAnch to ClearMenuData
//  [LBL] lda DisplayInfo::CurrentChar
//  CoMPare A with MenuData::CurrentChar
//  Branch to next label if EQuals
//         lda EncounterInfo::IntroFX
//         bmi :+		;branch if credits fight
//         lda #$0D	;C1 Routine
//  Jump to SubRoutine CallC1
// WaitForever:
//  BRAnch to WaitForever	;infinite loop?
//  [LBL] lda DisplayInfo::CurrentChar
//  Transfer A to X
//         lda ControlTarget,X
//         beq NoControlTarget
//  Transfer A to Y
//         lda ActiveParticipants,Y
//         beq ClearMenuData
//  INCrement ControlCommand,X
//  SEt Carry flag
//         lda ControlTarget,X
//         sbc #$04
//  STore A to $0E		;monster index of control target
//  Transfer A to Y
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//  CLear Carry
//         lda f:_d0eedb,X	;size of CharControl struct
//         adc MenuData::SelectedItem	;action 0-3
//  Transfer A to X
//         lda CharControl::Actions,X
//  STore A to MonsterControlActions,Y
//  SEt Carry flag
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
//  Store Zero to MenuData::Command
//  Store Zero to MenuData::MonsterTargets
//  Store Zero to MenuData::PartyTargets
//  Store Zero to MenuData::SelectedItem
//  Store Zero to MenuData::SecondActionFlag
//  Store Zero to MenuData::SecondCommand
//  Store Zero to MenuData::SecondMonsterTargets
//  Store Zero to MenuData::SecondPartyTargets
//  Store Zero to MenuData::SecondSelectedItem
//  BRAnch to CopyCommands
// NoControlTarget:
//         lda ControllingB
//         bne ClearMenuData	;controlling with no target
// CopyCommands:
//         lda DisplayInfo::CurrentChar
//  Transfer A to X
//  STore X to $2A
//         ldx #$028A   	;650, size of CharSpells struct
//  STore X to $2C
//  Jump to SubRoutine Multiply_16bit	;not using the rom *650 table?
//         Lengthen A
//  CLear Carry
//         lda $2E		;CurrentChar * 650
//         adc #$2D34   	;CharSpells struct location
//  STore A to TempSpellOffset
//  Clear A, then Shorten
//         ldx AttackerOffset
//         lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
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
//  BRAnch to CheckCommand
// NotXMagic:
//  Store Zero to CharStruct::SecondCommand,X
//  Store Zero to CharStruct::SecondMonsterTargets,X
//  Store Zero to CharStruct::SecondMonsterTargets,X	;**bug: PartyTargets
//  Store Zero to CharStruct::SecondSelectedItem,X
//  Store Zero to CharStruct::SecondActionFlag,X
// CheckCommand:
//         lda MenuData::Command
//  STore A to $24
//         lda #$08
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit
//         ldx $26		;commAND A with * 8
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
//         OR A with #$01     	;costs MP
//  STore A to CharStruct::ActionFlag,Y
// NotMagicCommand:
//         lda MenuData::Command
//  Transfer A to X
//         lda f:BattleCmdDelay,X
//         bmi CalculateDelay
//  PusH A
//         lda MenuData::Command
//  CoMPare A with #$11	;throw
//         beq Item
//  CoMPare A with #$20	;drink
//         beq Item
//  CoMPare A with #$1F	;mix
//         bne NotItem
// Mix:
//         lda MenuData::SecondSelectedItem
//  PusH A
//  Transfer A to X
//         lda InventoryItems,X
//         ldx AttackerOffset
//  STore A to CharStruct::SecondSelectedItem,X
//  PulL A
//  Jump to SubRoutine ConsumeItem
// Item:
//         lda MenuData::SelectedItem
//  PusH A
//  Transfer A to X
//         lda InventoryItems,X
//         ldx AttackerOffset
//  STore A to CharStruct::SelectedItem,X
//  PulL A
//  Jump to SubRoutine ConsumeItem
// NotItem:
//  PulL A
//         JuMP to Finish
// CalculateDelay:
//         lda MenuData::ActionFlag
//  AND A with #$08	;XMagic
//  Branch to next label if EQuals
//         JuMP to MagicDelay
//  [LBL] lda MenuData::ActionFlag
//  AND A with #$40	;Item
//         bne ItemDelay
//         lda MenuData::ActionFlag
//  AND A with #$20	;Magic
//  Branch to next label if EQuals
//         JuMP to MagicDelay
//  [LBL] lda MenuData::ActionFlag
//  AND A with #$10	;Weapon used as item
//         beq WeaponAttackDelay
//         JuMP to WeaponUseDelay
// WeaponAttackDelay:	;despite the calculation, I don't think any weapons have delay values
//  Store Zero to $0E
//         lda DisplayInfo::CurrentChar
//  STore A to $24
//         lda #$54     ;84, size of GearStats struct
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit
//         ldy $26
//         ldx AttackerOffset
//         lda CharStruct::RHWeapon,X
//  Branch to next label if EQuals
//         lda RHWeapon::Targetting,Y
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//  STore A to $0E		;attack delay
// :       ldx AttackerOffset
//         lda CharStruct::LHWeapon,X
//  Branch to next label if EQuals
//         lda LHWeapon,Y
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//  CLear Carry
//         lda f:AttackDelayTbl,X
//         adc $0E		;add other weapon's delay
//  STore A to $0E
//  [LBL] lda $0E		;attack delay
//         JuMP to Finish
// ItemDelay:
//         lda MenuData::SelectedItem
//  Transfer A to X
//         lda InventoryItems,X
//         ldx AttackerOffset
//  STore A to CharStruct::SelectedItem,X
//  SEt Carry flag
//         sbc #$E0	;consumable item offset
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//         lda f:ConsumableItemProp+2,X
//  AND A with #$08
//  Branch to next label if Not Equals
//         lda MenuData::SelectedItem
//  Jump to SubRoutine ConsumeItem
//  [LBL] lda f:ConsumableItemProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//  BRAnch to Finish
// MagicDelay:
//  Store Zero to $0E
//         lda MenuData::SelectedItem
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//         lda f:AttackProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//  STore A to $0E		;attack delay
//         lda MenuData::ActionFlag
//  AND A with #$08	;X-Magic
//         beq FinishMagic
//         lda MenuData::SecondSelectedItem
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//         lda f:AttackProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//  CLear Carry
//         lda f:AttackDelayTbl,X
//         adc $0E		;add other spell's delay
//  STore A to $0E
// FinishMagic:
//         lda $0E		;attack delay
//  BRAnch to Finish
// WeaponUseDelay:
//         lda DisplayInfo::CurrentChar
//  STore A to $24
//         lda #$54     	;84, size of GearStats struct
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit
//         ldy $26
//         lda MenuData::SelectedItem
//  Branch to next label if EQuals
//         Lengthen A
//  Transfer Y to A
//  CLear Carry
//         adc #$000C	;shifts offset from RHWeapon to LHWeapon
//  Transfer A to Y
//  Clear A, then Shorten
//  [LBL] lda RHWeapon::ItemMagic,Y	;could be LHWeapon
//  AND A with #$7F	;weapon magic to cast
//         beq Finish
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//         lda f:AttackProp,X
//  AND A with #$03	;delay bits (delay/10)
//  Transfer A to X
//         lda f:AttackDelayTbl,X
// Finish:
//  PusH A
//         lda DisplayInfo::CurrentChar
//  Jump to SubRoutine GetTimerOffset	;Y AND A with $36 = timer offset
//         ldx AttackerOffset
//  PulL A
//  Jump to SubRoutine HasteSlowMod	;adjusts delay
//  STore A to CurrentTimer::ATB,Y	;time until action fires
//         lda #$41		;flag indicating a queued action
//  STore A to EnableTimer::ATB,Y
//         lda #$80		;physical/other
//  STore A to MenuData::ActionFlag
//  Store Zero to MenuData::Command
//  Store Zero to MenuData::CurrentChar
//  Store Zero to MenuData::MonsterTargets
//  Store Zero to MenuData::PartyTargets
//  Store Zero to MenuData::SelectedItem
//  Store Zero to MenuData+7
//  Store Zero to MenuData::SecondActionFlag
//  Store Zero to MenuData::SecondCommand
//  Store Zero to MenuData+10
//  Store Zero to MenuData::SecondMonsterTargets
//  Store Zero to MenuData::SecondPartyTargets
//  Store Zero to MenuData::SecondSelectedItem
//  Return To Subroutine
}

// Address: _1C36
// subtracts 1 from item quantity of item in A
// blanks out inventory slot if qty is now 0
static void consumeItem(void) {
    // Transfer A to X
    // lda InventoryQuantities,X
    // dec
    // STore A to InventoryQuantities,X
    // bne Ret
    // STore Zero to InventoryItems,X
    // STore Zero to InventoryTargetting,X
    // lda #$5A
    // STore A to InventoryFlags,X
    // lda #$AA
    // STore A to InventoryUsable,X
    // Return to SubRoutine
}

// Address: _1C51
// Initializes some values when a
// battle during the credits happens
// This range is used by C1 graphics code but
// unsure what it does
static void setupCreditsDemo(void) {
    // lda #$80	;physical/other
    // STore A to MenuData::ActionFlag
    // STore A to MenuData::MonsterTargets
    // lda #$54	;job-specific animation (credits)
    // STore A to MenuData::Command
    // STore Zero to MenuData::PartyTargets
    // STore Zero to MenuData::SelectedItem
    // STore Zero to MenuData::SecondActionFlag
    // STore Zero to MenuData::SecondCommand
    // STore Zero to MenuData::SecondMonsterTargets
    // STore Zero to MenuData::SecondPartyTargets
    // STore Zero to MenuData::SecondSelectedItem
    // Return to SubRoutine
}

// Address: _1C74
// Returns >0 if
// character has a status that
// prevents them from taking Action
static void checkDisablingStatus(void) (
    // ldx AttackerOffset
    // lda CharStruct::Status1,X
    // OR A with CharStruct::AlwaysStatus1,X
    // AND A with #$C2   	;dead/stone/zombie
    // bne Ret
    // lda CharStruct::Status2,X
    // OR A with CharStruct::AlwaysStatus2,X
    // AND A with #$78   	;sleep/para/Charm/Berserk
    // bne Ret
    // lda CharStruct::Status3,X
    // AND A with #$10   	;stop
    // bne Ret
    // lda CharStruct::Status4,X
    // AND A with #$84   	;erased/singing
    // bne Ret
    // Transfer Direct page to aCcumulator
    // Return to SubRoutine
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
//         OR A with #$08   	;berserk
//  STore A to CharStruct::AlwaysStatus2,X
//  Return To Subroutine
}

// Address: _1CB3
// Disables Magic and Commands when
// Status or MP prevents their use
static void disableCommandsMagic(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  STore X to $16
//         lda Void
//  AND A with #$40     	;void
//  Branch to next label if EQuals
//         ldx #$0080
//  STore X to $16		;disables magic
//  [LBL] lda DisplayInfo::CurrentChar
//  Jump to SubRoutine CalculateSpellOffset	;sets Y
//         Lengthen A
//  Transfer Direct page to aCcumulator
//  STore A to $12
//  STore A to $14
//         ldx AttackerOffset
//         lda CharStruct::CurMP,X
//  STore A to $0E		;current mp
//         lda CharStruct::Status3,X
//         OR A with CharStruct::AlwaysStatus3,X
//  STore A to $22		;status 3/4
//         lda CharStruct::Status1,X
//         OR A with CharStruct::AlwaysStatus1,X
//  STore A to $10		;status 1/2
//  AND A with #$0400	;mute
//  Branch to next label if EQuals
//         lda #$0080
//  STore A to $12		;disables magic
//  [LBL] lda CharStruct::Status1,X
//         OR A with CharStruct::AlwaysStatus1,X
//  AND A with #$0020	;toad
//  Branch to next label if EQuals
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
//         OR A with #$0080
//  STore A to CharSpells::Flags,Y
//  BRAnch to NextSpell
// CheckStatus:
//         lda CharSpells::Flags,Y
//  AND A with #$FF7F	;clear bit 80h in flags, disabled bit?
//  STore A to CharSpells::Flags,Y
//         lda CharSpells::ID,Y
//  AND A with #$00FF
//  CoMPare A with #$0080	;blue magic
//         bcs NextSpell
//         lda CharSpells::Flags,Y
//         OR A with $12		;from mute
//         OR A with $14		;from toad
//         OR A with $16		;from void
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
//  INcrement Y
//  INcrement X
//  ComPare X with #$0082	;130 spell slots
//         bne DisableSpells
//  Clear A, then Shorten
//         lda DisplayInfo::CurrentChar
//  STore A to $24
//         lda #$14	;20, size of CharCommands struct
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  STore X to $0E
//         ldy $26
//         Lengthen A
// DisableCommands:
//         lda CharCommands::ID,Y
//  AND A with #$00FF
//  STore A to $12		;commAND A with id
//         beq DisableCommand
//  A Shift Left
//  Transfer A to X
//         lda f:BattleCmdDisableStatus,X
//  AND A with $10		;status 1/2
//         bne DisableCommand
//         lda $12		;commAND A with id
//  CoMPare A with #$0026	;show command
//         beq EnableCommand
//         lda $22		;status 3/4
//  AND A with #$0100	;hidden
//         beq EnableCommand
// DisableCommand:
//         lda CharCommands::Flags,Y
//         OR A with #$0080	;disabled
//  STore A to CharCommands::Flags,Y
//  BRAnch to NextCommand
// EnableCommand:
//         lda CharCommands::Flags,Y
//  AND A with #$FF7F	;enabled
//  STore A to CharCommands::Flags,Y
// NextCommand:
//  INcrement Y
//  INCrement $0E		;character index
//         lda $0E
//  CoMPare A with #$0004	;4 commands per character
//         bne DisableCommands
//  Clear A, then Shorten
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
//  STore X to $3D		;char index, used in subroutines also
//  STore X to $3F		;char offset
// Loop:
//         ldx $3D
//         lda UncontrolledATB,X
//         beq ActionReady
//         ldx $3F
//         lda CharStruct::Status3,X
//  AND A with #$10	;stop
//         bne Next
//         lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
//  AND A with #$60	;sleep/paralyze
//         bne Next
//         ldx $3D
//         dec UncontrolledATB,X
//  BRAnch to Next
// ActionReady:
//         ldx $3F		;char offset
//         lda #$01
//  STore A to CharStruct::CmdCancelled,X
//         lda CharStruct::Status1,X
//         OR A with CharStruct::AlwaysStatus1,X
//  AND A with #$02	;zombie
//  Branch to next label if EQuals
//  Jump to SubRoutine ZombieAction
//  BRAnch to Next
//  [LBL] lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
//  AND A with #$10	;charm
//  Branch to next label if EQuals
//  Jump to SubRoutine CharmAction
//  BRAnch to Next
//  [LBL] lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
//  AND A with #$08	;berserk
//         beq Next
//  Jump to SubRoutine BerserkAction
// Next:
//         ldx $3F		;char offset
//  Jump to SubRoutine NextCharOffset
//  STore X to $3F
//  INCrement a:$003D	;char index ; TODO: dont know why this is being done?
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
    // STore A to CharStruct::ActionFlag,X
    // lda #$05	;fight
    // STore A to CharStruct::Command,X
    // STore Zero to CharStruct::MonsterTargets,X
    // STore Zero to CharStruct::SelectedItem,X
    // STore Zero to CharStruct::SecondActionFlag,X
    // STore Zero to CharStruct::SecondCommand,X
    // STore Zero to CharStruct::SecondMonsterTargets,X
    // STore Zero to CharStruct::SecondPartyTargets,X
    // STore Zero to CharStruct::SecondSelectedItem,X
    // PusH X
    // Transfer Direct page to aCcumulator
    // Transfer A to X
    // lda #$03
    // Jump to SubRoutine Random_X_A  ;0..3
    // Transfer A to X
    // Transfer Direct page to aCcumulator
    // Jump to SubRoutine SetBit_X
    // PulL X
    // STore A to CharStruct::PartyTargets,X	;fight random party member
    // JuMP to QueueUncontrolledAction
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
//         OR A with CharStruct::EnableSpells+1,X	;black AND A with time magic
//         beq Fight
//  Jump to SubRoutine Random_0_99
//  CoMPare A with #$32	;50% chance of spell
//         bcc Magic
// Fight:
//         ldx $3F		;char offset
//         lda #$80
//  STore A to CharStruct::ActionFlag,X
//         lda #$05	;fight
//  STore A to CharStruct::Command,X
//  Store Zero to CharStruct::MonsterTargets,X
//  Store Zero to CharStruct::SelectedItem,X
//  Store Zero to CharStruct::SecondActionFlag,X
//  Store Zero to CharStruct::SecondCommand,X
//  Store Zero to CharStruct::SecondMonsterTargets,X
//  Store Zero to CharStruct::SecondPartyTargets,X
//  Store Zero to CharStruct::SecondSelectedItem,X
//  PusH X
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump to SubRoutine Random_X_A    ;0..3
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  PulL X
//  STore A to CharStruct::PartyTargets,X	;fight random party member
//         JuMP to _QueueUncontrolledAction
// Magic:
//         lda $3D		;char index
//  Transfer A to X
//  STore X to $2A
//         ldx #$028A ; TODO: fixme .sizeof(CharSpells)	;650, size of CharSpells struct
//  STore X to $2C
//  Jump to SubRoutine Multiply_16bit    ;**optimize: use rom table instead
//         ldx $2E
//  STore X to SpellOffsetRandom
//  Store Zero to $0E
// FindAnySpell:		;checks if any spells are learned
//         lda CharSpells::ID+18,X	;starts at first white spell
//  CoMPare A with #$46		;Quick spell
//         beq NextSpell
//  CoMPare A with #$FF		;empty spell slot
//         bne TryRandomSpell
// NextSpell:
//  INcrement X
//  INCrement $0E
//         lda $0E
//  CoMPare A with #$36
//         bne FindAnySpell
//  BRAnch to Fight		;no spells, hit something instead
// TryRandomSpell:
//         ldx #$0012		;first white spell
//         lda #$47		;last time spell
//  Jump to SubRoutine Random_X_A  	;random white/black/time spell
//         Lengthen A
//         adc SpellOffsetRandom
//  Transfer A to X
//  Clear A, then Shorten
//         lda CharSpells::ID,X
//  CoMPare A with #$FF		;empty spell slot
//         beq TryRandomSpell	;keep trying until we hit a known spell
//  CoMPare A with #$46		;quick spell
//         beq TryRandomSpell	;is no good either
//  PusH A 			;holds known random spell
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//         lda f:AttackProp,X
//  STore A to TempTargetting	;temp area
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//  STore Y to $16			;target bits
//         lda TempTargetting
//         bne CheckTargetting
// TargetSelf:
//         Lengthen A
//         lda $3F			;Char Offset
//  Jump to SubRoutine ShiftDivide_128	;char index (could've just loaded that)
//  Transfer A to X
//  Clear A, then Shorten
//  Jump to SubRoutine SetBit_X     	;target self if no targetting info
//  STore A to $16
//  BRAnch to TargetReady
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
//  Jump to SubRoutine Random_X_A	     	;random monster 0..7
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to $17			;monster target
//  BRAnch to TargetReady
// TargetsEnemy:			;normally targets enemy, now targets party
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump to SubRoutine Random_X_A    	;random party 0..3
//  Transfer A to X
//  Transfer Direct page to aCcumulator
//  Jump to SubRoutine SetBit_X
//  STore A to $16			;party target
//  BRAnch to TargetReady
// TargetsAll:
//         lda TempTargetting
//  AND A with #$08		;targets enemy by default
//  Branch to next label if Not Equals
//         lda #$FF
//  STore A to $17
//  BRAnch to TargetReady
//  [LBL] lda #$F0		;target all party members
//  STore A to $16
// TargetReady:
//         ldx $3F			;char Offset
//  PulL A 			;random known spell
//  STore A to CharStruct::SelectedItem,X
//         lda $16			;party targets
//  STore A to CharStruct::PartyTargets,X
//         lda $17			;monster targets
//  STore A to CharStruct::MonsterTargets,X
//         lda #$21		;magic + costs mp
//  STore A to CharStruct::ActionFlag,X
//         lda #$2C		;first magic command
//  STore A to CharStruct::Command,X
//  Store Zero to CharStruct::SecondActionFlag,X
//  Store Zero to CharStruct::SecondCommand,X
//  Store Zero to CharStruct::SecondMonsterTargets,X
//  Store Zero to CharStruct::SecondPartyTargets,X
//  Store Zero to CharStruct::SecondSelectedItem,X
// _QueueUncontrolledAction:
//         JuMP to QueueUncontrolledAction
}

// Address: _1F80
// Params:
// - X = Char Offset
// - $3D = Char index
// Sets up a fight command targetting a
// random party member
static void berserkAction(void) {
    // lda #$80
    // STore A to CharStruct::ActionFlag,X
    // lda #$05	;fight
    // STore A to CharStruct::Command,X
    // STore Zero to CharStruct::PartyTargets,X
    // STore Zero to CharStruct::SelectedItem,X
    // STore Zero to CharStruct::SecondActionFlag,X
    // STore Zero to CharStruct::SecondCommand,X
    // STore Zero to CharStruct::SecondMonsterTargets,X
    // STore Zero to CharStruct::SecondPartyTargets,X
    // STore Zero to CharStruct::SecondSelectedItem,X
    // PusH X
    // Transfer Direct page to aCcumulator
    // Transfer A to X
    // lda #$07
    // Jump to SubRoutine Random_X_A	;0..7 random monster
    // Transfer A to X
    // Transfer Direct page to aCcumulator
    // Jump to SubRoutine SetBit_X
    // PulL X
    // STore A to CharStruct::MonsterTargets,X
    // JuMP to QueueUncontrolledAction
}

// Param $3D = char index
// Sets character's queued action to fire
// on the next ATB tick, and reset their
// uncontrolled ATB for their next turn
static void queueUncontrolledAction(void) {
    //     lda $3D		;char index
    //     Jump to SubRoutine ResetATB   	;also sets Y = timer offset
    //     lda $3D
    //     Transfer A to X
    //     lda CurrentTimer::ATB,Y
    //     cmp #$7F
    //     bcc :+
    //     lda #$7F	;max ATB 127
    // :   STore A to UncontrolledATB,X
    //     lda #$01	;action on next ATB tick
    //     STore A to CurrentTimer::ATB,Y
    //     lda #$41    	;waiting for delayed action
    //     STore A to EnableTimer::ATB,Y
    //     Return to SubRoutine
}

// Address: _1FD2
// Randomizes a table of combatant numbers,
// also initializes global timers
static void randomizeOrder(void) {
//         lda CurrentlyReacting
//  Branch to next label if Not Equals
//  Jump to SubRoutine GlobalTimers
// :	   Transfer Direct page to aCcumulator
//  Transfer A to X
//         dec
//         									;:
//  [LBL] STore A to RandomOrder,X
//  INcrement X
//  ComPare X with #$000C
//  Branch to previous label if Not Equals
//         									;.
//  Transfer Direct page to aCcumulator
//  Transfer A to Y 			;slot for writing
// _RandomizeOrder:
//  Transfer Direct page to aCcumulator
//  Transfer A to X 			;slot for reading
//         lda #$0B
//  Jump to SubRoutine Random_X_A		;0..11
//  STore A to $0E
//         ldx #$0000
//         									;:
// CheckValueInUse:		;see if we've used this number yet
//         lda $0E
//  CoMPare A with RandomOrder,X
//         beq _Next		;already used, try another
//  INcrement X
//  ComPare X with #$000C
//         bne CheckValueInUse
//         									;.
//  STore A to RandomOrder,Y	;if not, save it
//  INcrement Y 			;AND A with select next writing slot
//         									;:
//  _Next:
//  ComPare Y with #$000C		;12 combatant slots
//         bne _RandomizeOrder
//         									;.
//  Return To Subroutine
}

// Address: _200B
// Updates Status/ATB timers for all combatants
// may skip updates depending on stop/etc.
static void updateTimers(void) {
//  Jump to SubRoutine GlobalTimers
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  STore X to $0A     		;char index
// Loop:	tdc
//  Transfer A to Y
//  STore Y to $0C     		;timer index
//         lda $0A
//  Jump to SubRoutine GetTimerOffset
//         tyx 			;X = Timer Offset
//         ldy $0A
//         lda ActiveParticipants,Y
//         beq NextChar
//         lda PauseTimerChecks,Y
//         bne NextChar
//         lda CurrentlyReacting
//  Branch to next label if Not Equals
//         lda QuickTimeFrozen,Y
//         bne NextChar
// :Jump to SubRoutine UpdateTimer 	;first timer is stop
//         lda $08			;check if stop active
//         bne NextChar  		;don't process other timers if stopped
//         ldy #$0008  		;process 8 more status timers
// :Jump to SubRoutine UpdateTimer
//         dey
//  Branch to previous label if Not Equals
//  Jump to SubRoutine UpdateTimer 	;one more status timer (paralyze)
//         lda $08			;check if paralyze active
//         bne NextChar
//  Jump to SubRoutine UpdateTimer  	;advance ATB timer if not paralyzed
// NextChar:
//  INCrement $0A     		;next char index
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
//  Store Zero to $08    	;timer triggered flag
//  PusH Y
//         ldy $0C		;timer index
//         lda ProcessTimer,Y	;should process this timer this tick?
//         beq Finish
//  ComPare Y with #$000A	;ProcessTimer::ATB
//  Branch to next label if EQuals
//         lda CurrentlyReacting
//         bne Finish
//  [LBL] lda EnableTimer,X	;is it enabled?
//         beq Finish
//         bmi TimerActive  	;check the 80h timer flag
//         lda CurrentTimer,X
//         beq FlagTimer
//         dec CurrentTimer,X
//         lda CurrentTimer,X
//         bne TimerActive
// FlagTimer:		;flag EnableTimer when CurrentTimer hits 0
//         lda EnableTimer,X
//         OR A with #$81
//  STore A to EnableTimer,X
// TimerActive:
//         lda $0C
//  Branch to next label if Not Equals		;doesn't branch anywhere regardless
// :INCrement $08    	;timer triggered flag
// Finish:
//  PulL Y 		;restore original Y
//  INcrement X 		;next timer (in offset)
//  INCrement $0C		;next timer index
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
//  Store Zero to ProcessTimer,X
//  BRAnch to :+
// Triggered:
//         lda #$01
//  STore A to ProcessTimer,X		;flag timer for processing
//         lda f:TimerDurTbl,X		;reset timer from rom
//  STore A to GlobalTimer,X
//         							;:
//  [LBL] INcrement X
//  ComPare X with #$000B			;11 timers
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
//  STore X to $08			;timer index
//  Transfer A to Y
//  [LBL] STore A to TimerEnded,Y
//  INcrement Y
//  ComPare Y with #$000B
//  Branch to previous label if Not Equals
// TimerLoop:	;for each timer, loop finds the first character for whom that timer ended, checking in a "random" order
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  STore X to $0A			;char count
//         ldx $08			;timer index
//         lda RandomOrderIndex,X
//  PusH A 			;original RandomOrderIndex
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
//  Branch to next label if Not Equals
//         lda QuickTimeFrozen,X
//         bne NextChar
//  [LBL] lda $0C			;char index
//  Jump to SubRoutine GetTimerOffset      ;Y = Timer Offset
//  Transfer Y to A
//  CLear Carry
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
//  PusH X 		;timer offset + index
//         ldx $08
//         lda RandomOrderIndex,X
//  Transfer A to X
//         lda RandomOrder,X
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_128
//  Transfer A to X
//  Clear A, then Shorten
//         lda CharStruct::Status4,X
//  AND A with #$81	;erased or hidden
//         bne NextCharPLX
//         lda CharStruct::CmdStatus,X
//  AND A with #$10	;jumping
//         beq EndTimerPLX
// NextCharPLX:
//  PulL X
//  BRAnch to NextChar
// EndTimerPLX:
//  PulL X 		;timer offset + index
// EndTimer:		;sets flag that timer has ended, so effects can be applied later
//  PulL A
//         lda EnableTimer,X
//  AND A with #$7E	;clear $81
//  STore A to EnableTimer,X
//         ldx $08		;timer index
//  PusH X
//         lda #$01	;flag that we found someone timer ended for
//  STore A to TimerEnded,X
//         lda RandomOrderIndex,X
//  Transfer A to X
//         lda RandomOrder,X
//  PulL X 		;timer index
//  STore A to TimerReadyChar,X	;which character had their timer end
//  BRAnch to NextTimer	;don't check any more characters for this timer
// NextChar:	;this character's timer didn't end or isn't eligable,
//         	;keep looking until all have been checked or one is found
//         ldx $08		;timer index
//  INCrement RandomOrderIndex,X
//         lda RandomOrderIndex,X
//  CoMPare A with #$0C	;reset index at 12
//  Branch to next label if Not Equals
//  Store Zero to RandomOrderIndex,X
// :INCrement $0A        	;char count
//         lda $0A
//  CoMPare A with #$0C	;12 chars
//  Branch to next label if EQuals
//         JuMP to CharLoop
// :PulL A 		;original RandomOrderIndex
//  STore A to RandomOrderIndex,X
// NextTimer:
//  INCrement $08        	;next timer index
//         lda $08
//  CoMPare A with #$0B	;11 timers
//  Branch to [Ret] if EQuals
//         JuMP to TimerLoop
// [Ret] Return To Subroutine
}

static void applyTimerEffects(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  STore X to ProcessingTimer
// Loop:
//         ldx ProcessingTimer
//         lda TimerEnded,X
//         beq NextTimer
//  INCrement RandomOrderIndex,X
//         lda RandomOrderIndex,X
//  CoMPare A with #$0C		;12 chars
//  Branch to next label if Not Equals
//  Store Zero to RandomOrderIndex,X
// :	    lda TimerReadyChar,X
//  Jump to SubRoutine GetTimerOffset    	;sets Y to timer offset
//         lda TimerReadyChar,X
//  Jump to SubRoutine CalculateCharOffset
//         lda ProcessingTimer
//         beq TimerEffect    	;timer 0 is stop, skips below check
//         lda EnableTimer,Y	;bits 80h AND A with 01 are cleared prev
//         bne NextTimer    	;skip effect if any other bits set
// TimerEffect:
//  Jump to SubRoutine DispatchTimerEffect
// NextTimer:
//  INCrement ProcessingTimer
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
    // A Shift Left
    // Transfer A to X
    // lda f:TimerEffectJumpTable,X
    // STore A to $08
    // lda f:TimerEffectJumpTable+1,X
    // STore A to $09
    // lda #$c2 ; Load from bank C2
    // STore A to $0A
    // jml [$0008]

    // TimerEffectJumpTable
    // .word $21E3, $21EE, $222A, $2235, $224E, $2259, $2264, $22AD, $2319, $237C, $238F
}

// Address: _21E3
static void timerEffectStop(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status3,X
    // AND A with #$EF	;clear stop
    // STore A to CharStruct::Status3,X
    // Return to SubRoutine
}

// Address: _21EE
static void timerEffectPoison(void) {
//         lda #$01
//  STore A to EnableTimer::Poison,Y
//         lda InitialTimer::Poison,Y
//  STore A to CurrentTimer::Poison,Y
//  Jump to SubRoutine WipeDisplayStructures
//         Lengthen A
//         ldx AttackerOffset
//         lda CharStruct::MaxHP,X
//  Jump to SubRoutine ShiftDivide_16
//  Branch to next label if Not Equals
//  INCrement 				;min 1 damage
//  [LBL] STore A to $0E				;poison tick damage
//  SEt Carry flag
//         lda CharStruct::CurHP,X
//         sbc $0E				;poison tick damage
//  Branch to next label if Carry Set
//  Transfer Direct page to aCcumulator 				;min 0 hp
//  [LBL] STore A to CharStruct::CurHP,X
//  Clear A, then Shorten
//         lda TimerReadyChar::Poison
//         ldx $0E				;poison tick damage
//  STore X to TempDisplayDamage
//  Jump to SubRoutine CopyDisplayDamage
//         lda #$09	;C1 routine: display regen/poison damage
//         JuMP to CallC1
}

static void timerEffectReflect(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status3,X
    // AND A with #$7F	;clear reflect
    // STore A to CharStruct::Status3,X
    // Return to SubRoutine
}

static void timerEffectCountdown(void) {
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//  AND A with #$02	;zombie
//         bne Ret
//         lda TimerReadyChar::Countdown
//  Jump to SubRoutine KillCharacter
//         lda MonsterDead
//  Branch to [Ret] if EQuals
//         lda #$07	;C1 routine: condemn death animation
//  Jump to SubRoutine CallC1
// Ret:	   Return to SubRoutine
}

static void timerEffectMute(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status2,X
    // AND A with #$FB	;clear mute
    // STore A to CharStruct::Status2,X
    // Return to SubRoutine
}

static void timerEffectHPLeak(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status4,X
    // AND A with #$F7	;clear hp leak
    // STore A to CharStruct::Status4,X
    // Return to SubRoutine
}

static void timerEffectOld(void) {
//         lda #$01
//  STore A to EnableTimer::Old,Y
//         lda InitialTimer::Old,Y
//  STore A to CurrentTimer::Old,Y
//         ldx AttackerOffset
//  Store Zero to $0E
// StatsLoop:		;applies to all 4 main stats
//         lda CharStruct::BaseStr,X
//         dec
//  Branch to next label if EQuals		;**bug: wraps 0 stats to 255
//  STore A to CharStruct::BaseStr,X
//  [LBL] lda CharStruct::EquippedStr,X
//         dec
//  Branch to next label if EQuals
//  STore A to CharStruct::EquippedStr,X
//  [LBL] INcrement X
//  INCrement $0E
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
//  Branch to next label if EQuals
//  STore A to CharStruct::Level,X
//  [LBL] lda CharStruct::MonsterAttack,X
//         dec
//         bpl Ret	;bug? only decreases attack if above 128
//  STore A to CharStruct::MonsterAttack,X
// [Ret] Return To Subroutine
}

static void timerEffectRegen(void) {
//         lda #$01
//  STore A to EnableTimer::Regen,Y
//         lda InitialTimer::Regen,Y
//  CoMPare A with #$1E
//  Branch to next label if Carry Set
//         lda #$1E	;max 30 ticks if it was slower
//  STore A to InitialTimer::Regen,Y
//  [LBL] STore A to CurrentTimer::Regen,Y
//  Jump to SubRoutine WipeDisplayStructures
//         ldx AttackerOffset
//  Jump to SubRoutine CopyStatsWithBonuses
//         lda Level
//  STore A to $24
//         lda Vitality
//  STore A to $25
//  Jump to SubRoutine Multiply_8bit
//         ldx AttackerOffset
//         lda CharStruct::Status1,X
//  AND A with #$02	;zombie
//         bne Ret
//         Lengthen A
//         lda $26
//  Jump to SubRoutine ShiftDivide_16
//  Transfer A to X
//  Branch to next label if Not Equals
//  INCrement 		;min 1
//  [LBL] STore A to $0E
//         ldx AttackerOffset
//  CLear Carry
//         adc CharStruct::CurHP,X
//  Branch to next label if Carry Set
//  CoMPare A with CharStruct::MaxHP,X
//  Branch to next label if Carry Clear+
//  [LBL] lda CharStruct::MaxHP,X	;cap at maxhp
//  [LBL] STore A to CharStruct::CurHP,X
//  Clear A, then Shorten
//         lda $0F
//         OR A with #$80       		;flag to display as healing
//  STore A to $0F
//         lda TimerReadyChar::Regen
//         ldx $0E
//  STore X to TempDisplayDamage
//  Jump to SubRoutine CopyDisplayDamage
//         lda #$09	;C1 routine: display regen/poison damage
//  Jump to SubRoutine CallC1
// [Ret] Return To Subroutine
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
//  Branch to [Ret] if EQuals
// FindSong:		;Y = song stat index
//  A Shift Left
//  Branch to next label if Carry Set
//  INcrement Y
//  BRAnch to FindSong
// :STore Y to $12		;song stat index
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  STore X to $0E		;target
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
//  STore X to $14		;char offset
//         Lengthen A
// Transfer X to A
//  CLear Carry
//         adc $12		;adjust offset by song stat
//  Transfer A to X
//  Clear A, then Shorten
// CharLoop:
//         ldy $0E		;target
//         lda ActiveParticipants,Y
//         beq Next
//  CLear Carry
//         lda CharStruct::BonusStr,X	;different stats depending on X
//  INCrement
//  CoMPare A with #$64	;don't apply changes at 100 AND A with up
//         bcs Next
//  STore A to CharStruct::BonusStr,X
// Next:
//  Jump to SubRoutine NextCharOffset
//  STore X to $14		;char offset
//  INCrement $0E		;next target
//         lda $0E
//  CoMPare A with $10		;last target +1
//         bne CharLoop
// [Ret] Return To Subroutine
}

static void timerEffectParalyze(void) {
    // ldx AttackerOffset
    // lda CharStruct::Status2,X
    // AND A with #$DF	;clear paralyze
    // STore A to CharStruct::Status2,X
    // ldx ProcessingTimer
    // lda TimerReadyChar,X
    // JuMP to ResetATB
}

static void timerEffectATB(void) {
//  Jump to SubRoutine CheckBattleEnd
//         lda BattleOver
//         bne GoRet
//         lda TimerReadyChar::ATB
//  STore A to AttackerIndex
//  Jump to SubRoutine GetTimerOffset
//         tyx
//         lda EnableTimer::Paralyze,X
//         bne GoRet
//         lda EnableTimer::ATB,X
//  Branch to next label if EQuals
//         JuMP to PerformAction      	;action is ready, do it
//  [LBL] lda TimerReadyChar::ATB
//  CoMPare A with #$04	;monster check
//         bcs Monster
//  Transfer Direct page to aCcumulator
//  Transfer A to X
// SearchTurnQueue:	;find character in turn queue
//         lda ATBReadyQueue,X
//  CoMPare A with TimerReadyChar::ATB
//         beq GoRet	;character already in turn queue
//  INcrement X
//  ComPare X with #$0004
//         bne SearchTurnQueue
//         lda TimerReadyChar::ATB
//  Jump to SubRoutine CheckDisablingStatus
//         bne GoRet
//         ldx ATBReadyCount
//         lda TimerReadyChar::ATB
//  STore A to ATBReadyQueue,X
//  INCrement ATBReadyCount
// GoRet:	jmp Ret
// Monster:
//  Jump to SubRoutine MonsterATB
// [Ret] Return To Subroutine
}

// Called when character's turn is up,
// perform their queued action
static void performAction(void) {
//  Jump to SubRoutine ProcessTurn
//         lda DelayedFight
//         bne Ret
//         lda AttackerIndex
//  CoMPare A with #$04	;monster check
//         bcs _ResetATB
//         ldx AttackerOffset
//         lda CharStruct::CmdStatus,X
//  AND A with #$E0	;clear many flags (jump/flirt/others?)
//  STore A to CharStruct::CmdStatus,X
//  Store Zero to CharStruct::DamageMod,X
//         lda CharStruct::Status1,X
//         OR A with CharStruct::AlwaysStatus1,X
//  AND A with #$02	;zombie
//         bne Uncontrolled
//         lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
//  AND A with #$18	;charm/berserk
//         beq _ResetATB
// Uncontrolled:
//         lda AttackerIndex
//  Jump to SubRoutine GetTimerOffset
//  Transfer Direct page to aCcumulator
//  STore A to EnableTimer::ATB,Y
//  INCrement
//  STore A to CurrentTimer::ATB,Y
//         lda AttackerIndex
//  Transfer A to X
//         lda UncontrolledATB,X
//  AND A with #$7F	;max 127
//  STore A to UncontrolledATB,X
// _ResetATB:
//  INCrement CheckQuick
//         lda AttackerIndex
//  Jump to SubRoutine ResetATB
//  Store Zero to CheckQuick
// [Ret] Return To Subroutine
}

// Waits when a character's turn arrives
// (amount depending on battle speed setting)
static void atbWait(void) {
//         lda ATBWaiting
//  Branch to [Ret] if EQuals
//         lda ATBWaitLeft
//         beq DoneWaiting
//         dec
//  STore A to ATBWaitLeft
//         bne Ret
// DoneWaiting:
//  Transfer Direct page to aCcumulator
//  STore A to ATBWaiting
// [Ret] Return To Subroutine
}

// Updates ATB for all combatants and
// sets them active if present
static void resetAtbAll(void) {
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//  Transfer A to Y
//  STore X to $0E			;char index
// ResetATBLoop:
//         lda $0E
//  Jump to SubRoutine ResetATB
//         lda $0E
//  Jump to SubRoutine CalculateCharOffset
//         lda $0E
//  CoMPare A with #$04		;monster check
//         bcs Monster
//         ldx AttackerOffset
//         lda CharStruct::CharRow,X
//  AND A with #$40		;not present
//         beq SetActive
//         bne Next
// Monster:
//  SEt Carry flag
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
//  INCrement $0E			;char index
//         lda $0E
//  CoMPare A with #$0C		;12 participants
//         bne ResetATBLoop
//         									;.
//  Return To Subroutine
}

// Initialize ATB (A: character index 0-12)
static void resetAtb(void) {
//  PusH A
//  Jump to SubRoutine GetTimerOffset	;Y AND A with $36 = timer offset
//  PulL A
//  Jump to SubRoutine CalculateCharOffset
//  Jump to SubRoutine CopyStatsWithBonuses
//         lda CharStruct::EqWeight,X
//  Jump to SubRoutine ShiftDivide_8	;weight/8
//  CLear Carry
//         adc #$78     		;+120
//  SEt Carry flag
//         sbc Agility    	;-agi
//  Branch to next label if EQuals
//  Branch to next label if Carry Set+
//  [LBL] lda #$01     		;min 1
// :Jump to SubRoutine HasteSlowMod
//  STore A to CurrentTimer::ATB,Y
//         lda EncounterInfo::IntroFX
//         bpl NotCredits		;80h indicates a credits demo battle
//         ldx AttackerOffset
//  ComPare X with #$0200		;monster
//         bcs CreditsMonster
//         lda #$01		;party member gets turn immediately
//  BRAnch to CreditsParty
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
//  PusH Y
//  Jump to SubRoutine ClearQuick
//  PulL Y
//  BRAnch to EnableATB
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

//  [LBL] STore Zero to QuickTimeFrozen,X
//  INcrement X
//  ComPare X with #$000C		;12 combatants
//  Branch to previous label if Not Equals
//  Return To Subroutine
}

// Stop Timer (X: #timer; A: Target index 0-12)
static void stopTimer(void) {
    // PusH X
    // Jump to SubRoutine GetTimerOffset
    // PulL X
    // Jump to SubRoutine AddTimerOffsetY
    // Transfer Direct page to aCcumulator
    // STore A to EnableTimer,Y
    // Return to SubRoutine
}

// Start Timer (X: #timer; A: Participant index)
static void startTimer(void) {
    // PusH X
    // PusH A
    // Jump to SubRoutine GetTimerOffset
    // PulL A
    // Jump to SubRoutine CalculateCharOffset
    // Jump to SubRoutine CopyStatsWithBonuses
    // PulL X
    // Jump to SubRoutine GetTimerDuration	;also sets up Y
    // ldx AttackerOffset	;not actually attacker, in this case
    // Jump to SubRoutine HasteSlowMod
    // STore A to CurrentTimer,Y
    // STore A to InitialTimer,Y
    // lda #$01
    // STore A to EnableTimer,Y
    // STore Zero to StatusFixedDur
    // Return to SubRoutine
}

// Get Timer Duration (X - #timer; $3ED7 - IsItem):
// A = return duration
// sets up and jumps to a jump table entry that
// sets the correct duration
// also sets up Y as the correct timer offset
static void getTimerDuration(void) {
    // Jump to SubRoutine AddTimerOffsetY      (Y = X + TimerOffset)
    // Transfer X to A
    // A Shift Left
    // CLear Carry flag
    // ADd StatusFixedDur to A with Carry    (uses alternate fixed status duration)
    // A Shift Left
    // Transfer A to X
    // LoaD f:TimerDurationJumpTable,X to A
    // STore A to $08
    // LoaD f:TimerDurationJumpTable+1,X to A
    // STore A to $09
    // LoaD #$c2 to A (.b #bank(TimerDurationJumpTable))
    // STore A to $0A
    // JuMP to [$0008]		(jump to table address)

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
    // Transfer X to A
    // Lengthen A
    // CLear Carry flag
    // ADd TimerOffset to A with Carry
    // Transfer A to Y
    // Clear A, then Shorten
    // Return to SubRoutine
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
    // ADd A with #$14 (#20) AND A with Carry
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
//  [LBL] lda #$1E	;min 30
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
//  SEt Carry flag
//         lda AttackerIndex
//         sbc #$04
//  STore A to MonsterIndex
//  Jump to SubRoutine ShiftMultiply_16
//  Transfer A to X
//  STore X to MonsterOffset16
//  A Shift Left
//  Transfer A to X
//  STore X to MonsterOffset32
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//  STore Y to TempCharm
//         ldx MonsterOffset16
//         lda #$FF
//  [LBL] STore A to MonsterMagic,X
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0010	;init 16 byte monster magic struct
//  Branch to previous label if Not Equals
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
//  [LBL] STore A to MonsterAIScript,X
//  INcrement X
//  INcrement Y
//  ComPare Y with #$0064	;init 100 bytes to $FF
//  Branch to previous label if Not Equals
//         lda AttackerIndex
//  Jump to SubRoutine CalculateCharOffset
//         ldx AttackerOffset
//         lda #$2C       	;magic
//  STore A to CharStruct::Command,X
//         lda #$21	;magic + costs mp
//  STore A to CharStruct::ActionFlag,X
//         ldx AttackerOffset
//         lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
//  AND A with #$08	;berserk
//         beq CheckCharm
//         lda #$01
//  STore A to CharStruct::CmdCancelled,X
//         lda #$80	;monster fight
//  STore A to AIBuffer
//         lda #$FF	;end of list
//  STore A to AIBuffer+1
//  Jump to SubRoutine DispatchAICommands
//         JuMP to GoFinish
// CheckCharm:
//         lda CharStruct::Status2,X
//         OR A with CharStruct::AlwaysStatus2,X
//  AND A with #$10	;charm
//         beq CheckFlirt
// TryRandomAction:
//         ldx AttackerOffset
//         lda #$01
//  STore A to CharStruct::CmdCancelled,X
//  Transfer Direct page to aCcumulator
//  Transfer A to X
//         lda #$03
//  Jump to SubRoutine Random_X_A 	;0..3
//  Transfer A to X
//  STore X to $0E
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to X
//         Lengthen A
//         lda BattleMonsterID,X
//  Jump to SubRoutine ShiftMultiply_4
//  CLear Carry
//         adc $0E		;random number 0..3
//  Transfer A to X 		;offset into control actions table
//  Clear A, then Shorten
//         lda f:MonsterControl,X
//  CoMPare A with #$FF
//         beq TryRandomAction	;no action in this slot, try again
//  STore A to AIBuffer
//         lda #$FF	;end of list
//  STore A to AIBuffer+1
//  INCrement TempCharm
//  Jump to SubRoutine DispatchAICommands
//  BRAnch to GoFinish
// CheckFlirt:								;
//         lda CharStruct::CmdStatus,X
//  AND A with #$08	;flirt
//         beq CheckControl
//         lda #$51	;throbbing command
//  STore A to CharStruct::Command,X
//         lda #$80	;other
//  STore A to CharStruct::ActionFlag,X
//  BRAnch to GoFinish
// CheckControl:
//         lda CharStruct::Status4,X
//  AND A with #$20	;control
//         bne Control
//         lda CharStruct::Status2,X
//  AND A with #$40	;sleep
//         bne Sleep
//  BRAnch to Normal
// Control:
//  Transfer Direct page to aCcumulator
//  Transfer A to Y
//  [LBL] lda ControlTarget,Y
//  CoMPare A with AttackerIndex
//         beq FoundController
//  INcrement Y
//  BRAnch to :-
// FoundController:
//         lda ControlCommand,Y
//         bne _ControlCommand
// Sleep:	;or controlled without a command
//  Store Zero to CharStruct::Command,X
//         lda #$80	;action complete?
//  STore A to CharStruct::ActionFlag,X
//  BRAnch to GoFinish
// _ControlCommand:
//  Transfer Direct page to aCcumulator
//  STore A to ControlCommand,Y
//         lda MonsterIndex
//  Transfer A to X
//         lda MonsterControlActions,X
//  STore A to AIBuffer
//         lda #$FF	;end of list
//  STore A to AIBuffer+1
//  Jump to SubRoutine DispatchAICommands
// GoFinish:
//         JuMP to Finish
// Normal:
//         lda MonsterIndex
//  Transfer A to X
//         lda AIActiveConditionSet,X
//  STore A to AICurrentActiveCondSet
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to X
//         Lengthen A
//  CLear Carry
//         lda f:_d0eea5,X	;*1620, size of MonsterAI struct
//         adc #MonsterAI
//  STore A to AIOffset
//  Clear A, then Shorten
//  Store Zero to AICurrentCheckedSet
// CheckAIConditions:
//         lda AICurrentCheckedSet
//  Transfer A to X
//         lda f:_d0eec9,X	;size of a MonsterAI condition
//  Transfer A to Y
//  STore Y to AIConditionOffset
//  Store Zero to AICheckIndex
// CheckSingleCondition:
//         ldy AIConditionOffset
//         lda (AIOffset),Y
//         beq AIActions		;0 always succeeds
//  CoMPare A with #$FE		;indicates end of condition set
//         beq AIActions
//  Jump to SubRoutine CheckAICondition
//         lda AIConditionMet
//         beq NextConditionSet
//         Lengthen A
//  CLear Carry
//         lda AIConditionOffset
//         adc #$0004		;next condition in set
//  STore A to AIConditionOffset
//  Clear A, then Shorten
//  INCrement AICheckIndex
//  BRAnch to CheckSingleCondition
// NextConditionSet:	;failed a condition in this set, check next set of conditions
//  INCrement AICurrentCheckedSet
//         lda AICurrentCheckedSet
//  CoMPare A with #$0A		;10 conditions max
//         bne CheckAIConditions
// AIActions:
//         Lengthen A
//  CLear Carry
//         lda AIOffset
//         adc #$00AA	;advances from Conditions to Actions
//  STore A to AIOffset
//  Clear A, then Shorten
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
//  Jump to SubRoutine ProcessAIScript
// Finish:
//         ldx MonsterOffset16
//         lda MonsterMagic,X
//         Lengthen A
//  Jump to SubRoutine ShiftMultiply_8
//  Transfer A to X
//  Clear A, then Shorten
//         lda f:AttackProp,X
//  AND A with #$03       	;delay values
//  Transfer A to X
//         lda f:AttackDelayTbl,X
//  PusH A
//         lda AttackerIndex
//  Jump to SubRoutine GetTimerOffset
//  PulL A
//  STore A to CurrentTimer::ATB,Y    ;**bug? doesn't adjust for haste/slow
//         lda #$41	;pending action
//  STore A to EnableTimer::ATB,Y
//         lda MonsterIndex
//  A Shift Left
//  Transfer A to X
//  Store Zero to ForcedTarget::Party,X
//  Store Zero to ForcedTarget::Monster,X
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
    //  Jump to SubRoutine [CountSetBits]
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
    //  Jump to SubRoutine CountSetBits
    //  DEcrement X 		(targets -1)
    //  Branch to [Fail] if MInus	(fail for 0 targets)
    //  JuMP to CheckInvert

    //  [Reaction2] LoaD AttackerOffset to X
    //  LoaD CharStruct::Reaction2Targets,X to A
    //  Jump to SubRoutine CountSetBits
    //  DEcrement X 		(targets -1)
    //  Branch to [Fail] if MInus	(fail for 0 targets)
    //  Jump to SubRoutine CheckInvert

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
    //  LoaD AIParam1 to A
    //  Jump to SubRoutine GetAITarget	(populates list of targets to check)
    //  LoaD AIParam2 to A
    //  Transfer A to X
    //  STore X to $0E		(Offset within CharStruct)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [Loop] Lengthen A
    //  LoaD AITargetOffsets,Y to A
    //  CoMPare A with #$FFFF	(end of list or no target found)
    //  Branch to [TargetFound] if Not Equals
    //  Clear A, then Shorten
    //  BRAnch to [Finish]

    //  [TargetFound] CLear Carry
    //  ADd $0E to A with Carry		(Offset within CharStruct)
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD CharStruct::CharRow,X to A	(check any single CharStruct byte)
    //  CoMPare A with AIParam3		(compare with provided value)
    //  Branch to next if Not Equal
    //  INCrement AIConditionMet

    //  [LBL] INcrement Y by 2
    //  ComPare Y with #$0018	(12 characters * 2 bytes)
    //  Branch to [Loop] if Not Equals

    //  [Finish]			(fail if any targets failed)
    //  LoaD AIMultiTarget to A
    //  Branch to [Ret] if EQuals
    //  LoaD AITargetCount to A
    //  CoMPare A with AIConditionMet
    //  Branch to [Ret] if EQuals
    //  Store Zero to AIConditionMet
    //  [Ret] Return To Subroutine
}

// Address: _2B19
// AI Condition $0C: Compare with value at $A2?
// Param2/3: 16 bit Value to compare, succeeds if >= value at $A2
static void aiCondition0C(void) {
    // Lengthen A
    // LoaD a:$00A2 to A (something from C1 bank code, TODO: why must this be done?)
    // CoMPare A with AIParam2
    // Branch to next label if Clear Carry
    // INCrement AIConditionMet
    // [LBL] Transfer Direct page to aCcumulator
    // Shorten A
    // Return to Subroutine
}

// Address: _2B2A
// AI Condition $0D: Check Event Flags
// Param2: Event Flag # (0-15)
// Param3: Value (bitmask)
// There's a special case for Event Flag 03
static void aiCondition0D(void) {
    // LoaD AIParam2 to A
    // Transfer A to X
    // CoMPare A with #$03 (special case)
    // Branch to [CheckEventFlags] if Not Equals (otherwise just compares flag bits)
    // STore Zero to $0E
    // Transfer Direct page to aCcumulator
    // Transfer A to X
    // Transfer A to Y

    // [PartyLoop] LoaD BattleData::EventFlags+3 to A
    // Jump to SubRoutine SelectBit_X
    // Branch to [Next] if EQuals (if flag bit not set, skip this party slot)
    // PusH X
    // LoaD CharStruct::CharRow,Y to A
    // AND A with #$07 (char id)
    // Transfer A to X
    // LoaD $0E to A
    // Jump to SubRoutine SetBit_X (otherwise, set bit corresponding with char)
    // STore A to $0E
    // PulL X

    // [Next] Lengthen A
    // Transfer Y to A
    // CLear Carry
    // ADd #$0080 to A with Carry (next CharStruct Offset)
    // Transfer A to Y
    // Clear and Shorten A
    // INcerment X
    // ComPare X with #$0004 (4 party slots)
    // Branch to [PartyLoop] if Not Equals
    // LoaD $0E to A (bits set for party chars matching flag slots)
    // BRAnch to [CheckMatch]

    // [CheckEventFlags] LoaD BattleData::EventFlags,X to A

    // [CheckMatch] AND A with AIParam3
    // Branch to [Ret] if EQuals
    // INCrement AIConditionMet

    // [RET] Return To Subroutine
}

// Address: _2B6F
// Reaction to Damage
static void aiCondition0E(void) {
    // LoaD ReactionFlags to A
    // AND A with #$01 (check second set of reactions)
    // Branch to [Reaction2] if Not Equals
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Reaction1Damage,X to A
    // Branch to [Met] if Not Equals
    // Return To Subroutine

    // [Reaction2] **bug: didn't load X for this path, but fortunately it's always? correct already
    // LoaD CharStruct::Reaction2Damage,X to A
    // Branch to [Fail] if EQuals

    // [Met] INCrement AIConditionMet

    // [Fail] Return To Subroutine
}

// Address: _2B87
// Sets flag to skip dead monster checks (Always Succeeds)
static void aiCondition0F(void) {
    // STore Zero to $4751
    // LoaD #$01 to A
    // STore A to AISkipDeadCheck
    // STore A to AIConditionMet
    // Return to Subroutine
}

// Address: _2B93
// One party member alive
static void aiCondition10(void) {
    // Transfer Direct page to aCcumulator
    // Transfer A to X
    // Transfer A to Y
    // STore Y to $0E

    // [PartyLoop] (count number of active party members)
    // LoaD ActiveParticipants,Y to A
    // Branch to [Next] if EQuals
    // LoaD CharStruct::Status1,X to A
    // AND A with #$C2 (Dead, Stone or Zombie)
    // Branch to [Next] if Not Equals
    // LoaD CharStruct::CurHP,X to A
    // OR A with CharStruct::CurHP+1,X
    // Branch to [Next] if EQuals
    // INCrement $0E (count of active characters)

    // [Next] Jump to SubRoutine NextCharOffset
    // INCrement Y
    // ComPare Y with #$0004 (4 party memebrs)
    // Branch to [PartyLoop] if Not Equals
    // LoaD $0E to A
    // DECrement A
    // Branch to [Fail] if Not Equals (>1 party member active)
    // INCrement AIConditionMet

    // [Fail] Return To Subroutine
}

// Address: _2BC0
// Reaction to Summon
static void aiCondition11(void) {
    // LoaD ReactionFlags to A
    // AND A with #$01 (check second set of reactions)
    // Branch to [Reaction2] if Not Equals
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Reaction1Command,X to A
    // CoMPare A with #$2B (magic)
    // Branch to next if EQuals
    // CoMPare A with #$17 (conjure)
    // Branch to [Fail] if Not Equals

    // [LBL] LoaD CharStruct::Reaction1Magic,X to A
    // CoMPare A with #$48 (first summon spell)
    // Branch to [Fail] if Carry Clear
    // CoMPare A with #$57 (past last summon spell)
    // Branch to [Fail] if Carry Set
    // BRAnch to [Met]

    // [Reaction2] LoaD AttackerOffset to X
    // LoaD CharStruct::Reaction2Command,X to A
    // CoMPare A with #$2B (magic)
    // Branch to next if EQuals
    // CoMPare A with #$17 (conjure)
    // Branch to [Fail] if Not Equals

    // [LBL] LoaD CharStruct::Reaction2Magic,X to A
    // CoMPare A with #$48 (first summon spell)
    // Branch to [Fail] if Carry Clear
    // CoMPare A with #$57 (past last summon spell)
    // Branch to [Fail] if Carry Set

    // [Met] INCrement AIConditionMet

    // [Fail] Return To Subroutine
}

// Address: _2BFD
// No Female targets available
static void aiCondition12(void) {
    // Transfer Dire page to aCcumulator
    // Transfer A to X
    // Transfer A to Y

    // [PartyLoop] LoaD CharStruct::CharRow,X to A
    // AND A with #$08 (gender)
    // Branch to [Next] if EQuals
    // LoaD ActiveParticipants,Y to A
    // Branch to [Next] if EQuals
    // LoaD CharStruct::Status4,X to A
    // AND A with #$81 (erased or hidden)
    // Branch to [Next] if Not Equals
    // LoaD CharStruct::CmdStatus,X to A
    // AND A with #$10 (jumping)
    // Branch to [Fail] if EQuals (girl available, fail condition)

    // [Next] Jump to SubRoutine NextCharOffset
    // INcement Y
    // ComPare Y with #$0004
    // Branch to [PartyLoop] if Not Equals
    // INCrement AIConditionMet

    // [Fail] Return to SubRoutine
}