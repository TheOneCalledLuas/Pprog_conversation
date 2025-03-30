/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Fernando Mijangos, Saul Lopez Romero
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include <stdio.h>

#include "game.h"
#include "game_reader.h"
#include "space.h"
#include "set.h"

typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief It creates a new Graphic engine structure with all its variables initialized
 * @author Saul Lopez Romero
 *
 * @return Pointer to the initialized graphic engine.
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys a graphic engine structure
 * @author Saul Lopez Romero
 *
 * @param ge The graphic engine structure you want to destroy.
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It prints on the terminal an image of the game
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game you are running.
 * @param ge Pointer to the graphic engine structure.
 * @param refresh FALSE if you want to refresh the screen so that the player can see the consequence of his actions.
 *                TRUE if you just want to go to the next "frame".
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Bool refresh);

#endif
