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

    new->x = tail->x;
    new->y = tail->y-1;
    new->dir = tail->dir;

    new->next = NULL;
    tail->next = new;
    tail = new;
    return;
}

void move_snake() {

    return;
}