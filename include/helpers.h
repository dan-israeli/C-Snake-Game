#ifndef CS50_HELPERS_H
#define CS50_HELPERS_H

#include <windows.h>

// directions
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define NO_INPUT '\0'

// Board symbols
#define HORIZONTAL_LINE '-'
#define VERTICAL_LINE '|'
#define EMPTY ' '
#define SNAKE_HEAD 'O'
#define SNAKE_BODY 'o'
#define APPLE '@'
#define OBSTACLE '#'

// Colors
#define WHITE 0
#define RED 31
#define GREEN 32

// ANSI print offsets
#define COLUMN_OFFSET 2
#define ROW_OFFSET 3

// Return value codes
#define SUCCESS_CODE 0
#define MEMORY_ERROR_CODE 1
#define INVALID_MOVE_CODE 2

//Misc
#define BUFFER_SIZE 50
#define GRACE_TIME 25
#define SCORE_INC 10
#define GENERATION_SEED_INC 60
#define SCORE_THRESHOLD 150
#define MIN_SLEEP_TIME 10

int get_int(HANDLE hConsole);
char get_user_input();
int get_random_int(int min, int max);
int modulus(int a, int b);
int get_color(char c);
void ansi_print(int i, int j, char *s, int color);
char get_random_direction();
void get_new_position(int *new_i_ptr, int *new_j_ptr, char direction);
char update_direction(char direction);
char get_opposite_direction(char direction);
void print_score(int game_score);
void update_score(int *game_score_ptr);
void update_game_speed(int *sleep_time_ptr, float *factor_ptr, int game_score);
int get_obstacle_generation_score(int threshold);

#endif //CS50_HELPERS_H
