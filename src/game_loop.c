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
#define READING_SECONDS 4        /*!< Seconds to read the screen. */
#define NUMBER_OF_BAD_LETTERS 13 /*!<Number of possible invalid letters for a new savefile name*/
#define NAME_SIZE 100            /*!< Max size of the name of the savefile. */

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
int game_loop_init(Game **game, Graphic_engine **gengine,Graphic_engine **gengine_menu, char *file_name);

/**
 * @brief Main game loop, where all the actions take place.
 *
 * @author Saul Lopez Romero
 * @param game Pointer to the game.
 * @param gengine Pointer to the graphic engine.
 * @param f Pointer to the file for the log.
 */
void game_loop_run(Game *game, Graphic_engine *gengine,Graphic_engine *gengine_menu, FILE *f);

/**
 * @brief Frees the memory and closes the game.
 *
 * @author Fernando Mijangos
 * @param game Pointer to the game.
 * @param gengine The graphic engine you are using.
 */
void game_loop_cleanup(Game **game, Graphic_engine *gengine, Graphic_engine *gengine_menu);

/**
 * @brief Loads or creates a new game, asks the user to chose.
 *
 * @author Fernando Mijangos
 * @param game Pointer to the game.
 * @param filename Name of the file where the information for new games is stored, so it doesnt write over it.
 * @return OK if everything went well, ERROR otherwise.
 */
Status game_loop_load_or_save(Game **game, char *filename);

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
    Graphic_engine *gengine_menu = NULL;
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
    if (!game_loop_init(&game, &gengine,&gengine_menu, argv[1]))
    {
        game_loop_run(game, gengine, gengine_menu,f);
        game_loop_cleanup(&game, gengine, gengine_menu);
        /*Closes the log if it proceeds.*/
        if (f)
            fclose(f);
    }

    /*Clean exit.*/
    return EXIT_SUCCESS;
}

