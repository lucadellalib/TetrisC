/**
 * @file main.c
 * @brief Main.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

/**
 * \mainpage Documentation TetrisC
 * \section Requirements
 * - libncurses5 (`sudo apt-get install ncurses-dev` to install on Ubuntu 18.04 LTS);
 * - Check (`sudo apt-get install check` to install on Ubuntu 18.04 LTS);
 * - make (`sudo apt-get install make` to install on Ubuntu 18.04 LTS);
 * - CMake (`sudo apt-get -y install cmake` to install on Ubuntu 18.04 LTS);
 * - Doxygen (`sudo apt-get install doxygen` to install on Ubuntu 18.04 LTS).
 */

/**
 * @defgroup Game
 *
 * @brief Game functions and data structure.
 *
 */

/**
 * @defgroup Utils
 *
 * @brief Utility functions for drawing the GUI, and creating and handling the timer.
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>

#include "shared.h"
#include "field.h"
#include "block.h"
#include "timer.h"
#include "gui.h"


#define KEY_MENU 112 /**< @brief Key P. */
#define KEY_RETURN '\n' /**< @brief Key Enter. */
#define KEY_SPACE ' ' /**< @brief Key Space. */

#define LEVEL_CAP 10 /**< @brief Max level. */
#define ROWS_PER_LEVEL 5 /**< @brief Number of completed rows required to level up. */
#define SCORE_PER_ROW 100 /**< @brief Score for single row completed. */
#define BONUS_EXPONENT 2 /**< @brief Bonus for multiple rows completed. */
#define BONUS_GHOST_OFF 2 /**< @brief Bonus for disabling 'Ghost' option. */

#define INIT_VALUE_MILLIS 800 /**< @brief Initial block fall interval in milliseconds. */
#define INTERVAL_REDUCTION_PER_LEVEL_MILLIS 50 /**< @brief Interval per level to subtract from the current one in milliseconds. */

