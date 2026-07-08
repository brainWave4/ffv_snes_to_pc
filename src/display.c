// Simulates the PPU chip of the SNES.
#include "display.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#define PALETTE_COUNT 8
#define PALETTE_SIZE_2BIT 4
#define PALETTE_SIZE_4BIT 16

#define TILE_WIDTH 8
#define TILE_WIDTH_TWICE 16

#define TILE_WIDTH_BYTES_1BIT 1
#define TILE_WIDTH_BYTES_2BIT 2
#define TILE_WIDTH_BYTES_4BIT 4
#define TILE_WIDTH_BYTES_8BIT 8

#define KEY_TILEISTWICE_BG1 0x10
#define KEY_TILEISTWICE_BG2 0x20
#define KEY_TILEISTWICE_BG3 0x40
#define KEY_TILEISTWICE_BG4 0x80

#define TILEMAP_TILEWIDTH 32

#define BASEGAME_TILEWIDTH 32
#define BASEGAME_TILEHEIGHT 28

static const SDL_PixelFormatDetails *SNES_FORMAT;

static const Uint8 BGLAYER_COUNTS[8] = {4, 3, 2, 2, 2, 2, 1, 1};

SDL_Renderer *renderer;

static BgLayer bgLayers[TOTAL_BG_COUNT];

// Address: _2100
Uint8 inidisp;

// Address: _2101-2104
// Concerns Object Sprites

// Address: _2105 is bgMode
// Covers:
//  - Char size for each Bg Layer
//  - Bg Layer 3 High's placement
//  - Bg Mode
static Uint8 bgMode;

// Address: _2106
Uint8 mosaic;

// Addresses _2107-2114 stores data
// for Background Layers
static Uint8 bg12nba = 0;
static Uint8 bg34nba = 0;

// Addresses _2115-2119 are for VRAM,
// which stores tilesets and tilemaps.
static Uint8 vram[65536] = {0};

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
static SDL_Palette palette_2bit[TOTAL_BG_COUNT][PALETTE_COUNT];
static SDL_Palette palette_4bit[PALETTE_COUNT];
static SDL_Palette *palette_8bit;

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

static Uint8 need_redrawing;

static Uint8 layerCount;
static void (*drawLayers[12])(void);

static SDL_Texture *sprite_texture[4];

static void updateTilemap(Uint8 bgLayerI, Uint8 startI, Uint8 size);

static void setBgMode(Uint8 val);

static void setBaseTilemapScroll(Uint8 bgI, Uint8 val);
static void setFromBgABnba(Uint8 i, Uint8 val);

static SDL_Palette createSubPalette(SDL_Palette base, Uint8 size, Uint8 start);

static void drawLayerLow(BgLayer *layer);
static void drawBg1Low();
static void drawBg2Low();
static void drawBg3Low();
static void drawBg4Low();
static void drawLayerHigh(BgLayer *layer);
static void drawBg1High();
static void drawBg2High();
static void drawBg3High();
static void drawBg4High();
static void drawSprites0();
static void drawSprites1();
static void drawSprites2();
static void drawSprites3();
static void draw(SDL_Renderer *renderer);

void setupDisplay(SDL_Renderer *new_renderer) {
    SNES_FORMAT = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ARGB1555);

    renderer = new_renderer;

    for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
        bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR1555, SDL_TEXTUREACCESS_TARGET, BASE_GAME_WIDTH, BASE_GAME_HEIGHT);
        bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR1555, SDL_TEXTUREACCESS_TARGET, BASE_GAME_WIDTH, BASE_GAME_HEIGHT);
        
        bgLayers[i].tilesetScroll = 0;

        bgLayers[i].key_rerendering = 1 << i;

        bgLayers[i].queueHighCounter = 0;

        for (Uint16 j = 0; j < TILEMAP_TILECOUNT; j ++) {
            bgLayers[i].tilemapIsHigh[j] = false;
        }
    }

    setBgMode(0);
    need_redrawing = 0;

    palette_8bit = SDL_CreatePalette(PALETTE_SIZE_8BIT);
    for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
        for (Uint8 j = 0; j < PALETTE_COUNT; j ++) {
            Uint8 start = PALETTE_SIZE_2BIT * j + PALETTE_SIZE_2BIT * PALETTE_COUNT * i;
            palette_2bit[i][j] = createSubPalette(*palette_8bit, PALETTE_SIZE_2BIT, start);
        }
    }
    for (Uint8 i = 0; i < PALETTE_COUNT; i ++) {
        Uint8 start = PALETTE_SIZE_4BIT * i;
        palette_4bit[i] = createSubPalette(*palette_8bit, PALETTE_SIZE_4BIT, start);
    }
}

