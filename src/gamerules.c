/**
 * @brief It implements gamerules into the game.
 *
 * @file gamerules.c
 * @author Saúl López Romero
 * @version 1
 * @date 15-04-2025
 * @copyright GNU Public License
 */

#define MAX_GAMERULES 100 /*!< Max gamerule number. Can be modified if required.*/
#define MAX_NAME 64       /*!< Max name for a gamerule.*/

#define NO_HEALTH 0                   /*!< No health value. */
#define P3_P4_GATE 49                 /*!< Id of the gate between P3 and P4.*/
#define START_ROOM_ID 111             /*!< Id of the start room.*/
#define SPIDER_BOSS_ID 60             /*!< Id of Arachne.*/
#define SPIDER_1 63                   /*!< Id of the first spider. */
#define SPIDER_2 64                   /*!< Id of the second spider. */
#define SPIDER_3 67                   /*!< Id of the third spider. */
#define SPIDER_4 69                   /*!< Id of the fourth spider. */
#define PRISON_ANT_ID 70              /*!< Id of the prison ant. */
#define WORRIED_ANT 68                /*!< Id of the worried ant. */
#define ANIMATION_BAD_ENDING_1 13     /*!< Animation for the bad ending of the spiders.*/
#define LEVER_1_ID 217                /*!< Id of the first lever.*/
#define LEVER_2_ID 218                /*!< Id of the second lever.*/
#define LINK_LEVER_1 411              /*!< Id of the link between the first lever and the second one.*/
#define LINK_LEVER_2 451              /*!< Id of the link for the second lever.*/
#define MAX_TURNS_LEVER 10            /*!< Max turns for the lever to be activated.*/
#define DINAMITE_ID 216               /*!< Id of the dynamite.*/
#define VICTIM_ID 66                  /*!< Id of the victim of the lever task.*/
#define ANIMATION_ARACHNE_DEATH 14    /*!< Animation for the death of Arachne.*/
#define POST_BOSS_ROOM_ID 113         /*!< Id of the room after the boss.*/
#define HOLE_LAIR 301                 /*!< Id of the hole in the lair. */
#define MERCHANT_ID 61                /*!< Id of the merchant.*/
#define ZERO_LINK 310                 /*!< Id of link to the zero room. */
#define DAMAGE_PROB 1                 /*!< Probability of random damage. */
#define HEAL_PROB 1                   /*!< Probability of random healing. */
#define RANDOM_START 1                /*!< Start of the random number. */
#define RANDOM_END 20                 /*!< End of the random number. */
#define HEAL_MSG 15                   /*!< Message for the healing. */
#define DAMAGE_MSG 16                 /*!< Message for the damage. */
#define BLUE_POTION 213               /*!< Id of the blue potion. */
#define BLUE_POTION_LINK 491          /*!< Id of the link for the blue potion. */
#define DINAMITE_ROOM 131             /*!< Id of the room where the dynamite can be used. */
#define DINAMITE_LINK 310             /*!< Id of the link for the dynamite. */
#define SPIDER_1_LINK 361             /*!< Id of the link for the first spider. */
#define SPIDER_2_LINK 371             /*!< Id of the link for the second spider. */
#define OPEN_ANIM 3                   /*!< Animation for the opening of any link. */
#define GUN_ID 123                    /*!< Id of the gun. */
#define BULLET_ID 221                 /*!< Id of the bullet. */
#define MERCHANT_BOOST 5              /*!< Boost for the merchant. */
#define ANIMATION_MERCHANT_ENDING_1 5 /*!< Animation for the merchant bad ending. */
#define ANIMATION_MERCHANT_ENDING_2 6 /*!< Animation for the merchant good ending. */
#define PLAYER_DEAD 2                 /*!< Animation for the player dead. */
#define FIRST_ANIMATION 4             /*!< Animation for the first action. */

