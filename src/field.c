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

void start(void);
static void fieldLoop(void);
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

static uint8_t h_memsel = 0;
static uint8_t h_mdmaen = 0;
static uint8_t h_hdmaen = 0;
static uint8_t h_inidisp = 0;
static uint8_t h_nmitimen = 143;
static uint8_t addr_7e0134 = 3;

void start(void) {
    // SEt Interrpt flag
    // CLear Carry flasg
    // eXchange Carry and Emulation flags
    // Lengthen indexes to 16-bits
    // Shorten Accumulator (A) to 8-bits

    // STore Zero to hMEMSEL
    //  - Used elsewhere?
    // STore Zero to hMDMAEN
    // STore Zero to hHDMAEN
    // LoaD #$8f (143) to A
    // Store A to hINIDISP
    // LoaD #0 to A
    // Store A to hNMITIMEN

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
    //  - Could be set when defined directly.

    // Jump to Subroutine Long ExecMenu_ext
    execMenu();

    // Jump to SubRoutine _c044e3
    func_c044e3();

    // Jump to SubRoutine InitHardware
    initHardware();

    // Jump to SubRoutine InitInterrupts
    initInterrupts();

    // LoaD $0139 to A
    // Branch to [NewGame] if EQual (Zero Flag is set)

    // (restore saved game)

    // Jump to SubRoutine _c0491d
    // LoaD $0af9 to A
    // Store A to $0b60
    // Shift Right A
    // Store A to $0b5f
    // Load #1 to A
    // Store A to $bd (show party sprite)
    // Store A to $bc (senable walking animation)
    // INCrement A
    // Store A to $b9
    // Load $0ad8 to A (x position)
    // Store A to $1088
    // Load $0ad9 to A (y position)
    // Store A to $1089
    // Jump to subroutine LoadMapNoFade
    
    // Jump to FieldLoop

    // [NewGame]
    // Jump to SubRoutine _c048fa
    // Jump to SubRoutine _c048ed
    // Jump to SubRoutine _c048dd
    // Jump to SubRoutine _c04528
    // Jump to SubRoutine _c0450a
    // Load #1 to A
    // Store A to $bd
    // Store A to $bc
    // Load #$0010 to X
    // Store X to $ce
    // Load #1 to A
    // Store $57 to A
    // Load #$81 to A
    // Store A to hNMITIMEN
    // cli
    // Jump to SubRoutine ExecEvent
    // Store Zero to $57
    // Store Zero to $58
    // Store Zero to $59
    
    // JuMP to FieldLoop
}

// Field Main Loop
static void fieldLoop(void) {}

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