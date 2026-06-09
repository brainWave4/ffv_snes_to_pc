// Simulates the PPU chip of the SNES.
#include "display.h"

#include <stdlib.h>

#include <SDL3/SDL.h>

#define PALETTE_COUNT_4BIT 8
#define PALETTE_SIZE_4BIT 16

#define TILE_WIDTH 8
#define TILE_WIDTH_TWICE 16

#define KEY_TILEISTWICE_BG1 0x10
#define KEY_TILEISTWICE_BG2 0x20
#define KEY_TILEISTWICE_BG3 0x40
#define KEY_TILEISTWICE_BG4 0x80

// Tileset Width = 8 pixels x 16 tiles x Bit count
#define TILESET_WIDTH_1BIT 128
#define TILESET_WIDTH_2BIT 256
#define TILESET_WIDTH_4BIT 512
#define TILESET_WIDTH_8BIT 1024

// Tileset has 1024 tiles total
// Since it is 16 tiles in width, it is 64 tiles in height
// Tileset Width = 8 pixels x 64 tiles x Bit count
#define TILESET_HEIGHT_1BIT 512
#define TILESET_HEIGHT_2BIT 1024
#define TILESET_HEIGHT_4BIT 2048
#define TILESET_HEIGHT_8BIT 4096

#define TILEMAP_TILEWIDTH 32

#define BASEGAME_TILEWIDTH 32
#define BASEGAME_TILEHEIGHT 28

static const SDL_PixelFormatDetails *SNES_FORMAT;

static const Uint8 BGLAYER_COUNTS[8] = {4, 3, 2, 2, 2, 2, 1, 1};

SDL_Renderer *renderer;

static Uint8 bgMode;
static Uint8 need_redrawing;

static Uint8 layerCount;
static void (*drawLayers[12])(void);
static Uint8 tilesetWidthsBits[4];

static SDL_Texture *sprite_texture[4];

void setupDisplay(SDL_Renderer *new_renderer) {
    SNES_FORMAT = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ARGB1555);

    renderer = new_renderer;

    for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
        bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR1555, SDL_TEXTUREACCESS_TARGET, BASE_GAME_WIDTH, BASE_GAME_HEIGHT);
        bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR1555, SDL_TEXTUREACCESS_TARGET, BASE_GAME_WIDTH, BASE_GAME_HEIGHT);
        
        bgLayers[i].key_rerendering = 1 << i;

        bgLayers[i].queueHighCounter = 0;

        for (Uint8 j = 0; j < TILEMAP_TILECOUNT; j ++) {
            bgLayers[i].tilemapIsHigh[j] = false;
        }
    }

    setBgMode(0);
    need_redrawing = 0;

    *palette_8bit = SDL_CreatePalette(PALETTE_SIZE_8BIT);
    for (Uint8 i = 0; i < PALETTE_COUNT_4BIT; i ++) {
        Uint8 start = PALETTE_SIZE_4BIT * i;
        *palette_4bit[i] = createSubPalette(palette_8bit, PALETTE_SIZE_4BIT, start);
    }
}

void updateTilesetFromFilePath(Uint8 i, char filepath[], SDL_Rect customRect) {
    FILE *fptr = open(filepath, "rb");
    SDL_UpdateTexture(bgLayers[i].tileset, customRect, &fptr, tilesetWidthsBits[i]);
    fclose(fptr);
}

// Before setting bgMode, textures must be destroyed first to change
// their bit depth and tilemap size
void changeBgMode(Uint8 val) {
    for (Uint8 i = 0; i < BGLAYER_COUNTS[bgMode & 7]; i ++) {
        SDL_DestroyTexture(bgLayers[i].tileset);
        
        for (Uint8 j = 0; j < TILEMAP_TILECOUNT; j++) {
            SDL_DestroyTexture(bgLayers[i]->tilemap[j]);
        }
    }

    setBgMode(val);
}

