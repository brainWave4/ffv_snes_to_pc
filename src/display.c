#include "include/display.h"

#include "<SDL3/SDL.h>"

void setupDisplay(void) {
    palette = SDL_CreatePalette(256);
    SDL_SetPaletteColors(palette, SDL_Color(0, 0, 0, SDL_ALPHAOPAQUE), 1, 1);
}

void draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, palette->colors[0]->r, palette->colors[0]->g, palette->colors[0]->b, palette->colors[0]->a);
    SDL_RenderClear(renderer);

    switch (bgMode) {
        default: // Mode 0
            break
    }

    SDL_RenderPresent(renderer);
}