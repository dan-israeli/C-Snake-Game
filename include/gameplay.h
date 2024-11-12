#ifndef CS50_PLAY_GAME_H
#define CS50_PLAY_GAME_H

// Board constants
#define GAME_START_MESSAGE "Press W, A, S, or D to start\n"
# define DELETE_GAME_START_MESSAGE "                                            "
#define GAME_END_MESSAGE "Game Over! Press 'B' to return to the main menu.\n"
#define MEMORY_ERROR "Memory error! Please close the game!\n"

// input
#define BACK 'b'
#define DELAY 50

void gameplay(int m, int n, int initial_sleep_time, float dynamic_obstacle_generation_prob,
               float initial_dynamic_speed_mode_factor, int is_dynamic_speed_mode, int is_invisible_walls_mode);


#endif //CS50_PLAY_GAME_H
