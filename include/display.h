#ifndef SNES_DISPLAY
#define SNES_DISPLAY

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

// Addresses _2115-2119 are VRAM
#endif