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

#define P3_P4_GATE 49     /*!< Id of the gate between P3 and P4.*/
#define START_ROOM_ID 111 /*!< Id of the start room.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "gamerules.h"
#include "game.h"
#include "link.h"
#include "command.h"
#include "types.h"

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
    if (len == 0)
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
    gv->n_gamerules = 0;

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
    return (gv ? gv->n_gamerules : -1);
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
    if (!gv || gv->n_gamerules <= 0)
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
        if (strcmp(gv->gamerules[i]->name, name) == 0)
            return gv->gamerules[i];
    }

    /*The gamerule wasn't found.*/
    return NULL;
}

/*Now we have all the gamerule functions.*/

Status gamerules_open_gate(Game *game, Gamerule *gr)
{
    /*Error handling.*/
    if (!game || !gr)
        return ERROR;

    /*Checks if the gamerule meets the requirements to be executed.*/
    if (player_has_object(game_get_actual_player(game), gr->value) == TRUE)
    {
        /*Opens the gate.*/
        link_set_state(game_find_link(game, P3_P4_GATE), TRUE);
        gamerules_increment_has_exec(gr);
        return OK;
    }
    else
    {
        /*The gamerule doesn't have to be executed.*/
        return OK;
    }
}

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
    if (command_get_code(cmd) == USE && strcasecmp(command_get_argument(cmd, 0), object_get_name(pass)) == 0 && strcasecmp(command_get_argument(cmd, SECOND_ARG), "over") == 0 && strcasecmp(command_get_argument(cmd, THIRD_ARG), "AnTrain") == 0)
    {
        /*The pass was used correctly.*/
        game_move_all_players(game, START_ROOM_ID);

        /*Attempts to move the pass out of the inventory.*/
        player_del_object(game_get_actual_player(game), pass_id);

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
