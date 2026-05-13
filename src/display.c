// Simulates the PPU chip of the SNES.

#include "include/display.h"

#include "<SDL3/SDL.h>"

#define TILESET_WIDTH = 128

static const SDL_PixelFormatDetails *SNES_FORMAT = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ARGB1555);

static const Uint8 BGLAYER_COUNTS[8] = {4, 3, 2, 2, 2, 2, 1, 1};

SDL_Renderer *renderer;

static Uint8 layer_count;
static SDL_Texture *layers_texture[];

static SDL_Texture *sprite_texture[4];

void setupDisplay(SDL_Renderer *new_renderer) {
    renderer = new_renderer;

    for (Uint8 i = 0; i < TOTAL_BG_COUNT; i ++) {
        bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
        bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
        bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
    }

    palette = SDL_CreatePalette(PALETTE_SIZE);
}

void updateTilesetFromFilePath(Uint8 i, char[] filepath) {
    FILE *fptr = open(filepath, "rb");
    SDL_UpdateTexture(bgLayers[0].tileset, NULL, &fptr, 384);
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
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            }

            layer_count = 12;
            layers_texture = {bgLayers[3].low_texture, bgLayers[2].low_texture, sprite_texture[0],
                    bgLayers[3].high_texture, bgLayers[2].high_texture, sprite_texture[1],
                    bgLayers[1].low_texture, bgLayers[0].low_texture, sprite_texture[2],
                    bgLayers[1].high_texture, bgLayers[0].high_texture, sprite_texture[3]
                };
        case 1:
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            }
            bgLayers[2].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[2].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[2].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            
            layer_count = 10;
            if (bgMode & 8) layers_texture = {bgLayers[2].low_texture, sprite_texture[0], sprite_texture[1],
                    bgLayers[1].low_texture, bgLayers[0].low_texture, sprite_texture[2],
                    bgLayers[1].high_texture, bgLayers[0].high_texture, sprite_texture[3],
                    bgLayers[2].high_texture
                };
            else layers_texture = {bgLayers[2].low_texture, sprite_texture[0],
                    bgLayers[2].high_texture, sprite_texture[1],
                    bgLayers[1].low_texture, bgLayers[0].low_texture, sprite_texture[2],
                    bgLayers[1].high_texture, bgLayers[0].high_texture, sprite_texture[3]
                };
        case 2:
            for (Uint8 i = 0; i < 2; i ++) {
                bgLayers[i].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
                bgLayers[i].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
                bgLayers[i].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            }

            layer_count = 8;
            layers_texture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
        case 3:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            
            layer_count = 8;
            layers_texture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
        case 4:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            
            layer_count = 8;
            layers_texture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
        case 5:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[1].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX2LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            
            layer_count = 8;
            layers_texture = {bgLayers[1].low_texture, sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    bgLayers[1].high_texture, sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
        case 6:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX4LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            
            layer_count = 6;
            layers_texture = {sprite_texture[0],
                    bgLayers[0].low_texture, sprite_texture[1],
                    sprite_texture[2],
                    bgLayers[0].high_texture, sprite_texture[3]
                };
        case 7:
            bgLayers[0].high_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].low_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            bgLayers[0].tileset = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8LSB, SDL_TEXTUREACCESS_STREAMING, TILESET_WIDTH, 128);
            
            layer_count = 7;
            layers_texture = {sprite_texture[0],
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
    for (Uint8 i = 0; i < layer_count; i++) {
        SDL_SetRenderTarget(renderer, layer);

        if (i == 0) SDL_SetRenderDrawColor(renderer, palette->colors[0]->r, palette->colors[0]->g, palette->colors[0]->b, SDL_ALPHAOPAQUE);
        else SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHATRANSPARENT);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderTexture(renderer, layers_texture[i], NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}