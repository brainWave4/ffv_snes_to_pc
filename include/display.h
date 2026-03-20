#ifndef SNES_DISPLAY
#define SNES_DISPLAY

#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>

typedef struct {
    // TODO: Get Tileset

    Uint16[1024] tilemap;

    Uint8 tilemapCount;

    Uint8 hScroll;

    Uint8 vScroll;
} BgLayer;

BgLayer[4] bgLayers;

// Address: _2100
Uint8 inidisp;

// Address: _2105
Uint8 bgMode;

// Address: _2106
Uint8 mosaic;

// Addresses _2115-2119 are for VRAM,
// which stores tilesets and tilemaps.

// Address: _211A
Uint8 mode7_settings;

// Address: _211B
Uint8 mode7_a;

// Address: _211C
Uint8 mode7_b;

// Address: _211D
Uint8 mode7_c;

// Address: _211E
Uint8 mode7_d;

// Address: _211F
Uint8 mode7_x;

// Address: _2120
Uint8 mode7_y;

// Addresses _2121-2122 are for CGRAM,
// which stores the palette.
SDL_Palette palette;

#endif