static void updateTilemap(Uint8 bgLayerI, Uint8 startI, Uint8 size) {
    for (Uint8 i = startI; i < size; i += 2) {
        BgLayer *bgLayer = &bgLayers[bgLayerI];

        Uint8 *ptrMapByte = &(vram + bgLayer->tilemapScroll);
        Uint8 *ptrMapByte1 = ptrMapByte + 1;

        Uint8 *ptrSet = &vram;
        ptrSet += bgLayer->tilesetScroll;
        ptrSet += *ptrMapByte;
        ptrSet += (*ptrMapByte1 & 3) * 0x100;

        Uint8 j = i / 2;

        SDL_UpdateTexture(bgLayer->tilemap[j], NULL, *ptrSet, bgLayer->bytesPerWidth);

        Uint8 palI = *ptrMapByte1 >> 2;
        palI &= 7;
        SDL_SetTexturePalette(bgLayer->tilemap[j], &palette_4bit[palI]);

        if (*ptrMapByte1 & 0x20) bgLayer->tilemapIsHigh[j] = true;

        SDL_FlipMode flip = SDL_FLIP_NONE;
        if (*ptrMapByte1 & 0x40) flip |= SDL_FLIP_HORIZONTAL;
        if (*ptrMapByte1 & 0x80) flip |= SDL_FLIP_VERTICAL;
        if (flip) SDL_RenderTextureRotated(*renderer, &bgLayers[bgLayerI], NULL, NULL, 0, NULL, flip);
    }

    need_redrawing |= bgLayer->key_rerendering;
}

void addToVram(Uint16 dest, char filepath[], Uint16 offset, Uint16 size) {
    FILE *fptr = fopen(filepath, "rb");

    if (offset) fseek(fptr, offset, SEEK_SET);

    fread(&(vram + dest), 1, size, fptr);
    fclose(fptr);

    if (size <= 0x800) {
        for (Uint8 = 0; i < TOTAL_BG_COUNT; i ++) {
            if (dest == bgLayers[i].tilemapScroll) updateTilemap(i, 0, size);
            else if (dest < bgLayers[i].tilemapScroll && dest + size >= bgLayers[i].tilemapScroll) {
                Uint8 startI = bgLayers[i].tilemapScroll - dest;
                updateTilemap(i, startI, size);
            } else {
                Uint16 tilemapScrollEnd = bgLayers[i].tilemapScroll + 0x100;
                if (dest < tilemapScrollEnd) {
                    if (dest + size > tilemapScrollEnd) {
                        Uint8 newDiff = tilemapScrollEnd - dest;
                        updateTilemap(i, 0, newDiff);
                    }
                    else updateTilemap(i, 0, size);
                }
            }
        }
    }
}

// Before setting bgMode, textures must be destroyed first to change
// their bit depth and tilemap size
void changeBgMode(Uint8 val) {
    for (Uint8 i = 0; i < BGLAYER_COUNTS[bgMode & 7]; i ++) {
        for (Uint16 j = 0; j < TILEMAP_TILECOUNT; j++) {
            SDL_DestroyTexture(bgLayers[i].tilemap[j]);
        }
    }

    setBgMode(val);
}

