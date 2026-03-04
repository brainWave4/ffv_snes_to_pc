// Bank Range: C1, D9
#include "btlgfx.h"

// for _c2a006
#include "menu.h"

// for Decomp_ext
#include "cutscene.h"

// for ExecSound_ext
#include "sound.h"

static void func_c1003f(void); // Incomplete
static void func_c10092(void); // Incomplete
static void func_c100c6(void); // Incomplete
static void func_c100f2(void); // Incomplete
static void func_c1010b(void); // Incomplete
static void func_c1014c(void); // Incomplete
static void func_c10158(void); // Incomplete
static void func_c1016c(void); // Incomplete
static void func_c101e4(void); // Incomplete
static void func_c101f6(void); // Incomplete
static void func_c101fe(void); // Incomplete
static void func_c10208(void); // Incomplete
static void showDamageNumerals(void); // Incomplete
static void func_c10276(void); // Incomplete
static void func_c10293(void); // Incomplete
static void func_c102ab(void); // Incomplete
static void func_c102df(void); // Incomplete
static void func_c102e0(void); // Incomplete
static void func_c102f2(void); // Incomplete
static void func_c102fe(void); // Incomplete
static void func_c10348(void); // Incomplete
static void updateSongTempoMult(void); // Incomplete
static void updateReflectSfx(void); // Incomplete
static void func_c10401(void); // Incomplete
static void func_c10491(void); // Incomplete
static void initRam(void); // Incomplete
static void updateSavedCursorChecksums(void); // Incomplete
static void validateSavedCursorChecksums(void); // Incomplete
static void resetSavedCursorPos(void); // Incomplete
static void calcSavedCursorChecksum(void); // Incomplete
static void clearSavedCursorPos(void); // Incomplete
static void getMonsterPalette(void); // Incomplete
static void initHardwareRegisters(void); // Incomplete
static void afterFunc_c10987(void); // Incomplete
static void func_c109a7(void); // Incomplete
static void func_c109b9(void); // Incomplete
static void func_c109ca(void); // Incomplete
static void func_c109d6(void); // Incomplete
static void func_c109e5(void); // Incomplete
static void func_c109f1(void); // Incomplete
static void func_c10a00(void); // Incomplete
static void func_c10a32(void); // Incomplete
static void func_c10a6e(void); // Incomplete
static void func_c10aea(void); // Incomplete
static void func_c10b1b(void); // Incomplete
static void func_c10b59(void); // Incomplete
static void playQueuedSong(void); // Incomplete
static void func_c10ba4(void); // Incomplete
static void updateNeoExdeathBattleBg(void); // Incomplete
static void func_c10f51(void); // Incomplete
static void updateUnderwaterTowerWalseBg(void); // Incomplete
static void updateDesertBg(void); // Incomplete
static void func_c11015(void); // Incomplete
static void func_c1105a(void); // Incomplete
static void updateKarnakCastleBg(void); // Incomplete
static void func_c1112f(void); // Incomplete
static void func_c11186(void); // Incomplete
static void func_c111c5(void); // Incomplete
static void func_c111d3(void); // Incomplete
static void func_c111e4(void); // Incomplete
static void updateBgScrollMosiacRegs(void); // Incomplete
static void func_c11235(void); // Incomplete
static void func_c1124a(void); // Incomplete
static void func_c112e8(void); // Incomplete
static void copyBtlBgToVram(void); // Incomplete
static void func_c1138e(void); // Incomplete
static void func_c113da(void); // Incomplete
static void func_c11434(void); // Incomplete
static void func_c11482(void); // Incomplete
static void func_c115d1(void); // Incomplete
static void func_c1162c(void); // Incomplete
static void func_c1169d(void); // Incomplete
static void func_c116f2(void); // Incomplete
static void func_c1170b(void); // Incomplete
static void func_c117c4(void); // Incomplete
static void func_c117d7(void); // Incomplete
static void func_c117f0(void); // Incomplete
static void func_c11815(void); // Incomplete
static void func_c1187f(void); // Incomplete
static void func_c118ae(void); // Incomplete
static void func_c118d2(void); // Incomplete
static void battleIrq(void); // Incomplete
static void battleNmi(void); // Incomplete
static void func_c11a57(void); // Incomplete
static void func_c11aa6(void); // Incomplete
static void func_c11b0d(void); // Incomplete
static void func_c11b65(void); // Incomplete
static void func_c11c84(void); // Incomplete
static void func_c11c8a(void); // Incomplete
static void blackWhiteMonsterPalette(void); // Incomplete
static void restoreMonsterPalette(void); // Incomplete
static void func_c11cdf(void); // Incomplete
static void func_c11ceb(void); // Incomplete
static void func_c11d25(void); // Incomplete
static void func_c11d48(void); // Incomplete
static void func_c11d65(void); // Incomplete
static void func_c11df6(void); // Incomplete
static void func_c11f22(void); // Incomplete
static void func_c1202f(void); // Incomplete
static void loadMonsterPalette(void); // Incomplete
static void loadMonsterGraphics(void); // Incomplete
static void getPtrMonsterPalette(void); // Incomplete
static void copyMonsterGraphicsToVram(void); // Incomplete
static void func_c12202(void); // Incomplete
static void getPtrMonsterGraphics(void); // Incomplete
static void func_c12289(void); // Incomplete
static void func_c122f2(void); // Incomplete
static void func_c12306(void); // Incomplete
static void func_c1242a(void); // Incomplete
static void func_c12454(void); // Incomplete
static void func_c12481(void); // Incomplete
static void func_c124d5(void); // Incomplete
static void loadCharGraphics(void); // Incomplete
static void func_c125a5(void); // Incomplete
static void func_c125e8(void); // Incomplete
static void loadCharPalettes(void); // Incomplete
static void func_c12689(void); // Incomplete
static void func_c126fb(void); // Incomplete
static void func_c12736(void); // Incomplete
static void copyCharGraphicsToVram(void); // Incomplete
static void func_c128d7(void); // Incomplete
static void drawBigTextString(void); // Incomplete
static void getNextByteString(void); // Incomplete
static void bigTextEscapeCode(void); // Incomplete
static void bartzName(void); // Incomplete
static void battleCommandName(void); // Incomplete
static void jobName(void); // Incomplete
static void attackName(void); // Incomplete
static void func_c12af9(void); // Incomplete
static void charName(void); // Incomplete
static void func_c12b35(void); // Incomplete
static void func_c12b85(void); // Incomplete
static void func_c12b91(void); // Incomplete
static void specialAbilityName(void); // Incomplete
static void monsterSpecialAttackName(void); // Incomplete
static void abilityName(void); // Incomplete
static void attackName(void); // Incomplete
static void func_c12c81(void); // Incomplete
static void func_c12c9a(void); // Incomplete
static void func_c12cab(void); // Incomplete
static void kanji(void); // Incomplete
static void drawKana(void); // Incomplete
static void drawSmallText(void); // Incomplete
static void drawSmallTextChar(void); // Incomplete
static void averageExp(void); // Incomplete
static void battleCount(void); // Incomplete
static void monstersSlain(void); // Incomplete
static void saveCount(void); // Incomplete
static void treasuresPercent(void); // Incomplete
static void smallTxtEscape01(void); // Incomplete
static void smallTxtEscape0d(void); // Incomplete
static void smallTxtEscape05(void); // Incomplete
static void smallTxtEscape06(void); // Incomplete
static void smallTxtEscape03(void); // Incomplete
static void decodeSmallTxtEscapeCode(void); // Incomplete
static void smallTxtEscape1b(void); // Incomplete
static void smallTxtEscape0f(void); // Incomplete
static void smallTxtEscape0e(void); // Incomplete
static void smallTxtEscape0b(void); // Incomplete
static void smallTxtEscape0c(void); // Incomplete
static void smallTxtEscape07(void); // Incomplete
static void smallTxtEscape08(void); // Incomplete
static void smallTxtEscape09(void); // Incomplete
static void smallTxtEscape0a(void); // Incomplete
static void func_c130d6(void); // Incomplete
static void func_c13112(void); // Incomplete
static void func_c1313f(void); // Incomplete
static void func_c13144(void); // Incomplete
static void func_c13149(void); // Incomplete
static void func_c1314e(void); // Incomplete
static void func_c13153(void); // Incomplete
static void func_c13158(void); // Incomplete
static void func_c1315d(void); // Incomplete
static void func_c13177(void); // Incomplete
static void func_c13182(void); // Incomplete
static void func_c1318d(void); // Incomplete
static void func_c13198(void); // Incomplete
static void func_c131a3(void); // Incomplete
static void func_c131aa(void); // Incomplete
static void func_c131b1(void); // Incomplete
static void func_c131b8(void); // Incomplete
static void func_c131bf(void); // Incomplete
static void func_c131c6(void); // Incomplete
static void func_c131cd(void); // Incomplete
static void func_c13231(void); // Incomplete
static void func_c1327b(void); // Incomplete
static void func_c132a5(void); // Incomplete
static void func_c132bc(void); // Incomplete
static void func_c132cb(void); // Incomplete
static void func_c13231(void); // Incomplete
static void func_c132da(void); // Incomplete
static void func_c132ed(void); // Incomplete
static void func_c132f0(void); // Incomplete
static void func_c13300(void); // Incomplete
static void func_c13309(void); // Incomplete
static void loadBattleBg(void); // Incomplete
static void loadBattleBgTileLayout(void); // Incomplete
static void func_c13577(void); // Incomplete
static void flipBattleBgHorizontailly(void); // Incomplete
static void setPriorityBitForBtlBgTiles(void); // Incomplete
static void clearPriorityBitForBtlBgTiles(void); // Incomplete
static void getNextByteForBtlBgTileFlipData(void); // Incomplete
static void getBattleBgTileFlip(void); // Incomplete
static void loadBattleBgPalette(void); // Incomplete
static void getPointerToBattleBgPalette(void); // Incomplete
static void loadBattleBgGfx(void); // Incomplete
static void reverseBitOrder(void); // Incomplete
static void func_c137b6(void); // Incomplete
static void func_c137ef(void); // Incomplete
static void func_c1382e(void); // Incomplete
static void func_c13835(void); // Incomplete
static void func_c138fe(void); // Incomplete
static void func_c13940(void); // Incomplete
static void func_c13954(void); // Incomplete
static void func_c1397e(void); // Incomplete
static void func_c139b2(void); // Incomplete
static void func_c139e2(void); // Incomplete
static void btlGfxFunc_openMenu(void); // Incomplete
static void btlGfxFunc_closeMenu(void); // Incomplete
static void func_c13a6e(void); // Incomplete
static void func_c13ad2(void); // Incomplete
static void func_c13ade(void); // Incomplete
static void func_c13aea(void); // Incomplete
static void func_c13b11(void); // Incomplete
static void func_c13b1f(void); // Incomplete
static void func_c13b5c(void); // Incomplete
static void func_c13b87(void); // Incomplete
static void func_c13c02(void); // Incomplete
static void func_c13c22(void); // Incomplete
static void func_c13c42(void); // Incomplete
static void func_c13c62(void); // Incomplete
static void func_c13c7f(void); // Incomplete
static void drawBtlMessage(void); // Incomplete
static void closeMessageWindow(void); // Incomplete
static void battleMenu_spellblade(void); // Incomplete
static void battleMenu_whiteMagic(void); // Incomplete
static void battleMenu_blackMagic(void); // Incomplete
static void battleMenu_timeMagic(void); // Incomplete
static void battleMenu_summon(void); // Incomplete
static void battleMenu_blueMagic(void); // Incomplete
static void battleMenu_song(void); // Incomplete
static void battleMenu_redMagic(void); // Incomplete
static void battleMenu_dualcast(void); // Incomplete
static void func_c13cff(void); // Incomplete
static void func_c13d8c(void); // Incomplete
static void initHdmaData(void); // Incomplete
static void func_c13ed3(void); // Incomplete
static void func_c13f53(void); // Incomplete
static void func_c13f60(void); // Incomplete
static void func_c13f71(void); // Incomplete
static void func_c13f95(void); // Incomplete
static void func_c13fa8(void); // Incomplete
static void func_c13ff4(void); // Incomplete
static void func_c1405b(void); // Incomplete
static void func_c140a0(void); // Incomplete
static void func_c140e4(void); // Incomplete
static void func_c1412f(void); // Incomplete
static void func_c1414b(void); // Incomplete
static void func_c1416b(void); // Incomplete
static void func_c14176(void); // Incomplete
static void func_c141a7(void); // Incomplete
static void func_c141be(void); // Incomplete
static void func_c141d5(void); // Incomplete
static void func_c141da(void); // Incomplete
static void func_c1421d(void); // Incomplete
static void func_c14224(void); // Incomplete
static void btlGfxFunc05(void); // Incomplete
static void func_c1427f(void); // Incomplete
static void func_c142f3(void); // Incomplete
static void func_c14316(void); // Incomplete
static void func_c14336(void); // Incomplete
static void func_c1434a(void); // Incomplete
static void func_c1434f(void); // Incomplete
static void func_c14365(void); // Incomplete
static void func_c143ce(void); // Incomplete
static void func_c1442e(void); // Incomplete
static void func_c14451(void); // Incomplete
static void func_c1445a(void); // Incomplete
static void func_c144c8(void); // Incomplete
static void func_c144d1(void); // Incomplete
static void func_c14552(void); // Incomplete
static void func_c1455b(void); // Incomplete
static void func_c1455e(void); // Incomplete
static void func_c145f1(void); // Incomplete
static void func_c14622(void); // Incomplete
static void func_c14641(void); // Incomplete
static void func_c14656(void); // Incomplete
static void battleCmdMenu_none(void); // Incomplete
static void battleCmdMenu0b(void); // Incomplete
static void battleCmdMenu_combine(void); // Incomplete
static void battleCmdMenu_drink(void); // Incomplete
static void battleCmdMenu_throw(void); // Incomplete
static void battleCmdMenu_spellblade(void); // Incomplete
static void battleCmdMenu_whiteMagic(void); // Incomplete
static void battleCmdMenu_blackMagic(void); // Incomplete
static void battleCmdMenu_timeMagic(void); // Incomplete
static void battleCmdMenu_summon(void); // Incomplete
static void battleCmdMenu_blueMagic(void); // Incomplete
static void battleCmdMenu_redMagic(void); // Incomplete
static void battleCmdMenu_song(void); // Incomplete
static void battleCmdMenu_dualcast(void); // Incomplete
static void func_c146e9(void); // Incomplete
static void func_c146fd(void); // Incomplete
static void func_c14735(void); // Incomplete
static void func_c14759(void); // Incomplete
static void func_c14773(void); // Incomplete
static void func_c14789(void); // Incomplete
static void func_c147a3(void); // Incomplete
static void battleCmdMenu_item(void); // Incomplete
static void func_c147ef(void); // Incomplete
static void func_c147fe(void); // Incomplete
static void func_c1483b(void); // Incomplete
static void func_c1485c(void); // Incomplete
static void func_c1486e(void); // Incomplete
static void func_c148a2(void); // Incomplete
static void func_c148f7(void); // Incomplete
static void func_c1491d(void); // Incomplete
static void func_c14930(void); // Incomplete
static void func_c1494d(void); // Incomplete
static void func_c1496a(void); // Incomplete
static void func_c14986(void); // Incomplete
static void func_c149c4(void); // Incomplete
static void func_c14a05(void); // Incomplete
static void func_c14a4f(void); // Incomplete
static void func_c14a68(void); // Incomplete
static void func_c14a86(void); // Incomplete
static void func_c14b22(void); // Incomplete
static void func_c14bbc(void); // Incomplete
static void func_c14be9(void); // Incomplete
static void func_c14bf6(void); // Incomplete
static void func_c14c1d(void); // Incomplete
static void func_c14c73(void); // Incomplete
static void func_c14c97(void); // Incomplete
static void func_c14cc4(void); // Incomplete
static void func_c14cef(void); // Incomplete
static void func_c14d28(void); // Incomplete
static void func_c14d3c(void); // Incomplete
static void func_c14d80(void); // Incomplete
static void func_c14e35(void); // Incomplete
static void func_c14e5e(void); // Incomplete
static void func_c14ea3(void); // Incomplete
static void func_c14ec6(void); // Incomplete
static void func_c14ee9(void); // Incomplete
static void func_c14f28(void); // Incomplete
static void func_c14f71(void); // Incomplete
static void func_c14f92(void); // Incomplete
static void func_c14fba(void); // Incomplete
static void func_c14ffe(void); // Incomplete
static void func_c15041(void); // Incomplete
static void func_c15086(void); // Incomplete
static void func_c150c9(void); // Incomplete
static void func_c1510e(void); // Incomplete
static void func_c15195(void); // Incomplete
static void func_c151a5(void); // Incomplete
static void func_c151e9(void); // Incomplete
static void func_c1522f(void); // Incomplete
static void func_c15270(void); // Incomplete
static void getMenuIdBatlCmd(void); // Incomplete
static void func_c152ad(void); // Incomplete
static void func_c152f6(void); // Incomplete
static void func_c15318(void); // Incomplete
static void func_c1531f(void); // Incomplete
static void func_c153ce(void); // Incomplete
static void func_c15494(void); // Incomplete
static void func_c154a1(void); // Incomplete
static void func_c15511(void); // Incomplete
static void func_c15536(void); // Incomplete
static void func_c1555b(void); // Incomplete
static void func_c15574(void); // Incomplete
static void func_c155d0(void); // Incomplete
static void func_c156e0(void); // Incomplete
static void func_c1571a(void); // Incomplete
static void func_c15750(void); // Incomplete
static void func_c1576c(void); // Incomplete
static void func_c15784(void); // Incomplete
static void func_c157b1(void); // Incomplete
static void func_c15806(void); // Incomplete
static void func_c1584b(void); // Incomplete
static void func_c15880(void); // Incomplete
static void func_c1588d(void); // Incomplete
static void func_c1594e(void); // Incomplete
static void func_c15ad0(void); // Incomplete
static void func_c15af9(void); // Incomplete
static void func_c15b65(void); // Incomplete
static void func_c15bb8(void); // Incomplete
static void func_c15b93(void); // Incomplete
static void func_c15ba3(void); // Incomplete
static void func_c15c88(void); // Incomplete
static void func_c15dd4(void); // Incomplete
static void func_c15dea(void); // Incomplete
static void func_c15e04(void); // Incomplete
static void func_c15e3b(void); // Incomplete
static void func_c15ee0(void); // Incomplete
static void func_c15f67(void); // Incomplete
static void func_c15f6b(void); // Incomplete
static void func_c15f92(void); // Incomplete
static void func_c15fcc(void); // Incomplete
static void func_c15ff0(void); // Incomplete
static void func_c1605c(void); // Incomplete
static void func_c1608e(void); // Incomplete
static void func_c1609d(void); // Incomplete
static void func_c160bb(void); // Incomplete
static void func_c160cc(void); // Incomplete
static void func_c160da(void); // Incomplete
static void func_c161b6(void); // Incomplete
static void func_c161c3(void); // Incomplete
static void func_c16268(void); // Incomplete
static void func_c16295(void); // Incomplete
static void func_c162d7(void); // Incomplete
static void func_c163aa(void); // Incomplete
static void func_c16423(void); // Incomplete
static void func_c16486(void); // Incomplete
static void func_c1649a(void); // Incomplete
static void func_c164b0(void); // Incomplete
static void func_c16533(void); // Incomplete
static void func_c165d7(void); // Incomplete
static void func_c1667c(void); // Incomplete
static void func_c166d5(void); // Incomplete
static void func_c1673a(void); // Incomplete
static void func_c167d3(void); // Incomplete
static void func_c167e4(void); // Incomplete
static void func_c168f1(void); // Incomplete
static void func_c1697d(void); // Incomplete
static void func_c1698c(void); // Incomplete
static void decodeStringOfAnimFrameTiles(void); // Incomplete
static void decodeSingleAnimFrameTiles(void); // Incomplete
static void hideDamageNumeralSprites(void); // Incomplete
static void func_c16c08(void); // Incomplete
static void func_c16c1a(void); // Incomplete
static void updateDamageNumeralSpritesGolem(void); // Incomplete
static void updateDamageNumeralSprites(void); // Incomplete
static void func_c16d5c(void); // Incomplete
static void func_c16e1c(void); // Incomplete
static void func_c16e52(void); // Incomplete
static void func_c16ed4(void); // Incomplete
static void func_c16ef6(void); // Incomplete
static void func_c16fa4(void); // Incomplete
static void func_c16fd5(void); // Incomplete
static void func_c1703a(void); // Incomplete
static void func_c1705c(void); // Incomplete
static void func_c1706b(void); // Incomplete
static void func_c170d3(void); // Incomplete
static void func_c172c1(void); // Incomplete
static void func_c172db(void); // Incomplete
static void func_c172fb(void); // Incomplete
static void func_c17374(void); // Incomplete
static void func_c173ec(void); // Incomplete
static void func_c17471(void); // Incomplete
static void func_c174d8(void); // Incomplete
static void func_c17529(void); // Incomplete
static void func_c17539(void); // Incomplete
static void func_c1754d(void); // Incomplete
static void func_c17576(void); // Incomplete
static void func_c175ac(void); // Incomplete
static void func_c175bb(void); // Incomplete
static void btlGfxFunc08(void); // Incomplete
static void func_c17602(void); // Incomplete
static void func_c17613(void); // Incomplete
static void func_c17624(void); // Incomplete
static void func_c1763d(void); // Incomplete
static void func_c1765e(void); // Incomplete
static void func_c1766b(void); // Incomplete
static void btlGfxFunc_doomAnim(void); // Incomplete
static void func_c17695(void); // Incomplete
static void func_c176bc(void); // Incomplete
static void func_c176fe(void); // Incomplete
static void func_c1772c(void); // Incomplete
static void func_c1778a(void); // Incomplete
static void func_c1781d(void); // Incomplete
static void func_c17864(void); // Incomplete
static void func_c178ab(void); // Incomplete
static void miscEffect_flashScreen(void); // Incomplete
static void updateScreenFlash(void); // Incomplete
static void func_c17930(void); // Incomplete
static void func_c17979(void); // Incomplete
static void func_c179a5(void); // Incomplete
static void func_c17a2a(void); // Incomplete
static void func_c17a93(void); // Incomplete
static void func_c17b02(void); // Incomplete
static void func_c17b43(void); // Incomplete
static void func_c17ba0(void); // Incomplete
static void func_c17c49(void); // Incomplete
static void func_c17cb1(void); // Incomplete
static void func_c17d52(void); // Incomplete
static void func_c17c5f(void); // Incomplete
static void func_c17d8c(void); // Incomplete
static void func_c17da7(void); // Incomplete
static void func_c17db0(void); // Incomplete
static void func_c17de7(void); // Incomplete
static void func_c17e1b(void); // Incomplete
static void func_c17e1f(void); // Incomplete
static void func_c17e44(void); // Incomplete
static void func_c17e6b(void); // Incomplete
static void func_c17e8b(void); // Incomplete
static void func_c17eab(void); // Incomplete
static void func_c17eb4(void); // Incomplete
static void func_c17ee4(void); // Incomplete
static void func_c17ef5(void); // Incomplete
static void func_c17f2b(void); // Incomplete
static void func_c17f34(void); // Incomplete
static void func_c17f43(void); // Incomplete
static void func_c17f70(void); // Incomplete
static void func_c17f9a(void); // Incomplete
static void func_c17fc7(void); // Incomplete
static void func_c17ffe(void); // Incomplete
static void moveBackAfterAttack(void); // Incomplete
static void moveForwardToAttack(void); // Incomplete
static void waitForCharToMoveForward(void); // Incomplete
static void flashActiveMonster(void); // Incomplete
static void flashMonster(void); // Incomplete
static void wait(void); // Incomplete
static void func_c1814a(void); // Incomplete
static void func_c18179(void); // Incomplete
static void btlGfxFunc_execGfxScript(void); // Incomplete
static void gfxScriptCmd_execMisc(void); // Incomplete
static void miscEffect09(void); // Incomplete
static void miscEffect0A(void); // Incomplete
static void miscEffect_wait(void); // Incomplete
static void miscEffect04(void); // Incomplete
static void func_c182c6(void); // Incomplete
static void miscEffect_shakeScreen(void); // Incomplete
static void miscEffect05(void); // Incomplete
static void miscEffect08(void); // Incomplete
static void miscEffect06(void); // Incomplete
static void miscEffect_playSoundEffect(void); // Incomplete
static void miscEffect_playSong(void); // Incomplete
static void func_c18344(void); // Incomplete
static void func_c18352(void); // Incomplete
static void func_c18360(void); // Incomplete
static void func_c18367(void); // Incomplete
static void func_c1836e(void); // Incomplete
static void func_c18382(void); // Incomplete
static void func_c1839b(void); // Incomplete
static void func_c183b4(void); // Incomplete
static void func_c183ca(void); // Incomplete
static void func_c18400(void); // Incomplete
static void func_c18436(void); // Incomplete
static void func_c18467(void); // Incomplete
static void func_c18498(void); // Incomplete
static void showMonster_fadeIn(void); // Incomplete
static void func_c184b5(void); // Incomplete
static void showMonster_ironClaw(void); // Incomplete
static void showMonster_merugene3(void); // Incomplete
static void showMonster_merugene4(void); // Incomplete
static void showMonster_discreet(void); // Incomplete
static void showMonster_motorTrap(void); // Incomplete
static void showMonster_fadeAndDrop(void); // Incomplete
static void showMonster_merugene1(void); // Incomplete
static void showMonster_merugene2(void); // Incomplete
static void showMonster_switch(void); // Incomplete
static void func_c185a6(void); // Incomplete
static void func_c185af(void); // Incomplete
static void showMonster_transform(void); // Incomplete
static void showMonster_pages(void); // Incomplete
static void func_c18695(void); // Incomplete
static void showMonster_sandworm(void); // Incomplete
static void doMonsterEntry(void); // Incomplete
static void func_c1875c(void); // Incomplete
static void func_c1879d(void); // Incomplete
static void func_c187cf(void); // Incomplete
static void monsterEntry02(void); // Incomplete
static void monsterEntry04(void); // Incomplete
static void func_c18836(void); // Incomplete
static void func_c1886b(void); // Incomplete
static void func_c188a8(void); // Incomplete
static void monsterEntry03(void); // Incomplete
static void monsterEntry05(void); // Incomplete
static void monsterEntry_enterFromSide(void); // Incomplete
static void monsterEntry_enterFromTop(void); // Incomplete
static void func_c189af(void); // Incomplete
static void func_c189c2(void); // Incomplete
static void showMonster_neoExdeath(void); // Incomplete
static void func_c18b2a(void); // Incomplete
static void gfxScriptCmd_showMonster(void); // Incomplete
static void gfxScriptCmd_execGfxCmd(void); // Incomplete
static void func_c18b93(void); // Incomplete
static void func_c18baa(void); // Incomplete
static void showAttackName(void); // Incomplete
static void animCommand_displayQueuedBtlMsg(void); // Incomplete
static void displayBattleMessage(void); // Incomplete
static void waitForMessage(void); // Incomplete
static void showNeoExdeathIntroDialog(void); // Incomplete
static void gfxScriptCmd_showBattleDialog(void); // Incomplete
static void displayBattleDialog(void); // Incomplete
static void func_c18cf1(void); // Incomplete
static void showCharInReadyStance(void); // Incomplete
static void showCharInNormalStance(void); // Incomplete
static void getAttackerId(void); // Incomplete
static void getTargetId(void); // Incomplete
static void func_c18d3b(void); // Incomplete
static void func_c18d41(void); // Incomplete
static void getGfxScriptParam3(void); // Incomplete
static void getGfxScriptParam2(void); // Incomplete
static void getGfxScriptParam4(void); // Incomplete
static void getGfxScriptParam1(void); // Incomplete
static void getGfxScriptParam3(void); // Incomplete
static void abilityAnim(void); // Incomplete
static void func_c18d74(void); // Incomplete
static void abilityAnimCredits_Knight(void); // Incomplete
static void abilityAnimCredits_JobMoveBack(void); // Incomplete
static void abilityAnimCredits_Monk(void); // Incomplete
static void abilityAnimCredits_Thief(void); // Incomplete
static void abilityAnimCredits_Dragoon(void); // Incomplete
static void abilityAnimCredits_Ninja(void); // Incomplete
static void abilityAnimCredits_Samurai(void); // Incomplete
static void abilityAnimCredits_Berserker(void); // Incomplete
static void abilityAnimCredits_Ranger(void); // Incomplete
static void abilityAnimCredits_MysticKnight(void); // Incomplete
static void abilityAnimCredits_WhiteMage(void); // Incomplete
static void abilityAnimCredits_BlackMage(void); // Incomplete
static void abilityAnimCredits_TimeMage(void); // Incomplete
static void abilityAnimCredits_Summoner(void); // Incomplete
static void abilityAnimCredits_BlueMage(void); // Incomplete
static void abilityAnimCredits_RedMage(void); // Incomplete
static void abilityAnimCredits_Beastmaster(void); // Incomplete
static void abilityAnimCredits_Chemist(void); // Incomplete
static void abilityAnimCredits_Geomancer(void); // Incomplete
static void abilityAnimCredits_Bard(void); // Incomplete
static void abilityAnimCredits_Dancer(void); // Incomplete
static void abilityAnimCredits_Mime(void); // Incomplete
static void abilityAnimCredits_Freelancer(void); // Incomplete
static void func_c18f3c(void); // Incomplete
static void showCharStatsInCredicts(void); // Incomplete
static void func_c1931a(void); // Incomplete
static void func_c1933e(void); // Incomplete
static void func_c19360(void); // Incomplete
static void func_c193af(void); // Incomplete
static void func_c1942f(void); // Incomplete
static void func_c1943d(void); // Incomplete
static void func_c19443(void); // Incomplete
static void func_c1946b(void); // Incomplete
static void func_c19481(void); // Incomplete
static void func_c194ea(void); // Incomplete
static void func_c19559(void); // Incomplete
static void func_c19581(void); // Incomplete
static void func_c195a6(void); // Incomplete
static void func_c195bf(void); // Incomplete
static void func_c1962c(void); // Incomplete
static void setAttackerAnimFrame(void); // Incomplete
static void func_c19709(void); // Incomplete
static void func_c1971b(void); // Incomplete
static void func_c19725(void); // Incomplete
static void abilityAnim_hide(void); // Incomplete
static void abilityAnim_show(void); // Incomplete
static void runOnOffScreen(void); // Incomplete
static void func_c1979e(void); // Incomplete
static void abilityAnim_guard(void); // Incomplete
static void abilityAnim_dance(void); // Incomplete
static void abilityAnim_flirt(void); // Incomplete
static void func_c19897(void); // Incomplete
static void abilityAnim_catch(void); // Incomplete
static void abilityAnim_gilToss(void); // Incomplete
static void func_c198d3(void); // Incomplete
static void abilityAnim_lance(void); // Incomplete
static void abilityAnim_tame(void); // Incomplete
static void abilityAnim_pray(void); // Incomplete
static void abilityAnim_revive(void); // Incomplete
static void abilityAnim_smoke(void); // Incomplete
static void abilityAnim_steal(void); // Incomplete
static void abilityAnim_chakra(void); // Incomplete
static void abilityAnim_image(void); // Incomplete
static void abilityAnim_def(void); // Incomplete
static void abilityAnim_focus(void); // Incomplete
static void func_c1999c(void); // Incomplete
static void abilityAnim_intRocket(void); // Incomplete
static void abilityAnim_jumpAttack(void); // Incomplete
static void func_c19b5b(void); // Incomplete
static void abilityAnim_jumpUp(void); // Incomplete
static void abilityAnim_slash(void); // Incomplete
static void abilityAnim_kick(void); // Incomplete
static void func_c19d37(void); // Incomplete
static void func_c19d3c(void); // Incomplete
static void func_c19d41(void); // Incomplete
static void func_c19d46(void); // Incomplete
static void func_c19d4b(void); // Incomplete
static void getPtrCharGfxProp(void); // Incomplete
static void func_c19d8c(void); // Incomplete
static void waitForDamageNumerals(void); // Incomplete
static void func_c19da1(void); // Incomplete
static void func_c19db3(void); // Incomplete
static void func_c19dcb(void); // Incomplete
static void func_c19e0a(void); // Incomplete
static void abilityAnim_row(void); // Incomplete
static void func_c19e89(void); // Incomplete
static void func_c19ed8(void); // Incomplete
static void func_c19ee7(void); // Incomplete
static void abilityAnim_throw(void); // Incomplete
static void abilityAnim_fight(void); // Incomplete
static void func_c19fed(void); // Incomplete
static void func_c1a01d(void); // Incomplete

