/**
 * @brief It defines the game loop.
 *
 * @file game_loop.c
 * @author Fernando Mijangos Varas
 * @version 1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_reader.h"
#include "graphic_engine.h"

/**
 * @brief Initialises the game.
 *
 * @author Profesores PPROG
 * @param game Pointer to the game.
 * @param gengine The graphic_engine you are going to be using.
 * @param file_name Name of the file where the information about the spaces is.
 *
 * @return 1 if it goes wrong, 0 otherwise.
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Main game loop, where all the actions take place.
 *
 * @author Profesores PPROG
 * @param game Pointer to the game.
 * @param gengine Pointer to the graphic engine.
 */
void game_loop_run(Game *game, Graphic_engine *gengine);

/**
 * @brief Frees the memory and closes the game.
 *
 * @author Profesores PPROG
 * @param game Pointer to the game.
 * @param gengine The graphic engine you are using.
 */
void game_loop_cleanup(Game **game, Graphic_engine *gengine);

int main(int argc, char *argv[])
{
    Game *game = NULL;
    Graphic_engine *gengine = NULL;

    /*Sets the random seed for the use of random numbers later on.*/
    srand(time(NULL));

    /*Checks if a parameter was given.*/
    if (argc < 2)
    {
        fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
        return 1;
    }

    /*Game loop is initated and terminated when its supposed to.*/
    if (!game_loop_init(&game, &gengine, argv[1]))
    {
        game_loop_run(game, gengine);
        game_loop_cleanup(&game, gengine);
    }

    /*Clean exit.*/
    return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
    /*Takes all the information related to the game from a file.*/
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error while initializing game.\n");
        return 1;
    }
    /*Starts the graphic engine.*/
    if ((*gengine = graphic_engine_create()) == NULL)
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return 1;
    }

    /*Clean exit.*/
    return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine)
{
    Command *last_cmd;

    /*Checks the parameters.*/
    if (!gengine)
    {
        return;
    }
    /*Gets the last command.*/
    last_cmd = game_get_last_command(game);

    /*It runs the game while you dont want to exit or the game is terminated.*/
    while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE))
    {
        graphic_engine_paint_game(gengine, game);
        command_get_user_input(last_cmd);
        game_actions_update(game, last_cmd);
    }
}

void game_loop_cleanup(Game **game, Graphic_engine *gengine)
{
    /*Frees all the memory.*/
    game_destroy(game);
    graphic_engine_destroy(gengine);
}
