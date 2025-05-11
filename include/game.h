/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Saúl Lopez Romero, Fernando Mijangos, Raquel Anguita Martínez de Velasco
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
#define MAX_SPACES 100     /*!<Max spaces.*/
#define MAX_OBJECTS 100    /*!<Max objects.*/
#define MAX_CHARACTERS 100 /*!<Max characters.*/
#define MAX_LINKS 400      /*!<Max links.*/

/*Keywords to obtain last commands.*/
#define FIRST_LAST_COMMAND 0  /*!<First one from the back.*/
#define SECOND_LAST_COMMAND 1 /*!<Second one from the back.*/
#define THIRD_LAST_COMMAND 2  /*!<Third one from the back.*/
#define COMMANDS_SAVED 3      /*!<Number of commands saved.*/

/**
 * @brief Command
 *
 * This struct stores all the information related to a game.
 */
typedef struct _Game Game;

#include "gamerules.h"
#include "animation.h"
/**
 * @brief Returns the animation manager.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @return Pointer to the animation manager or NULL if an error takes place.
 */
Animation_Manager *game_get_animation_manager(Game *game);

/**
 * @brief Returns the number of teams.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @return Number of teams or FUNCTION_ERROR if an error takes place.
 */
int game_get_n_teams(Game *game);

/**
 * @brief Sets if the game is determined.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param is_determined If the game is determined or not.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_set_determined(Game *game, Bool is_determined);

/**
 * @brief Gets if the game is determined.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @return If the game is determined or not, or FALSE if an error takes place.
 */
Bool game_get_determined(Game *game);

/**
 * @brief Returns a random number in a range.
 * @author Saúl López Romero
 *
 * @param start First number of the range.
 * @param end Last number in the range.
 * @return Random int number in the range.
 */
int game_random_int(int start, int end);

/**
 * @brief Sets the number of teams.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param n_teams Number of existent teams to be set.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_set_n_teams(Game *game, int n_teams);

/**
 * @brief Creates a team with two players, the id of the team will be the id of the leader one.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param player_leader Id of the player who will be the leader of the team.
 * @param player_member Id of the player who will be the member of the team.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_create_team(Game *game, Id player_leader, Id player_member);

/**
 * @brief Destroys a team, setting the id of the players to NO_ID.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param player Id of the player who will be the leader of the team.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_destroy_team(Game *game, Id player);

/**
 * @brief Gets the id of the player who is allyed with the first one.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param player Id of the player who will be the leader of the team.
 * @return Id of the member of the team or NO_ID if an error takes place or the player isn't teamed.
 */
Id game_get_teammate_from_player(Game *game, Id player);

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
 * @return Id of the space with the character, FUNCTION_ERROR if it wasn't found or -2 if an error takes place.
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
 * @return Object number or FUNCTION_ERROR if an error takes place.
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
 * @author Saúl Lopez Romero
 *
 * @param game Pointer to the game you want to create.
 * @param filename Name of the file with all the data.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_create_from_file(Game **game, char *filename);

/**
 * @brief It returns the number of animations loaded in the game.
 * @author Saúl Lopez Romero
 *
 * @param game Pointer to the game structure.
 * @return Number of animations in the game or FUNCTION_ERROR if an error takes place.
 */
int game_get_n_animations(Game *game);

/**
 * @brief It searches for a link by its name.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game structure.
 * @param name Name of the link to be searched.
 * @return Pointer to the link, NULL if it wasn't found or an error took place.
 */
Link *game_get_link_by_name(Game *game, char *name);

/**
 * @brief It destroys all the information about the spaces, and the last command.
 * @author Saúl Lopez Romero
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
 * @brief returns the game values.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @return Pointer to the game values or NULL.
 */
Game_values *game_get_game_values(Game *game);

/**
 * @brief Returns the id of the space at that position.
 * @author Saúl López Romero
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
 * @return number of players or FUNCTION_ERROR if an error takees place.
 */
int game_get_n_players(Game *game);

/**
 * @brief Returns the game turn.
 * @author Saúl López Romero
 *
 * @param game pointer to the game.
 * @return actual game turn or FUNCTION_ERROR if an error takes place.
 */
int game_get_turn(Game *game);

/**
 * @brief Returns a player by its turn number.
 * @author Saúl Lopez Romero
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
 * @brief Sets the turn to the one you want, this should only be used by game_manager
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @param turn Turn number.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_set_turn(Game *game, int turn);

/**
 * @brief Returns the next turn.
 * @author Saúl López Romero
 *
 * @param game pointer to the game.
 * @return next turn or FUNCTION_ERROR if an error takes place.
 */
int game_get_next_turn(Game *game);

/**
 * @brief Searches for a link with a specific id
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param link Id of the link to be searched
 * @return Pointer to the link, NULL if error
 */
Link *game_get_link(Game *game, Id link);

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
 * @author Saúl Lopez Romero
 *
 * @param game Pointer to the game.
 * @param id Id of the object to be added.
 * @return Pointer to the object, NULL if it wasn't found.
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief It returns the id of the space where an object is located.
 * @author Saúl Lopez Romero
 *
 * @param game Pointer to the game.
 * @param id Object's id.
 * @return Id of the location of the object.
 */
Id game_get_object_location(Game *game, Id id);

/**
 * @brief It returns a pointer to the last command.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @return Pointer to the last command.
 */
Command *game_get_last_command(Game *game);

/**
 * @brief It sets the last command to the command you want
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param command The command you want to set.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief Returns TRUE if the game has finished or FALSE if it hasn't.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @return TRUE if the game has finished or FALSE if it hasn't.
 */
Bool game_get_finished(Game *game);

