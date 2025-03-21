/**
 * @brief It implements the game update through user actions.
 *
 * @file game_actions.c
 * @author Fernando Mijangos, Saúl López Romero
 * @version 3
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "player.h"
#include "set.h"

#define ATTACK_PROB 9  /*Chances to attack.*/
#define SUCCESS_PROB 2 /*Chances to strike (the smaller the better).*/

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
 * @brief Action to be executed when left command is given.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_left(Game *game);

/**
 * @brief Action to be executed when right command is given.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_right(Game *game);

/**
 * @brief Action to be executed when take command is given.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_take(Game *game);

/**
 * @brief Action to be executed when drop command is given.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_drop(Game *game);

/**
 * @brief Action to be executed when chat command is given.
 * @author Saul Lopez Romero
 *
 * @param game Pointer to the game structure.
 */
void game_actions_chat(Game *game);

/**
 * @brief Action to be executed when attack command is given.
 * @author Saul López Romero
 *
 * @param game Pointer to the game structure.
 */
void game_actions_attack(Game *game);

/**
 * @brief Returns a random number in a range.
 * @author Saul López Romero
 *
 * @param start First number of the range.
 * @param end Last number in the range.
 * @return Random int number in the range.
 */
int random_int(int start, int end);

/**
   Game actions implementation.
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
        command_set_status(game_get_last_command(game), OK);
        game_actions_unknown(game);
        break;

    case EXIT:
        command_set_status(game_get_last_command(game), OK);
        game_actions_exit(game);
        break;

    case NEXT:
        game_actions_next(game);
        break;

    case BACK:
        game_actions_back(game);
        break;
    case LEFT:
        game_actions_left(game);
        break;
    case RIGTH:
        game_actions_right(game);
        break;
    case TAKE:
        game_actions_take(game);
        break;
    case DROP:
        game_actions_drop(game);
        break;
    case CHAT:
        game_actions_chat(game);
        break;
    case ATTACK:
        game_actions_attack(game);
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
    space_id = player_get_player_location(game_get_actual_player(game));
    if (space_id == NO_ID || space_id == ID_ERROR)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Sets the player location to the id space south of him.*/
    current_id = space_get_south(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game_get_actual_player(game), current_id);
    }
    else
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_back(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    /*Gets the player location.*/
    space_id = player_get_player_location(game_get_actual_player(game));
    if (NO_ID == space_id || ID_ERROR == space_id)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Sets the player location it to the id space north of him.*/
    current_id = space_get_north(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game_get_actual_player(game), current_id);
    }
    else
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_left(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    /*Gets the player location.*/
    space_id = player_get_player_location(game_get_actual_player(game));
    if (NO_ID == space_id || ID_ERROR == space_id)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Sets the player location it to the id space north of him.*/
    current_id = space_get_west(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game_get_actual_player(game), current_id);
    }
    else
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_right(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    /*Gets the player location.*/
    space_id = player_get_player_location(game_get_actual_player(game));
    if (NO_ID == space_id || ID_ERROR == space_id)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Sets the player location it to the id space north of him.*/
    current_id = space_get_east(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        player_set_player_location(game_get_actual_player(game), current_id);
    }
    else
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_take(Game *game)
{
    Player *player = NULL;
    Space *space = NULL;
    Id object = NO_ID;

    /*Error management.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*1-Gets all the different things it needs and error management.*/
    object = game_get_object_by_name(game, command_get_word(game_get_last_command(game)));
    if (object == NO_ID || object == ID_ERROR)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    space = game_get_space(game, player_get_player_location(game_get_actual_player(game)));
    if (space_find_object(space, object) == NO_ID)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    player = game_get_actual_player(game);

    /*2-Checks if the player already has an object.*/
    if (player_get_object(player) != NO_ID)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*3-Player takes the object and error management.*/
    if (!player_set_object(player, object))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    if (!space_take_object(space, object))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_drop(Game *game)
{
    Player *player = NULL;
    Space *space = NULL;
    Id object = NO_ID;

    /*Error management.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*1-Gets all the information it needs and error management.*/
    object = player_get_object(game_get_actual_player(game));
    if (object == NO_ID || object == ID_ERROR)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    space = game_get_space(game, player_get_player_location(game_get_actual_player(game)));
    if (space_find_object(space, object) != NO_ID)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    player = game_get_actual_player(game);

    /*2-Checks if the player has an object.*/
    if (player_get_object(player) == NO_ID)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*3-The player drops his object.*/
    if (!player_set_object(player, NO_ID))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    if (!space_add_object(space, object))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*4-Clean exit.*/
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_chat(Game *game)
{
    /*The chat action is managed by graphic engine; it starts as an error and
    if it goes as it should the error code is set to OK. */
    command_set_status(game_get_last_command(game), ERROR);
    return;
}

void game_actions_attack(Game *game)
{
    int rand_num = 0;
    Id player_location = NO_ID;
    Player *player = NULL;
    Bool has_character = FALSE;
    Character *character = NULL;

    /*Error handling.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    /*Checks that the player meets the requirements to attack.*/
    player = game_get_actual_player(game);
    player_location = player_get_player_location(player);
    has_character = space_get_character(game_get_space(game, player_location)) != NO_ID;
    if (!has_character)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    character = game_get_character(game, space_get_character(game_get_space(game, player_location)));

    if (character_get_friendly(character) == FALSE && character_get_health(character) > 0 && player_get_health(player) > 0)
    {
        /*Starts a fight between the entities.*/
        rand_num = random_int(0, ATTACK_PROB);
        if (rand_num <= (ATTACK_PROB) / SUCCESS_PROB)
        {
            /*Hits player.*/
            player_set_health(player, player_get_health(player) - 1);
        }
        else
        {
            /*Hits character.*/
            character_set_health(character, character_get_health(character) - 1);
        }
        /*Checks if the player died.*/
        if (player_get_health(player) <= 0)
        {
            game_set_finished(game, TRUE);
        }
        command_set_status(game_get_last_command(game), OK);
        return;
    }
    command_set_status(game_get_last_command(game), ERROR);
}

int random_int(int start, int end)
{
    /*Srand was called beforehand.*/

    /*Returns the number.*/
    return (start + rand() % (start - end + 1));
}