// Execute Battle Graphics
void execBtlGfx(void) {}

void func_c10003(void) {}

void func_c10006(void) {}

void func_c10009(void) {}

static void func_c1003f(void) {}

static void func_c10092(void) {}

static void func_c100c6(void) {}

static void func_c100f2(void) {}

static void func_c1010b(void) {}

static void func_c1014c(void) {}

static void func_c10158(void) {}

static void func_c1016c(void) {}

static void func_c101e4(void) {}

static void func_c101f6(void) {}

static void func_c101fe(void) {}

static void func_c10208(void) {}

// Address: _020d
static void showDamageNumerals(void) {}

static void func_c10276(void) {}

static void func_c10293(void) {}

static void func_c102ab(void) {}

static void func_c102df(void) {}

static void func_c102e0(void) {}

static void func_c102f2(void) {}

static void func_c102fe(void) {}

static void func_c10348(void) {}

// Address: _03a6
static void updateSongTempoMult(void) {}

// Address: _03f0
static void updateReflectSfx(void) {}

static void func_c10401(void) {}

// Address: _0490 only Returns to SubRoutine

static void func_c10491(void) {}

// Address: _04c9
static void initRam(void) {}

// Address: _081c
static void updateSavedCursorChecksums(void) {}

// Address: _082c
static void validateSavedCursorChecksums(void) {}