/*The following IDS are the ids of the rooms to reach completion.*/
#define ROOM_1 711          /*!< Id of the first room. */
#define ROOM_2 712          /*!< Id of the second room. */
#define ROOM_3 713          /*!< Id of the third room. */
#define ROOM_4 714          /*!< Id of the fourth room. */
#define ROOM_5 112          /*!< Id of the fifth room. */
#define ROOM_6 113          /*!< Id of the sixth room. */
#define ROOM_7 121          /*!< Id of the seventh room. */
#define ROOM_8 721          /*!< Id of the eighth room. */
#define ROOM_9 722          /*!< Id of the ninth room. */
#define ROOM_10 723         /*!< Id of the tenth room. */
#define ROOM_11 122         /*!< Id of the eleventh room. */
#define ROOM_12 731         /*!< Id of the twelfth room. */
#define ROOM_13 732         /*!< Id of the thirteenth room. */
#define ROOM_14 733         /*!< Id of the fourteenth room. */
#define ROOM_15 123         /*!< Id of the fifteenth room. */
#define ROOM_16 131         /*!< Id of the sixteenth room. */
#define ROOM_17 132         /*!< Id of the seventeenth room. */
#define COMPLETION_ROOMS 17 /*!< Number of rooms to reach completion. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "gamerules.h"
#include "game.h"
#include "link.h"
#include "command.h"
#include "types.h"

Id rooms[COMPLETION_ROOMS] = {ROOM_1, ROOM_2, ROOM_3, ROOM_4, ROOM_5, ROOM_6, ROOM_7, ROOM_8, ROOM_9,
                              ROOM_10, ROOM_11, ROOM_12, ROOM_13, ROOM_14, ROOM_15, ROOM_16, ROOM_17}; /*!<Array with all the essencial rooms.*/

/**
 * @brief TAD gamerule.
 */
struct _Gamerule
{
    Id id;                     /*!< Gamerule id. Must be unique.*/
    char *name;                /*!< Gamerule name.*/
    Bool is_valid;             /*!< Value used to turn the gamerule on or off. */
    int has_exec;              /*!< Number of times a gamerule has been executed.*/
    Bool do_once;              /*!< Decides if a gamerule has to be executed only once.*/
    int value;                 /*!< Numeric value for the gamerule to use (or not).*/
    Gamerule_func do_gamerule; /*!< Function to be exectuted for each gamerule.*/
};

/**
 * @brief Structure to store all the gamerules.
 */
struct _Game_values
{
    Gamerule **gamerules; /*!< Gamerules.*/
    int n_gamerules;      /*!< Number of gamerules.*/
};

Id *gamerules_get_all_gamerules(Game_values *gv)
{
    int i = 0, len = 0;
    Id *ids = NULL;
    /*Error handling.*/
    if (!gv)
        return NULL;
    len = gv->n_gamerules;
    if (len == NO_THINGS)
        return NULL;
    /*Allocates memory.*/
    if (!(ids = (Id *)calloc(len, sizeof(Id))))
        return NULL;
    /*Gets the ids.*/
    for (i = 0; i < len; i++)
    {
        ids[i] = gv->gamerules[i]->id;
    }
    return ids;
}

Game_values *gamerules_values_init()
{
    Game_values *gv = NULL;

    /*Allocates memory.*/
    if (!(gv = (Game_values *)calloc(1, sizeof(Game_values))))
        return NULL;
    if (!(gv->gamerules = (Gamerule **)calloc(MAX_GAMERULES, sizeof(Gamerule *))))
    {
        free(gv);
        return NULL;
    }

    /*Sets the values.*/
    gv->n_gamerules = NO_THINGS;

    /*Clean exit.*/
    return gv;
}

void gamerules_values_destroy(Game_values *gv)
{
    /*Error handling.*/
    if (gv)
    {
        if (gv->gamerules)
            free(gv->gamerules);
        free(gv);
    }
}

int gamerules_get_n_gamerules(Game_values *gv)
{
    return (gv ? gv->n_gamerules : FUNCTION_ERROR);
}

Status gamerules_values_add(Game_values *gv, Gamerule *gr)
{
    /*Error handling.*/
    if (!gv || !gr || gv->n_gamerules >= MAX_GAMERULES)
    {
        return ERROR;
    }
    /*Adds the gamerule.*/
    gv->gamerules[gv->n_gamerules++] = gr;

    /*Clean exit.*/
    return OK;
}

