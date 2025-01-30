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

/**
 * @brief locates an space by its id.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param id id of the space
 * @return pointer to the space, if it exists.
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief loads all the spaces from the data file.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param filename name of the data file where the map is stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_load_spaces(Game *game, char *filename);

Status game_add_space(Game *game, Space *space);

Id game_get_space_id_at(Game *game, int position);

#endif
