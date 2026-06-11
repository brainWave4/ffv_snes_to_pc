#ifndef SNES_DISPLAY
#define SNES_DISPLAY

#include <stdbool.h>
#include <SDL3/SDL.h>

#define BASE_GAME_WIDTH 256
#define BASE_GAME_HEIGHT 224

#define BASEGAME_TILESTOTAL 957

#define TILESET_WIDTH 128

#define TILEMAP_TILECOUNT 1024

#define TOTAL_BG_COUNT 4
#define PALETTE_SIZE_8BIT 256

typedef struct {
    SDL_Texture *high_texture, *low_texture;

    SDL_Texture *tileset;

    SDL_Texture *tilemap[TILEMAP_TILECOUNT];

    SDL_Texture *queueHighmap[BASEGAME_TILESTOTAL];
    SDL_FRect *queueHighrect[BASEGAME_TILESTOTAL];

    Uint8 hScroll;
    Uint8 vScroll;

    Uint8 key_rerendering;

    Uint8 queueHighCounter;

    bool tilemapIsHigh[TILEMAP_TILECOUNT];

    bool tileIsTwice;
} BgLayer;

void setupDisplay(SDL_Renderer *new_renderer);

void updateTilesetFromFilePath(Uint8 i, char filepath[], SDL_Rect *customRect);

void changeBgMode(Uint8 val);

void updateWholePalette(Uint16 arr_pal[PALETTE_SIZE_8BIT]);
#endif