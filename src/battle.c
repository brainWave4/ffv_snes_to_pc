// Bank Range: C2/0000 - C2/9FFF
#include <stdint.h>

#include "battle.h"

// for ExecBtlGfx_ext
#include "btlgfx.h"

// for ExecSound_ext
#include "sound.h"

// TODO: import RNGTbl (from field), AttackMessageTbl

// FUNCTION DECLARATIONS
static void setupRegisters(void); // Incomplete
static uint8_t getRandBetween(uint8_t min, uint8_t max); // Unfinished
static void wipeDisplayStructures(void); // Incomplete
static void copyStatsWithBonuses(void); // Incomplete
static void copyDisplayDamage(void); // Incomplete
static void wipeActionData(void); // Incomplete
static uint8_t getRandom0_99(void); // Incomplete
static uint16_t getTargetBitmask(void); // Incomplete
static void checkMultiTarget(void); // Incomplete
static void removeInactiveTargets(void); // Incomplete
static void copyRomMagicInfo(void); // Incomplete
static void nextMessageBoxSet(void); // Incomplete
static void getItemsUsableY(void); // Incomplete
static void setupInventoryInfo(void); // Incomplete
static void applyPercentage(void); // Incomplete

static void noActionAbility(void); // Incomplete
static void commandTable00(void); // Incomplete
static void itemCommand(void); // Incomplete
static void weaponItem(void); // Incomplete
static void prepMagicLamp(void); // Incomplete
static void commandTable02(void); // Incomplete
static void commandTable03(void); // Incomplete
static void commandTable05(void); // Incomplete
static void commandTable06(void); // Incomplete
static void commandTable07(void); // Incomplete
static void simpleFight(void); // Incomplete
static void commandTable08(void); // Incomplete
static void commandTable09(void); // Incomplete
static void commandTable0A(void); // Incomplete
static void commandTable0B(void); // Incomplete
static void commandTable0C(void); // Incomplete
static void commandTable2D(void); // Incomplete
static void commandTable2E(void); // Incomplete
static void commandTable0D(void); // Incomplete
static void commandTable0E(void); // Incomplete
static void commandTable0F(void); // Incomplete
static void commandTable10(void); // Incomplete
static void swordSlapCommand(void); // Incomplete
static void commandTable12(void); // Incomplete
static void commandTable13(void); // Incomplete
static void commandTable14(void); // Incomplete
static void commandTable15(void); // Incomplete
static void commandTable16(void); // Incomplete
static void commandTable18(void); // Incomplete
static void commandTable19(void); // Incomplete
static void commandTable17(void); // Incomplete
static void commandTable1A(void); // Incomplete
static void commandTable1B(void); // Incomplete
static void commandTable1C(void); // Incomplete
static void commandTable1D(void); // Incomplete
static void commandTable1E(void); // Incomplete
static void commandTable20(void); // Incomplete
static void commandTable21(void); // Incomplete
static void commandTable22(void); // Incomplete
static void commandTable24(void); // Incomplete
static void commandTable25(void); // Incomplete
static void commandTable28(void); // Incomplete
static void commandTable29(void); // Incomplete
static void commandTable2A(void); // Incomplete
static void commandTable2F(void); // Incomplete
static void commandTable30(void); // Incomplete
static void commandTable31(void); // Incomplete
static void commandTable32(void); // Incomplete
static void commandTable33(void); // Incomplete
static void commandTable34(void); // Incomplete

static void copyAbilityInfo(void); // Incomplete
static void gfXCmdAbilityAnim(void); // Incomplete
static void gfxCmdAttackNameA(void); // Incomplete
static void magicAtkTypeSingleTarget(void); // Incomplete
static void magicAtkTypeMultiTarget(void); // Incomplete
static void finishCommand(void); // Incomplete
static void finishCommandNullTargets(void); // Incomplete
static void getTargets(void); // Incomplete
static void handleAtbMenu(void); // Incomplete
static void checkControlTargetActive(void); // Incomplete
static void processMenuCommandData(void); // Incomplete
static void consumeItem(void); // Incomplete
static void setupCreditsDemo(void); // Incomplete
static void checkDisablingStatus(void); // Incomplete
static void applyBerserkStatus(void); // Incomplete
static void disableCommandsMagic(void); // Incomplete
static void handleUncontrolledParty(void); // Incomplete
static void zombieAction(void); // Incomplete
static void charmAction(void); // Incomplete
static void berserkAction(void); // Incomplete
static void queueUncontrolledAction(void); // Incomplete
static void randomizeOrder(void); // Incomplete

static void updateTimers(void); // Incomplete
static void updateTimer(void); // Incomplete
static void globalTimers(void); // Incomplete
static void findEndedTimers(void); // Incomplete
static void applyTimerEffects(void); // Incomplete
static void dispatchTimerEffect(void); // Incomplete
static void timerEffectStop(void); // Incomplete
static void timerEffectPoison(void); // Incomplete
static void timerEffectReflect(void); // Incomplete
static void timerEffectCountdown(void); // Incomplete
static void timerEffectMute(void); // Incomplete
static void timerEffectHPLeak(void); // Incomplete
static void timerEffectOld(void); // Incomplete
static void timerEffectRegen(void); // Incomplete
static void timerEffectSing(void); // Incomplete
static void timerEffectParalyze(void); // Incomplete
static void timerEffectATB(void); // Incomplete
static void performAction(void); // Incomplete
static void atbWait(void); // Incomplete
static void resetAtbAll(void); // Incomplete
static void resetAtb(void); // Incomplete
static void clearQuick(void); // Incomplete
static void stopTimer(void); // Incomplete
static void startTimer(void); // Incomplete
static void getTimerDuration(uint8_t timer); // Incomplete
static void addTimerOffsetY(uint8_t timer); // Incomplete
static uint8_t timerDuration_spell(void); // Incomplete
static uint8_t timerDuration_120(void);
static uint8_t timerDuration_stamina20(void); // Incomplete
static uint8_t timerDuration_049(void);
static uint8_t timerDuration_180MagicHalf(void); // Incomplete
static uint8_t timerDuration_180(void);
static uint8_t timerDuration_010(void);
static uint8_t timerDuration_110Magic(void); // Incomplete
static uint8_t timerDuration_030(void);
static uint8_t timerDuration_spellMagicHalf(void); // Incomplete
static uint8_t timerDuration_120MagicHalf(void); // Incomplete
static void monsterAtb(void); // Incomplete

static void checkAICondition(void); // Incomplete
static void aiCondition00(void); // Incomplete
static void aiCondition01(void); // Incomplete
static void aiCondition02(void); // Incomplete
static void aiCondition03(void); // Incomplete
static void aiCondition04(void); // Incomplete
static void aiCondition05(void); // Incomplete
static void aiCondition06(void); // Incomplete
static void aiCondition07(void); // Incomplete
static void aiCondition08(void); // Incomplete
static void aiCondition09(void); // Incomplete
static void aiCondition0A(void); // Incomplete
static void aiCondition0B(void); // Incomplete
static void aiCondition0C(void); // Incomplete
static void aiCondition0D(void); // Incomplete
static void aiCondition0E(void); // Incomplete
static void aiCondition0F(void); // Incomplete
static void aiCondition10(void); // Incomplete
static void aiCondition11(void); // Incomplete
static void aiCondition12(void); // Incomplete

static void getAiTarget(void); // Incomplete
static void aiTarget00(void); // Incomplete
static void aiTarget01(void); // Incomplete
static void aiTarget02(void); // Incomplete
static void aiTarget03(void); // Incomplete
static void aiTarget04(void); // Incomplete
static void aiTarget05(void); // Incomplete
static void aiTarget06(void); // Incomplete
static void aiTarget07(void); // Incomplete
static void aiTarget08(void); // Incomplete
static void aiTarget09(void); // Incomplete
static void aiTarget0a(void); // Incomplete
static void aiTarget0b(void); // Incomplete
static void aiTarget0c(void); // Incomplete
static void aiTarget0d(void); // Incomplete
static void aiTarget0e(void); // Incomplete
static void aiTarget0f(void); // Incomplete
static void aiTarget10(void); // Incomplete
static void aiTarget11(void); // Incomplete
static void aiTarget12(void); // Incomplete
static void aiTarget13(void); // Incomplete
static void aiTarget14(void); // Incomplete
static void aiTarget15(void); // Incomplete
static void aiTarget16(void); // Incomplete
static void aiTarget17(void); // Incomplete
static void aiTarget18(void); // Incomplete
static void aiTarget19(void); // Incomplete
static void aiTarget1a(void); // Incomplete
static void aiTarget1b(void); // Incomplete
static void aiTarget1c(void); // Incomplete
static void aiTarget1d(void); // Incomplete
static void aiTarget1e(void); // Incomplete
static void aiTarget1f(void); // Incomplete
static void aiTarget20(void); // Incomplete
static void aiTarget21(void); // Incomplete
static void aiTarget22(void); // Incomplete
static void aiTarget23(void); // Incomplete
static void aiTarget24(void); // Incomplete
static void aiTarget25(void); // Incomplete
static void aiTarget26(void); // Incomplete
static void aiTarget27(void); // Incomplete
static void aiTarget28(void); // Incomplete
static void aiTarget29(void); // Incomplete
static void aiTarget2a(void); // Incomplete
static void aiTarget2b(void); // Incomplete
static void aiTarget2c(void); // Incomplete
static void aiTarget2d(void); // Incomplete
static void aiTarget2e(void); // Incomplete
static void aiTarget2f(void); // Incomplete
static void aiTarget30(void); // Incomplete
static void aiTarget31(void); // Incomplete
static void aiTarget32(void); // Incomplete
static void checkTargetValid(void); // Incomplete

static void processAiScript(void); // Incomplete
static void dispatchAiCommands(void); // Incomplete
static void aiCastNormalSpell(void); // Incomplete
static void aiChoose1of3(void); // Incomplete
static void aiShowMonster(void); // Incomplete
static void aiSetTarget(void); // Incomplete
static void aiSetVar(void); // Incomplete
static void aiSetEventFlag(void); // Incomplete
static void aiSetStatsToggleStatus(void); // Incomplete
static void aiCopyCommand(void); // Incomplete
static void aiSpellTarget(void); // Incomplete
static void handleReactions(void); // Incomplete
static void checkReactionConditions(void); // Incomplete
static void saveActionData(void); // Incomplete
static void restoreActionData(void); // Incomplete
static void reactionPauseTimerChecks(void); // Incomplete
static void unpauseTimerChecks(void); // Incomplete
static void processReaction(void); // Incomplete

static void loadStatsEquipAi(void); // Incomplete
static void startTimerFromTemp(void); // Incomplete
static void setupInventoryMagic(void); // Incomplete
static void getItemUsableA(void); // Incomplete
static void startPartyPoisonTimers(void); // Incomplete
static void fightCommand(void); // Incomplete
static void processTurn(void); // Incomplete
static void shiftActionAnims(void); // Incomplete
static void dispatchCommand(void); // Incomplete
static void dispatchCommandReady(void); // Incomplete
static void restoreStatsAfterRelease(void); // Incomplete
static void checkRetarget(void); // Incomplete
static void checkValidTargetsExist(void); // Incomplete
static void checkLearnBlue(void); // Incomplete
static void startBattle(void); // Incomplete
static void checkOneTimeEncounters(void); // Incomplete
static void advanceStartingAtb(void); // Incomplete

static void initBattle(void); // Incomplete
static void checkAmbushes(void); // Incomplete
static void setupBackAttack(void); // Incomplete
static void setupPreemptive(void); // Incomplete
static void adjustAtb(void); // Incomplete
static void setupBattleMusic(void); // Incomplete

static void endBattle(void); // Incomplete
static void resetStats(void); // Incomplete
static void mergeItemDupes(void); // Incomplete
static void updateFieldData(void); // Incomplete
static void getLootExp(void); // Incomplete
static void checkHideAP(void); // Incomplete
static void dropMonsterLoot(void); // Incomplete
static void levelUp(void); // Incomplete
static void applyHPMPPassives(void); // Incomplete
static void divideExp(void); // Incomplete
static void gfxCmdMessageClearAnim(void); // Incomplete

static void mainBattleLoop(void); // Incomplete
static void copyHPMPStatus(void); // Incomplete
static void updateMonsterList(void); // Incomplete
static void checkBattleEnd(void); // Incomplete
static void updateMonsterRows(void); // Incomplete
static void castSpell(void); // Incomplete
static void castMultiHitSpell(void); // Incomplete
static void prepSummon(void); // Incomplete
static void getPartyTargetOffset(void); // Incomplete
static void hasteSlowMod(void); // Incomplete
static void killChar(void); // Incomplete
static void checkPartyDeath(void); // Incomplete
static void checkMonsterDeath(void); // Incomplete
static void checkForDeath(void); // Incomplete
static void setupAndLaunchAttack(void); // Incomplete
static void dispatchAttack(void); // Incomplete
static void clearAttackData(void); // Incomplete
static void copyAttackParams(void); // Incomplete
static void applyDamage(void); // Incomplete
static void getDamageDisplayOffset(void); // Incomplete

static void attackType00(void); // Incomplete
static void attackType01(void); // Incomplete
static void attackType02(void); // Incomplete
static void attackType03(void); // Incomplete
static void attackType04(void); // Incomplete
static void attackType05(void); // Incomplete
static void attackType06(void); // Incomplete
static void attackType07(void); // Incomplete
static void attackType08(void); // Incomplete
static void attackType09(void); // Incomplete
static void attackType0A(void); // Incomplete
static void attackType0B(void); // Incomplete
static void attackType0C(void); // Incomplete
static void attackType0D(void); // Incomplete
static void attackType0E(void); // Incomplete
static void attackType0F(void); // Incomplete
static void attackType10(void); // Incomplete
static void attackType11(void); // Incomplete
static void attackType12(void); // Incomplete
static void attackType13(void); // Incomplete
static void attackType14(void); // Incomplete
static void attackType15(void); // Incomplete
static void attackType16(void); // Incomplete
static void attackType17(void); // Incomplete
static void attackType18(void); // Incomplete
static void attackType19(void); // Incomplete
static void attackType1A(void); // Incomplete
static void attackType1B(void); // Incomplete
static void attackType1C(void); // Incomplete
static void attackType1D(void); // Incomplete
static void attackType1E(void); // Incomplete
static void attackType1F(void); // Incomplete
static void attackType20(void); // Incomplete
static void attackType21(void); // Incomplete
static void attackType22(void); // Incomplete
static void attackType23(void); // Incomplete
static void attackType24(void); // Incomplete
static void attackType25(void); // Incomplete
static void attackType26(void); // Incomplete
static void attackType27(void); // Incomplete
static void attackType28(void); // Incomplete
static void attackType29(void); // Incomplete
static void attackType2A(void); // Incomplete
static void attackType2B(void); // Incomplete
static void attackType2C(void); // Incomplete
static void attackType2D(void); // Incomplete
static void attackType2E(void); // Incomplete
static void attackType2F(void); // Incomplete
static void attackType30(void); // Incomplete
static void attackType31(void); // Incomplete
static void attackType32(void); // Incomplete
static void attackType33(void); // Incomplete
static void attackType34(void); // Incomplete
static void attackType35(void); // Incomplete
static void attackType36(void); // Incomplete
static void attackType37(void); // Incomplete
static void attackType38(void); // Incomplete
static void attackType39(void); // Incomplete
static void attackType3A(void); // Incomplete
static void attackType3B(void); // Incomplete
static void attackType3C(void); // Incomplete
static void attackType3D(void); // Incomplete
static void attackType3E(void); // Incomplete
static void attackType3F(void); // Incomplete
static void attackType40(void); // Incomplete
static void attackType41(void); // Incomplete
static void attackType42(void); // Incomplete
static void attackType43(void); // Incomplete
static void attackType44(void); // Incomplete
static void attackType45(void); // Incomplete
static void attackType46(void); // Incomplete
static void attackType47(void); // Incomplete
static void attackType48(void); // Incomplete
static void attackType49(void); // Incomplete
static void attackType4B(void); // Incomplete
static void attackType4C(void); // Incomplete
static void attackType4D(void); // Incomplete
static void attackType4E(void); // Incomplete
static void attackType4F(void); // Incomplete
static void attackType50(void); // Incomplete
static void attackType51(void); // Incomplete
static void attackType52(void); // Incomplete
static void attackType53(void); // Incomplete
static void attackType54(void); // Incomplete
static void attackType55(void); // Incomplete
static void attackType56(void); // Incomplete
static void attackType57(void); // Incomplete
static void attackType58(void); // Incomplete
static void attackType59(void); // Incomplete
static void attackType5A(void); // Incomplete
static void attackType5B(void); // Incomplete
static void attackType5C(void); // Incomplete
static void attackType5D(void); // Incomplete
static void attackType5E(void); // Incomplete
static void attackType5F(void); // Incomplete
static void attackType60(void); // Incomplete
static void attackType61(void); // Incomplete
static void attackType62(void); // Incomplete
static void attackType63(void); // Incomplete
static void attackType64(void); // Incomplete
static void attackType65(void); // Incomplete
static void attackType66(void); // Incomplete
static void attackType68(void); // Incomplete
static void attackType67(void); // Incomplete
static void attackType69(void); // Incomplete
static void attackType6A(void); // Incomplete
static void attackType6B(void); // Incomplete
static void attackType6C(void); // Incomplete
static void attackType6D(void); // Incomplete
static void attackType6E(void); // Incomplete
static void attackType6F(void); // Incomplete
static void attackType70(void); // Incomplete
static void attackType71(void); // Incomplete
static void attackType72(void); // Incomplete
static void attackType73(void); // Incomplete
static void attackType74(void); // Incomplete
static void attackType75(void); // Incomplete

static void hitCalcLevelMEvade(void); // Incomplete
static void setHitParam1TargetEvade(void); // Incomplete
static void setHit100TargetEvade(void); // Incomplete
static void setHit100HalfTargetEvade(void); // Incomplete
static void setHitParam1HalfTargetEvade(void); // Incomplete
static void setHitParam1TargetMEvade(void); // Incomplete
static void hitCalcSteal(void); // Incomplete
static void checkAegis(void); // Incomplete
static void multiTargetHitPercent(void); // Incomplete
static void checkSpecialEvade(void); // Incomplete
static void danceHitMod(void); // Incomplete
static void targetMHitMod(void); // Incomplete
static void targetPHitMod(void); // Incomplete
static void attackerStatusPHitMod(void); // Incomplete
static void checkTargetImage(void); // Incomplete
static void checkVoid(void); // Incomplete
static void checkFloat(void); // Incomplete
static void checkForHit(void); // Incomplete
static void checkForPHit(void); // Incomplete
static void checkHitByCreatureType(void); // Incomplete
static void checkLevel(void); // Incomplete
static void hitMagicCondAutohit(void); // Incomplete
static void hitPhysical(void); // Incomplete
static void hitMagic(void); // Incomplete
static void hitPhysicalMagic(void); // Incomplete
static void magicDamage(void); // Incomplete
static void flareDamage(void); // Incomplete
static void magicDamageRand(void); // Incomplete
static void magicDamagePhysical(void); // Incomplete

static void swordDamage(void); // Incomplete
static void fistDamage(void); // Incomplete
static void knifeDamage(void); // Incomplete
static void axeDamage(void); // Incomplete
static void bellDamage(void); // Incomplete
static void rodDamage(void); // Incomplete
static void levelDamage(void); // Incomplete
static void monsterDamage(void); // Incomplete
static void itemFormula(void); // Incomplete
static void physicalParamDamage(void); // Incomplete
static void throwDamage(void); // Incomplete
static void gilTossDamage(void); // Incomplete

static void multiTargetMod(void); // Incomplete
static void backRowMod(void); // Incomplete
static void commandMod(void); // Incomplete
static void doubleGripMod(void); // Incomplete
static void checkJump(void); // Incomplete
static void runeMod(void); // Incomplete
static void specialtyMod(void); // Incomplete
static void medicineMod(void); // Incomplete
static void creatureMod(void); // Incomplete
static void targetStatusModMag(void); // Incomplete
static void targetStatusModPhys(void); // Incomplete
static void attackerStatusModPhys(void); // Incomplete
static void equalLevelMod(void); // Incomplete

static void braveDamage(void); // Incomplete
static void goblinDamage(void); // Incomplete
static void strongFightDamage(void); // Incomplete
static void chickenDamage(void); // Incomplete

static void elementUpMod(void); // Incomplete
static void spellbladeMod(void); // Incomplete
static void elementDamageModPhys(void); // Incomplete
static void elementDamageModMag(void); // Incomplete
static void elementDamageModMag2(void); // Incomplete
static void checkCrit(void); // Incomplete
static void checkCreatureCrit(void); // Incomplete

static void calcFinalDmgSpellblade(void); // Incomplete
static void gravityDamage(void); // Incomplete