Status gamerules_try_exec_all(Game *game, Game_values *gv)
{
    int i = 0;
    /*Error handling.*/
    if (!game || !gv)
        return ERROR;

    /*Executes all the gamerules. */
    for (i = 0; i < gv->n_gamerules; i++)
    {
        gamerule_try_exec(game, gv->gamerules[i]);
    }

    /*Clean exit.*/
    return OK;
}

Gamerule *gamerules_values_delete_last(Game_values *gv)
{
    /*Error handling.*/
    if (!gv || gv->n_gamerules <= NO_THINGS)
        return NULL;

    /*Takes the item out.*/
    return gv->gamerules[--(gv->n_gamerules)];
}

Gamerule *gamerules_gamerule_create(Id id)
{
    Gamerule *gr = NULL;
    /*Error handling.*/
    if (id <= NO_ID)
        return NULL;

    /*Memory allocation.*/
    if (!(gr = (Gamerule *)calloc(1, sizeof(Gamerule))))
        return NULL;

    if (!(gr->name = (char *)calloc(MAX_NAME, sizeof(char))))
    {
        free(gr);
        return NULL;
    }

    /*Sets the values to default.*/
    gr->do_once = FALSE;
    gr->has_exec = FALSE;
    gr->id = id;
    gr->is_valid = FALSE;
    gr->name[0] = '\0';
    gr->value = 0;

    /*Clean exit.*/
    return gr;
}

void gamerules_gamerule_destroy(Gamerule *gr)
{
    /*Error handling.*/
    if (gr)
    {
        if (gr->name)
        {
            free(gr->name);
        }
        free(gr);
    }
    return;
}

Status gamerules_gamerule_set_func(Gamerule *gr, Gamerule_func g_func)
{
    /*Error handling.*/
    if (!gr || !g_func)
        return ERROR;

    /*Sets the value.*/
    gr->do_gamerule = g_func;
    return OK;
}

Gamerule_func gamerules_gamerule_get_func(Gamerule *gr)
{
    /*Error handling.*/
    if (!gr)
        return NULL;

    /*Returns the value.*/
    return gr->do_gamerule;
}

Status gamerule_try_exec(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if the gamerule meets the requirements to be executed.*/
    if (gr->is_valid == TRUE)
    {
        switch (gr->do_once)
        {
        case FALSE:
            return (gr->do_gamerule)(game, gr);
            break;

        case TRUE:
            if (gr->has_exec == 0) /*If its the first time the gamerule is activated.*/
            {
                if (gr->do_gamerule != NULL)
                {
                    return (gr->do_gamerule)(game, gr);
                }
            }
            else
            {
                return OK; /*The gamerule doesn't need to be executed.*/
            }
            break;

        default:
            return ERROR;
            break;
        }
    }
    return OK;
}

Id gamerules_get_id(Gamerule *gr)
{
    return (gr ? gr->id : ID_ERROR);
}

char *gamerules_get_name(Gamerule *gr)
{
    return (gr ? gr->name : NULL);
}

Bool gamerules_get_valid(Gamerule *gr)
{
    return (gr ? gr->is_valid : FALSE);
}

int gamerules_get_n_exec_times(Gamerule *gr)
{
    return (gr ? gr->has_exec : -1);
}

Bool gamerules_get_do_once(Gamerule *gr)
{
    return (gr ? gr->do_once : FALSE);
}

int gamerules_get_value(Gamerule *gr)
{
    return (gr ? gr->value : 0);
}

Status gamerules_set_name(Gamerule *gr, char *name)
{
    /*Error handling.*/
    if (!gr || !name || strlen(name) >= MAX_NAME)
        return ERROR;

    /*Sets the value.*/
    strcpy(gr->name, name);

    /*Clean exit.*/
    return OK;
}

Status gamerules_set_valid(Gamerule *gr, Bool value)
{
    /*Error handling.*/
    if (!gr)
        return ERROR;

    /*Sets the value.*/
    gr->is_valid = value;

    /*Clean exit.*/
    return OK;
}

int gamerules_increment_has_exec(Gamerule *gr)
{
    /*Error handling.*/
    if (!gr)
        return ERROR;

    /*Sets the value.*/
    gr->has_exec++;

    /*Clean exit.*/
    return OK;
}

