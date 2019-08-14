/**
 * @file timer.h
 * @brief Functions to create and handle a timer.
 *
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 *
 * @copyright Copyright © 2017 Luca Della Libera. All rights reserved.
 */

#ifndef TIMER_H
#define TIMER_H

/**
 * @brief Create new timer.
 *
 * @param handler pointer to the timer tick handler function.
 * 
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void make_timer(void (*handler)());

/**
 * @brief Enable previously instantiated timer.
 *
 * @param interval_millis interval in milliseconds.
 * 
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void start_timer(int interval_millis);

/**
 * @brief Stop previously activated timer.
 * 
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void stop_timer();

/**
 * @brief Delete previously instantiated timer from memory.
 * 
 * @author Luca Della Libera (<luca310795@gmail.com>)
 * @version 1.0
 * @since 1.0
 */
extern void delete_timer();

#endif
