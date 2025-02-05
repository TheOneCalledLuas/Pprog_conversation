/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"

#define MAX_SPACES 100
#define MAX_OBJECTS 100

/**
 * @brief Command
 *
 * This struct stores all the information related to a game.
 */
typedef struct _Game
{
    Id player_location;             /*!< Id of the space where the player is at */
    Id object_location;             /*!< Id of the space where the object is at */
    Space *spaces[MAX_SPACES];      /*!< An array with the information of every space */
    Object *objects[MAX_OBJECTS];   /*!< An array with the information of every objects*/
    int n_spaces;                   /*!< Number of spaces*/
    int n_objects;                  /*!< Number of objects*/
    Command *last_cmd;              /*!< A pointer to the last command entered by the user */
    Bool finished;                  /*!< Whether the game has finished or not*/
} Game;

/** 
 * @brief adds a space to the game structure.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param space the space to be added.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief It sets the number of spaces to zero, the ids to NO_ID, the last command is set to NO_CMD and the game is set to not finished
 * @author Profesores PPROG
 *
 * @param game the pointer to the gama you want to reset
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_create(Game *game);

/**
 * @brief It loads all spaces data from the file and sets all the other values to zero 
 * @author Profesores PPROG
 *
 * @param game the pointer to the game you want to create
 * @param filename name of the file with all the data
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief it destroys all the information about the spaces, and the last command
 * @author Profesores PPROG
 *
 * @param game the pointer to the game you want to destroy
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_destroy(Game *game);

/**
 * @brief locates an space by its id.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param id id of the space
 * @return pointer to the space, if it exists.
 */
Space *game_get_space(Game *game, Id id);

/** 
 * @brief returns the id of the space at that position
 * @author Profesores PPROG
 * 
 * @param game the pointer to the game 
 * @param position the position of the space you are looking for
 * @return The id of the space at that position
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief It returns the id of the space where the player is at
 * @author Profesores PPROG
 *
 * @param game the pointer to the game
 * @return The id of the location of the player
 */
Id game_get_player_location(Game *game);

/**
 * @brief It sets the id of the player location space to what you want
 * @author Profesores PPROG
 *
 * @param game the pointer to the game
 * @param id id of the space you want the location of the player to be at
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief It returns the id of the space where the object is at
 * @author Profesores PPROG
 *
 * @param game the pointer to the game 
 * @return The id of the location of the object
 */
Id game_get_object_location(Game *game);

/**
 * @brief It sets the id of the object location space to what you want
 * @author Profesores PPROG
 *
 * @param game the pointer to the game
 * @param id id of the space you want the location of the object to be at
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_object_location(Game *game, Id id);

/**
 * @brief It returns a pointer to the last command 
 * @author Profesores PPROG
 *
 * @param game the pointer to the game
 * @return a pointer to the last command
 */
Command *game_get_last_command(Game *game);

/**
 * @brief It sets the last command to the command you want
 * @author Profesores PPROG
 *
 * @param game the pointer to the game
 * @param command the command you want to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief it returns TRUE if the game has finished or FALSE if it hasn't
 * @author Profesores PPROG
 *
 * @param game the pointer to the game
 * @return it returns TRUE if the game has finished or FALSE if it hasn't
 */
Bool game_get_finished(Game *game);

/**
 * @brief it changes the value of the finished condition to what you want
 * @author Profesores PPROG
 *
 * @param game the pointer to the game
 * @param finished the Bool value you want to set it to (TRUE/FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief finds the id of the space where the player is.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param position the number of the room where the player is.
 * @return OK for a clean exit, otherwise ERROR.
 */
Id game_reader_get_space_id_at(Game *game, int position);

/**
 * @brief it prints on the terminal the number of spaces, the spaces, the location of the player, and the location of the object 
 * @author Profesores PPROG
 * 
 * @param game the poitner to the game 
 * @return nothing
 */
void game_print(Game *game);

/**
 * @brief adds an object to the game structure.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param object the object to be added.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_add_object(Game *game, Object *object);

#endif
