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

#define WORD_SIZE 1000
#define NO_ID -1

typedef long Id;

typedef enum
{
    FALSE,
    TRUE
} Bool;

typedef enum
{
    ERROR,
    OK
} Status;

/**
 * @brief cardinal points.
 */
typedef enum
{
    N,
    S,
    E,
    W
} Direction;

/**
 * @brief Set TAD structure.
 * 
 * @author Saúl López Romero.
 */
typedef struct _Object_set Object_set;

/**
 * @brief creates the Set structure.
 *
 * @author Saúl López Romero.
 * 
 * @return pointer to the set structure, NULL otherwise.
 */
Object_set *types_create_object_set();

/**
 * @brief adds an object to the set structure.
 *
 * @author Saúl López Romero.
 * 
 * @return Ok if the object was added, ERROR otherwise.
 */
Status types_object_set_add_element(Object_set *set, Object *element);

/**
 * @brief destroys the set strucutre.
 * @author Saúl López Romero.
 */
void types_object_set_destroy(Object_set *set);


#endif