/**
 * @brief it changes the value of the finished condition to what you want.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @param finished The Bool value you want to set it to (TRUE/FALSE).
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Prints on the terminal the number of spaces, the spaces, the location of the player, and the location of the object
 * @author Fernando Mijangos
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
 * @return FUNCTION_ERROR if an error takes place of the object wasn't found, the position of the object in the array otherwise.
 */
int game_has_object(Game *game, Id id);

/**
 * @brief Gets the number ob objects in the game.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @return Number ob objects, FUNCTION_ERROR for an error.
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
 * @brief Deletes a link from the link array (used to delete all the information of the links in game_manager).
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
 * @brief Looks how many followers a player has
 * @author Raquel Anguita
 *
 * @param game Pointer to the game
 * @param player Id of the player you want the information from
 * @return Number of followers of that player, FUNCTION_ERROR if error
 */
int game_get_n_followers(Game *game, Id player);

/**
 * @brief Gets the link information for a stace regarding the outgoing links.
 * @author Saúl López Romero.
 *
 * @param game Pointer to the game.
 * @param space Id of the space.
 * @param dir Direction for the link.
 * @return Link information (OPENED or CLOSED) or UNK in case of error.
 */
Link_Property game_get_space_outcoming_connection_info(Game *game, Id space, Direction dir);

/**
 * @brief It gets the player by its name.
 * @author Saúl Lopez Romero.
 *
 * @param game Pointer to the game.
 * @param name Name of the player.
 * @return Id of the player, NO_ID if it doesn't exist, ID_ERROR if an error takes place.
 */
Id game_get_player_by_name(Game *game, char *name);

/**
 * @brief It gets the player by its id.
 * @author Saúl Lopez Romero.
 *
 * @param game Pointer to the game.
 * @param id Id of the player.
 * @return Pointer to the player, NULL if it doesn't exist or an error takes place.
 */
Player *game_get_player_by_id(Game *game, Id id);

/**
 * @brief It gets an initialized array with the players ids.
 *          IMPORTANT you have to free it after using it.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @return Array of ids of the players, NULL if an error takes place.
 *      IMPORTANT you have to free it after using it.
 *
 */
Id *game_get_players(Game *game);

/**
 * @brief It gets an initialized array with the spaces ids.
 *         IMPORTANT you have to free it after using it.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @return Array of ids of the spaces, NULL if an error takes place.
 *         IMPORTANT you have to free it after using it.
 */
Id *game_get_spaces(Game *game);

/**
 * @brief It gets the number of spaces in the game.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @return Number of spaces in the game, FUNCTION_ERROR if an error takes place.
 */
int game_get_n_spaces(Game *game);

/**
 * @brief It gets an initialized array with the links ids.
 *         IMPORTANT you have to free it after using it.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @return Array of ids of the links, NULL if an error takes place.
 *         IMPORTANT you have to free it after using it.
 */
Id *game_get_links(Game *game);

/**
 * @brief It gets the number of links in the game.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @return Number of links in the game, FUNCTION_ERROR if an error takes place.
 */
int game_get_n_links(Game *game);

/**
 * @brief It gets an initialized array with the objects ids.
 *         IMPORTANT you have to free it after using it.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @return Array of ids of the objects, NULL if an error takes place.
 *        IMPORTANT you have to free it after using it.
 */
Id *game_get_gamerules(Game *game);

/**
 * @brief It gets the number of gamerules in the game.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game.
 * @return Number of gamerules in the game, FUNCTION_ERROR if an error takes place.
 */
int game_get_n_gamerules(Game *game);

/**
 * @brief Adds a new savefile name to the game structure
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param name Pointer to the name
 * @return OK if everything went well, ERROr othewise
 */
Status game_add_savefile(Game *game, char *name);

/**
 * @brief Adds a new savefile, creating a new file for it and adding its name to the game structure
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param name Pointer to the name
 * @return Ok if everything went well, ERROR otherwise
 */
Status game_add_new_savefile(Game *game, char *name);

/**
 * @brief Deletes a savefile, deleting its file and removing it from the game strucutre
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param name Pointer to the name
 * @return OK if everythig went well, ERROR otherwise
 */
Status game_delete_savefile(Game *game, char *name);

/**
 * @brief Gets the number of savefiles there are
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @return Number of existing savefiles, FUNCTION_ERROR if error
 */
int game_get_n_savefiles(Game *game);

/**
 * @brief Sets the number of savefiles to what you want
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param n New number of savfiles
 * @return OK if everything went well, ERROR otherwise
 */
Status game_set_n_savefiles(Game *game, int n);

/**
 * @brief It gets the name of a savefile in a position of the array
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param n Position you want the name for
 * @return Pointer to the name of the savefile in that position, NULL if ERROR
 */
char *game_get_savefile(Game *game, int n);

/**
 * @brief It gets the name of the current savefile
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @return Pointer to the name of the current savefile, NULL if ERROR
 */
char *game_get_current_savefile(Game *game);

/**
 * @brief It sets the name of the current savefile to what you want
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param name Name of the savefile you want to set as current
 * @return OK if everything went well, ERROR otherwise
 */
Status game_set_current_savefile(Game *game, char *name);

/**
 * @brief It moves all the players to a room.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param room Id of the room where you want to move the players.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_move_all_players(Game *game, Id room);

/**
 * @brief Gets all the character to unfollow.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @return OK or ERROR.
 */
Status game_unfollow_all(Game *game);

/**
 * @brief Vanishes an object from the game.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param object Id of the object to be taken.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_vanish_object(Game *game, Id object);

/**
 * @brief makes the player, drop all the objects in his inventory dependent on another object.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param object Pointer to the object.
 * @param player Pointer to the player.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_drop_all_dependant(Game *game, Object *object, Player *player);

#endif