static void cureTarget(void); // Incomplete
static void fullCureTarget(void); // Incomplete
static void setHPCritical(void); // Incomplete
static void drainDamage(void); // Incomplete
static void spellbladePsyche(void); // Incomplete
static void psycheDamage(void); // Incomplete
static void mpHeal(void); // Incomplete
static void fullMPHeal(void); // Incomplete

static void calcFinalDamage(void); // Incomplete
static void calcDamageMaxHP(void); // Incomplete
static void calcDamageAttackerCurHP(void); // Incomplete
static void calcDamageTargetCurHP(void); // Incomplete
static void calcDamageAttackerDiffHP(void); // Incomplete
static void restoreHalfMax(void); // Incomplete
static void calcStatusDuration(void); // Incomplete
static void applySpellbladeStatusEffect(void); // Incomplete
static void applyConditionalStatus(void); // Incomplete
static void applySpecialtyEffects(void); // Incomplete
static void applyStatus1(void); // Incomplete
static void applyStatus2(void); // Incomplete
static void applyStatus3(void); // Incomplete
static void applyStatus4(void); // Incomplete
static void toggleStatus1(void); // Incomplete
static void applyFlirt(void); // Incomplete
static void applyStatus3Exclusive(void); // Incomplete
static void removeStatus1(void); // Incomplete
static void removeStatus2(void); // Incomplete
static void removeStatus3(void); // Incomplete
static void killNonHeavy(void); // Incomplete
static void reviveTarget(void); // Incomplete
static void applyStatus1Bypass(void); // Incomplete
static void applyStatus2Bypass(void); // Incomplete
static void applyStatus3Bypass(void); // Incomplete
static void applyStatus1AttackerBypass(void); // Incomplete
static void removeSpellblade(void); // Incomplete
static void changeTargetRow(void); // Incomplete
static void moveTargetToFront(void); // Incomplete
static void moveAttackerToBack(void); // Incomplete
static void halveDefence(void); // Incomplete
static void halveLevel(void); // Incomplete
static void addLevel(void); // Incomplete
static void subtractLevel(void); // Incomplete
static void doubleMaxHP(void); // Incomplete
static void addAttack(void); // Incomplete
static void addDefenses(void); // Incomplete
static void toggleStatus4(void); // Incomplete
static void addCreatureType(void); // Incomplete
static void addStatus1Immunity(void); // Incomplete
static void addElementUp(void); // Incomplete
static void stealItem(void); // Incomplete
static void startStatus1Timer(void); // Incomplete
static void stopStatus1Timer(void); // Incomplete
static void stopStatus2Timer(void); // Incomplete
static void stopStatus3Timer(void); // Incomplete
static void stopStatus4Timer(void); // Incomplete
static void startStatus2Timer(void); // Incomplete
static void startStatus3Timer(void); // Incomplete
static void startStatus4Timer(void); // Incomplete
static void loseOneImage(void); // Incomplete
static void catchMonster(void); // Incomplete
static void calcBaseDamage(void); // Incomplete
static void processCommands(void); // Incomplete
static void findFirstTargetPlus1(void); // Incomplete
static void getCharStructActionData(void); // Incomplete
static void checkTargetRedirect(void); // Incomplete
static void checkValidTargetsExist2(void); // Incomplete
static void steupReactionsAnims(void); // Incomplete
static void copyReactionInfo(void); // Incomplete
static void gfxCmdDamageNumbers(void); // Incomplete
static void findOpenGfxQueueSlot(void); // Incomplete
static void selectCurProcSequence(void); // Incomplete
static void gfxCmdAttackNameFromTemp(void); // Incomplete
static void gfxCmdMessage(void); // Incomplete
static void setupMsgBoxIndexes(void); // Incomplete
static void deleteCommand(void); // Incomplete
static void collectMPCost(void); // Incomplete
static void applyPartyGear(void); // Incomplete
static void applyGear(void); // Incomplete
static void applyEquipStatus(void); // Incomplete
static void startTimerCurChar(void); // Incomplete
static void replaceHands(void); // Incomplete
static void swapHands(void); // Incomplete

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
    //  LoaD #$09 to A		(command 9: item use)
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
    //  LoaD #$0A to A	(command 10: weapon used as item)
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
    //  LoaD #$01 to A		(ability/command animation)
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
    //  LoaD #$17 to A		(ability name)
    //  Jump to SubRoutine GFXCmdAttackNameA
    //  Store Zero to $22			(index for attack loop)

    //  [AttackLoop]
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$07 to A
    //  Jump to SubRoutine Random_X_A 		(0..7 random monster)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  LoaD AttackerOffset to X
    //  STore A to CharStruct::MonsterTargets,X
    //  Store Zero to CharStruct::PartyTargets,X
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::MonsterTargets,X to A
    //  STore A to MonsterTargets
    //  LoaD CharStruct::PartyTargets,X to A
    //  STore A to PartyTargets
    //  Jump to SubRoutine CheckRetarget
    //  LoaD AttackerOffset to X
    //  LoaD PartyTargets to A
    //  STore A to CharStruct::PartyTargets,X
    //  LoaD MonsterTargets to A
    //  STore A to CharStruct::MonsterTargets,X
    //  PusH A
    //  AND A with #$F0
    //  Logical Shift Right A x4
    //  OR A with CharStruct::PartyTargets,X
    //  STore A to TempTargetBitmask
    //  PulL A
    //  AND A with #$0F
    //  A Shift Left x4
    //  STore A to TempTargetBitmask+1
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  LoaD f:_d0ed85,X to A	(combined size of gearstats structs)
    //  Transfer A to X
    //  STore X to $0E			(gearstats offset)
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::RHWeapon,X to A
    //  Branch to [RH] if Not Equals
    //  JuMP to LH

    //  [RH] Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $14			(AttackInfo offset)
    //  Store Zero to $12
    //  LoaD $0E to X			(gearstats offset)

    //  [LBL] lda RHWeapon,X
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $12
    //  LoaD $12 to A
    //  CoMPare A with #$0C		(copy 12 bytes weapon data)
    //  Branch to previous label if Not Equals
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$01 to A		(ability/command anim)
    //  STore A to GFXQueue::Type,X
    //  LoaD #$04 to A		(fight)
    //  STore A to GFXQueue::Data1,X
    //  Store Zero to GFXQueue::Data2,X	(right hand, no msword anim)
    //  LoaD $0E to X			(gearstats offset)
    //  LoaD RHWeapon::AtkType,X to A
    //  PusH A
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  PulL A
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD TempTargetBitmask to A
    //  STore A to CommandTargetBitmask,X
    //  LoaD TempTargetBitmask+1 to A
    //  STore A to CommandTargetBitmask+1,X
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers

    //  [LH] LoaD AttackerOffset to X
    //  LoaD CharStruct::LHWeapon,X to A
    //  Branch to next label if Not Equals
    //  JuMP to Finish

    //  [LBL] Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $12
    //  Store Zero to $14
    //  LoaD $0E to X		(gearstats offset)

    //  [LBL] lda LHWeapon,X
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $14
    //  LoaD $14 to A
    //  CoMPare A with #$0C	;copy 12 bytes weapon data
    //  Branch to previous label if Not Equals
    //  LoaD $0E to X		;gearstats offset
    //  LoaD ProcSequence to A
    //  Transfer A to Y
    //  LoaD LHWeapon::AtkType,X to A
    //  STore A to AtkType,Y
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$01 to A		(ability/command anim)
    //  STore A to GFXQueue::Type,X
    //  LoaD #$04 to A		(fight)
    //  STore A to GFXQueue::Data1,X
    //  LoaD #$80 to A		(left hand, no msword anim)
    //  STore A to GFXQueue::Data2,X
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD TempTargetBitmask to A
    //  STore A to CommandTargetBitmask,X
    //  LoaD TempTargetBitmask+1 to A
    //  STore A to CommandTargetBitmask+1,X
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers

    //  [Finish] INCrement $22			(attack loop index)
    //  LoaD $22 to A
    //  CoMPare A with #$04		(4 attacks)
    //  Branch to [Ret] if EQuals
    //  JuMP to [AttackLoop]

    //  [Ret] Return To Subroutine
}

