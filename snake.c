#include "snake.h"
#include "render.h"

int main(int argc, char** argv) {

    SDL_Window* window = NULL; // Window
    SDL_Surface* screenSurface = NULL; // surface (for images and stuff)

    // Initialize SDL with video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow(
        "Snake",
        WINDOW_X,
        WINDOW_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
    }



    SDL_DestroyWindow() // Destroy window

    SDL_Quit(); // Quit SDL subsystems
}