// Bank Range: C0
#include "include/field.h"

#include <SDL3/SDL.h>

#include "include/display.h"

//.import _c10003, _c10006
#include "include/btlgfx.h"

//.import ExecBattle_ext
#include "include/battle.h"

//.import ExecMenu_ext, _c2a008
#include "include/menu.h"

//.import ShowCutscene_ext, Decomp_ext
#include "include/cutscene.h"

//.import InitSound_ext, ExecSound_ext
#include "include/sound.h"

static void fieldLoop(void);
static void fieldNMI(void); // Incomplete
static void fieldIRQ(void); // Incomplete
static void execTriggerScript(Uint8 index); // Incomplete
static void checkTriggers(void); // Incomplete
static void checkVehicle(void); // Incomplete
static void func_c00853(void); // Incomplete
static void boardChoco(void);
static void landChoco(void);
static void boardBlkChoco(void); // Incomplete
static void boardHiryuu(void); // Incomplete
static void landBlkChoco(void); // Incomplete
static void landHiryuu(void); // Incomplete
static void boardSub(void);
static void landSub(void); // Incomplete
static void func_c009c6(void); // Incomplete
static void func_c009f7(void); // Incomplete
static void func_c00a11(void); // Incomplete
static void boardShip(void); // Incomplete
static void landShip(void); // Incomplete
static void boardAirship(void); // Incomplete
static void landAirship(void); // Incomplete
static void func_c00c9f(void); // Incomplete
static void func_c00d3d(void); // Incomplete
static void checkTresure(void); // Incomplete
static void giveGil(void); // Incomplete
static void calcGil(void); // Incomplete
static void checkPlayerMovementWorld(void); // Incomplete
static void func_c0103a(void); // Incomplete
static void func_c0104a(void); // Incomplete
static void func_c01055(void); // Incomplete
static void func_c010c8(void); // Incomplete
static void func_c0112d(void); // Incomplete
static void getWorldTileTransparantUnderwater(void); // Incomplete
static void checkPlayerMovementSub(void); // Incomplete
static void updateDestZLevel(void); // Incomplete
static void updateCurZLevel(void); // Incomplete
static void doTileDamage(void); // Incomplete
static void doPoisonDamage(void); // Incomplete
static void poisonMosaic(void); // Incomplete
static void updateCurPriority(void); // Incomplete
static void updateDestPriority(void); // Incomplete
static void checkDoor(void); // Incomplete
static void checkFindPits(void); // Incomplete
static void calcParallaxScroll(void); // Incomplete
static void checkPartyCanMove(void); // Incomplete
static void func_c016b7(void); // Incomplete
static void func_c016da(void); // Incomplete
static void updateLocalTilesWorld(void); // Incomplete
static void updateLocalTilesNorm(void); // Incomplete
static void getTilePropertiesCur(void); // Incomplete
static void func_c01a1d(void); // Incomplete
static void func_c01ae4(void); // Incomplete
static void updateTopChar(void); // Incomplete
static void updatePlayerGfx(void); // Incomplete
static void copyPlayerGfx(void); // Incomplete
static void copyAltGfx(void); // Incomplete
static void func_c01e64(void); // Incomplete
static void func_c01ec5(void); // Incomplete
static void func_c01f57(void); // Incomplete
static void func_c01fb4(void); // Incomplete
static void func_c01fff(void); // Incomplete
static void func_c0201f(void); // Incomplete
static void func_c0203f(void); // Incomplete
static void func_c02137(void); // Incomplete
static void func_c022fb(void); // Incomplete
static void drawPlayerSprite(void); // Incomplete
static void loadOverlayGfx(void); // Incomplete
static void loadOverlayProp(void); // Incomplete
static void drawOverlaySprites(void); // Incomplete
static void updateOverlay(void); // Incomplete
static void execNPCScript(void); // Incomplete
static void checkNPCEvents(void); // Incomplete
static void func_c0324b(void); // Incomplete
static void func_c03289(void); // Incomplete
static void updateObjects(void); // Incomplete
static void canNPCMoveToTile(void); // Incomplete
static void moveTowardsParty(void); // Incomplete
static void moveAwayFromParty(void); // Incomplete
static void drawHiryuu(void); // Incomplete
static void drawObjectSprites(void); // Incomplete
static void updateObjectPositions(void); // Incomplete
static void getPointerToObjLayout(void); // Incomplete
static void clearObjLayout(void); // Incomplete
static void addObjectToObjLayout(void); // Incomplete
static void removeObjectToObjLayout(void); // Incomplete
static void getObjectInObjLayout(void); // Incomplete
static void getTileZ(void); // Incomplete
static void loadNPCGfx(void); // Incomplete
static void getPointerToNPCProperties(void); // Incomplete
static void loadNPCs(void); // Incomplete
static void greyscalePalette(void); // Incomplete
static void func_c0406b(void); // Incomplete
static void copyDataToVram(void); // Incomplete
static void func_c04107(void); // Incomplete
static void func_c041f1(void); // Incomplete
static void func_c0420a(void); // Incomplete
static void showCutsceneFromField(Uint8 id); // Incomplete
static void initMapBank(void); // Incomplete
static void initVehicles(void); // Incomplete
static void initCharNames(void); // Incomplete
static void openMenu(void); // Incomplete
static void func_c0456b(void); // Incomplete
static void func_c04583(void); // Incomplete
static void playSong(void); // Incomplete
static void playSound(void); // Incomplete
static void playSfx(void); // Incomplete
static void updateScreenMosaic(void); // Incomplete
static void func_c046c4(void); // Incomplete
static void func_c04741(void); // Incomplete
static void func_c04798(void); // Incomplete
static void func_c047aa(void); // Incomplete
static void func_c047f7(void); // Incomplete
static void func_c04834(void); // Incomplete
static void initNPCFlags(void); // Incomplete
static void initEventFlags(void); // Incomplete
static void initNewCharData(void); // Incomplete
static void resetRam_0000_to_1D00(void); // Incomplete
static void resetRam_0B00_to_1D00(void); // Incomplete
static void func_c04931(void); // Incomplete
static void initColorAddition(void); // Incomplete
static void initColorSubtraction(void); // Incomplete
static void updateFixedColor(void); // Incomplete
static void setFixedColorParams(void); // Incomplete
static void initFadeIn(void); // Incomplete
static void initFadeOut(void); // Incomplete
static void func_c04a7a(void); // Incomplete
static void func_c04aad(void); // Incomplete
static void waitForKeypress(void); // Incomplete
static void tfrVehicleGfx(void); // Incomplete
static void tfrWorldGfx(void); // Incomplete
static void updateScrollingRegisters(void); // Incomplete
static void updateCtrl(void); // Incomplete
static void resetSprites(void); // Incomplete
static void hideSpritesInCutscenes(void); // Incomplete
static void tfrVram(void); // Incomplete
static void disableInterrupts(void); // Incomplete
static void enableInterrupts(void); // Incomplete
static void clearVramForCutscenes(void); // Incomplete
static void fillVram(void); // Incomplete
static void tfrSprites(void); // Incomplete
static void tfrPallets(void); // Incomplete
static void func_c04d8e(void); // Incomplete
static void waitVblank(void); // Incomplete
static void initInterrupts(void); // Incomplete
static void initHardware(void);
static void generateRandom(void); // Incomplete
static void crystalShatterAnim(void); // Incomplete
static void loadMap(void); // Incomplete
static void loadMapNoFade(void); // Incomplete
static void reloadMap(void);
static void loadParentMap(void);
static void func_c054a7(void); // Incomplete
static void func_c054f6(void); // Incomplete
static void loadWorldMap(void); // Incomplete
static void reloadWorldMap(void); // Incomplete
static void loadWorldMapPalette(void); // Incomplete
static void loadSubMap(void); // Incomplete
static void reloadSubMap(void); // Incomplete
static void func_c057f9(void); // Incomplete
static void initAutoScroll(void); // Incomplete
static void loadMapLayout(void); // Incomplete
static void loadMapPalette(void); // Incomplete
static void loadMapGfx(void); // Incomplete
static void func_c05adb(void); // Incomplete
static void loadMapProps(void); // Incomplete
static void initMapColorMathSettings(void); // Incomplete
static void func_c05bf4(void); // Incomplete
static void func_c05bf8(void); // Incomplete
static void func_c05c01(void); // Incomplete
static void loadTreasureChests(void); // Incomplete
static void updateWindowMaskCircle(void); // Incomplete
static void func_c05d54(void); // Incomplete
static void func_c05d87(void); // Incomplete
static void copyTileLayoutToVram(void); // Incomplete
static void func_c05e61(void); // Incomplete
static void func_c05ee5(void); // Incomplete
static void func_c05f3e(void); // Incomplete
static void func_c05f8d(void); // Incomplete
static void pitfallFadeOutAnim(void); // Incomplete
static void fadeOutMap(void); // Incomplete
static void pitfallFadeInAnim(void); // Incomplete
static void fadeInMap(void); // Incomplete
static void func_c0612b(void); // Incomplete
static void func_c06134(void); // Incomplete
static void func_c061d7(void); // Incomplete
static void func_c062bc(void); // Incomplete
static void func_c0630a(void); // Incomplete
static void func_c0637e(void); // Incomplete
static void func_c063d4(void); // Incomplete
static void func_c06465(void); // Incomplete
static void func_c064bb(void); // Incomplete
static void func_c06513(void); // Incomplete
static void func_c065a3(void); // Incomplete
static void showMiniMap(void); // Incomplete
static void func_c06731(void); // Incomplete
static void func_c06755(void); // Incomplete
static void func_c0679c(void); // Incomplete
static void func_c067ec(void); // Incomplete
static void func_c06831(void); // Incomplete
static void loadWorldTilemap(void); // Incomplete
static void loadSubTilemap(void); // Incomplete
static void fillTilemap(void); // Incomplete
static void loadWorldTileset(void); // Incomplete
static void loadSubTileset(void); // Incomplete
static void func_c06b99(void); // Incomplete
static void func_c06bac(void); // Incomplete
static void initBgScrollPos(void); // Incomplete
static void func_c06c4a(void); // Incomplete
static void func_c06c6a(void); // Incomplete
static void func_c06c9d(void); // Incomplete
static void func_c06cd4(void); // Incomplete
static void func_c06d0c(void); // Incomplete
static void func_c06de9(void); // Incomplete
static void horizontalScrolling(void); // Incomplete
static void verticalScrolling(void); // Incomplete
static void modBgTilemap(void); // Incomplete
static void func_c0703e(void); // Incomplete
static void func_c0707d(void); // Incomplete
static void func_c07221(void); // Incomplete
static void func_c0722f(void); // Incomplete
static void func_c07241(void); // Incomplete
static void showDialog(void); // Incomplete
static void getDialogPtr(void); // Incomplete
static void loadDialogText(void); // Incomplete
static void func_c08451(void); // Incomplete
static void func_c08459(void); // Incomplete
static void func_c08466(void); // Incomplete
static void func_c08477(void); // Incomplete
static void func_c08493(void); // Incomplete
static void func_c084af(void); // Incomplete
static void func_c084e9(void); // Incomplete
static void func_c08508(void); // Incomplete
static void func_c0850d(void); // Incomplete
static void func_c08512(void); // Incomplete
static void getSpellName(void); // Incomplete
static void getItemName(void); // Incomplete
static void getGilAmount(void); // Incomplete
static void func_c08b53(void); // Incomplete
static void func_c08ba4(void); // Incomplete
static void func_c08bd3(void); // Incomplete
static void func_c08be4(void); // Incomplete
static void func_c08c2e(void); // Incomplete
static void func_c08c7b(void); // Incomplete
static void func_c08c92(void); // Incomplete
static void func_c08d0e(void); // Incomplete
static void func_c08d3b(void); // Incomplete
static void func_c08e08(void); // Incomplete
static void func_c08e23(void); // Incomplete
static void func_c08ed3(void); // Incomplete
static void loadFontGfx(void); // Incomplete
static void func_c08f54(void); // Incomplete
static void drawYesNoIndicator(void); // Incomplete
static void showYesNoWindow(void); // Incomplete
static void func_c090ad(void); // Incomplete
static void showGPWindow(void); // Incomplete
static void func_c091ed(void); // Incomplete
static void showMapTitle(void); // Incomplete
static void initMapTitle(void); // Incomplete
static void drawMapTitleWindow(void); // Incomplete
static void hideMapTitleWindow(void); // Incomplete
static void func_c09440(void); // Incomplete
static void func_c094a8(void); // Incomplete
static void func_c09618(void); // Incomplete
static void func_c0964c(void); // Incomplete
static void func_c09695(void); // Incomplete
static void func_c09704(void); // Incomplete
static void func_c09772(void); // Incomplete
static void func_c0975f(void); // Incomplete
static void updatePaletteAnim(void); // Incomplete
static void func_c097e2(void); // Incomplete
static void func_c0980d(void); // Incomplete
static void func_c09838(void); // Incomplete
static void func_c09865(void); // Incomplete
static void func_c098e2(void); // Incomplete
static void initPaletteAnim(void); // Incomplete
static void func_c0996d(void); // Incomplete
static void updateMapAnim(void); // Incomplete
static void initMapAnim(void); // Incomplete
static void loadAnimTileGfx(void); // Incomplete
static void func_c09c3d(void); // Incomplete
static void func_c09cac(void); // Incomplete
static void updateTimer(void); // Incomplete
static void speedUpMusicWithTimer(void); // Incomplete

