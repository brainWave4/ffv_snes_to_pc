// Simulates the PPU chip of the SNES.

#include "include/display.h"

#include "<SDL3/SDL.h>"

#define TILESET_WIDTH_1BIT = 128
#define TILESET_WIDTH_2BIT = 256
#define TILESET_WIDTH_4BIT = 512
#define TILESET_WIDTH_8BIT = 1024

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

    for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
        bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
        bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
        bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
    }

    palette = SDL_CreatePalette(PALETTE_SIZE);
}

void updateTilesetFromFilePath(Uint8 i, char[] filepath) {
    FILE *fptr = open(filepath, "rb");
    SDL_UpdateTexture(bgLayers[i].tileset, NULL, &fptr, tilesetWidthsBits[i]);
    fclose(fptr);
}

// When bgMode is set, it also affects
// BG depths
void setBgMode(Uint8 val) {
    for (Uint8 i = 0; i < BGLAYER_COUNTS[bgMode & 7]; i ++) {
        SDL_DestroyTexture(bgLayers[i].high_texture);
        SDL_DestroyTexture(bgLayers[i].low_texture);
        SDL_DestroyTexture(bgLayers[i].tileset);
    }

    bgMode = val;

    switch (bgMode & 7) {
        case 0:
            for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                
                tilesetWidthsBits[i] = TILESET_WIDTH_2BIT;
            }

            layerCount = 12;
            layersTexture = {bgLayers[3].low_texture, bgLayers[2].low_texture, sprite_texture[0],
                    bgLayers[3].high_texture, bgLayers[2].high_texture, sprite_texture[1],
                    bgLayers[1].low_texture, bgLayers[0].low_texture, sprite_texture[2],
                    bgLayers[1].high_texture, bgLayers[0].high_texture, sprite_texture[3]
                };
        case 1:
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            }
            bgLayers[2].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[2].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[2].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            
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
        case 2:
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
                tilesetWidthsBits[i] = TILESET_WIDTH_2BIT;
            }

            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
                };
            tilesetWidthsBits = {TILESET_WIDTH_4BIT, TILESET_WIDTH_4BIT, 0, 0};
        case 3:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            
            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_8BIT, TILESET_WIDTH_4BIT, 0, 0};
        case 4:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            
            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_8BIT, TILESET_WIDTH_2BIT, 0, 0};
        case 5:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            
            layerCount = 8;
            layersTexture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_4BIT, TILESET_WIDTH_2BIT, 0, 0};
        case 6:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            
            layerCount = 6;
            layersTexture = {sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
            tilesetWidthsBits = {TILESET_WIDTH_4BIT, 0, 0, 0};
        case 7:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH_1BIT, 128);
            
            layerCount = 7;
            layersTexture = {sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    sprite_texture[2],
                    sprite_texture[3]
                };
    }
}

void updateWholePalette(Uint16 arr_pal[PALETTE_SIZE]) {
    SDL_Color color[PALETTE_SIZE];

    for (Uint8 i = 0; i < PALETTE_SIZE; i ++) {
        color[i] = {0, 0, 0, 0};
        SDL_GetRGBA(arr_pal[i], *SNES_FORMAT, NULL, &color[i]->r, &color[i]->g, &color[i]->b, &color[i]->a);
    }

    SDL_SetPaletteColors(palette, &color, 0, PALETTE_SIZE);
}

void draw(SDL_Renderer *renderer) {
    for (Uint8 i = 0; i < layerCount; i++) {
        SDL_SetRenderTarget(renderer, layer);

        if (i == 0) SDL_SetRenderDrawColor(renderer, palette->colors[0]->r, palette->colors[0]->g, palette->colors[0]->b, SDL_ALPHAOPAQUE);
        else SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHATRANSPARENT);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderTexture(renderer, layersTexture[i], NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}