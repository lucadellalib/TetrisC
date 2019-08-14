/**
 * @file gui.h
 * @brief Functions to draw the GUI.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

#ifndef GUI_H
#define GUI_H

/**
 * @brief Init colors.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void init_colors();

/**
 * @brief Init windows.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void init_windows();

/**
 * @brief Update global window layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_global_win();

/**
 * @brief Update main menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_main_menu();

/**
 * @brief Update main game area layout.
 *
 * @param f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_curr_field_win(Field *f);

/**
 * @brief Update next-block area layout.
 *
 * @param f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_next_field_win(Field *f);

/**
 * @brief Update game statistics layout.
 *
 * @param level level.
 * @param score score.
 * @param rows number of total deleted rows.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_stats_win(int level, int score, int rows);

/**
 * @brief Update help box layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_help_win();

/**
 * @brief Update options menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_options_win();

/**
 * @brief Update rules box layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_rules_win();

/**
 * @brief Update game menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_game_menu();

/**
 * @brief Update game over menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void refresh_game_over_win();

/**
 * @brief Reset main menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void reset_main_menu();

/**
 * @brief Reset option menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void reset_options_win();

/**
 * @brief Reset rules box layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void reset_rules_win();

/**
 * @brief Reset game menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void reset_game_menu();

/**
 * @brief Reset game over menu layout.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void reset_game_over_win();

/**
 * @brief Scroll main menu down.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_down_main_menu();

/**
 * @brief Scroll main menu up.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_up_main_menu();

/**
 * @brief Scroll options menu down.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_down_options_win();

/**
 * @brief Scroll options menu up.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_up_options_win();

/**
 * @brief Scroll 'Ghost' option to the right.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_right_option_ghost();

/**
 * @brief Scroll 'Ghost' option to the left.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_left_option_ghost();

/**
 * @brief Scroll 'Color' option to the right.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_right_option_color();

/**
 * @brief Scroll 'Color' option to the left.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_left_option_color();

/**
 * @brief Scroll rules box down.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_down_rules_win();

/**
 * @brief Scroll game menu down.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_down_game_menu();

/**
 * @brief Scroll game menu up.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_up_game_menu();

/**
 * @brief Scroll game over menu down.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_down_game_over_win();

/**
 * @brief Scroll game over menu up.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int scroll_up_game_over_win();

/**
 * @brief Change GUI global color.
 *
 *@param color color
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void change_global_color(int color);

#endif
