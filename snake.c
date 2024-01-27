// #include "snake.h"
#include "render.h"
#include <time.h>
int main() {

    make_snake();
    snake_plus();
    snake_plus();
    snake_plus();



    SDL_Window *window; // Window
    // SDL_Surface* screenSurface = NULL; // surface (for images and stuff)
    SDL_Renderer *renderer ;

    // Initialize SDL with video subsystem
    if (SDL_INIT_VIDEO < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow(
        "Snake Game",
        WINDOW_X,
        WINDOW_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
    }

    


    int grid_x = (WINDOW_WIDTH/2) - (GRID_DIM/2);
    int grid_y = (WINDOW_HEIGHT/2) - (GRID_DIM/2);
    // bool moved = false;

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
    
    SDL_RenderClear(renderer);
    // render_grid(renderer, grid_x, grid_y);
    // render_snake(renderer, grid_x, grid_y);
    // SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_UP:
                            if (head->dir != SNAKE_DOWN) {
                                head->dir = SNAKE_UP;
                                // move_snake();
                            }
                    }
                    break;
            }
        }
        SDL_RenderClear(renderer);


        render_grid(renderer, grid_x, grid_y);
        render_snake(renderer, grid_x, grid_y);
        move_snake();
        
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    
    // SDL_Delay(2000);




    SDL_DestroyRenderer(renderer); // Destroy renderer
    SDL_DestroyWindow(window); // Destroy window

    SDL_Quit(); // Quit SDL subsystems
}