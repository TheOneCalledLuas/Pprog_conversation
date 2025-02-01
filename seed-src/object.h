/**
 * @brief It handles object related tasks.
 *
 * @file object.h
 * @author Saúl López Romero
 * @version 0
 * @date 2-02-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/**
 * @brief It handles all the object creation proccess.
 * @author Saúl López Romero
 * 
 * @param id Unique id of the object structure. (make sure its not repeated)
 * @return Pointer to the object.
 */
Object * object_create(Id id);

/**
 * @brief Destroys the object structure propperly.
 * @author Saúl López Romero
 * 
 * @param object Pointer to the object.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_destroy(Object *object);

/**
 * @brief Gets the object's name.
 * @author Saúl López Romero
 * 
 * @param object Pointer to the object.
 * @return Pointer to the object name.
 */
char *object_get_name(Object *object);

/**
 * @brief Sets the object's name.
 * @author Saúl López Romero
 * 
 * @param object Pointer to the object.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_set_name(Object *object, char *name);

/**
 * @brief Gets the object's name.
 * @author Saúl López Romero
 * 
 * @param object Pointer to the object.
 * @return Object's id.
 */
Id object_get_id(Object *object);


#endif