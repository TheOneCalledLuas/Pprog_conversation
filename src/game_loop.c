/**
 * @brief It defines the game loop.
 *
 * @file game_loop.c
 * @author Fernando Mijangos, Saul Lopez Romero
 * @version 1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_reader.h"
#include "graphic_engine.h"
#include "gamerules.h"

/**
 * Maximun argument length.
 */
#define MAX_ARG 64
#define READING_SECONDS 4 /*!< Seconds to read the screen. */

/**
 * @brief Initialises the game.
 *
 * @author Fernando Mijangos
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
 * @author Saul Lopez Romero
 * @param game Pointer to the game.
 * @param gengine Pointer to the graphic engine.
 * @param f Pointer to the file for the log.
 */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *f);

/**
 * @brief Frees the memory and closes the game.
 *
 * @author Fernando Mijangos
 * @param game Pointer to the game.
 * @param gengine The graphic engine you are using.
 */
void game_loop_cleanup(Game **game, Graphic_engine *gengine);

/**
 * @brief Main game function.
 * @author Saúl López Romero
 *
 * @param argc Number of arguments passed.
 * @param argv Arguments passed.
 */
int main(int argc, char *argv[])
{
    Game *game = NULL;
    Graphic_engine *gengine = NULL;
    FILE *f = NULL;
    int i = 0;

    /*Sets the random seed for the use of random numbers later on.*/
    srand(time(NULL));

    /*Checks if a parameter was given.*/
    if (argc < 2)
    {
        fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
        return 1;
    }
    /*Searches if a log file has to be creeated.*/
    for (i = 0; i < argc; i++)
    {
        if (!strcmp("-l", argv[i]) && i + 1 < argc)
        {
            /*Sets up the log creation.*/
            f = fopen(argv[i + 1], "w");
        }
    }

    /*Game loop is initated and terminated when its supposed to.*/
    if (!game_loop_init(&game, &gengine, argv[1]))
    {
        game_loop_run(game, gengine, f);
        game_loop_cleanup(&game, gengine);
        /*Closes the log if it proceeds.*/
        if (f)
            fclose(f);
    }

    /*Clean exit.*/
    return EXIT_SUCCESS;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
    /*Takes all the information related to the game from a file.*/
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error while initializing game.\n");
        return EXIT_FAILURE;
    }
    /*Starts the graphic engine.*/
    if ((*gengine = graphic_engine_create()) == NULL)
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    /*Clean exit.*/
    return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *f)
{
    Command *last_cmd = NULL;
    Bool do_log = FALSE;

    /*Checks the parameters.*/
    if (!gengine || !game) /*File could be NULL intended.*/
    {
        return;
    }

    /*Checks if the log has to be created.*/
    if (f)
    {
        do_log = TRUE;
    }

    /*It runs the game while you dont want to exit or the game is terminated.*/
    while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE))
    {
        last_cmd = game_get_last_command(game);
        graphic_engine_paint_game(gengine, game, TRUE);
        command_get_user_input(last_cmd);
        /*Gets the last command.*/
        last_cmd = game_get_last_command(game);
        game_actions_update(game, last_cmd);

        /*Tries to execute all the gamerules.*/
        gamerules_try_exec_all(game, game_get_game_values(game));

        /*Refreshes the screen so that the player can see what he did.*/
        graphic_engine_paint_game(gengine, game, FALSE);

        /*Makes the log.*/
        if (do_log)
        {
            fprintf(f, "Player %ld executed ", player_get_player_id(game_get_actual_player(game)));
            command_print(last_cmd, f);
            fprintf(f, "\n");
        }

        /*Waits a bit so that the player can look what he did*/
        if (command_get_code(last_cmd) == INSPECT || command_get_code(last_cmd) == CHAT)
            sleep(READING_SECONDS);
        else
            sleep(command_get_code(last_cmd) == EXIT ? 0 : 1);

        /*Goes to the next turn if a command that changes turn is used.*/
        if (command_get_code(last_cmd) == MOVE)
            game_next_turn(game);

        game_next_command(game);
    }
}

void game_loop_cleanup(Game **game, Graphic_engine *gengine)
{
    /*Frees all the memory.*/
    game_destroy(game);
    graphic_engine_destroy(gengine);
}