static void execEvent(void); // Incomplete
static void nextEventCmd(void); // Incomplete
static void terminateEvent(void); // Incomplete
static void func_c0a365(void); // Incomplete
static void func_c0a380(void); // Incomplete
static void func_c0a3c9(void); // Incomplete
static void func_c0a40a(void); // Incomplete
static void func_c0a449(void); // Incomplete
static void func_c0a45f(void); // Incomplete
static void eventCmd_bf(void); // Incomplete
static void eventCmd_bf1a(void); // Incomplete
static void eventCmd_bf18(void); // Incomplete
static void func_c0a7be(void); // Incomplete
static void eventCmd_bf19(void); // Incomplete
static void eventCmd_bf15(void); // Incomplete
static void func_c0a933(void); // Incomplete
static void eventCmd_bf14(void); // Incomplete
static void func_c0aa0e(void); // Incomplete
static void eventCmd_bf13(void); // Incomplete
static void eventCmd_bf12(void); // Incomplete
static void func_c0ab8e(void); // Incomplete
static void func_c0abb5(void); // Incomplete
static void eventCmd_bf0f(void); // Incomplete
static void eventCmd_bf10(void); // Incomplete
static void eventCmd_bf07(void); // Incomplete
static void eventCmd_bf08(void); // Incomplete
static void eventCmd_bf09(void); // Incomplete
static void eventCmd_bf0a(void); // Incomplete
static void func_c0ac80(void); // Incomplete
static void func_c0ac8b(void); // Incomplete
static void func_c0acb1(void); // Incomplete
static void func_c0acdd(void); // Incomplete
static void func_c0ad01(void); // Incomplete
static void func_c0ad28(void); // Incomplete
static void func_c0ad54(void); // Incomplete
static void func_c0ad86(void); // Incomplete
static void func_c0ada0(void); // Incomplete
static void func_c0adb7(void); // Incomplete
static void func_c0add6(void); // Incomplete
static void func_c0ae0b(void); // Incomplete
static void func_c0ae32(void); // Incomplete
static void eventCmd_bf00(void); // Incomplete
static void eventCmd_bf01(void); // Incomplete
static void eventCmd_bf16(void); // Incomplete
static void eventCmd_bf02(void); // Incomplete
static void eventCmd_bf11(void); // Incomplete
static void eventCmd_bf05(void); // Incomplete
static void func_c0b240(void); // Incomplete
static void eventCmd_bf04(void); // Incomplete
static void func_c0b2a5(void); // Incomplete
static void func_c0b35c(void); // Incomplete
static void func_c0b371(void); // Incomplete
static void func_c0b3cd(void); // Incomplete
static void eventCmd_bf06(void); // Incomplete
static void func_c0b594(void); // Incomplete
static void eventCmd_bf0b(void); // Incomplete
static void func_c0b5fd(void); // Incomplete
static void eventCmd_bf17(void); // Incomplete
static void eventCmd_bf03(void); // Incomplete
static void func_c0b750(void); // Incomplete
static void func_c0b75e(void); // Incomplete
static void func_c0b791(void); // Incomplete
static void eventCmd_bf0c(void); // Incomplete
static void eventCmd_bf0e(void); // Incomplete
static void eventCmd_bf0d(void); // Incomplete
static void func_c0b854(void); // Incomplete
static void eventCmd_ea(void); // Incomplete
static void eventCmd_eb(void); // Incomplete
static void eventCmd_e9(void); // Incomplete
static void eventCmd_e7(void); // Incomplete
static void eventCmd_e6(void); // Incomplete
static void eventCmd_e4(void); // Incomplete
static void eventCmd_e5(void); // Incomplete
static void eventCmd_dd(void); // Incomplete
static void eventCmd_da(void); // Incomplete
static void func_c0b9f5(void); // Incomplete
static void eventCmd_79(void); // Incomplete
static void eventCmd_db(void); // Incomplete
static void eventCmd_d9(void); // Incomplete
static void changeColorPalette(void); // Incomplete
static void eventCmd_b6(void); // Incomplete
static void eventCmd_ae(void); // Incomplete
static void eventCmd_a6(void); // Incomplete
static void eventCmd_a7(void); // Incomplete
static void eventCmd_7b(void); // Incomplete
static void eventCmd_7f(void); // Incomplete
static void eventCmd_ad(void); // Incomplete
static void calcInnPrice(void); // Incomplete
static void eventCmd_ac(void); // Incomplete
static void eventCmd_c0(void); // Incomplete
static void func_c0bc9f(void); // Incomplete
static void eventCmd_d0(void); // Incomplete
static void eventCmd_70(void); // Incomplete
static void eventCmd_dc(void); // Incomplete
static void eventCmd_7a(void); // Incomplete
static void eventCmd_a1(void); // Incomplete
static void eventCmd_e8(void); // Incomplete
static void eventCmd_bd(void); // Incomplete
static void eventCmd_e2(void); // Incomplete
static void eventBattle(void); // Incomplete
static void eventCmd_b7(void); // Incomplete
static void eventCmd_c6(void); // Incomplete
static void eventCmd_af(void); // Incomplete
static void eventCmd_b0(void); // Incomplete
static void calcGilForEvent(void); // Incomplete
static void eventCmd_aa(void); // Incomplete
static void eventCmd_ab(void); // Incomplete
static void findItemSlot(void); // Incomplete
static void eventCmd_ba(void); // Incomplete
static void eventCmd_bb(void); // Incomplete
static void eventCmd_bc(void); // Incomplete
static void eventCmd_a8(void); // Incomplete
static void eventCmd_a9(void); // Incomplete
static void getPtrToCharData(void); // Incomplete
static void func_c0c19d(void); // Incomplete
static void eventCmd_c2(void); // Incomplete
static void eventCmd_d2(void); // Incomplete
static void eventCmd_c9(void); // Incomplete
static void eventCmd_b4(void); // Incomplete
static void eventCmd_d4(void); // Incomplete
static void eventCmd_b5(void); // Incomplete
static void eventCmd_d5(void); // Incomplete
static void eventCmd_76(void); // Incomplete
static void eventCmd_78(void); // Incomplete
static void eventCmd_77(void); // Incomplete
static void eventCmd_f1(void); // Incomplete
static void eventCmd_f0(void); // Incomplete
static void eventCmd_d6(void); // Incomplete
static void eventCmd_e0(void); // Incomplete
static void eventCmd_e1(void); // Incomplete
static void eventCmd_e3(void); // Incomplete
static void func_c0c43f(void); // Incomplete
static void eventCmd_f4(void); // Incomplete
static void eventCmd_f3(void); // Incomplete
static void eventCmd_7c(void); // Incomplete
static void eventCmd_d8(void); // Incomplete
static void eventCmd_d3(void); // Incomplete
static void removeCurObjFromObjLayout(void); // Incomplete
static void eventCmd_d1(void); // Incomplete
static void eventCmd_d7(void); // Incomplete
static void eventCmd_7d(void); // Incomplete
static void eventCmd_c5(void); // Incomplete
static void eventCmd_b8(void); // Incomplete
static void eventCmd_b9(void); // Incomplete
static void eventCmd_7e(void); // Incomplete
static void eventCmd_c3(void); // Incomplete
static void eventCmd_c4(void); // Incomplete
static void eventCmd_be(void); // Incomplete
static void eventCmd_c1(void); // Incomplete
static void eventCmd_b1(void); // Incomplete
static void func_c0c6de(void); // Incomplete
static void eventCmd_b2(void); // Incomplete
static void eventCmd_b3(void); // Incomplete
static void eventCmd_a0(void); // Incomplete
static void eventCmd_a2(void); // Incomplete
static void eventCmd_a4(void); // Incomplete
static void eventCmd_a3(void); // Incomplete
static void eventCmd_a5(void); // Incomplete
static void clearEventFlag_256_511(void); // Incomplete
static void eventCmd_c8(void); // Incomplete
static void initObjectMovement(void); // Incomplete
static void func_c0c7f9(void); // Incomplete
static void func_c0c932(void); // Incomplete
static void initCameraMovement(void); // Incomplete
static void giveSpell(void); // Incomplete
static void getNPCFlag(void); // Incomplete
static void eventCmd_ca(void); // Incomplete
static void eventCmd_cb(void); // Incomplete

