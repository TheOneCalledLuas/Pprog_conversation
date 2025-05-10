/**
 * @brief It implements the game update through user actions.
 *
 * @file game_actions.c
 * @author Fernando Mijangos, Saul López Romero
 * @version 3
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "game.h"
#include "player.h"
#include "set.h"
#include "character.h"

#define ATTACK_PROB 9    /*!<Chances to attack.*/
#define SUCCESS_PROB 2   /*!<Chances to strike (the smaller the better).*/
#define DAMAGE_DEALT 1   /*!<Amount of health the entity losses when hurt.*/
#define MIN_HEALTH 0     /*!<Minimum health the entity can have before dying.*/
#define N_DIRECTIONS 6   /*!<Number of directions.*/
#define N_VARIATIONS 2   /*!<Number of possible ways to call each direction.*/
#define DEAD_ANIMATION 2 /*!<Animation for the player dead.*/

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
 * @brief Moves the active player in that direction.
 * @author Fernando Mijangos.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_move(Game *game);

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
 * @author Saul López Romero
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
 * @brief Action to be executed when inspect command is given.
 * @author Saul López Romero
 *
 * @param game Pointer to the game structure.
 */
void game_actions_inspect(Game *game);

/**
 * @brief Action to be executed when abando command is given.
 * @author Raquel Anguita
 *
 * @param game Pointer to the game structure.
 */
void game_actions_abandon(Game *game);

/**
 * @brief Action to be executed when recruit command is given.
 * @author Raquel Anguita
 *
 * @param game Pointer to the game structure.
 */
void game_actions_recruit(Game *game);

/**
 * @brief Action to be executed when exit is given.
 * @author Profesores PProg.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_use(Game *game);

/**
 * @brief Action to be executed when exit is given.
 * @author Saul Lopez.
 *
 * @param game Pointer to the game structure.
 */
void game_actions_open(Game *game);

/**
 * @brief Action to be executed when save command is given.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game structure.
 */
void game_actions_save(Game *game);

/**
 * @brief Action to be executed when menu command is given.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game structure.
 */
void game_actions_menu(Game *game);

/**
 * @brief Action to be executed when wait command is given.
 * @author Saul López Romero
 *
 * @param game Pointer to the game structure.
 */
void game_actions_wait(Game *game);

/**
 * @brief Action to be executed when coop command is given.
 * @author Saul López Romero
 *
 * @param game Pointer to the game structure.
 */
void game_actions_coop(Game *game);

/**
 * @brief Action to be executed when coop command is given.
 * @author Saul López Romero
 *
 * @param game Pointer to the game structure.
 */
void game_actions_uncoop(Game *game);

/**
 * @brief IT shows up your inventory inside the map section
 * @author Fernando Mijangos
 *
 * @param game
 */
void game_actions_bag(Game *game);

/**
 * @brief It shows up the map in the map section
 * @author Fernando Mijangos
 *
 * @param game
 */
void game_actions_map(Game *game);

/**
 * @brief It shows up the help place
 * @author Fernando Mijangos
 *
 * @param game
 */
void game_actions_help(Game *game);

