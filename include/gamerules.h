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

typedef struct _Game_values Game_Values; /*!< Struct with all the game values, which determine some outcomes.*/
typedef struct _Gamerule Gamerule; /*!< Gamrule struct.*/

typedef Status (*Gamerule_func)(Game *game, Gamerule*gr); /*!< Pointer to function stored in a Gamerule.*/


#endif