// When bgMode is set, it also affects:
//  - BG depths
//  - Whether tilemaps are double the size
void setBgMode(Uint8 val) {
    bgMode = val;

    switch (bgMode & 7) {
        case 0:
            Uint8 KEY_TILEISTWICE[TOTAL_BG_COUNT] = {KEY_TILEISTWICE_BG1, KEY_TILEISTWICE_BG2, KEY_TILEISTWICE_BG3, KEY_TILEISTWICE_BG4};
            for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
                bgLayers[i]->tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
                bgLayers[i]->tileIsTwice = bgMode & KEY_TILEISTWICE[i];

                Uint8 tileSize = bgLayers[i]->tileIsTwice ? TILE_WIDTH_TWICE: TILE_WIDTH;
                for (Uint8 j = 0; j < TILEMAP_TILECOUNT; j++) {
                    bgLayers[i]->tilemap[j] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, tileSize, tileSize);
                }
                
                tilesetWidthsBits[i] = TILESET_WIDTH_2BIT;
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
        case 1:
            Uint8 KEY_TILEISTWICE[2] = {KEY_TILEISTWICE_BG1, KEY_TILEISTWICE_BG2};
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
                bgLayers[i].tileIsTwice = bgMode & KEY_TILEISTWICE[i];
            }
            bgLayers[2].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[2].tileIsTwice = bgMode & KEY_TILEISTWICE_BG3;
            
            Uint8 tileSizes[3];
            for (Uint8 i = 0; i < 2; i++) {
                tileSizes[i] = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE : TILE_WIDTH;
            }
            for (Uint8 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0]->tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[0], tileSizes[0]);
                bgLayers[1]->tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[1], tileSizes[1]);
                bgLayers[2]->tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[2], tileSizes[2]);
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
            tilesetWidthsBits[0] = TILESET_WIDTH_4BIT;
            tilesetWidthsBits[1] = TILESET_WIDTH_4BIT;
            tilesetWidthsBits[2] = TILESET_WIDTH_2BIT;
            tilesetWidthsBits[3] = 0;
            
            break;
        case 2:
            Uint8 KEY_TILEISTWICE[2] = {KEY_TILEISTWICE_BG1, KEY_TILEISTWICE_BG2};
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i]->tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
                bgLayers[i].tileIsTwice = bgMode & KEY_TILEISTWICE[i];

                Uint8 tileSize = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE: TILE_WIDTH;
                for (Uint8 j = 0; j < TILEMAP_TILECOUNT; j++) {
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
            tilesetWidthsBits[0] = TILESET_WIDTH_4BIT;
            tilesetWidthsBits[1] = TILESET_WIDTH_4BIT;
            tilesetWidthsBits[2] = 0;
            tilesetWidthsBits[3] = 0;
            
            break;
        case 3:
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileIsTwice = bgMode & KEY_TILEISTWICE_BG1;
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[1].tileIsTwice = bgMode & KEY_TILEISTWICE_BG2;
            
            Uint8 tileSizes[2];
            for (Uint8 i = 0; i < 2; i++) {
                tileSizes[i] = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE : TILE_WIDTH;
            }
            for (Uint8 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[0], tileSizes[0]);
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
            tilesetWidthsBits[0] = TILESET_WIDTH_8BIT;
            tilesetWidthsBits[1] = TILESET_WIDTH_4BIT;
            tilesetWidthsBits[2] = 0;
            tilesetWidthsBits[3] = 0;
            
            break;
        case 4:
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileIsTwice = bgMode & KEY_TILEISTWICE_BG1;
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[1].tileIsTwice = bgMode & KEY_TILEISTWICE_BG2;
            
            Uint8 tileSizes[2];
            for (Uint8 i = 0; i < 2; i++) {
                tileSizes[i] = bgLayers[i].tileIsTwice ? TILE_WIDTH_TWICE : TILE_WIDTH;
            }
            for (Uint8 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, tileSizes[0], tileSizes[0]);
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
            tilesetWidthsBits[0] = TILESET_WIDTH_8BIT;
            tilesetWidthsBits[1] = TILESET_WIDTH_2BIT;
            tilesetWidthsBits[2] = 0;
            tilesetWidthsBits[3] = 0;
            
            break;
        case 5:
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileIsTwice = true;
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[1].tileIsTwice = true;
                
            for (Uint8 i = 0; i < TILEMAP_TILECOUNT; i++) {
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
            tilesetWidthsBits[0] = TILESET_WIDTH_4BIT;
            tilesetWidthsBits[1] = TILESET_WIDTH_2BIT;
            tilesetWidthsBits[2] = 0;
            tilesetWidthsBits[3] = 0;
            
            break;
        case 6:
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileIsTwice = true;
                
            for (Uint8 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILE_WIDTH_TWICE, TILE_WIDTH_TWICE);
            }
            
            layerCount = 6;
            drawLayers[0] = drawSprites0;
            drawLayers[1] = drawBg1Low;
            drawLayers[2] = drawSprites1;
            drawLayers[3] = drawSprites2;
            drawLayers[4] = drawBg1High;
            drawLayers[5] = drawSprites3;
            tilesetWidthsBits[0] = TILESET_WIDTH_4BIT;
            tilesetWidthsBits[1] = 0;
            tilesetWidthsBits[2] = 0;
            tilesetWidthsBits[3] = 0;
            
            break;
        default:
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileIsTwice = false;
                
            for (Uint8 i = 0; i < TILEMAP_TILECOUNT; i++) {
                bgLayers[0].tilemap[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILE_WIDTH, TILE_WIDTH);
            }
            
            layerCount = 7;
            drawLayers[0] = drawSprites0;
            drawLayers[1] = drawBg1Low;
            drawLayers[2] = drawSprites1;
            drawLayers[3] = drawSprites2;
            drawLayers[4] = drawSprites3;
            tilesetWidthsBits[0] = TILESET_WIDTH_8BIT;
            tilesetWidthsBits[1] = TILESET_WIDTH_8BIT;
            tilesetWidthsBits[2] = 0;
            tilesetWidthsBits[3] = 0;
    }
}