// Address: _0847
static void resetSavedCursorPos(void) {}

// Address: _085a
static void calcSavedCursorChecksum(void) {}

// Address: _0871
static void clearSavedCursorPos(void) {}

// Address: _087f
static void getMonsterPalette(void) {}

// Address: _0888
static void initHardwareRegisters(void) {}

static void afterFunc_c10987(void) {}

static void func_c109a7(void) {}

static void func_c109b9(void) {}

static void func_c109ca(void) {}

static void func_c109d6(void) {}

static void func_c109e5(void) {}

static void func_c109f1(void) {}

static void func_c10a00(void) {}

static void func_c10a32(void) {}

static void func_c10a6e(void) {}

static void func_c10aea(void) {}

static void func_c10b1b(void) {}

static void func_c10b59(void) {}

// Address: _0b81
static void playQueuedSong(void) {}

static void func_c10ba4(void) {}

// Address: _0c5f
static void updateNeoExdeathBattleBg(void) {}

static void func_c10f51(void) {}

// Address: _0fc3
static void updateUnderwaterTowerWalseBg(void) {}

// Address: _0fd4
static void updateDesertBg(void) {}

static void func_c11015(void) {}

static void func_c1105a(void) {}

// Address: _10eb
static void updateKarnakCastleBg(void) {}

