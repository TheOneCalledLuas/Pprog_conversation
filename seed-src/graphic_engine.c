/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Saul Lopez Romero && Fernando Mijangos Varas
 * @version 1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include "game.h"
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "set.h"
#include "types.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Map measures.*/
#define WIDTH_MAP 58
#define WIDTH_DES 30
#define WIDTH_BAN 23
#define HEIGHT_MAP 29
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3
#define MAX_STRING_GE 255
#define WIDTH_SPACE 18
#define HEIGHT_SPACE 9

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

/* PRIVATE FUNCTIONS*/

/**
 * @brief prints the information of a space in a given array
 * @author Fernando Mijangos
 *
 * @param game Pointer to the game
 * @param space_id Id of the space you are searching information from
 * @param destination the array where you are storing the information
 * @return OK if everything went well, ERROR otherwise
 */
Status print_space(Game *game, Id space_id, char destination[HEIGHT_SPACE][WIDTH_SPACE]);

/* END OF PRIVATE FUNCTIONS*/

Graphic_engine *graphic_engine_create()
{
    static Graphic_engine *ge = NULL;

    if (ge)
    {
        return ge;
    }

    screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);

    /*Allocation of space and error management.*/
    ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
    if (ge == NULL)
    {
        return NULL;
    }

    /*It gives the value needed for each variable.*/
    ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
    ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
    ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
    ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
    ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

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
    return;
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
    /*the actual_id is to organize the spaces in this way*/
    /* ictual_id[0]  actual_id[1] actual_id[2] */
    /* ictual_id[3]  actual_id[4] actual_id[5] */
    /* ictual_id[6]  actual_id[7] actual_id[8] */

    Id id_space = 0;
    Space *space_act = NULL;
    char str[MAX_STRING_GE];
    /*char spaces[] = {"                 "};*/
    char map[HEIGHT_MAP][WIDTH_MAP], aux_map[HEIGHT_SPACE][WIDTH_SPACE];
    int i = 0, j = 0, t = 0, v = 0;
    Id *id_list = NULL, actual_id[9];
    CommandCode last_cmd = UNKNOWN;
    extern char *cmd_to_str[N_CMD][N_CMDT];

    /* Paints the information in the map area.*/
    screen_area_clear(ge->map);
    if ((actual_id[4] = player_get_player_location(game_get_player(game))) != NO_ID)
    {
        /*Gets the spaces located to the different points of the space.*/
        space_act = game_get_space(game, actual_id[4]);
        actual_id[1] = space_get_north(space_act);
        actual_id[7] = space_get_south(space_act);
        actual_id[3] = space_get_west(space_act);
        actual_id[5] = space_get_east(space_act);

        /*Gets the spaces situated on the corners*/
        if ((actual_id[0] = space_get_north(game_get_space(game, actual_id[3]))) == ID_ERROR)
        {
            if ((actual_id[0] = space_get_west(game_get_space(game, actual_id[1]))) == ID_ERROR)
                actual_id[0] = NO_ID;
        }
        if ((actual_id[6] = space_get_south(game_get_space(game, actual_id[3]))) == ID_ERROR)
        {
            if ((actual_id[6] = space_get_west(game_get_space(game, actual_id[7]))) == ID_ERROR)
                actual_id[6] = NO_ID;
        }
        if ((actual_id[2] = space_get_north(game_get_space(game, actual_id[5]))) == ID_ERROR)
        {
            if ((actual_id[2] = space_get_east(game_get_space(game, actual_id[1]))) == ID_ERROR)
                actual_id[2] = NO_ID;
        }
        if ((actual_id[8] = space_get_south(game_get_space(game, actual_id[5]))) == ID_ERROR)
        {
            if ((actual_id[8] = space_get_east(game_get_space(game, actual_id[7]))) == ID_ERROR)
                actual_id[8] = NO_ID;
        }

        /*CLEANS THE MAP*/
        for (i = 0; i < HEIGHT_MAP; i++)
        {
            for (j = 0; j < WIDTH_MAP; j++)
            {
                map[i][j] = ' ';
            }
            map[i][WIDTH_MAP] = '\0';
        }

        /*FILLS THE MAP*/
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (!(print_space(game, actual_id[i * 3 + j], aux_map)))
                {
                    continue;
                }
                for (t = 0; t < HEIGHT_SPACE; t++)
                {
                    for (v = 0; v < WIDTH_SPACE - 1; v++)
                    {
                        map[i * (HEIGHT_SPACE + 1) + t][j * (WIDTH_SPACE + 2) + v] = aux_map[t][v];
                    }
                }
            }
        }

        /*PUTS THE ARROWS*/
        if (actual_id[1] != NO_ID)
            map[HEIGHT_SPACE][WIDTH_SPACE * 3 / 2 + 1] = '^';
        if (actual_id[3] != NO_ID)
            map[HEIGHT_SPACE * 2 - 4][WIDTH_SPACE + 1] = '<';
        if (actual_id[5] != NO_ID)
            map[HEIGHT_SPACE * 2 - 4][2 * WIDTH_SPACE + 1] = '>';
        if (actual_id[7] != NO_ID)
            map[HEIGHT_SPACE * 2 + 1][1 + WIDTH_SPACE * 3 / 2] = 'v';
        /*PUTS \0 IN CASE THEY WEREN'T PLACED*/
        for (i = 0; i < HEIGHT_MAP; i++)
        {
            map[i][WIDTH_MAP - 1] = '\0';
        }

        /*PRINTS THE MAP*/
        for (i = 0; i < HEIGHT_MAP; i++)
        {
            screen_area_puts(ge->map, map[i]);
        }
    }

    /* Paint in the description area */
    screen_area_clear(ge->descript);
    sprintf(str, "  Objects:");
    screen_area_puts(ge->descript, str);
    if (game_get_n_objects(game) >= 1)
    {
        /*Prints the objects.*/
        id_list = game_get_objects(game);
        for (i = 0; i < game_get_n_objects(game); i++)
        {
            if ((id_space = game_get_object_location(game, id_list[i])) != -1)
            {
                sprintf(str, "%s : %ld", object_get_name(game_get_object(game, id_list[i])), id_space);
                screen_area_puts(ge->descript, str);
            }
        }
        free(id_list);
    }
    /* Prints the Message.*/
    if (command_get_code(game_get_last_command(game)) == CHAT)
    {
        /*Checks that there's a friendly NPC to talk with.*/
        if (space_get_character(game_get_space(game, actual_id[4])) != NO_ID && character_get_friendly(game_get_character(game, space_get_character(game_get_space(game, actual_id[4])))) == TRUE)
        {
            sprintf(str, "  Message: %s", character_get_message(game_get_character(game, space_get_character(game_get_space(game, actual_id[4])))));
            screen_area_puts(ge->descript, str);
        }
    }

    /* Paint in the banner area */
    screen_area_puts(ge->banner, "    The anthill game ");

    /* Paint in the help area */
    screen_area_clear(ge->help);
    sprintf(str, " The commands you can use are:");
    screen_area_puts(ge->help, str);
    sprintf(str, "     next or s, back or w,left or a, right or d, exit or e, take or t, drop or d, chat or c, attack or f");
    screen_area_puts(ge->help, str);

    /* Paint in the feedback area */
    last_cmd = command_get_code(game_get_last_command(game));
    sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
    screen_area_puts(ge->feedback, str);

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

