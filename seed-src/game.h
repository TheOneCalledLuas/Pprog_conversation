/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Saul Lopez Romero, Fernando Mijangos Varas
 * @version 3
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"
#include "character.h"

/*Maximun number of objects and spaces per game.*/
#define MAX_SPACES 100
#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100

/**
 * @brief Command
 *
 * This struct stores all the information related to a game.
 */
typedef struct _Game Game;

/**
 * @brief Searches for a character to the game structure.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param id id of the character to be searched.
 * @return Pointer to the character, NULL if an error takes place or the character wasn't found.
 */
Character *game_get_character(Game *game, Id id);

/**
 * @brief Adds a character to the game structure.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param character Pointer to the character.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief Gets the number of characters.
 * @author Saúl Lopez Romero
 *
 * @param game Pointer to the game.
 * @return Object number or -1 if an error takes place.
 */
int game_get_num_characters(Game * game);

/**
 * @brief Adds a space to the game structure.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param space Space to be added.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief It sets the number of spaces to zero, the ids to NO_ID, the last command is set to NO_CMD and the game is set to not finished
 * @author Saúl Lopez Romero
 *
 * @param game Pointer to the gama you want to reset.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_create(Game **game);

/**
 * @brief It loads all spaces data from the file and sets all the other values to zero.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game you want to create.
 * @param filename Name of the file with all the data.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_create_from_file(Game **game, char *filename);

/**
 * @brief It destroys all the information about the spaces, and the last command.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game you want to destroy.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_destroy(Game **game);

/**
 * @brief Locates an space by its id.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param id Id of the space.
 * @return Pointer to the space, if it exists.
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Returns the id of the space at that position.
 * @author Profesores PPROG
 *
 * @param game Pointer to the game.
 * @param position Position of the space you are looking for.
 * @return Id of the space at that position.
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief It returns a pointer to the player the game has.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @return The pointer to the player.
 */
Player *game_get_player(Game *game);

/**
 * @brief Returns the id of the space where the plater is at.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @param player Pointer to the player.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_set_player(Game *game, Player *player);

/**
 * @brief It returns a pointer to the object with the specified id.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game.
 * @param id Id of the object to be added.
 * @return Pointer to the object, NULL if it wasn't found.
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief It returns the id of the space where an object is located.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game.
 * @param id Object's id.
 * @return Id of the location of the object.
 */
Id game_get_object_location(Game *game, Id id);

/**
 * @brief It returns a pointer to the last command.
 * @author Profesores PPROG
 *
 * @param game Pointer to the game.
 * @return Pointer to the last command.
 */
Command *game_get_last_command(Game *game);

/**
 * @brief It sets the last command to the command you want
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 * @param command The command you want to set.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief Returns TRUE if the game has finished or FALSE if it hasn't.
 * @author Profesores PPROG
 *
 * @param game Pointer to the game.
 * @return TRUE if the game has finished or FALSE if it hasn't.
 */
Bool game_get_finished(Game *game);

/**
 * @brief it changes the value of the finished condition to what you want.
 * @author Profesores PPROG
 *
 * @param game Pointer to the game.
 * @param finished The Bool value you want to set it to (TRUE/FALSE).
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Prints on the terminal the number of spaces, the spaces, the location of the player, and the location of the object
 * @author Profesores PPROG
 *
 * @param game Pointer to the game.
 */
void game_print(Game *game);

/**
 * @brief Takes an object out of the game structure.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param object Pointer to the object to be taken out.
 * @return OK for a clean exit, otherwise ERROR (not found or other error.).
 */
Status game_take_object(Game *game, Object *object);

/**
 * @brief Links an object to the game structure.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param object Pointer to the object to be added.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief Gets an array with all the object's id from game.
 * Take into consideration that such array has to be freed by the
 * user, not by this function.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @return array with the ids, NULL if an exception occurs.
 */
Id *game_get_objects(Game *game);

/**
 * @brief Checks if an object is in the game.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param id Object's id.
 * @return -1 if an error takes place of the object wasn't found, the position of the object in the array otherwise.
 */
int game_has_object(Game *game, Id id);

/**
 * @brief Gets the number ob objects in the game.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @return Number ob objects, -1 for an error.
 */
int game_get_n_objects(Game *game);

/**
 * @brief Gets an object with a specfic tag inside the game
 * @author Fernando Mijangos
 * 
 * @param game Pointer to the game
 * @param word Tag of the object
 * @return Id of the object or NO_ID in any other case
 */
Id game_get_object_by_name(Game *game, char *word);

/**
 * @brief Sets the number of objects in the structure.
 * @author Saúl López Romero.
 *
 * @param game Game structure, where all the information related to game is included.
 * @param n_objects Object number to be set.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_set_n_objects(Game *game, int n_objects);
#endif
