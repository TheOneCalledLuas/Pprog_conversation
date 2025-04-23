/**
 * @brief It implements gamerules into the game.
 *
 * @file gamerules.h
 * @author Saúl López Romero
 * @version 1
 * @date 15-04-2025
 * @copyright GNU Public License
 */

#ifndef GAMERULES_H
#define GAMERULES_H /*!< Gamerules lib.*/

typedef struct _Game_values Game_values; /*!< Struct with all the game values, which determine some outcomes.*/
typedef struct _Gamerule Gamerule;       /*!< Gamerule struct.*/

#include "types.h"
#include "game.h"

typedef Status (*Gamerule_func)(Game *game, Gamerule *gr); /*!< Pointer to function stored in a Gamerule.*/

Game_values *gamerules_values_init();
void gamerules_values_destroy(Game_values *gv);
int gamerules_get_n_gamerules(Game_values *gv);
Status gamerules_values_add(Game_values *gv, Gamerule *gr);
Gamerule *gamerules_values_delete_last(Game_values *gv);
Gamerule *gamerules_gamerule_create(Id id);
void gamerules_gamerule_destroy(Gamerule *gr);
Status gamerules_gamerule_set_func(Gamerule *gr, Gamerule_func g_func);
Gamerule_func gamerules_gamerule_get_func(Gamerule *gr);
Status gamerule_try_exec(Game *game, Gamerule *gr);
Id gamerules_get_id(Gamerule *gr);
char *gamerules_get_name(Gamerule *gr);
Bool gamerules_get_valid(Gamerule *gr);
int gamerules_get_n_exec_times(Gamerule *gr);
Bool gamerules_get_do_once(Gamerule *gr);
int gamerules_get_value(Gamerule *gr);
Status gamerules_set_name(Gamerule *gr, char *name);
Status gamerules_set_valid(Gamerule *gr, Bool value);
int gamerules_increment_has_exec(Gamerule *gr);
Status gamerules_set_do_once(Gamerule *gr, Bool value);
Status gamerules_set_value(Gamerule *gr, int value);
Status gamerules_try_exec_all(Game *game, Game_values *gv);
Status gamerules_set_n_exec_times(Gamerule *gr, int has_exec);

/*Now we have the actual gamerule functions.*/
/**
 * @brief opnes the gatte between P3 and P4.
 * @author Saúl López Romero
 * 
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_open_gate(Game *game, Gamerule *gr);

#endif