/**
 * @brief It defines the player module
 *
 * @file player.h
 * @author Fernando Mijangos Varas
 * @version 1
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_NAME_SIZE 30

#include "types.h"

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its variables
 * @author Fernando Mijangos Varas
 * 
 * @param id the id for the new player
 * @return a pointer the a new player, initialized
 */
Player *player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player you want to destroy
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It sets the player name to a specified name
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @param name the name you want to give to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_player_name(Player* player, char name[PLAYER_NAME_SIZE]);

/**
 * @brief It sets the player location to an specified id
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @param id the id of the space you want the player to be at
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_player_location(Player* player, Id id);

/**
 * @brief It sets the condition of the object to what you want
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @param value TRUE/FALSE depending on if the player has the object or not
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player* player, Bool value);

/**
 * @brief It gets the player id
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @return the id of the player
 */
Id player_get_player_id(Player* player);

/**
 * @brief It gets the player name
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @return the name of the player
 */
char *player_get_player_name(Player* player);

/**
 * @brief It gets the player location id
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @return the id of the space the player is at
 */
Id player_get_player_location(Player* player);

/**
 * @brief It gets the value of the object condition
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @return TRUE if the player has the object or FALSE if not
 */
Bool player_get_object(Player* player);

/**
 * @brief It prints all the information about the player
 * @author Fernando Mijangos Varas
 * 
 * @param player the pointer to the player 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player *player);

#endif