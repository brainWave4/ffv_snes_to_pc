#include "include/display.h"

#include "<SDL3/SDL.h>"

static const Uint8 LAYER_COUNTS[8] = {12, 10, 8, 8, 8, 8, 6, 7} 

void setupDisplay(void) {
    palette = SDL_CreatePalette(256);
    SDL_SetPaletteColors(palette, SDL_Color(0, 0, 0, SDL_ALPHAOPAQUE), 1, 1);
}

void draw(SDL_Renderer *renderer) {
    SDL_Texture *layers[];

    switch (bgMode) {
        default: // Mode 0
            break
    }

    for(Uint8 i = 0; i < LAYER_COUNTS[bgMode]; i++) {
        SDL_Texture *layer = layers[i];

        SDL_SetRenderTarget(renderer, layer);

        if (i == 0) SDL_SetRenderDrawColor(renderer, palette->colors[0]->r, palette->colors[0]->g, palette->colors[0]->b, SDL_MAX_UINT8);
        elseSDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Draw Layer elements here

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderTexture(renderer, layer, 0, 0);
    }

    SDL_RenderPresent(renderer);
}