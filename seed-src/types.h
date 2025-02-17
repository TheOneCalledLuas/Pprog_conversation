/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/*Maximun lenght for each word.*/
#define WORD_SIZE 1000

/*Error code.*/
#define NO_ID -1

typedef long Id;

/**
 * @brief It sets the values FALSE (0) and TRUE (1).
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief It sets the value of ERROR(0) and OK(1).
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief * It stores the value each cardinal direction has N(0) S(1) E(2) S(3).
 */
typedef enum { N, S, E, W } Direction;

#endif
