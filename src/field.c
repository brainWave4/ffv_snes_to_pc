// Bank Range: C0
#include "field.h"

//.import _c10003, _c10006
#include "btlgfx.h"

//.import ExecBattle_ext
#include "battle.h"

//.import ExecMenu_ext, _c2a008
#include "menu.h"

//.import ShowCutscene_ext, Decomp_ext
#include "cutscene.h"

//.import InitSound_ext, ExecSound_ext
#include "sound.h"

static void fieldLoop(void);
static void fieldNMI(void);
static void fieldIRQ(void);
static void execTriggerScript(void);
static void checkTriggers(void);
static void checkVehicle(void);
static void func_c00853(void);
static void boardChoco(void);
static void landChoco(void);
static void boardBlkChoco(void);
static void boardHiryuu(void);
static void landBlkChoco(void);
static void landHiryuu(void);
static void boardSub(void);
static void landSub(void);
static void func_c009c6(void);
static void func_c009f7(void);
static void func_c00a11(void);
static void boardShip(void);
static void landShip(void);
static void boardAirship(void);
static void landAirship(void);
static void func_c00c9f(void);
static void func_c00d3d(void);
static void checkTresure(void);
static void giveGil(void);
static void calcGil(void);
static void checkPlayerMovementWorld(void);
static void func_c0103a(void);
static void func_c0104a(void);
static void func_c01055(void);
static void func_c010c8(void);
static void func_c0112d(void);
static void getWorldTileTransparantUnderwater(void);
static void checkPlayerMovementSub(void);
static void updateDestZLevel(void);
static void updateCurZLevel(void);
static void doTileDamage(void);
static void doPoisonDamage(void);
static void poisonMosaic(void);
static void updateCurPriority(void);
static void updateDestPriority(void);
static void checkDoor(void);
static void checkFindPits(void);
static void calcParallaxScroll(void);
static void checkPartyCanMove(void);
static void func_c016b7(void);
static void func_c016da(void);
static void updateLocalTilesWorld(void);
static void updateLocalTilesNorm(void);
static void getTilePropertiesCur(void);
static void func_c01a1d(void);
static void func_c01ae4(void);
static void updateTopChar(void);
static void updatePlayerGfx(void);
static void copyPlayerGfx(void);
static void copyAltGfx(void);
static void func_c01e64(void);
static void func_c01ec5(void);
static void func_c01f57(void);
static void func_c01fb4(void);
static void func_c01fff(void);
static void func_c0201f(void);
static void func_c0203f(void);
static void func_c02137(void);
static void func_c022fb(void);
static void drawPlayerSprite(void);
static void loadOverlayGfx(void);
static void loadOverlayProp(void);
static void loadOverlaySprites(void);
static void updateOverlay(void);
static void execNPCScript(void);
static void checkNPCEvents(void);
static void func_c0324b(void);
static void func_c03289(void);
static void updateObjects(void);
static void canNPCMoveToTile(void);
static void moveTowardsParty(void);
static void moveAwayFromParty(void);
static void drawHiryuu(void);
static void drawObjectSprites(void);
static void updateObjectPositions(void);
static void getPointerToObjLayout(void);
static void clearObjLayout(void);
static void addObjectToObjLayout(void);
static void removeObjectToObjLayout(void);
static void getObjectInObjLayout(void);
static void getTileZ(void);
static void loadNPCGfx(void);
static void getPointerToNPCProperties(void);
static void LoadNPCs(void);
static void greyscalePalette(void);
static void func_c0406b(void);
static void copyDataToVram(void);
static void func_c04107(void);
static void func_c041f1(void);
static void func_c0420a(void);
static void showCutsceneFromField(uint8_t id);
static void initMapBank(void);
static void initVehicles(void);
static void initCharNames(void);
static void openMenu(void);
static void func_c0456b(void);
static void func_c04583(void);
static void playSong(void);
static void playSound(void);
static void playSfx(void);
static void updateScreenMosaic(void);
static void func_c046c4(void);
static void func_c04741(void);
static void func_c04798(void);
static void func_c047aa(void);
static void func_c047f7(void);
static void func_c04834(void);
static void initNPCFlags(void);
static void initEventFlags(void);
static void initNewCharData(void);
static void resetRam_0000_to_1D00(void);
static void resetRam_0B00_to_1D00(void);
static void func_c04931(void);
static void initColorAddition(void);
static void initColorSubtraction(void);
static void updateFixedColor(void);
static void setFixedColorParams(void);
static void initFadeIn(void);
static void initFadeOut(void);
static void func_c04a7a(void);
static void func_c04aad(void);
static void waitForKeypress(void);
static void tfrVehicleGfx(void);
static void tfrWorldGfx(void);
static void updateScrollingRegisters(void);
static void updateCtrl(void);
static void resetSprites(void);
static void hideSpritesInCutscenes(void);
static void tfrVram(void);
static void disableInterrupts(void);
static void enableInterrupts(void);
static void clearVramForCutscenes(void);
static void fillVram(void);
static void tfrSprites(void);
static void tfrPallets(void);
static void func_c04d8e(void);
static void waitVram(void);
static void initInterrupts(void);
static void initHardware(void);
static void generateRandom(void);
static void crystalShatterAnim(void);
static void loadMap(void);
static void loadMapNoFade(void);
static void reloadMap(void);
static void loadParentMap(void);
static void func_c054a7(void);
static void func_c054f6(void);
static void loadWorldMap(void);
static void loadWorldMapPalette(void);
static void loadSubMap(void);
static void func_c057f9(void);
static void initAutoScroll(void);
static void loadMapLayout(void);
static void loadMapPalette(void);
static void loadMapGfx(void);
static void func_c05adb(void);
static void loadMapProps(void);
static void initMapColorMathSettings(void);
static void func_c05bf4(void);
static void func_c05bf8(void);
static void func_c05c01(void);
static void loadTreasureChests(void);
static void updateWindowMaskCircle(void);
static void func_c05d54(void);
static void func_c05d87(void);
static void copyTileLayoutToVram(void);
static void func_c05e61(void);
static void func_c05ee5(void);
static void func_c05f3e(void);
static void func_c05f8d(void);
static void pitfallFadeOutAnim(void);
static void fadeOutMap(void);
static void pitfallFadeInAnim(void);
static void fadeInMap(void);
static void func_c0612b(void);
static void func_c06134(void);
static void func_c061d7(void);
static void func_c062bc(void);
static void func_c0630a(void);
static void func_c0637e(void);
static void func_c063d4(void);
static void func_c06465(void);
static void func_c064bb(void);
static void func_c06513(void);
static void func_c065a3(void);
static void showMiniMap(void);
static void func_c06731(void);
static void func_c06755(void);
static void func_c0679c(void);
static void func_c067ec(void);
static void func_c06831(void);
static void loadWorldTilemap(void);
static void loadSubTilemap(void);
static void fillTilemap(void);
static void loadWorldTileset(void);
static void loadSubTileset(void);
static void func_c06b99(void);
static void func_c06bac(void);
static void initBgScrollPos(void);
static void func_c06c4a(void);
static void func_c06c6a(void);
static void func_c06c9d(void);
static void func_c06cd4(void);
static void func_c06d0c(void);
static void func_c06de9(void);
static void horizontalScrolling(void);
static void verticalScrolling(void);
static void modBgTilemap(void);
static void func_c0703e(void);
static void func_c0707d(void);
static void func_c07221(void);
static void func_c0722f(void);
static void func_c07241(void);
static void showDialog(void);
static void getDialogPtr(void);
static void loadDialogText(void);
static void func_c08451(void);
static void func_c08459(void);
static void func_c08466(void);
static void func_c08477(void);
static void func_c08493(void);
static void func_c084af(void);
static void func_c084e9(void);
static void func_c08508(void);
static void func_c0850d(void);
static void func_c08512(void);
static void getSpellName(void);
static void getItemName(void);
static void getGilAmount(void);
static void func_c08b53(void);
static void func_c08ba4(void);
static void func_c08bd3(void);
static void func_c08be4(void);
static void func_c08c2e(void);
static void func_c08c7b(void);
static void func_c08c92(void);
static void func_c08d0e(void);
static void func_c08d3b(void);
static void func_c08e08(void);
static void func_c08e23(void);
static void func_c08ed3(void);
static void loadFontGfx(void);
static void func_c08f54(void);
static void drawYesNoIndicator(void);
static void showYesNoWindow(void);
static void func_c090ad(void);
static void showGPWindow(void);
static void func_c091ed(void);
static void showMapTitle(void);
static void initMapTitle(void);
static void drawMapTitleWindow(void);
static void hideMapTitleWindow(void);
static void func_c09440(void);
static void func_c094a8(void);
static void func_c09618(void);
static void func_c0964c(void);
static void func_c09695(void);
static void func_c09704(void);
static void func_c09772(void);
static void func_c0975f(void);
static void updatePaletteAnim(void);
static void func_c097e2(void);
static void func_c0980d(void);
static void func_c09838(void);
static void func_c09865(void);
static void func_c098e2(void);
static void initPaletteAnim(void);
static void func_c0996d(void);
static void updateMapAnim(void);
static void initMapAnim(void);
static void loadAnimTileGfx(void);
static void func_c09c3d(void);
static void func_c09cac(void);
static void updateTimer(void);
static void speedUpMusicWithTimer(void);
static void execEvent(void);
static void nextEventCmd(void);
static void terminateEvent(void);
static void func_c0a365(void);
static void func_c0a380(void);
static void func_c0a3c9(void);
static void func_c0a40a(void);
static void func_c0a449(void);
static void func_c0a45f(void);
static void eventCmd_bf(void);
static void eventCmd_bf1a(void);
static void eventCmd_bf18(void);
static void func_c0a7be(void);
static void eventCmd_bf19(void);
static void eventCmd_bf15(void);
static void func_c0a933(void);
static void eventCmd_bf14(void);
static void func_c0aa0e(void);
static void eventCmd_bf13(void);
static void eventCmd_bf12(void);
static void func_c0ab8e(void);
static void func_c0abb5(void);
static void eventCmd_bf0f(void);
static void eventCmd_bf10(void);
static void eventCmd_bf07(void);
static void eventCmd_bf08(void);
static void eventCmd_bf09(void);
static void eventCmd_bf0a(void);
static void func_c0ac80(void);
static void func_c0ac8b(void);
static void func_c0acb1(void);
static void func_c0acdd(void);
static void func_c0ad01(void);
static void func_c0ad28(void);
static void func_c0ad54(void);
static void func_c0ad86(void);
static void func_c0ada0(void);
static void func_c0adb7(void);
static void func_c0add6(void);
static void func_c0ae0b(void);
static void func_c0ae32(void);
static void eventCmd_bf00(void);
static void eventCmd_bf01(void);
static void eventCmd_bf16(void);
static void eventCmd_bf02(void);
static void eventCmd_bf11(void);
static void eventCmd_bf05(void);
static void func_c0b240(void);
static void eventCmd_bf04(void);
static void func_c0b2a5(void);
static void func_c0b35c(void);
static void func_c0b371(void);
static void func_c0b3cd(void);
static void eventCmd_bf06(void);
static void func_c0b594(void);
static void eventCmd_bf0b(void);
static void func_c0b5fd(void);
static void eventCmd_bf17(void);
static void eventCmd_bf03(void);
static void func_c0b750(void);
static void func_c0b75e(void);
static void func_c0b791(void);
static void eventCmd_bf0c(void);
static void eventCmd_bf0e(void);
static void eventCmd_bf0d(void);
static void func_c0b854(void);
static void eventCmd_ea(void);
static void eventCmd_eb(void);
static void eventCmd_e9(void);
static void eventCmd_e7(void);
static void eventCmd_e6(void);
static void eventCmd_e4(void);
static void eventCmd_e5(void);
static void eventCmd_dd(void);
static void eventCmd_da(void);
static void func_c0b9f5(void);
static void eventCmd_79(void);
static void eventCmd_db(void);
static void eventCmd_d9(void);
static void changeColorPalette(void);
static void eventCmd_b6(void);
static void eventCmd_ae(void);
static void eventCmd_a6(void);
static void eventCmd_a7(void);
static void eventCmd_7b(void);
static void eventCmd_7f(void);
static void eventCmd_ad(void);
static void calcInnPrice(void);
static void eventCmd_ac(void);
static void eventCmd_c0(void);
static void func_c0bc9f(void);
static void eventCmd_d0(void);
static void eventCmd_70(void);
static void eventCmd_dc(void);
static void eventCmd_7a(void);
static void eventCmd_a1(void);
static void eventCmd_e8(void);
static void eventCmd_bd(void);
static void eventCmd_e2(void);
static void eventBattle(void);
static void eventCmd_b7(void);
static void eventCmd_c6(void);
static void eventCmd_af(void);
static void eventCmd_b0(void);
static void calcGilForEvent(void);
static void eventCmd_aa(void);
static void eventCmd_ab(void);
static void findItemSlot(void);
static void eventCmd_ba(void);
static void eventCmd_bb(void);
static void eventCmd_bc(void);
static void eventCmd_a8(void);
static void eventCmd_a9(void);
static void getPtrToCharData(void);
static void func_c0c19d(void);
static void eventCmd_c2(void);
static void eventCmd_d2(void);
static void eventCmd_c9(void);
static void eventCmd_b4(void);
static void eventCmd_d4(void);
static void eventCmd_b5(void);
static void eventCmd_d5(void);
static void eventCmd_76(void);
static void eventCmd_78(void);
static void eventCmd_77(void);
static void eventCmd_f1(void);
static void eventCmd_f0(void);
static void eventCmd_d6(void);
static void eventCmd_e0(void);
static void eventCmd_e1(void);
static void eventCmd_e3(void);
static void func_c0c43f(void);
static void eventCmd_f4(void);
static void eventCmd_f3(void);
static void eventCmd_7c(void);
static void eventCmd_d8(void);
static void eventCmd_d3(void);
static void removeCurObjFromObjLayout(void);
static void eventCmd_d1(void);
static void eventCmd_d7(void);
static void eventCmd_7d(void);
static void eventCmd_c5(void);
static void eventCmd_b8(void);
static void eventCmd_b9(void);
static void eventCmd_7e(void);
static void eventCmd_c3(void);
static void eventCmd_c4(void);
static void eventCmd_be(void);
static void eventCmd_c1(void);
static void eventCmd_b1(void);
static void func_c0c6de(void);
static void eventCmd_b2(void);
static void eventCmd_b3(void);
static void eventCmd_a0(void);
static void eventCmd_a2(void);
static void eventCmd_a4(void);
static void eventCmd_a3(void);
static void eventCmd_a5(void);
static void clearEventFlag_256_511(void);
static void eventCmd_c8(void);
static void initObjectMovement(void);
static void func_c0c7f9(void);
static void func_c0c932(void);
static void initCameraMovement(void);
static void giveSpell(void);
static void getNPCFlag(void);
static void eventCmd_ca(void);
static void eventCmd_cb(void);
static void setBattleFlag(void);
static void clearBattleFlag(void);
static void getTrasureFlag(void);
static void setTreasureFlag(void);
static void getEventFlag00xx(void);
static void setEventFlag01xx(void);
static void getFlagIndex(void);
static void checkRandomBattlesSub(void);
static void checkRandomBattlesWorld(void);
static void updateRandomForBattles(void);
static void func_c0cc6d(void);
static void battleBlurSub(void);
static void battleBlurWorld(void);
static void battleBlur(void);
static void randomBattle(void);
static void reset(void);

