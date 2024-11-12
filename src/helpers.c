#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "helpers.h"

int get_int(HANDLE hConsole)
{
    // Flush the input buffer (before using scanf)
    FlushConsoleInputBuffer(hConsole);

    int n;
    while (scanf("%i", &n) != 1)
    {
        // Clear the invalid provided input
        while (getchar() != '\n') {}
        printf("\nPlease provide a valid input!\n");
    }

    return n;

}


char get_user_input()
{
    char user_input = NO_INPUT;

    // Loop through possible keys and check if any are pressed
    for (int key = 8; key <= 255; key++)
    {
        if (GetAsyncKeyState(key) & 0x8000)
        {  // If the key is pressed
            user_input = (char) tolower(key);
            break;
        }
    }
    return user_input;
}

int get_random_int(int min, int max)
{
    int random_int = (rand() % (max - min + 1)) + min;
    return random_int;
}

int modulus(int a, int b)
{
    if (a < 0)
    {
        return a + b;
    }

    return a % b;
}


int get_color(char c)
{
    switch (c)
    {
        case SNAKE_HEAD:
        case SNAKE_BODY:
            return GREEN;

        case APPLE:
            return RED;

        default:
            return WHITE;
    }
}


void ansi_print(int i, int j, char *s, int color)
{
    // Print s on the terminal at location (i, j), and in color
    printf("\033[%d;%dH\033[%im%s\033[0m", i, j, color, s);
    fflush(stdout);

}


char get_random_direction()
{
    int random_int = get_random_int(0, 3);
    switch (random_int)
    {
        case 0:
            return UP;

        case 1:
            return DOWN;

        case 2:
            return LEFT;

        case 3:
            return RIGHT;
    }
}


void get_new_position(int *new_i_ptr, int *new_j_ptr, char direction)
{
    switch (direction)
    {
        case UP:
            (*new_i_ptr)--;
            break;

        case DOWN:
            (*new_i_ptr)++;
            break;

        case LEFT:
            (*new_j_ptr)--;
            break;

        case RIGHT:
            (*new_j_ptr)++;
            break;
    }
}


char update_direction(char direction)
{
    char user_input = get_user_input();

    // When there is no initial input, waits for any input
    // When moving up or down, can only update the move to left or right
    // When moving left or right, can only update the move to up or down
    if ( ((direction == NO_INPUT) && (user_input == UP || user_input == DOWN || user_input == LEFT || user_input == RIGHT)) ||
         ((direction == UP || direction == DOWN) && (user_input == LEFT || user_input == RIGHT)) ||
         ((direction == LEFT || direction == RIGHT) && (user_input == UP || user_input == DOWN)) )
    {
        direction = user_input;
    }

    return direction;
}


char get_opposite_direction(char direction)
{
    switch (direction)
    {
        case UP:
            return DOWN;

        case DOWN:
            return UP;

        case LEFT:
            return RIGHT;

        case RIGHT:
            return LEFT;
    }
}


void print_score(int game_score)
{
    char message[BUFFER_SIZE];
    sprintf(message, "Score: %i", game_score);
    ansi_print(1, 1, message, WHITE);
}


void update_score(int *game_score_ptr)
{
    // Increment game_score
    *game_score_ptr += SCORE_INC;

    // Print new game_score
    print_score(*game_score_ptr);
}


void update_game_speed(int *sleep_time_ptr, float *factor_ptr, int game_score)
{
    float factor = *factor_ptr;

    // Change in game speed is increasing before reaching the score threshold, and decreasing afterward
    if (game_score <= SCORE_THRESHOLD)
    {
        factor *= 1.1;
    }

    else
    {
        factor /= 1.1;
    }

    // Update sleep time
    *sleep_time_ptr = max(MIN_SLEEP_TIME, *sleep_time_ptr - floor(factor));

    // Update factor
    *factor_ptr = factor;
}


int get_obstacle_generation_score(int obstacle_generation_score_seed)
{
    // Get a new random score
    int delta = GENERATION_SEED_INC / 3;
    int obstacle_generation_score = get_random_int(obstacle_generation_score_seed - delta, obstacle_generation_score_seed + delta);

    // Ensure the random score is divisible by "SCORE_INC"
    obstacle_generation_score = (obstacle_generation_score / SCORE_INC) * SCORE_INC;
    return obstacle_generation_score;
}