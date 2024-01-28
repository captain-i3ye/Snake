// basic imports
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

// for grid
#define GRID_SIZE 20
#define GRID_DIM 800


// Score tracker
unsigned int score = 0;

// Checks if the game is paused or not
bool paused = false;

// FOOD
typedef struct food {
    int x;
    int y;
} Food;

Food fud;

// SNAKE
// directions (0-3)
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


// Create snake instance
void make_snake() {
    Snake *new = malloc(sizeof(Snake));
    new->x = rand() % (GRID_SIZE/2) + (GRID_SIZE/4); // <-|-- so that the snake does not spawn at weird places, somewhere around center.
    new->y = rand() % (GRID_SIZE/2) + (GRID_SIZE/4); // <-|
    // new->dir = rand()%4; // any of the directions (0-3) enum  // not working
    new->dir = SNAKE_UP; // therefore, this one is default
    new->next = NULL;

    head = new;
    tail = new;

    return;
}


// Increase snake size
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

// Moves snake and its body (probably)
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


// Moves snake and its body (does it)
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

// Reset the snake and board as in new game
void reset_snake() {
    Snake *body = head;
    Snake *temp;


    // free every node of snake linked list
    while (body != NULL) {
        temp = body;
        body = body->next;
        free(temp);
    }

    // create the snake again
    make_snake();
    snake_plus();
    snake_plus();
    snake_plus();


    return;
}


// Detects if snake crashes into boundary or itself

void detect_crash() {
    if (head->x < 0 || head->x == GRID_SIZE || head->y < 0 || head->y == GRID_SIZE) {
        paused = true;
    }

    // detect self crash
    Snake *body = head->next;
    while (body != NULL) {
        if (body->x == head->x && body->y == head->y) {
            paused = true;

            return;
        }
        body = body->next;
    }

    score = 0; // reset score

    return;
}



// FOOD

// Generate Food
// we check if the the generated food is at snake's body position, yes -> generate again, no -> go on.
void gen_food() {
    bool in_snake_body = false;

    do {
        fud.x = rand() % GRID_SIZE;
        fud.y = rand() % GRID_SIZE;

        Snake *body = head;
        while (body != NULL) {
            if (body->x == fud.x && body->y == fud.y) {
                in_snake_body = true;
            }

            body = body->next;
        }
    } while (in_snake_body);

    return;
}


// Snake detects food
void detect_food() {
    if (head->x == fud.x && head->y == fud.y) {
        gen_food();
        snake_plus();
        score++;
    }
}