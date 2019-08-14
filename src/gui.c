/**
 * @file gui.c
 * @brief Functions to draw the GUI.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

/**
 * @addtogroup Utils
 * @{
 */
#include <ncurses.h>

#include "shared.h"
#include "gui.h"


#define CHAR_PER_CELL 2 /**<@brief Number of horizontal characters to represent a cell of the game area. */

#define CURR_HEIGHT 24 /**< @brief Height of the main game area. */
#define CURR_WIDTH 24 /**< @brief Width of the main game area. */
#define NEXT_HEIGHT 7 /**< @brief Height of the next-block game area. */
#define NEXT_WIDTH 12 /**< @brief Width of the next-block game area. */
#define STATS_HEIGHT 3 /**< @brief Height of the game statistics windows. */
#define STATS_WIDTH 12 /**< @brief Width of the game statistics windows. */
#define HELP_HEIGHT 3 /**< @brief Height of the help box. */
#define HELP_WIDTH 30 /**< @brief Width of the help box. */
#define GAME_MENU_HEIGHT 5 /**< @brief Height of the game menu. */
#define GAME_MENU_WIDTH 14 /**< @brief Width of the game menu. */
#define MENU_BUTTON_HEIGHT 3 /**< @brief Height of main menu buttons. */
#define MENU_BUTTON_WIDTH 17 /**< @brief Width of main menu buttons. */
#define OPTIONS_HEIGHT 8 /**< @brief Height of options menu. */
#define OPTIONS_WIDTH 24 /**< @brief Width of options menu. */
#define RULES_HEIGHT 16 /**< @brief Height of the rules box. */
#define RULES_WIDTH 50 /**< @brief Width of the rules box. */
#define GAME_OVER_HEIGHT 4 /**< @brief Height of the game over menu. */
#define GAME_OVER_WIDTH 14 /**< @brief Width of the game over menu. */
#define GLOBAL_HEIGHT CURR_HEIGHT + HELP_HEIGHT + 2 /**< @brief Height of the global window. */
#define GLOBAL_WIDTH NEXT_WIDTH + CURR_WIDTH + STATS_WIDTH + 2 /**< @brief Width of the global window. */
#define TITLE_HEIGHT 7 /**< @brief Height of the title. */
#define TITLE_WIDTH CURR_WIDTH + STATS_WIDTH + NEXT_WIDTH + 2 /**< @brief Width of the title. */

/** @brief ASCII art of the title. */
#define TITLE " _______     _        _        ____\n"\
              "      /__   __/  _| |_     |_|      / ___\\\n"\
              "         | | ___/_   _/___  _   __ / /\n"\
              "         | |/ _ \\ | | |  _/| | / _/| |\n"\
              "         | || __/ | | | |  | | \\ \\ \\ \\___\n"\
              "         |_|\\___| |_| |_|  |_|/__/  \\____/\n"

/**
 * @enum gui_color
 * @brief Global colors of the GUI.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum gui_color {
    GUI_COLOR_DEFAULT = 17,
    GUI_COLOR_BLUE,
    GUI_COLOR_BLACK
};

/**
 * @enum color
 * @brief Used colors.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum color {
    COLOR_NEW_BLACK = 20,
    COLOR_NEW_WHITE,
    COLOR_NEW_RED,
    COLOR_NEW_GREEN,
    COLOR_NEW_BLUE,
    COLOR_NEW_CYAN,
    COLOR_NEW_ORANGE,
    COLOR_NEW_YELLOW,
    COLOR_NEW_PURPLE,
    COLOR_NEW_DARK_PURPLE,
    COLOR_NEW_PINK,
    COLOR_NEW_BROWN,
};

// menu windows
static WINDOW *global_win;
static WINDOW *options_win;
static WINDOW *rules_win;
static WINDOW *new_game_button;
static WINDOW *options_button;
static WINDOW *rules_button;
static WINDOW *quit_button;

// game windows
static WINDOW *curr_field_win;
static WINDOW *next_field_win;
static WINDOW *level_win;
static WINDOW *score_win;
static WINDOW *rows_win;
static WINDOW *help_win;
static WINDOW *game_menu_win;
static WINDOW *game_over_win;

// GUI element selectors
static int main_menu_select;
static int options_select;
static int ghost_select;
static int color_select;
static int rules_page_select;
static int game_menu_select;
static int game_over_select;

static int global_color; /**< @brief Global GUI color. */

