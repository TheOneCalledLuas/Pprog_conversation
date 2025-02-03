/**
 * @brief It defines the game update interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "game_reader.h"
#include "types.h"

/**
 * @brief It changes the player location space, or other things depending in the commandcode entered
 * @author Profesores PPROG
 *
 * @param game the pointer to the game you are running
 * @param cmd the pointer to the command you want to enter
 * @return OK if everything went correct or ERROR it it didn't
 */
Status game_actions_update(Game *game, Command *cmd);

#endif
