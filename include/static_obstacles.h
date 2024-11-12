#ifndef STATIC_OBSTACLES_H
#define STATIC_OBSTACLES_H

// Define structure
typedef struct Static_Obstacle
{
    int i;
    int j;
    int time;
    struct Static_Obstacle *next;
} Static_Obstacle;


int generate_static_obstacle(Static_Obstacle **obstacles, int m, int n, Tile **board);
void update_static_obstacles(Static_Obstacle *obstacles, Tile **board);
void free_static_obstacles(Static_Obstacle *head_obstacle);

#endif //STATIC_OBSTACLES_H