void init_colors() {
    start_color();
    // RGB colors scaled within the range [0, 1000]
    init_color(COLOR_NEW_BLACK, 0, 0, 0);
    init_color(COLOR_NEW_WHITE, 1000, 1000, 1000);
    init_color(COLOR_NEW_RED, 1000, 0, 0);
    init_color(COLOR_NEW_GREEN, 0, 1000, 0);
    init_color(COLOR_NEW_BLUE, 0, 0, 1000);
    init_color(COLOR_NEW_CYAN, 0, 1000, 1000);
    init_color(COLOR_NEW_ORANGE, 1000, 400, 0);
    init_color(COLOR_NEW_YELLOW, 1000, 1000, 0);
    init_color(COLOR_NEW_PURPLE, 796, 0, 796);
    init_color(COLOR_NEW_DARK_PURPLE, 187, 39, 140);
    init_color(COLOR_NEW_PINK, 1000, 400, 1000);
    init_color(COLOR_NEW_BROWN, 644, 200, 164);

    // pairs of foreground color, background color
    init_pair(GUI_COLOR_DEFAULT, COLOR_NEW_WHITE, COLOR_NEW_DARK_PURPLE);
    init_pair(GUI_COLOR_BLUE, COLOR_NEW_WHITE, COLOR_NEW_BLUE);
    init_pair(GUI_COLOR_BLACK, COLOR_NEW_WHITE, COLOR_NEW_BLACK);
    init_pair(BG, COLOR_NEW_BLACK, COLOR_NEW_BLACK);
    init_pair(F, COLOR_NEW_BLACK, COLOR_NEW_PINK);
    init_pair(F_R, COLOR_NEW_BLACK, COLOR_NEW_PINK);
    init_pair(I, COLOR_NEW_BLACK, COLOR_NEW_PURPLE);
    init_pair(L, COLOR_NEW_BLACK, COLOR_NEW_RED);
    init_pair(L_R, COLOR_NEW_BLACK, COLOR_NEW_RED);
    init_pair(N, COLOR_NEW_BLACK, COLOR_NEW_ORANGE);
    init_pair(N_R, COLOR_NEW_BLACK, COLOR_NEW_ORANGE);
    init_pair(P, COLOR_NEW_BLACK, COLOR_NEW_CYAN);
    init_pair(P_R, COLOR_NEW_BLACK, COLOR_NEW_CYAN);
    init_pair(T, COLOR_NEW_BLACK, COLOR_NEW_GREEN);
    init_pair(U, COLOR_NEW_BLACK, COLOR_NEW_WHITE);
    init_pair(W, COLOR_NEW_BLACK, COLOR_NEW_BROWN);
    init_pair(Y, COLOR_NEW_BLACK, COLOR_NEW_YELLOW);
    init_pair(Y_R, COLOR_NEW_BLACK, COLOR_NEW_YELLOW);
    init_pair(I_SHORT, COLOR_NEW_BLACK, COLOR_NEW_PURPLE);
    init_pair(GHOST, COLOR_NEW_WHITE, COLOR_NEW_DARK_PURPLE);
}