// When bgMode is set, it also affects:
//  - BG depths
//  - Whether tilemaps are double the size
static void setBgMode(Uint8 val) {
    bgMode = val;

    switch (bgMode & 7) {
        case 0: {
            Uint8 KEY_TILEISTWICE[TOTAL_BG_COUNT] = {KEY_TILEISTWICE_BG1, KEY_TILEISTWICE_BG2, KEY_TILEISTWICE_BG3, KEY_TILEISTWICE_BG4};
            for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
                bgLayers[i].tileIsTwice = bgMode & KEY_TILEISTWICE[i];

                bgLayers[i].bytesPerWidth = TILE_WIDTH_BYTES_2BIT;

                Uint8 tileSize = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE: TILE_WIDTH;
                for (Uint16 j = 0; j < TILEMAP_TILECOUNT; j++) {
                    bgLayers[i].tilemap[j] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, tileSize, tileSize);
                }
            }

            layerCount = 12;
            drawLayers[0] = drawBg4Low;
            drawLayers[1] = drawBg3Low;
            drawLayers[2] = drawSprites0;
            drawLayers[3] = drawBg4High;
            drawLayers[4] = drawBg3High;
            drawLayers[5] = drawSprites1;
            drawLayers[6] = drawBg2Low;
            drawLayers[7] = drawBg1Low;
            drawLayers[8] = drawSprites2;
            drawLayers[9] = drawBg2High;
            drawLayers[10] = drawBg1High;
            drawLayers[11] = drawSprites3;
            
            break;
        }
        case 1: {
            Uint8 KEY_TILEISTWICE[2] = {KEY_TILEISTWICE_BG1, KEY_TILEISTWICE_BG2};
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].tileIsTwice = bgMode & KEY_TILEISTWICE[i];
                bgLayers[i].bytesPerWidth = TILE_WIDTH_BYTES_4BIT;
            }
            bgLayers[2].tileIsTwice = bgMode & KEY_TILEISTWICE_BG3;
            bgLayers[2].bytesPerWidth = TILE_WIDTH_BYTES_2BIT;
            
            Uint8 tileSizes[3];
            for (Uint8 i = 0; i < 2; i++) {
                tileSizes[i] = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE : TILE_WIDTH;
            }
            for (Uint16 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[0], tileSizes[0]);
                bgLayers[1].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[1], tileSizes[1]);
                bgLayers[2].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[2], tileSizes[2]);
            }

            layerCount = 10;
            drawLayers[0] = drawBg3Low;
            drawLayers[1] = drawSprites0;
            if (bgMode & 8) {
                drawLayers[2] = drawSprites1;
                drawLayers[3] = drawBg2Low;
                drawLayers[4] = drawBg1Low;
                drawLayers[5] = drawSprites2;
                drawLayers[6] = drawBg2High;
                drawLayers[7] = drawBg1High;
                drawLayers[8] = drawSprites3;
                drawLayers[9] = drawBg3High;
            } else {
                drawLayers[2] = drawBg3High;
                drawLayers[3] = drawSprites1;
                drawLayers[4] = drawBg2Low;
                drawLayers[5] = drawBg1Low;
                drawLayers[6] = drawSprites2;
                drawLayers[7] = drawBg2High;
                drawLayers[8] = drawBg1High;
                drawLayers[9] = drawSprites3;
            }
            
            break;
        }
        case 2: {
            Uint8 KEY_TILEISTWICE[2] = {KEY_TILEISTWICE_BG1, KEY_TILEISTWICE_BG2};
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].tileIsTwice = bgMode & KEY_TILEISTWICE[i];
                bgLayers[i].bytesPerWidth = TILE_WIDTH_BYTES_4BIT;

                Uint8 tileSize = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE: TILE_WIDTH;
                for (Uint16 j = 0; j < TILEMAP_TILECOUNT; j++) {
                    bgLayers[i].tilemap[j] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, tileSize, tileSize);
                }
            }

            layerCount = 8;
            drawLayers[0] = drawBg2Low;
            drawLayers[1] = drawSprites0;
            drawLayers[2] = drawBg1Low;
            drawLayers[3] = drawSprites1;
            drawLayers[4] = drawBg2High;
            drawLayers[5] = drawSprites2;
            drawLayers[6] = drawBg1High;
            drawLayers[7] = drawSprites3;
            
            break;
        }
        case 3: {
            bgLayers[0].tileIsTwice = bgMode & KEY_TILEISTWICE_BG1;
            bgLayers[0].bytesPerWidth = TILE_WIDTH_BYTES_8BIT;
            bgLayers[1].tileIsTwice = bgMode & KEY_TILEISTWICE_BG2;
            bgLayers[1].bytesPerWidth = TILE_WIDTH_BYTES_4BIT;
            
            Uint8 tileSizes[2];
            for (Uint8 i = 0; i < 2; i++) {
                tileSizes[i] = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE : TILE_WIDTH;
            }
            for (Uint16 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8, SDL_TEXTUREACCESS_STREAMING, tileSizes[0], tileSizes[0]);
                bgLayers[1].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[1], tileSizes[1]);
            }

            layerCount = 8;
            drawLayers[0] = drawBg2Low;
            drawLayers[1] = drawSprites0;
            drawLayers[2] = drawBg1Low;
            drawLayers[3] = drawSprites1;
            drawLayers[4] = drawBg2High;
            drawLayers[5] = drawSprites2;
            drawLayers[6] = drawBg1High;
            drawLayers[7] = drawSprites3;
            
            break;
        }
        case 4: {
            bgLayers[0].tileIsTwice = bgMode & KEY_TILEISTWICE_BG1;
            bgLayers[0].bytesPerWidth = TILE_WIDTH_BYTES_8BIT;
            bgLayers[1].tileIsTwice = bgMode & KEY_TILEISTWICE_BG2;
            bgLayers[1].bytesPerWidth = TILE_WIDTH_BYTES_2BIT;
            
            Uint8 tileSizes[2];
            for (Uint8 i = 0; i < 2; i++) {
                tileSizes[i] = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE : TILE_WIDTH;
            }
            for (Uint16 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8, SDL_TEXTUREACCESS_STREAMING, tileSizes[0], tileSizes[0]);
                bgLayers[1].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[1], tileSizes[1]);
            }
            
            layerCount = 8;
            drawLayers[0] = drawBg2Low;
            drawLayers[1] = drawSprites0;
            drawLayers[2] = drawBg1Low;
            drawLayers[3] = drawSprites1;
            drawLayers[4] = drawBg2High;
            drawLayers[5] = drawSprites2;
            drawLayers[6] = drawBg1High;
            drawLayers[7] = drawSprites3;
            
            break;
        }
        case 5: {
            bgLayers[0].tileIsTwice = true;
            bgLayers[0].bytesPerWidth = TILE_WIDTH_BYTES_4BIT;
            bgLayers[1].tileIsTwice = true;
            bgLayers[1].bytesPerWidth = TILE_WIDTH_BYTES_2BIT;
                
            for (Uint16 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILE_WIDTH_TWICE, TILE_WIDTH_TWICE);
                bgLayers[1].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILE_WIDTH_TWICE, TILE_WIDTH_TWICE);
            }

            layerCount = 8;
            drawLayers[0] = drawBg2Low;
            drawLayers[1] = drawSprites0;
            drawLayers[2] = drawBg1Low;
            drawLayers[3] = drawSprites1;
            drawLayers[4] = drawBg2High;
            drawLayers[5] = drawSprites2;
            drawLayers[6] = drawBg1High;
            drawLayers[7] = drawSprites3;
            
            break;
        }
        case 6: {
            bgLayers[0].tileIsTwice = true;
            bgLayers[0].bytesPerWidth = TILE_WIDTH_BYTES_4BIT;
                
            for (Uint16 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILE_WIDTH_TWICE, TILE_WIDTH_TWICE);
            }
            
            layerCount = 6;
            drawLayers[0] = drawSprites0;
            drawLayers[1] = drawBg1Low;
            drawLayers[2] = drawSprites1;
            drawLayers[3] = drawSprites2;
            drawLayers[4] = drawBg1High;
            drawLayers[5] = drawSprites3;
            
            break;
        }
        default: {
            bgLayers[0].tileIsTwice = false;
            bgLayers[0].bytesPerWidth = TILE_WIDTH_BYTES_8BIT;
                
            for (Uint16 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8, SDL_TEXTUREACCESS_STREAMING, TILE_WIDTH, TILE_WIDTH);
            }
            
            layerCount = 7;
            drawLayers[0] = drawSprites0;
            drawLayers[1] = drawBg1Low;
            drawLayers[2] = drawSprites1;
            drawLayers[3] = drawSprites2;
            drawLayers[4] = drawSprites3;
        }
    }
}

