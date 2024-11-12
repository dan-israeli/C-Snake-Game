#ifndef DYNAMIC_OBSTACLES_H
#define DYNAMIC_OBSTACLES_H

#include "snake.h"

// Define structure
typedef struct Dynamic_Obstacle
{
    int i;
    int j;
    int time;
    char direction;
    struct Dynamic_Obstacle *next;
} Dynamic_Obstacle;


int generate_dynamic_obstacle(Dynamic_Obstacle **obstacles, int m, int n, Tile **board);
int move_dynamic_obstacles(Dynamic_Obstacle *obstacles, Node *snake_head, Node **snake_tail_ptr,
                           int m, int n, Tile **board);
void free_dynamic_obstacles(Dynamic_Obstacle *head_obstacle);

#endif //DYNAMIC_OBSTACLES_H
