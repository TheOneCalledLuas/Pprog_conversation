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

#include <stdio.h>
#include <stdlib.h>

#include "gamerules.h"
#include "game.h"
#include "types.h"

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

struct _Game_values
{
    Gamerule **gamerules; /*!< Gamerules.*/
    int n_gamerules;      /*!< Number of gamerules.*/
};

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
                return (gr->do_gamerule)(game, gr);
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
