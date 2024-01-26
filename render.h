#include <SDL.h>
#include "snake.h"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000
#define WINDOW_X 450
#define WINDOW_Y 50

#define GRID_SIZE 20
#define GRID_DIM 800

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

void render_snake(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0xaa, 0xaa, 255);

    int bit_size = GRID_DIM/GRID_SIZE;

    SDL_Rect bit;
    bit.w = bit_size;
    bit.h = bit_size;

    Snake *body = head;
    while(body != NULL) {
        bit.x = x + body->x * bit_size;
        bit.y = y + body->y * bit_size;

        SDL_RenderFillRect(renderer, &bit);
        body = body->next;
    }

    return;
}