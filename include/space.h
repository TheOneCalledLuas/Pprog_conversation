/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Fernando Mijangos && Saul Lopez
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "object.h"
#include "set.h"

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its variables.
 * @author Fernando Mijangos
 *
 * @param id Identification number for the new space.
 * @return a pointer to a new space, initialized.
 */
Space *space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory.
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space that must be destroyed.
 */
void space_destroy(Space *space);

/**
 * @brief Gets a determined line of the graphic description.
 * @author Saúl López Romero.
 *
 * @param space Pointer to the space.
 * @param line line to be given.
 * @return NULL if an error takes place, the line otherwise.
 */
char *space_get_gdesc_line(Space *space, int line);

/**
 * @brief Sets a line of the graphic description.
 * @author Saúl López Romero.
 *
 * @param space Pointer to the space.
 * @param line line to be modified.
 * @param string to be set.
 * @return OK if all goes as planned, ERROR otherwise.
 */
Status space_set_gdesc_line(Space *space, int line, char *str);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @return Id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space *space, char *name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @return  a string with the name of the space
 */
const char *space_get_name(Space *space);

/**
 * @brief It sets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @param id Id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_north(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @return Id number of the space located at the north
 */
Id space_get_north(Space *space);

/**
 * @brief It sets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @param id Id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @return Id number of the space located at the south
 */
Id space_get_south(Space *space);

/**
 * @brief It sets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @param id Id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @return Id number of the space located at the east
 */
Id space_get_east(Space *space);

/**
 * @brief It sets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @param id Id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space Pointer to the space
 * @return Id number of the space located at the west
 */
Id space_get_west(Space *space);

/**
 * @brief It returns an array with the ids of the objects in the space
 *          IMPORTANT you have to free the array after using it
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space.
 * @return Array with the ids of the objects
 *          IMPORTANT you have to free the array after using it.
 */
Id *space_get_objects(Space *space);

/**
 * @brief It adds a new object to the set
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space
 * @param object id of the object you want to add
 * @return OK if the element was added or already in the set, ERROR otherwise
 */
Status space_add_object(Space *space, Id object);

/**
 * @brief It searches for an object in the set of the space
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space
 * @param object Id of the object you are searching
 * @return Possition of the id in the set if found, -1 otherwise
 */
int space_find_object(Space *space, Id object);

/**
 * @brief It removes an object from the set of the space.
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space.
 * @param object Id of the object you want to take.
 * @return Id of the object you are taking.
 */
Id space_take_object(Space *space, Id object);

/**
 * @brief It gets the n_elements in the set of objects.
 * @author Fernando Mijangos
 * 
 * @param Space Pointer to the space.
 * @return n_elements of the set of object.
 */
int space_get_n_objects(Space *space);

/**
 * @brief Returns the character id.
 * @author Saul Lopez Romero
 *
 * @param space Pointer to the space.
 * @return Id of the character you are taking.
 */
Id space_get_character(Space *space);

/**
 * @brief Sets the space's character.
 * @author Saul Lopez Romero
 *
 * @param space Pointer to the space.
 * @param id Id of the character to be set up.
 * @return OK if it goes as planned, ERROR otherwise.
 */
Status space_set_character(Space *space, Id id);

/**
 * @brief It prints the space information(id, name, object id, north id, east id....).
 * @author Fernando Mijangos.
 *
 * @param space Pointer to the space.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status space_print(Space *space);

#endif
