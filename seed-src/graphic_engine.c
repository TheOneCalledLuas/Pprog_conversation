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

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "set.h"
#include "types.h"

/*Map measures.*/
#define WIDTH_MAP 55
#define WIDTH_DES 30
#define WIDTH_BAN 23
#define HEIGHT_MAP 26
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3
#define MAX_STRING_GE 255

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
    Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_space = 0, id_left = NO_ID, id_right = NO_ID, id_left_up = NO_ID, id_left_down = NO_ID, id_right_up = NO_ID, id_right_down = NO_ID;
    Space *space_act = NULL;
    char obj = '\0';
    char str[MAX_STRING_GE];
    char spaces[] = {"                 "};
    int i = 0;
    Id *id_list = NULL;
    CommandCode last_cmd = UNKNOWN;
    extern char *cmd_to_str[N_CMD][N_CMDT];

    /* Paints the information in the map area.*/
    screen_area_clear(ge->map);
    if ((id_act = player_get_player_location(game_get_player(game))) != NO_ID)
    {
        /*Gets the spaces located to the different points of the space.*/
        space_act = game_get_space(game, id_act);
        id_back = space_get_north(space_act);
        id_next = space_get_south(space_act);
        id_left = space_get_west(space_act);
        id_right = space_get_east(space_act);

        /*Gets the spaces situated on the corners*/
        if ((id_left_up = space_get_north(game_get_space(game, id_left))) == ID_ERROR)
        {
            if ((id_left_up = space_get_west(game_get_space(game, id_back))) == ID_ERROR)
            {
                id_left_up = NO_ID;
            }
        }
        if ((id_left_down = space_get_south(game_get_space(game, id_left))) == ID_ERROR)
        {
            if ((id_left_down = space_get_west(game_get_space(game, id_next))) == ID_ERROR)
            {
                id_left_down = NO_ID;
            }
        }
        if ((id_right_up = space_get_north(game_get_space(game, id_right))) == ID_ERROR)
        {
            if ((id_right_up = space_get_east(game_get_space(game, id_back))) == ID_ERROR)
            {
                id_right_up = NO_ID;
            }
        }
        if ((id_right_down = space_get_south(game_get_space(game, id_right))) == ID_ERROR)
        {
            if ((id_right_down = space_get_east(game_get_space(game, id_next))) == ID_ERROR)
            {
                id_right_down = NO_ID;
            }
        }

        /*The following 50 lines print the rooms.*/

        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "+---------------+" : spaces), (id_back != NO_ID ? "+---------------+" : spaces), (id_right_up != NO_ID ? "+---------------+" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "|            %3d|" : spaces), (id_back != NO_ID ? "|            %3d|" : spaces), (id_right_up != NO_ID ? "|            %3d|" : spaces));
        sprintf(str, str, (id_left_up != NO_ID ? id_left_up : (id_back ? id_back : id_right_up)), (id_left_up != NO_ID ? (id_back ? id_back : id_right_up) : (id_back ? id_right_up : -1)), id_right_up);
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "|               |" : spaces), (id_back != NO_ID ? "|               |" : spaces), (id_right_up != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "|               |" : spaces), (id_back != NO_ID ? "|               |" : spaces), (id_right_up != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "|               |" : spaces), (id_back != NO_ID ? "|               |" : spaces), (id_right_up != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "|               |" : spaces), (id_back != NO_ID ? "|               |" : spaces), (id_right_up != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "|               |" : spaces), (id_back != NO_ID ? "|               |" : spaces), (id_right_up != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_up != NO_ID ? "+---------------+" : spaces), (id_back != NO_ID ? "+---------------+" : spaces), (id_right_up != NO_ID ? "+---------------+" : spaces));
        screen_area_puts(ge->map, str);

        if (set_len(space_get_objects(game_get_space(game, id_act))) != 0)
            obj = '*';
        else
            obj = ' ';
        sprintf(str, "%s %s %s", (id_left!=NO_ID? (id_left_up!=NO_ID? "         ^       ": "                 "): "                 "),(id_back!=NO_ID? "         ^       ": "                 "),(id_right!=NO_ID? (id_right_up!=NO_ID? "         ^       ": "                 "): "                 "));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left != NO_ID ? "+---------------+" : spaces), (id_act != NO_ID ? "+---------------+" : spaces), (id_right != NO_ID ? "+---------------+" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left != NO_ID ? "|            %3d|" : spaces), (id_act != NO_ID ? "|            %3d|" : spaces), (id_right != NO_ID ? "|            %3d|" : spaces));
        sprintf(str, str, (id_left != NO_ID ? id_left : (id_act ? id_act : id_right_down)), (id_left != NO_ID ? (id_act ? id_act : id_right) : (id_act ? id_right : -1)), id_right);
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left != NO_ID ? "|               |" : spaces), (id_act != NO_ID ? "|     m0\"       |" : spaces), (id_right != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%19s%s%19s", (id_left != NO_ID ? "|               | <" : spaces), (id_act != NO_ID ? "|               |" : spaces), (id_right != NO_ID ? ">|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left != NO_ID ? "|               |" : spaces), (id_act != NO_ID ? "|               |" : spaces), (id_right != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left != NO_ID ? "|               |" : spaces), (id_act != NO_ID ? "|               |" : spaces), (id_right != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left != NO_ID ? "|               |" : spaces), (id_act != NO_ID ? "|               |" : spaces), (id_right != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left != NO_ID ? "+---------------+" : spaces), (id_act != NO_ID ? "+---------------+" : spaces), (id_right != NO_ID ? "+---------------+" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s %s %s", (id_left!=NO_ID? (id_left_down!=NO_ID? "         v       ": "                 "): "                 "),(id_next!=NO_ID? "         v       ": "                 "),(id_right!=NO_ID? (id_right_down!=NO_ID? "         v       ": "                 "): "                 "));
        screen_area_puts(ge->map, str);




        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "+---------------+" : spaces), (id_next != NO_ID ? "+---------------+" : spaces), (id_right_down != NO_ID ? "+---------------+" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "|            %3d|" : spaces), (id_next != NO_ID ? "|            %3d|" : spaces), (id_right_down != NO_ID ? "|            %3d|" : spaces));
        sprintf(str, str, (id_left_down != NO_ID ? id_left_down : (id_next ? id_next : id_right_down)), (id_left_down != NO_ID ? (id_next ? id_next : id_right_down) : (id_next ? id_right_down : -1)), id_right_down);
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "|               |" : spaces), (id_next != NO_ID ? "|               |" : spaces), (id_right_down != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "|               |" : spaces), (id_next != NO_ID ? "|               |" : spaces), (id_right_down != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "|               |" : spaces), (id_next != NO_ID ? "|               |" : spaces), (id_right_down != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "|               |" : spaces), (id_next != NO_ID ? "|               |" : spaces), (id_right_down != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "|               |" : spaces), (id_next != NO_ID ? "|               |" : spaces), (id_right_down != NO_ID ? "|               |" : spaces));
        screen_area_puts(ge->map, str);
        sprintf(str, "%s  %s  %s", (id_left_down != NO_ID ? "+---------------+" : spaces), (id_next != NO_ID ? "+---------------+" : spaces), (id_right_down != NO_ID ? "+---------------+" : spaces));
        screen_area_puts(ge->map, str);
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
        if (space_get_character(game_get_space(game, id_act)) != NO_ID && character_get_friendly(game_get_character(game, space_get_character(game_get_space(game, id_act)))) == TRUE)
        {
            sprintf(str, "  Message: %s", character_get_message(game_get_character(game, space_get_character(game_get_space(game, id_act)))));
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
