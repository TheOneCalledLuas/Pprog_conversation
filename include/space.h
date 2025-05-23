/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Fernando Mijangos && Saúl Lopez 
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "object.h"
#include "set.h"
#define SPACE_TEXTURE_LINES 29 /*!< Lines of each texture.*/
#define SPACE_TEXTURE_SIZE 67 /*!< Size of the texture.*/

typedef struct _Space Space; /*!<Space type.*/

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
 * @author Saúl Lopez Romero.
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
 * @param str to be set.
 * @return OK if all goes as planned, ERROR otherwise.
 */
Status space_set_gdesc_line(Space *space, int line, char *str);

/**
 * @brief Gets a determined line of the texture.
 * @author Fernando Mijangos.
 * 
 * @param space Pointer to the space.
 * @param line line to be given.
 * @return NULL if an error takes place, the line otherwise.
 */
char *space_get_texture_line(Space *space, int line);

/**
 * @brief Sets a line of the texture.
 * @author Fernando Mijangos.
 * 
 * @param space Pointer to the space.
 *  @param line line to be modified.
 * @param str to be set.
 * @return OK if all goes as planned, ERROR otherwise.
 */
Status space_set_texture_line(Space *space, int line, char *str);

/**
 * @brief It gets the id of a space
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space
 * @return Id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It sets the name of a space
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space *space, char *name);

/**
 * @brief It gets the name of a space
 * @author Fernando Mijangos
 *
 * @param space Pointer to the space
 * @return  a string with the name of the space
 */
const char *space_get_name(Space *space);

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
 * @return Possition of the id in the set if found, FUNCTION_ERROR otherwise
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
 * @param space Pointer to the space.
 * @return n_elements of the set of object.
 */
int space_get_n_objects(Space *space);

/**
 * @brief It returns an array with the ids of the characters in the space
 *          IMPORTANT you have to free the array after using it
 * @author Fernando Mijangos
 * 
 * @param space Pointer to the space.
 * @return Array with the ids of the characters.
 *          IMPORTANT you have to free the array after useing it.
 */
Id *space_get_characters(Space *space);

/**
 * @brief It adds a character to the space
 * @author Fernando Mijangos
 * 
 * @param space Pointer to the space
 * @param character Id of the character you want to add
 * @return OK if everything went well, ERROR otherwise
 */
Status space_add_character(Space *space, Id character);

/**
 * @brief It searches for a character inside of the space
 * @author Fernando Mijangos
 * 
 * @param space Pointer to the space
 * @param character Id of the character you searching for
 * @return position of the id in the set of characters, FUNCTION_ERROR otherwise
 */
int space_find_character(Space *space, Id character);

/**
 * @brief It takes a character from the space
 * @author Fernando Mijangos
 * 
 * @param space Pointer to the space
 * @param character Id of the chracter you want to remove
 * @return Id of the character taken out, ID_ERROR if any error
 */
Id space_take_character(Space *space, Id character);

/**
 * @brief Returns the number of characters inside of a space
 * @author Fernando Mijangos
 * 
 * @param space Pointer to the space
 * @return  Number of characters, FUNCTION_ERROR if ERROR
 */
int space_get_n_characters(Space *space);


/**
 * @brief Gets the information about if the space hs been discovered or not.
 * @author Fernando Mijangos.
 * 
 * @param space Pointer to the space.
 * @return TRUE if discovered, FALSE if it hasn't or FALSE if error.
 */
Bool space_is_discovered(Space *space);

/**
 * @brief Sets the discovered variable of a space to what you want.
 * @author Fernando Mijangos.
 * 
 * @param space Pointer to the space.
 * @param value New value, TRUE(discovered) or FALSE(not discovered).
 * @return OK if everything went well, ERROR otherwise.
 */
Status space_set_discovered(Space *space, Bool value);

/**
 * @brief It prints the space information(id, name, object id, north id, east id....).
 * @author Fernando Mijangos.
 *
 * @param space Pointer to the space.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status space_print(Space *space);

#endif