void init_windows() {
    main_menu_select = NEW_GAME;
    options_select = OPTION_GHOST;
    ghost_select = OPT_GHOST_ON;
    color_select = OPT_COLOR_DEFAULT;
    rules_page_select = RULES_PAGE_1;
    game_menu_select = MENU_PLAY;
    game_over_select = GAME_OVER_RESTART;
    global_color = GUI_COLOR_DEFAULT;

    // reference position to center the interface: refer to curr_field_win (double horizontal characters)
    int curr_x = (COLS - CURR_WIDTH) / 2;
    int curr_y = (LINES - CURR_HEIGHT - HELP_HEIGHT) / 2;

    global_win = newwin(GLOBAL_HEIGHT, GLOBAL_WIDTH, curr_y - 1, curr_x - NEXT_WIDTH - 1);

    options_win = newwin(OPTIONS_HEIGHT, OPTIONS_WIDTH, (LINES - OPTIONS_HEIGHT) / 2, (COLS - OPTIONS_WIDTH) / 2);
    
    rules_win = newwin(RULES_HEIGHT, RULES_WIDTH, (LINES - RULES_HEIGHT) / 2, (COLS - RULES_WIDTH) / 2);

    new_game_button = newwin(MENU_BUTTON_HEIGHT, MENU_BUTTON_WIDTH, curr_y + 10, curr_x - (MENU_BUTTON_WIDTH - CURR_WIDTH) / 2);
    
    options_button = newwin(MENU_BUTTON_HEIGHT, MENU_BUTTON_WIDTH, curr_y + 10 + 1 + MENU_BUTTON_HEIGHT, curr_x - (MENU_BUTTON_WIDTH - CURR_WIDTH) / 2);

    rules_button = newwin(MENU_BUTTON_HEIGHT, MENU_BUTTON_WIDTH, curr_y + 10 + 2 + 2*MENU_BUTTON_HEIGHT, curr_x - (MENU_BUTTON_WIDTH - CURR_WIDTH) / 2);
   
    quit_button = newwin(MENU_BUTTON_HEIGHT, MENU_BUTTON_WIDTH, curr_y + 10 + 3 + 3*MENU_BUTTON_HEIGHT, curr_x - (MENU_BUTTON_WIDTH - CURR_WIDTH) / 2);

    curr_field_win = newwin(CURR_HEIGHT, CURR_WIDTH, curr_y, curr_x);

    next_field_win = newwin(NEXT_HEIGHT, NEXT_WIDTH, curr_y, curr_x - NEXT_WIDTH);

    level_win = newwin(STATS_HEIGHT, STATS_WIDTH, curr_y, curr_x + CURR_WIDTH);

    score_win = newwin(STATS_HEIGHT, STATS_WIDTH, curr_y + STATS_HEIGHT, curr_x + CURR_WIDTH);

    rows_win = newwin(STATS_HEIGHT, STATS_WIDTH, curr_y + 2*STATS_HEIGHT, curr_x + CURR_WIDTH);

    help_win = newwin(HELP_HEIGHT, HELP_WIDTH, curr_y + CURR_HEIGHT, curr_x - (HELP_WIDTH - CURR_WIDTH) / 2);

    game_menu_win = newwin(GAME_MENU_HEIGHT, GAME_MENU_WIDTH, (LINES - GAME_MENU_HEIGHT) / 2, (COLS - GAME_MENU_WIDTH) / 2);
  
    game_over_win = newwin(GAME_OVER_HEIGHT, GAME_OVER_WIDTH, (LINES - GAME_OVER_HEIGHT) / 2, (COLS - GAME_OVER_WIDTH) / 2);
}

void refresh_global_win() {
    wbkgd(stdscr, COLOR_PAIR(global_color));
    refresh();
    wbkgd(global_win, COLOR_PAIR(global_color));
    mvwprintw(global_win, 1, 6, TITLE);
    box(global_win, 0, 0);
    wrefresh(global_win);
}

