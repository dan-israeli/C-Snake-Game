#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "helpers.h"
#include "snake.h"


bool is_valid_snake(int i, int j, int m, int n, Tile **board, Node *tail) {
    // Check if reached a wall or an obstacle
    if (is_out_of_bounds(i, j, m, n) || is_position_obstacle(i, j, board))
    {
        return false;
    }

    // The position is valid iff it is not containing any snake body, except the tail
    return (board[i][j].c != SNAKE_BODY) || (i == tail->i && j == tail->j);
}


void init_snake_head(Node *head, Node *tail, int m, int n, Tile **board)
{
    // Initialize the head's attributes (choose a random position)
    get_random_empty_position(&head->i, &head->j, m, n, board);
    head->next = tail;
    head->prev = NULL;
}


void init_snake_tail(Node* head, Node*tail, int m, int n, Tile **board)
{
    // Initialize the tail's attributes
    tail->i = head->i;
    tail->j = head->j;
    tail->next = NULL;
    tail->prev = head;


    // Make sure the tail will be randomly adjacent to the head, but in a valid position
    do
    {
        char random_direction = get_random_direction();
        get_new_position(&tail->i, &tail->j, random_direction);
    }
    while(is_out_of_bounds(tail->i, tail->j, m, n) || board[tail->i][tail->j].c != EMPTY);
}


bool init_snake(Node **head_ptr, Node **tail_ptr, int m, int n, Tile **board)
{
    // Allocate memory for the snake's head and tail
    Node *head = malloc(sizeof(Node));
    Node *tail = malloc(sizeof(Node));

    // Memory error
    if (head == NULL || tail == NULL)
    {
        return MEMORY_ERROR_CODE;
    }

    init_snake_head(head, tail, m, n, board);
    init_snake_tail(head, tail, m, n, board);

    // Update the board based on the initial snake position
    update_board(head->i, head->j, SNAKE_HEAD, board, true);
    update_board(tail->i, tail->j, SNAKE_BODY, board, true);

    // Update the values
    *head_ptr = head;
    *tail_ptr = tail;

    return SUCCESS_CODE;
}


void generate_apple(int m, int n, Tile **board)
{
    int i, j;
    get_random_empty_position(&i, &j, m, n, board);
    update_board(i, j, APPLE, board, true);
}


bool increment_snake(Node **head_ptr, int new_i, int new_j, Tile **board)
{
    // Get the value from the pointer
    Node *head = *head_ptr;

    // Initialize a new head
    Node *new_head = malloc(sizeof(Node));

    // Memory error
    if (new_head == NULL) {
        return false;
    }

    new_head->prev = NULL;
    new_head->next = head;
    new_head->i = new_i;
    new_head->j = new_j;


    // Update the board based on the initial snake position
    update_board(head->i, head->j, SNAKE_BODY, board, true);
    update_board(new_head->i, new_head->j, SNAKE_HEAD, board, true);

    // Update the head
    head->prev = new_head;
    *head_ptr = new_head;

    return true;
}


void shift_tail_to_head(Node **head_ptr, Node **tail_ptr, int new_i, int new_j, Tile **board)
{
    // Get the values from the pointers
    Node *head = *head_ptr;
    Node *tail = *tail_ptr;

    // Make the tail's previous node as the node tail
    Node *new_tail = tail->prev;
    new_tail->next = NULL;
    update_board(tail->i, tail->j, EMPTY, board, true);

    // Make the tail as the new head
    Node *new_head = tail;
    new_head->i = new_i;
    new_head->j = new_j;
    new_head->prev = NULL;
    new_head->next = head;
    head->prev = new_head;

    // Update board
    update_board(new_head->i, new_head->j, SNAKE_HEAD, board, true);
    update_board(head->i, head->j, SNAKE_BODY, board, true);

    // Update the head and tail values
    *head_ptr = new_head;
    *tail_ptr = new_tail;
}


int move_snake(Node **head_ptr, Node **tail_ptr, char direction, int m, int n, Tile **board,
               int *game_score_ptr, int *sleep_time_ptr, float *dynamic_speed_mode_factor_ptr,
               int is_invisible_walls_mode, int is_dynamic_speed_mode)
{
    // Get values from pointers
    Node *head = *head_ptr;
    Node *tail = *tail_ptr;

    int new_i = head->i;
    int new_j = head->j;

    get_new_position(&new_i, &new_j, direction);

    // Check if Invisible Walls Mode is enabled
    if (is_invisible_walls_mode)
    {
        new_i = modulus(new_i, m);
        new_j = modulus(new_j, n);
    }

    // Check if the new position is valid
    if (!is_valid_snake(new_i, new_j, m, n, board, tail))
    {
        return INVALID_MOVE_CODE;
    }

    // Check if the apple is eaten
    if (is_position_apple(new_i, new_j, board))
    {
        // Memory error
        if (!increment_snake(head_ptr, new_i, new_j, board))
        {
            return MEMORY_ERROR_CODE;
        }

        update_score(game_score_ptr);
        generate_apple(m, n, board);

        // Check if Dynamic Speed Mode is enabled
        if (is_dynamic_speed_mode)
        {
            update_game_speed(sleep_time_ptr, dynamic_speed_mode_factor_ptr, *game_score_ptr);
        }
        return SUCCESS_CODE;
    }

    shift_tail_to_head(head_ptr, tail_ptr, new_i, new_j, board);
    return SUCCESS_CODE;
}


void free_snake(Node *head_node)
{
    Node *c_node = head_node;
    while (c_node != NULL)
    {
        Node *n_node = c_node->next;
        free(c_node);
        c_node = n_node;
    }
}


Node *get_node(Node *head, int i, int j)
{
    for (Node *c_node = head; c_node != NULL; c_node = c_node->next)
    {
        if (c_node->i == i && c_node->j == j)
        {
            return c_node;
        }
    }

    return NULL;
}


int cut_snake(Node *head, Node **tail_ptr, int i, int j, Tile **board)
{
    // Get the node which collided with the obstacle (snake body node)
    Node *collided_node = get_node(head, i, j);

    // Update the tail global variable
    *tail_ptr = collided_node->prev;

    // The collided node is the second one
    if (*tail_ptr == head)
    {
        return INVALID_MOVE_CODE;
    }

    // Deleting all nodes from the collided node
    for (Node *c_node = collided_node; c_node != NULL; c_node = c_node->next)
    {
        update_board(c_node->i, c_node->j, EMPTY, board, true);
    }

    // Free memory of deleted nodes
    free_snake(collided_node);
    return SUCCESS_CODE;
}