Status gamerules_set_do_once(Gamerule *gr, Bool value)
{
    /*Error handling.*/
    if (!gr)
        return ERROR;

    /*Sets the value.*/
    gr->do_once = value;

    /*Clean exit.*/
    return OK;
}

Status gamerules_set_value(Gamerule *gr, int value)
{
    /*Error handling.*/
    if (!gr)
        return ERROR;

    /*Sets the value.*/
    gr->value = value;

    /*Clean exit.*/
    return OK;
}

Status gamerules_set_n_exec_times(Gamerule *gr, int has_exec)
{
    /*Error handling.*/
    if (!gr)
        return ERROR;

    /*Sets the value.*/
    gr->has_exec = has_exec;

    /*Clean exit.*/
    return OK;
}

Gamerule *gamerules_get_gamerule_by_id(Game_values *gv, Id id)
{
    int i = 0;

    /*Error handling.*/
    if (!gv || id <= NO_ID)
        return NULL;

    /*Searches the gamerule by its id.*/
    for (i = 0; i < gv->n_gamerules; i++)
    {
        if (gv->gamerules[i]->id == id)
            return gv->gamerules[i];
    }

    /*The gamerule wasn't found.*/
    return NULL;
}

Gamerule *gamerules_get_gamerule_by_name(Game_values *gv, char *name)
{
    int i = 0;

    /*Error handling.*/
    if (!gv || !name)
        return NULL;

    /*Searches the gamerule by its name.*/
    for (i = 0; i < gv->n_gamerules; i++)
    {
        if (strcmp(gv->gamerules[i]->name, name) == EQUAL_WORDS)
            return gv->gamerules[i];
    }

    /*The gamerule wasn't found.*/
    return NULL;
}

/*Now we have all the gamerule functions.*/

Status gamerules_use_train_pass(Game *game, Gamerule *gr)
{
    Object *pass = NULL;
    Command *cmd = NULL;
    Id pass_id = NO_ID; /*Id of the pass.*/
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Gets the pass id.*/
    pass_id = gamerules_get_value(gr);

    /*Gets the Pass.*/
    if (!(pass = game_get_object(game, pass_id)))
    {
        return ERROR;
    }

    /*Checks if the gamerule meets the requirements to be executed.*/
    if (object_get_is_used(pass))
    {
        /*They attempted to use the pass, checks if it was used correctly.*/
        if (!(cmd = game_get_last_command(game)))
            return ERROR;
    }
    if (command_get_code(cmd) == USE && strcasecmp(command_get_argument(cmd, 0), object_get_name(pass)) == EQUAL_WORDS && strcasecmp(command_get_argument(cmd, SECOND_ARG), "over") == EQUAL_WORDS && strcasecmp(command_get_argument(cmd, THIRD_ARG), "AnTrain") == EQUAL_WORDS)
    {
        /*The pass was used correctly.*/
        game_move_all_players(game, START_ROOM_ID);

        /*Takes the followers out.*/
        game_unfollow_all(game);

        /*Attempts to move the pass out of the inventory.*/
        player_del_object(game_get_actual_player(game), pass_id);

        /*Runs the animation*/
        animation_run(game_get_animation_manager(game), 17);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
        return OK;
    }
    else
    {
        /*The gamerule doesn't have to be executed, as the pass wasn't used correctly.*/
        object_set_is_used(pass, FALSE);
        command_set_status(cmd, ERROR);
        return OK;
    }
}

Status gamerules_bad_ending(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks in which stage of the gamerule we are.*/
    switch (gamerules_get_value(gr))
    {
    case 0:
        /*We are waiting for the player to talk to the ant on room 711.*/
        if (command_get_code(game_get_last_command(game)) == CHAT && strcasecmp(command_get_argument(game_get_last_command(game), 0), "Vengeful_Ant") == 0)
        {
            /*The player talked to the ant, we go to the next stage.*/
            gamerules_set_value(gr, 1);
        }
        return OK;
        break;
    case 1:
        /*We are waiting for the player to kill the spider boss and all the spiders.*/

        if (character_get_health(game_get_character(game, SPIDER_BOSS_ID)) > NO_HEALTH ||
            character_get_health(game_get_character(game, SPIDER_1)) > NO_HEALTH ||
            character_get_health(game_get_character(game, SPIDER_2)) > NO_HEALTH ||
            character_get_health(game_get_character(game, SPIDER_3)) > NO_HEALTH ||
            character_get_health(game_get_character(game, SPIDER_4)) > NO_HEALTH)
        {
            /*Some enemies are missing to be killed.*/
            return OK;
        }

        /*The player killed all the spiders, we activate the ending..*/
        animation_run(game_get_animation_manager(game), ANIMATION_BAD_ENDING_1);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
        return OK;
        break;
    default:
        return ERROR;
    }
    return ERROR;
}