void refresh_main_menu() {
    wbkgd(new_game_button, COLOR_PAIR(global_color));
    box(new_game_button, 0, 0);
    if (main_menu_select == NEW_GAME) {
        wattron(new_game_button, A_STANDOUT);
    }
    mvwprintw(new_game_button, 1, 5, "NEW GAME");
    wattroff(new_game_button, A_STANDOUT);

    wbkgd(options_button, COLOR_PAIR(global_color));
    box(options_button, 0, 0);
    if (main_menu_select == OPTIONS) {
        wattron(options_button, A_STANDOUT);
    }
    mvwprintw(options_button, 1, 5, "OPTIONS");
    wattroff(options_button, A_STANDOUT);
   
    wbkgd(rules_button, COLOR_PAIR(global_color));
    box(rules_button, 0, 0);
    if (main_menu_select == RULES) {
        wattron(rules_button, A_STANDOUT);
    }
    mvwprintw(rules_button, 1, 6, "RULES");
    wattroff(rules_button, A_STANDOUT);

    wbkgd(quit_button, COLOR_PAIR(global_color));
    box(quit_button, 0, 0);
    if (main_menu_select == QUIT) {
        wattron(quit_button, A_STANDOUT);
    }
    mvwprintw(quit_button, 1, 6, "EXIT");
    wattroff(quit_button, A_STANDOUT);

    wrefresh(new_game_button);
    wrefresh(options_button);
    wrefresh(rules_button);
    wrefresh(quit_button);
}

void refresh_curr_field_win(Field *f) {
    // background color
    wbkgd(curr_field_win, COLOR_PAIR(global_color));
    // border
    box(curr_field_win, 0, 0);
    int row, col;
    int color;
    for (row = 0; row < f->rows; row++) {
        for (col = 0; col < f->cols; col++) {
            color = f->grid[row][col];
            wattrset(curr_field_win, COLOR_PAIR(color));
            if (color != BG) {
                mvwprintw(curr_field_win, row + 1, CHAR_PER_CELL*col + 1, "..");
            }
            else {
                mvwprintw(curr_field_win, row + 1, CHAR_PER_CELL*col + 1, "  ");
            }
        }
    }
    wrefresh(curr_field_win);
}

void refresh_next_field_win(Field *f) {
    wbkgd(next_field_win, COLOR_PAIR(global_color));
    box(next_field_win, 0, 0);
    mvwprintw(next_field_win, 0, 4, "Next");
    int row, col;
    int color;
    for (row = 0; row < f->rows; row++) {
        for (col = 0; col < f->cols; col++) {
            color = f->grid[row][col];
            wattrset(next_field_win, COLOR_PAIR(color));
            if (color != BG) {
                mvwprintw(next_field_win, row + 1, CHAR_PER_CELL*col + 1, "..");
            }
            else {
                mvwprintw(next_field_win, row + 1, CHAR_PER_CELL*col + 1, "  ");
            }
        }
    }
    wrefresh(next_field_win);
}

void refresh_stats_win(int level, int score, int rows) {
    wbkgd(level_win, COLOR_PAIR(global_color));
    box(level_win, 0, 0);
    mvwprintw(level_win, 0, 4, "Level");
    mvwprintw(level_win, 1, 5, "%02d", level);

    wbkgd(score_win, COLOR_PAIR(global_color));
    box(score_win, 0, 0);
    mvwprintw(score_win, 0, 4, "Score");
    mvwprintw(score_win, 1, 4, "%05d", score);

    wbkgd(rows_win, COLOR_PAIR(global_color));
    box(rows_win, 0, 0);
    mvwprintw(rows_win, 0, 4, "Rows");
    mvwprintw(rows_win, 1, 5, "%03d", rows);

    wrefresh(level_win);
    wrefresh(score_win);
    wrefresh(rows_win);
}

void refresh_help_win() {
    wbkgd(help_win, COLOR_PAIR(global_color));
    box(help_win, 0, 0);
    mvwprintw(help_win, 1, 3, "Press P to open the menu");

    wrefresh(help_win);
}

