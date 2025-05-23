/**
 * @brief It defines the player module
 *
 * @file player.h
 * @author Fernando Mijangos && Saúl López Romero
 * @version 3
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_NAME_SIZE 30    /*!<Maxinum name length.*/
#define PLAYER_TEXTURE_LINES 7 /*!< Lines of each texture.*/
#define PLAYER_TEXTURE_SIZE 10 /*!< Size of the texture.*/

#include "types.h"
#include "object.h"
#include "inventory.h"

typedef struct _Player Player; /*!<Player type.*/

/**
 * @brief It creates a new player, allocating memory and initializing its variables
 * @author Fernando Mijangos
 *
 * @param id Id for the new player.
 * @return Pointer the a new player, initialized.
 */
Player *player_create(Id id);

/**
 * @brief It sets the player team.
 * @author Saúl López Romero
 *
 * @param player Pointer to the player.
 * @param team Id of the team.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_set_team(Player *player, Id team);

/**
 * @brief It gets the player team.
 * @author Saúl López Romero
 *
 * @param player Pointer to the player.
 * @return Id of the team or NO_ID if an error takes place.
 */
Id player_get_team(Player *player);

/**
 * @brief It sets a line of the texture.
 * @author Fernando Mijangos.
 *
 * @param player Pointer to the player.
 * @param line line to be modified.
 * @return OK if all goes as planned, ERROR otherwise.
 */
char *player_get_texture_line(Player *player, int line);

/**
 * @brief It sets a line of the texture.
 * @author Fernando Mijangos.
 *
 * @param player Pointer to the player.
 * @param line line to be given.
 * @param str to be set.
 * @return NULL if an error takes place, the line otherwise.
 */
Status player_set_texture_line(Player *player, int line, char *str);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player you want to destroy.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_destroy(Player *player);

/**
 * @brief It sets the player name to a specified name.
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player.
 * @param name The name you want to give to the player.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_set_player_name(Player *player, char name[PLAYER_NAME_SIZE]);

/**
 * @brief Takes an object out of the player inventory.
 * @author Saúl López Romero
 *
 * @param player Pointer to the player.
 * @param object Id of the object to be taken.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_del_object(Player *player, Id object);

/**
 * @brief Gets the number of objects the playes has.
 * @author Saúl López Romero.
 *
 * @param player Pinter to the player.
 * @return Number of objects the player has, or FUNCTION_ERROR if an error takes place.
 */
int player_get_n_objects(Player *player);

/**
 * @brief Sets the maximun object number for the player.
 * @author Saúl López Romero
 *
 * @param player Pointer to the player.
 * @param capacity Number of objects.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_set_inventory_capacity(Player *player, long capacity);

/**
 * @brief Gets the maximun object number for the player.
 * @author Saúl López Romero
 *
 * @param player Pointer to the player.
 * @return Number of objects or FUNCTION_ERROR if an error takes place.
 */
long player_get_inventory_capacity(Player *player);

/**
 * @brief It sets the player location to an specified id.
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player.
 * @param id Id of the space you want the player to be at.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_set_player_location(Player *player, Id id);

/**
 * @brief Adds an object to the inventory.
 * @author Saúl López Romero.
 *
 * @param player Pointer to the player.
 * @param object Id of the object you want the player to have.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_add_object(Player *player, Id object);

/**
 * @brief It gets the player id.
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player.
 * @return Id of the player.
 */
Id player_get_player_id(Player *player);

/**
 * @brief It sets the player id.
 * @author Saúl López Romero
 *
 * @param player Pointer to the player.
 * @param gdesc Graphic description.
 * @return OK or ERROR if somenthing goes wrong.
 */
Status player_set_gdesc(Player *player, char *gdesc);

/**
 * @brief It gets the player graphic description.
 * @author Saúl López Romero
 *
 * @param player Pointer to the player.
 * @return string with the description or NULL if it goes wrong.
 */
char *player_get_gdesc(Player *player);

/**
 * @brief It gets the player name
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player.
 * @return the name of the player.
 */
char *player_get_player_name(Player *player);

/**
 * @brief It gets the player location id.
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player.
 * @return Id of the space the player is at.
 */
Id player_get_player_location(Player *player);

/**
 * @brief It gets an allocated array of ids of the objects the player has.
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player.
 * @return Array of ids of the obejcts the player has.
 * @note IMPORTANT, you have to free the memory after using this
 */
Id *player_get_inventory(Player *player);

/**
 * @brief Gets the amount of health the player has.
 * @author Saúl Lopez Romero.
 *
 * @param player Pointer to the player.
 * @return amount of health, FUNCTION_ERROR if an error takes place.
 */
int player_get_health(Player *player);

/**
 * @brief Searches for an object in a player's inventory.
 * @author Saúl López Romero.
 *
 * @param player Pointer to the player.
 * @param object Id of the object to be searched for.
 * @return NO_POSITION if the object wasn't found or
 */
Bool player_has_object(Player *player, Id object);

/**
 * @brief Sets the player health to a value.
 * @author Saúl López Romero.
 *
 * @param player Pointer to the player.
 * @param health Amount of health to be set.
 * @return OK if everythign goes as planned, ERROR otherwise.
 */
Status player_set_health(Player *player, int health);

/**
 * @brief It prints all the information about the player
 * @author Fernando Mijangos
 *
 * @param player Pointer to the player.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status player_print(Player *player);

#endif