static void func_c1112f(void) {}

static void func_c11186(void) {}

static void func_c111c5(void) {}

static void func_c111d3(void) {}

static void func_c111e4(void) {}

// Address: _11f5
static void updateBgScrollMosiacRegs(void) {}

static void func_c11235(void) {}

static void func_c1124a(void) {}

static void func_c112e8(void) {}

// Address: _133d
static void copyBtlBgToVram(void) {}

static void func_c1138e(void) {}

static void func_c113da(void) {}

static void func_c11434(void) {}

static void func_c11482(void) {}

static void func_c115d1(void) {}

static void func_c1162c(void) {}

static void func_c1169d(void) {}

static void func_c116f2(void) {}

static void func_c1170b(void) {}

static void func_c117c4(void) {}

static void func_c117d7(void) {}

static void func_c117f0(void) {}

static void func_c11815(void) {}

static void func_c1187f(void) {}

static void func_c118ae(void) {}

static void func_c118d2(void) {}

// Address: _19e9
static void battleIrq(void) {}

// Address: _19ea
static void battleNmi(void) {}

static void func_c11a57(void) {}

static void func_c11aa6(void) {}

static void func_c11b0d(void) {}

static void func_c11b65(void) {}

static void func_c11c84(void) {}

static void func_c11c8a(void) {}

