/**
 * @brief It implements a textual graphic engine.
 *
 * @file graphic_engine.c
 * @author Saul Lopez Romero && Fernando Mijangos
 * @version 7
 * @date 2-03-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include "game.h"
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "set.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Gap measures.*/

/**
 * Map width.*/
#define WIDTH_MAP 67
/**
 * Description width.*/
#define WIDTH_DES 30
/**
 * Banner width.*/
#define WIDTH_BAN 23
/**
 * Map height.*/
#define HEIGHT_MAP 29
/**
 * Banner height.*/
#define HEIGHT_BAN 1
/**
 * Help height.*/
#define HEIGHT_HLP 3
/**
 * FDB height.*/
#define HEIGHT_FDB 3
/**
 * Max string lenght.*/
#define MAX_STRING_GE 255
/**
 * Space width.*/
#define WIDTH_SPACE 21
/**
 * Space height.*/
/**
 * Start of the gap when placed.*/
#define STARING_POINT 1
/**
 * The amount of charactes the icon for tha player occupies.*/
#define PLAYER_LENGTH 7
/**
 * Elements that cannot be written per room.*/
#define NON_WRITTABLE_ELEMS 5
#define LIMIT_OF_ELEMENTS 2 /*!<Number of elements that can't be written on when printing each line of each space.*/
#define EXTRA_LINE 1        /*!<Number of extra lines beetween elements of the ge.*/

/**
 * @brief Numbers used for the lines that form the sapce description.
 */
typedef enum
{
    FIRST_LINE,   /*!<First line of a space*/
    SECOND_LINE,  /*!<Second line of a space*/
    THIRD_LINE,   /*!<Third line of a space*/
    FOURTH_LINE,  /*!<Fourth line of a space*/
    FIFTH_LINE,   /*!<Fifth line of a space*/
    SIXTH_LINE,   /*!<Sixth line of a space*/
    SEVENTH_LINE, /*!<Seventh line of a space*/
    EIGHT_LINE,   /*!<Eight line of a space*/
    NINETH_LINE,  /*!<Nineth line of a space*/
    HEIGHT_SPACE  /*!<Space height*/
} space_information;
/**
 * Space positions in array
 * This is like this so that later when printing its easier with a for
 *    [0] [1] [2]
 *    [3] [4] [5]
 *    [6] [7] [8] */
typedef enum
{
    NORTH_WEST,      /*!<North west direction.*/
    NORTH,           /*!<North direction.*/
    NORTH_EAST,      /*!<North east direction.*/
    WEST,            /*!<West direction.*/
    ACTUAL_POSITION, /*!<Actual direction.*/
    EAST,            /*!<East direction.*/
    SOUTH_WEST,      /*!<South west direction.*/
    SOUTH,           /*!<South direction.*/
    SOUTH_EAST,      /*!<South east direction.*/
    NUM_IDS          /*!<Number of ids.*/
} Positions;
/**
 * @brief _Graphic_engine
 *
 * This struct stores all the information of the dimmensions needed for the graphic engine.
 */
struct _Graphic_engine
{
    Area *map;      /*!< Map area dimensions.*/
    Area *descript; /*!< Description area dimensions.*/
    Area *banner;   /*!< Banner area dimensions.*/
    Area *help;     /*!< Help area dimensions.*/
    Area *feedback; /*!< Dimensions of each parameter needed.*/
};

/* PRIVATE FUNCTIONS.*/

/**
 * @brief prints the information of a space in a given array
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @param space_id Id of the space you are searching information from.
 * @param destination the array where you are storing the information.
 * @return OK if everything went well, ERROR otherwise.
 */
Status graphic_engine_print_space(Game *game, Id space_id, char **destination);

/**
 * @brief Initalises all the data to be printed in an array structure.
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game.
 * @param map Map to be initialised.
 */
Status map_init(Game *game, char **map);

/* END OF PRIVATE FUNCTIONS.*/

