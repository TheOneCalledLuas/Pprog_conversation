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
#define READING_SECONDS 1        /*!< Seconds to read the screen. */
#define NUMBER_OF_BAD_LETTERS 13 /*!<Number of possible invalid letters for a new savefile name*/
#define NAME_SIZE 100            /*!< Max size of the name of the savefile. */
#define FIRST_CHAR 0             /*!<Position number 0 of a string, used to get inputs in menu*/
#define SECOND_CHAR 1            /*!<Position number 1 of a string, used to get inputs in menu*/

/**
 * @brief It defines the menu actions.
 */
typedef enum Menu_actions
{
    CREATE = 1, /*!<Code for create savefile*/
    LOAD,       /*!<Code for load savefile*/
    DELETE,     /*!<Code for delete savefile*/
    EXIT_MENU,  /*!<Code for exit menu*/
    GO_BACK,    /*!<Code for go back to the previous menu*/
    OK_MENU,    /*!<Code for ok menu exit*/
    FAIL_MENU   /*!<Code for fail menu exit*/
} Menu_actions;

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
int game_loop_init(Game **game, Graphic_engine **gengine, Graphic_engine **gengine_menu, char *file_name);

/**
 * @brief Main game loop, where all the actions take place.
 *
 * @author Saul Lopez Romero
 * @param game Pointer to the game.
 * @param gengine Pointer to the graphic engine.
 * @param f Pointer to the file for the log.
 * @param base_savefile named of the file that is used a template for new games
 */
void game_loop_run(Game **game, Graphic_engine *gengine, Graphic_engine *gengine_menu, FILE *f, char *base_savefile);

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
Menu_actions game_loop_menu(Game **game, Graphic_engine *ge_menu, char *filename);

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
    if (!game_loop_init(&game, &gengine, &gengine_menu, argv[1]))
    {
        game_loop_run(&game, gengine, gengine_menu, f, argv[1]);
        game_loop_cleanup(&game, gengine, gengine_menu);
        /*Closes the log if it proceeds.*/
        if (f)
            fclose(f);
    }
    else
    {
        game_loop_cleanup(&game, gengine, gengine_menu);
        if (f)
            fclose(f);
    }

    /*Clean exit.*/
    return EXIT_SUCCESS;
}

int game_loop_init(Game **game, Graphic_engine **gengine, Graphic_engine **gengine_menu, char *file_name)
{
    Menu_actions cond = OK_MENU;
    /*Takes all the information related to the game from a file.*/
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error while initializing game.\n");
        return EXIT_FAILURE;
    }

    /*Starts the menu graphich_engine*/
    if (!(*gengine_menu = graphic_engine_menu_create()))
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }

    /*Loads or creates a new game*/
    if (FAIL_MENU == (cond = game_loop_menu(game, *gengine_menu, file_name)))
    {
        fprintf(stderr, "Error while loading or creating a game.\n");
        game_destroy(game);
        return EXIT_FAILURE;
    }
    else if (cond == EXIT_MENU)
    {
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

    /*Clean exit.*/
    return 0;
}