// Address: _1cb1
static void blackWhiteMonsterPalette(void) {}

// Address: _1cb8
static void restoreMonsterPalette(void) {}

static void func_c11cdf(void) {}

static void func_c11ceb(void) {}

static void func_c11d25(void) {}

static void func_c11d48(void) {}

static void func_c11d65(void) {}

static void func_c11df6(void) {}

static void func_c11f22(void) {}

static void func_c1202f(void) {}

// Address: _2068
static void loadMonsterPalette(void) {}

// Address: _20c4
static void loadMonsterGraphics(void) {}

// Address: _2133
static void getPtrMonsterPalette(void) {}

// Address: _2157
static void copyMonsterGraphicsToVram(void) {}

static void func_c12202(void) {}

// Address: _2251
static void getPtrMonsterGraphics(void) {}

static void func_c12289(void) {}

static void func_c122f2(void) {}

static void func_c12306(void) {}

static void func_c1242a(void) {}

static void func_c12454(void) {}

static void func_c12481(void) {}

static void func_c124d5(void) {}

// Address: _24d5
static void loadCharGraphics(void) {}

static void func_c125a5(void) {}

static void func_c125e8(void) {}

// Address: _2607
static void loadCharPalettes(void) {}

static void func_c12689(void) {}

static void func_c126fb(void) {}

static void func_c12736(void) {}

// Address: _28c4
static void copyCharGraphicsToVram(void) {}

static void func_c128d7(void) {}

// Address: _2971
static void drawBigTextString(void) {}

// Address: _299a
static void getNextByteString(void) {}

// Address: _29a0
static void bigTextEscapeCode(void) {}

// Address: _29f1
static void bartzName(void) {}

// Address: _2a2f
static void battleCommandName(void) {}

// Address: _2a6e
static void jobName(void) {}

// Address: _2a90
static void attackName(void) {}

static void func_c12af9(void) {}

// Address: _2b13
static void charName(void) {}

static void func_c12b35(void) {}

static void func_c12b85(void) {}

static void func_c12b91(void) {}

// Address: _2b9d
static void specialAbilityName(void) {}

// Address: _2bb6
static void monsterSpecialAttackName(void) {}

// Address: _2bdb
static void abilityName(void) {}

// Address: _2c15
static void attackName(void) {}

static void func_c12c81(void) {}

static void func_c12c9a(void) {}

static void func_c12cab(void) {}

// Address: _2cb2
static void kanji(void) {}

// Address: _2cf1
static void drawKana(void) {}

// Address: _2dac
static void drawSmallText(void) {}

// Address: _2dea
static void drawSmallTextChar(void) {}

// Address: _2e55
static void averageExp(void) {}

// Address: _2e9a
static void battleCount(void) {}

// Address: _2e9f
static void monstersSlain(void) {}

// Address: _2ea4
static void saveCount(void) {}

// Address: _2ebf
static void treasuresPercent(void) {}

// Address: _2f0f only Return to SubRoutine

// Address: _2f10
static void smallTxtEscape01(void) {}

// Address: _2f29
static void smallTxtEscape0d(void) {}

// Address: _2f31
static void smallTxtEscape05(void) {}

// Address: _2f42
static void smallTxtEscape06(void) {}

// Address: _2f55
static void smallTxtEscape03(void) {}

// Address: _2f5d
static void decodeSmallTxtEscapeCode(void) {}

// Address: _2f6e
static void smallTxtEscape1b(void) {}

// Address: _2fa3
static void smallTxtEscape0f(void) {}

// Address: _2fe3
static void smallTxtEscape0e(void) {}

