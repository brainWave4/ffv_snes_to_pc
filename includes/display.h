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

    Uint16 tilesetScroll;

    Uint8 baseTilemapScroll;
    Uint16 tilemapScroll;
    bool tileMapIsTwiceX;
    bool tileMapIsTwiceY;
    Uint8 bytesPerWidth;
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

extern Uint8 inidisp;
extern Uint8 mosaic;
extern Uint8 mode7_settings;
extern Uint8 mode7_a;
extern Uint8 mode7_b;
extern Uint8 mode7_c;
extern Uint8 mode7_d;
extern Uint8 mode7_x;
extern Uint8 mode7_y;
extern Uint8 w12sel;
extern Uint8 w34sel;
extern Uint8 wObjSel;
extern Uint8 wh0;
extern Uint8 wh1;
extern Uint8 wh2;
extern Uint8 wh3;
extern Uint8 bgMask;
extern Uint8 objMask;
extern Uint8 enableMain;
extern Uint8 enableSub;
extern Uint8 enableMainWindow;
extern Uint8 enableSubWindow;
extern Uint8 cgWSel;
extern Uint8 colData;
extern Uint8 setIni;

void setupDisplay(SDL_Renderer *new_renderer);

void addToVram(Uint16 dest, char filepath[], Uint16 offset, Uint16 size);

void changeBgMode(Uint8 val);

void setBg1sc(Uint8 val);
void setBg2sc(Uint8 val);
void setBg3sc(Uint8 val);
void setBg4sc(Uint8 val);

void setBg12nba(Uint8 val);
void setBg34nba(Uint8 val);

void updateWholePalette(Uint16 arr_pal[PALETTE_SIZE_8BIT]);
#endif