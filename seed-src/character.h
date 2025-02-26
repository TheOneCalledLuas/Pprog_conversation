/**
 * @brief It implements the character module
 *
 * @file character.h
 * @author Fernando Mijangos
 * @version 1
 * @date 23-02-2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"
#define MAX_NAME 20
#define MAX_DESC 7
#define MAX_MESSAGE 100

typedef struct _Character Character;

/**
 * @brief Allocates the memory needed and initializas the values.
 * @author Fernando Mijangos
 * 
 * @param Id Id of the new character.
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
 * @brief Sets the name of the character to what you want.
 * @author Fernando Mijangos
 * 
 * @param character Pointer to the character.
 * @param name New name of the character.
 * @return OK, if everything went well, ERROR if it didn't.
 */
Status character_set_name(Character *character, char* name);

/**
 * @brief Gets the name of the character.
 * @author Fernando Mijangos
 * 
 * @param character Pointer to the character.
 * @return Name od the character, NULL if error.
 */
char *character_get_name(Character *character);


/**
 * @brief Sets the description of the character to what you want.
 * @author Fernando Mijangos
 * 
 * @param chracter Pointer to the character.
 * @param description New description of the character.
 * @return OK, if everything went well, ERROR if it didn't.
 */
Status character_set_description(Character *character, char* description);

/**
 * @brief Gets the description of the character.
 * @author Fernando Mijangos
 * 
 * @param chracter Pointer to the character.
 * @return Description of the character, NULL if error.
 */
char *character_get_description(Character *character);

/**
 * @brief Sets the value of the friendly value.
 * @author Fernando Mijangos
 * 
 * @param chracter Pointer to the character.
 * @param value New value of the parameter.
 * @return OK, if everything went well, ERROR if it didn't.
 */
Status character_set_friendly(Character *character, Bool value);

/**
 * @brief Gets the value of the friendly parameter.
 * @author Fernando Mijangos
 * 
 * @param character Pointer to the character.
 * @return Value of the friendly paramaeter, 0 if error.
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
Status character_set_message(Character *character, char* message);

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
 * @return Health amount of the character, -1 if error.
 */
int character_get_health(Character *character);

/**
 * @brief GPrints the information of the character.
 * @author Fernando Mijangos.
 * 
 * @param character Pointer to the character.
 * @return OK if it works, ERROR otherwise.
 */
Status character_print(Character *character);

#endif