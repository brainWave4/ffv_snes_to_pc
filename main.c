#include <SDL3/SDL.h>

int main(void) {
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Final Fantasy V", 256, 224, 0);
    
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}