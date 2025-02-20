/**
 * @brief It defines the player module
 *
 * @file player.h
 * @author Fernando Mijangos Varas, saúl López Romero
 * @version 2
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_NAME_SIZE 30

#include "types.h"
#include "object.h"

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its variables
 * @author Fernando Mijangos Varas
 *
 * @param id Id for the new player.
 * @return Pointer the a new player, initialized.
 */
Player *player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player you want to destroy.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_destroy(Player *player);

/**
 * @brief It sets the player name to a specified name.
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @param name The name you want to give to the player.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_set_player_name(Player *player, char name[PLAYER_NAME_SIZE]);

/**
 * @brief It sets the player location to an specified id.
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @param id Id of the space you want the player to be at.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_set_player_location(Player *player, Id id);

/**
 * @brief It sets the object of the player to the one you want.
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @param object Id of the object you want the player to have.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_set_object(Player *player, Id object);

/**
 * @brief It gets the player id.
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @return Id of the player.
 */
Id player_get_player_id(Player *player);

/**
 * @brief It gets the player name
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @return the name of the player.
 */
char *player_get_player_name(Player *player);

/**
 * @brief It gets the player location id.
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @return Id of the space the player is at.
 */
Id player_get_player_location(Player *player);

/**
 * @brief It gets the id of the object the player has.
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @return Id of the object the player has.
 */
Id player_get_object(Player *player);

/**
 * @brief Gets the amount of health the player has.
 * @author Saul Lopez Romero.
 *
 * @param player Pointer to the player.
 * @return amount of health, -1 if an error takes place.
 */
int player_get_health(Player *player);

/**
 * @brief Sets the player health to a value.
 * @author Saul López Romero.
 *
 * @param player Pointer to the player.
 * @param health Amount of health to be set.
 * @return OK if everythign goes as planned, ERROR otherwise.
 */
Status player_set_health(Player *player, int health);

/**
 * @brief It prints all the information about the player
 * @author Fernando Mijangos Varas
 *
 * @param player Pointer to the player.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_print(Player *player);

#endif