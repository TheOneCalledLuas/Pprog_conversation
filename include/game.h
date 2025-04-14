/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Saul Lopez Romero, Fernando Mijangos, Raquel Anguita Martínez de Velasco
 * @version 3
 * @date 29-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H /*!<Game_h header.*/

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"
#include "character.h"
#include "link.h"

/*Maximun number of objects and spaces per game.*/
#define MAX_SPACES 100 /*!<Max spaces.*/
#define MAX_OBJECTS 100 /*!<Max objects.*/
#define MAX_CHARACTERS 100 /*!<Max characters.*/
#define MAX_LINKS 400 /*!<Max links.*/

/*Keywords to obtain last commands.*/
#define FIRST_LAST_COMMAND 0 /*!<First one from the back.*/
#define SECOND_LAST_COMMAND 1 /*!<Second one from the back.*/
#define THIRD_LAST_COMMAND 2 /*!<Third one from the back.*/
#define COMMANDS_SAVED 3 /*!<Number of commands saved.*/

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
 * @brief Gets one of the previously executed commands by the player.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param command_num Command to be returned (use FIRST_LAST_COMMAND, SECOND_LAST_COMMAND or THIRD_LAST_COMMAND)
 * @return Pointer to the command or NULL
 */
Command *game_get_previous_command(Game *game, int command_num);

/**
 * @brief Goes to the next command.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @return OK or ERROR
 */
Status game_next_command(Game *game);

/**
 * @brief It returns an array with the ids of the characters,
 *        IMPORTANT it returns something that has been allocated, you have to free it.
 * @author Fernando Mijangos
 *
 * @param game Game structure, where all the information related to game is included.
 * @return The array of ids of the character.
 *          IMPORTANT you have to free it afrter using it.
 */
Id *game_get_characters(Game *game);

/**
 * @brief Searches for a character and returns the id of the space where its located.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param id id of the character to be searched for.
 * @return Id of the space with the character, -1 if it wasn't found or -2 if an error takes place.
 */
Id game_get_character_location(Game *game, Id id);

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
int game_get_num_characters(Game *game);

/**
 * @brief Gets a character with a specfic name inside the game
 * @author Raquel Anguita Martínez de Velasco
 *
 * @param game Pointer to the game.
 * @param word Character's name.
 * @return Id of the character or NO_ID in any other case.
 */
Id game_get_character_by_name(Game *game, char *word);

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
 * @brief It sets the number of spaces to zero, the ids to NO_ID,
 * the last command is set to NO_CMD and the game is set to not finished
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
 * @brief Returns the number of players.
 * @author Saúl López Romero
 *
 * @param game pointer to the game.
 * @return number of players or -1 if an error takees place.
 */
int game_get_n_players(Game *game);

/**
 * @brief Returns the game turn.
 * @author Saúl López Romero
 *
 * @param game pointer to the game.
 * @return actual game turn or -1 if an error takes place.
 */
int game_get_turn(Game *game);

/**
 * @brief Returns a player by its turn number.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game.
 * @param player_number Turn number.
 */
Player *game_get_player(Game *game, int player_number);

/**
 * @brief Advances to the next turn.
 * @author Saúl López Romero
 *
 * @param game pointer to the game.
 * @return OK or ERROR.
 */
Status game_next_turn(Game *game);

/**
 * @brief Returns the next turn.
 * @author Saúl López Romero
 *
 * @param game pointer to the game.
 * @return next turn or -1 if an error takes place.
 */
int game_get_next_turn(Game *game);

/**
 * @brief Gets the actual player.
 * @author Saúl López Romero.
 *
 * @param game pointer to the game.
 * @return Pointer to the player or NULL in case of ERROR.
 */
Player *game_get_actual_player(Game *game);

/**
 * @brief Gets the last player.
 * @author Saúl López Romero.
 *
 * @param game pointer to the game.
 * @return Pointer to the player or NULL in case of ERROR.
 */
Player *game_get_last_player(Game *game);

/**
 * @brief Adds a player to the game.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param player Pointer to the player.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */

Status game_add_player(Game *game, Player *player);

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
 * @param game Pointer to the game.
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
 * @param game Pointer to the game.
 * @param word Tag of the object.
 * @return Id of the object or NO_ID in any other case.
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

/**
 * @brief Adds a link to the link array.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @param link Pointer to the new link.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief Deletes a link from the link array (used to delete all the information of the links in game_reader).
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @param position Position of the link in the array.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_delete_link(Game *game, int position);

/**
 * @brief Takes a link from the link array.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @param link_id Id of the link.
 * @return Pointer to the link with that id, or NULL if error.
 */
Link *game_find_link(Game *game, Id link_id);

/**
 * @brief Looks for the space situated at a given direction from a space.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @param space Id of the space from where the new space is searched.
 * @param direction Direction in which you search.
 * @return If it finds a space in that direction, it returns the id of that space, otherwise it returns
 *          NO_ID, returns ID_ERROR if any error.
 */
Id game_get_space_at(Game *game, Id space, Direction direction);

/**
 * @brief Gets the link information for a stace regarding the outgoing links.
 * @author Saúl López Romero.
 * 
 * @param game Pointer to the game.
 * @param space Id of the space.
 * @param dir Direction for the link.
 * @return Link information (OPENED or CLOSED) or UNK in case of error.
 */
Link_Property game_get_space_outcoming_connection_info(Game * game, Id space, Direction dir);
#endif