// Address: _0DA2
// Command $19 (Observe/Check)
static void commandTable18(void) {
    // LoaD #$19 to A		(observe ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask

    // LoaD #$19 to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$18 to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Address: _0DC3
// Command $1A (Analyze/Scan)
static void commandTable19(void) {
    // LoaD #$1A to A		;observe ability
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask

    // LoaD #$1A to A		;ability name
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$19 to A		;ability anim
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMess
}

// Address: _0DE4
// Command $18 (Conjure)
static void commandTable17(void) {
    //  [ConjureCommand]
    //  LoaD MagicBits+10 to A	(2nd byte of summons)
    //  AND A with #$FE		(last bit is a song)
    //  OR A with MagicBits+9		(1st byte of summons)
    //  Branch to [PickRandomSummon] if Not Equals

    //  ;no summons known
    //  LoaD #$18 to A
    //  Jump to SubRoutine GFXCmdAttackNameA
    //  LoaD MessageBoxOffset to A
    //  Transfer A to X
    //  LoaD #$1D to A		(message)
    //  STore A to MessageBoxes,X
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  LoaD #$7E to A		(always miss)
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  LoaD #$0D to A		(ability animation)
    //  Jump to SubRoutine GFXCmdAbilityAnim
    //  Jump to SubRoutine FinishCommandNullTargets
    //  Jump to SubRoutine GFXCmdMessage
    //  JuMP to [Ret]

    //  [PickRandomSummon]
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  STore X to $0E
    //  LoaD #$0E to A
    //  Jump to SubRoutine Random_X_A    	(0..14)
    //  CLear Carry
    //  ADd #$48 to A with Carry		(offset of first summon)
    //  STore A to TempSpell
    //  Store Zero to TempIsEffect
    //  Logical Shift Right A
    //  ROtate $0E Right
    //  Logical Shift Right A
    //  ROtate $0E Right
    //  Logical Shift Right A
    //  ROtate $0E Right
    //  Transfer A to Y 			(MagicBits offset)
    //  LoaD $0E to A
    //  Jump to SubRoutine ShiftDivide_32
    //  Transfer A to X 			(MagicBits spell)
    //  LoaD MagicBits,Y to A
    //  Jump to SubRoutine SelectBit_X
    //  Branch to [PickRandomSummon] if EQuals	(don't know this one, try again)

    //  [MagicLamp]			(Magic Lamp use jumps in here)
    //  Store Zero to PartyTargets
    //  Store Zero to MonsterTargets
    //  LoaD TempSpell to A
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [LBL] lda f:AttackProp,X
    //  STore A to Temp,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0008		(copy 8 bytes magic data)
    //  Branch to previous label if Not Equals
    //  LoaD Temp to A		(targetting)
    //  Branch to [FindTargets] if Not Equals

    //  ;no targetting data, target self
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to PartyTargets
    //  BRAnch to TargetSet

    //  [FindTargets]
    //  AND A with #$40		(hits all)
    //  Branch to [TargetAll] if Not Equals
    //  LoaD Temp to A		(targetting)
    //  AND A with #$08		(enemy by default)
    //  Branch to [SingleEnemy] if Not Equals

    //  [SingleAlly]			(hardcoded for phoenix, targets first dead ally)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  Transfer A to Y
    //  [LBL] lda CharStruct::Status1,X
    //  AND A with #$80		(dead)
    //  Branch to [DeadAlly] if Not Equals
    //  Jump to SubRoutine NextCharOffset
    //  INcrement Y
    //  ComPare Y with #$0004		(4 chars)
    //  Branch to previous label if Not Equals
    //  LoaD #$80 to A		(defaults to first member if none dead)
    //  BRAnch to SetAlly

    //  [DeadAlly]
    //  Transfer Y to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X

    //  [SetAlly]
    //  STore A to PartyTargets	(target single dead ally)
    //  BRAnch to TargetSet

    //  [SingleEnemy]
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$07 to A
    //  Jump to SubRoutine Random_X_A 		(0..7 random monster)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to MonsterTargets
    //  BRAnch to TargetSet

    //  [TargetAll]
    //  LoaD Temp to A		(targetting)
    //  AND A with #$08		(enemy by default)
    //  Branch to [AllEnemy] if Not Equals
    //  LoaD #$F0 to A
    //  STore A to PartyTargets	(all allies)
    //  BRAnch to TargetSet

    //  [AllEnemy]
    //  LoaD #$FF to A
    //  STore A to MonsterTargets	(all enemies)

    //  [TargetSet]
    //  Store Zero to TempAttachedSpell	(params for CastSpell)
    //  Store Zero to TempSkipNaming
    //  Jump to SubRoutine CastSpell
    //  LoaD TempAttachedSpell to A
    //  Branch to [Ret] if EQuals
    //  LoaD TempAttachedSpell to A	(second spell, for phoenix summon)
    //  STore A to TempSpell
    //  Store Zero to TempIsEffect
    //  LoaD TempMonsterTargets to A
    //  STore A to MonsterTargets
    //  LoaD TempPartyTargets to A
    //  STore A to PartyTargets
    //  INCrement TempSkipNaming	(2nd spell has no label AND A with diff anim)
    //  Jump to SubRoutine CastSpell

    //  [Ret] Return To Subroutine

    //  ConjureMagicLamp := CommandTable17::MagicLamp   (Definition needed to jump to here)
}

// Address: _0EE0
// Command $1B (Tame/Calm)
static void commandTable1A(void) {
    // LoaD #$1B to A		(tame ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask

    // LoaD #$1B to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$1A to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // JuMP to FinishCommand
}

// Address: _0EFE
// Command $1C (Control)
static void commandTable1B(void) {
    // LoaD #$1C to A		(control ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask

    // LoaD #$1C to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$1B to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Address: _0F1F
// Command $1D (Catch)
static void commandTable1C(void) {
    // LoaD #$1D to A		(catch ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask

    // LoaD #$1D to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$1C to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdMessage
}

// Address: _0F40
// Command $1E (Release)
static void commandTable1D(void) {
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::CaughtMonster,X to A
    //  STore A to ReleasedMonsterID
    //  PusH A
    //  LoaD #$FF to A		(no monster caught)
    //  STore A to CharStruct::CaughtMonster,X
    //  PulL A
    //  Transfer A to X
    //  LoaD f:MonsterRelease,X to A
    //  STore A to TempSpell
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [LBL] LoaD f:AttackProp,X to A
    //  STore A to TempMagicInfo,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0008		(8 bytes magic data)
    //  Branch to previous label if Not Equals
    //  Jump to SubRoutine SelectCurrentProcSequence
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X

    //  [LBL] lda TempMagicInfo,X
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare X with #$0005		(copy first 5 bytes)
    //  Branch to previous label if Not Equals
    //  INcrement Y 			(increment dest pointer by 4)
    //  INcrement Y
    //  INcrement Y
    //  INcrement Y

    //  [LBL] lda TempMagicInfo,X
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare X with #$0008		(then copy remaining 3 bytes)
    //  Branch to previous label if Not Equals
    //  Store Zero to MonsterTargets
    //  Store Zero to PartyTargets
    //  LoaD TempMagicInfo::Targetting to A
    //  Branch to Targetting if Not Equals
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to PartyTargets	;default to attacker if no targetting
    //  BRAnch to [TargetSet]

    //  [Targetting]
    //  AND A with #$40		(all targets)
    //  Branch to [TargetAll] if Not Equals
    //  LoaD TempMagicInfo::Targetting to A
    //  AND A with #$08		(enemy by default)
    //  Branch to [TargetEnemy] if Not Equals

    //  [TargetParty]
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$03 to A
    //  Jump to SubRoutine Random_X_A		(0..3 random party)
    //  CoMPare A with AttackerIndex
    //  Branch to [TargetParty] if EQuals	(pick again if attacker chosen)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to PartyTargets
    //  BRAnch to [TargetSet]

    //  [TargetEnemy]
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$07 to A
    //  Jump to SubRoutine Random_X_A	      	(0..7 random monster)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to MonsterTargets
    //  BRAnch to [TargetSet]

    //  [TargetAll]
    //  LoaD TempMagicInfo::Targetting to A
    //  AND A with #$08		(enemy by default)
    //  Branch to [TargetAllEnemy] if Not Equals
    //  LoaD #$F0 to A
    //  STore A to PartyTargets
    //  BRAnch to [TargetSet]

    //  [TargetAllEnemy]
    //  LoaD #$FF to A
    //  STore A to MonsterTargets

    //  [TargetSet]
    //  Jump to SubRoutine CheckMultiTarget
    //  Branch to [Multi] if Not Equals
    //  LoaD TempMagicInfo::AtkType to A
    //  Branch to [_CheckRetarget] if PLus
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  INCrement HitsInactive,X
    //  BRAnch to [TargetOK]

    //  [_CheckRetarget]
    //  Jump to SubRoutine CheckRetarget
    //  BRAnch to [TargetOK]

    //  [Multi]
    //  Jump to SubRoutine RemoveInactiveTargets
    //  Jump to SubRoutine CheckMultiTarget

    //  [TargetOK]
    //  Jump to SubRoutine BuildTargetBitmask
    //  LoaD TempSpell to A
    //  STore A to Temp+1		(attack id)
    //  Store Zero to Temp		(string table 0)
    //  Jump to SubRoutine GFXCmdAttackNameFromTemp
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  Store Zero to GFXQueue::Data2,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$00 to A		(attack animation)
    //  STore A to GFXQueue::Type,X
    //  LoaD Temp+1 to A		(attack id)
    //  STore A to GFXQueue::Data1,X
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  LoaD TempMagicInfo::AtkType to A
    //  AND A with #$7F		(remove flag bit)
    //  STore A to AtkType,X
    //  LoaD TempTargetting to A	(number of targets minus 1)
    //  STore A to MultiTarget,X
    //  Branch to next label if EQuals
    //  INCrement MultiTarget,X	(number of targets (but 1 target -> 0))
    //  LoaD #$80 to A		(multi target)

    //  [LBL] STore A to TargetType,X
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD TempTargetBitmask to A
    //  STore A to CommandTargetBitmask,X
    //  STore A to TargetBitmask,X
    //  LoaD TempTargetBitmask+1 to A
    //  STore A to CommandTargetBitmask+1,X
    //  STore A to TargetBitmask+1,X
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  LoaD AttackerIndex to A
    //  STore A to $24
    //  LoaD #$14 to A
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit     	(Index * 20, size of CharCommands)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD $26 to X			(CharCommands offset)

    //  [FindCmd]
    //  LoaD CharCommands::ID,X to A
    //  CoMPare A with #$1E		(release)
    //  Branch to [Found] if EQuals
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0004		(4 command slots)
    //  Branch to [FindCmd] if Not Equals
    //  Branch to [CopyStats] if EQuals

    //  [Found]
    //  LoaD #$1D to A		(catch)
    //  STore A to CharCommands::ID,X
    //  LoaD #$28 to A		(target selectable + enemy default)
    //  STore A to CharCommands::Targetting,X
    //  INcrement X
    //  INcrement Y
    //  BRAnch to [FindCmd]		(keep going, could have multiple copies)

    //  [CopyStats]	(backs up attacker's stats so it can load monster stats instead, they will be restored later)
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Level,X to A
    //  STore A to SavedCharStats::Level
    //  LoaD CharStruct::MonsterAttack,X to A
    //  STore A to SavedCharStats::MonsterAttack
    //  LoaD CharStruct::MonsterM,X to A
    //  STore A to SavedCharStats::MonsterM
    //  LoaD CharStruct::EquippedMag,X to A
    //  STore A to SavedCharStats::EquippedMag
    //  LoaD CharStruct::CharRow,X to A
    //  STore A to SavedCharStats::CharRow
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [CopyStatus]
    //  LoaD CharStruct::Status1,X to A
    //  STore A to SavedCharStats::Status1,Y
    //  Store Zero to CharStruct::Status1,X	(clear status for released mon)
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0009		(9 bytes of status/passives)
    //  Branch to CopyStatus if Not Equals
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD AttackerOffset to X

    //  [CopyMSword]
    //  LoaD CharStruct::MSwordElemental1,X to A
    //  STore A to SavedCharStats::MSwordElemental1,Y
    //  Store Zero to CharStruct::MSwordElemental1,X	(clear all msword)
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0006		(6 bytes msword elements/status)
    //  Branch to [CopyMSword] if Not Equals
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD AttackerOffset to X

    //  [CopyMisc]
    //  LoaD CharStruct::AlwaysStatus1,X to A
    //  STore A to SavedCharStats::AlwaysStatus1,Y
    //  Store Zero to CharStruct::AlwaysStatus1,X
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$000B		(11 bytes always status/bonuses/etc)
    //  Branch to [CopyMisc] if Not Equals
    //  LoaD ReleasedMonsterID to A
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_32
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD AttackerOffset to Y
    //  LoaD CharStruct::CharRow,Y to A
    //  AND A with #$7F		;always front row
    //  STore A to CharStruct::CharRow,Y
    //  LoaD f:MonsterProp + 31,X to A
    //  STore A to CharStruct::Level,Y
    //  LoaD f:MonsterProp + 1,X to A
    //  STore A to CharStruct::MonsterAttack,Y
    //  LoaD f:MonsterProp + 2,X to A
    //  STore A to CharStruct::MonsterM,Y
    //  LoaD f:MonsterProp + 5,X to A
    //  STore A to CharStruct::EquippedMag,Y
    //  LoaD #$01 to A
    //  STore A to WasMonsterReleased	(causes stats to be restored later)
    //  Return To Subroutine
}

// Address: _1125
// Command $1F (Combine/Mix)
static void commandTable1E(void) {
    // LoaD AttackerOffset to X
    // LoaD CharStruct::MonsterTargets,X to A
    // STore A to MonsterTargets
    // LoaD CharStruct::PartyTargets,X to A
    // STore A to PartyTargets
    // LoaD CharStruct::SelectedItem,X to A
    // SEt Carry flag
    // SuBtract #$E0 from A with Carry	(remove consumable item offset from item id)
    // Transfer A to X
    // STore X to $0E		(first item consumable index)
    // LoaD AttackerOffset to X
    // LoaD CharStruct::SecondSelectedItem,X to A
    // SEt Carry flag
    // SuBtract #$E0 from A with Carry	(remove consumable item offset from item id)
    // STore A to $24
    // LoaD #$0C to A
    // STore A to $25
    // Jump to SubRoutine Multiply_8bit    	(item*12)
    // Lengthen A
    // CLear Carry flag
    // LoaD $26 to A			(second item * 12)
    // ADd $0E to A with Carry			(+ first item)
    // Transfer A to X
    // Clear A, then Shorten
    // LoaD f:MixComboTbl,X to A
    // STore A to TempSpell
    // STore Zero to TempAttachedSpell
    // STore Zero to TempSkipNaming
    // LoaD #$01 to A
    // STore A to TempIsEffect
    // JuMP to CastSpell
}

// Address: _1169
// Command $21 (Pray/Recover)
static void commandTable20(void) {
    // LoaD #$21 to A		(recover ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget

    // LoaD #$21 to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$20 to A		(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeMultiTarget
    // Jump to SubRoutine FinishCommand
    // JuMP to GFXCmdDamageNumbers
}

// Address: _118A
// Command $22 (Revive)
static void commandTable21(void) {
    // LoaD #$22 to A		(revive ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine BuildTargetBitmask
    // Jump to SubRoutine CheckMultiTarget

    // LoaD ProcSequence to A
    // Transfer A to X
    // inc HitsInactive,X

    // LoaD #$22 to A		(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$21 to A		(ability anim)
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
    //  LoaD Level to A
    //  Jump to SubRoutine Random_X_A 	(0..Level)
    //  CoMPare A with #$0B
    //  Branch to next label if Carry Set
    //  Transfer Direct page to aCcumulator          	(<11, 0)
    //  BRAnch to [Chosen]

    //  [LBL] CoMPare A with #$15
    //  Branch to next label if Carry Set
    //  LoaD #$01 to A     	(<21, 1)
    //  BRAnch to [Chosen]

    //  [LBL] CoMPare A with #$33
    //  Branch to next label if Carry Set
    //  LoaD #$02 to A     	(<50, 2)
    //  BRAnch to [Chosen]

    //  [LBL] LoaD #$03 to A     	(otherwise 3)

    //  [Chosen]
    //  STore A to $0E		(terrain spell slot 0-3)
    //  LoaD TerrainType to A
    //  Jump to SubRoutine ShiftMultiply_4
    //  CLear Carry
    //  ADd $0E to A with Carry
    //  Transfer A to X
    //  LoaD f:TerrainAttackTbl,X to A
    //  STore A to TempSpell
    //  LoaD TempSpell to A	(pointless load?)
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [LBL] lda f:SpecialAbilityAttackProp,X
    //  STore A to Temp,Y
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0008	(copy 8 bytes spell data)
    //  Branch to previous label if Not Equals
    //  Store Zero to PartyTargets
    //  Store Zero to MonsterTargets
    //  LoaD Temp to A		(targetting byte)
    //  Branch to [Targetting] if Not Equals
    //  LoaD AttackerIndex to A	(default to attacker)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to PartyTargets
    //  BRAnch to [TargetSet]

    //  [Targetting]
    //  AND A with #$08	(target enemy by default)
    //  Branch to [TargetEnemy] if Not Equals
    //  LoaD Temp to A
    //  AND A with #$40	(target all)
    //  Branch to [TargetAllParty] if Not Equals
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$03 to A
    //  Jump to SubRoutine Random_X_A 	(0..3 random party)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to PartyTargets
    //  BRAnch to [TargetSet]

    //  [TargetAllParty]
    //  LoaD #$F0 to A
    //  STore A to PartyTargets
    //  BRAnch to [TargetSet]

    //  [TargetEnemy]
    //  LoaD Temp to A
    //  AND A with #$40	;target all
    //  Branch to [TargetAllEnemy] if Not Equals
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$07 to A	(0..7 random monster)
    //  Jump to SubRoutine Random_X_A
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to MonsterTargets
    //  BRAnch to [TargetSet]

    //  [TargetAllEnemy]
    //  LoaD #$FF to A
    //  STore A to MonsterTargets

    //  [TargetSet]
    //  Store Zero to TempAttachedSpell
    //  Store Zero to TempSkipNaming
    //  LoaD #$01 to A
    //  STore A to TempIsEffect
    //  JuMP to CastSpell
}

// Address: _125E
// Command $25 (Hide)
static void commandTable24(void) {
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status4,X to A
    //  OR A with #$01	(hidden)
    //  STore A to CharStruct::Status4,X
    //  LoaD #$25 to A	(ability name)
    //  Jump to SubRoutine GFXCmdAttackNameA
    //  LoaD #$24 to A	(ability anim)
    //  Jump to SubRoutine GFXCmdAbilityAnim
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  INCrement UnknownReaction
    //  Jump to SubRoutine FinishCommandNullTargets
    //  LoaD AttackerIndex to A
    //  STore A to $24
    //  LoaD #$14 to A	(20, size of CharCommands struct)
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD $26 to X

    //  [FindHideCommands]
    //  LoaD CharCommands::ID,X to A
    //  CoMPare A with #$25	(hide command)
    //  Branch to [Found] if EQuals
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0004	(4 command slots)
    //  Branch to [FindHideCommands] if Not Equals
    //  Branch to [Ret] if EQuals

    //  [Found]LoaD #$26 to A	(show command)
    //  STore A to CharCommands::ID,X
    //  LoaD #$08 to A	(target enemy?)
    //  STore A to CharCommands::Targetting,X
    //  INcrement X
    //  INcrement Y
    //  BRAnch to [FindHideCommands]

    //  [Ret] Return To Subroutine
}

// Address: _12B3
// Command $26 (Show)
static void commandTable25(void) {
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status4,X to A
    //  AND A with #$FE	(clear hidden)
    //  STore A to CharStruct::Status4,X

    //  LoaD #$26 to A	(ability name)
    //  Jump to SubRoutine GFXCmdAttackNameA

    //  LoaD #$25 to A	(ability anim)
    //  Jump to SubRoutine GFXCmdAbilityAnim
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  INCrement UnknownReaction
    //  Jump to SubRoutine FinishCommandNullTargets
    //  LoaD AttackerIndex to A
    //  STore A to $24
    //  LoaD #$14 to A	(20, size of CharCommands struct)
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD $26 to X

    //  [FindShowCommands]
    //  LoaD CharCommands::ID,X to A
    //  CoMPare A with #$26	;show command
    //  Branch to [Found] if EQuals
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0004	(4 command slots)
    //  Branch to [FindShowCommands] if Not Equals
    //  Branch to [Ret] if EQuals

    //  [Found]
    //  LoaD #$25 to A
    //  STore A to CharCommands::ID,X
    //  Store Zero to CharCommands::Targetting,X
    //  INcrement X
    //  INcrement Y
    //  BRAnch to FindShowCommands

    //  [Ret] Return To Subroutine
}

// Address: _1306
// Command $29 (Flirt)
static void commandTable28(void) {
    // LoaD #$29 to A	(flirt ability)
    // Jump to SubRoutine CopyAbilityInfo
    // Jump to SubRoutine GetTargets
    // Jump to SubRoutine CheckRetarget
    // Jump to SubRoutine BuildTargetBitmask

    // LoaD #$29 to A	(ability name)
    // Jump to SubRoutine GFXCmdAttackNameA

    // LoaD #$28 to A	(ability anim)
    // Jump to SubRoutine GFXCmdAbilityAnim
    // Jump to SubRoutine MagicAtkTypeSingleTarget
    // Jump to SubRoutine FinishCommand
    // Jump to SubRoutine GFXCmdDamageNumbers
    // LoaD MessageBoxOffset to A
    // Transfer A to X

    // LoaD #$27 to A	(message)
    // STore A to MessageBoxes,X
    // JuMP to GFXCmdMessage
}

// Address: _1333
// Command $2A (Dance)
static void commandTable29(void) {
    //  Store Zero to ProcSequence	(reset command sequence ;no procs)
    //  Store Zero to NextGFXQueueSlot
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$03 to A
    //  Jump to SubRoutine Random_X_A		(0..3 random dance)
    //  STore A to TempDance
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::ArmorProperties,X to A
    //  AND A with #$04		(sword dance up)
    //  BRAnch to [DanceCheck] if EQuals
    //  Jump to SubRoutine Random_0_99
    //  Logical Shift Right A
    //  BRAnch to [NotSwordDance] if Carry Set	(50% chance of sword dance)
    //  LoaD #$03 to A		(sword dance)
    //  STore A to TempDance
    //  BRAnch to [DanceCheck]

    //  [NotSwordDance]
    //  Jump to SubRoutine Random_0_99
    //  Logical Shift Right A
    //  Store Zero to TempDance
    //  ROtate TempDance Left		(50% chance of 0 or 1)

    //  [DanceCheck]
    //  LoaD TempDance to A
    //  CoMPare A with #$03		(sword dance)
    //  BRAnch to [SwordDance] if EQuals
    //  Jump to SubRoutine GetTargets
    //  Jump to SubRoutine CheckRetarget
    //  Jump to SubRoutine BuildTargetBitmask
    //  Jump to SubRoutine CheckMultiTarget
    //  CLear Carry
    //  LoaD TempDance to A
    //  ADd #$79 to A with Carry		(offset to dance strings)
    //  STore A to Temp+1		(string id / ability id)
    //  Store Zero to Temp		(string table)
    //  Jump to SubRoutine GFXCmdAttackNameFromTemp
    //  LoaD #$29 to A		(dance anim)
    //  Jump to SubRoutine GFXCmdAbilityAnim
    //  Jump to SubRoutine SelectCurrentProcSequence
    //  LoaD Temp+1 to A		(ability id)
    //  Jump to SubRoutine CopyROMMagicInfo
    //  Jump to SubRoutine MagicAtkTypeSingleTarget
    //  Jump to SubRoutine FinishCommand
    //  JuMP to GFXCmdDamageNumbers

    //  [SwordDance]
    //  LoaD #$7D to A		(sword dance ability)
    //  STore A to Temp+1		(string id / ability id)
    //  Store Zero to Temp		(string table)
    //  Jump to SubRoutine GFXCmdAttackNameFromTemp

    //  LoaD #$29 to A		(dance anim)
    //  Jump to SubRoutine GXCmdAbilityAnim
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  LoaD #$7F to A		(do nothing)
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  Jump to SubRoutine FinishCommandNullTargets
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::DamageMod,X to A
    //  OR A with #$D0		(auto hit, damage*2, M*2)
    //  STore A to CharStruct::DamageMod,X
    //  JuMP to SimpleFight
}

// Address: _13CE
// Command $2B (Mimic)
static void commandTable2A(void) {
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD AttackerOffset to X

    //  [LBL] lda SavedAction,Y
    //  STore A to CharStruct::ActionFlag,X
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$000A	;copy 10 bytes action data
    //  Branch to previous label if Not Equals
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::ActionFlag,X to A
    //  AND A with #$FE	;clear "costs mp" bit
    //  STore A to CharStruct::ActionFlag,X
    //  LoaD CharStruct::Command,X to A
    //  JuMP to DispatchCommand_CommandReady
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
    // LoaD ProcSequence to A
    // Transfer A to X
    // STore Zero to AtkType,X
    // STore Zero to MultiTarget,X
    // STore Zero to TargetType,X
    // Jump to SubRoutine FinishCommandNullTargets
    // LoaD MessageBoxOffset to A
    // Transfer A to X
    // LoaD #$28 to A	(message to display)
    // STore A to MessageBoxes,X
    // JuMP to GFXCmdMessage
}

// Address: _141D
// Command $52
// Jump with a different name
static void commandTable30(void) {
    // LoaD #$52 to A	(command name)
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
    //  LoaD #$4B to A	(wind slash spell effect)
    //  STore A to TempEffect

    //  [WeaponEffectCommand]	(called here for other weapon effects)
    //  Store Zero to $0E		(hand)
    //  Store Zero to NextGFXQueueSlot
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::RHWeapon,X to A
    //  Branch to next label if Not Equals
    //  LoaD #$80 to A	(left hand)
    //  STore A to $0E

    //  [LBL] Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag
    //  LoaD #$FC to A	(exec graphics command)
    //  STore A to GFXQueue::Cmd
    //  LoaD #$01 to A	(ability/command anim)
    //  STore A to GFXQueue::Type
    //  LoaD #$04 to A	(fight)
    //  STore A to GFXQueue::Data1
    //  LoaD $0E to A		(hand (0 for RH, 80 for LH))
    //  STore A to GFXQueue::Data2
    //  LoaD #$7E to A	(always miss)
    //  STore A to AtkType
    //  Store Zero to MultiTarget
    //  Store Zero to TargetType
    //  Store Zero to CommandTargetBitmask
    //  Store Zero to CommandTargetBitmask+1
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  LoaD #$FF to A
    //  STore A to a:wMonsterTargets	(**optimize: wasted bytes)
    //  Store Zero to a:wPartyTargets
    //  LoaD TempEffect to A
    //  STore A to TempSpell
    //  LoaD #$01 to A
    //  STore A to TempIsEffect
    //  STore A to TempSkipNaming
    //  Store Zero to TempAttachedSpell
    //  Jump to SubRoutine CastSpell
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Command,X to A
    //  CoMPare A with #$0C	(capture/mug)
    //  Branch to [Ret] if Not Equals	(removes return address from stack for capture)
    //  PulL X 		(likely unreachable since capture cancels procs)

    //  [Ret] Return To Subroutine
}

// Address: _1490
// Command $54
// Job-specific attack animation
// likely for credits demo?
static void commandTable32(void) {
    // LoaD AttackerOffset to X
    // CLear Carry flag
    // LoaD CharStruct::Job,X to A
    // ADd #$30 to A with Carry
    // Jump to SubRoutine GFXCmdAbilityAnim
    // LoaD #$7F to A	(null attack)
    // STore A to AtkType
    // STore Zero to MultiTarget
    // STore Zero to TargetType
    // LoaD #$08 to A	(first monster)
    // STore A to CommandTargetBitmask
    // STore A to TargetBitmask
    // STore Zero to CommandTargetBitmask+1
    // STore Zero to TargetBitmask+1
    // INCrement UnknownReaction
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
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::MonsterTargets,X to A
    //  STore A to MonsterTargets
    //  LoaD CharStruct::PartyTargets,X to A
    //  STore A to PartyTargets
    //  Jump to SubRoutine CheckRetarget
    //  LoaD AttackerOffset to X
    //  LoaD PartyTargets to A
    //  STore A to CharStruct::PartyTargets,X
    //  LoaD MonsterTargets to A
    //  STore A to CharStruct::MonsterTargets,X
    //  PusH A
    //  AND A with #$F0
    //  Logical Shift Right A x4
    //  OR A with CharStruct::PartyTargets,X
    //  STore A to TempTargetBitmask
    //  PulL A
    //  AND A with #$0F
    //  A Shift Left x4
    //  STore A to TempTargetBitmask+1
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  LoaD f:_d0ed85,X to A	(size of one character's gear structs)
    //  Transfer A to X
    //  STore X to $0E			(GearStruct offset)
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::RHWeapon,X to A
    //  Branch to [RH] if Not Equals
    //  JuMP to [LH]

    //  [RH] Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $14
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
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$01 to A		(ability/command animation)
    //  STore A to GFXQueue::Type,X
    //  LoaD #$04 to A		(fight)
    //  STore A to GFXQueue::Data1,X
    //  Store Zero to GFXQueue::Data2,X	;right hand, no msword
    //  LoaD $0E to X			(GearStruct offset)
    //  LoaD RHWeapon::AtkType,X to A
    //  PusH A
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  PulL A
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD TempTargetBitmask to A
    //  STore A to CommandTargetBitmask,X
    //  LoaD TempTargetBitmask+1 to A
    //  STore A to CommandTargetBitmask+1,X
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $14
    //  Store Zero to $12
    //  LoaD $0E to X			(GearStruct offset)
    //  LoaD RHWeapon::Properties,X to A
    //  AND A with #$02		(command instead of attack)
    //  Branch to [LH] if EQuals
    //  LoaD RHWeapon::Param3,X to A
    //  CoMPare A with #$55		(this command)
    //  Branch to [LH] if Not Equals

    //  [LBL] lda RHWeapon,X
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $12
    //  LoaD $12 to A
    //  CoMPare A with #$0C		(copy 12 bytes data for 2nd attack)
    //  Branch to previous label if Not Equals
    //  LoaD #$80 to A
    //  STore A to ActionAnimShift	(flag for later anim manipulation)
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  Store Zero to GFXQueue::Cmd,X
    //  Store Zero to GFXQueue::Type,X
    //  Store Zero to GFXQueue::Data1,X
    //  Store Zero to GFXQueue::Data2,X
    //  LoaD $0E to X			(GearStruct offset)
    //  LoaD RHWeapon::AtkType,X to A
    //  PusH A
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  PulL A
    //  STore A to AtkType,X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD TempTargetBitmask to A
    //  STore A to CommandTargetBitmask,X
    //  LoaD TempTargetBitmask+1 to A
    //  STore A to CommandTargetBitmask+1,X
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers

    //  [LH] LoaD AttackerOffset to X
    //  LoaD CharStruct::LHWeapon,X to A
    //  Branch to next label if Not Equals
    //  JuMP to [Ret]

    //  [LBL] Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $12
    //  Store Zero to $14
    //  LoaD $0E to X			(GearStruct offset)

    //  [LBL] LoaD LHWeapon,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $14
    //  LoaD $14 to A
    //  CoMPare A with #$0C		(copy 12 bytes weapon data)
    //  Branch to previous label if Not Equals
    //  LoaD $0E to X			(GearStruct offset)
    //  LoaD ProcSequence to A
    //  Transfer A to Y
    //  LoaD LHWeapon::AtkType,X to A
    //  STore A to AtkType,Y
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  LoaD #$FC to A		(exec graphics command)
    //  STore A to GFXQueue::Cmd,X
    //  LoaD #$01 to A		(command/ability anim)
    //  STore A to GFXQueue::Type,X
    //  LoaD #$04 to A		(fight)
    //  STore A to GFXQueue::Data1,X
    //  LoaD #$80 to A		(left hand, no msword)
    //  STore A to GFXQueue::Data2,X
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD TempTargetBitmask to A
    //  STore A to CommandTargetBitmask,X
    //  LoaD TempTargetBitmask+1 to A
    //  STore A to CommandTargetBitmask+1,X
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers
    //  Jump to SubRoutine SelectCurrentProcSequence
    //  STore Y to $12
    //  Store Zero to $14
    //  LoaD $0E to X
    //  LoaD LHWeapon::Properties,X to A
    //  AND A with #$02		;command instead of attack
    //  Branch to [Ret] if EQuals
    //  LoaD LHWeapon::Param3,X to A
    //  CoMPare A with #$55		(this command)
    //  Branch to [Ret] if Not Equals

    //  [LBL] LoaD LHWeapon,X
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $14
    //  LoaD $14 to A
    //  CoMPare A with #$0C		(copy 12 bytes weapon data for 2nd atk)
    //  Branch to previous label if Not Equals
    //  LoaD ActionAnimShift to A
    //  OR A with #$40
    //  STore A to ActionAnimShift
    //  LoaD $0E to X
    //  LoaD ProcSequence to A
    //  Transfer A to Y
    //  LoaD LHWeapon::AtkType,X to A
    //  STore A to AtkType,Y
    //  Jump to SubRoutine FindOpenGFXQueueSlot
    //  Store Zero to GFXQueue::Flag,X
    //  Store Zero to GFXQueue::Cmd,X
    //  Store Zero to GFXQueue::Type,X
    //  Store Zero to GFXQueue::Data1,X
    //  Store Zero to GFXQueue::Data2,X
    //  LoaD ProcSequence to A
    //  Transfer A to X
    //  Store Zero to MultiTarget,X
    //  Store Zero to TargetType,X
    //  LoaD ProcSequence to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD TempTargetBitmask to A
    //  STore A to CommandTargetBitmask,X
    //  LoaD TempTargetBitmask+1 to A
    //  STore A to CommandTargetBitmask+1,X
    //  INCrement ProcSequence
    //  Jump to SubRoutine GFXCmdDamageNumbers

    //  [Ret] Return To Subroutine
}

// Address: _16A2
// Command $56
// Earthquake weapon effect
static void commandTable34(void) {
    // LoaD #$4A to A	(earthquake)
    // STore A to TempEffect
    // JuMP to CommandTable31::WeaponEffectCommand
}

// Address: _16AA
static void copyAbilityInfo(void) {
    //  PusH A
    //  Jump to SubRoutine SelectCurrentProcSequence
    //  PulL A
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  Store Zero to $0A

    //  [LBL] LoaD f:BattleCmdProp,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $0A
    //  LoaD $0A to A
    //  CoMPare A with #$05     (copy first 5 bytes)
    //  Branch to previous label if Not Equals
    //  INcrement Y          (skip 4 on destination)
    //  INcrement Y
    //  INcrement Y
    //  INcrement Y

    //  [LBL] LoaD f:BattleCmdProp,X to A
    //  STore A to AttackInfo,Y
    //  INcrement X
    //  INcrement Y
    //  INCrement $0A
    //  LoaD $0A to A
    //  CoMPare A with #$08      (copy remaining 3 bytes)
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
    // LoaD #$FC to A	(exec graphics command)
    // STore A to GFXQueue::Cmd,X
    // LoaD #$01 to A	(ability/command anim)
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
    // LoaD #$01 to A
    // STore A to Temp
    // JuMP to GFXCmdAttackNameFromTemp
}

// Address: _1705
static void magicAtkTypeSingleTarget(void) {
    // LoaD ProcSequence to A
    // Transfer A to X
    // LoaD $0C to Y
    // LoaD AttackInfo::MagicAtkType,Y to A
    // AND A with #$7F
    // STore A to AtkType,X
    // STore Zero to MultiTarget,X
    // STore Zero to TargetType,X
    // Return to SubRoutine
}

// Address: _171A
static void magicAtkTypeMultiTarget(void) {
    // LoaD ProcSequence to A
    // Transfer A to X
    // LoaD $0C to Y
    // LoaD AttackInfo::MagicAtkType,Y to A
    // AND A with #$7F
    // STore A to AtkType,X
    // LoaD TempTargetting to A
    // INCrement A 	(unconditional, so always considered multitarget)
    // STore A to MultiTarget,X
    // LoaD #$80 to A	(multi target)
    // STore A to TargetType,X
    // Return to SubRoutine
}

// Address: _1735
// Copies command targetting to final locations and
// advances ProcSequence
static void finishCommand(void) {
    // LoaD ProcSequence to A
    // A Shift Left
    // Transfer A to X
    // LoaD TempTargetBitmask to A
    // STore A to CommandTargetBitmask,X
    // STore A to TargetBitmask,X
    // LoaD TempTargetBitmask+1 to A
    // STore A to CommandTargetBitmask+1,X
    // STore A to TargetBitmask+1,X
    // INCrement ProcSequence
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
    // LoaD AttackerOffset to X
    // LoaD CharStruct::PartyTargets,X to A
    // STore A to PartyTargets
    // LoaD CharStruct::MonsterTargets,X to A
    // STore A to MonsterTargets
    // Return to SubRoutine
}

// Address: _176C
static void handleAtbMenu(void) {
    //  LoaD MenuData::MenuOpen to A
    //  Branch to MenuOpen if Not Equals
    //  JuMP to [MenuClosed]

    //  [MenuOpen]	(checks if current display info for status/mp matches what's in CharStruct)
    //  LoaD DisplayInfo::CurrentChar to A
    //  STore A to CurrentChar
    //  Jump to SubRoutine CalculateCharOffset
    //  Lengthen A
    //  LoaD CharStruct::Status1,X to A	(includes status 2)
    //  CoMPare A with DisplayInfo::Status1
    //  Branch to [Differs] if Not Equals
    //  LoaD CharStruct::Status3,X to A	(includes status 4)
    //  CoMPare A with DisplayInfo::Status3
    //  Branch to [Differs] if Not Equals
    //  LoaD CharStruct::CurMP,X to A
    //  CoMPare A with DisplayInfo::CurMP
    //  Branch to [Differs] if Not Equals
    //  Clear A, then Shorten
    //  BRAnch to [Matches]

    //  [Differs]	(disable commands as needed, AND A with update displayinfo for menu)
    //  Clear A, then Shorten
    //  Jump to SubRoutine CheckDisablingStatus
    //  Branch to [Disabled] if Not Equals
    //  Jump to SubRoutine DisableCommandsMagic
    //  Jump to SubRoutine ApplyBerserkStatus
    //  Branch to [Disabled] if Not Equals
    //  LoaD #$05 to A		(C1 routine)
    //  Jump to SubRoutine CallC1
    //  LoaD #$06 to A		(C1 routine)
    //  Jump to SubRoutine CallC1
    //  Lengthen A
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status1,X to A
    //  STore A to DisplayInfo::Status1
    //  LoaD CharStruct::Status3,X to A
    //  STore A to DisplayInfo::Status3
    //  LoaD CharStruct::CurMP,X to A
    //  STore A to DisplayInfo::CurMP
    //  Clear A, then Shorten
    //  BRAnch to [Matches]

    //  [Disabled]	(if character has become disabled while their menu is open, close the menu)
    //  LoaD DisplayInfo::CurrentChar to A
    //  STore A to MenuCurrentChar
    //  LoaD GearChanged to A
    //  Branch to next label if EQuals
    //  Store Zero to GearChanged
    //  Jump to SubRoutine ReplaceHands
    //  Jump to SubRoutine ApplyGear

    //  [LBL] lda DisplayInfo::CurrentChar
    //  STore A to MenuCurrentChar
    //  LoaD MenuDataC1::MenuOpen to A
    //  Branch to WaitMenu if EQuals
    //  LoaD #$01 to A	(C1 routine: close menu)
    //  Jump to SubRoutine CallC1

    //  [WaitMenu]
    //  LoaD MenuDataC1::MenuOpen to A
    //  Branch to WaitMenu if Not Equals	(ends up 0 eventually? via interrupts?)
    //  LoaDda #$FF to A
    //  STore A to DisplayInfo::CurrentChar
    //  Return To Subroutine

    //  [Matches]	(data either already matched or has been updated)
    //  LoaD ControllingA to A
    //  Branch to [Ret] if EQuals
    //  LoaD DisplayInfo::CurrentChar to A
    //  Transfer A to X
    //  LoaD ControlTarget,X to A
    //  Branch to next label if EQuals
    //  Transfer A to X
    //  LoaD ActiveParticipants,X to A
    //  Branch to [Ret] if Not Equals

    //  [LBL] LoaD DisplayInfo::CurrentChar
    //  STore A to MenuCurrentChar
    //  LoaD MenuDataC1::MenuOpen to A
    //  Branch to [WaitMenu2] if EQuals
    //  LoaD #$01 to A	(C1 routine: close menu)
    //  Jump to SubRoutine CallC1

    //  [WaitMenu2]
    //  LoaD MenuDataC1::MenuOpen to A
    //  Branch to [WaitMenu2] if Not Equals	(ends up 0 eventually? via interrupts?)
    //  LoaD #$80 to A
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
    //  BRAnch to [MenuClosed]

    //  [Ret] Return To Subroutine

    //  [MenuClosed]
    //  LoaD DisplayInfo::CurrentChar to A
    //  CoMPare A with #$FF
    //  Branch to [NoCurrentChar] if EQuals
    //  JuMP to ProcessMenuCommand

    //  [NoCurrentChar]:
    //  LoaD ATBReadyQueue to A
    //  CoMPare A with #$FF
    //  Branch to [NextReadyATB] if Not Equals
    //  Return To Subroutine		(no one else in queue either)

    //  [NextReadyATB]	(there's a character in the queue with ATB ready)
    //  PusH A
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X

    //  [AdvanceQueue]	(advances all the queue elements up by one, there's a terminator $FF in the 5th slot)
    //  LoaD ATBReadyQueue+1,X to A
    //  STore A to ATBReadyQueue,X
    //  INcrement X
    //  ComPare X with #$0004
    //  Branch to AdvanceQueue if Not Equals
    //  DECrement ATBReadyCount
    //  PulL A
    //  STore A to MenuCurrentChar
    //  STore A to DisplayInfo::CurrentChar
    //  Jump to SubRoutine CalculateCharOffset
    //  LoaD QuickTurns to A
    //  Branch to [DontStopTime] if EQuals
    //  LoaD DisplayInfo::CurrentChar to A
    //  CoMPare A with QuickCharIndex
    //  Branch to [DontStopTime] if EQuals
    //  Jump to SubRoutine GetTimerOffset  	(sets Y to Timer offset)
    //  LoaD CurrentTimer::ATB,Y to A
    //  Branch to FinishEarly if Not Equals	(check if frozen char's ATB is ready)
    //  LoaD #$01 to A		(increase ATB to 1 (no longer ready))
    //  STore A to CurrentTimer::ATB,Y
    //  STore A to EnableTimer::ATB,Y
    //  BRAnch to [FinishEarly]

    //  [DontStopTime]
    //  Jump to SubRoutine CheckDisablingStatus
    //  Branch to [NotDisabled] if EQuals

    //  [FinishEarly]
    //  LoaD #$FF to A
    //  STore A to DisplayInfo::CurrentChar
    //  Return To Subroutine

    //  [NotDisabled]	(character's turn has just come up)
    //  Store Zero to MenuCurrentChar+1
    //  Jump to SubRoutine ApplyBerserkStatus
    //  Branch to [FinishEarly] if Not Equals
    //  Jump to SubRoutine DisableCommandsMagic
    //  LoaD #$01 to A
    //  STore A to ATBWaiting
    //  LoaD ATBWaitTime to A
    //  STore A to ATBWaitLeft
    //  Lengthen A
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status1,X to A	(includes 2)
    //  STore A to DisplayInfo::Status1
    //  LoaD CharStruct::Status3,X to A	(includes 4)
    //  STore A to DisplayInfo::Status3
    //  LoaD CharStruct::CurMP,X to A
    //  STore A to DisplayInfo::CurMP
    //  Store Zero to CharStruct::CmdStatus,X	(also damagemod)
    //  Clear A, then Shorten
    //  Jump to SubRoutine CheckControlTargetActive
    //  LoaD #$01 to A
    //  STore A to FleeTickerActive	;can't start running until first atb
    //  LoaD EncounterInfo::IntroFX to A
    //  Branch to [NoCredits] if PLus
    //  Store Zero to MenuData::MenuOpen
    //  Return To Subroutine

    //  [NoCredits]
    //  LoaD DisplayInfo::CurrentChar to A
    //  Jump to SubRoutine GetTimerOffset	(Y = Timer offset)
    //  LoaD EnableTimer::ATB,Y to A
    //  Branch to [TimerOff] if EQuals
    //  LoaD #$FF to A
    //  STore A to DisplayInfo::CurrentChar
    //  JuMP to NoCurrentChar

    //  [TimerOff]
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine CallC1 	(C1 routine $00: open menu)

    //  [WaitMenu3]
    //  LoaD MenuDataC1::MenuOpen to A
    //  Branch to WaitMenu3 if EQuals
    //  Return To Subroutine

    //  [ProcessMenuCommand]
    //  Store Zero to ATBWaiting
    //  Jump to SubRoutine ProcessMenuCommandData
    //  LoaD #$FF to A	(no current char)
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
    //  LoaD to A DisplayInfo::CurrentChar
    //  Transfer A to X
    //  LoaD to A ControlTarget,X
    //  Branch to [Finish] if EQuals
    //  Transfer A to Y
    //  LoaD to A ActiveParticipants,Y
    //  Branch to [Finish] if EQuals
    //  LoaD to A #$01
    //  STore A to ControllingA

    //  [Finish] STore A to ControllingB
    //  Return To Subroutine
}

// Address: _1926
// copies command data from MenuData struct into CharStruct,
// and performs any other necessary processing
// Also handles gear changes, removing control when needed,
// consuming items when used, and action delays
static void processMenuCommandData(void) {
    //  LoaD EncounterInfo::IntroFX to A
    //  Branch to next label if PLus		(check for credits demo)
    //  Jump to SubRoutine SetupCreditsDemo

    //  [LBL] LoaD DisplayInfo::CurrentChar
    //  STore A to CurrentChar
    //  LoaD GearChanged to A
    //  Branch to next label if EQuals
    //  Store Zero to GearChanged
    //  Jump to SubRoutine ReplaceHands
    //  Jump to SubRoutine ApplyGear

    //  [LBL] LoaD DisplayInfo::CurrentChar
    //  Jump to SubRoutine CalculateCharOffset
    //  LoaD CharStruct::Status1,X to A
    //  AND A with #$C0	(dead/stone)
    //  Branch to [ClearControl] if Not Equals
    //  LoaD CharStruct::Status2,X to A
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$78	(sleep/para/charm/berserk)
    //  Branch to [ClearControl] if Not Equals
    //  LoaD CharStruct::Status3,X to A
    //  AND A with #$10	(stop)
    //  Branch to [ClearControl] if Not Equals
    //  LoaD CharStruct::Status4,X to A
    //  AND A with #$80	(erased)
    //  Branch to next label if EQuals

    //  [ClearControl]
    //  LoaD DisplayInfo::CurrentChar to A
    //  Transfer A to X
    //  Store Zero to ControlTarget,X
    //  BRAnch to ClearMenuData

    //  [LBL] LoaD DisplayInfo::CurrentChar to A
    //  CoMPare A with MenuData::CurrentChar
    //  Branch to next label if EQuals
    //  LoaD EncounterInfo::IntroFX to A
    //  Branch to next label is MInus		(branch if credits fight)
    //  LoaD #$0D to A	(C1 Routine)
    //  Jump to SubRoutine CallC1

    //  [WaitForever]
    //  BRAnch to [WaitForever]	(infinite loop?)

    //  [LBL] LoaD DisplayInfo::CurrentChar to A
    //  Transfer A to X
    //  LoaD ControlTarget,X to A
    //  Branch to NoControlTarget if EQuals
    //  Transfer A to Y
    //  LoaD ActiveParticipants,Y to A
    //  Branch to [ClearMenuData] if EQuals
    //  INCrement ControlCommand,X
    //  SEt Carry flag
    //  LoaD ControlTarget,X to A
    //  SuBtract #$04 from A with Carry
    //  STore A to $0E		(monster index of control target)
    //  Transfer A to Y
    //  LoaD DisplayInfo::CurrentChar to A
    //  Transfer A to X
    //  CLear Carry
    //  LoaD f:_d0eedb,X to A	(size of CharControl struct)
    //  ADd MenuData::SelectedItem to A with Carry	(action 0-3)
    //  Transfer A to X
    //  LoaD CharControl::Actions,X to A
    //  STore A to MonsterControlActions,Y
    //  SEt Carry flag
    //  LoaD $0E to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD MenuData::PartyTargets to A
    //  STore A to ForcedTarget::Party,X
    //  LoaD MenuData::MonsterTargets to A
    //  STore A to ForcedTarget::Monster,X

    //  [ClearMenuData]
    //  LoaD #$80 to A
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
    //  BRAnch to [CopyCommands]

    //  [NoControlTarget]
    //  LoaD ControllingB to A
    //  Branch to ClearMenuData if Not Equals	(controlling with no target)

    //  [CopyCommands]
    //  LoaD DisplayInfo::CurrentChar to A
    //  Transfer A to X
    //  STore X to $2A
    //  LoaD #$028A to X   	(650, size of CharSpells struct)
    //  STore X to $2C
    //  Jump to SubRoutine Multiply_16bit	(not using the rom *650 table?)
    //  Lengthen A
    //  CLear Carry
    //  LoaD $2E to A		(CurrentChar * 650)
    //  ADd #$2D34 to A with Carry   	(CharSpells struct location)
    //  STore A to TempSpellOffset
    //  Clear A, then Shorten
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status2,X to A
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$18	;charm/berserk
    //  Branch to CheckCommand if Not Equals
    //  LoaD MenuData::Command to A
    //  STore A to CharStruct::Command,X
    //  LoaD MenuData::MonsterTargets to A
    //  STore A to CharStruct::MonsterTargets,X
    //  LoaD MenuData::PartyTargets to A
    //  STore A to CharStruct::PartyTargets,X
    //  LoaD MenuData::SelectedItem to A
    //  STore A to CharStruct::SelectedItem,X
    //  LoaD MenuData::ActionFlag to A
    //  STore A to CharStruct::ActionFlag,X
    //  AND A with #$20	;magic
    //  Branch to [NotXMagic] if EQuals
    //  LoaD MenuData::SelectedItem to A
    //  Transfer A to Y
    //  LoaD (TempSpellOffset),Y to A
    //  STore A to CharStruct::SelectedItem,X
    //  LoaD MenuData::ActionFlag to A
    //  AND A with #$08	;x-magic
    //  Branch to [NotXMagic] if EQuals
    //  LoaD MenuData::SecondCommand to A
    //  STore A to CharStruct::SecondCommand,X
    //  LoaD MenuData::SecondMonsterTargets to A
    //  STore A to CharStruct::SecondMonsterTargets,X
    //  LoaD MenuData::SecondPartyTargets to A
    //  STore A to CharStruct::SecondPartyTargets,X
    //  LoaD MenuData::SecondSelectedItem to A
    //  Transfer A to Y
    //  LoaD (TempSpellOffset),Y to A
    //  STore A to CharStruct::SecondSelectedItem,X
    //  LoaD MenuData::SecondActionFlag to A
    //  STore A to CharStruct::SecondActionFlag,X
    //  BRAnch to CheckCommand

    //  [NotXMagic]
    //  Store Zero to CharStruct::SecondCommand,X
    //  Store Zero to CharStruct::SecondMonsterTargets,X
    //  Store Zero to CharStruct::SecondMonsterTargets,X	(**bug: PartyTargets)
    //  Store Zero to CharStruct::SecondSelectedItem,X
    //  Store Zero to CharStruct::SecondActionFlag,X

    //  [CheckCommand]
    //  LoaD MenuData::Command to A
    //  STore A to $24
    //  LoaD #$08 to A
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit
    //  LoaD $26 to X		(command * 8)
    //  LoaD AttackerOffset to Y
    //  LoaD f:BattleCmdProp+2,X to A
    //  STore A to CharStruct::CmdStatus,Y
    //  LoaD f:BattleCmdProp+3,X to A
    //  STore A to CharStruct::DamageMod,Y
    //  LoaD MenuData::Command to A
    //  CoMPare A with #$2C	(first magic command)
    //  Branch to [NotMagicCommand] if Carry Cleared
    //  CoMPare A with #$4E	(after last magic command)
    //  Branch to [NotMagicCommand] if Carry Set
    //  LoaD CharStruct::ActionFlag,Y to A
    //  OR A with #$01     	(costs MP)
    //  STore A to CharStruct::ActionFlag,Y

    //  [NotMagicCommand]
    //  LoaD MenuData::Command to A
    //  Transfer A to X
    //  LoaD f:BattleCmdDelay,X to A
    //  Branch to CalculateDelay if MInus
    //  PusH A
    //  LoaD MenuData::Command to A
    //  CoMPare A with #$11	(throw)
    //  Branch to [Item] if EQuals
    //  CoMPare A with #$20	(drink)
    //  Branch to [Item] if EQuals
    //  CoMPare A with #$1F	(mix)
    //  Branch to [NotItem] if Not Equals

    //  [Mix]
    //  LoaD MenuData::SecondSelectedItem to A
    //  PusH A
    //  Transfer A to X
    //  LoaD InventoryItems,X to A
    //  LoaD AttackerOffset to X
    //  STore A to CharStruct::SecondSelectedItem,X
    //  PulL A
    //  Jump to SubRoutine ConsumeItem

    //  [Item]
    //  LoaD MenuData::SelectedItem to A
    //  PusH A
    //  Transfer A to X
    //  LoaD InventoryItems,X to A
    //  LoaD AttackerOffset to X
    //  STore A to CharStruct::SelectedItem,X
    //  PulL A
    //  Jump to SubRoutine ConsumeItem

    //  [NotItem]
    //  PulL A
    //  JuMP to [Finish]

    //  [CalculateDelay]
    //  LoaD MenuData::ActionFlag to A
    //  AND A with #$08	;XMagic
    //  Branch to next label if EQuals
    //  JuMP to MagicDelay

    //  [LBL] LoaD MenuData::ActionFlag
    //  AND A with #$40	;Item
    //  Branch to ItemDelay if Not Equals
    //  LoaD MenuData::ActionFlag to A
    //  AND A with #$20	;Magic
    //  Branch to next label if EQuals
    //  JuMP to MagicDelay

    //  [LBL] LoaD MenuData::ActionFlag to A
    //  AND A with #$10	;Weapon used as item
    //  Branch to [WeaponAttackDelay] if EQuals
    //  JuMP to WeaponUseDelay

    //  [WeaponAttackDelay]	(despite the calculation, I don't think any weapons have delay values)
    //  Store Zero to $0E
    //  LoaD DisplayInfo::CurrentChar to A
    //  STore A to $24
    //  LoaD #$54 to A     (84, size of GearStats struct)
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit
    //  LoaD $26 to Y
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::RHWeapon,X to A
    //  Branch to next label if EQuals
    //  LoaD RHWeapon::Targetting,Y to A
    //  AND A with #$03	(delay bits; delay/10)
    //  Transfer A to X
    //  LoaD f:AttackDelayTbl,X to A
    //  STore A to $0E		(attack delay)

    //  [LBL] LoaD AttackerOffset to X
    //  LoaD CharStruct::LHWeapon,X to A
    //  Branch to next label if EQuals
    //  LoaD LHWeapon,Y to A
    //  AND A with #$03	(delay bits; delay/10)
    //  Transfer A to X
    //  CLear Carry
    //  LoaD f:AttackDelayTbl,X to A
    //  ADd $0E to A with Carry		(add other weapon's delay)
    //  STore A to $0E

    //  [LBL] lda $0E		(attack delay)
    //  JuMP to Finish

    //  [ItemDelay]
    //  LoaD MenuData::SelectedItem to A
    //  Transfer A to X
    //  LoaD InventoryItems,X to A
    //  LoaD AttackerOffset to X
    //  STore A to CharStruct::SelectedItem,X
    //  SEt Carry flag
    //  SuBtract #$E0 from A with Carry	(consumable item offset)
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:ConsumableItemProp+2,X to A
    //  AND A with #$08
    //  Branch to next label if Not Equals
    //  LoaD MenuData::SelectedItem to A
    //  Jump to SubRoutine ConsumeItem

    //  [LBL] lda f:ConsumableItemProp,X
    //  AND A with #$03	(delay bits; delay/10)
    //  Transfer A to X
    //  LoaD f:AttackDelayTbl,X to A
    //  BRAnch to Finish

    //  [MagicDelay]
    //  Store Zero to $0E
    //  LoaD MenuData::SelectedItem to A
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:AttackProp,X to A
    //  AND A with #$03	(delay bits; delay/10)
    //  Transfer A to X
    //  LoaD f:AttackDelayTbl,X to A
    //  STore A to $0E		(attack delay)
    //  LoaD MenuData::ActionFlag to A
    //  AND A with #$08	;X-Magic
    //  Branch to [FinishMagic] if EQuals
    //  LoaD MenuData::SecondSelectedItem to A
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:AttackProp,X to A
    //  AND A with #$03	(delay bits; delay/10)
    //  Transfer A to X
    //  CLear Carry
    //  LoaD f:AttackDelayTbl,X to A
    //  ADd $0E to A with Carry		(add other spell's delay)
    //  STore A to $0E

    //  [FinishMagic]
    //  LoaD $0E to A		(attack delay)
    //  BRAnch to [Finish]

    //  [WeaponUseDelay]
    //  LoaD DisplayInfo::CurrentChar to A
    //  STore A to $24
    //  LoaD #$54 to A     	(84, size of GearStats struct)
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit
    //  LoaD $26 to Y
    //  LoaD MenuData::SelectedItem to A
    //  Branch to next label if EQuals
    //  Lengthen A
    //  Transfer Y to A
    //  CLear Carry
    //  ADd #$000C to A with Carry	(shifts offset from RHWeapon to LHWeapon)
    //  Transfer A to Y
    //  Clear A, then Shorten

    //  [LBL] LoaD RHWeapon::ItemMagic,Y to A	(could be LHWeapon)
    //  AND A with #$7F	;weapon magic to cast
    //  Branch to [Finish] if EQuals
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:AttackProp,X to A
    //  AND A with #$03	(delay bits; delay/10)
    //  Transfer A to X
    //  LoaD f:AttackDelayTbl,X to A

    //  [Finish]
    //  PusH A
    //  LoaD DisplayInfo::CurrentChar to A
    //  Jump to SubRoutine GetTimerOffset	(Y AND A with $36 = timer offset)
    //  LoaD AttackerOffset to X
    //  PulL A
    //  Jump to SubRoutine HasteSlowMod	(adjusts delay)
    //  STore A to CurrentTimer::ATB,Y	(time until action fires)
    //  LoaD #$41 to A		(flag indicating a queued action)
    //  STore A to EnableTimer::ATB,Y
    //  LoaD #$80 to A		(physical/other)
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
    // LoaD InventoryQuantities,X to A
    // DECrement A
    // STore A to InventoryQuantities,X
    // Branch to [Ret] if Not Equals
    // STore Zero to InventoryItems,X
    // STore Zero to InventoryTargetting,X
    // LoaD #$5A to A
    // STore A to InventoryFlags,X
    // LoaD #$AA to A
    // STore A to InventoryUsable,X
    // [Ret] Return to SubRoutine
}

// Address: _1C51
// Initializes some values when a
// battle during the credits happens
// This range is used by C1 graphics code but
// unsure what it does
static void setupCreditsDemo(void) {
    // LoaD #$80 to A	(physical/other)
    // STore A to MenuData::ActionFlag
    // STore A to MenuData::MonsterTargets
    // LoaD #$54 to A	(job-specific animation (credits))
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
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Status1,X to A
    // OR A with CharStruct::AlwaysStatus1,X
    // AND A with #$C2   	(dead/stone/zombie)
    // Branch to [Ret] if Not Equals
    // LoaD CharStruct::Status2,X to A
    // OR A with CharStruct::AlwaysStatus2,X
    // AND A with #$78   	(sleep/para/Charm/Berserk)
    // Branch to [Ret] if Not Equals
    // LoaD CharStruct::Status3,X to A
    // AND A with #$10   	(stop)
    // Branch to [Ret] if Not Equals
    // LoaD CharStruct::Status4,X to A
    // AND A with #$84   	(erased/singing)
    // Branch to [Ret] if Not Equals
    // Transfer Direct page to aCcumulator
    // [Ret] Return to SubRoutine
)

// Address: _1C9A
// Make Berserk ability have Berserk Status
static void applyBerserkStatus(void) {
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Passives2,X to A
    //  AND A with #$08   	(berserk)
    //  Branch to [Finish] if EQuals
    //  LoaD EncounterInfo::IntroFX to A
    //  Branch to [NotCredits] if PLus

    //  [Finish] Transfer Direct page to aCcumulator
    //  Return To Subroutine

    //  [NotCredits]
    //  LoaD CharStruct::AlwaysStatus2,X to A
    //  OR A with #$08   	(berserk)
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
    //  LoaD Void to A
    //  AND A with #$40     	(void)
    //  Branch to next label if EQuals
    //  LoaD #$0080 to X
    //  STore X to $16		(disables magic)

    //  [LBL] LoaD DisplayInfo::CurrentChar
    //  Jump to SubRoutine CalculateSpellOffset	(sets Y)
    //  Lengthen A
    //  Transfer Direct page to aCcumulator
    //  STore A to $12
    //  STore A to $14
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::CurMP,X to A
    //  STore A to $0E		(current mp)
    //  LoaD CharStruct::Status3,X to A
    //  OR A with CharStruct::AlwaysStatus3,X
    //  STore A to $22		(status 3/4)
    //  LoaD CharStruct::Status1,X to A
    //  OR A with CharStruct::AlwaysStatus1,X
    //  STore A to $10		(status 1/2)
    //  AND A with #$0400	(mute)
    //  Branch to next label if EQuals
    //  LoaD #$0080 to A
    //  STore A to $12		(disables magic)

    //  [LBL] LoaD CharStruct::Status1,X
    //  OR A with CharStruct::AlwaysStatus1,X
    //  AND A with #$0020	(toad)
    //  Branch to next label if EQuals
    //  LoaD #$0080 to A
    //  STore A to $14		(disables magic)
    //  [LBL] Transfer Direct page to aCcumulator
    //  Transfer A to X

    //  [DisableSpells]
    //  LoaD CharSpells::Flags,Y to A
    //  AND A with #$0001	(skip mp/status checks)
    //  Branch to [NextSpell] if Not Equals
    //  LoaD CharSpells::MP,Y to A
    //  AND A with #$00FF	(clear high part since it's an 8 bit field)
    //  CoMPare A with $0E		(current mp)
    //  Branch to [CheckStatus] if EQuals
    //  Branch to [CheckStatus] if Carry Clear
    //  LoaD CharSpells::Flags,Y to A
    //  OR A with #$0080
    //  STore A to CharSpells::Flags,Y
    //  BRAnch to [NextSpell]

    //  [CheckStatus]
    //  LoaD CharSpells::Flags,Y to A
    //  AND A with #$FF7F	(clear bit 80h in flags, disabled bit?)
    //  STore A to CharSpells::Flags,Y
    //  LoaD CharSpells::ID,Y to A
    //  AND A with #$00FF
    //  CoMPare A with #$0080	(blue magic)
    //  Branch to [NextSpell] if Carry Set
    //  LoaD CharSpells::Flags,Y to A
    //  OR A with $12		(from mute)
    //  OR A with $14		(from toad)
    //  OR A with $16		(from void)
    //  STore A to CharSpells::Flags,Y
    //  LoaD $16 to A
    //  Branch to [NextSpell] if Not Equals
    //  LoaD $12 to A
    //  Branch to [NextSpell] if Not Equals
    //  LoaD $14 to A
    //  Branch to [NextSpell] if EQuals
    //  LoaD CharSpells::ID,Y to A
    //  AND A with #$00FF
    //  CoMPare A with #$0029	(toad spell)
    //  Branch to [NextSpell] if Not Equals
    //  LoaD CharSpells::Flags,Y to A
    //  AND A with #$FF7F	(re-enable toad spell if toad status)
    //  STore A to CharSpells::Flags,Y

    //  [NextSpell]
    //  INcrement Y
    //  INcrement X
    //  ComPare X with #$0082	(130 spell slots)
    //  Branch to [DisableSpells] if Not Equals
    //  Clear A, then Shorten
    //  LoaD DisplayInfo::CurrentChar to A
    //  STore A to $24
    //  LoaD #$14	(20, size of CharCommands struct) to A
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  STore X to $0E
    //  LoaD $26 to Y
    //  Lengthen A

    //  [DisableCommands]
    //  LoaD CharCommands::ID,Y to A
    //  AND A with #$00FF
    //  STore A to $12		(command id)
    //  Branch to [DisableCommand] if EQuals
    //  A Shift Left
    //  Transfer A to X
    //  LoaD f:BattleCmdDisableStatus,X to A
    //  AND A with $10		(status 1/2)
    //  Branch to [DisableCommand] if Not Equals
    //  LoaD $12		(command id) to A
    //  CoMPare A with #$0026	(show command)
    //  Branch to [EnableCommand] if EQuals
    //  LoaD $22		(status 3/4) to A
    //  AND A with #$0100	(hidden)
    //  Branch to [EnableCommand] if EQuals

    //  [DisableCommand]
    //  LoaD CharCommands::Flags,Y to A
    //  OR A with #$0080	(disabled)
    //  STore A to CharCommands::Flags,Y
    //  BRAnch to [NextCommand]

    //  [EnableCommand]
    //  LoaD CharCommands::Flags,Y to A
    //  AND A with #$FF7F	(enabled)
    //  STore A to CharCommands::Flags,Y

    //  [NextCommand]
    //  INcrement Y
    //  INCrement $0E		(character index)
    //  LoaD $0E to A
    //  CoMPare A with #$0004	(4 commands per character)
    //  Branch to DisableCommands if Not Equals
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
    //  STore X to $3D		(char index, used in subroutines also)
    //  STore X to $3F		(char offset)

    //  [Loop]
    //  LoaD $3D to X
    //  LoaD UncontrolledATB,X to A
    //  Branch to [ActionReady] if EQuals
    //  LoaD $3F to X
    //  LoaD CharStruct::Status3,X to A
    //  AND A with #$10	(stop)
    //  Branch to [Next] if Not Equals
    //  LoaD CharStruct::Status2,X to A
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$60	(sleep/paralyze)
    //  Branch to [Next] if Not Equals
    //  LoaD $3D to X
    //  DECrement UncontrolledATB,X
    //  BRAnch to [Next]

    //  [ActionReady]
    //  LoaD $3F to X		(char offset)
    //  LoaD #$01 to A
    //  STore A to CharStruct::CmdCancelled,X
    //  LoaD CharStruct::Status1,X to A
    //  OR A with CharStruct::AlwaysStatus1,X
    //  AND A with #$02	(zombie)
    //  Branch to next label if EQuals
    //  Jump to SubRoutine ZombieAction
    //  BRAnch to [Next]

    //  [LBL] lda CharStruct::Status2,X
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$10	(charm)
    //  Branch to next label if EQuals
    //  Jump to SubRoutine CharmAction
    //  BRAnch to [Next]

    //  [LBL] lda CharStruct::Status2,X
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$08	(berserk)
    //  Branch to [Next] if EQuals
    //  Jump to SubRoutine BerserkAction

    //  [Next]
    //  LoaD $3F to X		(char offset)
    //  Jump to SubRoutine NextCharOffset
    //  STore X to $3F
    //  INCrement a:$003D	(char index ; TODO: dont know why this is being done?)
    //  LoaD a:$003D to A
    //  CoMPare A with #$04	(4 characters)
    //  Branch to [Loop] if Not Equals
    //  Return To Subroutine
}

// Address: _1E2F
// Params
//  - X = Char Offset
//  - $3D = Char index
// Sets up a fight command targetting
// a Random party member
static void zombieAction(void) {
    // LoaD #$80 to A
    // STore A to CharStruct::ActionFlag,X
    // LoaD #$05 to A	(fight)
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
    // LoaD #$03 to A
    // Jump to SubRoutine Random_X_A  (0..3)
    // Transfer A to X
    // Transfer Direct page to aCcumulator
    // Jump to SubRoutine SetBit_X
    // PulL X
    // STore A to CharStruct::PartyTargets,X	(fight random party member)
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
    //  LoaD CharStruct::EnableSpells,X to A
    //  AND A with #$0F			(white magic)
    //  OR A with CharStruct::EnableSpells+1,X	(black and time magic)
    //  Branch to [Fight] if EQuals
    //  Jump to SubRoutine Random_0_99
    //  CoMPare A with #$32	(50% chance of spell)
    //  Branch to [Magic] if Carry Clear

    //  [Fight]
    //  LoaD $3F to X		(char offset)
    //  LoaD #$80 to A
    //  STore A to CharStruct::ActionFlag,X
    //  LoaD #$05 to A	(fight)
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
    //  LoaD #$03 to A
    //  Jump to SubRoutine Random_X_A    (0..3)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  PulL X
    //  STore A to CharStruct::PartyTargets,X	(fight random party member)
    //  JuMP to _QueueUncontrolledAction

    //  [Magic]
    //  LoaD $3D to A		(char index)
    //  Transfer A to X
    //  STore X to $2A
    //  LoaD #$028A to X    (TODO: fixme .sizeof(CharSpells);	650, size of CharSpells struct)
    //  STore X to $2C
    //  Jump to SubRoutine Multiply_16bit    (**optimize: use rom table instead)
    //  LoaD $2E to X
    //  STore X to SpellOffsetRandom
    //  Store Zero to $0E

    //  [FindAnySpell]		(checks if any spells are learned)
    //  LoaD CharSpells::ID+18,X to A	(starts at first white spell)
    //  CoMPare A with #$46		(Quick spell)
    //  Branch to NextSpell if EQuals
    //  CoMPare A with #$FF		(empty spell slot)
    //  Branch to [TryRandomSpell] if Not Equals

    //  [NextSpell]
    //  INcrement X
    //  INCrement $0E
    //  LoaD $0E to A
    //  CoMPare A with #$36
    //  Branch to FindAnySpell if Not Equals
    //  BRAnch to Fight		(no spells, hit something instead)

    //  [TryRandomSpell]
    //  LoaD #$0012 to X		(first white spell)
    //  LoaD #$47 to A		(last time spell)
    //  Jump to SubRoutine Random_X_A  	(random white/black/time spell)
    //  Lengthen A
    //  ADd SpellOffsetRandom to A with Carry
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD CharSpells::ID,X to A
    //  CoMPare A with #$FF		(empty spell slot)
    //  Branch to [TryRandomSpell] if EQuals	(keep trying until we hit a known spell)
    //  CoMPare A with #$46		(quick spell)
    //  Branch to [TryRandomSpell] if EQuals	(is no good either)
    //  PusH A 			(holds known random spell)
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:AttackProp,X to A
    //  STore A to TempTargetting	(temp area)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  STore Y to $16			(target bits)
    //  LoaD TempTargetting to A
    //  Branch to [CheckTargetting] if Not Equals

    //  [TargetSelf]
    //  Lengthen A
    //  LoaD $3F to A			(Char Offset)
    //  Jump to SubRoutine ShiftDivide_128	(char index; could've just loaded that)
    //  Transfer A to X
    //  Clear A, then Shorten
    //  Jump to SubRoutine SetBit_X     	(target self if no targetting info)
    //  STore A to $16
    //  BRAnch to TargetReady

    //  [CheckTargetting]
    //  AND A with #$40		(hits all)
    //  Branch to [TargetsAll] if Not Equals
    //  LoaD TempTargetting to A
    //  AND A with #$08		(targets enemy by default)
    //  Branch to [TargetsEnemy] if Not Equals

    //  [TargetsOther]			(assumed to normally target party, now targets monsters)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$07 to A
    //  Jump to SubRoutine Random_X_A	     	(random monster 0..7)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to $17			(monster target)
    //  BRAnch to TargetReady

    //  [TargetsEnemy]			(normally targets enemy, now targets party)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$03 to A
    //  Jump to SubRoutine Random_X_A    	(random party 0..3)
    //  Transfer A to X
    //  Transfer Direct page to aCcumulator
    //  Jump to SubRoutine SetBit_X
    //  STore A to $16			(party target)
    //  BRAnch to [TargetReady]

    //  [TargetsAll]
    //  LoaD TempTargetting to A
    //  AND A with #$08		(targets enemy by default)
    //  Branch to next label if Not Equals
    //  LoaD #$FF to A
    //  STore A to $17
    //  BRAnch to [TargetReady]

    //  [LBL] LoaD #$F0		(target all party members)
    //  STore A to $16

    //  [TargetReady]:
    //  LoaD $3F to X 		(char Offset)
    //  PulL A 			(random known spell)
    //  STore A to CharStruct::SelectedItem,X
    //  LoaD $16 to A			(party targets)
    //  STore A to CharStruct::PartyTargets,X
    //  LoaD $17 to A			(monster targets)
    //  STore A to CharStruct::MonsterTargets,X
    //  LoaD #$21 to A		(magic + costs mp)
    //  STore A to CharStruct::ActionFlag,X
    //  LoaD #$2C to A		(first magic command)
    //  STore A to CharStruct::Command,X
    //  Store Zero to CharStruct::SecondActionFlag,X
    //  Store Zero to CharStruct::SecondCommand,X
    //  Store Zero to CharStruct::SecondMonsterTargets,X
    //  Store Zero to CharStruct::SecondPartyTargets,X
    //  Store Zero to CharStruct::SecondSelectedItem,X

    //  [_QueueUncontrolledAction]
    //  JuMP to QueueUncontrolledAction
}

// Address: _1F80
// Params:
// - X = Char Offset
// - $3D = Char index
// Sets up a fight command targetting a
// random party member
static void berserkAction(void) {
    // LoaD #$80 to A
    // STore A to CharStruct::ActionFlag,X
    // LoaD #$05 to A	(fight)
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
    // LoaD #$07 to A
    // Jump to SubRoutine Random_X_A	(0..7 random monster)
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
    //  LoaD $3D to A		(char index)
    //  Jump to SubRoutine ResetATB   	(also sets Y = timer offset)
    //  LoaD $3D to A
    //  Transfer A to X
    //  LoaD CurrentTimer::ATB,Y to A
    //  CoMPare A with #$7F
    //  Brach to next label if Carry Clear
    //  LoaD #$7F to A	    (max ATB 127)

    //  [LBL] STore A to UncontrolledATB,X
    //  LoaD #$01 to A	    (action on next ATB tick)
    //  STore A to CurrentTimer::ATB,Y
    //  LoaD #$41 to A    	(waiting for delayed action)
    //  STore A to EnableTimer::ATB,Y
    //  Return to SubRoutine
}

// Address: _1FD2
// Randomizes a table of combatant numbers,
// also initializes global timers
static void randomizeOrder(void) {
    //  LoaD CurrentlyReacting to A
    //  Branch to next label if Not Equals
    //  Jump to SubRoutine GlobalTimers

    //  [LBL] Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  DECrement

    //  [LBL] STore A to RandomOrder,X
    //  INcrement X
    //  ComPare X with #$000C
    //  Branch to previous label if Not Equals

    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y 			(slot for writing)

    //  [_RandomizeOrder]
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X 			(slot for reading)
    //  LoaD #$0B to A
    //  Jump to SubRoutine Random_X_A		(0..11)
    //  STore A to $0E
    //  LoaD #$0000 to X

    //  [CheckValueInUse]		(see if we've used this number yet)
    //  LoaD $0E to A
    //  CoMPare A with RandomOrder,X
    //  Brach to [_Next] if EQuals		(already used, try another)
    //  INcrement X
    //  ComPare X with #$000C
    //  Brach to [CheckValueInUse] if Not Equals

    //  STore A to RandomOrder,Y	(if not, save it)
    //  INcrement Y 			    (and select next writing slot)

    //  [_Next]
    //  ComPare Y with #$000C		(12 combatant slots)
    //  Brach to [_RandomizeOrder] if Not Equals

    //  Return To Subroutine
}

// Address: _200B
// Updates Status/ATB timers for all combatants
// may skip updates depending on stop/etc.
static void updateTimers(void) {
    //  Jump to SubRoutine GlobalTimers
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  STore X to $0A     		(char index)

    //  [Loop] Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  STore Y to $0C     		(timer index)
    //  LoaD $0A to A
    //  Jump to SubRoutine GetTimerOffset
    //  Transfer Y to X 			(X = Timer Offset)
    //  LoaD $0A to Y
    //  LoaD ActiveParticipants,Y to A
    //  Brach to [NextChar] to EQuals
    //  LoaD PauseTimerChecks,Y to A
    //  Brach to [NextChar] if Not Equals
    //  LoaD CurrentlyReacting to A
    //  Branch to next label if Not Equals
    //  LoaD QuickTimeFrozen,Y to A
    //  Brach to [NextChar] if Not Equals
    //  [LBL] Jump to SubRoutine UpdateTimer 	(first timer is stop)
    //  LoaD $08 to A			(check if stop active)
    //  Brach to [NextChar] if Not Equals  		(don't process other timers if stopped)
    //  LoaD #$0008 to Y  		(process 8 more status timers)

    //  [LBL] Jump to SubRoutine UpdateTimer
    //  DEcrement Y
    //  Branch to previous label if Not Equals
    //  Jump to SubRoutine UpdateTimer 	(one more status timer for paralyze)
    //  LoaD $08 to A			(check if paralyze active)
    //  Brach to [NextChar] if Not Equals
    //  Jump to SubRoutine UpdateTimer  	(advance ATB timer if not paralyzed)

    //  [NextChar]
    //  INCrement $0A     		(next char index)
    //  LoaD $0A to A
    //  CoMPare A with #$0C		(12 combatants)
    //  Brach to [Loop] if Not Equals

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
    //  Store Zero to $08    	(timer triggered flag)
    //  PusH Y
    //  LoaD $0C to Y		(timer index)
    //  LoaD ProcessTimer,Y to A	(should process this timer this tick?)
    //  Branch to [Finish] if EQuals
    //  ComPare Y with #$000A	(ProcessTimer::ATB)
    //  Branch to next label if EQuals
    //  LoaD CurrentlyReacting to A
    //  Branch to [Finish] if Not Equals

    //  [LBL] LoaD EnableTimer,X	(is it enabled?)
    //  Branch to [Finish] if EQuals
    //  Branch to TimerActive if MInus	(check the 80h timer flag)
    //  LoaD CurrentTimer,X to A
    //  Branch to [FlagTimer] if EQuals
    //  DECrement CurrentTimer,X
    //  LoaD CurrentTimer,X to A
    //  Branch to [TimerActive] if Not Equals

    //  [FlagTimer]		(flag EnableTimer when CurrentTimer hits 0)
    //  LoaD EnableTimer,X to A
    //  OR A with #$81
    //  STore A to EnableTimer,X

    //  [TimerActive]
    //  LoaD $0C to A
    //  Branch to next label if Not Equals		(doesn't branch anywhere regardless)
    //  [LBL] INCrement $08    	(timer triggered flag)

    //  [Finish]
    //  PulL Y 		(restore original Y)
    //  INcrement X 		(next timer in offset)
    //  INCrement $0C		(next timer index)
    //  Return To Subroutine
}

// Address: _2090
// Decreases global status timers,
// then flags and reset those that trigger
// sets ProcessTimer to indicate that status
// should be updated this tick
static void globalTimers(void) {
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X

    //  [DecTimer]
    //  LoaD GlobalTimer,X to A
    //  Branch to Triggered if EQuals
    //  DECrement GlobalTimer,X
    //  Store Zero to ProcessTimer,X
    //  BRAnch to next label

    //  [Triggered]
    //  LoaD #$01 to A
    //  STore A to ProcessTimer,X		(flag timer for processing)
    //  LoaD f:TimerDurTbl,X to A		(reset timer from rom)
    //  STore A to GlobalTimer,X

    //  [LBL] INcrement X
    //  ComPare X with #$000B			(11 timers)
    //  Branch to DecTimer if Not Equals
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
    //  STore X to $08			(timer index)
    //  Transfer A to Y

    //  [LBL] STore A to TimerEnded,Y
    //  INcrement Y
    //  ComPare Y with #$000B
    //  Branch to previous label if Not Equals

    //  [TimerLoop]	(for each timer, loop finds the first character for whom that timer ended, checking in a "random" order)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  STore X to $0A			(char count)
    //  LoaD $08 to X			(timer index)
    //  LoaD RandomOrderIndex,X to A
    //  PusH A 			(original RandomOrderIndex)

    //  [CharLoop]  (searches characters in a "random" order)
    //  LoaD $08 to X			(timer index)
    //  LoaD RandomOrderIndex,X to A
    //  Transfer A to X
    //  LoaD RandomOrder,X to A
    //  STore A to $0C			(char index)
    //  Transfer A to X
    //  LoaD PauseTimerChecks,X to A
    //  Branch to [NextChar] if Not Equals
    //  LoaD CurrentlyReacting to A
    //  Branch to next label if Not Equals
    //  LoaD QuickTimeFrozen,X to A
    //  Branch to [NextChar] if Not Equals

    //  [LBL] LoaD $0C to A			(char index)
    //  Jump to SubRoutine GetTimerOffset      (Y = Timer Offset)
    //  Transfer Y to A
    //  CLear Carry
    //  ADd $08 to A with Carry
    //  Transfer A to X 			(timer offset + index)
    //  LoaD EnableTimer,X to A
    //  Branch to [NextChar] with PLus		(80h must be set to contiue)
    //  LoaD $0C to A
    //  Transfer A to Y
    //  LoaD ActiveParticipants,Y to A
    //  Branch to [NextChar] if EQuals
    //  LoaD $08 to A			(timer index)
    //  CoMPare A with #$01		(poison)
    //  Branch to [PoisonCountRegen] if EQuals
    //  CoMPare A with #$03		(countdown)
    //  Branch to [PoisonCountRegen] if EQuals
    //  CoMPare A with #$07		(regen)
    //  Branch to [EndTimer] if Not Equals

    //  [PoisonCountRegen]	(skips ending timer for these status if they're also erased/hidden/jumping)
    //  PusH X 		(timer offset + index)
    //  LoaD $08 to X
    //  LoaD RandomOrderIndex,X to A
    //  Transfer A to X
    //  LoaD RandomOrder,X to A
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_128
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD CharStruct::Status4,X to A
    //  AND A with #$81	(erased or hidden)
    //  Branch to [NextCharPLX] if Not Equals
    //  LoaD CharStruct::CmdStatus,X to A
    //  AND A with #$10	(jumping)
    //  Branch to [EndTimerPLX] if EQuals

    //  [NextCharPLX]
    //  PulL X
    //  BRAnch to NextChar

    //  [EndTimerPLX]
    //  PulL X 		(timer offset + index)

    //  [EndTimer]		(sets flag that timer has ended, so effects can be applied later)
    //  PulL A
    //  LoaD EnableTimer,X to A
    //  AND A with #$7E	(clear $81)
    //  STore A to EnableTimer,X
    //  LoaD $08 to X		(timer index)
    //  PusH X
    //  LoaD #$01 to A	(flag that we found someone timer ended for)
    //  STore A to TimerEnded,X
    //  LoaD RandomOrderIndex,X to A
    //  Transfer A to X
    //  LoaD RandomOrder,X to A
    //  PulL X 		(timer index)
    //  STore A to TimerReadyChar,X	(which character had their timer end)
    //  BRAnch to [NextTimer]	(don't check any more characters for this timer)

    //  [NextChar]	(this character's timer didn't end or isn't eligable,
    //         	     keep looking until all have been checked or one is found)
    //  LoaD $08 to X		(timer index)
    //  INCrement RandomOrderIndex,X
    //  LoaD RandomOrderIndex,X to A
    //  CoMPare A with #$0C	(reset index at 12)
    //  Branch to next label if Not Equals
    //  Store Zero to RandomOrderIndex,X

    //  [LBL] INCrement $0A        	(char count)
    //  LoaD $0A to A
    //  CoMPare A with #$0C	(12 chars)
    //  Branch to next label if EQuals
    //  JuMP to CharLoop

    //  [LBL] PulL A 		(original RandomOrderIndex)
    //  STore A to RandomOrderIndex,X

    //  [NextTimer]
    //  INCrement $08        	(next timer index)
    //  LoaD $08 to A
    //  CoMPare A with #$0B	(11 timers)
    //  Branch to [Ret] if EQuals
    //  JuMP to TimerLoop

    //  [Ret] Return To Subroutine
}

static void applyTimerEffects(void) {
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  STore X to ProcessingTimer

    //  [Loop]
    //  LoaD ProcessingTimer to X
    //  LoaD TimerEnded,X to A
    //  Branch to [NextTimer] if EQuals
    //  INCrement RandomOrderIndex,X
    //  LoaD RandomOrderIndex,X to A
    //  CoMPare A with #$0C		(12 chars)
    //  Branch to next label if Not Equals
    //  Store Zero to RandomOrderIndex,X

    //  [LBL] LoaD TimerReadyChar,X to A
    //  Jump to SubRoutine GetTimerOffset    	(sets Y to timer offset)
    //  LoaD TimerReadyChar,X to A
    //  Jump to SubRoutine CalculateCharOffset
    //  LoaD ProcessingTimer to A
    //  Branch to [TimerEffect] if EQuals    	(timer 0 is stop, skips below check)
    //  LoaD EnableTimer,Y to A	(bits 80h AND A with 01 are cleared prev)
    //  Branch to [NextTimer] Not Equals    	(skip effect if any other bits set)

    //  [TimerEffect]
    //  Jump to SubRoutine DispatchTimerEffect

    //  [NextTimer]
    //  INCrement ProcessingTimer
    //  LoaD ProcessingTimer to A
    //  CoMPare A with #$0B		(11 timers)
    //  Branch to [Loop] Not Equals
    //  Return To Subroutine
}

// Uses a jump table to call an
// appropriate timer effect routine
// Params:
// - Y = timer offset (used in the effect routines)
static void dispatchTimerEffect(void) {
    // LoaD ProcessingTimer to A
    // A Shift Left
    // Transfer A to X
    // LoaD f:TimerEffectJumpTable,X to A
    // STore A to $08
    // LoaD f:TimerEffectJumpTable+1,X to A
    // STore A to $09
    // LoaD #$c2 to A
    // STore A to $0A
    // JuMp to Long address [$0008]

    // TimerEffectJumpTable
    // .word $21E3, $21EE, $222A, $2235, $224E, $2259, $2264, $22AD, $2319, $237C, $238F
}

// Address: _21E3
static void timerEffectStop(void) {
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Status3,X to A
    // AND A with #$EF	(clear stop)
    // STore A to CharStruct::Status3,X
    // Return to SubRoutine
}

// Address: _21EE
static void timerEffectPoison(void) {
    //  LoaD #$01 To A
    //  STore A to EnableTimer::Poison,Y
    //  LoaD InitialTimer::Poison,Y to A
    //  STore A to CurrentTimer::Poison,Y
    //  Jump to SubRoutine WipeDisplayStructures
    //  Lengthen A
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::MaxHP,X to A
    //  Jump to SubRoutine ShiftDivide_16
    //  Branch to next label if Not Equals
    //  INCrement 				(min 1 damage)

    //  [LBL] STore A to $0E				(poison tick damage)
    //  SEt Carry flag
    //  LoaD CharStruct::CurHP,X to A
    //  SuBtract $0E from A with Carry				(poison tick damage)
    //  Branch to next label if Carry Set
    //  Transfer Direct page to aCcumulator 				(min 0 hp)

    //  [LBL] STore A to CharStruct::CurHP,X
    //  Clear A, then Shorten
    //  LoaD TimerReadyChar::Poison to A
    //  LoaD $0E to X				(poison tick damage)
    //  STore X to TempDisplayDamage
    //  Jump to SubRoutine CopyDisplayDamage
    //  LoaD #$09 to A	(C1 routine: display regen/poison damage)
    //  JuMP to CallC1
}

static void timerEffectReflect(void) {
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Status3,X to A
    // AND A with #$7F	(clear reflect)
    // STore A to CharStruct::Status3,X
    // Return to SubRoutine
}

static void timerEffectCountdown(void) {
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status1,X to A
    //  AND A with #$02	(zombie)
    //  Branch to Ret if Not Equals
    //  LoaD TimerReadyChar::Countdown to A
    //  Jump to SubRoutine KillCharacter
    //  LoaD MonsterDead to A
    //  Branch to [Ret] if EQuals
    //  LoaD #$07 to A	(C1 routine: condemn death animation)
    //  Jump to SubRoutine CallC1
    //  [Ret] Return to SubRoutine
}

static void timerEffectMute(void) {
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Status2,X to A
    // AND A with #$FB	(clear mute)
    // STore A to CharStruct::Status2,X
    // Return to SubRoutine
}

static void timerEffectHPLeak(void) {
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Status4,X to A
    // AND A with #$F7	(clear hp leak)
    // STore A to CharStruct::Status4,X
    // Return to SubRoutine
}

static void timerEffectOld(void) {
//  LoaD #$01 to A
//  STore A to EnableTimer::Old,Y
//  LoaD InitialTimer::Old,Y to A
//  STore A to CurrentTimer::Old,Y
//  LoaD AttackerOffset to X
//  Store Zero to $0E

//  [StatsLoop]		(applies to all 4 main stats)
//  LoaD CharStruct::BaseStr,X to A
//  DECrement
//  Branch to next label if EQuals		(**bug: wraps 0 stats to 255)
//  STore A to CharStruct::BaseStr,X

//  [LBL] LoaD CharStruct::EquippedStr,X to A
//  DECrement
//  Branch to next label if EQuals
//  STore A to CharStruct::EquippedStr,X

//  [LBL] INcrement X
//  INCrement $0E
//  LoaD $0E to A
//  CoMPare A with #$04	(4 stats)
//  Branch to [StatsLoop] if Not Equals
//  LoaD ProcessingTimer to X
//  LoaD TimerReadyChar,X to A
//  CoMPare A with #$04	(monster check)
//  Branch to [Ret] if Carry Clear
//  LoaD AttackerOffset to X
//  LoaD CharStruct::Level,X to A
//  DECrement
//  Branch to next label if EQuals
//  STore A to CharStruct::Level,X

//  [LBL] LoaD CharStruct::MonsterAttack,X to A
//  DECrement
//  Branch to [Ret] if PLus	(bug? only decreases attack if above 128)
//  STore A to CharStruct::MonsterAttack,X

//  [Ret] Return To Subroutine
}

static void timerEffectRegen(void) {
    //  LoaD #$01 to A
    //  STore A to EnableTimer::Regen,Y
    //  LoaD InitialTimer::Regen,Y to A
    //  CoMPare A with #$1E
    //  Branch to next label if Carry Set
    //  LoaD #$1E to A	(max 30 ticks if it was slower)
    //  STore A to InitialTimer::Regen,Y

    //  [LBL] STore A to CurrentTimer::Regen,Y
    //  Jump to SubRoutine WipeDisplayStructures
    //  LoaD AttackerOffset to X
    //  Jump to SubRoutine CopyStatsWithBonuses
    //  LoaD Level to A
    //  STore A to $24
    //  LoaD Vitality to A
    //  STore A to $25
    //  Jump to SubRoutine Multiply_8bit
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status1,X to A
    //  AND A with #$02	(zombie)
    //  Branch to [Ret] if Not Equals
    //  Lengthen A
    //  LoaD $26 to A
    //  Jump to SubRoutine ShiftDivide_16
    //  Transfer A to X
    //  Branch to next label if Not Equals
    //  INCrement 		(min 1)

    //  [LBL] STore A to $0E
    //  LoaD AttackerOffset to X
    //  CLear Carry
    //  ADd CharStruct::CurHP,X to A with Carry
    //  Branch to next label if Carry Set
    //  CoMPare A with CharStruct::MaxHP,X
    //  Branch to next label if Carry Clear

    //  [LBL] LoaD CharStruct::MaxHP,X to A	(cap at maxhp)

    //  [LBL] STore A to CharStruct::CurHP,X
    //  Clear A, then Shorten
    //  LoaD $0F to A
    //  OR A with #$80       		(flag to display as healing)
    //  STore A to $0F
    //  LoaD TimerReadyChar::Regen to A
    //  LoaD $0E to X
    //  STore X to TempDisplayDamage
    //  Jump to SubRoutine CopyDisplayDamage
    //  LoaD #$09 to A	(C1 routine: display regen/poison damage)
    //  Jump to SubRoutine CallC1

    //  [Ret] Return To Subroutine
}

static void timerEffectSing(void) {
    //  LoaD #$01 to A
    //  STore A to EnableTimer::Sing,Y
    //  LoaD InitialTimer::Sing,Y to A
    //  STore A to CurrentTimer::Sing,Y
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Song,X to A
    //  Branch to [Ret] if EQuals

    //  [FindSong]		(Y = song stat index)
    //  A Shift Left
    //  Branch to next label if Carry Set
    //  INcrement Y
    //  BRAnch to [FindSong]

    //  [LBL] STore Y to $12		(song stat index)
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  STore X to $0E		(target)
    //  LoaD #$04 to A
    //  STore A to $10		(afer last target)
    //  LoaD TimerReadyChar::Sing to A
    //  CoMPare A with #$04	(monster check? monsters can sing?)
    //  Branch to ApplySong if Clear Carry
    //  LoaD #$04 to A
    //  STore A to $0E		(target)
    //  LoaD #$0C to A
    //  STore A to $10		(last target +1)
    //  LoaD #$0180 to X	(**bug: should be $0200 for first monster)

    //  [ApplySong]
    //  STore X to $14 to X		(char offset)
    //  Lengthen A
    //  Transfer X to A
    //  CLear Carry
    //  ADd $12 to A with Carry		(adjust offset by song stat)
    //  Transfer A to X
    //  Clear A, then Shorten

    //  [CharLoop]
    //  LoaD $0E to Y		(target)
    //  LoaD ActiveParticipants,Y to A
    //  Branch to [Next] if EQuals
    //  CLear Carry
    //  LoaD CharStruct::BonusStr,X to A	(different stats depending on X)
    //  INCrement
    //  CoMPare A with #$64	(don't apply changes at 100 and up)
    //  Branch to [Next] if Carry Set
    //  STore A to CharStruct::BonusStr,X

    //  [Next]
    //  Jump to SubRoutine NextCharOffset
    //  STore X to $14		(char offset)
    //  INCrement $0E		(next targett)
    //  LoaD $0E to A
    //  CoMPare A with $10		(last target +1)
    //  Branch to CharLoop if Not Equals

    //  [Ret] Return To Subroutine
}

static void timerEffectParalyze(void) {
    // LoaD AttackerOffset to X
    // LoaD CharStruct::Status2,X to A
    // AND A with #$DF	(clear paralyze)
    // STore A to CharStruct::Status2,X
    // LoaD ProcessingTimer to X
    // LoaD TimerReadyChar,X to A
    // JuMP to ResetATB
}

static void timerEffectATB(void) {
    //  Jump to SubRoutine CheckBattleEnd
    //  LoaD BattleOver to A
    //  Branch to [GoRet] if Not Equals
    //  LoaD TimerReadyChar::ATB
    //  STore A to AttackerIndex
    //  Jump to SubRoutine GetTimerOffset
    //  Transfer Y to X
    //  LoaD EnableTimer::Paralyze,X
    //  Branch to [GoRet]
    //  LoaD EnableTimer::ATB,X
    //  Branch to next label if EQuals
    //  JuMP to PerformAction      	(action is ready, do it)

    //  [LBL] lda TimerReadyChar::ATB
    //  CoMPare A with #$04	(monster check)
    //  Branch to [Monster] if Carry Set
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X

    //  [SearchTurnQueue]	(find character in turn queue)
    //  LoaD ATBReadyQueue,X
    //  CoMPare A with TimerReadyChar::ATB
    //  Branch to [GoRet] if EQuals	(character already in turn queue)
    //  INcrement X
    //  ComPare X with #$0004
    //  Branch to [SearchTurnQueue] if Not Equals
    //  LoaD TimerReadyChar::ATB
    //  Jump to SubRoutine CheckDisablingStatus
    //  Branch to [GoRet] if Not Equals
    //  LoaD ATBReadyCount
    //  LoaD TimerReadyChar::ATB
    //  STore A to ATBReadyQueue,X
    //  INCrement ATBReadyCount

    //  [GoRet]	JuMP to [Ret]

    //  [Monster] Jump to SubRoutine MonsterATB

    //  [Ret] Return To Subroutine
}

// Called when character's turn is up,
// perform their queued action
static void performAction(void) {
    //  Jump to SubRoutine ProcessTurn
    //  LoaD DelayedFight to A
    //  Branch to [Ret] if Not Equals
    //  LoaD AttackerIndex to A
    //  CoMPare A with #$04	;monster check
    //  Branch to [_ResetATB] if Carry Set
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::CmdStatus,X to A
    //  AND A with #$E0	;clear many flags (jump/flirt/others?)
    //  STore A to CharStruct::CmdStatus,X
    //  Store Zero to CharStruct::DamageMod,X
    //  LoaD CharStruct::Status1,X to A
    //  OR A with CharStruct::AlwaysStatus1,X
    //  AND A with #$02	;zombie
    //  Branch to [Uncontrolled] if Not Equals
    //  LoaD CharStruct::Status2,X to A
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$18	;charm/berserk
    //  Branch to [_ResetATB] if EQuals

    //  [Uncontrolled]
    //  LoaD AttackerIndex to A
    //  Jump to SubRoutine GetTimerOffset
    //  Transfer Direct page to aCcumulator
    //  STore A to EnableTimer::ATB,Y
    //  INCrement
    //  STore A to CurrentTimer::ATB,Y
    //  LoaD AttackerIndex to A
    //  Transfer A to X
    //  LoaD UncontrolledATB,X to A
    //  AND A with #$7F	;max 127
    //  STore A to UncontrolledATB,X

    //  [_ResetATB]
    //  INCrement CheckQuick
    //  LoaD AttackerIndex to A
    //  Jump to SubRoutine ResetATB
    //  Store Zero to CheckQuick

    //  [Ret] Return To Subroutine
}

// Waits when a character's turn arrives
// (amount depending on battle speed setting)
static void atbWait(void) {
    //  LoaD ATBWaiting to A
    //  Branch to [Ret] if EQuals
    //  LoaD ATBWaitLeft to A
    //  Branch to [DoneWaiting] if EQuals
    //  DECrement
    //  STore A to ATBWaitLeft
    //  Branch to [Ret] if Not Equals

    //  [DoneWaiting]
    //  Transfer Direct page to aCcumulator
    //  STore A to ATBWaiting

    //  [Ret] Return To Subroutine
}

// Updates ATB for all combatants and
// sets them active if present
static void resetAtbAll(void) {
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  Transfer A to Y
    //  STore X to $0E			(char index)

    //  [ResetATBLoop]
    //  LoaD $0E to A
    //  Jump to SubRoutine ResetATB
    //  LoaD $0E to A
    //  Jump to SubRoutine CalculateCharOffset
    //  LoaD $0E to A
    //  CoMPare A with #$04		(monster check)
    //  Branch to Monster if Carry Set
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::CharRow,X to A
    //  AND A with #$40		(not present)
    //  Branch to [SetActive] if EQuals
    //  Branch to [Next] if Not Equals

    //  [Monster]
    //  SEt Carry flag
    //  LoaD $0E to A
    //  SuBtract #$04 from A with Carry
    //  Transfer A to X 			(monster index)
    //  LoaD InitialMonsters,X to A
    //  Branch to [Next] if EQuals

    //  [SetActive]
    //  LoaD $0E to X
    //  LoaD #$01 to A
    //  STore A to ActiveParticipants,X

    //  [Next]
    //  INCrement $0E			(char index)
    //  LoaD $0E to A
    //  CoMPare A with #$0C		(12 participants)
    //  Branch to [ResetATBLoop] if Not Equals

    //  Return To Subroutine
}

// Initialize ATB (A: character index 0-12)
static void resetAtb(void) {
    //  PusH A
    //  Jump to SubRoutine GetTimerOffset	(Y AND A with $36 = timer offset)
    //  PulL A
    //  Jump to SubRoutine CalculateCharOffset
    //  Jump to SubRoutine CopyStatsWithBonuses
    //  LoaD CharStruct::EqWeight,X to A
    //  Jump to SubRoutine ShiftDivide_8	(weight/8)
    //  CLear Carry
    //  ADd #$78 to A with Carry     		(+120)
    //  SEt Carry flag
    //  SuBtract Agility from A with Carry    	(-agi)
    //  Branch to next label if EQuals
    //  Branch to next label if Carry Set

    //  [LBL] LoaD #$01 to A     		(min 1)

    //  [LBL] Jump to SubRoutine HasteSlowMod
    //  STore A to CurrentTimer::ATB,Y
    //  LoaD EncounterInfo::IntroFX to A
    //  Branch to [NotCredits] if PLus		(80h indicates a credits demo battle)
    //  LoaD AttackerOffset to X
    //  ComPare X with #$0200		(monster)
    //  Branch to [CreditsMonster] if Carry Set
    //  LoaD #$01 to A		(party member gets turn immediately)
    //  BRAnch to [CreditsParty]

    //  [CreditsMonster]
    //  LoaD #$FF to A		(monster turn as late as possible)

    //  [CreditsParty]
    //  STore A to CurrentTimer::ATB,Y

    //  [NotCredits]
    //  LoaD CheckQuick to A
    //  Branch to [EnableATB] if EQuals
    //  LoaD QuickTurns to A
    //  Branch to [EnableATB] if EQuals
    //  LoaD CurrentlyReacting to A
    //  Branch to [EnableATB] if Not Equals
    //  DECrement QuickTurns
    //  LoaD QuickTurns to A
    //  Branch to [Quick] if Not Equals
    //  PusH Y
    //  Jump to SubRoutine ClearQuick
    //  PulL Y
    //  BRAnch to [EnableATB]

    //  [Quick]
    //  LoaD #$01 to A
    //  STore A to CurrentTimer::ATB,Y

    //  [EnableATB]
    //  LoaD #$01 to A
    //  STore A to EnableTimer::ATB,Y
    //  Return To Subroutine
}

// Unfreezes time for everyone
static void clearQuick(void) {
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X

    //  [LBL] STore Zero to QuickTimeFrozen,X
    //  INcrement X
    //  ComPare X with #$000C		(12 combatants)
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
    // Jump to SubRoutine GetTimerDuration	(also sets up Y)
    // LoaD AttackerOffset to X	(not actually attacker, in this case)
    // Jump to SubRoutine HasteSlowMod
    // STore A to CurrentTimer,Y
    // STore A to InitialTimer,Y
    // LoaD #$01 to A
    // STore A to EnableTimer,Y
    // STore Zero to StatusFixedDur
    // Return to SubRoutine
}

// Get Timer Duration
    //  Input X - #timer
    //  $3ED7 - IsItem
// Output A = return duration
// sets up and jumps to a jump table entry that
// sets the correct duration
// also sets up Y as the correct timer offset
static void getTimerDuration(uint8_t timer) {
    // TimerDurationJumpTable (Address: _254A)
        // Is only called in this function

    // .word DurSpell, Dur120a, DurVit, DurVit, DurSpell
    // .word Dur120b, DurSpell, Dur49, DurSpell, Dur180mod
    // .word DurSpell, Dur180, Dur10, Dur10, Dur110mod
    // .word Dur110mod, Dur30, Dur30, DurSpellmod, Dur120mod

    // .word $2572, $2576, $2579, $2579, $2572
    //       $2584, $2572, $2587, $2572, $258A
    //       $2572, $259A, $259D, $259D, $25A0
    //       $25A0, $25AF, $25AF, $25B2, $25C3

    const uint8_t (*spellDurations[20])() = {
        timerDuration_spell, timerDuration_120, timerDuration_stamina20, timerDuration_stamina20, timerDuration_spell,
        timerDuration_120, timerDuration_spell, timerDuration_049, timerDuration_spell, timerDuration_180MagicHalf,
        timerDuration_spell, timerDuration_180, timerDuration_010, timerDuration_010, timerDuration_110Magic,
        timerDuration_110Magic, timerDuration_030, timerDuration_030, timerDuration_spellMagicHalf, timerDuration_120MagicHalf
    };

    // Jump to SubRoutine AddTimerOffsetY      (Y = X + TimerOffset)
    addTimerOffsetY(timer);

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
}

// Address: _253F
// (X): Y = X + $36 (Timer Offset)
static void addTimerOffsetY(uint8_t timer) {
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
// TODO: Get duration
static uint8_t timerDuration_spell(void) {
    // LoaD StatusDuration to A
    // Return To Subroutine
    return 0;
}

// Address: _2576
// Duration = 120
static uint8_t timerDuration_120(void) {
    // LoaD #$78 (#120) to A
    // Return To Subroutine
    return 120;
}

// Address: _2579
// Duration = Attacker's Vitality + 20
// TODO: Update formula to include Vitality
static uint8_t timerDuration_stamina20(void) {
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
// Essentially the same as _2576

// Address: _2587
// Duration = 49
static uint8_t timerDuration_049(void) {
    // LoaD #$31 (#49) to A
    // Return To Subroutine
    return 49;
}

// Address: 258A
// Duration = 180 - Attacker's Magic Power / 2
// TODO: Update formula with Magic Power
static uint8_t timerDuration_180MagicHalf(void) {
    // Load MagicPower to A
    // (L)Shift A Right
    // Store A to $0E
    // SEt Carry
    // Load #$B4 (#180) to A
    // SuBtract $0E from A with Carry
    uint8_t total = 0;

    // Branch to next label if Carry Set
    // LoaD #$01 to A
    // [LBL] Return To Subroutine
    if (total < MIN_BYTE) return MIN_BYTE;

    return total;
}

// Address: _259A
// Duration = 180
static uint8_t timerDuration_180(void) {
    // LoaD #$B4 (#180) to A
    // Return To Subroutine
    return 180;
}

// Address: _259D
// Duration = 10
static uint8_t timerDuration_010(void) {
    // LoaD #$0A (#10) to A
    // Return To Subroutine
    return 10;
}

// Address: _25A0
// Duration = 110 - Attacker's Magic Power, min 30
// TODO: Update formula with Magic Power
static uint8_t timerDuration_110Magic(void) {
    //  SEt Carry flag
    //  LoaD #$6E to A
    //  SuBtract MagicPower from A with Carry
    //  Brach to next label if Carry Clear
    //  CoMPare A with #$1E	(min 30)
    //  Branch to second next label if Carry Set
    //  [LBL] Load #$1E to A	(min 30)
    //  [LBL] Return To Subroutine
    uint8_t total = 110;

    if (total < 30) return 30;

    return total;
}

// Address: _25AF
// Duration = 30
static uint8_t timerDuration_030(void) {
    // LoaD #$1E (#30) to A
    // Return To Subroutine
    return 30;
}

// Address: _25B2
// Duration = Spell Duration - Attacker's Magic Power / 2
static uint8_t timerDuration_spellMagicHalf(void) {
    return 1;
}

// Address: _25C3
// Duration = 120 - Attacker's Magic Power / 2
static uint8_t timerDuration_120MagicHalf(void) {
    return 120;
}

// Queues up a monster's action when
// their ATB is ready
static void monsterAtb(void) {
    //  LoaD #$01 to A
    //  STore A to AISkipDeadCheck
    //  SEt Carry flag
    //  LoaD AttackerIndex to A
    //  SuBtract #$04 from A with Carry
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
    //  LoaD MonsterOffset16 to X
    //  LoaD #$FF to A

    //  [LBL] STore A to MonsterMagic,X
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0010	(init 16 byte monster magic struct)
    //  Branch to previous label if Not Equals

    //  LoaD MonsterIndex to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD f:_d0ee95,X to A
    //  STore A to $0E
    //  LoaD f:_d0ee95+1,X to A
    //  STore A to $0F
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y
    //  LoaD $0E		(MonsterIndex *100)
    //  LoaD #$FF to A

    //  [LBL] STore A to MonsterAIScript,X
    //  INcrement X
    //  INcrement Y
    //  ComPare Y with #$0064	(init 100 bytes to $FF)
    //  Branch to previous label if Not Equals
    //  LoaD AttackerIndex to A
    //  Jump to SubRoutine CalculateCharOffset
    //  LoaD AttackerOffset to X
    //  LoaD #$2C to A       	(magic)
    //  STore A to CharStruct::Command,X
    //  LoaD #$21 to A	(magic + costs mp)
    //  STore A to CharStruct::ActionFlag,X
    //  LoaD AttackerOffset to X
    //  LoaD CharStruct::Status2,X to A
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$08	(berserk)
    //  Branch to [CheckCharm] if EQuals
    //  LoaD #$01 to A
    //  STore A to CharStruct::CmdCancelled,X
    //  LoaD #$80 to A	(monster fight)
    //  STore A to AIBuffer
    //  LoaD #$FF to A	(end of list)
    //  STore A to AIBuffer+1
    //  Jump to SubRoutine DispatchAICommands
    //  JuMP to GoFinish

    //  [CheckCharm]
    //  LoaD CharStruct::Status2,X to A
    //  OR A with CharStruct::AlwaysStatus2,X
    //  AND A with #$10	(charm)
    //  Branch to CheckFlirt if EQuals

    //  [TryRandomAction]
    //  LoaD AttackerOffset to X
    //  LoaD #$01 to A
    //  STore A to CharStruct::CmdCancelled,X
    //  Transfer Direct page to aCcumulator
    //  Transfer A to X
    //  LoaD #$03 to A
    //  Jump to SubRoutine Random_X_A 	(0..3)
    //  Transfer A to X
    //  STore X to $0E
    //  LoaD MonsterIndex to A
    //  A Shift Left
    //  Transfer A to X
    //  Lengthen A
    //  LoaD BattleMonsterID,X to A
    //  Jump to SubRoutine ShiftMultiply_4
    //  CLear Carry
    //  Add $0E to A with Carry		(random number 0..3)
    //  Transfer A to X 		(offset into control actions table)
    //  Clear A, then Shorten
    //  LoaD f:MonsterControl,X to A
    //  CoMPare A with #$FF to A
    //  Branch to TryRandomAction if EQuals	(no action in this slot, try again)
    //  STore A to AIBuffer
    //  LoaD #$FF to A	(end of list)
    //  STore A to AIBuffer+1
    //  INCrement TempCharm
    //  Jump to SubRoutine DispatchAICommands
    //  BRAnch to [GoFinish]

    //  [CheckFlirt]
    //  LoaD CharStruct::CmdStatus,X to A
    //  AND A with #$08	[flirt]
    //  Branch to [CheckControl] if EQuals
    //  LoaD #$51 to A	[throbbing command]
    //  STore A to CharStruct::Command,X
    //  LoaD #$80 to A	[other]
    //  STore A to CharStruct::ActionFlag,X
    //  BRAnch to [GoFinish]

    //  [CheckControl]
    //  LoaD CharStruct::Status4,X to A
    //  AND A with #$20	(control)
    //  Branch to [Control] if Not Equals
    //  LoaD CharStruct::Status2,X to A
    //  AND A with #$40	(sleep)
    //  Branch to [Sleep] if Not Equals
    //  BRAnch to [Normal]

    //  [Control]
    //  Transfer Direct page to aCcumulator
    //  Transfer A to Y

    //  [LBL] LoaD ControlTarget,Y to A
    //  CoMPare A with AttackerIndex
    //  Branch to [FoundController] if EQuals
    //  INcrement Y
    //  BRAnch to previous label

    //  [FoundController]
    //  LoaD ControlCommand,Y to A
    //  Branch to [_ControlCommand] if Not Equals
    //  [Sleep]	(or controlled without a command)
    //  Store Zero to CharStruct::Command,X
    //  LoaD #$80 to A	(action complete?)
    //  STore A to CharStruct::ActionFlag,X
    //  BRAnch to [GoFinish]

    //  [_ControlCommand]
    //  Transfer Direct page to aCcumulator
    //  STore A to ControlCommand,Y
    //  LoaD MonsterIndex to A
    //  Transfer A to X
    //  LoaD MonsterControlActions,X to A
    //  STore A to AIBuffer
    //  LoaD #$FF to A	(end of list)
    //  STore A to AIBuffer+1
    //  Jump to SubRoutine DispatchAICommands

    //  [GoFinish]
    //  JuMP to Finish

    //  [Normal]
    //  LoaD MonsterIndex to A
    //  Transfer A to X
    //  LoaD AIActiveConditionSet,X to A
    //  STore A to AICurrentActiveCondSet
    //  LoaD MonsterIndex to A
    //  A Shift Left
    //  Transfer A to X
    //  Lengthen A
    //  CLear Carry
    //  LoaD f:_d0eea5,X to A	(*1620, size of MonsterAI struct)
    //  ADd #MonsterAI to A with Carry
    //  STore A to AIOffset
    //  Clear A, then Shorten
    //  Store Zero to AICurrentCheckedSet

    //  [CheckAIConditions]
    //  LoaD AICurrentCheckedSet to A
    //  Transfer A to X
    //  LoaD f:_d0eec9,X to A	(size of a MonsterAI condition)
    //  Transfer A to Y
    //  STore Y to AIConditionOffset
    //  Store Zero to AICheckIndex

    //  [CheckSingleCondition]
    //  LoaD AIConditionOffset to Y
    //  LoaD (AIOffset),Y to A
    //  Branch to [AIActions] if Equals		(0 always succeeds)
    //  CoMPare A with #$FE		(indicates end of condition set)
    //  Branch to [AIActions] if EQuals
    //  Jump to SubRoutine CheckAICondition
    //  LoaD AIConditionMet to A
    //  Branch to NextConditionSet if EQuals
    //  Lengthen A
    //  CLear Carry
    //  LoaD AIConditionOffset to A
    //  ADd #$0004 to A with Carry		(next condition in set)
    //  STore A to AIConditionOffset
    //  Clear A, then Shorten
    //  INCrement AICheckIndex
    //  BRAnch to CheckSingleCondition

    //  [NextConditionSet]	(failed a condition in this set, check next set of conditions)
    //  INCrement AICurrentCheckedSet
    //  LoaD AICurrentCheckedSet to A
    //  CoMPare A with #$0A		(10 conditions max)
    //  Branch to CheckAIConditions if Not Equals

    //  [AIActions]
    //  Lengthen A
    //  CLear Carry
    //  LoaD AIOffset to A
    //  ADd #$00AA to A with Carry	(advances from Conditions to Actions)
    //  STore A to AIOffset
    //  Clear A, then Shorten
    //  LoaD AICurrentActiveCondSet to A
    //  CoMPare A with AICurrentCheckedSet
    //  Branch to [ConditionOK] if EQuals	(matches so don't need to change things)
    //  LoaD MonsterIndex to A
    //  Transfer A to X
    //  LoaD AICurrentCheckedSet to A
    //  STore A to AIActiveConditionSet,X	(checked cond is now current)
    //  LoaD MonsterIndex to A
    //  A Shift Left
    //  Transfer A to Y
    //  LoaD AICurrentCheckedSet to A
    //  A Shift Left
    //  Transfer A to X
    //  LoaD f:_d0eeb5,X to A
    //  STore A to AICurrentOffset,Y
    //  LoaD f:_d0eeb5+1,X to A
    //  STore A to AICurrentOffset+1,Y

    //  [ConditionOK]
    //  Jump to SubRoutine ProcessAIScript

    //  [Finish]
    //  LoaD MonsterOffset16 to X
    //  LoaD MonsterMagic,X to A
    //  Lengthen A
    //  Jump to SubRoutine ShiftMultiply_8
    //  Transfer A to X
    //  Clear A, then Shorten
    //  LoaD f:AttackProp,X to A
    //  AND A with #$03       	(delay values)
    //  Transfer A to X
    //  LoaD f:AttackDelayTbl,X to A
    //  PusH A
    //  LoaD AttackerIndex to A
    //  Jump to SubRoutine GetTimerOffset
    //  PulL A
    //  STore A to CurrentTimer::ATB,Y    (**bug? doesn't adjust for haste/slow)
    //  LoaD #$41	;pending action to A
    //  STore A to EnableTimer::ATB,Y
    //  LoaD MonsterIndex to A
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

// Address: _2C27
static void getAiTarget(void) {}

static void aiTarget00(void) {}

static void aiTarget01(void) {}

static void aiTarget02(void) {}

static void aiTarget03(void) {}

static void aiTarget04(void) {}

static void aiTarget05(void) {}

static void aiTarget06(void) {}

static void aiTarget07(void) {}

static void aiTarget08(void) {}

static void aiTarget09(void) {}

static void aiTarget0a(void) {}

static void aiTarget0b(void) {}

static void aiTarget0c(void) {}

static void aiTarget0d(void) {}

static void aiTarget0e(void) {}

static void aiTarget0f(void) {}

static void aiTarget10(void) {}

static void aiTarget11(void) {}

static void aiTarget12(void) {}

static void aiTarget13(void) {}

static void aiTarget14(void) {}

static void aiTarget15(void) {}

static void aiTarget16(void) {}

static void aiTarget17(void) {}

static void aiTarget18(void) {}

static void aiTarget19(void) {}

static void aiTarget1a(void) {}

static void aiTarget1b(void) {}

static void aiTarget1c(void) {}

static void aiTarget1d(void) {}

static void aiTarget1e(void) {}

static void aiTarget1f(void) {}

static void aiTarget20(void) {}

static void aiTarget21(void) {}

static void aiTarget22(void) {}

static void aiTarget23(void) {}

static void aiTarget24(void) {}

static void aiTarget25(void) {}

static void aiTarget26(void) {}

static void aiTarget27(void) {}

static void aiTarget28(void) {}

static void aiTarget29(void) {}

static void aiTarget2a(void) {}

static void aiTarget2b(void) {}

static void aiTarget2c(void) {}

static void aiTarget2d(void) {}

static void aiTarget2e(void) {}

static void aiTarget2f(void) {}

static void aiTarget30(void) {}

static void aiTarget31(void) {}

static void aiTarget32(void) {}

// Address: _3127
static void checkTargetValid(void) {}

// Address: _313B
static void processAiScript(void) {}

// Address: _3210
static void dispatchAiCommands(void) {}

// Address: _329C
static void aiCastNormalSpell(void) {}

// Address: _334D
static void aiChoose1of3(void) {}

// Address: _336E
static void aiShowMonster(void) {}

// Address: _33EC
static void aiSetTarget(void) {}

// Address: _346F
static void aiSetVar(void) {}

// Address: _347B
static void aiSetEventFlag(void) {}

// Address: _348A
static void aiSetStatsToggleStatus(void) {}

// Address: _34D9
static void aiCopyCommand(void) {}

// Address: _3504
static void aiSpellTarget(void) {}

// Address: _35E3
static void handleReactions(void) {}

// Address: _3C10
static void checkReactionConditions(void) {}

// Address: _3C7F
static void saveActionData(void) {}

// Address: _3D08
static void restoreActionData(void) {}

// Address: _3D9C
static void reactionPauseTimerChecks(void) {}

// Address: _3DBB
static void unpauseTimerChecks(void) {}

// Address: _3DC7
static void processReaction(void) {}

// Address: _3EA2
static void loadStatsEquipAi(void) {}

// Address: _41A3
static void startTimerFromTemp(void) {}

// Address: _41AF
static void setupInventoryMagic(void) {}

// Address: _455E
static void getItemUsableA(void) {}

// Address: _45D5
static void startPartyPoisonTimers(void) {}

// Address: _45FF
static void fightCommand(void) {}

// Address: _48BD
static void processTurn(void) {}

// Address: _4923
static void shiftActionAnims(void) {}

// Address: _4968
static void dispatchCommand(void) {}

static void dispatchCommandReady(void) {}

// Address: _4A2F
static void restoreStatsAfterRelease(void) {}

// Address: _4AFE
static void checkRetarget(void) {}

// Address: _4BD7
static void checkValidTargetsExist(void) {}

// Address: _4C10
static void checkLearnBlue(void) {}

// Address: _4CE0
static void startBattle(void) {}

// Address: _4E25
static void checkOneTimeEncounters(void) {}

// Address: _4E9F
static void advanceStartingAtb(void) {}

// Address: _4F0A
static void initBattle(void) {}

// Address: _4F7A
static void checkAmbushes(void) {}

// Address: _4FEA
static void setupBackAttack(void) {}

// Address: _5001
static void setupPreemptive(void) {}

// Address: _501D
static void adjustAtb(void) {}

// Address: _505C
static void setupBattleMusic(void) {}

// Address: _5070
static void endBattle(void) {}

// Address: _515C
static void resetStats(void) {}

// Address: _51C2
static void mergeItemDupes(void) {}

// Address: _51F4
static void updateFieldData(void) {}

// Address: _52A2
static void getLootExp(void) {}

// Address: _5974
static void checkHideAP(void) {}

// Address: _569A
static void dropMonsterLoot(void) {}

// Address: _56EC
static void levelUp(void) {}

// Address: _57C7
static void applyHPMPPassives(void) {}

// Address: _57E6
static void divideExp(void) {}

// Address: _5847
static void gfxCmdMessageClearAnim(void) {}

// Address: _5872
static void mainBattleLoop(void) {}

// Address: _5921
static void copyHPMPStatus(void) {}

// Address: _5A41
static void updateMonsterList(void) {}

// Address: _5AB4
static void checkBattleEnd(void) {}

// Address: _5B6C
static void updateMonsterRows(void) {}

// Address: _5CE1
static void castSpell(void) {}

// Address: _5F75
static void castMultiHitSpell(void) {}

// Address: _60A3
static void prepSummon(void) {}

// Address: _614E
static void getPartyTargetOffset(void) {}

// Address: _6163
static void hasteSlowMod(void) {}

// Address: _618A
static void killChar(void) {}

// Address: _6257
static void checkPartyDeath(void) {}

// Address: _6265
static void checkMonsterDeath(void) {}

// Address: _6272
static void checkForDeath(void) {}

// Address: _6408
static void setupAndLaunchAttack(void) {}

// Address: _64B2
static void dispatchAttack(void) {}

// Address: _6523
static void clearAttackData(void) {}

// Address: _653A
static void copyAttackParams(void) {}

// Address: _654D
static void applyDamage(void) {}

// Address: _685C
static void getDamageDisplayOffset(void) {}

// Address: _686C
static void attackType00(void) {}

// Address: _6870
static void attackType01(void) {}

// Address: _6898
static void attackType02(void) {}

// Address: _68E2
static void attackType03(void) {}

// Address: _68F7
static void attackType04(void) {}

// Address: _690C
static void attackType05(void) {}

// Address: _6921
static void attackType06(void) {}

// Address: _694A
static void attackType07(void) {}

// Address: _6971
static void attackType08(void) {}

// Address: _6993
static void attackType09(void) {}

// Address: _69B5
static void attackType0A(void) {}

// Address: _69DB
static void attackType0B(void) {}

// Address: _6A07
static void attackType0C(void) {}

// Address: _6A3C
static void attackType0D(void) {}

// Address: _6A65
static void attackType0E(void) {}

// Address: _6A76
static void attackType0F(void) {}

// Address: _6A81
static void attackType10(void) {}

// Address: _6A8E
static void attackType11(void) {}

// Address: _6AC4
static void attackType12(void) {}

// Address: _6ACF
static void attackType13(void) {}

// Address: _6ADD
static void attackType14(void) {}

// Address: _6AEB
static void attackType15(void) {}

// Address: _6AF6
static void attackType16(void) {}

// Address: _6B01
static void attackType17(void) {}

// Address: _6B32
static void attackType18(void) {}

// Address: _6B35
static void attackType19(void) {}

// Address: _6B52
static void attackType1A(void) {}

// Address: _6B7D
static void attackType1B(void) {}

// Address: _6BFC
static void attackType1C(void) {}

// Address: _6C17
static void attackType1D(void) {}

// Address: _6CE4
static void attackType1E(void) {}

// Address: _6CEF
static void attackType1F(void) {}

// Address: _6D2E
static void attackType20(void) {}

// Address: _6D4B
static void attackType21(void) {}

// Address: _6D5B
static void attackType22(void) {}

// Address: _6D83
static void attackType23(void) {}

// Address: _6DAB
static void attackType24(void) {}

// Address: _6DB4
static void attackType25(void) {}

// Address: _6DBD
static void attackType26(void) {}

// Address: _6DD7
static void attackType27(void) {}

// Address: _6DED
static void attackType28(void) {}

// Address: _6E12
static void attackType29(void) {}

// Address: _6E2D
static void attackType2A(void) {}

// Address: _6E4C
static void attackType2B(void) {}

// Address: _6E5E
static void attackType2C(void) {}

// Address: _6E72
static void attackType2D(void) {}

// Address: _6E9B
static void attackType2E(void) {}

// Address: _6EB1
static void attackType2F(void) {}

// Address: _6EBC
static void attackType30(void) {}

// Address: _6EE1
static void attackType31(void) {}

// Address: _6F1E
static void attackType32(void) {}

// Address: _6F58
static void attackType33(void) {}

// Address: _6F84
static void attackType34(void) {}

// Address: _6FA8
static void attackType35(void) {}

// Address: _6FC9
static void attackType36(void) {}

// Address: _6FF9
static void attackType37(void) {}

// Address: _7020
static void attackType38(void) {}

// Address: _703E
static void attackType39(void) {}

// Address: _7053
static void attackType3A(void) {}

// Address: _7074
static void attackType3B(void) {}

// Address: _709D
static void attackType3C(void) {}

// Address: _70C4
static void attackType3D(void) {}

// Address: _70DB
static void attackType3E(void) {}

// Address: _70EC
static void attackType3F(void) {}

// Address: _7119
static void attackType40(void) {}

// Address: _7134
static void attackType41(void) {}

// Address: _7140
static void attackType42(void) {}

// Address: _7150
static void attackType43(void) {}

// Address: _71B9
static void attackType44(void) {}

// Address: _71D7
static void attackType45(void) {}

// Address: _71F5
static void attackType46(void) {}

// Address: _71FB
static void attackType47(void) {}

// Address: _720D
static void attackType48(void) {}

// Address: _7255
static void attackType49(void) {}

// Address: _7266
static void attackType4B(void) {}

// Address: _728D
static void attackType4C(void) {}

// Address: _729B
static void attackType4D(void) {}

// Address: _72B2
static void attackType4E(void) {}

// Address: _72DB
static void attackType4F(void) {}

// Address: _7300
static void attackType50(void) {}

// Address: _7319
static void attackType51(void) {}

// Address: _735E
static void attackType52(void) {}

// Address: _7379
static void attackType53(void) {}

// Address: _7384
static void attackType54(void) {}

// Address: _738F
static void attackType55(void) {}

// Address: _7398
static void attackType56(void) {}

// Address: _73A3
static void attackType57(void) {}

// Address: _73C0
static void attackType58(void) {}

// Address: _73F0
static void attackType59(void) {}

// Address: _7407
static void attackType5A(void) {}

// Address: _740E
static void attackType5B(void) {}

// Address: _7419
static void attackType5C(void) {}

// Address: _7427
static void attackType5D(void) {}

// Address: _743D
static void attackType5E(void) {}

// Address: _745C
static void attackType5F(void) {}

// Address: _7476
static void attackType60(void) {}

// Address: _7562
static void attackType61(void) {}

// Address: _7662
static void attackType62(void) {}

// Address: _76CE
static void attackType63(void) {}

// Address: _7774
static void attackType64(void) {}

// Address: _77A4
static void attackType65(void) {}

// Address: _77B6
static void attackType66(void) {}

// Address: _77E0
static void attackType68(void) {}

// Address: _77E5
static void attackType67(void) {}

// Address: _77E9
static void attackType69(void) {}

// Address: _78BC
static void attackType6A(void) {}

// Address: _78DD
static void attackType6B(void) {}

// Address: _78EE
static void attackType6C(void) {}

// Address: _78FA
static void attackType6D(void) {}

// Address: _791B
static void attackType6E(void) {}

// Address: _794D
static void attackType6F(void) {}

// Address: _7956
static void attackType70(void) {}

// Address: _7964
static void attackType71(void) {}

// Address: _7AD9
static void attackType72(void) {}

// Address: _7AFA
static void attackType73(void) {}

// Address: _7B1E
static void attackType74(void) {}

static void attackType75(void) {}

// Address: _7C0D
static void hitCalcLevelMEvade(void) {}

// Address: _7C3B
static void setHitParam1TargetEvade(void) {}

// Address: _7C47
static void setHit100TargetEvade(void) {}

// Address: _7C53
static void setHit100HalfTargetEvade(void) {}

// Address: _7C60 is duplicate of _7C3B / setHitParam1TargetEvade(void)

// Address: _7C6C
static void setHitParam1HalfTargetEvade(void) {}

// Address: _7C79
static void setHitParam1TargetMEvade(void) {}

// Address: _7C85
static void hitCalcSteal(void) {}

// Address: _7C97
static void checkAegis(void) {}

// Address: _7CC3
static void multiTargetHitPercent(void) {}

// Address: _7CFC
static void checkSpecialEvade(void) {}

// Address: _7D7F
static void danceHitMod(void) {}

// Address: _7D8B
static void targetMHitMod(void) {}

// Address: _7DAC
static void targetPHitMod(void) {}

// Address: _7DD1
static void attackerStatusPHitMod(void) {}

// Address: _7DE2
static void checkTargetImage(void) {}

// Address: _7DF1
static void checkVoid(void) {}

// Address: _7E03
static void checkFloat(void) {}

// Address: _7E12
static void checkForHit(void) {}

// Address: _7E23
static void checkForPHit(void) {}

// Address: _7E5B
static void checkHitByCreatureType(void) {}

// Address: _7E67
static void checkLevel(void) {}

// Address: _7E81
static void hitMagicCondAutohit(void) {}

// Address: _7EBE
static void hitPhysical(void) {}

// Address: _7EF6
static void hitMagic(void) {}

// Address: _7F1B
static void hitPhysicalMagic(void) {}

// Address: _7F30
static void magicDamage(void) {}

// Address: _7F6A
static void flareDamage(void) {}

// Address: _7FA7
static void magicDamageRand(void) {}

// Address: _7FC2
static void magicDamagePhysical(void) {}

// Address: _7FFC
static void swordDamage(void) {}

// Address: _803E
static void fistDamage(void) {}

// Address: _80D4
static void knifeDamage(void) {}

// Address: _812B
static void axeDamage(void) {}

// Address: _816F
static void bellDamage(void) {}

// Address: _81CB
static void rodDamage(void) {}

// Address: _8205
static void levelDamage(void) {}

// Address: _8227
static void monsterDamage(void) {}

// Address: _8252
static void itemFormula(void) {}

// Address: _8261
static void physicalParamDamage(void) {}

// Address: _8299
static void throwDamage(void) {}

// Address: _830A
static void gilTossDamage(void) {}

// Address: _8366
static void multiTargetMod(void) {}

// Address: _839B
static void backRowMod(void) {}

// Address: _83BD
static void commandMod(void) {}

// Address: _8430
static void doubleGripMod(void) {}

// Address: _8452
static void checkJump(void) {}

// Address: _8467
static void runeMod(void) {}

// Address: _84AF
static void specialtyMod(void) {}

// Address: _84CF
static void medicineMod(void) {}

// Address: _84DD
static void creatureMod(void) {}

// Address: _84F3
static void targetStatusModMag(void) {}

// Address: _8512
static void targetStatusModPhys(void) {}

// Address: _8533
static void attackerStatusModPhys(void) {}

// Address: _855D
static void equalLevelMod(void) {}

static void braveDamage(void) {}

// Address: _85AD
static void goblinDamage(void) {}

// Address: _85F1
static void strongFightDamage(void) {}

// Address: _8626
static void chickenDamage(void) {}

// Address: _866D
static void elementUpMod(void) {}

// Address: _8684
static void spellbladeMod(void) {}

// Address: _8734
static void elementDamageModPhys(void) {}

// Address: _876E
static void elementDamageModMag(void) {}

// Address: _87B5
static void elementDamageModMag2(void) {}

// Address: _87DF
static void checkCrit(void) {}

// Address: _87F9
static void checkCreatureCrit(void) {}

// Address: _8811
static void calcFinalDmgSpellblade(void) {}

// Address: _8874
static void gravityDamage(void) {}

// Address: _88C1
static void cureTarget(void) {}

// Address: _88D8
static void fullCureTarget(void) {}

// Address: _88FD
static void setHPCritical(void) {}

// Address: _88C1
static void drainDamage(void) {}

// Address: _894D
static void spellbladePsyche(void) {}

// Address: _8985
static void psycheDamage(void) {}

// Address: _89DE
static void mpHeal(void) {}

// Address: _89F7
static void fullMPHeal(void) {}

// Address: _8A05
static void calcFinalDamage(void) {}

// Address: _8A4E
static void calcDamageMaxHP(void) {}

// Address: _8A9D
static void calcDamageAttackerCurHP(void) {}

// Address: _8AEC
static void calcDamageTargetCurHP(void) {}

// Address: _8B33
static void calcDamageAttackerDiffHP(void) {}

// Address: _8B4D
static void restoreHalfMax(void) {}

// Address: _8B7D
static void calcStatusDuration(void) {}

// Address: _8BCF
static void applySpellbladeStatusEffect(void) {}

// Address: _8BF9
static void applyConditionalStatus(void) {}

// Address: _8C2F
static void applySpecialtyEffects(void) {}

// Address: _8CAC
static void applyStatus1(void) {}

// Address: _8D2E
static void applyStatus2(void) {}

// Address: _8DCB
static void applyStatus3(void) {}

// Address: _8E05
static void applyStatus4(void) {}

// Address: _8E25
static void toggleStatus1(void) {}

// Address: _8E3A
static void applyFlirt(void) {}

// Address: _8E51
static void applyStatus3Exclusive(void) {}

// Address: _8EB6
static void removeStatus1(void) {}

// Address: _8F11
static void removeStatus2(void) {}

// Address: _8F6E
static void removeStatus3(void) {}

// Address: _8F82
static void killNonHeavy(void) {}

// Address: _8FAA
static void reviveTarget(void) {}

// Address: _902B
static void applyStatus1Bypass(void) {}

// Address: _9039
static void applyStatus2Bypass(void) {}

// Address: _90CD
static void applyStatus3Bypass(void) {}

// Address: _90DB
static void applyStatus1AttackerBypass(void) {}

// Address: _90E9
static void removeSpellblade(void) {}

// Address: _9101
static void changeTargetRow(void) {}

// Address: _9117
static void moveTargetToFront(void) {}

// Address: _9122
static void moveAttackerToBack(void) {}

// Address: _912D
static void halveDefence(void) {}

// Address: _9136
static void halveLevel(void) {}

// Address: _9143
static void addLevel(void) {}

// Address: _9153
static void subtractLevel(void) {}

// Address: _9163
static void doubleMaxHP(void) {}

// Address: _9197
static void addAttack(void) {}

// Address: _91B4
static void addDefenses(void) {}

// Address: _91D1
static void toggleStatus4(void) {}

// Address: _91DC seems to be unused

// Address: _91E7
static void addCreatureType(void) {}

// Address: _91F2
static void addStatus1Immunity(void) {}

// Address: _91FD
static void addElementUp(void) {}

// Address: _9208
static void stealItem(void) {}

// Address: _92A5
static void startStatus1Timer(void) {}

// Address: _92B4
static void stopStatus1Timer(void) {}

// Address: _92C3
static void stopStatus2Timer(void) {}

// Address: _92EE
static void stopStatus3Timer(void) {}

// Address: _9319
static void stopStatus4Timer(void) {}

// Address: _9328
static void startStatus2Timer(void) {}

// Address: _934D
static void startStatus3Timer(void) {}

// Address: _9319
static void startStatus4Timer(void) {}

// Address: _938F
static void loseOneImage(void) {}

// Address: _93A5
static void catchMonster(void) {}

// Address: _93F8
static void calcBaseDamage(void) {}

// Address: _9427
static void processCommands(void) {}

// Address: _94FF
static void findFirstTargetPlus1(void) {}

// Address: _951A
static void getCharStructActionData(void) {}

// Address: _9561
static void checkTargetRedirect(void) {}

// Address: _9728
static void checkValidTargetsExist2(void) {}

// Address: _9761
static void steupReactionsAnims(void) {}

// Address: _9885
static void copyReactionInfo(void) {}

// Address: _98E3
static void gfxCmdDamageNumbers(void) {}

// Address: _98FA
static void findOpenGfxQueueSlot(void) {}

// Address: _9923
static void selectCurProcSequence(void) {}

// Address: _992F
static void gfxCmdAttackNameFromTemp(void) {}

// Address: _994C
static void gfxCmdMessage(void) {}

// Address: _9965
static void setupMsgBoxIndexes(void) {}

// Address: _9980
static void deleteCommand(void) {}

// Address: _9A08
static void collectMPCost(void) {}

// Address: _9A5E
static void applyPartyGear(void) {}

// Address: _9A6F
static void applyGear(void) {}

// Address: _9D01
static void applyEquipStatus(void) {}

// Address: _9F2E
static void startTimerCurChar(void) {}

// Address: _9F3A
static void replaceHands(void) {}

// Address: _9FE7
static void swapHands(void) {}