static void setBattleFlag(void); // Incomplete
static void clearBattleFlag(void); // Incomplete
static void getTrasureFlag(void); // Incomplete
static void setTreasureFlag(void); // Incomplete
static void getEventFlag00xx(void); // Incomplete
static Uint8 getEventFlag01xx(Uint8 val); // Incomplete
static void getFlagIndex(void); // Incomplete
static void checkRandomBattlesSub(void); // Incomplete
static void checkRandomBattlesWorld(void); // Incomplete
static void updateRandomForBattles(void); // Incomplete
static void func_c0cc6d(void); // Incomplete
static void battleBlurSub(void); // Incomplete
static void battleBlurWorld(void); // Incomplete
static void battleBlur(void); // Incomplete
static void randomBattle(void); // Incomplete
static void reset(void); // Incomplete

// These adresses are called before
// having any value stored first
static Uint8 addr_7e0139 = 0;
static Uint8 addr_7e0af9 = 0;

static Uint8 addr_7e0002;
static Uint8 addr_7e0003;
static Uint8 addr_7e0006;
static Uint8 addr_7e0008;
static Uint8 addr_7e003d;
static Uint8 addr_7e0040;
static Uint8 addr_7e0053;
static Uint8 addr_7e0055;
static Uint8 addr_7e0058;
static Uint8 addr_7e005d;
static Uint8 addr_7e0061;
static Uint8 addr_7e0063;
static Uint8 addr_7e006e;
static Uint8 addr_7e0071;
static Uint8 addr_7e0075;
static Uint8 addr_7e0076;
static Uint8 addr_7e0088;
static Uint8 addr_7e0089;
static Uint8 addr_7e00a6;
static Uint8 addr_7e00b4;
static Uint8 addr_7e00b5;
static Uint8 addr_7e00b9;
static Uint8 addr_7e00bc;
static Uint8 addr_7e00bd;
static Uint8 addr_7e00ce;
static Uint8 addr_7e0134;
static Uint8 addr_7e0135;
static Uint8 addr_7e0139;
static Uint8 addr_7e0ad6;
static Uint8 addr_7e0ad8;
static Uint8 addr_7e0ad9;
static Uint8 addr_7e0adc;
static Uint8 addr_7e0af5;
static Uint8 addr_7e0af7;
static Uint8 addr_7e0af8;
static Uint8 addr_7e0b60;
static Uint8 addr_7e0b61;
static Uint8 addr_7e0b63;
static Uint8 addr_7e0b5f;
static Uint8 addr_7e1088;
static Uint8 addr_7e1089;
static Uint8 addr_7e10fb;
static Uint8 addr_7e110f;
static Uint8 addr_7e16aa;

// Address: _4200
static Uint8 h_nmitimen;
// Address: _4201
static Uint8 h_wrio;
// Address: _4207
static Uint8 h_htimel;
// Address: _4208
static Uint8 h_htimeh;
// Address: _4209
static Uint8 h_vtimel;
// Address: _420a
static Uint8 h_vtimeh;
// Address: _420b
static Uint8 h_mdmaen;
// Address: _420c
static Uint8 h_hdmaen;
// Address: _420d
static Uint8 h_memsel;

void start(void) {
    // SEt Interrpt flag
    // CLear Carry flasg
    // eXchange Carry and Emulation flags
    // Lengthen indexes to 16-bits
    // Shorten Accumulator (A) to 8-bits

    // STore Zero to hMEMSEL
    h_memsel = 0;
    // STore Zero to hMDMAEN
    h_mdmaen = 0;
    // STore Zero to hHDMAEN
    h_hdmaen = 0;
    // LoaD #$8f (143) to A
    // Store A to hINIDISP
    inidisp = 143;
    // LoaD #0 to A
    // Store A to hNMITIMEN
    h_nmitimen = 0;

    // LoaD #0 to A
    // eXchange data Bank and A 8-bit accumulators
    // LoaD #$1fff to X
    // Transfer X to Stack pointer
    // Load #0 to A
    // PusH A
    // PulL data Bank register
    // LoaD #$0b00 to X
    // PusH X
    // PulL Direct page register

    // LoaD #0 to X
    // STore X to $06
    addr_7e0006 = 0;

    // Jump to Subroutine Long InitSound_ext
    initSound();

    // LoaD #$f1 to Accumulator
    const Uint8 CUTSCENE_TITLE = 241;
    // Jump to SubRoutine ShowCutscene
    showCutsceneFromField(CUTSCENE_TITLE);

    // Jump to SubRoutine InitHardware
    initHardware();

    // Jump to SubRoutine _c0490a
    resetRam_0000_to_1D00();

    // LoaD #3 to Accumulator
    // STore A to $0134
    addr_7e0134 = 3;

    // Jump to Subroutine Long ExecMenu_ext
    execMenu();

    // Jump to SubRoutine _c044e3
    initMapBank();

    // Jump to SubRoutine InitHardware
    initHardware();

    // Jump to SubRoutine InitInterrupts
    initInterrupts();

    // LoaD $0139 to A
    // Branch to [NewGame] if EQual
    //  - by equal, it's if the zero flag is set
    //  - for this case, check whether Address $0139 is valued zero.
    if (addr_7e0139 == 0) {
        // [NewGame]
        // Jump to SubRoutine _c048fa
        initNewCharData();
        // Jump to SubRoutine _c048ed
        initEventFlags();
        // Jump to SubRoutine _c048dd
        initNPCFlags();
        // Jump to SubRoutine _c04528
        initCharNames();
        // Jump to SubRoutine _c0450a
        initVehicles();
        
        // Load #1 to A
        // Store A to $bd
        addr_7e00bd = 1;
        // Store A to $bc
        addr_7e00bc = 1;

        // Load #$0010 to X
        // Store X to $ce
        addr_7e00ce = 16;

        // Load #1 to A
        // Store A to $57
        addr_7e0057 = 1;

        // Load #$81 to A
        // Store A to hNMITIMEN
        h_nmitimen = 129;

        // CLear Interrupt flag
        // Jump to SubRoutine ExecEvent
        execEvent();

        // Store Zero to $57
        addr_7e0057 = 0;
        // Store Zero to $58
        addr_7e0058 = 0;
        // Store Zero to $59
        addr_7e0059 = 0;

        // JuMP to FieldLoop
        //  - To be called at App Iterate
    } else {
        // (restore saved game)

        // Jump to SubRoutine _c0491d
        resetRam_0B00_to_1D00();

        // LoaD $0af9 to A
        // Store A to $0b60
        addr_7e0b60 = addr_7e0af9;

        // Shift Right A
        // Store A to $0b5f
        addr_7e0b5f = addr_7e0b60 >> 1;

        // Load #1 to A
        // Store A to $bd (show party sprite)
        addr_7e00bd = 1;
        // Store A to $bc (senable walking animation)
        addr_7e00bc = 1;

        // INCrement A
        // Store A to $b9
        addr_7e00b9 = 2;

        // Load $0ad8 to A (x position)
        // Store A to $1088
        addr_7e1088 = addr_7e0ad8;

        // Load $0ad9 to A (y position)
        // Store A to $1089
        addr_7e1089 = addr_7e0ad9;

        // Jump to subroutine LoadMapNoFade
        loadMapNoFade();
        
        // Jump to FieldLoop
        //  - To be called at App Iterate
    }
}

