// Simulates the PPU chip of the SNES.

#include "include/display.h"

#include "<SDL3/SDL.h>"

static const Uint8 BGLAYER_COUNTS[8] = {4, 3, 2, 2, 2, 2, 1, 1};
static const Uint8 LAYER_COUNTS[8] = {12, 10, 8, 8, 8, 8, 6, 7};
static SDL_Texture *layers_texture[8][];
static SDL_Rect *layers_rect[8][][];
static Uint8 *layers_rect_count[8][];

void setupDisplay(void) {
    palette = SDL_CreatePalette(256);
    SDL_SetPaletteColors(palette, SDL_Color(0, 0, 0, SDL_ALPHAOPAQUE), 0, 1);
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