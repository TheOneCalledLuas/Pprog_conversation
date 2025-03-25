/**
 * @brief It defines the game update interface.
 *
 * @file game_actions.h
 * @author Fernando Mijangos.
 * @version 3
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
 * @brief It changes the player location space, or other things depending on the command entered.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game you are running.
 * @param cmd Pointer to the command you want to enter.
 * @return OK if everything went correct or ERROR it it didn't.
 */
Status game_actions_update(Game *game, Command *cmd);

#endif
