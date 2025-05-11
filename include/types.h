/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Saúl López Romero && Fernando Mijangos
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000                             /*!<Maximun word length.*/
#define NO_ID -1                                   /*!<Minor error code.*/
#define ID_ERROR -2                                /*!<Major error code.*/
#define SAVEFILES_NAMES "data/savefiles_names.txt" /*!<Name of the file where the savefiles names are stored.*/
#define MAX_SAVEFILES 10                           /*!<Maximum number of savefiles*/
#define FUNCTION_ERROR -1                          /*!< Function error code.*/
#define NO_POSITION -1                             /*!< No position code. */
#define EQUAL_WORDS 0                              /*!< Equal words code. */
#define NO_THINGS 0                                /*!< No things code. */

typedef long Id; /*!< Id type. */

/**Link properties. */
typedef enum
{
    UNK = -1, /*!<Not known state.*/
    CLOSED,   /*!<Closed link.*/
    OPENED    /*!<Opened link.*/
} Link_Property;

/**Boolean values.*/
typedef enum
{
    FALSE, /*!< False value.*/
    TRUE   /*!< True value.*/
} Bool;

/**
 * @brief Status code.
 */
typedef enum
{
    ERROR, /*!< Error value.*/
    OK     /*!< Good functioning value.*/
} Status;

/**
 * @brief Cardinal points.
 */
typedef enum
{
    N,            /*!< North.*/
    S,            /*!< South.*/
    E,            /*!< East.*/
    W,            /*!< West.*/
    U,            /*!< Up.*/
    D,            /*!< Down.*/
    UNK_DIRECTION /*!< Unknown direction*/
} Direction;

#endif