void updateWholePalette(Uint16 arr_pal[PALETTE_SIZE_8BIT]) {
    const SDL_Color *color[PALETTE_SIZE_8BIT];

    for (Uint8 i = 0; i < PALETTE_SIZE_8BIT; i ++) {
        *color[i] = {0, 0, 0, 0};
        SDL_GetRGBA(arr_pal[i], SNES_FORMAT, NULL, color[i]->r, color[i]->g, color[i]->b, color[i]->a);
    }

    SDL_SetPaletteColors(&palette_8bit, &color, 0, PALETTE_SIZE_8BIT);
}

SDL_Palette createSubPalette(SDL_Palette *base, Uint8 size, Uint8 start) {
    SDL_Color *colors[size];

    for (Uint8 i = 0; i < size; i ++) {
        colors[i] = base->colors[start + i];
    }

    return {size, *colors};
}

void drawLayerLow(BgLayer *layer) {
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

void drawBg1Low() {
    drawLayerLow(bgLayers[0]);
}

void drawBg2Low() {
    drawLayerLow(bgLayers[1]);
}

void drawBg3Low() {
    drawLayerLow(bgLayers[2]);
}

void drawBg4Low() {
    drawLayerLow(bgLayers[3]);
}

void drawLayerHigh(BgLayer *layer) {
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

void drawBg1High() {
    drawLayerHigh(bgLayers[0]);
}

void drawBg2High() {
    drawLayerHigh(bgLayers[1]);
}

void drawBg3High() {
    drawLayerHigh(bgLayers[2]);
}

void drawBg4High() {
    drawLayerHigh(bgLayers[3]);
}

void drawSprites0() {}

void drawSprites1() {}

void drawSprites2() {}

void drawSprites3() {}

void draw(SDL_Renderer *renderer) {
    if (need_redrawing) {
        for (Uint8 i = 0; i < layerCount; i++) {
            if (i == 0) SDL_SetRenderDrawColor(renderer, palette_8bit.colors[0].r, palette_8bit.colors[0].g, palette_8bit.colors[0].b, SDL_ALPHA_OPAQUE);
            drawLayers[i]();
            if (i == 0) SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        }

        SDL_RenderPresent(renderer);

        need_redrawing = 0;
    }
}