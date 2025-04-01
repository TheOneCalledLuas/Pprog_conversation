/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Saúl López Romero
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /*!<Maximun word length.*/
#define NO_ID -1 /*!<Minor error code.*/
#define ID_ERROR -2 /*!<Major error code.*/

typedef long Id; /*!< Id type. */

/**Boolean values.*/
typedef enum
{
    FALSE,  /*!< False value.*/
    TRUE    /*!< True value.*/
} Bool;

/**
 * @brief Status code.
 */
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
    W,   /*!< West.*/
    UNK_DIRECTION /*!< Unknown direction*/
} Direction;

#endif