// Field Main Loop
static void fieldLoop(void) {
    // Jump to SubRoutine WaitVBlank
    waitVblank();

    // Check if the menu button is pressed
        // LoaD $02 to A
        // AND A with #JOY_X
        // Branch to next label if EQuals
        // LoaD $53 to A
        // Branch to [CheckMenu] if EQuals
        // LoaD $5d to A
        // Branch to [CheckMenu] if EQuals
    const Uint8 JOY_X = 64;
    if (addr_7e0002 & JOY_X == 0 || addr_7e0053 | addr_7e005d) {
        // [CheckMenu]
        // LoaD $0b61 to A
        // AND A with #$1f
        // Branch to [NoMenu] if Not Equals
            // if partially scrolled
        // LoaD $0b63 to A
            // bg1 y position
        // AND A with #$1f
        // Branch to [NoMenu] if Not Equals
            // if partially scrolled
        const Uint8 PARTIALLY_SCROLLED = 0x1F;
        if (addr_7e0b61 & PARTIALLY_SCROLLED && addr_7e0b63 & PARTIALLY_SCROLLED) {
            // LoaD #$00 to A
            // STore A to $0135
            addr_7e0135 = 0;

            // LoaD $0adc (if in a vehicle) to A
            // Branch to [CheckWarp] if Not Equals
            if (addr_7e0adc) {
                // LoaD $0ad6 (map index) to X
                // ComPare X with #$0005
                // Branch to [EnableSave] if Carry Clear
                    // if not on a world map
                if (addr_7e0ad6 >= 5) {
                    // LoaD #$fd to A
                    // Jump to SubRoutine _c0ca3c
                        // get event flag $01xx
                    Uint8 flagIndex = getEventFlag01xx(0xFD);
                    // CoMPare A with #$00
                    // Branch to [CheckWarp] if EQuals
                    if (flagIndex == 0) goto checkWarp;
                }
                
                // [EnableSave]
                // LoaD #$80 to A
                // STore A to $0135
                    // Enable tent/cabin/save
                addr_7e0135 = 0x80;

            }
            
            // [CheckWarp]
            checkWarp:
                // STore Zero to $08
                addr_7e0008 = 0;

                // LoaD $53 to A
                // Branch to next label if EQuals
                if (addr_7e0053) {
                    // LoaD $110f to A
                        // Enable warp/teleporter?
                    // AND A with #$03
                    // STore A to $08
                    addr_7e0008 = addr_7e110f & 3;
                }
            
            // Open the menu
                // [LBL] LoaD $0135 to A
                // OR A with $08
                // STore A to $0135
            addr_7e0135 |= 8;

                // LoaD #$00 to A (menu command index)
                // STore A to $0134
            addr_7e0134 = 0;

                // Jump to SubRoutine OpenMenu
            openMenu();

                // LoaD #$02 to A
                // STore A to $55
            addr_7e0055 = 2;

                // LoaD $0ad8 to A
                // STore A to $1088
            addr_7e1088 = addr_7e0ad8;

                // LoaD $0ad9 to A
                // STore A to $1089
            addr_7e1089 = addr_7e0ad9;

                // Jump to SubRoutine ReloadMap
            reloadMap();
            
            // Check if an item was used in the menu
                // LoaD $0139 to A (the item used)
                // CoMPare A with #$f0
                // Branch to next label if Not Equals
                    // if not tent
            Uint8 event_i;
            if (addr_7e0139 == 0xF0) {
                    // LoaD #$0022 to X
                event_i = 0x22;
                    // BRAnch to [DoMenuEvent]
            }
                // [LBL] CoMPare A with #$f1
                // Branch to next label if Not Equals
                    // if not cabin
            if (addr_7e0139 == 0xF1) {
                    // LoaD #$0024 to X
                event_i = 0x24;
                    // BRAnch to [DoMenuEvent]
            }
                // CoMPare A with #$3e (judgement staff???)
                // Branch to next label if Not Equals
            if (addr_7e0139 == 0x3E) {
                    // LoaD #$0032 to X
                event_i = 0x32;
            }
            
            // [DoMenuEvent]
                // Jump to SubRoutine ExecTriggerScript
            execTriggerScript(event_i);

                // [LBL] STore Zero to $16aa
            addr_7e16aa = 0;

                // Jump to SubRoutine PoisonMosaic
            poisonMosaic();

                // JuMP to FieldLoop
            return;
        }
        // [LBL] JuMP to [NoMenu]
    } else {
        // [NoMenu] (check triggers and timer)
        // Jump to SubRoutine CheckTriggers
        checkTriggers();

        // Jump to SubRoutine _c0a18b (update timer)
        updateTimer();

        // LoaD $58 to A
        // Branch to next label if EQuals
        if (addr_7e0058) {
            // STore Zero to $58
            addr_7e0058 = 0;

            // JuMP to FieldLoop
            return;
        }

        // [LBL] LoaD $6e to A
        // Branch to next label if EQuals
        if (addr_7e006e) {
            // Jump to SubRoutine LoadMap
            loadMap();

            // JuMP to FieldLoop
            return;
        }

        // [LBL] LoaD $0ad6 (map index) to X
        // ComPare X to #$0005
        // Jump to [SubMapLoop] if Carry Set
        if (addr_7e0ad6 >= 5) {
            // [SubMapLoop] check activated NPCs and treasures
            // Jump to SubRoutine _c00d3d
            func_c00d3d();

            // LoaD $58 to A
            // Branch to next if EQuals
            if (addr_7e0058) {
                // STore Zero to $58
                addr_7e0058 = 0;

                // JuMP to FieldLoop
                return;
            }

            // [LBL] check map exit
            // LoaD $10fb (tile properties byte 2) to A
            // CoMPare A with #$00
            // Branch to next if Not Equals (if not exit)
            if (addr_7e10fb == 0) {
                // Jump to SubRoutine LoadParentMap
                loadParentMap();

                // LoaD #$001c to X
                // Jump to SubRoutine ExecTriggerScript
                execTriggerScript(0x1C);

                // JuMP to FieldLoop
                return;
            }

            // [LBL] check random battles
            // Jump to SubRoutine _c0ca69
            checkRandomBattlesSub();

            // LoaD $55 to A
            // Branch to next if EQuals
            if (addr_7e0055) {
                // LoaD #$ff to A
                // Jump to SubRoutine _c0ca3c
                Uint8 eventFlag = getEventFlag01xx(SDL_MAX_UINT8);

                // CoMPare A with #$00
                // Branch to next if Not Equals
                if (eventFlag == 0) {
                    // Jump to SubRoutine RandomBattle
                    randomBattle();

                    // Jump to SubRoutine ReloadMap
                    reloadMap();

                    // JuMP to FieldLoop
                    return;
                }
            }

            // [LBL] STore Zero to $55
            addr_7e0055 = 0;

            // Jump to SubRoutine _c032ab
            updateObjects();

            // Jump to SubRoutine CheckPlayerMoveSub
            checkPlayerMovementSub();

            // LoaD $6e to A
            // Branch to next if EQuals
            if (addr_7e006e) {
                // Jump to SubRoutine LoadMap
                loadMap();

                // JuMP to FieldLoop
                return;
            }

            // [LBL] loop if an event is running
            // LoaD $58 to A
            // Branch to next if EQuals
            if (addr_7e0058) {
                // STore Zero to $58
                addr_7e0058 = 0;

                // JuMP to FieldLoop
                return;
            }

            // [LBL] do updates if no events are running
            // Jump to SubRoutine _c01ae4
            func_c01ae4();

            // Jump to SubRoutine _c03bac
            updateObjectPositions();

            // Jump to SubRoutine ResetSprites
            resetSprites();

            // Jump to SubRoutine _c04834
            func_c04834();

            // Jump to SubRoutine DrawPlayerSprite
            drawPlayerSprite();

            // Jump to SubRoutine DrawObjSprites
            drawObjectSprites();

            // Jump to SubRoutine DrawOverlaySprites
            drawOverlaySprites();

            // Jump to SubRoutine _c0420a
            func_c0420a();

            // JuMP to FieldLoop
            // Return to SubRoutine (unused step)
            return;
        }
        
        // World Map
        // check if boarding or landing a vehicle
            // Jump to SubRoutine CheckVehicle
        checkVehicle();

            // LoaD $58 to A
            // Branch to next label if EQuals
        if (addr_7e0058) {
            // STore Zero to $58
            addr_7e0058 = 0;

            // JuMP to FieldLoop
            return;
        }

        // check events
            // [LBL] LoaD $61 to A
            // AND A with #$1f (31)
        const Uint8 CMP = 31;

            // Branch to [NoWorldEvent] if Not Equals
            // LoaD $63 to A
            // AND A with #$1f (31)
            // Branch to [NoWorldEvent] if Not Equals
        Uint8 event_i = 0;
        if (addr_7e0061 != CMP && addr_7e0063 != 31) {
            // LoaD $0ad6 (map index) to A
            // CoMPare A with #$01
            // Branch to next label if Not Equals
            if (addr_7e0ad6 != 1 &&
            
            // LoaD $0ad9 to A
            // CoMPare A with #$a1
            // Branch to next label if Not Equals
                    addr_7e0ad9 != 0xA1 &&
            
            // LoaD $0ad8 to A
            // CoMPare A with #$9f
            // Branch to next label if Carry Clear
                    addr_7e0ad8 >= 0x9F &&

            // CoMPare A with #$a2
            // Branch to next label if Carry Set
                    addr_7e0ad8 < 0xA2) {
                // LoaD #$0012 to X
                event_i = 0x12;
                
                // BRAnch to [DoWorldEvent]

            // [LBL] LoaD $0ad6 (map index) to A
            // Branch to next label if Not Equals
        } else if (addr_7e0ad6 == 0 &&

            // LoaD $0adc to A
            // CoMPare A with #$06
            // Branch to next label if Not Equals
                addr_7e0adc == 6 &&

            // LoaD $0ad8 to A
            // CoMPare A with #$3d
            // Branch to next label if Carry Clear
                addr_7e0ad8 >= 0x3D &&

            // CoMPare A with #$43
            // Branch to next label if Carry Set
                addr_7e0ad8 < 0x43 &&
            
            // LoaD $0ad9 to A
            // CoMPare A with #$9e
            // Branch to next if Carry Clear
                addr_7e0ad9 >= 0x9e &&

            // CoMPare A with #$a5
            // Branch to next if Carry Set
                addr_7e0ad9 < 0xA5) {
                // LoaD #$0020 to X
            event_i = 0x20;

                // BRAnch to [DoWorldEvent]

            // [LBL] LoaD $0ad6 (map index) to A
            // CoMPare A with #$02
            // Branch to next if Not Equals
        } else if (addr_7e0ad6 == 2 &&

            // LoaD $0adc to A
            // CoMPare A with #$05
            // Branch to next if Carry Clear
                addr_7e0adc >= 5 &&

            // LoaD $0ad8 to A
            // CoMPare A with #$b6
            // Branch to next if Carry Clear
                addr_7e0ad8 >= 0xb6 &&

            // CoMPare A with #$ba
            // Branch to next if Carry Set
                addr_7e0ad8 < 0xBA &&

            // LoaD $0ad9 to A
            // CoMPare A with #$87
            // Branch to next if Carry Clear
                addr_7e0ad9 >= 0x87 &&

            // CoMPare A with #$8b
            // Branch to next if Carry Set
                addr_7e0ad9 < 0x8B) {
            
                // LoaD #$0018 to X
                event_i = 0x18;
            }
        }
        
        // [DoWorldEvent]
            // Jump to SubRoutine ExecTriggerScript
        execTriggerScript(event_i);
            
            // LoaD $58 to A
            // Branch to next if EQuals
        if (addr_7e0058) {

            // STore Zero to $58
            addr_7e0058 = 0;

            // JuMP to FieldLoop
            return;
        }
        
        // check random battle
            // [NoWorldEvent]
            // Jump to SubRoutine _c0cb11
        checkRandomBattlesWorld();

            // LoaD $55 to A
            // Branch to next if EQuals
            // LoaD #$ff to A
            // Jump to SubRoutine _c0ca3c (get event flag $01xx)
            // CoMPare A with #$00
            // Branch to next if Not Equals
        if (addr_7e0055 && getEventFlag01xx(SDL_MAX_UINT8) == 0) {
            
            // Jump to SubRoutine RandomBattle
            randomBattle();

            // LoaD $0ad8 to A
            // STore A to $1088
            addr_7e1088 = addr_7e0ad8;

            // LoaD $0ad9 to A
            // STore A to $1089
            addr_7e1089 = addr_7e0ad9;

            // Jump to SubRoutine ReloadMap
            reloadMap();

            // JuMP to FieldLoop
            return;
        }
        
        // check minimap
            // [LBL] STore Zero to $55
        addr_7e0055 = 0;

            // LoaD $03 to A
            // AND A with #>JOY_Y
            // Branch to next if EQuals
            // LoaD #$fb to A
            // Jump to SubRoutine _c0ca3c
            // CoMPare A with #$00
            // Branch to next if EQuals
        if (addr_7e0003 & 16384 && getEventFlag01xx(0xFB)) {

            // Jump to SubRoutine ShowMinimap
            showMiniMap();

            // LoaD $0ad8 to A
            // STore A to $1088
            addr_7e1088 = addr_7e0ad8;

            // LoaD $0ad9 to A
            // STore A to $1089
            addr_7e1089 = addr_7e0ad9;

            // Jump to SubRoutine ReloadMap
            reloadMap();

            // JuMP to FieldLoop
            return;
        }
            
        // [LBL] Jump to SubRoutine CheckPlayerMoveWorld
        checkPlayerMovementWorld();

        // Jump to SubRoutine _c01a1d
        func_c01a1d();

        // Jump to SubRoutine ResetSprites
        resetSprites();

        // Jump to SubRoutine _c02137
        func_c02137();

        // Jump to SubRoutine _c0612b
        func_c0612b();

        // Jump to SubRoutine _c01ec5
        func_c01ec5();

        // Jump to SubRoutine _c01e64
        func_c01e64();

        // Jump to SubRoutine _c0420a
        func_c0420a();

        // JuMP to FieldLoop
        // Reutrn to Subroutine (unused step)
    }
}

static void fieldNMI(void) {}

static void fieldIRQ(void) {
    // PusH Processor stack register
    // Lengthen A
    // PusH A
    // PusH X
    // PusH Y
    // PusH Bank data
    // PusH Direct Page
    // LoaD #$0 to A
    // Shorten A
    // LoaD #$0b00 to X
    // PusH X
    // PulL Direct Page
    // LoaD #$0 to A
    // PulL Bank data
    // LoaD hTIMEUP to A
    // INCrement $40
    addr_7e0040 ++;

    // Lengthen A
    // PulL Direct Page
    // PulL Bank data
    // PulL Y
    // PulL X
    // PulL A
    // PulL Processor stack register
    // ReTurn from Interrupt
}

// execute trigger script
// +X: trigger script index * 2
static void execTriggerScript(Uint8 index) {}

