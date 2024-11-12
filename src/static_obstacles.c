#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "board.h"
#include "static_obstacles.h"


void flash_static_obstacle(Static_Obstacle *obstacle, Tile **board)
{
    if (obstacle->time % 2 == 0)
    {
        update_board(obstacle->i, obstacle->j, EMPTY, board, false);
        return;
    }

    update_board(obstacle->i, obstacle->j, OBSTACLE, board, false);
}


int generate_static_obstacle(Static_Obstacle **obstacles, int m, int n, Tile **board)
{
    Static_Obstacle *new_obstacle = malloc(sizeof(Static_Obstacle));

    // Memory error
    if (new_obstacle == NULL)
    {
        return MEMORY_ERROR_CODE;
    }

    // Initialize obstacle's attributes
    get_random_empty_position(&new_obstacle->i, &new_obstacle->j, m, n, board);
    new_obstacle->time = 1;

    // Initialize the head
    if (obstacles == NULL)
    {
        new_obstacle->next = NULL;
        *obstacles = new_obstacle;
        return true;
    }

    // Add the new obstacle to the list (as the new head)
    new_obstacle->next = *obstacles;
    *obstacles = new_obstacle;
    return SUCCESS_CODE;
}

void update_static_obstacles(Static_Obstacle *obstacles, Tile **board)
{
    for (Static_Obstacle *c_obstacle = obstacles; c_obstacle != NULL; c_obstacle = c_obstacle->next)
    {
        if (c_obstacle->time <= GRACE_TIME)
        {
            flash_static_obstacle(c_obstacle, board);
            (c_obstacle->time)++;
            continue;
        }

        if (!is_position_obstacle(c_obstacle->i, c_obstacle->j, board))
        {
            update_board(c_obstacle->i, c_obstacle->j, OBSTACLE, board, true);
        }
    }
}


void free_static_obstacles(Static_Obstacle *head_obstacle)
{
    Static_Obstacle *c_obstacle = head_obstacle;
    while (c_obstacle != NULL)
    {
        Static_Obstacle *n_dynamic_obstacle = c_obstacle->next;
        free(c_obstacle);

        c_obstacle = n_dynamic_obstacle;
    }
}