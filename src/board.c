#include <stdio.h>
#include "helpers.h"
#include "board.h"


void print_horizontal_border(int n)
{
    for (int i = 0; i < n; i++){
        printf("%c", HORIZONTAL_LINE);
    }
    printf("\n");
}


void print_borders(int m, int n)
{
    // Print board borders
    print_horizontal_border(n+2);
    for (int i = 0; i < m; i++)
    {
        printf("%c", VERTICAL_LINE);
        for (int j = 0; j < n; j++)
        {
            printf("%c", EMPTY);
        }
        printf("%c\n", VERTICAL_LINE);
    }
    print_horizontal_border(n+2);
}


Tile **init_board(int m, int n)
{
    // Allocate memory for the board (2D array of Tile structures), and initialize values to EMPTY
    Tile **board = malloc(m * sizeof(char *));
    for (int i = 0; i < m; i++)
    {
        board[i] = malloc(n * sizeof(Tile));

        for (int j = 0; j < n; j++)
        {
            // Initialize a new tile
            Tile tile;
            tile.c = EMPTY;
            tile.is_visible = true;

            // Update board
            board[i][j] = tile;
        }
    }

    return board;
}


void free_board(int m, Tile **board)
{
    for (int i = 0; i < m; i++)
    {
        free(board[i]);
    }

    free(board);
}


void get_random_empty_position(int *i_ptr, int *j_ptr, int m, int n, Tile **board)
{
    int i, j;
    do
    {
        i = get_random_int(0, m-1);
        j = get_random_int(0, n-1);
    } while (board[i][j].c != EMPTY);

    *i_ptr = i;
    *j_ptr = j;
}


bool is_out_of_bounds(int i, int j, int m, int n)
{
    return i == -1 || i == m || j == -1 || j == n;
}


bool is_position_apple(int i, int j, Tile **board)
{
   return board[i][j].c == APPLE;
}


bool is_position_snake(int i, int j, Tile **board)
{
    return board[i][j].c == SNAKE_HEAD || board[i][j].c == SNAKE_BODY;
}


bool is_position_obstacle(int i, int j, Tile **board)
{
    return board[i][j].c == OBSTACLE && board[i][j].is_visible;
}


void update_board(int i, int j, char c, Tile **board, bool is_visible)
{
    // Update tile's attributes
    board[i][j].c = c;
    board[i][j].is_visible = is_visible;

    // Cast char to string
    char s[2];
    s[0] = c;
    s[1] = NO_INPUT;

    // Get printing color
    int color = get_color(c);

    // Print update
    ansi_print(i+ROW_OFFSET, j+COLUMN_OFFSET, s, color);
}