// Address: _3004
static void smallTxtEscape0b(void) {}

// Address: _303e
static void smallTxtEscape0c(void) {}

// Address: _3061
static void smallTxtEscape07(void) {}

// Address: _306e
static void smallTxtEscape08(void) {}

// Address: _307b
static void smallTxtEscape09(void) {}

// Address: _3004
static void smallTxtEscape0a(void) {}

static void func_c130d6(void) {}

static void func_c13112(void) {}

static void func_c1313f(void) {}

static void func_c13144(void) {}

static void func_c13149(void) {}

static void func_c1314e(void) {}

static void func_c13153(void) {}

static void func_c13158(void) {}

static void func_c1315d(void) {}

static void func_c13177(void) {}

static void func_c13182(void) {}

static void func_c1318d(void) {}

static void func_c13198(void) {}

static void func_c131a3(void) {}

static void func_c131aa(void) {}

static void func_c131b1(void) {}

static void func_c131b8(void) {}

static void func_c131bf(void) {}

static void func_c131c6(void) {}

static void func_c131cd(void) {}

static void func_c13231(void) {}

static void func_c1327b(void) {}

static void func_c132a5(void) {}

static void func_c132bc(void) {}

static void func_c132cb(void) {}

static void func_c13231(void) {}

static void func_c132da(void) {}

static void func_c132ed(void) {}

static void func_c132f0(void) {}

static void func_c13300(void) {}

static void func_c13309(void) {}

// Address: _335a
static void loadBattleBg(void) {}

// Address: _33cc
static void loadBattleBgTileLayout(void) {}

static void func_c13577(void) {}

// Address: _3599
static void flipBattleBgHorizontailly(void) {}

// Address: _35e1
static void setPriorityBitForBtlBgTiles(void) {}

// Address: _35fe
static void clearPriorityBitForBtlBgTiles(void) {}

// Address: _361b
static void getNextByteForBtlBgTileFlipData(void) {}

// Address: _3670
static void getBattleBgTileFlip(void) {}

// Address: _36a5
static void loadBattleBgPalette(void) {}

// Address: _36dc
static void getPointerToBattleBgPalette(void) {}

// Address: _36eb decompresses battle bg graphics

// Address: _3725
static void loadBattleBgGfx(void) {}

// Address: _37ac
static void reverseBitOrder(void) {}

static void func_c137b6(void) {}

static void func_c137ef(void) {}

// Address: _382d only Return to SubRoutine

static void func_c1382e(void) {}

static void func_c13835(void) {}

static void func_c138fe(void) {}

static void func_c13940(void) {}

static void func_c13954(void) {}

static void func_c1397e(void) {}

static void func_c139b2(void) {}

static void func_c139e2(void) {}

// Address: _39f9
static void btlGfxFunc_openMenu(void) {}

// Address: _3a55
static void btlGfxFunc_closeMenu(void) {}

static void func_c13a6e(void) {}

// Address: _3a95 only Return to SubRoutine

static void func_c13ad2(void) {}

static void func_c13ade(void) {}

static void func_c13aea(void) {}

static void func_c13b11(void) {}

static void func_c13b1f(void) {}

static void func_c13b5c(void) {}

static void func_c13b87(void) {}

static void func_c13c02(void) {}

static void func_c13c22(void) {}

static void func_c13c42(void) {}

static void func_c13c62(void) {}

static void func_c13c7f(void) {}

// Address: _3c88
static void drawBtlMessage(void) {}

// Address: _3cbb
static void closeMessageWindow(void) {}

// Address: _3cd3
static void battleMenu_spellblade(void) {}

// Address: _3cd7
static void battleMenu_whiteMagic(void) {}

// Address: _3cdc
static void battleMenu_blackMagic(void) {}

// Address: _3ce1
static void battleMenu_timeMagic(void) {}

// Address: _3ce6
static void battleMenu_summon(void) {}

// Address: _3ceb
static void battleMenu_blueMagic(void) {}

// Address: _3cf0
static void battleMenu_song(void) {}

// Address: _3cf5
static void battleMenu_redMagic(void) {}

// Address: _3cfa
static void battleMenu_dualcast(void) {}

static void func_c13cff(void) {}

static void func_c13d8c(void) {}

// Address: _3dc5
static void initHdmaData(void) {}

static void func_c13ed3(void) {}

static void func_c13f53(void) {}

static void func_c13f60(void) {}

static void func_c13f71(void) {}

static void func_c13f95(void) {}

static void func_c13fa8(void) {}

static void func_c13ff4(void) {}

static void func_c1405b(void) {}

static void func_c140a0(void) {}

static void func_c140e4(void) {}

static void func_c1412f(void) {}

static void func_c1414b(void) {}

static void func_c1416b(void) {}

static void func_c14176(void) {}

static void func_c141a7(void) {}

static void func_c141be(void) {}

static void func_c141d5(void) {}

static void func_c141da(void) {}

static void func_c1421d(void) {}

static void func_c14224(void) {}

// Address: _422b
static void btlGfxFunc05(void) {}

static void func_c1427f(void) {}

static void func_c142f3(void) {}

static void func_c14316(void) {}

static void func_c14336(void) {}

static void func_c1434a(void) {}

static void func_c1434f(void) {}

static void func_c14365(void) {}

static void func_c143ce(void) {}

static void func_c1442e(void) {}

static void func_c14451(void) {}

static void func_c1445a(void) {}

static void func_c144c8(void) {}

static void func_c144d1(void) {}

static void func_c14552(void) {}

static void func_c1455b(void) {}

static void func_c1455e(void) {}

static void func_c145f1(void) {}

static void func_c14622(void) {}

static void func_c14641(void) {}

static void func_c14656(void) {}

// Address: _4676
static void battleCmdMenu_none(void) {}

// Address: _468c
static void battleCmdMenu0b(void) {}

// Address: _468d
static void battleCmdMenu_combine(void) {}

// Address: _469f
static void battleCmdMenu_drink(void) {}

// Address: _46ab
static void battleCmdMenu_throw(void) {}

// Address: _46b7
static void battleCmdMenu_spellblade(void) {}

// Address: _46bc
static void battleCmdMenu_whiteMagic(void) {}

// Address: _46c1
static void battleCmdMenu_blackMagic(void) {}

// Address: _46c6
static void battleCmdMenu_timeMagic(void) {}

// Address: _46cb
static void battleCmdMenu_summon(void) {}

// Address: _46d0
static void battleCmdMenu_blueMagic(void) {}

// Address: _46d5
static void battleCmdMenu_redMagic(void) {}

// Address: _46da
static void battleCmdMenu_song(void) {}

// Address: _46df
static void battleCmdMenu_dualcast(void) {}

static void func_c146e9(void) {}

static void func_c146fd(void) {}

static void func_c14735(void) {}

static void func_c14759(void) {}

static void func_c14773(void) {}

static void func_c14789(void) {}

static void func_c147a3(void) {}

// Address: _47b6
static void battleCmdMenu_item(void) {}

static void func_c147ef(void) {}

static void func_c147fe(void) {}

static void func_c1483b(void) {}

static void func_c1485c(void) {}

static void func_c1486e(void) {}

static void func_c148a2(void) {}

static void func_c148f7(void) {}

static void func_c1491d(void) {}

static void func_c14930(void) {}

static void func_c1494d(void) {}

static void func_c1496a(void) {}

static void func_c14986(void) {}

static void func_c149c4(void) {}

static void func_c14a05(void) {}

static void func_c14a4f(void) {}

static void func_c14a68(void) {}

static void func_c14a86(void) {}

static void func_c14b22(void) {}

static void func_c14bbc(void) {}

static void func_c14be9(void) {}

static void func_c14bf6(void) {}

static void func_c14c1d(void) {}

static void func_c14c73(void) {}

static void func_c14c97(void) {}

static void func_c14cc4(void) {}

static void func_c14cef(void) {}

static void func_c14d28(void) {}

static void func_c14d3c(void) {}

static void func_c14d80(void) {}

static void func_c14e35(void) {}

static void func_c14e5e(void) {}

static void func_c14ea3(void) {}

static void func_c14ec6(void) {}

static void func_c14ee9(void) {}

static void func_c14f28(void) {}

