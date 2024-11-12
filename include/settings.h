#ifndef CS50_SETTINGS_H
#define CS50_SETTINGS_H


// Setting menu controls
#define DIFFICULTY '1'
#define BOARD_SIZE '2'
#define DYNAMIC_SPEED_MODE '3'
#define WALLS_MODE '4'
#define BACK 'b'
#define DELAY 50

// Mode values
#define DISABLED 0
#define ENABLED 1

// Board size values
#define SMALL 1
#define MEDIUM 2
#define LARGE 3
#define SMALL_ROWS 10
#define SMALL_COLS 30
#define MEDIUM_ROWS 15
#define MEDIUM_COLS 45
#define LARGE_ROWS 20
#define LARGE_COLS 60

// Difficulty menu values
#define EASY 1
#define MEDIUM 2
#define HARD 3
#define INFO 4

// Easy
#define EASY_SLEEP_TIME 150
#define EASY_PROB 0.1
#define EASY_FACTOR 1

// Medium
#define MEDIUM_SLEEP_TIME 100
#define MEDIUM_PROB 0.4
#define MEDIUM_FACTOR 1.1

// Hard
#define HARD_SLEEP_TIME 75
#define HARD_PROB 0.8
#define HARD_FACTOR 1.3


void settings(int *m_ptr, int *n_ptr, int *initial_sleep_time_ptr, float *dynamic_obstacle_generation_prob_ptr,
              float *dynamic_speed_mode_factor_ptr, int *is_dynamic_speed_mode_ptr, int *is_invisible_walls_mode_ptr);

#endif //CS50_SETTINGS_H
