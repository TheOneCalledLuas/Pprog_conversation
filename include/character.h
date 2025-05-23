/**
 * @brief It implements the character module
 *
 * @file character.h
 * @author Fernando Mijangos && Irene García
 * @version 1
 * @date 23-03-2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H
#define CHARACTER_TEXTURE_LINES 5 /*!< Lines of each texture.*/
#define CHARACTER_TEXTURE_SIZE 10 /*!< Size of the texture.*/

#include "types.h"
#include "player.h"

typedef struct _Character Character; /*!<Character type.*/

/**
 * @brief Allocates the memory needed and initializas the values.
 * @author Fernando Mijangos
 *
 * @param id Id of the new character.
 * @return Pointer to the new character, or NULL if any error happened.
 */
Character *character_create(Id id);

/**
 * @brief Frees all the memory that was allocated in character, and sets character to NULL.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 */
void character_destroy(Character *character);

/**
 * @brief Returns the id of the character.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @return Id of the character, ID_ERROR if error.
 */
Id character_get_id(Character *character);

/**
 * @brief Sets a line of the texture.
 * @author Fernando Mijangos.
 *
 * @param character Pointer to the character.
 * @param line line to be modified.
 * @param str to be set.
 * @return OK if all goes as planned, ERROR otherwise.
 */
Status character_set_texture_line(Character *character, int line, char *str);

/**
 * @brief Gets a determined line of the texture.
 * @author Fernando Mijangos.
 *
 * @param character Pointer to the character.
 * @param line line to be given.
 * @return NULL if an error takes place, the line otherwise.
 */
char *character_get_texture_line(Character *character, int line);
/**
 * @brief Sets the name of the character to what you want.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @param name New name of the character.
 * @return OK, if everything went well, ERROR if it didn't.
 */
Status character_set_name(Character *character, char *name);

/**
 * @brief Gets the name of the character.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @return Character's name, NULL if error.
 */
char *character_get_name(Character *character);

/**
 * @brief Sets the description of the character to what you want.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @param description New description of the character.
 * @return OK, if everything went as it should, ERROR if it didn't.
 */
Status character_set_description(Character *character, char *description);

/**
 * @brief Gets the description of the character.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @return Character's description, NULL if error.
 */
char *character_get_description(Character *character);

/**
 * @brief Sets the value of the friendly value.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @param value New value of the parameter.
 * @return OK, if everything went well, ERROR if it didn't.
 */
Status character_set_friendly(Character *character, Bool value);

/**
 * @brief Gets the value of the friendly parameter.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @return Value of the friendly parameter, 0 if error.
 */
Bool character_get_friendly(Character *character);

/**
 * @brief Sets the message of the character to what you want.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @param message String with the new message.
 * @return OK, if everything went well, ERROR if it didn't.
 */
Status character_set_message(Character *character, char *message);

/**
 * @brief Gets the message of the character.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the chracter.
 * @return The message of the character, NULL if any error happened.
 */
char *character_get_message(Character *character);

/**
 * @brief Sets the amount of live the character has.
 * @author Fernando Mijangos
 *
 * @param character Pointer to the character.
 * @param health New amount of health.
 * @return OK, if everything went well, ERROR if it didn't.
 */
Status character_set_health(Character *character, int health);

/**
 * @brief Gets the amount of health of the character.
 * @author Fernando Mijangos.
 *
 * @param character Pointer to the character.
 * @return Health amount of the character, FUNCTION_ERROR if error.
 */
int character_get_health(Character *character);

/**
 * @brief Prints the information of the character.
 * @author Fernando Mijangos.
 *
 * @param character Pointer to the character.
 * @param player Player id.
 * @return OK if it works, ERROR otherwise.
 */

Status character_set_follow(Character *character, Id player);

/**
 * @brief Gets the id of the player the character follows.
 * @author Irene García.
 *
 * @param character Pointer to the character.
 * @return Id of the player that the character follows, ID_ERROR if error.
 */
Id character_get_follow(Character *character);

/**
 * @brief Gets the id of the player the character follows.
 * @author Irene García.
 *
 * @param character Pointer to the character.
 * @return Id of the player that the character follows, ID_ERROR if error.
 */

Status character_print(Character *character);

#endif