static void func_c14f71(void) {}

static void func_c14f92(void) {}

static void func_c14fba(void) {}

static void func_c14ffe(void) {}

static void func_c15041(void) {}

static void func_c15086(void) {}

static void func_c150c9(void) {}

static void func_c1510e(void) {}

static void func_c15195(void) {}

static void func_c151a5(void) {}

static void func_c151e9(void) {}

static void func_c1522f(void) {}

static void func_c15270(void) {}

// Address: _52a7
static void getMenuIdBatlCmd(void) {}

static void func_c152ad(void) {}

static void func_c152f6(void) {}

static void func_c15318(void) {}

static void func_c1531f(void) {}

static void func_c153ce(void) {}

static void func_c15494(void) {}

static void func_c154a1(void) {}

static void func_c15511(void) {}

static void func_c15536(void) {}

static void func_c1555b(void) {}

static void func_c15574(void) {}

static void func_c155d0(void) {}

static void func_c156e0(void) {}

static void func_c1571a(void) {}

static void func_c15750(void) {}

static void func_c1576c(void) {}

static void func_c15784(void) {}

static void func_c157b1(void) {}

static void func_c15806(void) {}

static void func_c1584b(void) {}

static void func_c15880(void) {}

static void func_c1588d(void) {}

static void func_c1594e(void) {}

static void func_c15ad0(void) {}

static void func_c15af9(void) {}

static void func_c15b65(void) {}

static void func_c15bb8(void) {}

static void func_c15b93(void) {}

static void func_c15ba3(void) {}

static void func_c15c88(void) {}

static void func_c15dd4(void) {}

static void func_c15dea(void) {}

static void func_c15e04(void) {}

static void func_c15e3b(void) {}

static void func_c15ee0(void) {}

static void func_c15f67(void) {}

static void func_c15f6b(void) {}

static void func_c15f92(void) {}

static void func_c15fcc(void) {}

static void func_c15ff0(void) {}

static void func_c1605c(void) {}

static void func_c1608e(void) {}

static void func_c1609d(void) {}

static void func_c160bb(void) {}

static void func_c160cc(void) {}

static void func_c160da(void) {}

static void func_c161b6(void) {}

static void func_c161c3(void) {}

static void func_c16268(void) {}

static void func_c16295(void) {}

static void func_c162d7(void) {}

static void func_c163aa(void) {}

static void func_c16423(void) {}

static void func_c16486(void) {}

static void func_c1649a(void) {}

static void func_c164b0(void) {}

static void func_c16533(void) {}

static void func_c165d7(void) {}

static void func_c1667c(void) {}

static void func_c166d5(void) {}

static void func_c1673a(void) {}

static void func_c167d3(void) {}

static void func_c167e4(void) {}

static void func_c168f1(void) {}

static void func_c1697d(void) {}

static void func_c1698c(void) {}

// Address: _6ab1
static void decodeStringOfAnimFrameTiles(void) {}

// Address: _6b6c
static void decodeSingleAnimFrameTiles(void) {}

// Address: _6bef
static void hideDamageNumeralSprites(void) {}

static void func_c16c08(void) {}

static void func_c16c1a(void) {}

// Address: _6c58
static void updateDamageNumeralSpritesGolem(void) {}

// Address: _6cd4
static void updateDamageNumeralSprites(void) {}

static void func_c16d5c(void) {}

static void func_c16e1c(void) {}

static void func_c16e52(void) {}

static void func_c16ed4(void) {}

static void func_c16ef6(void) {}

static void func_c16fa4(void) {}

static void func_c16fd5(void) {}

static void func_c1703a(void) {}

static void func_c1705c(void) {}

static void func_c1706b(void) {}

static void func_c170d3(void) {}

static void func_c172c1(void) {}

static void func_c172db(void) {}

static void func_c172fb(void) {}

static void func_c17374(void) {}

static void func_c173ec(void) {}

static void func_c17471(void) {}

static void func_c174d8(void) {}

static void func_c17529(void) {}

static void func_c17539(void) {}

static void func_c1754d(void) {}

static void func_c17576(void) {}

static void func_c175ac(void) {}

static void func_c175bb(void) {}

// Address: _75d7
static void btlGfxFunc08(void) {}

static void func_c17602(void) {}

static void func_c17613(void) {}

static void func_c17624(void) {}

static void func_c1763d(void) {}

static void func_c1765e(void) {}

static void func_c1766b(void) {}

// Address: _768d
static void btlGfxFunc_doomAnim(void) {}

static void func_c17695(void) {}

static void func_c176bc(void) {}

static void func_c176fe(void) {}

static void func_c1772c(void) {}

static void func_c1778a(void) {}

static void func_c1781d(void) {}

static void func_c17864(void) {}

static void func_c178ab(void) {}

// Address: _78f5
static void miscEffect_flashScreen(void) {}

// Address: _78fe
static void updateScreenFlash(void) {}

static void func_c17930(void) {}

static void func_c17979(void) {}

static void func_c179a5(void) {}

static void func_c17a2a(void) {}

static void func_c17a93(void) {}

static void func_c17b02(void) {}

static void func_c17b43(void) {}

static void func_c17ba0(void) {}

static void func_c17c49(void) {}

static void func_c17cb1(void) {}

static void func_c17d52(void) {}

static void func_c17c5f(void) {}

// Address: _7d79 only JuMPs to ($0088)

static void func_c17d8c(void) {}

static void func_c17da7(void) {}

static void func_c17db0(void) {}

static void func_c17de7(void) {}

static void func_c17e1b(void) {}

static void func_c17e1f(void) {}

static void func_c17e44(void) {}

static void func_c17e6b(void) {}

static void func_c17e8b(void) {}

static void func_c17eab(void) {}

static void func_c17eb4(void) {}

// Address: _7ed1 only Return To Subroutine

// Address: _7ee1 only JuMPs to _7f34

static void func_c17ee4(void) {}

static void func_c17ef5(void) {}

static void func_c17f2b(void) {}

static void func_c17f34(void) {}

static void func_c17f43(void) {}

static void func_c17f70(void) {}

static void func_c17f9a(void) {}

static void func_c17fc7(void) {}

static void func_c17ffe(void) {}

// Address: _8062
static void moveBackAfterAttack(void) {}

// Address: _80b8
static void moveForwardToAttack(void) {}

// Address: _8103
static void waitForCharToMoveForward(void) {}

// Address: _810e
static void flashActiveMonster(void) {}

// Address: _8125
static void flashMonster(void) {}

// Address: _8141
static void wait(void) {}

static void func_c1814a(void) {}

static void func_c18179(void) {}

// Address: _8189
static void btlGfxFunc_execGfxScript(void) {}

// Address: _8234
static void gfxScriptCmd_execMisc(void) {}

// Address: _825e
static void miscEffect09(void) {}

// Address: _8281
static void miscEffect0A(void) {}

// Address: _82a4 only Return To Subroutine

// Address: _82a5
static void miscEffect_wait(void) {}

// Address: _821b
static void miscEffect04(void) {}

static void func_c182c6(void) {}

// Address: _830e
static void miscEffect_shakeScreen(void) {}

// Address: _8317
static void miscEffect05(void) {}

// Address: _8320
static void miscEffect08(void) {}

// Address: _8329
static void miscEffect06(void) {}

// Address: _8332
static void miscEffect_playSoundEffect(void) {}

// Address: _833d
static void miscEffect_playSong(void) {}

static void func_c18344(void) {}

static void func_c18352(void) {}

static void func_c18360(void) {}

static void func_c18367(void) {}

static void func_c1836e(void) {}

static void func_c18382(void) {}

static void func_c1839b(void) {}

static void func_c183b4(void) {}

static void func_c183ca(void) {}

static void func_c18400(void) {}

static void func_c18436(void) {}

static void func_c18467(void) {}

static void func_c18498(void) {}

// Address: _84a7
static void showMonster_fadeIn(void) {}

static void func_c184b5(void) {}

// Address: _84c1
static void showMonster_ironClaw(void) {}

// Address: _84d8
static void showMonster_merugene3(void) {}

// Address: _8500
static void showMonster_merugene4(void) {}

// Address: _8528
static void showMonster_discreet(void) {}