Graphic_engine *graphic_engine_create()
{
    static Graphic_engine *ge = NULL;

    /*Screen initialisation.*/
    screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4 * EXTRA_LINE, WIDTH_MAP + WIDTH_DES + 3 * EXTRA_LINE);

    /*Space allocation and error management.*/
    ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
    if (ge == NULL)
    {
        return NULL;
    }

    /*It gives the value needed for each variable.*/
    ge->map = screen_area_init(STARING_POINT, STARING_POINT, WIDTH_MAP, HEIGHT_MAP);
    ge->descript = screen_area_init(WIDTH_MAP + 2 * EXTRA_LINE, STARING_POINT, WIDTH_DES, HEIGHT_MAP);
    ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 * EXTRA_LINE - WIDTH_BAN) / 2), HEIGHT_MAP + 2 * EXTRA_LINE, WIDTH_BAN, HEIGHT_BAN);
    ge->help = screen_area_init(1 * EXTRA_LINE, HEIGHT_MAP + HEIGHT_BAN + 2 * EXTRA_LINE, WIDTH_MAP + WIDTH_DES + 1 * EXTRA_LINE, HEIGHT_HLP);
    ge->feedback = screen_area_init(1 * EXTRA_LINE, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3 * EXTRA_LINE, WIDTH_MAP + WIDTH_DES + 1 * EXTRA_LINE, HEIGHT_FDB);

    /*Clean exit.*/
    return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
    /*Error management.*/
    if (!ge)
        return;

    /*Destroys everything.*/
    screen_area_destroy(ge->map);
    screen_area_destroy(ge->descript);
    screen_area_destroy(ge->banner);
    screen_area_destroy(ge->help);
    screen_area_destroy(ge->feedback);

    screen_destroy();
    free(ge);
    /*Clean exit.*/
    return;
}

