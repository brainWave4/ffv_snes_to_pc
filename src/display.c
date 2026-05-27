// Simulates the PPU chip of the SNES.

#include "include/display.h"

#include "<SDL3/SDL.h>"

#define PALETTE_COUNT_4BIT = 8
#define PALETTE_SIZE_4BIT = 16

// Tileset Width = 8 pixels x 16 tiles x Bit count
#define TILESET_WIDTH_1BIT = 128
#define TILESET_WIDTH_2BIT = 256
#define TILESET_WIDTH_4BIT = 512
#define TILESET_WIDTH_8BIT = 1024

// Tileset has 1024 tiles total
// Since it is 16 tiles in width, it is 64 tiles in height
// Tileset Width = 8 pixels x 64 tiles x Bit count
#define TILESET_HEIGHT_1BIT = 512
#define TILESET_HEIGHT_2BIT = 1024
#define TILESET_HEIGHT_4BIT = 2048
#define TILESET_HEIGHT_8BIT = 4096

static const SDL_PixelFormatDetails *SNES_FORMAT = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ARGB1555);

static const Uint8 BGLAYER_COUNTS[8] = {4, 3, 2, 2, 2, 2, 1, 1};

SDL_Renderer *renderer;

static Uint8 bgMode;

static Uint8 layerCount;
static SDL_Texture *layersTexture[];
static Uint8 tilesetWidthsBits[4];

static SDL_Texture *sprite_texture[4];

void setupDisplay(SDL_Renderer *new_renderer) {
    renderer = new_renderer;

    setBgMode(0);

    palette_8bit = SDL_CreatePalette(PALETTE_SIZE_8BIT);
    for (Uint8 i = 0; i < PALETTE_COUNT_4BIT; i ++) {
        Uint8 start = PALETTE_SIZE_4BIT * i;
        palette_4bit[i] = createSubPalette(palette_8bit, PALETTE_SIZE_4BIT, start);
    }
}

void updateTilesetFromFilePath(Uint8 i, char[] filepath, SDL_Rect customRect = NULL) {
    FILE *fptr = open(filepath, "rb");
    SDL_UpdateTexture(bgLayers[i].tileset, customRect, &fptr, tilesetWidthsBits[i]);
    fclose(fptr);
}

// Before setting bgMode, textures must be destroyed first to change their bit depth
void changeBgMode(Uint8 val) {
    for (Uint8 i = 0; i < BGLAYER_COUNTS[bgMode & 7]; i ++) {
        SDL_DestroyTexture(bgLayers[i].high_texture);
        SDL_DestroyTexture(bgLayers[i].low_texture);
        SDL_DestroyTexture(bgLayers[i].tileset);
    }

    setBgMode(val);
}

// When bgMode is set, it also affects:
//  - BG depths
void setBgMode(Uint8 val) {
    bgMode = val;

    switch (bgMode & 7) {
        case 0:
            for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                
                tilesetWidthsBits[i] = TILESET_WIDTH_2BIT;
            }

            layerCount = 12;
            layersTexture = {bgLayers[3].low_texture, bgLayers[2].low_texture, sprite_texture[0],
                    bgLayers[3].high_texture, bgLayers[2].high_texture, sprite_texture[1],
                    bgLayers[1].low_texture, bgLayers[0].low_texture, sprite_texture[2],
                    bgLayers[1].high_texture, bgLayers[0].high_texture, sprite_texture[3]
                };
            
            break;
        case 1:
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            }
            bgLayers[2].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[2].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[2].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            
            layerCount = 10;
            if (bgMode & 8) layersTexture = {bgLayers[2].low_texture, sprite_texture[0], sprite_texture[1],
                    bgLayers[1].low_texture, bgLayers[0].low_texture, sprite_texture[2],
                    bgLayers[1].high_texture, bgLayers[0].high_texture, sprite_texture[3],
                    bgLayers[2].high_texture
                };
            else layersTexture = {bgLayers[2].low_texture, sprite_texture[0],
                    bgLayers[2].high_texture, sprite_texture[1],
                    bgLayers[1].low_texture, bgLayers[0].low_texture, sprite_texture[2],
                    bgLayers[1].high_texture, bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_4BIT, TILESET_WIDTH_4BIT, TILESET_WIDTH_2BIT, 0};
            
            break;
        case 2:
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
                tilesetWidthsBits[i] = TILESET_WIDTH_2BIT;
            }

            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_4BIT, TILESET_WIDTH_4BIT, 0, 0};
            
            break;
        case 3:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            
            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_8BIT, TILESET_WIDTH_4BIT, 0, 0};
            
            break;
        case 4:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            
            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_8BIT, TILESET_WIDTH_2BIT, 0, 0};
            
            break;
        case 5:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            
            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_4BIT, TILESET_WIDTH_2BIT, 0, 0};
            
            break;
        case 6:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            
            layerCount = 6;
            layersTexture = {sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_4BIT, 0, 0, 0};
            
            break;
        default:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, TILESET_HEIGHT_1BIT);
            
            layerCount = 7;
            layersTexture = {sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    sprite_texture[2],
                    sprite_texture[3]
                };
    }
}

void updateWholePalette(Uint16 arr_pal[PALETTE_SIZE_8BIT]) {
    SDL_Color color[PALETTE_SIZE_8BIT];

    for (Uint8 i = 0; i < PALETTE_SIZE_8BIT; i ++) {
        color[i] = {0, 0, 0, 0};
        SDL_GetRGBA(arr_pal[i], *SNES_FORMAT, NULL, &color[i]->r, &color[i]->g, &color[i]->b, &color[i]->a);
    }

    SDL_SetPaletteColors(palette_8bit, &color, 0, PALETTE_SIZE_8BIT);
}

SDL_Palette createSubPalette(SDL_Palette base, Uint8 size, Uint8 start) {
    SDL_Color *colors[size];

    for (Uint8 i = 0; i < size; i ++) {
        colors[i] = base.colors[start + i];
    }

    return {size, *colors};
}

void draw(SDL_Renderer *renderer) {
    for (Uint8 i = 0; i < layerCount; i++) {
        SDL_SetRenderTarget(renderer, layer);

        if (i == 0) SDL_SetRenderDrawColor(renderer, palette_8bit->colors[0]->r, palette_8bit->colors[0]->g, palette_8bit->colors[0]->b, SDL_ALPHAOPAQUE);
        else SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHATRANSPARENT);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderTexture(renderer, layersTexture[i], NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}