Menu_actions game_loop_menu(Game **game, Graphic_engine *ge_menu, char *file_name)
{
    Bool condition = FALSE;
    char str[WORD_SIZE] = "", str2[NAME_SIZE] = "", bad_letters[NUMBER_OF_BAD_LETTERS] = ".&|?'\"\n!¿¡";
    int number = 0, i = 0, j = 0;

    do
    {
        /*If there is at least one existing savefile, it gives some options for the user*/
        if (game_get_n_savefiles(*game) > 0)
        {
            do
            {
                /*Gets the input*/
                if (game_get_n_savefiles(*game) >= MAX_SAVEFILES)
                {
                    do
                    {
                        graphic_engine_menu_paint(ge_menu, *game, LIMIT_SAVEFILES);
                        printf("prompt>");
                        /*I get the input this way to prevent possible errors.*/
                        scanf("%s", str);
                        if (str[FIRST_CHAR] == '2' || str[FIRST_CHAR] == '3' || str[FIRST_CHAR] == '4')
                        {
                            /*If the input is correct, it cuts the string and sets the condition to TRUE*/
                            str[SECOND_CHAR] = '\0';
                            number = atoi(str);
                            condition = TRUE;
                        }
                        else if (str[FIRST_CHAR] == '1' && game_get_n_savefiles(*game) < MAX_SAVEFILES)
                        {
                            str[SECOND_CHAR] = '\0';
                            number = atoi(str);
                            condition = TRUE;
                        }
                    } while (condition == FALSE);
                }
                else
                {
                    do
                    {
                        graphic_engine_menu_paint(ge_menu, *game,EXISTING_SAVES);
                        printf("prompt>");
                        scanf("%s", str);
                        if (str[FIRST_CHAR] == '1' || str[FIRST_CHAR] == '2' || str[FIRST_CHAR] == '3' || str[FIRST_CHAR] == '4')
                        {
                            str[SECOND_CHAR] = '\0';
                            number = atoi(str);
                            condition = TRUE;
                        }
                    } while (condition == FALSE);
                }
                condition = FALSE;
                /*If the player wants to create a new game , it does this*/
                if (number == CREATE)
                {
                    if (game_get_n_savefiles(*game) < MAX_SAVEFILES)
                    {
                        /*Paints the menu*/
                        graphic_engine_menu_paint(ge_menu, *game, NEW_GAME);
                        do
                        {
                            /*Gets the name*/
                            printf("propmt>");
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
                            if (str[FIRST_CHAR] != '4')
                            {

                                /*Checks that the name doesnt match the one where the new game information is stored, but first it cuts the name */
                                for (i = 0; i < strlen(file_name) - strlen(".dat"); i++)
                                {
                                    str2[i] = file_name[i];
                                }
                                str2[i] = '\0';
                                if (strcmp(str, str2 + strlen("data/")) == 0)
                                    condition = TRUE;

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
                                    /*And starts a new game using the template*/
                                    game_create_from_file(game, file_name);
                                    if (ERROR == game_add_new_savefile(*game, str))
                                    {
                                        printf("Error while creating new savefile.\n");
                                        return FAIL_MENU;
                                    }
                                    /*Saves the game*/
                                    if (game_reader_save_game(*game, str) == ERROR)
                                    {
                                        printf("Error while saving game.\n");
                                        return FAIL_MENU;
                                    }
                                }
                                /*Else, it continues looping*/
                                else
                                    graphic_engine_menu_paint(ge_menu, *game, FAIL_NEW_GAME);
                            }
                            else
                            {
                                condition = TRUE;
                                number = GO_BACK;
                            }
                        } while (condition == FALSE);
                        if (number != GO_BACK)
                        {
                            game_set_current_savefile(*game, str);
                            /*Does an fgets cause if not the first game loop gets skiped as it reads a \n*/
                            fgets(str, WORD_SIZE, stdin);
                            return OK_MENU;
                        }
                    }
                }
                else if (number == LOAD)
                {
                    /*Prints the menu*/
                    graphic_engine_menu_paint(ge_menu, *game, LOAD_GAME);
                    /*Asks the user a file*/
                    do
                    {
                        /*Gets the name of the savefile*/
                        printf("prompt>");
                        scanf("%s", str);
                        if (str[FIRST_CHAR] != '4')
                        {

                            /*Checks that savefile exists*/
                            for (i = 0; i < game_get_n_savefiles(*game); i++)
                            {
                                if (strcmp(str, game_get_savefile(*game, i)) == 0)
                                {
                                    /*If it finds it, it loads it and sets condition to TRUE*/
                                    /*Gets the real location of the file*/
                                    strcpy(str2, str);
                                    sprintf(str, "data/%s.dat", str2);
                                    /*Loads the real file*/
                                    if (game_create_from_file(game, str) == ERROR)
                                    {
                                        fprintf(stderr, "Error while loading game.\n");
                                        return FAIL_MENU;
                                    }
                                    /*Sets the condition to TRUE so that it stops looping*/
                                    condition = TRUE;
                                }
                            }
                            if (condition == FALSE)
                                graphic_engine_menu_paint(ge_menu, *game, FAIL_LOAD_GAME);
                        }
                        else
                        {
                            /*If the user wants to go back, it sets the condition to TRUE*/
                            condition = TRUE;
                            number = GO_BACK;
                        }
                    } while (condition == FALSE);
                    if (number != GO_BACK)
                    {
                        game_set_current_savefile(*game, str2);
                        /*Gets a string from the terminal cuase if not the first action that the player does, gets ignored, as there is a \n*/
                        fgets(str, WORD_SIZE, stdin);
                        return OK_MENU;
                    }
                }
                else if (number == DELETE)
                {
                    /*Prints the menu*/
                    graphic_engine_menu_paint(ge_menu, *game, DELETE);
                    /*Gets the name of the savefile*/
                    printf("prompt>");
                    scanf("%s", str);
                    /*Checks that savefile exists*/
                    for (i = 0; i < game_get_n_savefiles(*game); i++)
                    {
                        if (strcmp(str, game_get_savefile(*game, i)) == 0)
                        {
                            /*If it finds it, it deletes it and sets condition to TRUE*/
                            game_delete_savefile(*game, str);
                        }
                    }
                    /*Even if it doesn't find the file, as we dont want to force the player to delete a savefile.*/
                    /*we set the condition to TRUE so it goes out of the loop*/
                    condition = TRUE;
                }
                /*If the player wants to exit the menu, it sets the condition to TRUE*/
                else if (number == EXIT_MENU)
                {
                    fgets(str, WORD_SIZE, stdin);
                    return EXIT_MENU;
                }
            } while (condition == FALSE);
        }

        /*If there aren't any savefiles, it makes the player create a new one*/
        else
        {
            /*As there arent any savefiles, ask the user for the name of the new savefile*/
            graphic_engine_menu_paint(ge_menu, *game, NO_SAVES);
            do
            {
                condition = FALSE;
                printf("prompt>");
                scanf("%s", str);
                if (str[FIRST_CHAR] == '4')
                {
                    fgets(str, WORD_SIZE, stdin);
                    return EXIT_MENU;
                }
                else
                {
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
                }
            } while (condition == FALSE);
            /*If the name is ok, it creates the new savefile*/
            if (ERROR == game_add_new_savefile(*game, str))
            {
                graphic_engine_menu_paint(ge_menu, *game, NO_SAVES);
                return FAIL_MENU;
            }
            game_reader_save_game(*game, str);

            /*Does an fgets cause if not the first game loop gets skiped as it reads a \n*/
            fgets(str, WORD_SIZE, stdin);
            return OK_MENU;
        }
        if (number == DELETE)
            condition = FALSE;
        if (number == GO_BACK)
            condition = FALSE;
    } while (condition == FALSE);

    fgets(str, WORD_SIZE, stdin);
    return OK_MENU;
}

