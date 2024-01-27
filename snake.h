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
    // new->dir = rand()%4; // any of the directions (0-3) enum
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


// I don't know why this does not work.
void move_snake_nw() {
    Snake *prev = head;
    Snake *curr = head->next; 
    Snake *temp = malloc(sizeof(Snake));
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
    
    while (curr != NULL) {
        temp->x = curr->x;
        temp->y = curr->y;
        temp->dir = curr->dir;

        curr->x = prev->x;
        curr->y = prev->y;
        curr->dir = prev->dir;

        prev = temp;

        curr = curr->next;
    }
    free(temp);
    return;
}

void move_snake()
{
    int prev_x = head->x;
    int prev_y = head->y;
    int prev_dir = head->dir;

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

    Snake *curr = head;

    if(curr->next != NULL) {
        curr = curr->next;
    }

    while(curr != NULL) {
        
        int temp_x = curr->x;
        int temp_y = curr->y;
        int temp_dir = curr->dir;

        curr->x = prev_x;
        curr->y = prev_y;
        curr->dir = prev_dir;

        curr = curr->next;

        prev_x = temp_x;
        prev_y = temp_y;
        prev_dir= temp_dir;

    }

    return;
}
