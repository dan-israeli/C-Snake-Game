#include <time.h>
#include <windows.h>
#include "helpers.h"
#include "board.h"
#include "snake.h"
#include "static_obstacles.h"
#include "dynamic_obstacles.h"
#include "gameplay.h"


void free_memory_allocations(Node *snake_head, Static_Obstacle *static_obstacles,
                             Dynamic_Obstacle *dynamic_obstacles, int m, Tile **board)
{
    free_board(m, board);
    free_snake(snake_head);
    free_static_obstacles(static_obstacles);
    free_dynamic_obstacles(dynamic_obstacles);
}


void gameplay(int m, int n, int initial_sleep_time, float dynamic_obstacle_generation_prob,
               float initial_dynamic_speed_mode_factor, int is_dynamic_speed_mode, int is_invisible_walls_mode)
{
    // Clear terminal window
    system("cls");

    // Set random seed
    srand(time(NULL));

    // Set game parameters
    Node *snake_head = NULL;
    Node *snake_tail = NULL;
    Static_Obstacle *static_obstacles = NULL;
    Dynamic_Obstacle *dynamic_obstacles = NULL;

    int sleep_time = initial_sleep_time;
    float dynamic_speed_mode_factor = initial_dynamic_speed_mode_factor;

    int obstacle_generation_score_seed = GENERATION_SEED_INC;
    int game_score = 0;

    // Print game start message
    ansi_print(1, 1, GAME_START_MESSAGE, WHITE);

    // Initialize board
    print_borders(m, n);
    Tile** board = init_board(m, n);

    // Initialize snake
    int function_output = init_snake(&snake_head, &snake_tail, m, n, board);

    // Memory error
    if (function_output == MEMORY_ERROR_CODE)
    {
        ansi_print(m+4, 1, MEMORY_ERROR, WHITE);
        return;
    }

    // Generate apple
    generate_apple(m, n, board);

    // Get the first obstacle generation score
    int obstacle_generation_score = get_obstacle_generation_score(obstacle_generation_score_seed);


    // Wait for an initial input from the user to start the game
    char direction = NO_INPUT;
    while (direction == NO_INPUT)
    {
        direction = update_direction(direction);
    }

    Sleep(DELAY);

    ansi_print(1, 1, DELETE_GAME_START_MESSAGE, WHITE);
    print_score(game_score);

    // Start game
    bool memory_error_flag = false;
    while (true)
    {
        // Update the snake's direction (based on the user's input)
        direction = update_direction(direction);

        // Move snake based on the direction
        function_output = move_snake(&snake_head, &snake_tail, direction, m, n, board,
                                     &game_score, &sleep_time, &dynamic_speed_mode_factor,
                                     is_invisible_walls_mode, is_dynamic_speed_mode);

        // Check the move_snake function's output code
        if (function_output != SUCCESS_CODE)
        {
            if (function_output == MEMORY_ERROR_CODE)
            {
                memory_error_flag = true;
            }
            break;
        }

        // Check for new obstacle generation
        if (game_score == obstacle_generation_score)
        {
            // sample a random number between 0 and 1
            float x = (float)rand() / RAND_MAX;

            // Generate obstacle type based on the sampled number
            if (x <= dynamic_obstacle_generation_prob)
            {
                function_output = generate_dynamic_obstacle(&dynamic_obstacles, m, n, board);
            }

            else
            {
                function_output = generate_static_obstacle(&static_obstacles, m, n, board);
            }

            // Memory error
            if (function_output == MEMORY_ERROR_CODE)
            {
                memory_error_flag = true;
                break;
            }

            // increase generation threshold, and get the new obstacle generation score
            obstacle_generation_score_seed += GENERATION_SEED_INC;
            obstacle_generation_score = get_obstacle_generation_score(obstacle_generation_score_seed);
        }

        // Update static obstacles
        update_static_obstacles(static_obstacles, board);

        // Move dynamic obstacles
        function_output = move_dynamic_obstacles(dynamic_obstacles, snake_head, &snake_tail, m, n, board);

        // Invalid move
        if (function_output == INVALID_MOVE_CODE)
        {
            break;
        }

        // Wait between frames
        Sleep(sleep_time);
    }

    // Free memory allocations
    free_memory_allocations(snake_head, static_obstacles, dynamic_obstacles, m, board);

    if (memory_error_flag)
    {
        ansi_print(m+4, 1, MEMORY_ERROR, WHITE);
    }

    else
    {
        ansi_print(m+4, 1, GAME_END_MESSAGE, WHITE);
    }

    char user_input = NO_INPUT;
    while (user_input != BACK)
    {
        user_input = get_user_input();
    }
}