void game_loop_run(Game **game, Graphic_engine *gengine, Graphic_engine *gengine_menu, FILE *f, char *base_savefile)
{
    Command *last_cmd = NULL;
    CommandCode last_code = UNKNOWN;
    Bool do_log = FALSE;

    /*It runs the game while you dont want to exit or the game is terminated.*/
    graphic_engine_paint_game(gengine, *game, TRUE);
    while ((last_code != EXIT) && (game_get_finished(*game) == FALSE))
    {
        if (last_code == MENU)
        {
            game_loop_menu(game, gengine_menu, base_savefile);
        }
        if (last_code == MOVE)
            graphic_engine_paint_game(gengine, *game, TRUE);

        last_cmd = game_get_last_command(*game);
        last_code = command_get_code(last_cmd);
        printf("prompt>");
        command_get_user_input(last_cmd);
        /*Gets the last command.*/
        last_cmd = game_get_last_command(*game);
        last_code = command_get_code(last_cmd);
        /*Checks if the command is valid.*/
        game_actions_update(*game, last_cmd);
        if (last_code == SAVE)
        {
            if (game_reader_save_game(*game, game_get_current_savefile(*game)) == ERROR)
            {
                fprintf(stderr, "Error while saving game.\n");
                return;
            }
            command_set_argument(last_cmd, "game", 0);
            command_set_argument(last_cmd, "saved", 1);
            command_set_argument(last_cmd, "as", 2);
            command_set_argument(last_cmd, game_get_current_savefile(*game), 3);
            command_set_status(last_cmd, OK);
        }

        /*Tries to execute all the gamerules.*/
        gamerules_try_exec_all(*game, game_get_game_values(*game));

        /*Refreshes the screen so that the player can see what he did.*/
        graphic_engine_paint_game(gengine, *game, FALSE);

        /*Makes the log.*/
        if (do_log)
        {
            fprintf(f, "Player %ld executed ", player_get_player_id(game_get_actual_player(*game)));
            command_print(last_cmd, f);
            fprintf(f, "\n");
        }

        if (last_code != MENU)
        {

            /*Waits a bit so that the player can look what he did*/
            if (last_code == MOVE)
            {
                printf("waiting :)");
                sleep(READING_SECONDS);
            }

            /*Goes to the next turn if a command that changes turn is used.*/
            if (last_code == MOVE)
                game_next_turn(*game);

            game_next_command(*game);
        }
    }
}

void game_loop_cleanup(Game **game, Graphic_engine *gengine, Graphic_engine *gengine_menu)
{
    /*Frees all the memory.*/
    game_destroy(game);
    graphic_engine_destroy(gengine);
    graphic_engine_menu_destroy(gengine_menu);
    *game = NULL;
}