// These adresses are loaded before
// having valued stored there
static uint8_t addr_7e0139 = 0;
static uint8_t addr_7e0af9 = 0;

// Address: _420d
static uint8_t h_memsel;
// Address: _420b
static uint8_t h_mdmaen;
// Address: _420c
static uint8_t h_hdmaen;
// Address: _2100
static uint8_t h_inidisp;
// Address: _4200
static uint8_t h_nmitimen;
static uint8_t addr_7e0134;
static uint8_t addr_7e00bd;
static uint8_t addr_7e00bc;
static uint8_t addr_7e00ce;
static uint8_t addr_7e0057;
static uint8_t addr_7e0058;
static uint8_t addr_7e0059;
static uint8_t addr_7e0b60;
static uint8_t addr_7e0b5f;
static uint8_t addr_7e00b9;
static uint8_t addr_7e0088;
static uint8_t addr_7e0089;

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
    h_inidisp = 143;
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
    // Jump to Subroutine Long InitSound_ext
    initSound();

    // LoaD #$f1 to Accumulator
    const uint8_t CUTSCENE_TITLE = 241;
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
        //  - To be called outside branch
    } else {
        // (restore saved game)

        // Jump to SubRoutine _c0491d
        resetRam_0B00_to_1D00();

        // LoaD $0af9 to A
        // Store A to $0b60
        addr_7e0b60 = addr_0af9;

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
        //  - To be called outside branch
    }

    fieldLoop(void);
}

