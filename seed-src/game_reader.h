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
 * @brief loads all the spaces from the data file.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param filename name of the data file where the map is stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_reader_load_spaces(Game *game, char *filename);

/**
 * @brief loads all the objects from the data file.
 * @author Saúl López Romero
 *
 * @param game game structure, where all the information related to game is included.
 * @param filename name of the data file where the map is stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_reader_load_objects(Game *game, char *filename);

#endif
