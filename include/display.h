#ifndef SNES_DISPLAY
#define SNES_DISPLAY

#include <SDL3/SDL_pixels.h>
#include <stdint.h>

typedef struct {
    // TODO: Get Tileset

    uint16_t[1024] tilemap;

    uint8_t tilemapCount;

    uint8_t hScroll;

    uint8_t vScroll;
} BgLayer;

// Address: _2100
uint8_t inidisp;

// Address: _2105
uint8_t bgMode;

// Address: _2106
uint8_t mosaic;

// Addresses _2115-2119 are for VRAM,
// which stores tilesets and tilemaps.

// Address: _211A
uint8_t mode7_settings;

// Address: _211B
uint8_t mode7_a;

// Address: _211C
uint8_t mode7_b;

// Address: _211D
uint8_t mode7_c;

// Address: _211E
uint8_t mode7_d;

// Address: _211F
uint8_t mode7_x;

// Address: _2120
uint8_t mode7_y;

// Addresses _2121-2122 are for CGRAM,
// which stores the palette.
SDL_Color[256] palette;

#endif