// Address: _8533
static void showMonster_motorTrap(void) {}

// Address: _854e
static void showMonster_fadeAndDrop(void) {}

// Address: _856a
static void showMonster_merugene1(void) {}

// Address: _857e
static void showMonster_merugene2(void) {}

// Address: _8592
static void showMonster_switch(void) {}

static void func_c185a6(void) {}

static void func_c185af(void) {}

// Address: _85b8
static void showMonster_transform(void) {}

// Address: _8626
static void showMonster_pages(void) {}

static void func_c18695(void) {}

// Address: _869f
static void showMonster_sandworm(void) {}

// Address: _8736
static void doMonsterEntry(void) {}

static void func_c1875c(void) {}

static void func_c1879d(void) {}

static void func_c187cf(void) {}

// Address: _87e3
static void monsterEntry02(void) {}

// Address: _8826
static void monsterEntry04(void) {}

static void func_c18836(void) {}

static void func_c1886b(void) {}

static void func_c188a8(void) {}

// Address: _890c
static void monsterEntry03(void) {}

// Address: _8926
static void monsterEntry05(void) {}

// Address: _8962
static void monsterEntry_enterFromSide(void) {}

// Address: _897c
static void monsterEntry_enterFromTop(void) {}

static void func_c189af(void) {}

static void func_c189c2(void) {}

// Address: _89d0
static void showMonster_neoExdeath(void) {}

static void func_c18b2a(void) {}

// Address: _8b46
static void gfxScriptCmd_showMonster(void) {}

// Address: _8b69
static void gfxScriptCmd_execGfxCmd(void) {}

static void func_c18b93(void) {}

// Address: _8ba9 only Return To Subroutine

static void func_c18baa(void) {}

// Address: _8be4
static void showAttackName(void) {}

// Address: _8c37
static void animCommand_displayQueuedBtlMsg(void) {}

// Address: _8c6d
static void displayBattleMessage(void) {}

// Address: _8c93
static void waitForMessage(void) {}

// Address: _8ca8
static void showNeoExdeathIntroDialog(void) {}

// Address: _8cbd
static void gfxScriptCmd_showBattleDialog(void) {}

// Address: _8cd4
static void displayBattleDialog(void) {}

static void func_c18cf1(void) {}

// Address: _8d14
static void showCharInReadyStance(void) {}

// Address: _8d22
static void showCharInNormalStance(void) {}

// Address: _8d2f
static void getAttackerId(void) {}

// Address: _8d35
static void getTargetId(void) {}

static void func_c18d3b(void) {}

static void func_c18d41(void) {}

// Address: _8d47
static void getGfxScriptParam3(void) {}

// Address: _8d4d
static void getGfxScriptParam2(void) {}

// Address: _8d53
static void getGfxScriptParam4(void) {}

// Address: _8d59
static void getGfxScriptParam1(void) {}

// Address: _8d47
static void getGfxScriptParam3(void) {}

// Address: _8d5f
static void abilityAnim(void) {}

// Address: _8d73 is only Return To Subroutine

static void func_c18d74(void) {}

// Address: _8e14
static void abilityAnimCredits_Knight(void) {}

// Address: _8e1a
static void abilityAnimCredits_JobMoveBack(void) {}

// Address: _8e20
static void abilityAnimCredits_Monk(void) {}

// Address: _8e29
static void abilityAnimCredits_Thief(void) {}

// Address: _8e32
static void abilityAnimCredits_Dragoon(void) {}

// Address: _8e3b
static void abilityAnimCredits_Ninja(void) {}

// Address: _8e44
static void abilityAnimCredits_Samurai(void) {}

// Address: _8e4a
static void abilityAnimCredits_Berserker(void) {}

// Address: _8e53
static void abilityAnimCredits_Ranger(void) {}

// Address: _8e62
static void abilityAnimCredits_MysticKnight(void) {}

// Address: _8e72
static void abilityAnimCredits_WhiteMage(void) {}

// Address: _8e82
static void abilityAnimCredits_BlackMage(void) {}

// Address: _8e92
static void abilityAnimCredits_TimeMage(void) {}

// Address: _8ea2
static void abilityAnimCredits_Summoner(void) {}

// Address: _8eb2
static void abilityAnimCredits_BlueMage(void) {}

// Address: _8ec2
static void abilityAnimCredits_RedMage(void) {}

// Address: _8ed2
static void abilityAnimCredits_Beastmaster(void) {}

// Address: _8eea
static void abilityAnimCredits_Chemist(void) {}

// Address: _8f01
static void abilityAnimCredits_Geomancer(void) {}

// Address: _8f11
static void abilityAnimCredits_Bard(void) {}

// Address: _8f21
static void abilityAnimCredits_Dancer(void) {}

// Address: _8f2a
static void abilityAnimCredits_Mime(void) {}

// Address: _8f33
static void abilityAnimCredits_Freelancer(void) {}

static void func_c18f3c(void) {}

// Address: _906f
static void showCharStatsInCredicts(void) {}

static void func_c1931a(void) {}

static void func_c1933e(void) {}

static void func_c19360(void) {}

static void func_c193af(void) {}

static void func_c1942f(void) {}

static void func_c1943d(void) {}

static void func_c19443(void) {}

static void func_c1946b(void) {}

static void func_c19481(void) {}

static void func_c194ea(void) {}

static void func_c19559(void) {}

static void func_c19581(void) {}

static void func_c195a6(void) {}

static void func_c195bf(void) {}

static void func_c1962c(void) {}

// Address: _96ec
static void setAttackerAnimFrame(void) {}

static void func_c19709(void) {}

static void func_c1971b(void) {}

static void func_c19725(void) {}

// Address: _972e
static void abilityAnim_hide(void) {}

// Address: _974a
static void abilityAnim_show(void) {}

// Address: _9763
static void runOnOffScreen(void) {}

static void func_c1979e(void) {}

// Address: _9815
static void abilityAnim_guard(void) {}

// Address: _981d
static void abilityAnim_dance(void) {}

// Address: _987d
static void abilityAnim_flirt(void) {}

static void func_c19897(void) {}

// Address: _98a9
static void abilityAnim_catch(void) {}

// Address: _98c1
static void abilityAnim_gilToss(void) {}

static void func_c198d3(void) {}

// Address: _98df
static void abilityAnim_lance(void) {}

// Address: _98f7
static void abilityAnim_tame(void) {}

// Address: _9909
static void abilityAnim_pray(void) {}

// Address: _991b
static void abilityAnim_revive(void) {}

// Address: _992d
static void abilityAnim_smoke(void) {}

// Address: _9951
static void abilityAnim_steal(void) {}

// Address: _9966
static void abilityAnim_chakra(void) {}

// Address: _9977
static void abilityAnim_image(void) {}

// Address: _9986
static void abilityAnim_def(void) {}

// Address: _998b
static void abilityAnim_focus(void) {}

static void func_c1999c(void) {}

// Address: _99ad
static void abilityAnim_intRocket(void) {}

// Address: _99e0
static void abilityAnim_jumpAttack(void) {}

static void func_c19b5b(void) {}

// Address: _9b74
static void abilityAnim_jumpUp(void) {}

// Address: _9be3
static void abilityAnim_slash(void) {}

// Address: _9c7c
static void abilityAnim_kick(void) {}

static void func_c19d37(void) {}

static void func_c19d3c(void) {}

static void func_c19d41(void) {}

static void func_c19d46(void) {}

static void func_c19d4b(void) {}

// Address: _9d80
static void getPtrCharGfxProp(void) {}

static void func_c19d8c(void) {}

// Address: _9d93
static void waitForDamageNumerals(void) {}

static void func_c19da1(void) {}

static void func_c19db3(void) {}

static void func_c19dcb(void) {}

static void func_c19e0a(void) {}

// Address: _9e4d
static void abilityAnim_row(void) {}

static void func_c19e89(void) {}

static void func_c19ed8(void) {}

static void func_c19ee7(void) {}

// Address: _9ef6
static void abilityAnim_throw(void) {}

// Address: _9f44
static void abilityAnim_fight(void) {}

static void func_c19fed(void) {}

static void func_c1a01d(void) {}