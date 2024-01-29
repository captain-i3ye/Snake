#include <SDL.h>
#include "snakeNfood.h"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000
#define WINDOW_X 450
#define WINDOW_Y 50

#define GRID_SIZE 20
#define GRID_DIM 900


// Render the whole boxed grid
void render_grid(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

    int cell_size = GRID_DIM / GRID_SIZE;

    SDL_Rect cell;
    cell.w = cell_size;
    cell.h = cell_size;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cell.x = x + i*cell_size;
            cell.y = y + j*cell_size;
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

// Render the border of grid only
void render_grid_border(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

    int box_size = GRID_DIM;

    SDL_Rect box;

    box.w = box_size;
    box.h = box_size;
    box.x = x;
    box.y = y;

    SDL_RenderDrawRect(renderer, &box);

    return;
}

// Render Snake head
void render_snake_head(SDL_Renderer *renderer, int x, int y) {
    int bit_size = GRID_DIM/GRID_SIZE;
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    SDL_Rect header;
    header.w = bit_size;
    header.h = bit_size;
    header.x = x + head->x * bit_size;
    header.y = y + head->y * bit_size;
    SDL_RenderFillRect(renderer, &header);
}


// Render Snake body
void render_snake(SDL_Renderer *renderer, int x, int y) {
    int bit_size = GRID_DIM/GRID_SIZE;

    SDL_SetRenderDrawColor(renderer, 0x00, 0xaa, 0xaa, 255);

    

    SDL_Rect bit;
    bit.w = bit_size;
    bit.h = bit_size;

    Snake *body = head->next;
    while(body != NULL) {
        bit.x = x + body->x * bit_size;
        bit.y = y + body->y * bit_size;

        SDL_RenderFillRect(renderer, &bit);
        body = body->next;
    }

    return;
}

// Render Food
void render_food(SDL_Renderer *renderer, int x, int y) {
    int fud_size = GRID_DIM / GRID_SIZE;
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 255);
    SDL_Rect fuud;

    fuud.x = x + (fud_size * fud.x);
    fuud.y = y + (fud_size * fud.y);

    SDL_RenderFillRect(renderer, &fuud);

    return;
}