int game_loop_init(Game **game, Graphic_engine **gengine,Graphic_engine **gengine_menu, char *file_name)
{
    /*Takes all the information related to the game from a file.*/
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error while initializing game.\n");
        return EXIT_FAILURE;
    }
    /*Loads or creates a new game*/
    if (ERROR == game_loop_load_or_save(game, file_name))
    {
        fprintf(stderr, "Error while loading or creating a game.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    /*Starts the graphic engine.*/
    if ((*gengine = graphic_engine_create()) == NULL)
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    /*Starts the menu graphich_engine*/
    if(!(*gengine_menu = graphic_engine_menu_create()))
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    /*Clean exit.*/
    return 0;
}

Status game_loop_load_or_save(Game **game, char *file_name)
{
    Bool condition = FALSE;
    char str[WORD_SIZE], str2[NAME_SIZE], bad_letters[NUMBER_OF_BAD_LETTERS] = ".&|?'\"\n!¿¡";
    int number, i, j;

    /*Asks if you want to load or save a game*/
    if (game_get_n_savefiles(*game) > 0)
    {
        do
        {
            printf("Do you want to create(1) or load(2) a game:");
            scanf("%d", &number);
            if (number == 1)
            {
                /*If the player wants to create a game, asks for the name of the new game*/
                if (game_get_n_savefiles(*game) < MAX_SAVEFILES)
                {
                    do
                    {
                        printf("Existing savefiles:\n");
                        /*Prints all the names of the savefiles*/
                        for (i = 0; i < game_get_n_savefiles(*game); i++)
                            printf("<%s>\n", game_get_savefile(*game, i));
                        /*Asks the user to chose a name for the new game*/
                        printf("Chose a name for the new game that doesn't match the ones above:");
                        scanf("%s", str);
                        /*Checks the the name doesnt have weird characters*/
                        for (i = 0; i < strlen(str); i++)
                        {
                            for (j = 0; j < NUMBER_OF_BAD_LETTERS; j++)
                            {
                                if (str[i] == bad_letters[j])
                                    condition = TRUE;
                            }
                        }
                        /*Checks that the name doesnt match the one where the new game information is stored, but first it cuts the name */
                        for(i=0;i<strlen(file_name)-strlen(".dat");i++)
                        {
                            str2[i]=file_name[i];
                        }
                        str2[i]='\0';
                        if(strcmp(str, str2+strlen("data/"))==0)
                        {
                            condition = TRUE;
                            printf("Dont use a name with that word, it can mess with the real data file, try again\n");
                        }

                        /*Cheks that the name doesnt match any other existing one*/
                        for (i = 0; i < game_get_n_savefiles(*game); i++)
                        {
                            if (strcmp(str, game_get_savefile(*game, i)) == 0)
                                condition = TRUE;
                        }
                        condition = !condition;
                        /*If there aren't any bad characters it does this*/
                        if (condition == TRUE)
                        {
                            /*The game that ha been loadede was already a new game, so it just adds this new game*/
                            if (ERROR == game_add_new_savefile(*game, str))
                            {
                                fprintf(stderr, "Error while creating new savefile.\n");
                                return ERROR;
                            }
                            /*Saves the game*/
                            if (game_reader_save_game(*game, str) == ERROR)
                            {
                                fprintf(stderr, "Error while saving game.\n");
                                return ERROR;
                            }
                        }
                        /*Else, it continues looping*/
                        else
                            printf("Not a good name, try again\n");
                    } while (condition == FALSE);
                    game_set_current_savefile(*game, str);
                    /*Does an fgets cause if not the first game loop gets skiped as it reads a \n*/
                    fgets(str, WORD_SIZE, stdin);
                    return OK;
                }
                else
                    printf("Max_number of savefiles reached\n");
            }
            else if (number == 2)
            {
                /*Prints all the savefiles*/
                printf("Existing savefiles:\n");
                for (i = 0; i < game_get_n_savefiles(*game); i++)
                    printf("<%s>\n",game_get_savefile(*game, i));
                /*Asks the user to chose one*/
                do
                {
                    printf("Type the name of the savefile you want to load, the names are shown up:\n");
                    scanf("%s", str);
                    /*Checks that savefile exists*/
                    for (i = 0; i < game_get_n_savefiles(*game); i++)
                    {
                        if (strcmp(str, game_get_savefile(*game, i)) == 0)
                        {
                            /*If it finds it, it loads it and sets condition to TRUE*/
                            /*Destroys what had been created*/
                            game_destroy(game);
                            /*Gets the real location of the file*/
                            strcpy(str2, str);
                            sprintf(str, "data/%s.dat", str2);
                            /*Loads the real file*/
                            if (game_create_from_file(game, str) == ERROR)
                            {
                                fprintf(stderr, "Error while loading game.\n");
                                return ERROR;
                            }
                            /*Sets the condition to TRUE so that it stops looping*/
                            condition = TRUE;
                        }
                    }
                } while (condition == FALSE);
                game_set_current_savefile(*game, str2);
            }
            else
                printf("Chose an available choice\n");

        } while (condition == FALSE);
        /*Does an fgets cause if not the first game loop gets skiped as it reads a \n*/
        fgets(str, WORD_SIZE, stdin);
        return OK;
    }
    else
    {
        /*As there arent any savefiles, ask the user for the name of the new savefile*/
        do
        {
            condition = FALSE;
            printf("There are no savefiles, chose a name for the new game:");
            scanf("%s", str);
            /*Checks the name of the new savefile*/
            for (i = 0; i < strlen(str); i++)
            {
                for (j = 0; j < NUMBER_OF_BAD_LETTERS; j++)
                {
                    if (str[i] == bad_letters[j])
                        condition = TRUE;
                }
            }
            condition = !condition;
        } while (condition == FALSE);
        /*If the name is ok, it creates the new savefile*/
        if (ERROR == game_add_new_savefile(*game, str))
        {
            fprintf(stderr, "Error while creating new savefile.\n");
            return ERROR;
        }
        game_reader_save_game(*game, str);
    }
    /*Does an fgets cause if not the first game loop gets skiped as it reads a \n*/
    fgets(str, WORD_SIZE, stdin);
    return OK;
}

void game_loop_run(Game *game, Graphic_engine *gengine,Graphic_engine *gengine_menu, FILE *f)
{
    Command *last_cmd = NULL;
    Bool do_log = FALSE;

    /*It runs the game while you dont want to exit or the game is terminated.*/
    while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE))
    {
        last_cmd = game_get_last_command(game);
        graphic_engine_paint_game(gengine, game, TRUE);
        command_get_user_input(last_cmd);
        /*Gets the last command.*/
        last_cmd = game_get_last_command(game);
        game_actions_update(game, last_cmd);
        if (command_get_code(last_cmd) == SAVE)
        {
            if (game_reader_save_game(game, game_get_current_savefile(game)) == ERROR)
            {
                fprintf(stderr, "Error while saving game.\n");
                return;
            }
            command_set_argument(last_cmd, "game", 0);
            command_set_argument(last_cmd, "saved", 1);
            command_set_argument(last_cmd, "as", 2);
            command_set_argument(last_cmd, game_get_current_savefile(game), 3);
            command_set_status(last_cmd, OK);
        }

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

void game_loop_cleanup(Game **game, Graphic_engine *gengine, Graphic_engine *gengine_menu)
{
    /*Frees all the memory.*/
    game_destroy(game);
    graphic_engine_destroy(gengine);
    graphic_engine_menu_destroy(gengine_menu);
}
