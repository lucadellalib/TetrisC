/**
 * @file field.h
 * @brief Functions to create and manipulate a game area.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

#ifndef FIELD_H
#define FIELD_H

/**
 * @brief Allocate new field.
 *
 * @return f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern Field *create_field();

/**
 * @brief Deallocate field.
 *
 * @param f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void delete_field(Field *f);

/**
 * @brief Delete field content.
 *
 * @param f field pointer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void clear_field(Field *f);

/**
 * @brief Init field.
 *
 * @param f field pointer.
 * @param rows number of rows.
 * @param cols number of columns.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void init_field(Field *f, int rows, int cols);

/**
 * @brief Find the first completed row, between rows of index 'from' and 'to'.
 *
 * @param f field pointer.
 * @param from start row.
 * @param to end row.
 * @return row index if it exists, -1 otherwise.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern int find_row_field(Field *f, int from, int to);

/**
 * @brief Delete row and update field.
 *
 * @param f field pointer.
 * @param row_to_clear row to delete.
 * 
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void clear_row_field(Field *f, int row_to_clear);

#endif
