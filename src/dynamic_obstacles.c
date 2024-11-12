#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "board.h"
#include "dynamic_obstacles.h"
#include "snake.h"


void update_board_dynamic_obstacle(Dynamic_Obstacle *obstacle, int old_i, int old_j, Tile **board)
{

    if (!is_position_snake(old_i, old_j, board))
    {
        update_board(old_i, old_j, EMPTY, board, true);
    }

    int new_i = obstacle->i;
    int new_j = obstacle->j;

    // Place the obstacle at the new position (flashing when still in GRACE_TIME)
    if (obstacle->time <= GRACE_TIME)
    {
        if (is_position_snake(new_i, new_j, board))
        {
            return;
        }

        if (obstacle->time % 2 == 0)
        {
            update_board(new_i, new_j, EMPTY, board, false);
            return;
        }

        update_board(new_i, new_j, OBSTACLE, board, false);
        return;
    }

    // Place the obstacle at the new position
    update_board(new_i, new_j, OBSTACLE, board, true);
}


int generate_dynamic_obstacle(Dynamic_Obstacle **obstacles, int m, int n, Tile **board)
{
    Dynamic_Obstacle *new_obstacle = malloc(sizeof(Dynamic_Obstacle));

    // Memory error
    if (new_obstacle == NULL)
    {
        return MEMORY_ERROR_CODE;
    }

    // Initialize obstacle's attributes
    get_random_empty_position(&new_obstacle->i, &new_obstacle->j, m, n, board);
    new_obstacle->time = 1;
    new_obstacle->direction = get_random_direction();

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


bool is_position_blocked(int i, int j, int m, int n, Tile **board)
{
    if (is_out_of_bounds(i, j, m, n))
    {
        return true;
    }

    return board[i][j].c != EMPTY && !is_position_snake(i, j, board);
}


void update_dynamic_obstacles_direction(Dynamic_Obstacle *obstacles, int m, int n, Tile **board)
{
    for (Dynamic_Obstacle *c_obstacle = obstacles; c_obstacle != NULL; c_obstacle = c_obstacle->next)
    {
        // Get new position
        int new_i = c_obstacle->i;
        int new_j = c_obstacle->j;
        get_new_position(&new_i, &new_j, c_obstacle->direction);

        // Check if the new position is blocked
        if (is_position_blocked(new_i, new_j, m, n, board))
        {
            c_obstacle->direction = get_opposite_direction(c_obstacle->direction);
        }
    }
}


int move_dynamic_obstacles(Dynamic_Obstacle *obstacles, Node *snake_head, Node **snake_tail_ptr,
                           int m, int n, Tile **board)
{
    // Update relevant obstacles direction
    update_dynamic_obstacles_direction(obstacles, m, n, board);

    for (Dynamic_Obstacle *c_obstacle = obstacles; c_obstacle != NULL; c_obstacle = c_obstacle->next)
    {
        // Save old location
        int old_i = c_obstacle->i;
        int old_j = c_obstacle->j;

        // Get new position
        int new_i = old_i, new_j = old_j;
        get_new_position(&new_i, &new_j, c_obstacle->direction);

        // Only relevant after the grace time has passed
        if (c_obstacle->time > GRACE_TIME)
        {
            // Check if the snake's head is at the new location
            if (board[new_i][new_j].c == SNAKE_HEAD)
            {
                return INVALID_MOVE_CODE;
            }

            // Check if the snake's body is at the new location
            if (board[new_i][new_j].c == SNAKE_BODY)
            {
                if (cut_snake(snake_head, snake_tail_ptr, new_i, new_j, board) == INVALID_MOVE_CODE)
                {
                    return INVALID_MOVE_CODE;
                };
            }
        }

        // Update to the new position if it is not blocked
        // Else, the obstacle does not move in the current frame
        if (!is_position_blocked(new_i, new_j, m, n, board))
        {
            c_obstacle->i = new_i;
            c_obstacle->j = new_j;
        }

        // Update board
        update_board_dynamic_obstacle(c_obstacle, old_i, old_j, board);

        // Update obstacle time
        if (c_obstacle->time <= GRACE_TIME)
        {
            (c_obstacle->time)++;
        }

    }
    return SUCCESS_CODE;
}


void free_dynamic_obstacles(Dynamic_Obstacle *head_obstacle)
{
    Dynamic_Obstacle *c_obstacle = head_obstacle;
    while (c_obstacle != NULL)
    {
        Dynamic_Obstacle *n_dynamic_obstacle = c_obstacle->next;
        free(c_obstacle);

        c_obstacle = n_dynamic_obstacle;
    }
}