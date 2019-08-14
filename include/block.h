/**
 * @file block.h
 * @brief Functions to create and manipulate a block.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

#ifndef BLOCK_H
#define BLOCK_H

/**
 * @brief Allocate new block.
 *
 * @return block pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern Block *create_block();

/**
 * @brief Deallocate block.
 *
 * @param b block pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void delete_block(Block *b);

/**
 * @brief Init block.
 *
 * @param b block pointer.
 * @param type block type.
 * @param rot rotation.
 * @param row rotation center row.
 * @param col rotation center column.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void init_block(Block *b, int type, int rot, int row, int col);

/**
 * @brief Init 'Ghost'.
 *
 * @param b block pointer.
 * @param type block type.
 * @param rot rotation.
 * @param row rotation center row.
 * @param col rotation center column.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void init_ghost_block(Block *b, int type, int rot, int row, int col);

/**
 * @brief Delete block from field.
 *
 * @param b block pointer.
 * @param f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void erase_block(Block *b, Field *f);

/**
 * @brief Write block to field.
 *
 * @param b block pointer.
 * @param f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void write_block(Block *b, Field *f);

/**
 * @brief Update block.
 *
 * @param b block pointer.
 * @param f field pointer.
 * @param new_rot new rotation.
 * @param new_row new rotation center row.
 * @param new_col new rotation center column.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void update_block(Block *b, Field *f, int new_rot, int new_row, int new_col);

/**
 * @brief Return block upper limit.
 *
 * @param b block pointer.
 * @return max row index occupied by a cell of the block.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int get_limit_high_block(Block *b);

/**
 * @brief Return block lower limit.
 *
 * @param b block pointer.
 * @return min row index occupied by a cell of the block.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int get_limit_low_block(Block *b);

/**
 * @brief Move block.
 *
 * @param b block pointer.
 * @param f field pointer.
 * @param dir direction.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void move_block(Block *b, Field *f, int dir);

/**
 * @brief Rotate block.
 *
 * @param b block pointer.
 * @param f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void rotate_block(Block *b, Field *f);

/**
 * @brief Return TRUE if block can move, FALSE otherwise.
 *
 * @param b block pointer.
 * @param f field pointer.
 * @param dir direction.
 * @return true if block can move, false otherwise.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern bool can_move_block(Block *b, Field *f, int dir);

/**
 * @brief Return TRUE if block can rotate, FALSE otherwise.
 *
 * @param b block pointer.
 * @param f field pointer.
 * @return true if block can rotate, false otherwise.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern bool can_rotate_block(Block *b, Field *f);

#endif
