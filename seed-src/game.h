/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 2
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

/*Maximun number of objects and spaces per game.*/
#define MAX_SPACES 100
#define MAX_OBJECTS 100

/**
 * @brief Command
 *
 * This struct stores all the information related to a game.
 */
typedef struct _Game
{
    Player *player;               /*!< Pointer to the player. */
    Object *object;               /*!< Pointer to the object. */
    Space *spaces[MAX_SPACES];    /*!< An array with the information of every space. */
    Object *objects[MAX_OBJECTS]; /*!< An array with the information of every objects.*/
    int n_spaces;                 /*!< Number of spaces.*/
    int n_objects;                /*!< Number of objects.*/
    Command *last_cmd;            /*!< A pointer to the last command entered by the user.*/
    Bool finished;                /*!< Whether the game has finished or not.*/
} Game;

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
Status game_create(Game *game);

/**
 * @brief It loads all spaces data from the file and sets all the other values to zero.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game you want to create.
 * @param filename Name of the file with all the data.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief It destroys all the information about the spaces, and the last command.
 * @author S
 *
 * @param game Pointer to the game you want to destroy.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_destroy(Game *game);

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
Player* game_get_player(Game *game);
 
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
 * @brief It returns a pointer to the object.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game.
 * @return Pointer to the object.
 */
Object *game_get_object(Game *game);

/**
 * @brief It returns the id of the space where the object is at
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game.
 * @return Id of the location of the object.
 */
Id game_get_object_location(Game *game);

/**
 * @brief It sets the id of the object location space to what you want
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @param id Id of the space you want the location of the object to be at.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
Status game_set_object_location(Game *game, Id id);

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
 * @brief Finds the id of the space where the player is.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param position Number of the room where the player is.
 * @return OK for a clean exit, otherwise ERROR.
 */
Id game_reader_get_space_id_at(Game *game, int position);

/**
 * @brief Prints on the terminal the number of spaces, the spaces, the location of the player, and the location of the object
 * @author Profesores PPROG
 *
 * @param game Pointer to the game.
 */
void game_print(Game *game);

/**
 * @brief Links an object to the game structure.
 * @author Saúl López Romero
 *
 * @param game Game structure, where all the information related to game is included.
 * @param object Pointer to the object to be added.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_set_object(Game *game, Object *object);
#endif
