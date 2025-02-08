/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
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

void game_actions_unknown(Game *game);

void game_actions_exit(Game *game);

void game_actions_next(Game *game);

void game_actions_back(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command)
{
    CommandCode cmd;

    /*Error management.*/
    if(game==NULL || command==NULL)
    {
        return ERROR;
    }

    game_set_last_command(game, command);

    cmd = command_get_code(command);

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

    default:
        break;
    }

    return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = player_get_player_location(game_get_player(game));
    if (space_id == NO_ID)
    {
        return;
    }

    current_id = space_get_south(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game->player,current_id);
    }

    return;
}

void game_actions_back(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = player_get_player_location(game_get_player(game));
    if (NO_ID == space_id)
    {
        return;
    }

    current_id = space_get_north(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game->player, current_id);
    }

    return;
}
