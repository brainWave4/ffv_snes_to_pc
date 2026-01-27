#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "field.h"

int main(void) {
    // Initializing Window

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENT) > 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError())
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("FFV", 256, 224, 0);
    if (window == NULL) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError())
        return -2;
    }

    SDL_Renderer renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNCH);
    if (renderer == NULL) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError())
        return -3;
    }

    // Setup
    //start();

    // Game Loop

    bool running = true;
    SDL_Event event;

    while (running) {
        // Input
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            }
        }

        // Inner Logic Loop
        //fieldLoop();

        // Rendering
    }

    // Closing
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}