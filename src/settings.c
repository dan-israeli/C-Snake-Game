// libraries
#include <stdio.h>
#include <windows.h>
#include "helpers.h"
#include "settings.h"


void print_settings_menu()
{
    // Clear the terminal window
    system("cls");

    // Print the settings screen menu
    printf("====================================\n");
    printf("          GAME SETTINGS MENU            \n");
    printf("====================================\n\n");
    printf("[1] Adjust Game Difficulty\n");
    printf("[2] Adjust Board Size\n");
    printf("[3] Toggle Dynamic Speed Mode\n");
    printf("[4] Toggle Invisible Walls Mode\n");
    printf("[B] Return to Main Menu\n\n");
    printf("====================================\n");
}


void print_easy_info()
{
    printf("EASY   - Initial game speed is slow. Small probability for dynamic obstacles.\n");
    printf("         If Dynamic Speed Mode is enabled, each speed increment is very subtle.\n\n");
}


void print_medium_info()
{
    printf("NORMAL - Initial game speed is normal. Some probability for dynamic obstacles.\n");
    printf("         If Dynamic Speed Mode is enabled, each speed increment is subtle.\n\n");
}


void print_hard_info()
{
    printf("HARD   - Initial game speed is fast. High probability for dynamic obstacles.\n");
    printf("         If Dynamic Speed Mode is enabled, the change is more noticeable.\n");
}


void adjust_game_difficulty(int *initial_sleep_time_ptr, float *dynamic_obstacle_generation_prob_ptr,
                            float *dynamic_speed_mode_factor_ptr, HANDLE hConsole)
{
    // Print current game difficulty
    switch(*initial_sleep_time_ptr)
    {
        case EASY_SLEEP_TIME:
            printf("Current Game Difficulty: EASY\n");
            break;

        case MEDIUM_SLEEP_TIME:
            printf("Current Game Difficulty: MEDIUM\n");
            break;

        case HARD_SLEEP_TIME:
            printf("Current Game Difficulty: HARD\n");
            break;
    }

    // Print difficulty setting instructions
    printf("[1] EASY\n");
    printf("[2] MEDIUM\n");
    printf("[3] HARD\n");
    printf("[4] Information about Difficulty Modes\n");

    while (true) {
        // Get user's input
        int user_input = get_int(hConsole);
        while (user_input != EASY && user_input != MEDIUM && user_input != HARD && user_input != INFO)
        {
            printf("\nPlease provide a valid input!\n");
            user_input = get_int(hConsole);
        }

        switch (user_input)
        {
            // Adjust difficulty and print success message
            case EASY:
                *initial_sleep_time_ptr = EASY_SLEEP_TIME;
                *dynamic_obstacle_generation_prob_ptr = EASY_PROB;
                *dynamic_speed_mode_factor_ptr = EASY_FACTOR;
                printf("\nEASY Selected!\n\n");
            return;

            case MEDIUM:
                *initial_sleep_time_ptr = MEDIUM_SLEEP_TIME;
                *dynamic_obstacle_generation_prob_ptr = MEDIUM_PROB;
                *dynamic_speed_mode_factor_ptr = MEDIUM_FACTOR;
                printf("\nMEDIUM Selected!\n\n");
            return;

            case HARD:
                *initial_sleep_time_ptr = HARD_SLEEP_TIME;
                *dynamic_obstacle_generation_prob_ptr = HARD_PROB;
                *dynamic_speed_mode_factor_ptr = HARD_FACTOR;;
                printf("\nHARD Selected!\n\n");
                return;

            case INFO:
                printf("\n");
                print_easy_info();
                print_medium_info();
                print_hard_info();
                printf("\n");
                break;
        }
    }
}