Status gamerules_lever_challenge(Game *game, Gamerule *gr)
{
    Bool lever_1 = FALSE, lever_2 = FALSE;
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks the gamerule state.*/
    switch (gamerules_get_value(gr))
    {
    case 0:
        /*We are waiting for the player to talk with Worried ant.*/
        if (command_get_code(game_get_last_command(game)) == CHAT && strcasecmp(command_get_argument(game_get_last_command(game), 0), "Worried_Ant") == EQUAL_WORDS)
        {
            /*The player talked to the ant, we go to the next stage.*/
            gamerules_set_value(gr, 1);
        }
        return OK;
        break;
    case -1:
        /*The lost the challenge, but the links can be opened.*/
        /*Opens links if required.*/
        lever_1 = object_get_is_used(game_get_object(game, LEVER_1_ID));
        lever_2 = object_get_is_used(game_get_object(game, LEVER_2_ID));
        if (lever_1)
        {
            /*The first lever was used, we open the link.*/
            link_set_state(game_find_link(game, LINK_LEVER_1), TRUE);
            object_set_is_used(game_get_object(game, LEVER_1_ID), FALSE);
        }
        if (lever_2)
        {
            /*The second lever was used, we open the link.*/
            link_set_state(game_find_link(game, LINK_LEVER_2), TRUE);
            object_set_is_used(game_get_object(game, LEVER_2_ID), FALSE);
        }
        if (lever_1 && lever_2)
        {
            /*The gamerule stops.*/
            gamerules_increment_has_exec(gr);
            return OK;
        }
        return OK;
        break;
    default:
        /*Forwads the timer.*/
        gamerules_set_value(gr, gamerules_get_value(gr) + 1);
        /*Opens links if required.*/
        lever_1 = object_get_is_used(game_get_object(game, LEVER_1_ID));
        lever_2 = object_get_is_used(game_get_object(game, LEVER_2_ID));
        if (lever_1)
        {
            /*The first lever was used, we open the link.*/
            link_set_state(game_find_link(game, LINK_LEVER_1), TRUE);
        }
        if (lever_2)
        {
            /*The second lever was used, we open the link.*/
            link_set_state(game_find_link(game, LINK_LEVER_2), TRUE);
        }

        /*We are waiting for the player to pull the levers.*/
        if (lever_1 && lever_2)
        {
            /*As both levers were used, the timer stops ant one item is used.*/
            game_vanish_object(game, DINAMITE_ID);

            /*Stops the timer.*/
            gamerules_increment_has_exec(gr);

            /*Sets other value so  that the gamerule stops cheching this.*/
            gamerules_set_value(gr, -1);

            return OK;
        }

        /*If the timer has run out.*/
        if (gamerules_get_value(gr) >= MAX_TURNS_LEVER * game_get_n_players(game))
        {
            /*The player didn't pull the levers in time.*/
            character_set_health(game_get_character(game, VICTIM_ID), -10);
            gamerules_set_value(gr, -1);
            return OK;
        }

        return OK;
        break;
    }
}

