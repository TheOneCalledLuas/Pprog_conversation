/**
 * @brief It loads and makes all the actions related to space management.
 *
 * @file game_reader.c
 * @author Saúl López Romero
 * @version 3
 * @date 30-01-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DESC_SIZE 9

Status game_reader_load_spaces(Game *game, char *filename)
{
    FILE *file = NULL;
    int i = 0;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    char desc[5][10];
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
    Space *space = NULL;
    Status status = OK;

    /*Checks the pointers.*/
    if (!filename || !game)
    {
        return ERROR;
    }

    /*Opens the file.*/
    file = fopen(filename, "r");
    if (file == NULL)
    {
        return ERROR;
    }

    /*Gets the data line by line.*/
    while (fgets(line, WORD_SIZE, file))
    {
        /*Checks that the line contains a room.*/
        if (strncmp("#s:", line, 3) == 0)
        {
            /*Takes the information data by data and saves it.*/
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            north = atol(toks);
            toks = strtok(NULL, "|");
            east = atol(toks);
            toks = strtok(NULL, "|");
            south = atol(toks);
            toks = strtok(NULL, "|");
            west = atol(toks);
            /*Takes the graphic description.*/
            for (i = 0; i < 5; i++)
            {
                toks = strtok(NULL, "|");

                /*Error handling.*/
                if (!toks || strlen(toks) != DESC_SIZE)
                {
                    strcpy(desc[i], "         "); /*9 spaces.*/
                }
                else
                    strcpy(desc[i], toks);
            }
/*If DEBUG mode is active (defined) prints what it has read.*/
#ifdef DEBUG
            printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
            for (i = 0; i < 5; i++)
            {
                printf("%s|", desc[i]);
            }
            printf("\n");
            sleep(1);
#endif
            /*Creates a new space and fills it with the information gathered.*/
            space = space_create(id);
            if (space != NULL)
            {
                space_set_name(space, name);
                space_set_north(space, north);
                space_set_east(space, east);
                space_set_south(space, south);
                space_set_west(space, west);
                game_add_space(game, space);
                for (i = 0; i < 5; i++)
                {
                    space_set_gdesc_line(space, i, desc[i]);
                }
#ifdef DEBUG
                for (i = 0; i < 5; i++)
                {
                    printf("%s|", space_get_gdesc_line(space, i));
                }
                printf("\n");
                sleep(1);
#endif
            }
            else
            {
                return ERROR;
            }
        }
    }
    /*If something went wrong while reading the file.*/
    if (ferror(file))
    {
        status = ERROR;
    }
    /*Closes the file.*/
    fclose(file);

    /*Clean exit.*/
    return status;
}

Status game_reader_load_objects(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    Id id = NO_ID, space_id = NO_ID;
    Object *object = NULL;
    char *toks = NULL;

    /*Checks the arguments.*/
    if (!game || !filename)
    {
        return ERROR;
    }

    /*Opens the file.*/
    if (!(file = fopen(filename, "r")))
    {
        return ERROR;
    }

    /*Gets the data line by line.*/
    while (fgets(line, WORD_SIZE, file))
    {
        /*Checks that the line contains an object.*/
        if (strncmp("#o:", line, 3) == 0)
        {
            /*Takes the information data by data.*/
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            space_id = atol(toks);

            /*Creates an object and saves the data.*/
            object = object_create(id);
            /*Checks that the memory allocacion took place.*/
            if (!object)
            {
                return ERROR;
            }
            object_set_name(object, name);
            game_add_object(game, object);

            /*Places the object in its initial place.*/
            if (space_id != -1)
            {
                space_add_object(game_get_space(game, space_id), id);
            }
        }
    }
    /*Close the file.*/
    fclose(file);

    /*Clean exit.*/
    return OK;
}

Status game_reader_load_players(Game *game, char *filename)
{
    FILE *f = NULL;
    Player *player = NULL;
    char name[WORD_SIZE];
    char gdesc[WORD_SIZE];
    char line[WORD_SIZE];
    Id player_id = 0, space_id = 0;
    char *toks = NULL;
    int player_inventory = 0, player_health = 0; /*"Gives a warning untill someone programs the inventory..."Saul, "When will the inventory be programmed :( "Fernando */

    /*Error handling.*/
    if (!game || !filename)
        return ERROR;

    /*Opens the file.*/
    if (!(f = fopen(filename, "r")))
        return ERROR;

    /*Gets the data line by line.*/
    while (fgets(line, WORD_SIZE, f))
    {
        /*Checks that the line contains a player.*/
        if (strncmp("#p:", line, 3) == 0)
        {
            /*Takes the information data by data.*/
            toks = strtok(line + 3, "|");
            player_id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            strcpy(gdesc, toks);
            toks = strtok(NULL, "|");
            space_id = atol(toks);
            toks = strtok(NULL, "|");
            player_health = atol(toks);
            toks = strtok(NULL, "|");
            player_inventory = atol(toks);

            /*Creates an object and saves the data.*/
            player = player_create(player_id);
            /*Checks that the memory allocacion took place.*/
            if (!player)
            {
                return ERROR;
            }
            player_set_player_name(player, name);
            player_set_player_location(player, space_id);
            player_set_gdesc(player, gdesc);
            player_set_health(player, player_health);
            /*Adds the player to the space.*/
            game_add_player(game, player);
        }
    }
    /*Close the file.*/
    fclose(f);

    /*Clean exit.*/
    return OK;
}