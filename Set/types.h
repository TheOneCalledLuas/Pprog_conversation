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
 * @brief Cardinal points.
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
 * @brief Creates the Set structure.
 *
 * @author Saúl López Romero.
 *
 * @return pointer to the set structure, NULL otherwise.
 */
Object_set *types_create_object_set();

/**
 * @brief Adds an object to the set structure.
 *
 * @author Saúl López Romero.
 *
 * @return Ok if the object was added, ERROR otherwise.
 */
Status types_object_set_add_element(Object_set *set, Object *element);

/**
 * @brief Destroys the set structure.
 *
 * @author Saúl López Romero.
 */
void types_object_set_destroy(Object_set *set);

/**
 * @brief Tries to take an element from the set.
 *
 * @author Saúl López Romero.
 *
 * @param set Pointer to the object set.
 *
 * @param id Id of the object to be taken out.
 * 
 * @return OK if the object was taken, ERROR otherwise.
 */
Status types_object_set_take_object(Object_set *set, Id id);


/**
 * @brief Returns the number of elements in the set.
 *
 * @author Saúl López Romero.
 *
 * @param set Pointer to the object set.
 * 
 * @return the number of elements, -1 if anything goes wrong.
 */
int types_object_set_get_len(Object_set *set);

/**
 * @brief Looks for an element from the set.
 *
 * @author Saúl López Romero.
 *
 * @param set Pointer to the object set.
 *
 * @param id Id of the object.
 * 
 * @return pointer to the object if found., NULL otherwise.
 */
Object *types_get_object_from_set(Object_set *set, Id id);

#endif
