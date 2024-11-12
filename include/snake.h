#ifndef SNAKE_H
#define SNAKE_H

// Define structure
typedef struct Node
{
    int i;
    int j;
    struct Node *next;
    struct Node *prev;
} Node;

bool init_snake(Node **head_ptr, Node **tail_ptr, int m, int n, Tile **board);
void generate_apple(int m, int n, Tile **board);
int move_snake(Node **head_ptr, Node **tail_ptr, char direction, int m, int n, Tile **board,
               int *game_score_ptr, int *sleep_time_ptr, float *dynamic_speed_mode_factor_ptr,
               int is_invisible_walls_mode, int is_dynamic_speed_mode);
int cut_snake(Node *head, Node **tail_ptr, int i, int j, Tile **board);
void free_snake(Node *head_node);

#endif //SNAKE_H
