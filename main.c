// libraries
#include <stdio.h>
#include <windows.h>
#include "helpers.h"
#include "settings.h"
#include "gameplay.h"

#define INITIAL_SLEEP_TIME 100
#define PLAY_GAME '1'
#define SETTINGS '2'
#define QUIT 'q'


int main(void)
{
    int m = MEDIUM_ROWS;
    int n = MEDIUM_COLS;
    int initial_sleep_time = MEDIUM_SLEEP_TIME;
    float dynamic_obstacle_generation_prob = MEDIUM_PROB;
    float dynamic_speed_mode_factor = MEDIUM_FACTOR;
    int is_dynamic_speed_mode = DISABLED;
    int is_invisible_walls_mode = DISABLED;

    bool print_flag = true;
    while (true)
    {
        if (print_flag)
        {
            system("cls");

            printf("====================================\n");
            printf("         WELCOME TO SNAKE GAME      \n");
            printf("====================================\n\n");
            printf("[1] Start Game          \n");
            printf("[2] Adjust Settings     \n");
            printf("[Q] Quit                \n\n");
            printf("====================================\n");

            print_flag = false;
        }

        switch (get_user_input())
        {
            case PLAY_GAME:
                Sleep(DELAY);
                gameplay(m, n, initial_sleep_time, dynamic_obstacle_generation_prob,
                          dynamic_speed_mode_factor, is_dynamic_speed_mode, is_invisible_walls_mode);
                Sleep(DELAY);
                print_flag = true;
                break;

            case SETTINGS:
                Sleep(DELAY);
                settings(&m, &n, &initial_sleep_time, &dynamic_obstacle_generation_prob,
                         &dynamic_speed_mode_factor, &is_dynamic_speed_mode, &is_invisible_walls_mode);

                print_flag = true;
                break;

            case QUIT:
                Sleep(DELAY);
                return 0;
        }
    }
}



