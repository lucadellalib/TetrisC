/**
 * @file field.c
 * @brief Functions to create and manipulate a game area.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

/**
 * @addtogroup Game
 * @{
 */
#include <stdlib.h>

#include "shared.h"
#include "field.h"


Field *create_field() {
    Field *field = malloc(sizeof(Field));
    return field;
}

void delete_field(Field *f) {
    free(f);
}

void clear_field(Field *f) {
    // write BG in each grid cell
    int row, col;
    for (row = 0; row < f->rows; row++) {
        for (col = 0; col < f->cols; col++) {
            f->grid[row][col] = BG;
        }
    }
}

void init_field(Field *f, int rows, int cols) {
    f->rows = rows;
    f->cols = cols;
    clear_field(f);
}

int find_row_field(Field *f, int from, int to) {
    int row, col;
    for (row = to; row >= from; row--) {
        col = 0;
        while (col < f->cols && f->grid[row][col] != BG) {
            col++;
        }
        if (col == f->cols) {
            return row;
        }
    }
    return -1;
}

void clear_row_field(Field *f, int row_to_clear) {
    // copy each row into the following one
    int row, col;
    for (row = row_to_clear; row > 0; row--) {
        for (col = 0; col < f->cols; col++) {
            f->grid[row][col] = f->grid[row - 1][col];
        }
    }   
    // first row must be deleted
    for (col = 0; col < f->cols; col++) {
        f->grid[0][col] = BG;
    }
}
/** \} */
