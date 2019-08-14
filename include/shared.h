/**
 * @file shared.h
 * @brief Shared macros, costants and data structures.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

#ifndef SHARED_H
#define SHARED_H

/**
 * @brief Terminate with an error message.
 *
 * @param msg message.
 */
#define ERROR_EXIT(msg) do { \
    perror(msg); \
    exit(EXIT_FAILURE); \
} while (0)

//                                                   MAIN_MENU
/*------------------------------------------------------------*/

/**
 * @addtogroup Utils
 * @{
 */

/**
 * @enum main_menu
 * @brief Elements of the main menu.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum main_menu {
    NEW_GAME,
    OPTIONS,
    RULES,
    QUIT
};

//                                                 OPTIONS_WIN
/*------------------------------------------------------------*/

/**
 * @enum options
 * @brief Elements of the option menu.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum options {
    OPTION_GHOST,
    OPTION_COLOR,
    OPTION_OK
};

//                                                     OPTIONS
/*------------------------------------------------------------*/

/**
 * @enum ghost_option
 * @brief Values of 'Ghost' option.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum ghost_option {
    OPT_GHOST_ON,
    OPT_GHOST_OFF
};

/**
 * @enum color_option
 * @brief Values of 'Color' option.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum color_option {
    OPT_COLOR_DEFAULT,
    OPT_COLOR_BLUE,
    OPT_COLOR_BLACK
};

//                                                       RULES
/*------------------------------------------------------------*/

/**
 * @enum rules
 * @brief Rules box pages.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum rules {
    RULES_PAGE_1,
    RULES_PAGE_2
};

//                                                   GAME_MENU
/*------------------------------------------------------------*/

/**
 * @enum game_menu
 * @brief Elements of game menu.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum game_menu {
    MENU_PLAY,
    MENU_RESTART,
    MENU_BACK
};

//                                              GAME_OVER_MENU
/*------------------------------------------------------------*/

/**
 * @enum game_over
 * @brief Elements of game over menu.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum game_over {
    GAME_OVER_RESTART,
    GAME_OVER_BACK
};
/** \} */

//                                                       FIELD
/*------------------------------------------------------------*/

/**
 * @addtogroup Game
 * @{
 */
#define ROWS 22 /**< @brief Number of rows of the game area. */
#define COLUMNS 11 /**< @brief Number of columns of the game area. */
#define BLOCK_MAX_SIZE 5 /**< @brief Max number of cells that constitute a block. */

/**
 * @struct Field
 * @brief Structure to represent a game area.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
typedef struct {
    int rows; /**< @brief Number of rows. */
    int cols; /**< @brief Number of columns. */
    int grid[ROWS][COLUMNS]; /**< @brief 2D matrix. */
} Field;

//                                                       BLOCK
/*------------------------------------------------------------*/

/**
 * @enum direction
 * @brief Movement directions.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum direction {
    LEFT,
    RIGHT,
    DOWN
};

/**
 * @enum type
 * @brief Block types.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
enum type {
    BG, /**< @brief Empty block. */
    F,
    F_R,
    I,
    L,
    L_R,
    N,
    N_R,
    P,
    P_R,
    T,
    U,
    W,
    Y,
    Y_R,
    I_SHORT,
    GHOST
};

/**
 * @struct Block
 * @brief Structure to represent a block.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
typedef struct {
    int type; /**< @brief Block type. */
    int rot; /**< @brief Current rotation. */
    int row; /**< @brief Rotation center row. */
    int col; /**< @brief Rotation center column. */
    int mark; /**< @brief Mark to use to print the block. */
} Block;
/** \} */

#endif