// Address: _061a
static void checkTriggers(void) {}

// Address: _073e
static void checkVehicle(void) {}

// Address: _0853
static void func_c00853(void) {
    // LoaD $169c to Y
    // LoaD $0ad8 to A
    // STore A to ($0adf + Y)
    
    // LoaD $0ad9 to A
    // STore A to ($0ae0 + Y)

    // LoaD ($0ade + Y) to A
    // AND A with #$7f
    // STore A to ($0ade + Y)

    // LoaD $0ad6 to A
    // A Shift Left x5
    // STore A to $08
    addr_7e0008 = addr_7e0ad6 << 5;

    // Load ($0add + Y) to A
    // AND A with #$1f
    // OR A with $08
    // STore A to ($0add + Y)

    // LoaD #$02 to A
    // STore A to $c0
    addr_7e00c0 = 2;

    // Jump to SubRoutine _c04583
    func_c04583();

    // LoaD $57 to A
    // Branch to [_088f] if Not Equals
    if (addr_7e0057 == 0) {
        // LoaD #$0240 to X
        // Jump to SubRoutine ExecTriggerScript
        execTriggerScript(0x240);
    }

    // [_088f] Return to Subroutine
}

static void boardChoco(void) {
    // Return to Subroutine
}

static void landChoco(void) {
    // STore Zero to $0adc
    addr_7e0adc = 0;

    // JuMP to _c00853
    func_c00853();
}

static void boardBlkChoco(void) {
    // LoaD #$00 to A
    // STore A to $3d
    addr_7e003d = 0;

    // [LBL] Jump to SubRoutine WaitVBlank
    waitVblank();

    // Jump to SubRoutine ResetSprites
    resetSprites();

    // LoaD $169c to Y
    // LoaD $3d to A
    // Transfer A to X
    // Load (f:_c00c4f,x) to A
    // OR A with #$80
    // STore A to ($0ade + Y) (Vehicle Height)

    // Jump to SubRoutine _c02137
    func_c02137();

    // Jump to SubRoutine _c0612b
    func_c0612b();

    // Jump to SubRoutine _c01ec5
    func_c01ec5();

    // Jump to SubRoutine _c01e64
    func_c01e64();

    // INCrement $3d
    addr_7e003d ++;

    // LoaD $3d to A
    // CoMPare A with #$40
    // Branch to previous label if Not Equals

    // Return To Subroutine
}

static void boardHiryuu(void) {
}

static void landBlkChoco(void) {}

static void landHiryuu(void) {}

static void boardSub(void) {
    // Return To SubRoutine
}

static void landSub(void) {}

static void func_c009c6(void) {}

static void func_c009f7(void) {}

static void func_c00a11(void) {}

static void boardShip(void) {}

static void landShip(void) {}

static void boardAirship(void) {}

static void landAirship(void) {}

static void func_c00c9f(void) {}

static void func_c00d3d(void) {}

static void checkTresure(void) {}

// Address: _0efe
static void giveGil(void) {}

static void calcGil(void) {}

static void checkPlayerMovementWorld(void) {}

static void func_c0103a(void) {}

static void func_c0104a(void) {}

static void func_c01055(void) {}

static void func_c010c8(void) {}

// check if there is a vehicle at the current position
// return 0 if not, 1 if there is a vehicle
// $23 is a pointer to vehicle data
static void func_c0112d(void) {}

// Address: _119a
static void getWorldTileTransparantUnderwater(void) {}

static void checkPlayerMovementSub(void) {}

// update party z-level (destination tile)
static void updateDestZLevel(void) {}

// update party z-level (current tile)
static void updateCurZLevel(void) {}

static void doTileDamage(void) {}

static void doPoisonDamage(void) {}

static void poisonMosaic(void) {}

// update party sprite priority (current tile)
static void updateCurPriority(void) {}

// update party sprite priority (destination tile)
static void updateDestPriority(void) {}

static void checkDoor(void) {}

static void checkFindPits(void) {}

// 0 = return $c0 (1x)
// 1 = return $c0 >> 1 (0.5x)
// 2 = return $c0 << 1 (2x)
// 3 = return zero (no scroll)
static void calcParallaxScroll(void) {}

static void checkPartyCanMove(void) {}

static void func_c016b7(void) {}

static void func_c016da(void) {}

// Address: _1733
static void updateLocalTilesWorld(void) {}

// Address: _17e8
static void updateLocalTilesNorm(void) {}

// Address: _19f1
// get tile properties at current tile (unused)
static void getTilePropertiesCur(void) {}

static void func_c01a1d(void) {}

static void func_c01ae4(void) {
    // [_1ae4] LoaD $be to A
    // Branch to [_1af5] if EQuals
    // LoaD $be to A
    // SEt Carry flag
    // SuBtract $c0 from A with Carry
    // STore A to $be
    // AND A with #$7f
    // Branch to [_1af5] if Not Equals
    // STore Zero to $be

    // [_1af5] LoaD $ba to A
    // Branch to [_1afc] if Not Equals
    // INCrement $41
    // Return To Subroutine

    // [_1afc] LoaD $41 to A
    // Logical Shift Right
    // Branch to [_1b46] if Carry Set
    // LoaD $0ad9 to A
    // STore A to $76
    // LoaD $0ad8 to A
    // STore A to $75
    // LoaD $ba to A
    // LoaD $06 to X
    // STore X to $71
    // Jump to SubRoutine _c0707d
    // LoaD $1121 to A
    // AND A with #$40
    // Branch to [_1b2d] if Not Equals
    // LoaD $78 to A
    // STore A to $76
    // LoaD $77 to A
    // STore A to $75
    // LoaD $ba to A
    // LoaD #$1000 to X
    // STore X to $71
    // Jump to SubRoutine _c0707d

    // [_1b2d] LoaD $1121
    // Branch to [_1b44] if MInus
    // LoaD $7a to A
    // STore A to $76
    // LoaD $79 to A
    // STore A to $75
    // LoaD $ba to A
    // LoaD #$2000 to X
    // STore X to $71
    // Jump to SubRoutine _c0707d

    // [_1b44] INCrement $9f

    // [_1b46] LoaD $ba to A
    // DECrement A
    // Branch to [_1ba6] if Not Equals
    // LoaD $63 to A
    // AND A with #$1f
    // SEt Carry flag
    // SuBtract $c0 from A with Carry
    // Branch to [_1b5d] if Carry Set
    // LoaD $0ad9 to A
    // DECrement A
    // AND A with #$3f
    // STore A to $0ad9

    // [_1b5d] LoaD $67 to A
    // AND A with #$1f
    // SEt Carry flag
    // SuBtract $1082 from A with Carry
    // Branch to [_1b70] if Carry Set
    // LoaD $0b78 to A
    // DECrement A
    // AND A with #$3f
    // STore A to $0b78

    // [_1b70] LoaD $6b to A
    // AND A with #$1f
    // SEt Carry flag
    // SuBtract $1086 from A
    // Branch to [_1b83] if Carry Set
    // LoaD $0b7a to A
    // DECrement A
    // AND A with #$3f
    // STore A to $0b7a

    // [_1b83] Lengthen A
    // LoaD $63 to A
    // SEt Carry flag
    // SuBtract $c0 from A with Carry
    // AND A with #$0fff
    // STore A to $63
    // LoaD $67 to A
    // SEt Carry flag
    // SuBtract $1082 from A with Carry
    // STore A to $67
    // LoaD $6b to A
    // SEt Carry flag
    // SuBtract $1086 from A with Carry
    // STore A to $6b
    // LoaD $06 to A
    // Shorten A
    // JuMP to _1cc6

    // [_1ba6] DECrement A
    // Branch to [_1c0a] if Not Equals
    // LoaD $61 to A
    // AND A with #$1f
    // CLear Carry flag
    // ADd $co to A with Carry
    // AND A with #$e0
    // Branch to [_1bbd] if EQuals
    // LoaD $0ad8 to A
    // INCrement A
    // AND A with #$3f
    // STore A to $0ad8

    // [_1bbd] LoaD $65 to A
    // AND A with #$1f
    // CLear Carry flag
    // ADd $1080 to A with Carry
    // AND A with #$e0
    // Branch to [_1bd2] if EQuals
    // LoaD $0b77 to A
    // INCrement A
    // AND A with #$3f
    // STore A to $0b77

    // [_1bd2] LoaD $69 to A
    // AND A to #$1f
    // CLear Carry
    // Add $1084 to A with Carry
    // AND A with #$e0
    // Branch to [_1be7] if EQuals
    // LoaD $0b79 to A
    // INCrement A
    // AND A with #$3f
    // STore A to $0b79

    // [_1be7] Lengthen A
    // LoaD $61 to A
    // CLear Carry
    // AND A with #$0fff
    // ADd $c0 to A with Carry
    // STore A to $61
    // LoaD $65 to A
    // CLear Carry
    // ADd $1080 with Carry
    // STore A to $65
    // LoaD $69 to A
    // CLear Carry
    // ADd $1084 to A with Carry
    // STore A to $69
    // LoaD $06 to A
    // Shorten A
    // JuMP to [_1cc6]

    // [_1c0a] DECrement A
    // Branch to [_1c6e] if Not Equals
    // LoaD $63 to A
    // AND A with #$1f
    // CLear Carry
    // ADd $c0 to A with Carry
    // AND A with #$e0
    // Branch to [_1c21] if EQuals
    // LoaD $0ad9 to A
    // INCrement A
    // AND A with #$3f
    // STore A to $0ad9

    // [_1c21] LoaD $67 to A
    // AND A with #$1f
    // CLear Carry
    // ADd $1082 to A with Carry
    // AND A with #$e0
    // Branch to [_1c36] if EQuals
    // LoaD $0b78 to A
    // INCrement A
    // AND A with #$3f
    // STore A to $0b78

    // [_1c36] LoaD $6b to A
    // AND A with #$1f
    // CLear Carry
    // ADd $1086 to A with Carry
    // AND A with #$e0
    // Branch to [_1c4b] if EQuals
    // LoaD $0b7a to A
    // INCrement A
    // AND A with #$3f
    // STore A to $0b7a

    // [_1c4b] Lengthen A
    // LoaD $63 to A
    // CLear Carry
    // AND A with #$0fff
    // ADd $c0 to A with Carry
    // STore A to $63
    // LoaD $67 to A
    // CLear Carry
    // Add $1082 to A with Carry
    // STore A to $67
    // LoaD $6b to A
    // CLear Carry
    // ADd $1086 to A with Carry
    // STore A to $6b
    // LoaD $06 to A
    // Shorten A
    // JuMP to [_1cc6]

    // [_1c6e] LoaD $61 to A
    // AND A with #$1f
    // SEt Carry
    // SuBtract $c0 from A with Carry
    // Branch to [_1c80] if Carry Set
    // LoaD $0ad8 to A
    // DECrement A
    // AND A with #$3f
    // STore A to $0ad8

    // [_1c80] LoaD $65 to A
    // AND A with #$1f
    // SEt Carry
    // SuBtract $1080 from A with Carry
    // Branch to [_1c93] if Carry Set
    // LoaD $0b77 to A
    // DECrement A
    // AND A with #$3f
    // STore A to $0b77

    // [_1c93] LoaD $69 to A
    // AND A with #$1f
    // SEt Carry
    // SuBtract $1084 from A with Carry
    // Branch to [_1ca6] if Carry Set
    // LoaD $0b79 to A
    // DECrement A
    // AND A with #$3f
    // STore A to $0b79

    // [_1ca6] Lengthen A
    // LoaD $61 to A
    // SEt Carry
    // AND A with #$0fff
    // SuBtract $c0 from A with Carry
    // STore A to $61
    // LoaD $65 to A
    // SEt Carry
    // SuBtract $1080 from A with Carry
    // STore A to $65
    // LoaD $69 to A
    // SEt Carry
    // SuBtract $1084 from A with Carry
    // STore A to $69
    // LoaD $06 to A
    // Shorten A

    // [_1cc6] LoaD $61 to A
    // AND A with #$1f
    // Branch to [_1cd4] if Not Equals
    // LoaD $63 to A
    // AND A with #$1f
    // Branch to [_1cd4] if Not Equals
    // INCrement $56 (enable random battle)

    // [_1dc4] INCrement $41
    // Return To Subroutine
}