static void setBaseTilemapScroll(Uint8 bgI, Uint8 val) {
    bgLayers[bgI].baseTilemapScroll = val;

    bgLayers[bgI].tilemapScroll = val & 0xFC;
    bgLayers[bgI].tilemapScroll <<= 8;

    bgLayers[bgI].tileMapIsTwiceX = val & 1;
    bgLayers[bgI].tileMapIsTwiceY = val & 2;
}

void setBg1sc(Uint8 val) {
    setBaseTilemapScroll(0, val);
}

void setBg2sc(Uint8 val) {
    setBaseTilemapScroll(1, val);
}

void setBg3sc(Uint8 val) {
    setBaseTilemapScroll(2, val);
}

void setBg4sc(Uint8 val) {
    setBaseTilemapScroll(3, val);
}

static void setFromBgABnba(Uint8 i, Uint8 val) {
    bgLayers[i].tilesetScroll = val % 0x100;
    bgLayers[i].tilesetScroll <<= 12;

    bgLayers[i + 1].tilesetScroll = val & 0xFF00;
    bgLayers[i + 1].tilesetScroll <<= 4;
}

void setBg12nba(Uint8 val) {
    bg12nba = val;
    setFromBgABnba(0, val);
}

void setBg34nba(Uint8 val) {
    bg34nba = val;
    setFromBgABnba(2, val);
}

void updateWholePalette(Uint16 arr_pal[PALETTE_SIZE_8BIT]) {
    SDL_Color color[PALETTE_SIZE_8BIT] = {0, 0, 0, 0};

    for (Uint8 i = 0; i < PALETTE_SIZE_8BIT; i ++) {
        SDL_GetRGBA(arr_pal[i], SNES_FORMAT, NULL, &color[i].r, &color[i].g, &color[i].b, &color[i].a);
    }

    SDL_SetPaletteColors(palette_8bit, &color[0], 0, PALETTE_SIZE_8BIT);
}

