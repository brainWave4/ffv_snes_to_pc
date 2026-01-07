//.import _c10003, _c10006

//.import ExecBattle_ext
#include "battle.h"

//.import ExecMenu_ext, _c2a008
#include "menu.h"

//.import ShowCutscene_ext, Decomp_ext

//.import InitSound_ext, ExecSound_ext
#include "sound.h"

void start(void);

void start(void) {
    // SEt Interrpt flag
    // CLear Carry flasg
    // eXchange Carry and Emulation flags
    // Lengthen indexes to 16-bits
    // Shorten Accumulator (A) to 8-bits
    // STore Zero to hMEMSEL
    // STore Zero to hMDMAEN
    // STore Zero to hHDMAEN
    // LoaD #$8f to A
    // Store A to hINIDISP
    // LoaD #0 to A
    // Store A to hNMITIMEN
    // LoaD #0 to A
    // eXchange B and A 8-bit accumulators
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
    // LoaD #$f1 to Accumulator
    // Jump to SubRoutine ShowCutscene
    // Jump to SubRoutine InitHardware
    // Jump to SubRoutine _c0490a
    // LoaD #3 to Accumulator
    // STore $0134 to A
    // Jump to Subroutine Long ExecMenu_ext
    // Jump to SubRoutine _c044e3
    // Jump to SubRoutine InitHardware
    // Jump to SubRoutine InitInterrupts
    // LoaD $0139 to A
    // Branch to [NewGame] if EQual (Zero Flasg is set)

    // (restore saved game)

    // Jump to SubRoutine _c044e3
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
}