// Address: _1cd7
static void updateTopChar(void) {}

// Address: _1ce2
static void updatePlayerGfx(void) {}

// Address: _1d1e
// copy to vram
static void copyPlayerGfx(void) {}

// Address: _1e14
// copy to vram
static void copyAltGfx(void) {}

static void func_c01e64(void) {}

static void func_c01ec5(void) {}

static void func_c01f57(void) {}

static void func_c01fb4(void) {}

static void func_c01fff(void) {}

static void func_c0201f(void) {}

static void func_c0203f(void) {}

static void func_c02137(void) {}

static void func_c022fb(void) {}

// update party sprite
static void drawPlayerSprite(void) {}

static void loadOverlayGfx(void) {}

static void loadOverlayProp(void) {}

static void drawOverlaySprites(void) {}

static void updateOverlay(void) {}

// Address: _2f95
static void execNPCScript(void) {}

// Address: _317b
static void checkNPCEvents(void) {}

static void func_c0324b(void) {}

static void func_c03289(void) {}

// Address: _32ab
static void updateObjects(void) {}

// Address: _34eb
// x: direction
// a: movement direction (out, zero if can't move)
static void canNPCMoveToTile(void) {}

// Address: _351c
static void moveTowardsParty(void) {}

// Address: _3555
static void moveAwayFromParty(void) {}

// Address: _358e
static void drawHiryuu(void) {}

// Address: _39b3
static void drawObjectSprites(void) {}

// Address: _3bac
static void updateObjectPositions(void) {}

// Address: _3cbb
static void getPointerToObjLayout(void) {}

// Address: _3cd3
static void clearObjLayout(void) {}

// Address: _3ce0
static void addObjectToObjLayout(void) {}

// Address: _3cf8
static void removeObjectToObjLayout(void) {}

// Address: _3d0b
static void getObjectInObjLayout(void) {}

// Address: _3d15
// get tile z-level (unused)
// a: tile index, z-level (out)
static void getTileZ(void) {}

// Address: _3d28
static void loadNPCGfx(void) {}

// Address: _3e98
static void getPointerToNPCProperties(void) {}

// Address: _3eaa
static void loadNPCs(void) {}

// Address: 4008
static void greyscalePalette(void) {}

static void func_c0406b(void) {}

// Address: _40d8
static void copyDataToVram(void) {}

static void func_c04107(void) {}

static void func_c041f1(void) {}

static void func_c0420a(void) {}

static void showCutsceneFromField(Uint8 id) {}

// Address: _44e3
static void initMapBank(void) {}

// Address: _450a
static void initVehicles(void) {}

// Address: _4528
static void initCharNames(void) {}

static void openMenu(void) {}

static void func_c0456b(void) {}

static void func_c04583(void) {}

static void playSong(void) {}

// Address: _4635
static void playSound(void) {}

// play sound effect
// A: sound effect
static void playSfx(void) {}

// Address: _4653
static void updateScreenMosaic(void) {}

static void func_c046c4(void) {}

static void func_c04741(void) {}

static void func_c04798(void) {}

static void func_c047aa(void) {}

static void func_c047f7(void) {}

static void func_c04834(void) {}

static void initNPCFlags(void) {}

static void initEventFlags(void) {}

static void initNewCharData(void) {}

static void resetRam_0000_to_1D00(void) {
    // Essentially loops 2 bytes over a given range
    // to be set as Zero.

    // Can't be done here as not all variables
    // share the same type. Some are even objects.

    resetRam_0B00_to_1D00();
}

static void resetRam_0B00_to_1D00(void) {
    // See above function.
}

static void func_c04931(void) {}

// Address: _49d7
static void initColorAddition(void) {}

// Address: _49e9
static void initColorSubtraction(void) {}

// Address: _49ff
static void updateFixedColor(void) {}

// Address: _4a44
static void setFixedColorParams(void) {}

static void initFadeIn(void) {}

static void initFadeOut(void) {}

static void func_c04a7a(void) {}

static void func_c04aad(void) {}

// Address: _4ac1
static void waitForKeypress(void) {}

// copy vehicle graphics to vram (3bpp)
// +$30: source address (+$db0000)
// +$33: vram address
//  $35: tile count
static void tfrVehicleGfx(void) {}

static void tfrWorldGfx(void) {}

// Address: _4bc0
static void updateScrollingRegisters(void) {}

static void updateCtrl(void) {}

static void resetSprites(void) {}

// Address: _4cad
static void hideSpritesInCutscenes(void) {}

static void tfrVram(void) {}

static void disableInterrupts(void) {}

static void enableInterrupts(void) {}

// Address: _4d06
static void clearVramForCutscenes(void) {}

static void fillVram(void) {
    // LoaD #$80 to A
    // STore A to hVMAINC
    // STore Zero to hMDMAEN
    
    // LoaD #$09 to A
    // STore A to hDMA0::CTRL

    // LoaD #<hVMDATAL to A
    // STore A to hDMA0::HREG

    // LoaD $2e to X
    // STore X to hVMADDL

    // LoaD #$0b6d to X
    // STore X to hDMA0::ADDR
    // STore Z to hDMA0::ADDR_B

    // LoaD $2c to X
    // STore X to hDMA0::SIZE

    // LoaD A to #$01
    // STore A to hMDMAEN

    // Return To Subroutine
}

static void tfrSprites(void) {}

static void tfrPallets(void) {}

static void func_c04d8e(void) {}

// Hex to Dec

static void waitVblank(void) {
    // STore Zero to $51
    // [LBL] LoaD $51 to A
    // Branch to previous label if EQuals
    // STore Zero to $51
    // Return to SubRoutine
}

static void initInterrupts(void) {}

static void initHardware(void) {
    // LoaD #$80 to A
    // STore A to hINIDISP
    inidisp = 0x80;

    // LoaD #0 to A
    // STore A to hNMITIMEN
    h_nmitimen = 0;

    // STore Zero to hMDMAEN
    h_mdmaen = 0;

    // STore Zero to hHDMAEN
    // LoaD #3 to A
    // STore A to hOBJSEL
    // STore Zero to hOAMADDL
    // STore Zero to hOAMADDH

    // LoaD #$09 to A
    // STore A to hBGMODE
    bgMode = 9;

    // STore Zero to hMOSAIC
    mosaic = 0;

    // LoaD #$00 to A
    // STore A to hBG12NBA
    // LoaD #$04 to A
    // STore A to hBG34NBA
    // LoaD #$80 to A
    // STore A to hVMAINC

    // STore Zero to hM7SEL
    mode7_settings = 0;

    // STore Zero to hM7A
    // LoaD #$08 to A
    // STore A to hM7A
    mode7_a = 8;

    // STore Zero to hM7B twice
    mode7_b = 0;

    // STore Zero to hM7C twice
    mode7_c = 0;

    // STore Zero to hM7D
    // LoaD #$08 to A
    // STore A to hM7D
    mode7_d = 8;

    // LoaD #$80 to A
    // STore A to hM7X twice
    mode7_x = 0x80;

    // STore A to hM7Y twice
    mode7_y = 0x80;

    // STore A to hCGADD
    // LoaD #$bf to A
    // STore A to hW12SEL
    w12sel = 0xBF;

    // LoaD #$0b to A
    // STore A to hW34SEL
    w34sel = 0x0B;

    // LoaD #$bb to A
    // STore A to hWOBJSEL
    wObjSel = 0xBB;

    // LoaD #$08 to A
    // STore A to hWHO
    wh0 = 8;

    // LoaD #$f7 to A
    // STore A to hWH1
    wh1 = 0xF7;

    // LoaD #$ff to A
    // STore A to hWH2
    wh2 = 0xFF;

    // LoaD #$00 to A
    // STore A to hWH3
    wh3 = 0;

    // LoaD #$01 to A
    // STore A to hWBGLOG
    bgMask = 1;

    // LoaD #$00 to A
    // STore A to hWOBJLOG
    objMask = 0;

    // LoaD #$13 to A
    // STore A to hTM
    enableMain = 0x13;

    // LoaD #$04 to A
    // STore A to hTS
    enableSub = 4;

    // LoaD #$17 to A
    // STore A to hTMW
    enableMainWindow = 0x17;

    // STore Zero to hTSW
    enableSubWindow = 0;

    // LoaD #$22 to A
    // STore A to hCGSWSEL
    cgWSel = 0x22;

    // LoaD #$e0 to A
    // STore A to hCOLDATA
    colData = 0xE0;

    // LoaD #$00 to A
    // STore A to hSETINI
    setIni = 0;

    // LoaD #$ff to A
    // STore A to hWRIO
    h_wrio = 0xFF;

    // STore Zero to hHTIMEL
    h_htimel = 0;

    // STore Zero to hHTIMEH
    h_htimeh = 0;

    // STore Zero to hVTIMEL
    h_vtimel = 0;

    // STore Zero to hVTIMEH
    h_vtimeh = 0;

    // Return to SubRoutine
}

static void generateRandom(void) {}

static void crystalShatterAnim(void) {}

static void loadMap(void) {}

static void loadMapNoFade(void) {}

static void reloadMap(void) {
    // LoaD $0ad6 from X
    // ComPare X with #$0005
    // Branch to next if Carry Set
    if (addr_7e0ad6 < 5) {
        // (World Map)
        // Jump to SubRoutine ReloadWorldMap
        reloadWorldMap();

        // Jump to SubRoutine FadeInMap
        fadeInMap();

        // Return To Subroutine

    // [LBL] Sub-Map
    } else {
        // Jump to SubRoutine ReloadSubMap
        reloadSubMap();

        // Jump to SubRoutine FadeInMap
        fadeInMap();
        
        // Jump to SubRoutine ShowMapTitle
        showMapTitle();
        
        // Return To Subroutine
    }
}