/*
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

    case MOVE:
        game_actions_move(game);
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

    case INSPECT:
        game_actions_inspect(game);
        break;

    case ABANDON:
        game_actions_abandon(game);
        break;

    case RECRUIT:
        game_actions_recruit(game);
        break;
    case SAVE:
        game_actions_save(game);
        break;
    case MENU:
        game_actions_menu(game);
        break;
    case USE:
        game_actions_use(game);
        break;
    case OPEN:
        game_actions_open(game);
        break;
    case BAG:
        game_actions_bag(game);
        break;
    case MAP:
        game_actions_map(game);
        break;
    case WAIT:
        game_actions_wait(game);
        break;
    case COOP:
        game_actions_coop(game);
        break;
    case UNCOOP:
        game_actions_uncoop(game);
        break;
    case HELP:
        game_actions_help(game);
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

void game_actions_move(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;
    Id *characters = NULL;
    Player *player = NULL, *mate = NULL;
    Direction direction = UNK_DIRECTION;
    int i = 0;
    Bool is_teamed = FALSE;

    /*List with all the possible directions the player can move towards.*/
    char *dir_from_string[N_DIRECTIONS][N_VARIATIONS] = {{"n", "north"}, {"s", "south"}, {"e", "east"}, {"w", "west"}, {"u", "up"}, {"d", "down"}};

    /*Gets the player location.*/
    player = game_get_actual_player(game);
    if (!player)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Gets the player team, if existent.*/
    if (player_get_team(player) != NO_ID)
    {
        is_teamed = TRUE;
        mate = game_get_player_by_id(game, game_get_teammate_from_player(game, player_get_player_id(player)));
    }
    space_id = player_get_player_location(player);
    if (NO_ID == space_id || ID_ERROR == space_id)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Gets the direction in which the player will move*/
    while (direction == UNK_DIRECTION && i < N_DIRECTIONS)
    {
        if (strcasecmp(command_get_argument(game_get_last_command(game), 0), dir_from_string[i][CMDS]) == 0 || strcasecmp(command_get_argument(game_get_last_command(game), 0), dir_from_string[i][CMDL]) == 0)
        {
            direction = i;
        }
        else
        {
            i++;
        }
    }
    if (direction == UNK_DIRECTION)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Sets the player location it to the id space in that direction of him.*/
    current_id = game_get_space_at(game, space_id, direction);
    if (game_get_space_outcoming_connection_info(game, space_id, direction) != OPENED)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    if (current_id != NO_ID && current_id != ID_ERROR)
    {
        /*Removes the characters that are following the player from the space they are at, if the conditions are met*/
        if (!(characters = game_get_characters(game)))
        {
            command_set_status(game_get_last_command(game), ERROR);
            return;
        }
        for (i = 0; i < game_get_num_characters(game); i++)
        {
            if (character_get_follow(game_get_character(game, characters[i])) == player_get_player_id(player))
            {
                space_take_character(game_get_space(game, space_id), characters[i]);
            }
        }
        player_set_player_location(player, current_id);

        /*If the player is teamed moves his teammate to the other room.*/
        if (is_teamed)
        {
            player_set_player_location(mate, current_id);
            /*Moves the characters that are following the player to the new space*/
            for (i = 0; i < game_get_num_characters(game); i++)
            {
                if (character_get_follow(game_get_character(game, characters[i])) == player_get_player_id(mate))
                {
                    space_take_character(game_get_space(game, space_id), characters[i]);
                    if (character_get_follow(game_get_character(game, characters[i])) == player_get_player_id(mate))
                    {
                        space_add_character(game_get_space(game, current_id), characters[i]);
                    }
                }
            }
        }

        for (i = 0; i < game_get_num_characters(game); i++)
        {
            if (character_get_follow(game_get_character(game, characters[i])) == player_get_player_id(player))
            {
                space_add_character(game_get_space(game, current_id), characters[i]);
            }
        }
    }
    else
    {
        free(characters);
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    free(characters);
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_take(Game *game)
{
    Player *player = NULL;
    Space *space = NULL;
    Id object = NO_ID, dependency = NO_ID;

    /*Error management.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*1-Gets all the different things it needs and error management.*/
    object = game_get_object_by_name(game, command_get_argument(game_get_last_command(game), 0));
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

    /*1.2.-CHecks if the object can be taken.*/
    if (object_get_movable(game_get_object(game, object)) == FALSE)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*1.3.-Checks the object dependency.*/
    if ((dependency = object_get_dependency(game_get_object(game, object))) > NO_ID)
    {
        if (!player_has_object(player, dependency))
        {
            command_set_status(game_get_last_command(game), ERROR);
            return;
        }
    }

    /*3-Player takes the object and error management.*/
    if (!player_add_object(player, object))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    /*4-The object is taken out of the space.*/
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
    Object *p_object = NULL;

    /*Error management.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*1-Gets all the information it needs and error management.*/
    object = game_get_object_by_name(game, command_get_argument(game_get_last_command(game), 0));
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

    /*2-Checks if the player hasn't got the object.*/
    if (player_has_object(player, object) == FALSE)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*3-The player drops his object and all the ones which depended of it.*/
    if (player_del_object(player, object) == ERROR)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    if (!space_add_object(space, object))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    p_object = game_get_object(game, object);
    if (!p_object)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    game_drop_all_dependant(game, p_object, player);

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
    int rand_num = 0, coop_dmg = 0;
    Id player_location = NO_ID;
    Player *player = NULL;
    Character *character = NULL;

    /*Error handling.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    player = game_get_actual_player(game);
    player_location = player_get_player_location(player);

    /*1-If it doesnt find the character you are trying to attack, return ERROR.*/
    if (!(character = game_get_character(game, game_get_character_by_name(game, command_get_argument(game_get_last_command(game), 0)))))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    if (space_find_character(game_get_space(game, player_location), character_get_id(character)) == -1)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    coop_dmg = (player_get_team(player) != NO_ID) ? 1 : 0;

    /*2-If that character isnt friendly, attack it*/
    if (character_get_friendly(character) == FALSE && character_get_health(character) > MIN_HEALTH && player_get_health(player) > MIN_HEALTH)
    {
        /*Starts a fight between the entities.*/
        /*Checks if the game is in determinist mode.*/
        if (!game_get_determined(game))
        {
            rand_num = game_random_int(0, ATTACK_PROB);
        }
        else
        {
            /*If the game is in determinist mode, the player always wins.*/
            rand_num = ATTACK_PROB + 1;
        }
        if (rand_num <= (ATTACK_PROB) / SUCCESS_PROB)
        {
            /*Hits player.*/
            player_set_health(player, player_get_health(player) - DAMAGE_DEALT);
        }
        else
        {
            /*Hits character.*/
            character_set_health(character, character_get_health(character) - (DAMAGE_DEALT + coop_dmg + game_get_n_followers(game, player_get_player_id(player))));
        }
        /*Checks if the player died.*/
        if (player_get_health(player) <= MIN_HEALTH)
        {
            animation_run(game_get_animation_manager(game), DEAD_ANIMATION);
        }
        command_set_status(game_get_last_command(game), OK);
        return;
    }
    command_set_status(game_get_last_command(game), ERROR);
}

void game_actions_inspect(Game *game)
{
    /*The inspect action is managed by graphic engine; it starts as an error and
    if it goes as it should the error code is set to OK, similar to chat. */
    command_set_status(game_get_last_command(game), ERROR);
    return;
}

void game_actions_recruit(Game *game)
{
    Player *player = NULL;
    Character *character = NULL;
    Id player_location = NO_ID;
    Bool same_character = FALSE;

    /*Error handling.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Checks that the player meets the requirements to recruit.*/
    player = game_get_actual_player(game);
    player_location = player_get_player_location(player);
    character = game_get_character(game, game_get_character_by_name(game, command_get_argument(game_get_last_command(game), 0)));
    same_character = (space_find_character(game_get_space(game, player_location), character_get_id(character)) != -1);
    if (same_character == FALSE || character_get_follow(character) != NO_ID)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Actual command.*/
    if (character_get_friendly(character) == TRUE && character_get_health(character) > MIN_HEALTH)
    {
        if (character_set_follow(character, player_get_player_id(player)) == ERROR)
        {
            command_set_status(game_get_last_command(game), ERROR);
        }
        command_set_status(game_get_last_command(game), OK);
        return;
    }
    command_set_status(game_get_last_command(game), ERROR);
}

void game_actions_abandon(Game *game)
{
    Player *player = NULL;
    Character *character = NULL;
    Id following_player = NO_ID;

    /*Error handling.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Checks that the player meets the requirements to abandon.*/
    player = game_get_actual_player(game);
    character = game_get_character(game, game_get_character_by_name(game, command_get_argument(game_get_last_command(game), 0)));
    following_player = character_get_follow(character);
    if (following_player != player_get_player_id(player))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Actual command.*/
    if (character_get_follow(character) != NO_ID && character_get_follow(character) != ID_ERROR)
    {
        if (character_set_follow(character, NO_ID) == ERROR)
        {
            command_set_status(game_get_last_command(game), ERROR);
            return;
        }
        command_set_status(game_get_last_command(game), OK);
        return;
    }
    command_set_status(game_get_last_command(game), ERROR);
}

void game_actions_use(Game *game)
{
    Space *last_space = NULL;
    Id object_id = ID_ERROR;
    Player *player = NULL;
    Object *object = NULL;
    char *entity = NULL;
    Id target = NO_ID, team_id = NO_ID;
    Bool do_take = FALSE;
    Bool coop_reeachable = FALSE;

    /*Error handling.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Gets all the necessary information.*/
    player = game_get_actual_player(game);
    object_id = game_get_object_by_name(game, command_get_argument(game_get_last_command(game), FIRST_ARG));
    last_space = game_get_space(game, player_get_player_location(player));

    /*Checks that the player meets the requirements to use the provided object.*/
    if (object_id <= NO_ID)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Searches if the object is reachable via a coop.*/
    if (player_get_team(player) != NO_ID)
    {
        if ((team_id = game_get_teammate_from_player(game, player_get_player_id(player))) != NO_ID)
        {
            coop_reeachable = player_has_object(game_get_player(game, team_id), object_id);
        }
    }

    /*Searches if the object is reachable.*/
    if (object_id >= 0 && (space_find_object(last_space, object_id) != -1 || player_has_object(player, object_id) || coop_reeachable))
    {
        /*If the object was found anywhere accesible by the player.*/
        object = game_get_object(game, object_id);
    }
    else
    {
        /*The object isn't reachable.*/
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Does the special case where the object has a special use manged by a gamerule.*/
    if (object_get_special_use(object))
    {
        object_set_is_used(object, TRUE);
        command_set_status(game_get_last_command(game), OK);
        return;
    }

    /*If the object can't be used with use it ends here.*/
    if (object_get_health(object) == 0)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Checks where to use the object.*/
    if (strcasecmp(command_get_argument(game_get_last_command(game), SECOND_ARG), "over") == 0)
    {
        /*The object is intended to be used over a specific entity.*/
        entity = command_get_argument(game_get_last_command(game), THIRD_ARG);
        /*Checks if the entity was a player or a character.*/
        if ((target = game_get_player_by_name(game, entity)) >= 0)
        {
            /*The object was used over an actual player.*/
            player_set_health(game_get_player_by_id(game, target), player_get_health(player) + object_get_health(object));
            do_take = TRUE;
            object_set_is_used(object, TRUE);
            command_set_status(game_get_last_command(game), OK);
        }
        else if (game_get_character_by_name(game, entity) != NO_ID)
        {
            /*The object was used over a character.*/
            character_set_health(game_get_character(game, game_get_character_by_name(game, entity)), character_get_health(game_get_character(game, game_get_character_by_name(game, entity))) + object_get_health(object));
            command_set_status(game_get_last_command(game), OK);
            object_set_is_used(object, TRUE);
            do_take = TRUE;
        }
        else
        {
            /*The object was used over an invalid entity.*/
            command_set_status(game_get_last_command(game), ERROR);
            return;
        }
    }
    else
    {
        /*The object was used over the actual player.*/
        player_set_health(player, player_get_health(player) + object_get_health(object));
        object_set_is_used(object, TRUE);
        command_set_status(game_get_last_command(game), OK);
        do_take = TRUE;
    }

    /*Checks if the object has to be taken out.*/
    if (do_take)
    {
        /*Tries to take the object from the space AND inventory. If the object isn't there, it must be on one of them
          and it won't happen anything if the object isn't there  when we try to take it out.*/
        if (coop_reeachable && player_has_object(game_get_player_by_id(game, team_id), object_id))
        {
            player_del_object(game_get_player_by_id(game, team_id), object_id);
        }
        player_del_object(player, object_id);
        space_take_object(last_space, object_id);
    }
    return;
}

void game_actions_save(Game *game)
{
    /*The save action is managed by game_loop; it starts as an error and
    if it goes as it should the error code is set to OK. */
    command_set_status(game_get_last_command(game), ERROR);
    return;
}

void game_actions_open(Game *game)
{
    Command *command = NULL;
    Space *act_space = NULL;
    Link *link = NULL;
    Object *object = NULL;
    Player *player = NULL;
    Bool condition1 = FALSE, condition2 = FALSE;
    Id team_id = NO_ID, object_id;
    Bool coop_reachable = FALSE;

    /*Error handling.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Gathers all the information.*/
    if (!(command = game_get_last_command(game)))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    condition1 = strcasecmp(command_get_argument(command, SECOND_ARG), "with") != 0;
    condition2 = strlen(command_get_argument(command, FIRST_ARG)) == 0;
    if (condition1 || condition2)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    act_space = game_get_space(game, player_get_player_location(game_get_actual_player(game)));
    link = game_get_link_by_name(game, command_get_argument(command, FIRST_ARG));
    object = game_get_object(game, game_get_object_by_name(game, command_get_argument(command, THIRD_ARG)));
    player = game_get_actual_player(game);
    object_id = object_get_id(object);

    /*More error management.*/
    if (!act_space || !link || !object || !player)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Searches if the object is reachable via a coop.*/
    if (player_get_team(player) != NO_ID)
    {
        if ((team_id = game_get_teammate_from_player(game, player_get_player_id(player))) != NO_ID)
        {
            coop_reachable = player_has_object(game_get_player(game, team_id), object_id);
        }
    }

    /*Checks if the object opens the link.*/
    if (object_get_open(object) != link_get_id(link))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Checks if the link is reachable and can be opened.*/
    if (link_get_state(link) == ((Bool)OPENED))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    if (link_get_destination(link) != space_get_id(act_space) && link_get_origin(link) != space_get_id(act_space))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Checks if the object is reachable.*/
    if (player_has_object(game_get_actual_player(game), object_get_id(object)) == TRUE)
    {
        /*Executes the command and takes the object out of the inventory.*/
        link_set_state(link, OPENED);
        player_del_object(game_get_actual_player(game), object_get_id(object));
    }
    else if (space_find_object(act_space, object_get_id(object)) != -1)
    {
        /*Executes the command and takes the object out of the space.*/
        link_set_state(link, OPENED);
        space_take_object(act_space, object_get_id(object));
    }
    else if (coop_reachable)
    {
        /*Executes the command and takes the object out of the space of the other player.*/
        link_set_state(link, OPENED);
        player_del_object(game_get_player_by_id(game, team_id), object_get_id(object));
    }
    else
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Clean exit.*/
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_menu(Game *game)
{
    /*The menu action is managed by game_loop; it starts as an error and
    if it goes as it should the error code is set to OK. */
    command_set_status(game_get_last_command(game), ERROR);
    return;
}

void game_actions_wait(Game *game)
{
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_coop(Game *game)
{
    Status result = ERROR;
    Id player_id = NO_ID;
    Id team_id = NO_ID;
    Player *player = NULL, *mate = NULL;

    /*Error handling.*/
    if (!game)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Gets all the information.*/
    player = game_get_actual_player(game);
    player_id = player_get_player_id(player);
    mate = game_get_player_by_id(game, game_get_player_by_name(game, command_get_argument(game_get_last_command(game), 0)));
    team_id = player_get_player_id(mate);

    if (!player || !mate)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }
    /*Checks that the players aren't already teamed.*/
    if (player_get_team(player) != NO_ID || player_get_team(mate) != NO_ID)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Checks that the players are in the same location.*/
    if (player_get_player_location(player) != player_get_player_location(mate))
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Allies the players.*/
    result = game_create_team(game, player_id, team_id);
    if (result == ERROR)
    {
        command_set_status(game_get_last_command(game), ERROR);
        return;
    }

    /*Clean exit.*/
    command_set_status(game_get_last_command(game), OK);
    return;
}

void game_actions_uncoop(Game *game)
{
    Status result = ERROR;
    result = game_destroy_team(game, player_get_player_id(game_get_actual_player(game)));
    command_set_status(game_get_last_command(game), result);
    return;
}

void game_actions_bag(Game *game)
{
    /*This action is managed by graphic_engine, its first to ERROR, and then graphic engine sets it to OK, if evrything went well*/
    command_set_status(game_get_last_command(game), ERROR);
    return;
}

void game_actions_map(Game *game)
{
    /*This action is magned by graphic engine, its first to ERROR, and the graphic engine sets it to OK, if everything went well*/
    command_set_status(game_get_last_command(game), ERROR);
    return;
}

void game_actions_help(Game *game)
{
    /*This action is managed by graphic engine, its first to ERROR, and then graphic engine sets it to OK, if evrything went well*/
    command_set_status(game_get_last_command(game), ERROR);
    return;
}
