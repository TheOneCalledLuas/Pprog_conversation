/**
 * @brief It defines common types for the whole project
 *
 * @file set.h
 * @author Saúl López Romero
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

typedef long Id;

typedef enum
{
    FALSE,  /*!< False value.*/
    TRUE    /*!< True value.*/
} Bool;

typedef enum
{
    ERROR,  /*!< Error value.*/
    OK      /*!< Good functioning value.*/
} Status;

/**
 * @brief Cardinal points.
 */
typedef enum
{
    N,  /*!< North.*/
    S,  /*!< South.*/
    E,  /*!< East.*/
    W   /*!< West.*/
} Direction;

#endif