void adjust_board_size(int *m_ptr, int *n_ptr, HANDLE hConsole)
{
    // Print current board size
    switch(*m_ptr)
    {
        case SMALL_ROWS:
            printf("Current Board Size: SMALL\n\n");
            break;

        case MEDIUM_ROWS:
            printf("Current Board Size: MEDIUM\n\n");
            break;

        case LARGE_ROWS:
            printf("Current Board Size: LARGE\n\n");
            break;
    }

    printf("[1] SMALL\n");
    printf("[2] MEDIUM\n");
    printf("[3] LARGE\n");

    // Get user's input
    int user_input = get_int(hConsole);
    while (user_input != SMALL && user_input != MEDIUM && user_input != LARGE)
    {
        printf("\nPlease provide a valid input!\n");
        user_input = get_int(hConsole);
    }

    switch (user_input)
    {
        // Adjust board size and print success message
        case EASY:
            *m_ptr = SMALL_ROWS;
            *n_ptr = SMALL_COLS;
            printf("\nSMALL Selected!\n\n");
            break;

        case MEDIUM:
            *m_ptr = MEDIUM_ROWS;
            *n_ptr = MEDIUM_COLS;
            printf("\nMEDIUM Selected!\n\n");
            break;

        case HARD:
            *m_ptr = LARGE_ROWS;
            *n_ptr = LARGE_COLS;
            printf("\nLARGE Selected!\n\n");
            break;
    }

}


void toggle_mode(int *is_mode_ptr, char *mode, HANDLE hConsole)
{
    // Print mode adjustment instructions
    switch (*is_mode_ptr)
    {
        case DISABLED:
            printf("%s Mode is disabled!\n");
            printf("Press 1 to enabled it, or 0 to remain it disabled:\n");
            break;

        case ENABLED:
            printf("%s Mode is enabled!\n");
            printf("Press 0 to disable it, or 1 to remain it enabled:\n");
            break;
    }

    // Get user's input
    int user_input = get_int(hConsole);
    while (user_input != DISABLED && user_input != ENABLED)
    {
        printf("\nPlease provide a valid input!\n");
        user_input = get_int(hConsole);
    }

    *is_mode_ptr = user_input;

    // Print success message
    switch (*is_mode_ptr)
    {
        case DISABLED:
            printf("\n%s Mode disabled!\n\n", mode);
            break;

        case ENABLED:
            printf("\n%s Mode enabled!\n\n", mode);
            break;
    }
}


void toggle_dynamic_speed_mode(int *is_dynamic_speed_mode_ptr, HANDLE hConsole)
{
    Sleep(DELAY);
    toggle_mode(is_dynamic_speed_mode_ptr, "Dynamic Speed", hConsole);
    Sleep(DELAY);
}


void toggle_invisible_walls_mode(int *is_invisible_walls_mode_ptr, HANDLE hConsole)
{
    Sleep(DELAY);
    toggle_mode(is_invisible_walls_mode_ptr, "Invisible Walls", hConsole);
    Sleep(DELAY);
}


void settings(int *m_ptr, int *n_ptr, int *initial_sleep_time_ptr, float *dynamic_obstacle_generation_prob_ptr,
              float *dynamic_speed_mode_factor_ptr, int *is_dynamic_speed_mode_ptr, int *is_invisible_walls_mode_ptr)
{
    print_settings_menu();

    // Used for flushing the input buffer (before using scanf)
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);

    while (true)
    {
        char user_input = get_user_input();

        if (user_input == DIFFICULTY || user_input == BOARD_SIZE ||
            user_input == DYNAMIC_SPEED_MODE || user_input == WALLS_MODE)
        {
            print_settings_menu();
        }

        switch (user_input)
        {
            case DIFFICULTY:
                adjust_game_difficulty(initial_sleep_time_ptr, dynamic_obstacle_generation_prob_ptr,
                                       dynamic_speed_mode_factor_ptr, hConsole);
                break;

            case BOARD_SIZE:
                adjust_board_size(m_ptr, n_ptr, hConsole);
                break;

            case DYNAMIC_SPEED_MODE:
                toggle_dynamic_speed_mode(is_dynamic_speed_mode_ptr, hConsole);
                break;

            case WALLS_MODE:
                toggle_invisible_walls_mode(is_invisible_walls_mode_ptr, hConsole);
                break;

            case BACK:
                Sleep(DELAY);
                return;
        }
    }
}