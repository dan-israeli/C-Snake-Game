#ifndef BOARD_H
#define BOARD_H

// Define structure
typedef struct
{
    char c;
    bool is_visible;
} Tile;


void print_horizontal_border(int n);
void print_borders(int m, int n);

Tile **init_board(int m, int n);
void free_board(int m, Tile **board);
bool is_out_of_bounds(int i, int j, int m, int n);
bool is_position_apple(int i, int j, Tile **board);
bool is_position_snake(int i, int j, Tile **board);
bool is_position_obstacle(int i, int j, Tile **board);
void update_board(int i, int j, char c, Tile **board, bool is_visible);
void get_random_empty_position(int *i_ptr, int *j_ptr, int m, int n, Tile **board);

#endif //BOARD_H
