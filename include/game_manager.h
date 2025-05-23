/**
 * @brief It loads all the game data into the program.
 *
 * @file game_manager.h
 * @author Saúl López Romero, Raquel Anguita Martínez de Velasco, Fernando Mijangos
 * @version 3
 * @date 26-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "types.h"
#include "game.h"

/**
 * @brief Loads all the spaces from the data file.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game structure, where all the information related to game is included.
 * @param filename Name of the data file where the map is stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_manager_load_spaces(Game *game, char *filename);

/**
 * @brief Loads all the objects from the data file.
 * Should be called once all the spaces have been loaded in.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game structure, where all the information related to game is included.
 * @param filename Name of the data file where the map is stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_manager_load_objects(Game *game, char *filename);

/**
 * @brief Loads all the players from the data file.
 * Should be called once all the spaces have been loaded in.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game structure, where all the information related to game is included.
 * @param filename Name of the data file where the map is stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_manager_load_players(Game *game, char *filename);

/**
 * @brief Loads all the links from the data file.
 * Should be called once all the spaces have been loaded in.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game structure, where all the information related to game is included.
 * @param filename Name of the data file where the map is stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_manager_load_links(Game *game, char *filename);

/**
 * @brief Loads all the characters from the data file.
 * @author Raquel Anguita.
 *
 * @param game Pointer to the game.
 * @param filename NAme of the data file where the characters are stored.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_manager_load_characters(Game *game, char *filename);

/**
 * @brief Loads all the gamerules from the data file.
 * Should be called the last one.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game structure, where all the information related to game is included.
 * @param filename Name of the data file where the gamerules are stored.
 * @return OK for a clean exit, otherwise ERROR.
 */
Status game_manager_load_gamerules(Game *game, char *filename);

/**
 * @brief Loads all the animations from the data file.
 * @author Saúl López Romero
 *
 * @param game Pointer to the game structure, where all the information related to game is included.
 * @param filename Name of the data file where the animations are stored.
 * @return OK for  a clean exit, otherwise ERROR.
 */
Status game_manager_load_animations(Game *game, char *filename);

/**
 * @brief Loads all the savefile names from the data file.
 * @author Fernando Mijangos
 * 
 * @param game Pointer to the game
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_manager_load_savefile_names(Game *game);

/**
 * @brief Saves the game in a file.
 * @author Fernando Mijangos
 * 
 * @param game Pointer to the game.
 * @param filename Name of the file where the game is going to be saved.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_manager_save_game(Game *game, char *filename);

/**
 * @brief Loads the last turn of the game.
 * @author Fernando Mijangos
 * 
 * @param game Pointer to the game.
 * @param filename Name of the file where the last turn is stored.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_manager_load_last_turn(Game *game, char *filename);


#endif
