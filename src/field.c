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
static void showCutsceneFromField(uint8_t id);
static void func_c044e3(void);
static void func_c0450a(void);
static void func_c04528(void);
static void func_c048dd(void);
static void func_c048ed(void);
static void func_c048fa(void);
static void func_c0490a(void);
static void func_c0491d(void);
static void loadMapNoFade(void);
static void initInterrupts(void);
static void initHardware(void);
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
    func_c0490a();

    // LoaD #3 to Accumulator
    // STore A to $0134
    addr_7e0134 = 3;

    // Jump to Subroutine Long ExecMenu_ext
    execMenu();

    // Jump to SubRoutine _c044e3
    func_c044e3();

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
        func_c048fa();
        // Jump to SubRoutine _c048ed
        func_c048ed();
        // Jump to SubRoutine _c048dd
        func_c048dd();
        // Jump to SubRoutine _c04528
        func_c04528();
        // Jump to SubRoutine _c0450a
        func_c0450a();
        
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
        func_c0491d();

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

static void showCutsceneFromField(uint8_t id) {}

static void func_c044e3(void) {}

static void func_c0450a(void) {}

static void func_c04528(void) {}

static void func_c048dd(void) {}

static void func_c048ed(void) {}

static void func_c048fa(void) {}

static void func_c0490a(void) {}

static void func_c0491d(void) {}

static void loadMapNoFade(void) {}

static void initInterrupts(void) {}

static void initHardware(void) {}

static void execEvent(void) {}