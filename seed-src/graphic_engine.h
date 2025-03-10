/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Fernando Mijangos
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
 * @author Profesores PPROG
 *
 * @return Pointer to the initialized graphic engine.
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys a graphic engine structure
 * @author Profesores PPROG
 *
 * @param ge The graphic engine structure you want to destroy.
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It prints on the terminal an image of the game
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game you are running.
 * @param gw Pointer to the graphic engine structure.
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
