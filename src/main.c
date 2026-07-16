#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>

#include "display.h"
#include "field.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
} AppState;

static SDL_Thread* gameLoop;

static int thrdFunc_gameLoop(void* data) {
    fieldLoop();
    return 42;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    // Initializing Window
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    AppState* state = (AppState*)SDL_calloc(1, sizeof(AppState));
    if (!state) return SDL_APP_FAILURE;

    state->window = SDL_CreateWindow("FFV", BASE_GAME_WIDTH, BASE_GAME_HEIGHT, 0);
    if (state->window == NULL) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->renderer = SDL_CreateRenderer(state->window, NULL);
    if (state->renderer == NULL) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->running = true;
    *appstate = state;

    // Setup
    setupDisplay(state->renderer);
    start();
    //gameLoop = SDL_CreateThread(thrdFunc_gameLoop, "Game Loop", NULL);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState* state = (AppState*)appstate;

    // Rendering

    return state->running ? SDL_APP_CONTINUE : SDL_APP_SUCCESS;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState* state = (AppState*)appstate;

    switch (event->type) {
    case SDL_EVENT_QUIT:
        state->running = false;
        break;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    if (appstate != NULL) {
        //SDL_DetachThread(gameLoop);
        
        AppState* state = (AppState*)appstate;
        if (state->renderer) SDL_DestroyRenderer(state->renderer);
        if (state->window) SDL_DestroyWindow(state->window);
        SDL_free(state);
    }
}