// Address: _548f
static void loadParentMap(void) {
    // LoaD $0af5 to X
    // STore $0ad6 to X
    addr_7e0ad6 = addr_7e0af5;

    // LoaD $0af7 to A
    // STore $1088 to XA
    addr_7e1088 = addr_7e0af7;

    // LoaD $0af8 to A
    // STore $1089 to A
    addr_7e1089 = addr_7e0af8;

    // INCrement $6e
    addr_7e006e ++;

    // Jump to SubRoutine LoadMap
    loadMap();

    // Return to Subroutine
}

static void func_c054a7(void) {}

static void func_c054f6(void) {}

static void loadWorldMap(void) {}

static void reloadWorldMap(void) {}

static void loadWorldMapPalette(void) {}

static void loadSubMap(void) {}

static void reloadSubMap(void) {}

static void func_c057f9(void) {}

// Address: _580e
static void initAutoScroll(void) {}

// Address: _5875
static void loadMapLayout(void) {}

// Address: _58db
static void loadMapPalette(void) {}

// Address: _591a
static void loadMapGfx(void) {}

static void func_c05adb(void) {}

// Address: _5af6
static void loadMapProps(void) {}

// Address: _5b2d
static void initMapColorMathSettings(void) {}

static void func_c05bf4(void) {}

static void func_c05bf8(void) {}

static void func_c05c01(void) {}

// Address: _5cbd
static void loadTreasureChests(void) {}

// Address: _5d30
static void updateWindowMaskCircle(void) {}

static void func_c05d54(void) {}

static void func_c05d87(void) {}

// Address: _5e2b
static void copyTileLayoutToVram(void) {}

static void func_c05e61(void) {}

static void func_c05ee5(void) {}

static void func_c05f3e(void) {}

static void func_c05f8d(void) {}

static void pitfallFadeOutAnim(void) {}

static void fadeOutMap(void) {}

static void pitfallFadeInAnim(void) {}

static void fadeInMap(void) {}

static void func_c0612b(void) {}

static void func_c06134(void) {}

static void func_c061d7(void) {}

static void func_c062bc(void) {}

static void func_c0630a(void) {}

static void func_c0637e(void) {}

static void func_c063d4(void) {}

static void func_c06465(void) {}

static void func_c064bb(void) {}

static void func_c06513(void) {}

static void func_c065a3(void) {}

static void showMiniMap(void) {}

static void func_c06731(void) {}

static void func_c06755(void) {}

static void func_c0679c(void) {}

static void func_c067ec(void) {}

static void func_c06831(void) {}

static void loadWorldTilemap(void) {}

static void loadSubTilemap(void) {}

static void fillTilemap(void) {}

static void loadWorldTileset(void) {}

static void loadSubTileset(void) {}

static void func_c06b99(void) {}

static void func_c06bac(void) {}

// Address: _6bdb
static void initBgScrollPos(void) {}

static void func_c06c4a(void) {}

static void func_c06c6a(void) {}

static void func_c06c9d(void) {}

static void func_c06cd4(void) {}

static void func_c06d0c(void) {}

static void func_c06de9(void) {}

// Address: _6df5
static void horizontalScrolling(void) {}

// Address: _6e7a
static void verticalScrolling(void) {}

static void modBgTilemap(void) {}

static void func_c0703e(void) {}

static void func_c0707d(void) {}

static void func_c07221(void) {}

static void func_c0722f(void) {}

static void func_c07241(void) {}

static void showDialog(void) {}

static void getDialogPtr(void) {}

static void loadDialogText(void) {}

static void func_c08451(void) {}

static void func_c08459(void) {}

static void func_c08466(void) {}

static void func_c08477(void) {}

static void func_c08493(void) {}

static void func_c084af(void) {}

static void func_c084e9(void) {}

static void func_c08508(void) {}

static void func_c0850d(void) {}

static void func_c08512(void) {}

// Address: _8a5f gets kanji from $1e

// Address: _8a6a gets kanji from $1f

// Address: _8a85
static void getSpellName(void) {}

// Address: _8ab7
static void getItemName(void) {}

// Address: _8aea
static void getGilAmount(void) {}

static void func_c08b53(void) {}

static void func_c08ba4(void) {}

static void func_c08bd3(void) {
    // LoaD $06 to X
    // ...
    // INcrement X
    // ComPare X to #$0031 (#49)
    // Branch to [@8bd5] if Not Equals
    for (Uint8 i = addr_7e0006; i < 49; i++) {
        // [@8bd5] LoaD ($7f6a8a + x) to A
        // STore A to ($7f6a59 + x)
    }
    // Return To Subroutine
}

static void func_c08be4(void) {}

static void func_c08c2e(void) {}

static void func_c08c7b(void) {}

static void func_c08c92(void) {}

static void func_c08d0e(void) {}

static void func_c08d3b(void) {}

static void func_c08e08(void) {}

static void func_c08e23(void) {}

static void func_c08ed3(void) {}

// Address: _8f01
static void loadFontGfx(void) {}

static void func_c08f54(void) {}

// Address: _8f78
static void drawYesNoIndicator(void) {}

// Address: _8fed
static void showYesNoWindow(void) {}

static void func_c090ad(void) {}

// Address: _9133
static void showGPWindow(void) {}

static void func_c091ed(void) {}

static void showMapTitle(void) {
    // LoaD $0b53 to A
    // Branch to [DONE] if EQuals
    
    // LoaD $16a0 to A
    // Branch to next label if EQuals (if map title is disabled)
    
    // LoaD #$01 to A
    // STore A to $b4

    // Jump to SubRoutine DrawMapTitleWindow
    // Jump to SubRoutine _c04ac1 (wait for keypress)
    // Jump to SubRoutine HideMapTitleWindow
    // [LBL] STore Zero to $16a0
    // INCrement $a5
    // Jump to SubRoutine WaitVBlank
    
    // LoaD #$01 A
    // STore A to $10b8

    // [DONE] Return To Subroutine
}

static void initMapTitle(void) {}

// Address: _933d
// Output: X?
static void drawMapTitleWindow(void) {
    // Jump to SubRoutine _8bd3
    // LoaD $b4 to A
    // SEt Carry flag
    // ADd $0ad9 to A with Carry
    // STore A to $76
    addr_7e0076 = addr_7e0ad9 + addr_7e00b4;

    // LoaD $0ad8 to A
    // STore A to $75
    addr_7e0075 = addr_7e0ad8;

    // LoaD #$00 to A
    // STore A to $b5
    // ...
    // LoaD $b5 to A
    // CoMPare A with #$02
    // Branch to [@9351] if Not Equals
    for (addr_7e00b5 = 0; addr_7e00b5 < 2; addr_7e00b5++) {
        // [@9351] Jump to SubRoutine WaitVBlank
        waitVblank();

        // LoaD #$01 to A
        // LoaD $06 to X
        // STore X to $71
        addr_7e0071 = addr_7e0006;

        // Jump to SubRoutine _707d
        func_c0707d();

        // LoaD $b5 to A
        // Lengthen A
        // eXchange high Bytes in A with lower
        // Logical Shift A Right x2
        // Transfer A to X
        Uint8 x = addr_7e00b5;
        x %= 0x10;
        x *= 0x100000;

        // LoaD $06 to A
        // Shorten A

        // LoaD #$0004 to Y
        // ...
        // INcrement Y by 2
        // ComPare Y with #$003c (#60)
        // Branch to [@936c] if Not Equals
        for (Uint8 y = 4; y < 60; y+=2) {
            // [@936c] LoaD f:_c09399,x to A
                // _c09399:
                    // .byte   $d1,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7
                    // .byte   $d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d7,$d2,$00,$00,$00,$00
            // STore A to ($16f3 + y)

            // LoaD #$03 to A
            // STore A to ($16f4 + y)

            // LoaD (f:_c093b9 + x) to A
            // STore A to ($1733 + y)
            
            // LoaD #$03 to A
            // STore A to ($1734 + y)

            // INcrement X
            x ++;
        }

        // INCrement $a6
        addr_7e00a6 ++;

        // INCrement $76
        addr_7e0076 ++;

        // INCrement $b5
            // Already done within loop
    }

    // Return To Subroutine
}

static void hideMapTitleWindow(void) {
    // LoaD $b4 to A
    // SEt Carry flag
    // ADd $0ad9 to A with Carry
    // CLear Carry flag
    // ADd #$01 to A with Carry
    // STore A to $76

    // LoaD $0ad8 to A
    // STore A to $75

    // [LBL] Jump to SubRoutine WaitVBlank
    // LoaD #$01 to A

    // LoaD $06 to X
    // STore X to $71

    // Jump to SubRoutine _c0707d
    // INCrement $a6
    // DECrement $76
    // DECrement $b5

    // LoaD $b5 to A
    // Branch to previous label if Not Equals
    // Return to SubRoutine
}

static void func_c09440(void) {}

static void func_c094a8(void) {}

static void func_c09618(void) {}

static void func_c0964c(void) {}

static void func_c09695(void) {}

static void func_c09704(void) {}

static void func_c09772(void) {}

static void func_c0975f(void) {}

// Address: _9799
static void updatePaletteAnim(void) {}

static void func_c097e2(void) {}

static void func_c0980d(void) {}

static void func_c09838(void) {}

static void func_c09865(void) {}

static void func_c098e2(void) {}

// Address: _990d
static void initPaletteAnim(void) {}

static void func_c0996d(void) {}

// Address: _9a00
static void updateMapAnim(void) {}

// Address: _9a96
static void initMapAnim(void) {}

// Address: _9b01
static void loadAnimTileGfx(void) {}

static void func_c09c3d(void) {}

static void func_c09cac(void) {}

// Address: _a18b
static void updateTimer(void) {}

// Address: _a1c1
static void speedUpMusicWithTimer(void) {}

static void execEvent(void) {}

static void nextEventCmd(void) {}

static void terminateEvent(void) {}

static void func_c0a365(void) {}

static void func_c0a380(void) {}

static void func_c0a3c9(void) {}

static void func_c0a40a(void) {}

static void func_c0a449(void) {}

static void func_c0a45f(void) {}

// Address: _a672
static void eventCmd_bf(void) {}

// Address: _a685
static void eventCmd_bf1a(void) {}

// Address: _a766
static void eventCmd_bf18(void) {}

static void func_c0a7be(void) {}

// Address: _a7c9
static void eventCmd_bf19(void) {}

// Address: _a86d
static void eventCmd_bf15(void) {}

static void func_c0a933(void) {}

// Address: _a98b
static void eventCmd_bf14(void) {}

static void func_c0aa0e(void) {}

// Address: _ab49
static void eventCmd_bf13(void) {}

// Address: _ab65
static void eventCmd_bf12(void) {}

static void func_c0ab8e(void) {}

static void func_c0abb5(void) {}

// Address: _ac01
// Show epilogue cutscene
static void eventCmd_bf0f(void) {}

// Address: _ac1c
// Show game stats (unknown cave psychic)
static void eventCmd_bf10(void) {}

