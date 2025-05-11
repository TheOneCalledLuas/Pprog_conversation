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
/**
 * @brief It initialises the game values.
 * @author Saúl López Romero
 *
 * @return Pointer to the game values struct.
 */
Game_values *gamerules_values_init();

/**
 * @brief It returns an initialised array with the ids of the gamerules.
 *      IMPORTANT The array must be freed after use.
 * @author Fernando Mijangos
 *
 * @param gv Pointer to the game values struct.
 * @return Pointer to the array with the ids of the gamerules or NULL if an error takes place.
 *      IMPORTANT The array must be freed after use.
 */
Id *gamerules_get_all_gamerules(Game_values *gv);

/**
 * @brief It destroys the game values.
 * @author Saúl López Romero
 *
 * @param gv Pointer to the game values struct.
 */
void gamerules_values_destroy(Game_values *gv);

/**
 * @brief It returns the number of gamerules.
 * @author Saúl López Romero
 *
 * @param gv Pointer to the game values struct.
 * @return Number of gamerules or FUNCTION_ERROR if an error takes place.
 */
int gamerules_get_n_gamerules(Game_values *gv);

/**
 * @brief It adds a gamerule to the game values.
 * @author Saúl López Romero
 *
 * @param gv Pointer to the game values struct.
 * @param gr Pointer to the gamerule struct.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_values_add(Game_values *gv, Gamerule *gr);

/**
 * @brief It deletes the last gamerule added to the game values structure.
 * @author Saúl López Romero
 *
 * @param gv Pointer to the game values struct.
 * @return Pointer to the deleted gamerule or NULL if an error takes place.
 */
Gamerule *gamerules_values_delete_last(Game_values *gv);

/**
 * @brief It initialises a new gamerule struct.
 * @author Saúl López Romero
 *
 * @param id Id of the gamerule.
 * @return Pointer to the gamerule struct, NULL otherwise.
 */
Gamerule *gamerules_gamerule_create(Id id);

/**
 * @brief It destroys a gamerule struct.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 */
void gamerules_gamerule_destroy(Gamerule *gr);

/**
 * @brief It sets the function pointer of a gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @param g_func Pointer to the function to be set.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_gamerule_set_func(Gamerule *gr, Gamerule_func g_func);

/**
 * @brief It gets the function pointer of a gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return Pointer to the function of the gamerule, NULL otherwise.
 */
Gamerule_func gamerules_gamerule_get_func(Gamerule *gr);

/**
 * @brief It tries to execute a gamerule.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game struct.
 * @param gr Pointer to the gamerule struct.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerule_try_exec(Game *game, Gamerule *gr);

/**
 * @brief It returns the gamerule id.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return Id of the gamerule or ID_ERROR.
 */
Id gamerules_get_id(Gamerule *gr);

/**
 * @brief It returns the name of the gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return Name of the gamerule or NULL.
 */
char *gamerules_get_name(Gamerule *gr);

/**
 * @brief It returns the validity of the gamerule; the value which determines if a gamerule can be executed.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return TRUE if the gamerule is valid, FALSE otherwise.
 */
Bool gamerules_get_valid(Gamerule *gr);

/**
 * @brief It returns the number of times a gamerule has been executed.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return Number of times the gamerule has been executed or FUNCTION_ERROR if an error takes place.
 */
int gamerules_get_n_exec_times(Gamerule *gr);

/**
 * @brief It determines if a gamerule is a one use one.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return Value of the gamerule or 0 if an error takes place.
 */
Bool gamerules_get_do_once(Gamerule *gr);

/**
 * @brief It returns the value of the gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return Value of the gamerule or FUNCTION_ERROR if an error takes place.
 */
int gamerules_get_value(Gamerule *gr);

/**
 * @brief It sets the name of the gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @param name Name of the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_set_name(Gamerule *gr, char *name);

/**
 * @brief It sets the validity of the gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @param value Value of the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_set_valid(Gamerule *gr, Bool value);

/**
 * @brief adds an execution to the gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @return OK if everything goes well, ERROR otherwise.
 */
int gamerules_increment_has_exec(Gamerule *gr);

/**
 * @brief It sets if a gamerule is a one use one.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @param value Value to set.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_set_do_once(Gamerule *gr, Bool value);

/**
 * @brief It sets the value of the gamerule.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @param value Value of the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_set_value(Gamerule *gr, int value);

/**
 * @brief It tries to execute all the gamerules on a game values struct.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game struct.
 * @param gv Pointer to the game values struct.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_try_exec_all(Game *game, Game_values *gv);

/**
 * @brief Sets the number of times a gamerule has been executed.
 * @author Saúl López Romero
 *
 * @param gr Pointer to the gamerule struct.
 * @param has_exec Number of times the gamerule has been executed.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_set_n_exec_times(Gamerule *gr, int has_exec);

/**
 * @brief It gets a gamerule by its id.
 * @author Saúl López Romero
 *
 * @param gv Pointer to the game values struct.
 * @param name Gamerule name.
 * @return Pointer to the gamerule struct or NULL if an error takes place.
 */
Gamerule *gamerules_get_gamerule_by_name(Game_values *gv, char *name);

/**
 * @brief It gets a gamerule by its id.
 * @author Saúl López Romero
 *
 * @param gv Pointer to the game values struct.
 * @param id Id of the gamerule.
 * @return Pointer to the gamerule struct or NULL if an error takes place.
 */
Gamerule *gamerules_get_gamerule_by_id(Game_values *gv, Id id);

/*Now we have the actual gamerule functions.*/

/**
 * @brief opens the gate between P3 and P4.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_open_gate(Game *game, Gamerule *gr);

/**
 * @brief Uses the train and ends the tutorial.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_use_train_pass(Game *game, Gamerule *gr);

/**
 * @brief Activates the bad ending.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_bad_ending(Game *game, Gamerule *gr);

/**
 * @brief controls the lever challenge.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_lever_challenge(Game *game, Gamerule *gr);

/**
 * @brief Actions to be done if the spider boss is killed.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_spider_boss_killed(Game *game, Gamerule *gr);

/**
 * @brief random damage to the player.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_random_damage(Game *game, Gamerule *gr);

/**
 * @brief random heal to the player.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_random_heal(Game *game, Gamerule *gr);

/**
 * @brief Blue potion mechanics.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_blue_potion(Game *game, Gamerule *gr);

/**
 * @brief Handles dinamite interactivity.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 */
Status gamerules_dinamite_interactivity(Game *game, Gamerule *gr);

/**
 * @brief Handles the misterious spider kill.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 */
Status gamerules_misterious_spider_kill(Game *game, Gamerule *gr);

/**
 * @brief Handles the guard spider kill.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_guard_spider_kill(Game *game, Gamerule *gr);

/**
 * @brief Handles exploration progress.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_exploration_progress(Game *game, Gamerule *gr);

/**
 * @brief Boosts merchant when precise.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_merchant_boost(Game *game, Gamerule *gr);

/**
 * @brief Handles merchant bad ending.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_merchant_bad_ending(Game *game, Gamerule *gr);

/**
 * @brief Handles merchant good ending.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_merchant_good_ending(Game *game, Gamerule *gr);

/**
 * @brief Handles bad ending attached to any of the players dying.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_neutral_ending(Game *game, Gamerule *gr);

/**
 * @brief handles red potion mechanics.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_red_potion(Game *game, Gamerule *gr);

/**
 * @brief handles the initial animation.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game.
 * @param gr Pointer to the gamerule.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status gamerules_initial_animation(Game *game, Gamerule *gr);

#endif