/**
 * @brief It loads all the game data into the program.
 *
 * @file game_reader.h
 * @author Saúl López Romero
 * @version 0
 * @date 29-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "types.h"
#include "game.h"

Space *game_get_space(Game *game, Id id);

Status game_load_spaces(Game *game, char *filename);

Status game_add_space(Game *game, Space *space);

Id game_get_space_id_at(Game *game, int position);

#endif
