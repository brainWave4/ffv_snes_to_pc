#ifndef SNES_DISPLAY
#define SNES_DISPLAY

#include <stdbool.h>
#include <SDL3/SDL.h>

#define BASE_GAME_WIDTH 256
#define BASE_GAME_HEIGHT 224

#define BASEGAME_TILESTOTAL 957

#define TILEMAP_TILECOUNT 1024

#define TOTAL_BG_COUNT 4
#define PALETTE_SIZE_8BIT 256

typedef struct {
    SDL_Texture *high_texture, *low_texture;

    SDL_Texture *tileset;

    SDL_Texture tilemap[TILEMAP_TILECOUNT];

    SDL_Texture queueHighmap[BASEGAME_TILESTOTAL];
    SDL_FRect queueHighrect[BASEGAME_TILESTOTAL];

    Uint8 hScroll;
    Uint8 vScroll;

    Uint8 key_rerendering;

    Uint8 queueHighCounter;

    bool tilemapIsHigh[TILEMAP_TILECOUNT];

    bool tileIsTwice;
} BgLayer;

BgLayer[TOTAL_BG_COUNT] bgLayers;

// Address: _2100
Uint8 inidisp;

// Address: _2101-2104
// Concerns Object Sprites

// Address: _2105 is bgMode, which covers:
//  - Char size for each Bg Layer
//  - Bg Layer 3 High's placement
//  - Bg Mode
// Is made private in favor of setting it
//      via function, as it affects other
//      properties in the process.

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
SDL_Palette palette_4bit[8];
SDL_Palette palette_8bit;

// Address: _2123
Uint8 w12sel;

// Address: _2124
Uint8 w34sel;

// Address: _2125
Uint8 wObjSel;

// Address: _2126
// Window 1 left position
Uint8 wh0;

// Address: _2127
// Window 1 right position
Uint8 wh1;

// Address: _2128
// Window 2 left position
Uint8 wh2;

// Address: _2129
// Window 2 right position
Uint8 wh3;

// Address: _212A
Uint8 bgMask;

// Address: _212B
Uint8 objMask;

// Address: _212C
Uint8 enableMain;

// Address: _212D
Uint8 enableSub;

// Address: _212E
Uint8 enableMainWindow;

// Address: _212F
Uint8 enableSubWindow;

// Address: _2130
Uint8 cgWSel;

// Address: _2132
Uint8 colData;

// Address: _2133
Uint8 setIni;

void updateTilesetFromFilePath(Uint8 i, char[] filepath);

void changeBgMode(Uint8 val);

void updateWholePalette(Uint16 arr_pal[PALETTE_SIZE_8BIT]);
#endif