Status gamerules_spider_boss_killed(Game *game, Gamerule *gr)
{
    Character *merchant = NULL;
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;
    /*Checks if the Spider boss was killed.*/
    if (character_get_health(game_get_character(game, SPIDER_BOSS_ID)) <= NO_HEALTH)
    {
        /*The spider boss was killed.*/
        game_move_all_players(game, POST_BOSS_ROOM_ID);
        animation_run(game_get_animation_manager(game), ANIMATION_ARACHNE_DEATH);

        /*Closes the gate.*/
        link_set_state(game_find_link(game, HOLE_LAIR), FALSE);

        /*Opens the zero room.*/
        link_set_state(game_find_link(game, ZERO_LINK), TRUE);

        /*Changes merchant.*/
        merchant = game_get_character(game, MERCHANT_ID);
        character_set_friendly(merchant, FALSE);
        character_set_follow(merchant, NO_ID);
        space_take_character(game_get_space(game, game_get_character_location(game, MERCHANT_ID)), MERCHANT_ID);
        space_add_character(game_get_space(game, 0), MERCHANT_ID);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
        return OK;
    }
    return OK;
}

Status gamerules_random_damage(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*If the game is determined, this doesn't apply.*/
    if (game_get_determined(game))
    {
        return OK;
    }

    /*Checks if the player moved.*/
    if (command_get_code(game_get_last_command(game)) != MOVE)
    {
        return OK;
    }

    /*Checks if the damage is dealt.*/
    if (game_random_int(1, 15) <= HEAL_PROB)
    {
        player_set_health(game_get_actual_player(game), player_get_health(game_get_actual_player(game)) - 1);
        animation_run(game_get_animation_manager(game), DAMAGE_MSG);

        /*Refreshes the gamerule.*/
        gamerules_increment_has_exec(gr);
        return OK;
    }
    /*Clean exit.*/
    return OK;
}

Status gamerules_random_heal(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*If the game is determined, this doesn't apply.*/
    if (game_get_determined(game))
    {
        return OK;
    }

    /*Checks if the player moved.*/
    if (command_get_code(game_get_last_command(game)) != MOVE)
    {
        return OK;
    }

    /*Checks if the damage is dealt.*/
    if (game_random_int(1, 15) <= DAMAGE_PROB)
    {
        player_set_health(game_get_actual_player(game), player_get_health(game_get_actual_player(game)) + 1);
        animation_run(game_get_animation_manager(game), HEAL_MSG);

        /*Refreshes the gamerule.*/
        gamerules_increment_has_exec(gr);
        return OK;
    }
    /*Clean exit.*/
    return OK;
}

Status gamerules_blue_potion(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;
    if (object_get_is_used(game_get_object(game, BLUE_POTION)))
    {
        /*The potion was used.*/
        link_set_state(game_find_link(game, BLUE_POTION_LINK), TRUE);
        /*The potion is taken out of the game.*/
        game_vanish_object(game, BLUE_POTION);
        game_vanish_object(game, DINAMITE_ID);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
    }

    /*Clean exit.*/
    return OK;
}

Status gamerules_dinamite_interactivity(Game *game, Gamerule *gr)
{
    Object *dynamite = NULL;
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Gets the dinamite.*/
    if (!(dynamite = game_get_object(game, DINAMITE_ID)))
    {
        return ERROR;
    }

    /*Checks if the dinamite was used.*/
    if (object_get_is_used(dynamite))
    {
        /*The dinamite was used.*/
        object_set_is_used(dynamite, FALSE);
        /*Checks if the player was in the correct room.*/
        if (player_get_player_location(game_get_actual_player(game)) == DINAMITE_ROOM)
        {
            /*We take the dinamite out.*/
            game_vanish_object(game, DINAMITE_ID);
            if (link_get_state(game_find_link(game, DINAMITE_LINK)) == (Bool)CLOSED)
            {
                link_set_state(game_find_link(game, DINAMITE_LINK), TRUE);
                /*We kill all the corresponding charracters.*/
                character_set_health(game_get_character(game, PRISON_ANT_ID), NO_HEALTH);
                character_set_health(game_get_character(game, WORRIED_ANT), NO_HEALTH);
            }
            /*Actualises the gamerule.*/
            gamerules_increment_has_exec(gr);
        }
    }
    /*Clean exit.*/
    return OK;
}

Status gamerules_misterious_spider_kill(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if the spider was killed.*/
    if (character_get_health(game_get_character(game, SPIDER_1)) <= NO_HEALTH)
    {
        /*The spider was killed.*/
        link_set_state(game_find_link(game, SPIDER_1_LINK), TRUE);
        animation_run(game_get_animation_manager(game), OPEN_ANIM);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
    }
    /*Clean exit.*/
    return OK;
}

