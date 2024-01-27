#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// for graphics
#include <SDL.h>

// dimensions for window
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000
#define WINDOW_X 10
#define WINDOW_Y -20


// grid details
#define GRID_SIZE 20
#define GRID_DIM 800


typedef struct snake {
    int x;
    int y;
    int dir;
    struct snake *next;
} Snake;

enum directions{
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT
};


Snake *head;
Snake *tail;


// FUNCTIONALITIES

// Create Snake
void make_snake() {
    Snake *new = malloc(sizeof(Snake));
    new->x = rand() % (GRID_SIZE/2) + (GRID_SIZE/4); // <-|-- snake spawns away from border (somewhere near the middle)
    new->y = rand() % (GRID_SIZE/2) + (GRID_SIZE/4); // <-|
    new->dir = rand()%4; // any of the directions (0-3)
    new->next = NULL;

    head = new;
    tail = new;

    return;
}

// Increase Snake
void snake_plus() {
    Snake *new = malloc(sizeof(Snake));
    
    // add snake part in opposite direction of its movement
    switch(tail->dir) {
        case SNAKE_UP:
            new->x = tail->x;
            new->y = tail->y+1;
            break;
        case SNAKE_DOWN:
            new->x = tail->x;
            new->y = tail->y-1;
            break;
        case SNAKE_LEFT:
            new->x = tail->x+1;
            new->y = tail->y;
            break;
        case SNAKE_RIGHT:
            new->x = tail->x-1;
            new->y = tail->y;
            break;
    }

    new->next = NULL;
    tail->next = new;
    tail = new;

    return;
}

// reset



// Movement
void move_snake() {
    
    switch(head->dir) {
        case SNAKE_UP:
            head->y--;
            break;
        case SNAKE_DOWN:
            head->y++;
            break;
        case SNAKE_LEFT:
            head->x--;
            break;
        case SNAKE_RIGHT:
            head->x++;
            break;  
    }

    Snake *body = head;

    while (body->next != NULL) {
        body->next->x = body->x;
        body->next->y = body->y;
        body->next->dir = body->dir;

        body = body->next;
    }

    return;
}


// RENDERING

void render_grid(SDL_Renderer *renderer, int x, int y) {

    SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255);

    int cell_size = GRID_DIM/GRID_SIZE;

    SDL_Rect cell;
    cell.w = cell_size;
    cell.h = cell_size;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cell.x = x + (i*cell_size);
            cell.y = y + (j*cell_size);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }

    return;
}











int main() {

    SDL_Window *window;
    SDL_Renderer *renderer;


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL cannot initialize due to : %s\n", SDL_GetError());
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
        fprintf(stderr, "Could not create window : %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        fprintf(stderr, "Could not create renderer : %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 0x0a, 0x0a, 0x0a, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;

    // to center the grid
    int grid_x = (WINDOW_WIDTH/2) - (GRID_DIM/2);
    int grid_y = (WINDOW_HEIGHT/2) - (GRID_DIM/2);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_UP:
                            if (head->dir != SNAKE_DOWN){
                                head->dir = SNAKE_UP;
                            }
                            break;
                        case SDLK_DOWN:
                            if (head->dir != SNAKE_UP){
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
                        
                    }
            }
        }
    }

    SDL_RenderClear(renderer);

    render_grid();

    

}