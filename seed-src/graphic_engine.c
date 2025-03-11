/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Saul Lopez Romero && Fernando Mijangos
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*Space positions in array*/
/*This is like this so that later when printing its easier with a for*/
/* [0] [1] [2] */
/* [3] [4] [5] */
/* [6] [7] [8] */
typedef enum
{
    NORTH_WEST,
    NORTH,
    NORTH_EAST,
    WEST,
    ACTUAL_POSITION,
    EAST,
    SOUTH_WEST,
    SOUTH,
    SOUTH_EAST,
    NUM_IDS
}Positions;
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
Status graphic_engine_print_space(Game *game, Id space_id, char destination[HEIGHT_SPACE][WIDTH_SPACE]);

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
    Id id_aux = 0, *id_aux_2 = NULL;
    Character *character;
    Player *player;
    Space *space_act = NULL;
    char str[MAX_STRING_GE];
    char map[HEIGHT_MAP][WIDTH_MAP], aux_map[HEIGHT_SPACE][WIDTH_SPACE];
    int i = 0, j = 0, t = 0, v = 0;
    Id *id_list = NULL, actual_id[NUM_IDS];
    CommandCode last_cmd = UNKNOWN;
    extern char *cmd_to_str[N_CMD][N_CMDT];
    player = game_get_player(game);
    /* Paints the information in the map area.*/
    screen_area_clear(ge->map);
    if ((actual_id[ACTUAL_POSITION] = player_get_player_location(player)) != NO_ID)
    {
        /*Gets the spaces located to the different points of the space.*/
        space_act = game_get_space(game, actual_id[ACTUAL_POSITION]);
        actual_id[NORTH] = space_get_north(space_act);
        actual_id[SOUTH] = space_get_south(space_act);
        actual_id[WEST] = space_get_west(space_act);
        actual_id[EAST] = space_get_east(space_act);
        actual_id[NORTH_EAST] = NO_ID;
        actual_id[NORTH_WEST] = NO_ID;
        actual_id[SOUTH_EAST] = NO_ID;
        actual_id[SOUTH_WEST] = NO_ID;

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
                if (!(graphic_engine_print_space(game, actual_id[i * 3 + j], aux_map)))
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
        if (actual_id[NORTH] != NO_ID)
            map[HEIGHT_SPACE][WIDTH_SPACE * 3 / 2 + 1] = '^';
        if (actual_id[WEST] != NO_ID)
            map[HEIGHT_SPACE * 2 - 4][WIDTH_SPACE] = '<';
        if (actual_id[EAST] != NO_ID)
            map[HEIGHT_SPACE * 2 - 4][2 * WIDTH_SPACE + 2] = '>';
        if (actual_id[SOUTH] != NO_ID)
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
    sprintf(str, "  OBJECTS:");
    screen_area_puts(ge->descript, str);
    if (game_get_n_objects(game) >= 1)
    {
        /*Prints the objects.*/
        id_list = game_get_objects(game);
        for (i = 0; i < game_get_n_objects(game); i++)
        {
            if ((id_aux = game_get_object_location(game, id_list[i])) != -1)
            {
                sprintf(str, "   %-12s : %ld", object_get_name(game_get_object(game, id_list[i])), id_aux);
                screen_area_puts(ge->descript, str);
            }
        }
        free(id_list);
    }

    /*Prints the characters information*/
    screen_area_puts(ge->descript, " ");
    screen_area_puts(ge->descript, "  CHARACTERS");
    id_aux_2 = game_get_characters(game);
    for (i = 0; i < game_get_num_characters(game); i++)
    {
        character = game_get_character(game, id_aux_2[i]);
        sprintf(str, "   %-6s: %ld (%d)", character_get_description(character), game_get_character_location(game, character_get_id(character)), character_get_health(character));
        screen_area_puts(ge->descript, str);
    }
    screen_area_puts(ge->descript, " ");
    free(id_aux_2);

    /*Prints the player information*/
    sprintf(str, "   %-9s: %ld (%d)", "Player", player_get_player_location(player), player_get_health(player));
    screen_area_puts(ge->descript, str);
    if (player_get_object(player) != NO_ID)
    {
        id_aux = player_get_object(player);
        sprintf(str, "   Player_object: %s", object_get_name(game_get_object(game, id_aux)));
        screen_area_puts(ge->descript, str);
    }
    else
    {
        sprintf(str, "   Player has no objects");
        screen_area_puts(ge->descript, str);
    }

    /* Prints the Message.*/
    if (command_get_code(game_get_last_command(game)) == CHAT)
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
    i = command_get_status(game_get_last_command(game));
    sprintf(str, " -%-10s (%1s):%s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], (i == OK ? "OK" : "ERROR"));
    screen_area_puts(ge->feedback, str);

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

Status graphic_engine_print_space(Game *game, Id space_id, char destination[HEIGHT_SPACE][WIDTH_SPACE])
{
    char aux[4] = {"   "}, aux_2[WIDTH_SPACE - 2], *aux_3 = NULL, aux_4[WIDTH_SPACE - 3];
    Space *space;
    int i, j, n_objs_space, cond = 0;
    Id *set;

    /*Error handling.*/
    if (!game || space_id == NO_ID || space_id == ID_ERROR)
        return ERROR;
    /*Checks if the player is in the room.*/
    if (space_id == player_get_player_location(game_get_player(game)))
    {
        strcpy(aux, "m0\"");
    }

    /*Gets the actual space.*/
    space = game_get_space(game, space_id);
    if (!space)
        return ERROR;

    /*Starts printing the space.*/
    sprintf(destination[0], "+---------------+");
    sprintf(destination[1], "|%3s %6s  %3ld|", aux, ((aux_3 = character_get_description(game_get_character(game, space_get_character(space)))) != NULL ? aux_3 : ""), space_id);
    for (i = 0; i < 5; i++)
    {
        sprintf(destination[i + 2], "|%s      |", space_get_gdesc_line(space, i));
    }
    /*Once the space is printed, shows the objects on screen.*/
    n_objs_space = space_get_n_objects(space);
    set = (space_get_objects(space));
    if (set)
    {
        /*Looks how many strings it can print inside the 15 letters in the space given
        (Width_space -2 for the barriers, -1 for the extra space i'm placing)*/
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
        aux_2[0] = '\0';
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
        free(set);
    }
    else
    {
        aux_2[0] = '\0';
    }

    /*Finishes printing the spaces.*/
    sprintf(destination[7], "|%-14s |", aux_2);
    sprintf(destination[8], "+---------------+");
    return OK;
}