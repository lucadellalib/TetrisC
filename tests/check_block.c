/**
 * @file check_block.c
 * @brief Unit tests.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

#include <check.h>
 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "shared.h"
#include "field.h"
#include "block.h"

// number of attempts
#define TIMES 500

// check pattern
static const int PATTERN[22][11] = 
{
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30},
 {30, 0, 0, 0, 0, 0, 0, 0, 0, 30, 30},
 {30, 30, 30, 0, 0, 0, 0, 0, 0, 30, 0},
 {30, 30, 0, 0, 0, 0, 0, 0, 0, 30, 0},
 {30, 0, 30, 0, 0, 0, 0, 30, 30, 30, 30},
 {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}
};

// game area
static Field *curr_field;

// block
static Block *curr_block;

static void drop_block() {
    curr_block = create_block();
    // init current block
    init_block(curr_block, rand() % I_SHORT + 1, rand() % 4, -BLOCK_MAX_SIZE, COLUMNS / 2);
    // move down until the first cell of the block appears on row 16
    while (get_limit_high_block(curr_block) < 16 && can_move_block(curr_block, curr_field, DOWN)) {
        move_block(curr_block, curr_field, DOWN);
    }
    write_block(curr_block, curr_field);
}

static void init_game() {
    curr_field = create_field();
    init_field(curr_field, ROWS, COLUMNS);

    int row, col;
    for (row = 0; row < curr_field->rows; row++) {
        for (col = 0; col < curr_field->cols; col++) {
            curr_field->grid[row][col] = PATTERN[row][col];
        }
    }

    drop_block();
}

static int check_pattern() {
    int row, col;
    for (row = 0; row < curr_field->rows; row++) {
        for (col = 0; col < curr_field->cols; col++) {
            if (curr_field->grid[row][col] != PATTERN[row][col]) {
                return 1;
            }
        }
    }
    return 0;
}

START_TEST(test_block_move) {
    srand(time(NULL));

    init_game();

    int action;
    int i;
    for (i = 0; i < TIMES; i++) {
        action = rand() % 4;
        switch (action) {
            case 0:
                // rotate
                if (can_rotate_block(curr_block, curr_field)) {
                    rotate_block(curr_block, curr_field);
                }
                break;
            case 1:
                // move down
                if (can_move_block(curr_block, curr_field, DOWN)) {
                    move_block(curr_block, curr_field, DOWN);
                }          
                break;
            case 2:
                // move left
                if (can_move_block(curr_block, curr_field, LEFT)) {
                    move_block(curr_block, curr_field, LEFT);
                }
                break;
            case 3:
                // move right
                if (can_move_block(curr_block, curr_field, RIGHT)) {
                    move_block(curr_block, curr_field, RIGHT);
                }
                break;
        }
    }
    
    // delete current block
    erase_block(curr_block, curr_field);
    // compare to the pattern
    ck_assert_int_eq(check_pattern(), 0);
    // print number of performed actions
    printf("Performed actions: %d\n", TIMES);
    // print block type
    switch (curr_block->type) {
        case F:
            printf("Type: F\n");
            break;
        case F_R:
            printf("Type: F_R\n");
            break;
        case I:
            printf("Type: I\n");
            break;
        case L:
            printf("Type: L\n");
            break;
        case L_R:
            printf("Type: L_R\n");
            break;
        case N:
            printf("Type: N\n");
            break;
        case N_R:
            printf("Type: N_R\n");
            break;
        case P:
            printf("Type: P\n");
            break;
        case P_R:
            printf("Type: P_R\n");
            break;
        case T:
            printf("Type: T\n");
            break;
        case U:
            printf("Type: U\n");
            break;
        case W:
            printf("Type: W\n");
            break;
        case Y:
            printf("Type: Y\n");
            break;
        case Y_R:
            printf("Type: Y_R\n");
            break;
        case I_SHORT:
            printf("Type: I_SHORT\n");
            break;
    }
    // print rotation
    printf("Rotation: %d\n", curr_block->rot);
}
END_TEST

static Suite *block_suite() {
    Suite *s;
    TCase *tc_core;
    s = suite_create("Block");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_block_move);
    suite_add_tcase(s, tc_core);
    return s;
}

int main() {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = block_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
