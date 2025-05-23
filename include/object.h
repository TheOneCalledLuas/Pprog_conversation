/**
 * @brief It handles object related tasks.
 *
 * @file object.h
 * @author Saúl López Romero, Irene García, Fernando Mijangos
 * @version 2
 * @date 2-02-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#define OBJECT_TEXTURE_LINES 5 /*!< Lines of each texture.*/
#define OBJECT_TEXTURE_SIZE 10 /*!< Size of the texture.*/

typedef struct _Object Object; /*!< Object type.*/

/**
 * @brief It handles all the object creation proccess.
 * @author Saúl López Romero
 *
 * @param id Unique id of the object structure. (make sure its not repeated)
 * @return Pointer to the object.
 */
Object *object_create(Id id);

/**
 * @brief Destroys the object structure propperly.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_destroy(Object *object);

/**
 * @brief Sets a line of the texture.
 * @author Fernando Mijangos.
 *
 * @param object Pointer to the object.
 * @param line line to be modified.
 * @param str to be set.
 * @return OK if all goes as planned, ERROR otherwise.
 */
Status object_set_texture_line(Object *object, int line, char *str);

/**
 * @brief Gets a determined line of the texture.
 * @author Fernando Mijangos.
 *
 * @param object Pointer to the object.
 * @param line line to be given.
 * @return NULL if an error takes place, the line otherwise.
 */
char *object_get_texture_line(Object *object, int line);

/**
 * @brief Gets the object's name.
 * @author Saúl López Romero
 *
 * @param object Pointer to the object.
 * @return Pointer to the object name.
 */
char *object_get_name(Object *object);

Status object_set_name(Object *object, char *desc);

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
Status object_set_description(Object *object, char *desc);

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
 * @brief Sets the amount of health an object gives
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @param health The amount of health it gives or takes
 * @return Object's health.
 */
Status object_set_health(Object *object, int health);

/**
 * @brief Gets the amount of health an object gives.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @return Object's health.
 */
int object_get_health(Object *object);

/**
 * @brief Determines wether an object is movable or not.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @param movable True if it can be moved, false otherwise.
 * @return Object's movable value.
 */
Status object_set_movable(Object *object, Bool movable);

/**
 * @brief Gets the information of the movability of an object.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @return Object's movable value.
 */
Bool object_get_movable(Object *object);

/**
 * @brief  Determines wether an object is dependant on other to be interacted with.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @param dependency Wether an object depends on another or not
 * @return Object's dependency value.
 */
Status object_set_dependency(Object *object, Id dependency);

/**
 * @brief Gets the dependency value of an object.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @return Object's dependency value.
 */
Id object_get_dependency(Object *object);

/**
 * @brief Determines wether an object can open a link between spaces or not.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @param open value of the open parameter
 * @return Object's open value.
 */
Status object_set_open(Object *object, Id open);

/**
 * @brief Gets the link id that an object can open.
 * @author Irene García
 *
 * @param object Pointer to the object.
 * @return Object's open value.
 */
Id object_get_open(Object *object);

/**
 * @brief Sets the is_used value of an object.
 * @author Saúl López Romero
 *
 * @param object Pointer to the object.
 * @param is_used Wether the object is used or not.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_set_is_used(Object *object, Bool is_used);

/**
 * @brief Gets the is_used value of an object.
 * @author Saúl López Romero
 *
 * @param object Pointer to the object.
 * @return Object's is_used value or FALSE if an error takes place.
 */
Bool object_get_is_used(Object *object);

/**
 * @brief Sets the special_use value of an object.
 * @author Saúl López Romero
 *
 * @param object Pointer to the object.
 * @param special_use Wether the object is used in a special way or not.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_set_special_use(Object *object, Bool special_use);

/**
 * @brief Gets the special_use value of an object.
 * @author Saúl López Romero
 *
 * @param object Pointer to the object.
 * @return Object's special_use value or FALSE if an error takes place.
 */
Bool object_get_special_use(Object *object);

/**
 * @brief Prints the object info (debug intended).
 * @author Saúl López Romero
 *
 * @param object Pointer to the object.
 * @return OK if it works as intended, ERROR otherwise.
 */
Status object_print_info(Object *object);
#endif