void refresh_options_win() {
    wbkgd(options_win, COLOR_PAIR(global_color));
    box(options_win, 0, 0 );

    mvwprintw(options_win, 0, 9, "OPTIONS");
    mvwprintw(options_win, 2, 2, "Ghost:");
    mvwprintw(options_win, 4, 2, "Color:");

    if (options_select == OPTION_GHOST) {
        wattron(options_win, A_STANDOUT);
    }
    switch (ghost_select) {
        case OPT_GHOST_ON:
            mvwprintw(options_win, 2, 11, "<   On    >");
            break;
        case OPT_GHOST_OFF:
            mvwprintw(options_win, 2, 11, "<   Off   >");
            break;
    }
    wattroff(options_win, A_STANDOUT);
    
    if (options_select == OPTION_COLOR) {
        wattron(options_win, A_STANDOUT);
    }
    switch (color_select) {
        case OPT_COLOR_DEFAULT:
            mvwprintw(options_win, 4, 11, "< Default >");
            break;
        case OPT_COLOR_BLUE:
            mvwprintw(options_win, 4, 11, "<  Blue   >");
            break;
        case OPT_COLOR_BLACK:
            mvwprintw(options_win, 4, 11, "<  Black  >");
            break;
    }
    wattroff(options_win, A_STANDOUT);

    if (options_select == OPTION_OK) {
        wattron(options_win, A_STANDOUT);
    }
    mvwprintw(options_win, 6, 11, "OK");
    wattroff(options_win, A_STANDOUT);

    wrefresh(options_win);
}

void refresh_rules_win() {
    // cancella il contenuto
    werase(rules_win);
    wbkgd(rules_win, COLOR_PAIR(global_color));
    box(rules_win, 0, 0 );
    mvwprintw(rules_win, 0, 22, "RULES");

    if (rules_page_select == RULES_PAGE_1) {
        mvwprintw(rules_win, 2, 2, "The goal of the game consists in positioning");
        mvwprintw(rules_win, 4, 2, "each block without leaving holes. The complet-");
        mvwprintw(rules_win, 6, 2, "ed rows are removed and the player gets points.");
        mvwprintw(rules_win, 8, 2, "If multiple rows are completed simultaneously,");
        mvwprintw(rules_win, 10, 2, "bonus points are obtained. By disabling the");
        mvwprintw(rules_win, 12, 2, "option \'Ghost\', the points are doubled.");
        wattron(rules_win, A_STANDOUT);
        mvwprintw(rules_win, 14, 23, "Next");
        wattroff(rules_win, A_STANDOUT);
    }
    else if (rules_page_select == RULES_PAGE_2) {
        mvwprintw(rules_win, 2, 14, "P  open the menu");
        mvwprintw(rules_win, 4, 5, "Left arrow  move block to the left");
        mvwprintw(rules_win, 6, 4, "Right arrow  move block to the right");
        mvwprintw(rules_win, 8, 7, "Up arrow  rotate block");
        mvwprintw(rules_win, 10, 5, "Down arrow  move block down");
        mvwprintw(rules_win, 12, 10, "Space  make the block fall fast");
        wattron(rules_win, A_STANDOUT);
        mvwprintw(rules_win, 14, 24, "OK");
        wattroff(rules_win, A_STANDOUT);
    }
    wrefresh(rules_win);
}

void refresh_game_menu() {
    wbkgd(game_menu_win, COLOR_PAIR(global_color));
    box(game_menu_win, 0, 0 );
    mvwprintw(game_menu_win, 0, 5, "MENU");

    if (game_menu_select == MENU_PLAY) {
        wattron(game_menu_win, A_STANDOUT);
    }
    mvwprintw(game_menu_win, 1, 4, "Resume");
    wattroff(game_menu_win, A_STANDOUT);
            
    if (game_menu_select == MENU_RESTART) {
        wattron(game_menu_win, A_STANDOUT);
    }
    mvwprintw(game_menu_win, 2, 4, "Restart");
    wattroff(game_menu_win, A_STANDOUT);

    if (game_menu_select == MENU_BACK) {
        wattron(game_menu_win, A_STANDOUT);
    }
    mvwprintw(game_menu_win, 3, 5, "Exit");
    wattroff(game_menu_win, A_STANDOUT);      

    wrefresh(game_menu_win);
}

