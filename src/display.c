// Simulates the PPU chip of the SNES.

#include "include/display.h"

#include "<SDL3/SDL.h>"

static const SDL_PixelFormatDetails *SNES_FORMAT = SDL_GetPixelFormatDetails(SDL_PixelForm.SDL_PIXELFORMAT_ARGB1555);

static const Uint8 BGLAYER_COUNTS[8] = {4, 3, 2, 2, 2, 2, 1, 1};
static const Uint8 LAYER_COUNTS[8] = {12, 10, 8, 8, 8, 8, 6, 7};
static SDL_Texture *layers_texture[8][];
static SDL_Rect *layers_rect[8][][];
static Uint8 *layers_rect_count[8][];

void setupDisplay(void) {
    palette = SDL_CreatePalette(PALETTE_SIZE);
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

    for (Uint8 i = 0; i < BGLAYER_COUNTS[8]; i++) {
        BgLayer *bgLayer = bgLayers[i];

    }

    for (Uint8 i = 0; i < LAYER_COUNTS[bgMode]; i++) {
        SDL_Texture *layer_texture = layers_texture[bgMode][i];
        SDL_Rect *layer_rect[] = layers_rect[bgMode][i];

        SDL_SetRenderTarget(renderer, layer);

        if (i == 0) SDL_SetRenderDrawColor(renderer, palette->colors[0]->r, palette->colors[0]->g, palette->colors[0]->b, SDL_ALPHAOPAQUE);
        else SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHATRANSPARENT);
        SDL_RenderClear(renderer);

        Uint8 layer_rect_count = layer_rect_count[bgMode][i];
        for (Uint8 j = 0; j < layer_rect_count; j++) {
            SDL_RenderFillRect(renderer, &layer_rect[j]);
        }

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderTexture(renderer, layer_texture, NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}