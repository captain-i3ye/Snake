#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#define GRID_SIZE 20
#define GRID_DIM 800

enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT
};

typedef struct snake {
    int x;
    int y;
    int dir;

    struct snake *next;
} Snake;

Snake *head;
Snake *tail;

void make_snake() {
    Snake *new = malloc(sizeof(Snake));
    new->x = rand() % (GRID_SIZE/2) + (GRID_SIZE/4);
    new->y = rand() % (GRID_SIZE/2) + (GRID_SIZE/4);
    new->dir = SNAKE_UP;
    new->next = NULL;

    head = new;
    tail = new;

    return;
}

void snake_plus() {
    Snake *new = malloc(sizeof(Snake));

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

void move_snake() {
    // int prev_x = head->x;
    // int prev_y = head->y; 
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
    // Snake *body = head;
    // while (body->next != NULL) {
    //     body->next->x = body->x;
    //     body->next->y = body->y;

    //     body = body->next;
    // }
    return;
}