Status gamerules_guard_spider_kill(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if the spider was killed.*/
    if (character_get_health(game_get_character(game, SPIDER_2)) <= NO_HEALTH)
    {
        /*The spider was killed.*/
        link_set_state(game_find_link(game, SPIDER_2_LINK), TRUE);
        animation_run(game_get_animation_manager(game), OPEN_ANIM);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
    }
    /*Clean exit.*/
    return OK;
}

Status gamerules_exploration_progress(Game *game, Gamerule *gr)
{
    int i = 0;
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if all the rooms are explored.*/
    for (i = 0; i < COMPLETION_ROOMS; i++)
    {
        if (space_is_discovered(game_get_space(game, rooms[i])) == (Bool)FALSE)
        {
            /*The room wasn't explored.*/
            return OK;
        }
    }
    /*All the rooms were explored.*/
    link_set_state(game_find_link(game, HOLE_LAIR), TRUE);
    animation_run(game_get_animation_manager(game), OPEN_ANIM);

    /*Actualises the gamerule.*/
    gamerules_increment_has_exec(gr);

    /*Clean exit.*/
    return OK;
}

Status gamerules_merchant_boost(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if any player has the bullets AND the gun.*/
    if (player_has_object(game_get_actual_player(game), GUN_ID) && player_has_object(game_get_actual_player(game), BULLET_ID))
    {
        /*The player has the bullets and the gun, we give him the boost.*/
        character_set_health(game_get_character(game, MERCHANT_ID), character_get_health(game_get_character(game, MERCHANT_ID)) + MERCHANT_BOOST);
        animation_run(game_get_animation_manager(game), OPEN_ANIM);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
    }

    /*Clean exit.*/
    return OK;
}

Status gamerules_merchant_bad_ending(Game *game, Gamerule *gr)
{
    Command *cmd = NULL;
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Gets the last command.*/
    if (!(cmd = game_get_last_command(game)))
        return ERROR;

    /*Checks if the last command was using the gun against merchant.*/
    if (command_get_code(cmd) == USE && strcasecmp(command_get_argument(cmd, FIRST_ARG), "artifact") == EQUAL_WORDS && strcasecmp(command_get_argument(cmd, SECOND_ARG), "over") == EQUAL_WORDS && strcasecmp(command_get_argument(cmd, THIRD_ARG), "Merchant") == EQUAL_WORDS)
    {
        /*The player used the gun against the merchant.*/
        character_set_health(game_get_character(game, MERCHANT_ID), NO_HEALTH);
        animation_run(game_get_animation_manager(game), ANIMATION_MERCHANT_ENDING_1);
        game_set_finished(game, TRUE);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
    }

    /*Clean exit.*/
    return OK;
}

Status gamerules_merchant_good_ending(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if the merchant is dead.*/
    if (character_get_health(game_get_character(game, MERCHANT_ID)) <= NO_HEALTH)
    {
        /*The merchant is dead, we set the game as finished.*/
        game_set_finished(game, TRUE);
        animation_run(game_get_animation_manager(game), ANIMATION_MERCHANT_ENDING_2);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
    }

    /*Clean exit.*/
    return OK;
}

Status gamerules_neutral_ending(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if any player is dead.*/
    if (player_get_health(game_get_actual_player(game)) <= NO_HEALTH)
    {
        /*The player is dead, we set the game as finished.*/
        game_set_finished(game, TRUE);
        animation_run(game_get_animation_manager(game), PLAYER_DEAD);

        /*Actualises the gamerule.*/
        gamerules_increment_has_exec(gr);
    }

    /*Clean exit.*/
    return OK;
}

Status gamerules_initial_animation(Game *game, Gamerule *gr)
{
    /* Error handling.*/
    if (!game || !gr)
        return ERROR;

    if (gamerules_get_n_exec_times(gr) > NO_THINGS)
    {
        /*The animation was already executed, we don't need to do it again.*/
        return OK;
    }

    /*Executes the initial animation.*/
    animation_run(game_get_animation_manager(game), FIRST_ANIMATION);

    /*Actualises the gamerule.*/
    gamerules_increment_has_exec(gr);
    return OK;
}