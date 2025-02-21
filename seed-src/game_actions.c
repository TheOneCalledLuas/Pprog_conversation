/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG, Fernando Mijangos Varas.
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "player.h"

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
 */
void game_actions_take(Game *game);

/**
 * @brief Action to be executed when take command is given.
 * @author Fernando Mijangos Varas.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_drop(Game *game);

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
        game_actions_take(game);
        break;
    case DROP:
        game_actions_drop(game);
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

void game_actions_take(Game *game)
{
    /*Takes all the information I'll need.*/
    Player *player = game_get_player(game);
    Space *space = game_get_space(game, player_get_player_location(player));
    Id object = space_get_object(space);
    Id player_object = player_get_object(game_get_player(game));

    if (object != -1)
    {
        if (player_object != NO_ID)
        {
            /*If the player has an object it drops it.*/
            space_set_object(space, player_object);
        }
        else
        {
            /*If he doesnt have an object,
            the space gets a NULL as object pointer.*/
            space_set_object(space, NO_ID);
        }

        /*The player gets the object.*/
        player_set_object(player, object);
    }
    return;
}

void game_actions_drop(Game *game)
{
    /*Gets all the information it need.*/
    Id player_object = player_get_object(game_get_player(game));
    Player *player = game_get_player(game);
    Id player_location = player_get_player_location(game_get_player(game));
    Space *space = game_get_space(game, player_location);
    Id object = space_get_object(space);

    /*Checks if the player has an object, and if he has one, he drops it.*/
    if (player_object == NO_ID)
    {
        return;
    }

    /*Gives the object to the space and I take it out from the player.*/
    player_set_object(player, object);
    space_set_object(space, player_object);
    return;
}
