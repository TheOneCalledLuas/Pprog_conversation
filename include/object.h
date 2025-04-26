/**
 * @brief It handles object related tasks.
 *
 * @file object.h
 * @author Saúl López Romero, Irene García
 * @version 2
 * @date 2-02-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object; /*!< Object type.*/

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
 * @author Irene García
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

Status object_set_name(Object * object, char * desc);

/**
 * @brief Gets the object's description.
 * @author Irene García
 * 
 * @param object Pointer to the object.
 * @return Pointer to the object description.
 */
char *object_get_description(Object *object);

/**
 * @brief Gets the object's description.
 * @author Irene García
 * 
 * @param object Pointer to the object.
 * @param desc Pointer to the descprition.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_set_description(Object * object, char * desc);

/**
 * @brief Sets the object's name.
 * @author Saúl López Romero
 * 
 * @param object Pointer to the object.
 * @param name Name string.
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

/**
 * @brief Gets the object's name.
 * @author Saúl López Romero
 * 
 * @param object Pointer to the object.
 * @return Object's id.
 */

Status object_set_health(Object *object, int health);
int object_get_health(Object *object);
Status object_is_movable(Object *object, Bool movable);
Bool object_get_movable(Object *object);
Status object_set_dependency(Object *object, Id dependency);
Id object_get_dependency(Object *object);
Status object_set_open(Object *object, Id open);
Id object_get_open(Object *object);

/**
 * @brief Prints the object info (debug intended).
 * @author Saúl López Romero
 * 
 * @param object Pointer to the object.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_print_info(Object *object);
#endif