// Field Main Loop
static void fieldLoop(void) {}

static void fieldNMI(void) {}

static void fieldIRQ(void) {}

// execute trigger script
// +X: trigger script index * 2
static void execTriggerScript(void) {}

// Address: _061a
static void checkTriggers(void) {}

// Address: _073e
static void checkVehicle(void) {}

// Address: _0853
static void func_c00853(void) {}

static void boardChoco(void) {}

static void landChoco(void) {}

static void boardBlkChoco(void) {}

static void boardHiryuu(void) {}

static void landBlkChoco(void) {}

static void landHiryuu(void) {}

static void boardSub(void) {}

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

static void func_c01ae4(void) {}

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

static void loadOverlaySprites(void) {}

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
static void LoadNPCs(void) {}

// Address: 4008
static void greyscalePalette(void) {}

static void func_c0406b(void) {}

// Address: _40d8
static void copyDataToVram(void) {}

static void func_c04107(void) {}

static void func_c041f1(void) {}

static void func_c0420a(void) {}

static void showCutsceneFromField(uint8_t id) {}

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

static void resetRam_0000_to_1D00(void) {}

static void resetRam_0B00_to_1D00(void) {}

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

static void fillVram(void) {}

static void tfrSprites(void) {}

static void tfrPallets(void) {}

static void func_c04d8e(void) {}

// Hex to Dec

static void waitVram(void) {}

static void initInterrupts(void) {}

static void initHardware(void) {}

static void generateRandom(void) {}

static void crystalShatterAnim(void) {}

static void loadMap(void) {}

static void loadMapNoFade(void) {}

static void reloadMap(void) {}

// Address: _548f
static void loadParentMap(void) {}

static void func_c054a7(void) {}

static void func_c054f6(void) {}

static void loadWorldMap(void) {}

static void loadWorldMapPalette(void) {}

static void loadSubMap(void) {}

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

static void func_c08bd3(void) {}

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

static void showMapTitle(void) {}

static void initMapTitle(void) {}

static void drawMapTitleWindow(void) {}

static void hideMapTitleWindow(void) {}

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
static void setEventFlag01xx(void) {}

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