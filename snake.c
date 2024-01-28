// #include "snake.h"
#include "render.h"
#include <time.h>


int main() {

    make_snake();
    snake_plus();
    snake_plus();
    snake_plus();
    gen_food();


    SDL_Window *window; // Window
    // SDL_Surface* screenSurface = NULL; // surface (for images and stuff)
    SDL_Renderer *renderer ;

    // Initialize SDL with video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
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
        fprintf(stderr, "SDL could not create Window: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        fprintf(stderr, "SDL could not create Renderer: %s\n", SDL_GetError());
    }

    


    int grid_x = (WINDOW_WIDTH/2) - (GRID_DIM/2);
    int grid_y = (WINDOW_HEIGHT/2) - (GRID_DIM/2);
    // bool moved = false;

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
    
    SDL_RenderClear(renderer);
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
                            }
                            break;
                        case SDLK_DOWN:
                            if (head->dir != SNAKE_UP) {
                                head->dir = SNAKE_DOWN;
                            }
                            break;
                        case SDLK_LEFT:
                            if (head->dir != SNAKE_RIGHT) {
                                head->dir = SNAKE_LEFT;
                            }
                            break;
                        case SDLK_RIGHT:
                            if (head->dir != SNAKE_LEFT) {
                                head->dir = SNAKE_RIGHT;
                            }
                            break;
                        case SDLK_SPACE:
                            paused = false;
                            reset_snake();
                            gen_food();

                            break;
                    }
                    break;
            }
        }
        SDL_RenderClear(renderer);

        detect_food();

        render_grid(renderer, grid_x, grid_y);
        render_snake_head(renderer, grid_x, grid_y);
        render_snake(renderer, grid_x, grid_y);
        render_food(renderer, grid_x, grid_y);


        if (paused == false) {
            move_snake();
            detect_crash();
        }
        
        
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(180);
    }

    
    // SDL_Delay(2000);




    SDL_DestroyRenderer(renderer); // Destroy renderer
    SDL_DestroyWindow(window); // Destroy window

    SDL_Quit(); // Quit SDL subsystems
}