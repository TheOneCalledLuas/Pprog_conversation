/**
 * @brief It implements the game update through user actions.
 *
 * @file game_actions.c
 * @author Fernando Mijangos Varas, Saúl López Romero.
 * @version 3
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "player.h"
#include "set.h"

/**
   Private functions
*/

/**
 * @brief Action to be executed when an unknown command is given.
 * @author Profesores PProg.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_unknown(Game *game);

/**
 * @brief Action to be executed when exit is given.
 * @author Profesores PProg.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_exit(Game *game);

/**
 * @brief Action to be executed when next command is given.
 * @author Profesores PProg.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_next(Game *game);

/**
 * @brief Action to be executed when back command is given.
 * @author Profesores PProg.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_back(Game *game);

/**
 * @brief Action to be executed when take command is given.
 * @author Fernando Mijangos Varas.
 *
 * @param game Pointer to the game structure.
 * @param word Name of the object to be taken
 */
void game_actions_take(Game *game, char *word);

/**
 * @brief Action to be executed when take command is given.
 * @author Fernando Mijangos Varas.
 *
 * @param game Pointer to the game structure.
 * @param word Name of the object that will be drop
 */
void game_actions_drop(Game *game, char *word);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command)
{
    CommandCode cmd;

    /*Error management.*/
    if (game == NULL || command == NULL)
    {
        return ERROR;
    }

    game_set_last_command(game, command);

    /*It gets the code given.*/
    cmd = command_get_code(command);

    /*It executes the function that corresponds to the code given.*/
    switch (cmd)
    {
    case UNKNOWN:
        game_actions_unknown(game);
        break;

    case EXIT:
        game_actions_exit(game);
        break;

    case NEXT:
        game_actions_next(game);
        break;

    case BACK:
        game_actions_back(game);
        break;
    case TAKE:
        game_actions_take(game, command_get_word(command));
        break;
    case DROP:
        game_actions_drop(game, command_get_word(command));
        break;
    default:
        break;
    }

    return OK;
}

/*
    Calls implementation for each action.
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    /*It gets the player location.*/
    space_id = player_get_player_location(game_get_player(game));
    if (space_id == NO_ID)
    {
        return;
    }

    /*Sets the player location to the id space south of him.*/
    current_id = space_get_south(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game_get_player(game), current_id);
    }

    return;
}

void game_actions_back(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    /*Gets the player location.*/
    space_id = player_get_player_location(game_get_player(game));
    if (NO_ID == space_id)
    {
        return;
    }

    /*Sets the player location it to the id space north of him.*/
    current_id = space_get_north(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game_get_player(game), current_id);
    }

    return;
}

void game_actions_take(Game *game, char *word)
{
    Player *player = NULL;
    Space *space = NULL;
    Id object = NO_ID;

    /*1-Gets all the different that it needs and error management.*/
    object=game_get_object_by_name(game, word);
    if(object==NO_ID)
    {
        return;
    }
    space = game_get_space(game, player_get_player_location(game_get_player(game)));
    if(space_find_object(space, object)==-1)
    {
        return;
    }
    player=game_get_player(game);

    /*2-Checks if the player already has the object. */
    if(player_find_object(player, object)!=-1)
    {
        return;
    }

    /*3-Player takes the object and error management.*/
    if(!player_add_object(player, object))
    {
        return;
    }
    if(!space_take_object(space, object))
    {
        return;
    }
    return;
}

void game_actions_drop(Game *game, char *word)
{
    Player *player=NULL;
    Space *space = NULL;
    Id object = NO_ID;

    /*1-Gets all the information it needs and error management.*/
    object=game_get_object_by_name(game, word);
    if(object==NO_ID)
    {
        return;
    }
    space = game_get_space(game, player_get_player_location(game_get_player(game)));
    if(space_find_object(space, object)!=-1)
    {
        return;
    }
    player=game_get_player(game);

    /*2-Checks if the player has the object.*/
    if(player_find_object(player, object)==-1)
    {
        return;
    }

    /*3-The player drops his object.*/
    if(!player_take_object(player, object))
    {
        return;
    }
    if(!space_add_object(space, object))
    {
        return;
    }
    return;
}