// Address: _ac37
static void eventCmd_bf07(void) {}

// Address: _ac4a
static void eventCmd_bf08(void) {}

// Address: _ac65
static void eventCmd_bf09(void) {}

// Address: _ac71
static void eventCmd_bf0a(void) {}

static void func_c0ac80(void) {}

static void func_c0ac8b(void) {}

static void func_c0acb1(void) {}

static void func_c0acdd(void) {}

static void func_c0ad01(void) {}

static void func_c0ad28(void) {}

static void func_c0ad54(void) {}

static void func_c0ad86(void) {}

static void func_c0ada0(void) {}

static void func_c0adb7(void) {}

static void func_c0add6(void) {}

static void func_c0ae0b(void) {}

static void func_c0ae32(void) {}

// Address: _b044
// Game Over
static void eventCmd_bf00(void) {}

// Address: _b04c
// Load parent map
static void eventCmd_bf01(void) {}

// Address: _b052
static void eventCmd_bf16(void) {}

// Address: _b0a7
// Crystal Shatters
static void eventCmd_bf02(void) {}

// Address: _b10b
static void eventCmd_bf11(void) {}

// Address: _b185
static void eventCmd_bf05(void) {}

static void func_c0b240(void) {}

// Address: _b259
static void eventCmd_bf04(void) {}

static void func_c0b2a5(void) {}

static void func_c0b35c(void) {}

static void func_c0b371(void) {}

static void func_c0b3cd(void) {}

// Address: _b548
static void eventCmd_bf06(void) {}

static void func_c0b594(void) {}

// Address: _b5b1
// Tower of Walse sinking
static void eventCmd_bf0b(void) {}

static void func_c0b5fd(void) {}

// Address: _b60e
static void eventCmd_bf17(void) {}

// Address: _b6b0
static void eventCmd_bf03(void) {}

static void func_c0b750(void) {}

static void func_c0b75e(void) {}

static void func_c0b791(void) {}

// Address: _b834
static void eventCmd_bf0c(void) {}

// Address: _b83a
static void eventCmd_bf0e(void) {}

// Address: _b848
static void eventCmd_bf0d(void) {}

static void func_c0b854(void) {}

// Address: _b8a0
// Show map title
static void eventCmd_ea(void) {}

// Address: _b8b7
// Transfer Galuf's stats to Krile
static void eventCmd_eb(void) {}

// Address: _b8c8
// Load character stats (ending)
static void eventCmd_e9(void) {}

// Address: _b991
static void eventCmd_e7(void) {}

// Address: _b9cf
// Greyscale color palettes
static void eventCmd_e6(void) {}

// Address: _b9d5
// Wait for spc-2
static void eventCmd_e4(void) {}

// Address: _b9dd
// Wait for spc-3
static void eventCmd_e5(void) {}

// Address: _b9e5
// Set character data
static void eventCmd_dd(void) {}

// Address: _b9ef
static void eventCmd_da(void) {}

static void func_c0b9f5(void) {}

// Address: _ba98
// Show mini-map
static void eventCmd_79(void) {}

// Address: _ba9e
// Update party graphic
static void eventCmd_db(void) {}

// Address: _baa8
// Change color palette
static void eventCmd_d9(void) {}

// Address: _baae
static void changeColorPalette(void) {}

// Address: _bad9
// Show cutscene
static void eventCmd_b6(void) {}

// Address: _bae1
// Pixelate the screen
static void eventCmd_ae(void) {}

// Address: _baef
// Set battle flag
static void eventCmd_a6(void) {}

// Address: _baf7
// Clear battle flag
static void eventCmd_a7(void) {}

// Address: _baff
static void eventCmd_7b(void) {}

// Address: _bb24
static void eventCmd_7f(void) {}

// Address: _bb4c
// Inn
static void eventCmd_ad(void) {}

// Address: _bc51
static void calcInnPrice(void) {}

// Address: _bc64
// Give magic spell
static void eventCmd_ac(void) {}

// Address: _bc6c
// Set window mask circle diameter
static void eventCmd_c0(void) {}

static void func_c0bc9f(void) {}

// Address: _bcb4
// Spc command
static void eventCmd_d0(void) {}

// Address: _bcce
// Wait
static void eventCmd_70(void) {}

// Address: _bcf5
// Tutorial menu
static void eventCmd_dc(void) {}

// Address: _bd0d
// Name change menu
static void eventCmd_7a(void) {}

// Address: _bd1e
// Shop
static void eventCmd_a1(void) {}

// Address: _bd36
// Character stats battle (ending)
static void eventCmd_e8(void) {}

// Address: _bd8d
// Event battle
static void eventCmd_bd(void) {}

// Address: _bdbc
// Event battle (can lose)
static void eventCmd_e2(void) {}

// Address: _bde6
static void eventBattle(void) {}

// Address: _be62
// Add/remove character
static void eventCmd_b7(void) {}

// Address: _bee9
// Give job
static void eventCmd_c6(void) {}

// Address: _bf07
// Give gil
static void eventCmd_af(void) {}

// Address: _bf10
// Take gil
static void eventCmd_b0(void) {}

// Address: _bf3f
static void calcGilForEvent(void) {}

// Address: _bf92
// Add item to inventory
static void eventCmd_aa(void) {}

// Address: _bfc0
// Remove item to inventory
static void eventCmd_ab(void) {}

// Address: _bfdd
static void findItemSlot(void) {}

// Address: _bff1
// Remove status
static void eventCmd_ba(void) {}

// Address: _c00f
// Set status
static void eventCmd_bb(void) {}

// Address: _c02d
static void eventCmd_bc(void) {}

// Address: _c04b
// Modify HP
static void eventCmd_a8(void) {}

// Address: _c0e0
// Modify MP
static void eventCmd_a9(void) {}

// Address: _c164
static void getPtrToCharData(void) {}

static void func_c0c19d(void) {}

// Address: _c1aa
// Hide vehicle
static void eventCmd_c2(void) {}

// Address: _c1bb
// Show vehicle
static void eventCmd_d2(void) {}

// Address: _c1ed
// Resume Suspended Song
static void eventCmd_c9(void) {}

// Address: _c212
// Play Song
static void eventCmd_b4(void) {}

// Play Song (specify volume)
static void eventCmd_d4(void) {}

// Address: _c25a
// Play Sound Effect
static void eventCmd_b5(void) {}

// Address: _c266
// Play Sound Effect (specify volume)
static void eventCmd_d5(void) {}

// Address: _c27c
// Set scroll speed to normal
static void eventCmd_76(void) {}

// Address: _c282
// Set scroll speed to slow
static void eventCmd_78(void) {}

// Address: _c28a
// Set scroll speed to fast
static void eventCmd_77(void) {}

// Address: _c292
// Jump forward randomly
static void eventCmd_f1(void) {}

// Address: _c2af
// Show Y/N Dialog
static void eventCmd_f0(void) {}

// Address: _c362
// Change vehicle
static void eventCmd_d6(void) {}

// Address: _c3d3
// load map (fade out/in)
static void eventCmd_e0(void) {}

// Address: _c3f7
// load map (no fade)
static void eventCmd_e1(void) {}

// Address: _c418
// load map (fade out only)
static void eventCmd_e3(void) {}

static void func_c0c43f(void) {}

// Address: _c4e0
// change background (relative)
static void eventCmd_f4(void) {}

// Address: _c504
// change background (absolute)
static void eventCmd_f3(void) {}

// Address: _c56f
// disable timer
static void eventCmd_7c(void) {}

// Address: _c57a
// set object position (relative)
static void eventCmd_d8(void) {}

// Address: _c5c4
// set object position (absolute)
static void eventCmd_d3(void) {}

// Address: _c5e4
static void removeCurObjFromObjLayout(void) {}

// Address: _c5fb
// Start timer
static void eventCmd_d1(void) {}

// Address: _c623
// Start timer (speed up music)
static void eventCmd_d7(void) {}

// Address: _c64b
static void eventCmd_7d(void) {}

// Address: _c65a
// Flash screen
static void eventCmd_c5(void) {}

// Address: _c67d
// Color addition
static void eventCmd_b8(void) {}

// Address: _c692
// Color subtraction
static void eventCmd_b9(void) {}

// Address: _c6a7
// Stop fade
static void eventCmd_7e(void) {}

// Address: _c6ac
// Fade in
static void eventCmd_c3(void) {}

// Address: _c6b7
// Fade out
static void eventCmd_c4(void) {}

// Address: _c6c4
// Shake screen
static void eventCmd_be(void) {}

// Address: _c6cb
static void eventCmd_c1(void) {}

// Address: _c6d4
// Set party sprite graphic
static void eventCmd_b1(void) {}

static void func_c0c6de(void) {}

// Address: _c70b
// Wait xx frames
static void eventCmd_b2(void) {}

// Address: _c71c
// Wait xx * 15 frames
static void eventCmd_b3(void) {}

// Address: _c735
// Show npc dialog
static void eventCmd_a0(void) {}

// Address: _c758
// Set event flag (0-255)
static void eventCmd_a2(void) {}

// Address: _c76a
// Set event flag (256-511)
static void eventCmd_a4(void) {}

// Address: _c77c
// Clear event flag (0-255)
static void eventCmd_a3(void) {}

// Address: _c78e
// Clear event flag (256-511)
static void eventCmd_a5(void) {}

// Address: _c796
static void clearEventFlag_256_511(void) {}

// Address: _c7a4
// Show dialog
static void eventCmd_c8(void) {}

// Address: _c7c8
static void initObjectMovement(void) {}

static void func_c0c7f9(void) {}

static void func_c0c932(void) {}

// Address: _c98a
static void initCameraMovement(void) {}

// Address: _c9a5
static void giveSpell(void) {}

// Address: _c9c1
static void getNPCFlag(void) {}

// Address: _c9ce
// Set NPC flag
static void eventCmd_ca(void) {}

// Address: _c9e4
// Clear NPC flag
static void eventCmd_cb(void) {}

// Address: _c9fa
static void setBattleFlag(void) {}

// Address: _ca08
static void clearBattleFlag(void) {}

// Address: _ca16
static void getTrasureFlag(void) {}

// Address: _ca21
static void setTreasureFlag(void) {}

// Address: _ca2f
static void getEventFlag00xx(void) {}

// Address: _ca3c
static Uint8 getEventFlag01xx(Uint8 val) {return 0;}

// Address: _ca49
static void getFlagIndex(void) {}

// Address: _ca69
static void checkRandomBattlesSub(void) {}

// Address: _cb11
static void checkRandomBattlesWorld(void) {}

// Address: _cc52
static void updateRandomForBattles(void) {}

static void func_c0cc6d(void) {}

static void battleBlurSub(void) {}

static void battleBlurWorld(void) {}

static void battleBlur(void) {}

// Address: _ccf0
static void randomBattle(void) {}

// Address: _cec0
static void reset(void) {}

// Address: _cee0 jumps long to c01f00

// Address: _cee4 jumps long to c01f04

// Remaining addresses below are all data