/**
 * @enum game_status
 * @brief Game status.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum game_status {
    GAME_RUNNING,
    GAME_MENU,
    GAME_OVER
};

// statistics
static int level;
static int rows;
static int score;
static int status;

// game areas
static Field *curr_field;
static Field *next_field;

// blocks
static Block *curr_block;
static Block *ghost_block;
static Block *next_block;

// options
static int option_ghost;
static int option_color;

/**
 * @brief Create new block.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
static void drop_block() {
    // init ghost if the option is enabled
    if (option_ghost == OPT_GHOST_ON) {
        init_ghost_block(ghost_block, next_block->type, next_block->rot, -BLOCK_MAX_SIZE, COLUMNS / 2);
        // move down to position the ghost
        while (can_move_block(ghost_block, curr_field, DOWN)) {
            move_block(ghost_block, curr_field, DOWN);
        }
        write_block(ghost_block, curr_field);                    
    }
    
    // init current block
    init_block(curr_block, next_block->type, next_block->rot, -BLOCK_MAX_SIZE, COLUMNS / 2);
    // move down until the first cell of the block appears on the screen
    while (get_limit_high_block(curr_block) < 0 && can_move_block(curr_block, curr_field, DOWN)) {
        move_block(curr_block, curr_field, DOWN);
    }
    write_block(curr_block, curr_field);

    // Init next block
    init_block(next_block, rand() % I_SHORT + 1, rand() % 4, BLOCK_MAX_SIZE / 2, BLOCK_MAX_SIZE / 2);

    clear_field(next_field);
    write_block(next_block, next_field);

    refresh_curr_field_win(curr_field);
    refresh_next_field_win(next_field);
}

/**
 * @brief Function to handle the tick of the timer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
static void timer_handler() {
    if (can_move_block(curr_block, curr_field, DOWN)) {
        move_block(curr_block, curr_field, DOWN);
        refresh_curr_field_win(curr_field);
    }
    else {
        stop_timer();
        // check if the whole block appears on the screen: if not it is game over
        if (get_limit_low_block(curr_block) < 0) {
            status = GAME_OVER;
            reset_game_over_win();
            refresh_game_over_win();
            return;
        }

        // find completed rows to delete by checking the ones occupied by curr_block
        int row_to_clear = find_row_field(curr_field, get_limit_low_block(curr_block), get_limit_high_block(curr_block));
        // count rows completed simultaneously
        int rows_count = 0;
        while (row_to_clear != -1) {
            clear_row_field(curr_field, row_to_clear);
            rows++;
            // level up
            if (rows % ROWS_PER_LEVEL == 0 && level < LEVEL_CAP) {
                level++;
            }
            rows_count++;
            row_to_clear = find_row_field(curr_field, get_limit_low_block(curr_block), get_limit_high_block(curr_block));
        }

        // update score with bonus
        int bonus = (option_ghost == OPT_GHOST_OFF) ? BONUS_GHOST_OFF : 1;
        score += SCORE_PER_ROW*(int)pow(rows_count, BONUS_EXPONENT)*bonus;

        refresh_stats_win(level, score, rows);

        // drop new block
        drop_block();
        // restart timer
        start_timer(INIT_VALUE_MILLIS - INTERVAL_REDUCTION_PER_LEVEL_MILLIS*(level - 1));
    }
}

/**
 * @brief Init game.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
static void init_game() {
    level = 1;
    rows = 0;
    score = 0;

    init_field(curr_field, ROWS, COLUMNS);
    init_field(next_field, BLOCK_MAX_SIZE, BLOCK_MAX_SIZE);

    init_block(next_block, rand() % I_SHORT + 1, rand() % 4, BLOCK_MAX_SIZE / 2, BLOCK_MAX_SIZE / 2);

    drop_block();

    refresh_help_win();
    refresh_curr_field_win(curr_field);
    refresh_next_field_win(next_field);
    refresh_stats_win(level, score, rows);
}

/**
 * @brief Update 'Ghost'.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
static void update_ghost() {
    update_block(ghost_block, curr_field, curr_block->rot, curr_block->row, curr_block->col);
    while (can_move_block(ghost_block, curr_field, DOWN)) {
        move_block(ghost_block, curr_field, DOWN);
    }
    // update curr_block to prevent the ghost from overwriting it in case of superposition
    update_block(curr_block, curr_field, curr_block->rot, curr_block->row, curr_block->col);
}

/**
 * @brief Fix block position after failed rotation.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
static void fix_block_position() {
    // if possible, move left
    if (can_move_block(curr_block, curr_field, LEFT)) {
        move_block(curr_block, curr_field, LEFT);
        // if possible, rotate
        if (can_rotate_block(curr_block, curr_field)) {
            rotate_block(curr_block, curr_field);
        }
        // if possible, move left again
        else if (can_move_block(curr_block, curr_field, LEFT)) {
            move_block(curr_block, curr_field, LEFT);
            // if possible, rotate
            if (can_rotate_block(curr_block, curr_field)) {
                rotate_block(curr_block, curr_field);
            }
            // otherwise reset it to the initial position, by moving it twice to the right
            else {
                move_block(curr_block, curr_field, RIGHT);
                move_block(curr_block, curr_field, RIGHT);
            }
        }
        else {
            // otherwise reset it to the initial position, by moving it once to the right
            move_block(curr_block, curr_field, RIGHT); 
        }
    }

    // if possible, move right
    if (can_move_block(curr_block, curr_field, RIGHT)) {
        move_block(curr_block, curr_field, RIGHT);
        // if possible, rotate
        if (can_rotate_block(curr_block, curr_field)) {
            rotate_block(curr_block, curr_field);
        }
        // if possible, move right again
        else if (can_move_block(curr_block, curr_field, RIGHT)) {
            move_block(curr_block, curr_field, RIGHT);
            // if possible, rotate
            if (can_rotate_block(curr_block, curr_field)) {
                rotate_block(curr_block, curr_field);
            }
            // otherwise reset it to the initial position, by moving it twice to the left
            else {
                move_block(curr_block, curr_field, LEFT);
                move_block(curr_block, curr_field, LEFT);
            }
        }
        else {
            // otherwise reset it to the initial position, by moving it once to the left
            move_block(curr_block, curr_field, LEFT);
            // the block cannot rotate, even after repositioning
        }
    }
}

/**
 * @brief Main game loop.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
static void game_loop() {
    curr_field = create_field();
    next_field = create_field();

    curr_block = create_block();
    if (option_ghost == OPT_GHOST_ON) {
        ghost_block = create_block();
    }
    next_block = create_block();
    
    // init random number generator
    srand(time(NULL));

    init_game();

    make_timer(timer_handler);
    start_timer(INIT_VALUE_MILLIS);

    // menu selectors
    int menu_selection = MENU_PLAY;
    int game_over_selection = GAME_OVER_RESTART;
    int ch;
    // input routine
    while (ch = getch()) {
        if (status == GAME_RUNNING) {
            switch (ch) {
                case KEY_UP:
                    // rotate
                    if (can_rotate_block(curr_block, curr_field)) {
                        rotate_block(curr_block, curr_field);
                        if (option_ghost == OPT_GHOST_ON) {
                            update_ghost();
                        }
                        refresh_curr_field_win(curr_field);
                    }
                    else {
                        // fix block position
                        fix_block_position();
                        if (option_ghost == OPT_GHOST_ON) {
                            update_ghost();
                        }
                        refresh_curr_field_win(curr_field);
                    }
                    break;
                case KEY_DOWN:
                    // move down
                    if (can_move_block(curr_block, curr_field, DOWN)) {
                        move_block(curr_block, curr_field, DOWN);
                        if (option_ghost == OPT_GHOST_ON) {
                            update_ghost();
                        }
                        refresh_curr_field_win(curr_field);
                    }          
                    break;
                case KEY_LEFT:
                    // move left
                    if (can_move_block(curr_block, curr_field, LEFT)) {
                        move_block(curr_block, curr_field, LEFT);
                        if (option_ghost == OPT_GHOST_ON) {
                            update_ghost();
                        }
                        refresh_curr_field_win(curr_field);
                    }
                    break;
                case KEY_RIGHT:
                    // move right
                    if (can_move_block(curr_block, curr_field, RIGHT)) {
                        move_block(curr_block, curr_field, RIGHT);
                        if (option_ghost == OPT_GHOST_ON) {
                            update_ghost();
                        }
                        refresh_curr_field_win(curr_field);
                    }
                    break;
                case KEY_SPACE:
                    // fall instantaneously
                    while (can_move_block(curr_block, curr_field, DOWN)) {
                        move_block(curr_block, curr_field, DOWN);
                    }
                    if (option_ghost == OPT_GHOST_ON) {
                        update_ghost();
                    }
                    refresh_curr_field_win(curr_field);
                    break;
                case KEY_MENU:
                    // menu
                    stop_timer();
                    status = GAME_MENU;
                    refresh_game_menu();
            }
        }
        else if (status == GAME_MENU) {      
                switch (ch) {
                    case KEY_UP:
                        menu_selection = scroll_up_game_menu();
                        refresh_game_menu();
                        break;
                    case KEY_DOWN:
                        menu_selection = scroll_down_game_menu();
                        refresh_game_menu();
                        break;
                    case KEY_RETURN:
                        switch (menu_selection) {
                            case MENU_PLAY:
                                refresh_help_win();
                                refresh_curr_field_win(curr_field);
                                refresh_next_field_win(next_field);
                                refresh_stats_win(level, score, rows);
                                reset_game_menu();
                                status = GAME_RUNNING;
                                start_timer(INIT_VALUE_MILLIS - INTERVAL_REDUCTION_PER_LEVEL_MILLIS*(level - 1));
                                break;
                            case MENU_RESTART:
                                init_game();
                                reset_game_menu();
                                status = GAME_RUNNING;
                                start_timer(INIT_VALUE_MILLIS);
                                menu_selection = MENU_PLAY;
                                break;
                            case MENU_BACK:
                                delete_field(curr_field);
                                delete_field(next_field);
                                delete_block(curr_block);
                                if (option_ghost == OPT_GHOST_ON) {
                                    delete_block(ghost_block);
                                }
                                delete_block(next_block);
                                delete_timer();
                                reset_game_menu();
                                refresh_global_win();
                                refresh_main_menu();
                                return;
                        }
                        break;
                }  
        }
        else if (status == GAME_OVER) {
            switch (ch) {
                case KEY_UP:
                    game_over_selection = scroll_up_game_over_win();
                    refresh_game_over_win();
                    break;
                case KEY_DOWN:
                    game_over_selection = scroll_down_game_over_win();
                    refresh_game_over_win();
                    break;
                case KEY_RETURN:
                    switch (game_over_selection) {
                        case GAME_OVER_RESTART:
                            status = GAME_RUNNING;
                            init_game();
                            reset_game_menu();
                            start_timer(INIT_VALUE_MILLIS);
                            game_over_selection = GAME_OVER_RESTART;
                            break;
                        case GAME_OVER_BACK:
                            delete_field(curr_field);
                            delete_field(next_field);
                            delete_block(curr_block);
                            if (option_ghost == OPT_GHOST_ON) {
                                delete_block(ghost_block);
                            }
                            delete_block(next_block);
                            delete_timer();
                            reset_game_menu();
                            refresh_global_win();
                            refresh_main_menu();
                            return;
                    }
                    break;
            }
        } 
    }
}

/**
 * @brief Game routine.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
int main() {
    // init window mode of ncurses
    initscr();
    // hide cursor
    curs_set(0);
    // prevent pressed keys from writing on the terminal
    noecho();
    init_colors();
    // disable line buffering
    cbreak();
    // enable pressed keys acquisition
    keypad(stdscr, TRUE);

    // default options
    option_ghost = OPT_GHOST_ON;
    option_color = OPT_COLOR_DEFAULT;

    init_windows();
    refresh_global_win();
    refresh_main_menu();

    // init menu selectors
    int menu_selection = NEW_GAME;
    int options_selection = OPTION_GHOST;
    int ch;
    // input routine
    while (ch = getch()) {
        switch (ch) {
            case KEY_UP:
                menu_selection = scroll_up_main_menu();
                refresh_main_menu();
                break;
            case KEY_DOWN:
                menu_selection = scroll_down_main_menu();
                refresh_main_menu();
                break;
            case KEY_RETURN:
                switch (menu_selection) {
                    case NEW_GAME:
                        reset_main_menu();
                        status = GAME_RUNNING;
                        game_loop();
                        break;
                    case OPTIONS:
                        refresh_options_win();
                        while (ch = getch(), (ch != KEY_RETURN || options_selection != OPTION_OK)) {
                            switch (ch) {
                                case KEY_UP:
                                    options_selection = scroll_up_options_win();
                                    refresh_options_win();
                                    break;
                                case KEY_DOWN:
                                    options_selection = scroll_down_options_win();
                                    refresh_options_win();
                                    break;
                                case KEY_LEFT:
                                    if (options_selection == OPTION_GHOST) {
                                        option_ghost = scroll_left_option_ghost();
                                    }
                                    else if (options_selection == OPTION_COLOR) {
                                        option_color = scroll_left_option_color();
                                        change_global_color(option_color);
                                        refresh_global_win();
                                        refresh_main_menu();
                                    }
                                    refresh_options_win();
                                    break;
                                case KEY_RIGHT:
                                    if (options_selection == OPTION_GHOST) {
                                        option_ghost = scroll_right_option_ghost();
                                    }
                                    else if (options_selection == OPTION_COLOR) {
                                        option_color = scroll_right_option_color();
                                        change_global_color(option_color);
                                        refresh_global_win();
                                        refresh_main_menu();
                                    }
                                    refresh_options_win();
                                    break;
                            }
                        }
                        reset_options_win();
                        options_selection = OPTION_GHOST;
                        refresh_global_win();
                        refresh_main_menu();
                        break;
                    case RULES:
                        refresh_rules_win();
                        while (ch = getch(), ch != KEY_RETURN);
                        scroll_down_rules_win();
                        refresh_rules_win();
                        while (ch = getch(), ch != KEY_RETURN);
                        reset_rules_win();
                        refresh_global_win();
                        refresh_main_menu();
                        break;
                    case QUIT:
                        reset_main_menu();
                        // terminate window mode of ncurses
                        endwin();
                        return EXIT_SUCCESS;
                        break;
                }
                break;
        }
    }
}