static SDL_Palette createSubPalette(SDL_Palette base, Uint8 size, Uint8 start) {
    SDL_Palette new_palette;
    
    new_palette.ncolors = size;
    new_palette.colors = (base.colors + start);

    return new_palette;
}

static void drawLayerLow(BgLayer *layer) {
    SDL_SetRenderTarget(renderer, layer->low_texture);
    SDL_RenderClear(renderer);

    if (need_redrawing & layer->key_rerendering) {
        Uint8 tileWidth = layer->tileIsTwice ? TILE_WIDTH_TWICE : TILE_WIDTH;

        Uint8 startI = layer->hScroll / tileWidth;
        Sint16 x = layer->hScroll % tileWidth;
        Uint8 gameWidth = BASEGAME_TILEWIDTH;
        if (x) {
            x -= tileWidth;
            gameWidth ++;
        }
        
        Uint8 startJ = layer->vScroll / tileWidth;
        Sint16 startY = layer->vScroll % tileWidth;
        Uint8 gameHeight = BASEGAME_TILEHEIGHT;
        if (startY) {
            startY -= tileWidth;
            gameHeight ++;
        }
        for (Uint8 i = startI; i < gameWidth; i ++) {
            Uint8 loopI = i;
            if (loopI >= TILEMAP_TILEWIDTH) loopI -= TILEMAP_TILEWIDTH;
            Uint8 tileI = loopI * TILEMAP_TILEWIDTH;
            
            Sint16 y = startY;
            for (Uint8 j = startJ; j < gameHeight; j ++) {
                Uint8 loopJ = j;
                if (loopJ >= TILEMAP_TILEWIDTH) loopJ -= TILEMAP_TILEWIDTH;

                Uint8 tileJ = tileI + loopJ;
                SDL_FRect dest = {x, y, tileWidth, tileWidth};

                if (layer->tilemapIsHigh[tileJ]) {
                    layer->queueHighrect[layer->queueHighCounter] = &dest;
                    layer->queueHighmap[layer->queueHighCounter] = layer->tilemap[tileJ];
                    layer->queueHighCounter ++;
                }
                else {
                    SDL_RenderTexture(renderer, layer->tilemap[tileJ], NULL, &dest);
                }

                y += tileWidth;
            }

            x += tileWidth;
        }
    }
    
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, layer->low_texture, NULL, NULL);
}

static void drawBg1Low() {
    drawLayerLow(&bgLayers[0]);
}

static void drawBg2Low() {
    drawLayerLow(&bgLayers[1]);
}

static void drawBg3Low() {
    drawLayerLow(&bgLayers[2]);
}

static void drawBg4Low() {
    drawLayerLow(&bgLayers[3]);
}

static void drawLayerHigh(BgLayer *layer) {
    SDL_SetRenderTarget(renderer, layer->high_texture);
    SDL_RenderClear(renderer);

    if (need_redrawing & layer->key_rerendering) {
        while(layer->queueHighCounter > 0) {
            SDL_RenderTexture(renderer, layer->queueHighmap[layer->queueHighCounter], NULL, layer->queueHighrect[layer->queueHighCounter]);
            layer->queueHighmap[layer->queueHighCounter] = NULL;
            
            free(layer->queueHighrect[layer->queueHighCounter]);
            layer->queueHighrect[layer->queueHighCounter] = NULL;

            layer->queueHighCounter --;
        }
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, layer->high_texture, NULL, NULL);
}

static void drawBg1High() {
    drawLayerHigh(&bgLayers[0]);
}

static void drawBg2High() {
    drawLayerHigh(&bgLayers[1]);
}

static void drawBg3High() {
    drawLayerHigh(&bgLayers[2]);
}

static void drawBg4High() {
    drawLayerHigh(&bgLayers[3]);
}

static void drawSprites0() {}

static void drawSprites1() {}

static void drawSprites2() {}

static void drawSprites3() {}

static void draw(SDL_Renderer *renderer) {
    if (need_redrawing) {
        for (Uint8 i = 0; i < layerCount; i++) {
            if (i == 0) SDL_SetRenderDrawColor(renderer, palette_8bit->colors[0].r, palette_8bit->colors[0].g, palette_8bit->colors[0].b, SDL_ALPHA_OPAQUE);
            drawLayers[i]();
            if (i == 0) SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        }

        SDL_RenderPresent(renderer);

        need_redrawing = 0;
    }
}