/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Fernando Mijangos, Saúl Lopez Romero
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include <stdio.h>

#include "game.h"
#include "game_manager.h"
#include "space.h"
#include "set.h"

/**
 * @brief Cods for possible situations that can appear in menu
 */
typedef enum
{
    NO_SAVES,         /*!<No existing saves situation*/
    EXISTING_SAVES,   /*!<Existing daves situations*/
    LIMIT_SAVEFILES,  /*!<Max number of savefiles reached*/
    LOAD_GAME,        /*!<Load game situations*/
    FAIL_LOAD_GAME,   /*!<Fail to load a game situation*/
    NEW_GAME,         /*!<New game situation*/
    FAIL_NEW_GAME,    /*!<Fail to create a new game*/
    DELETE_FILE,      /*!<Delete file situation*/
    FINAL,            /*!<Used when exiting the game to put credits*/
    N_MENU_SITUATIONS /*!<Number of possible situations*/
} Menu_states;

typedef struct _Graphic_engine Graphic_engine; /*!< Graphic engine type.*/

/**
 * @brief It creates a new Graphic engine structure with all its variables initialized
 * @author Saúl Lopez Romero
 *
 * @return Pointer to the initialized graphic engine.
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys a graphic engine structure
 * @author Saúl Lopez Romero
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

/**
 * @brief It creates a new Graphic engine structure with all its varialbes initialized in menu mode
 * @author Fernando Mijangos
 *
 * @return Pointer to the initialized graphic engine.
 */
Graphic_engine *graphic_engine_menu_create();

/**
 * @brief It destroyes a graphic engine structure in menu mode
 * @author Fernando Mijangos
 *
 * @param ge The graphic engine structure you want to destroy.
 */
void graphic_engine_menu_destroy(Graphic_engine *ge);

/**
 * @brief It paints the menu in the terminal
 * @author Fernando Mijangos
 *
 * @param ge Pointer to the graphic engine you are using.
 * @param game Pointer to the game you are running.
 * @param state The state of the game you are in.
 * @note             0->Prints screen where there arent saves
 * @note             1->Prints screen where there are saves
 * @note             2->Prints screen where you can load a game
 * @note             3->Prints screen where you tried to load a game that doesnt exist
 * @note             4->Prints screen where you create a new game
 * @note             5->Prints a screen where you try to create a game that already exists or cant be created
 * @note             6->Prints screen where you chose which file to delete
 * @note             7->Prints screen where you get help
 */
void graphic_engine_menu_paint(Graphic_engine *ge, Game *game, int state);

#endif