Status map_init(Game *game, char **map)
{
    int i = 0, j = 0, t = 0, v = 0;
    char **aux_map = NULL;
    Id actual_id[NUM_IDS] = {NO_ID};
    Link_Property link_statuses[NUM_IDS] = {CLOSED};

    /*Error control.*/
    if (!game || !map)
        return ERROR;

    /*Allocates memory for the aux_map.*/
    if (!(aux_map = (char **)calloc(HEIGHT_SPACE, sizeof(char *))))
    {
        return ERROR;
    }
    for (i = 0; i < HEIGHT_SPACE; i++)
    {
        if (!(aux_map[i] = (char *)calloc(WIDTH_SPACE, sizeof(char))))
        {
            for (i = 0; i < HEIGHT_SPACE; i++)
            {
                if (aux_map[i] != NULL)
                {
                    free(aux_map[i]);
                }
            }
            free(aux_map);
            return ERROR;
        }
    }

    if ((actual_id[ACTUAL_POSITION] = player_get_player_location(game_get_actual_player(game))) != NO_ID)
    {
        /*1-Gets the spaces located to the different points of the space, and the information about the links.*/
        actual_id[NORTH] = game_get_space_at(game, actual_id[ACTUAL_POSITION], N);
        link_statuses[NORTH] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], N);
        actual_id[SOUTH] = game_get_space_at(game, actual_id[ACTUAL_POSITION], S);
        link_statuses[SOUTH] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], S);
        actual_id[WEST] = game_get_space_at(game, actual_id[ACTUAL_POSITION], W);
        link_statuses[WEST] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], W);
        actual_id[EAST] = game_get_space_at(game, actual_id[ACTUAL_POSITION], E);
        link_statuses[EAST] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], E);
        actual_id[NORTH_EAST] = NO_ID;
        link_statuses[NORTH_EAST] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], UNK_DIRECTION);
        actual_id[NORTH_WEST] = NO_ID;
        link_statuses[NORTH_WEST] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], UNK_DIRECTION);
        actual_id[SOUTH_EAST] = NO_ID;
        link_statuses[SOUTH_EAST] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], UNK_DIRECTION);
        actual_id[SOUTH_WEST] = NO_ID;
        link_statuses[SOUTH_WEST] = game_get_space_outcoming_connection_info(game, actual_id[ACTUAL_POSITION], UNK_DIRECTION);

        /*2-Cleans the map.*/
        for (i = 0; i < HEIGHT_MAP; i++)
        {
            for (j = 0; j < WIDTH_MAP; j++)
            {
                map[i][j] = ' ';
            }
        }

        /*3-Fills the map.*/
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (!(graphic_engine_print_space(game, actual_id[i * 3 + j], aux_map)))
                    continue;

                if (link_statuses[i * 3 + j] != OPENED && actual_id[i * 3 + j] != actual_id[ACTUAL_POSITION])
                    continue;

                for (t = 0; t < HEIGHT_SPACE; t++)
                {
                    /*The -1 after width_space in the loop is so that it doesnt copy the '\0'*/
                    for (v = 0; v < WIDTH_SPACE - 1; v++)
                    {
                        map[i * (HEIGHT_SPACE + 1) + t][j * (WIDTH_SPACE + 2) + v] = aux_map[t][v];
                    }
                }
            }
        }

        /*4-Puts the arrows.*/
        if (actual_id[NORTH] != NO_ID)
            map[HEIGHT_SPACE][WIDTH_SPACE * 3 / 2 + 1] = (link_statuses[NORTH] == OPENED ? '^' : 'X');
        if (actual_id[WEST] != NO_ID)
            map[HEIGHT_SPACE * 2 - 4][WIDTH_SPACE] = (link_statuses[WEST] == OPENED ? '<' : 'X');
        if (actual_id[EAST] != NO_ID)
            map[HEIGHT_SPACE * 2 - 4][2 * WIDTH_SPACE + 2] = (link_statuses[EAST] == OPENED ? '>' : 'X');
        if (actual_id[SOUTH] != NO_ID)
            map[HEIGHT_SPACE * 2 + 1][1 + WIDTH_SPACE * 3 / 2] = (link_statuses[SOUTH] == OPENED ? 'v' : 'X');
        /*5-puts \0*/
        for (i = 0; i < HEIGHT_MAP; i++)
        {
            map[i][WIDTH_MAP - 1] = '\0';
        }
    }

    /*Frees the memroy.*/
    for (i = 0; i < HEIGHT_SPACE; i++)
    {
        if (aux_map[i])
            free(aux_map[i]);
    }
    free(aux_map);

    /*Clean exit.*/
    return OK;
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Bool refresh)
{
    Id id_aux = 0, *id_aux_2 = NULL, *id_list = NULL, desc_id = 0, *objects = NULL;
    Character *character = NULL;
    Player *player = NULL;
    Space *space_act = NULL, *last_space = NULL;
    Object *object = NULL;
    char str[MAX_STRING_GE], **map = NULL, *obj_name = NULL;
    int i = 0, n_objects = 0;
    CommandCode last_cmd = UNKNOWN;
    extern char *cmd_to_str[N_CMD][N_CMDT];
    player = game_get_actual_player(game);
    space_act = game_get_space(game, player_get_player_location(player));

    /*Error management.*/
    if (!ge || !game)
        return;

    /*MAP SECTION.*/
    /*1-Allocates memory needed.*/
    if (!(map = (char **)calloc(HEIGHT_MAP, sizeof(char *))))
    {
        return;
    }
    for (i = 0; i < HEIGHT_MAP; i++)
    {
        if (!(map[i] = (char *)calloc(WIDTH_MAP, sizeof(char))))
        {
            for (i = 0; i < HEIGHT_MAP; i++)
            {
                if (map[i])
                    free(map[i]);
            }
            free(map);
            return;
        }
    }
    /*2-Clears the map.*/
    screen_area_clear(ge->map);

    /*4-Sets the space where the player is at to discovered.*/
    if (space_set_discovered(space_act, TRUE) == ERROR)
        return;

    /*3-Fills the map that we modify and later print.*/
    if (map_init(game, map) == ERROR)
    {
        for (i = 0; i < HEIGHT_MAP; i++)
        {
            if (map[i])
                free(map[i]);
        }
        return;
    }

    /*4-Prints the map.*/
    for (i = 0; i < HEIGHT_MAP; i++)
    {
        screen_area_puts(ge->map, map[i]);
    }
    /*5-Frees the allocated memory.*/
    for (i = 0; i < HEIGHT_MAP; i++)
    {
        if (map[i])
            free(map[i]);
    }
    free(map);

    /*DESCRIPTION SECTION.*/
    /*1-Clears the area.*/
    screen_area_clear(ge->descript);
    /*2-Prints the information about the objects inside space the player has discovered.*/
    sprintf(str, "  OBJECTS:");
    screen_area_puts(ge->descript, str);
    if (game_get_n_objects(game) >= 1)
    {
        /*Prints the objects.*/
        id_list = game_get_objects(game);
        for (i = 0; i < game_get_n_objects(game); i++)
        {
            if ((id_aux = game_get_object_location(game, id_list[i])) != NO_ID)
            {
                /*If the object is inside a discovered space it prints it.*/
                if (space_is_discovered(game_get_space(game, id_aux)) == TRUE)
                {
                    sprintf(str, "   %-12s : %ld", object_get_name(game_get_object(game, id_list[i])), id_aux);
                    screen_area_puts(ge->descript, str);
                }
            }
        }
        free(id_list);
    }

    /*3-Prints the information about the characters that have been discovered.*/
    screen_area_puts(ge->descript, " ");
    screen_area_puts(ge->descript, "  CHARACTERS");
    id_aux_2 = game_get_characters(game);
    for (i = 0; i < game_get_num_characters(game); i++)
    {
        id_aux = game_get_character_location(game, id_aux_2[i]);
        /*If the character is in a discovered space it prints its information.*/
        if (space_is_discovered(game_get_space(game, id_aux)) == TRUE)
        {
            character = game_get_character(game, id_aux_2[i]);
            sprintf(str, "   %-6s: %ld (%d)", character_get_description(character), game_get_character_location(game, character_get_id(character)), character_get_health(character));
            screen_area_puts(ge->descript, str);
        }
    }
    screen_area_puts(ge->descript, " ");
    free(id_aux_2);

    /*4-Prints the player information.*/
    sprintf(str, "  PLAYERS INFORMATION");
    screen_area_puts(ge->descript, str);

    for (i = 0; i < game_get_n_players(game); i++)
    {
        player = game_get_player(game, i);
        sprintf(str, "   %-9s: %ld (%d)", player_get_player_name(player), player_get_player_location(player), player_get_health(player));
        screen_area_puts(ge->descript, str);
    }
    screen_area_puts(ge->descript, " ");
    player = game_get_actual_player(game);
    if ((n_objects = player_get_n_objects(player)) <= 0)
    {
        sprintf(str, "   %s has no objects", player_get_player_name(player));
        screen_area_puts(ge->descript, str);
        screen_area_puts(ge->descript, " ");
    }
    else
    {
        sprintf(str, "   %s inventory:", player_get_player_name(player));
        screen_area_puts(ge->descript, str);
        objects = player_get_inventory(player);
        for (i = 0; i < n_objects; i++)
        {
            obj_name = object_get_name(game_get_object(game, objects[i]));
            sprintf(str, "    %s", obj_name);
            screen_area_puts(ge->descript, str);
        }
        screen_area_puts(ge->descript, " ");
        free(objects);
        objects = NULL;
    }
    /*5-Prints the message if the conditions for it appearing are satisfied.*/
    if (command_get_code(game_get_last_command(game)) == CHAT && refresh == FALSE)
    {
        id_aux = space_get_character(space_act);
        /*Checks that there's a friendly NPC to talk with.*/
        if (id_aux != NO_ID && (character_get_friendly(game_get_character(game, id_aux)) == TRUE))
        {
            screen_area_puts(ge->descript, " ");
            sprintf(str, "  MESSAGE: %s", character_get_message(game_get_character(game, id_aux)));
            screen_area_puts(ge->descript, str);
            command_set_status(game_get_last_command(game), OK);
        }
    }
    /*6.Prints the object information if the conditions for it appearing are satisfied.*/
    if (command_get_code(game_get_last_command(game)) == INSPECT && refresh == FALSE)
    {
        last_space = game_get_space(game, player_get_player_location(player));
        /*Searches for the object.*/
        desc_id = game_get_object_by_name(game, command_get_word(game_get_last_command(game)));
        if (desc_id >= 0 && (space_find_object(last_space, desc_id) != -1 || player_has_object(player, desc_id)))
        {
            /*If the object was found anywhere accesible by the player.*/
            object = game_get_object(game, desc_id);
            screen_area_puts(ge->descript, " ");
            sprintf(str, "  OBJECT DESCRIPTION:");
            screen_area_puts(ge->descript, str);
            sprintf(str, "  %s", object_get_description(object));
            screen_area_puts(ge->descript, str);
            command_set_status(game_get_last_command(game), OK);
        }
    }

    /*BANNER AREA.*/
    screen_area_puts(ge->banner, "    The anthill game ");

    /*HELP AREA.*/
    screen_area_clear(ge->help);
    sprintf(str, " The commands you can use are:");
    screen_area_puts(ge->help, str);
    sprintf(str, "     move or m, exit or e, take or t, drop or d, chat or c, attack or a, inspect or i");
    screen_area_puts(ge->help, str);

    /*FEEDBACK AREA.*/
    for (i = COMMANDS_SAVED - 1; i >= 0; i--)
    {
        last_cmd = command_get_code(game_get_previous_command(game, i + refresh));
        if (last_cmd != NO_CMD)
        {
            sprintf(str, " -%-7s (%1s):%s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], (command_get_status(game_get_previous_command(game, i + refresh)) == OK ? "OK" : "ERROR"));
            screen_area_puts(ge->feedback, str);
        }
        else
        {
            screen_area_puts(ge->feedback, " ");
        }
    }

    /*PRINTS ALL THE THINGS INTO THE TERMINAL.*/
    screen_paint(game_get_turn(game));
    if (command_get_code(game_get_last_command(game)) != EXIT)
    {
        fprintf(stdout, "%s", (refresh ? "prompt>" : "waiting :) "));
        fflush(stdout);
    }
}

Status graphic_engine_print_space(Game *game, Id space_id, char **destination)
{
    char aux[PLAYER_LENGTH] = {"   "}, aux_2[WIDTH_SPACE - LIMIT_OF_ELEMENTS], *aux_3 = NULL, aux_4[WIDTH_SPACE - NON_WRITTABLE_ELEMS];
    Space *space;
    int i, j, n_objs_space, cond = 0;
    Id *set;

    /*Error handling.*/
    if (!game || space_id == NO_ID || space_id == ID_ERROR)
        return ERROR;
    /*Checks if the player is in the room.*/
    if (space_id == player_get_player_location(game_get_actual_player(game)))
    {
        sprintf(aux, "%s", player_get_gdesc(game_get_actual_player(game)));
    }

    /*Gets the actual space.*/
    space = game_get_space(game, space_id);
    if (!space)
        return ERROR;

    /*If the space hasn't been discovered, it prints a blank space.*/
    if (space_is_discovered(space) == FALSE)
    {
        sprintf(destination[FIRST_LINE], "+------------------+");
        for (i = 1; i < HEIGHT_SPACE - 1; i++)
            sprintf(destination[i], "|                  |");
        sprintf(destination[NINETH_LINE], "+------------------+");
        return OK;
    }
    /*Starts printing the space.*/
    sprintf(destination[FIRST_LINE], "+------------------+");
    sprintf(destination[SECOND_LINE], "|%-7s %6s %3ld|", aux, ((aux_3 = character_get_description(game_get_character(game, space_get_character(space)))) != NULL ? aux_3 : ""), space_id);
    for (i = THIRD_LINE; i < EIGHT_LINE; i++)
    {
        sprintf(destination[i], "|%-18s|", space_get_gdesc_line(space, i - LIMIT_OF_ELEMENTS));
    }
    /*Once the space is printed, shows the objects on screen.*/
    n_objs_space = space_get_n_objects(space);
    set = (space_get_objects(space));

    if (set)
    {
        /*Looks how many strings it can print inside the 12 letters in the space given and stores the final string
        in aux_2 (WIDTH_SPACE -2 for the barriers, -3 for the extra things i'm placing)*/

        /*1-Looks how many objects it can fit inside the space given, 'i' will have the amount of objects that can be printed*/
        for (i = n_objs_space; cond == 0 && i != 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                cond += 1 + strlen(object_get_name(game_get_object(game, set[j])));
            }

            if (cond > WIDTH_SPACE - NON_WRITTABLE_ELEMS)
            {
                cond = 0;
            }
        }

        /*2-If there are any objects that can't be printed, set cond to 1 to later print an extra thing*/
        if (i < n_objs_space - 1)
            cond = TRUE;
        aux_2[0] = '\0';

        /*3-Fills the string with the tags of the objects that fit*/
        for (j = 0; j <= i; j++)
        {
            aux_3 = object_get_name(game_get_object(game, set[j]));
            if (aux_2[0] != '\0')
            {
                strcpy(aux_4, aux_2);
                sprintf(aux_2, "%s%c%s", aux_4, ',', aux_3);
            }
            else
            {
                sprintf(aux_2, "%s", (aux_3 ? aux_3 : " "));
            }
        }

        /*4-If the previous condition is equal to 1, it adds "..." so that the player
        knows there are more objects that are't being represented*/
        if (cond == TRUE)
        {
            strcpy(aux_4, aux_2);
            sprintf(aux_2, "%s%s", aux_4, "...");
        }
        free(set);
    }
    else
    {
        aux_2[0] = '\0';
    }

    /*Finishes printing the spaces.*/
    sprintf(destination[EIGHT_LINE], "|%-18s|", aux_2);
    sprintf(destination[NINETH_LINE], "+------------------+");
    return OK;
}
