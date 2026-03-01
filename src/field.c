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
static void execEvent(void);

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

static void execEvent(void) {}