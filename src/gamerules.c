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

#include <stdio.h>
#include <stdlib.h>

#include "gamerules.h"
#include "game.h"
#include "types.h"

struct _Gamerule
{
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