void refresh_game_over_win() {
    wbkgd(game_over_win, COLOR_PAIR(global_color));
    box(game_over_win, 0, 0 );
    mvwprintw(game_over_win, 0, 3, "GAME OVER");
 
    if (game_over_select == GAME_OVER_RESTART) {
        wattron(game_over_win, A_STANDOUT);
    }
    mvwprintw(game_over_win, 1, 4, "Restart");
    wattroff(game_over_win, A_STANDOUT);

    if (game_over_select == GAME_OVER_BACK) {
        wattron(game_over_win, A_STANDOUT);
    }
    mvwprintw(game_over_win, 2, 5, "Exit");
    wattroff(game_over_win, A_STANDOUT);

    wrefresh(game_over_win);
}

void reset_main_menu() {
    main_menu_select = NEW_GAME;
   
}

void reset_options_win() {
    options_select = OPTION_GHOST;
}

void reset_rules_win() {
    rules_page_select = RULES_PAGE_1;
}

void reset_game_menu() {
    game_menu_select = MENU_PLAY; 
}

void reset_game_over_win() {
    game_over_select = GAME_OVER_RESTART;
}

int scroll_down_main_menu() {
    main_menu_select++;
    // circular scroll
    main_menu_select %= QUIT + 1;
    return main_menu_select;
}

int scroll_up_main_menu() {
    main_menu_select--;
    main_menu_select += QUIT + 1;
    main_menu_select %= QUIT + 1;
    return main_menu_select;
}

int scroll_down_options_win() {
    options_select++;
    options_select %= OPTION_OK + 1;
    return options_select;
}

int scroll_up_options_win() {
    options_select--;
    options_select += OPTION_OK + 1;
    options_select %= OPTION_OK + 1;
    return options_select;
}

int scroll_right_option_ghost() {
    ghost_select++;
    ghost_select %= OPT_GHOST_OFF + 1;
    return ghost_select;
}

int scroll_left_option_ghost() {
    ghost_select--;
    ghost_select += OPT_GHOST_OFF + 1;
    ghost_select %= OPT_GHOST_OFF + 1;
    return ghost_select;
}

int scroll_right_option_color() {
    color_select++;
    color_select %= OPT_COLOR_BLACK + 1;
    return color_select;
}

int scroll_left_option_color() {
    color_select--;
    color_select += OPT_COLOR_BLACK + 1;
    color_select %= OPT_COLOR_BLACK + 1;
    return color_select;
}

int scroll_down_rules_win() {
    rules_page_select++;
    rules_page_select %= RULES_PAGE_2 + 1;
    return rules_page_select;
}

int scroll_down_game_menu() {
    game_menu_select++;
    game_menu_select %= MENU_BACK + 1;
    return game_menu_select;
}

int scroll_up_game_menu() {
    game_menu_select--;
    game_menu_select += MENU_BACK + 1;
    game_menu_select %= MENU_BACK + 1;
    return game_menu_select;
}

int scroll_down_game_over_win() {
    game_over_select++;
    game_over_select %= GAME_OVER_BACK + 1;
    return game_over_select;
}

int scroll_up_game_over_win() {
    game_over_select--;
    game_over_select += GAME_OVER_BACK + 1;
    game_over_select %= GAME_OVER_BACK + 1;
    return game_over_select;
}

void change_global_color(int color) {
    switch (color) {
        case OPT_COLOR_DEFAULT:
            global_color = GUI_COLOR_DEFAULT;
            // update ghost background color
            init_pair(GHOST, COLOR_NEW_WHITE, COLOR_NEW_DARK_PURPLE);
            break;
        case OPT_COLOR_BLUE:
            global_color = GUI_COLOR_BLUE;
            init_pair(GHOST, COLOR_NEW_WHITE, COLOR_NEW_BLUE);
            break;
         case OPT_COLOR_BLACK:
            global_color = GUI_COLOR_BLACK;
            init_pair(GHOST, COLOR_NEW_WHITE, COLOR_NEW_BLACK);
            break;
    }
}
/** \} */