Status print_space(Game *game, Id space_id, char destination[HEIGHT_SPACE][WIDTH_SPACE])
{
    char aux[4] = {"   "}, aux_2[WIDTH_SPACE - 3], *aux_3 = NULL, aux_4[WIDTH_SPACE - 3];
    Space *space;
    int i, j, n_objs_space, cond = 0;
    Id *set;
    memset(aux_2, '\0', sizeof(aux_2));
    if (!game || space_id == NO_ID || space_id == ID_ERROR)
        return ERROR;
    if (space_id == player_get_player_location(game_get_player(game)))
    {
        strcpy(aux, "m0\"");
    }
    space = game_get_space(game, space_id);
    if (!space)
        return ERROR;

    sprintf(destination[0], "+---------------+");
    sprintf(destination[1], "|%3s %6s  %3ld|", aux, ((aux_3 = character_get_description(game_get_character(game, space_get_character(space)))) != NULL ? aux_3 : "     "), space_id);
    for (i = 0; i < 5; i++)
    {
        sprintf(destination[i + 2], "|%6s      |", space_get_gdesc_line(space, i));
        destination[i + 2][19] = '\0';
    }
    n_objs_space = set_len(space_get_objects(space));
    set = set_get_content(space_get_objects(space));

    /*Looks how many strings it can print inside the 15 letters in the space given
    (18 -2 for the barriers, -1 for the extra space i'm placing)*/
    for (i = n_objs_space; cond == 0 && i != 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            cond = cond + 1 + strlen(object_get_name(game_get_object(game, set[j])));
        }

        if (cond > WIDTH_SPACE - 3)
        {
            cond = 0;
        }
    }
    for (j = 0; j <= i; j++)
    {
        aux_3 = object_get_name(game_get_object(game, set[j]));
        if (aux_2[0] != '\0')
        {
            strcpy(aux_4, aux_2);
            snprintf(aux_2, sizeof(aux_2), "%s%c%s", aux_4, ',', aux_3);
        }
        else
        {
            snprintf(aux_2, sizeof(aux_2), "%s", (aux_3 && n_objs_space ? aux_3 : " "));
        }
    }
    sprintf(destination[7], "|%-14s |", aux_2);
    destination[7][19] = '\0';
    sprintf(destination[8], "+---------------+");
    destination[8][19] = '\0';
    return OK;
}