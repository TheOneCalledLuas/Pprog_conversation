/**
 * @brief It loads and makes all the actions related to space management.
 *
 * @file game_reader.c
 * @author Saúl López Romero
 * @version 1
 * @date 30-01-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_reader_load_spaces(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
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
/*If DEBUG mode is active (defined) prints what it has read.*/
#ifdef DEBUG
            printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
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

Status game_reader_add_object(Game *game, Object *object)
{
    /*Checks the arguments.*/
    if (!game || !object || game->n_objects > MAX_OBJECTS)
    {
        return ERROR;
    }

    /*Adds the object.*/
    game->objects[game->n_objects] = object;
    game->n_objects++;

    /*Clean exit.*/
    return OK;
}

Status game_reader_load_objects(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    Id id = NO_ID;
    Id id_space = NO_ID;
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
        /*Checks that the line contains a room.*/
        if (strncmp("#o:", line, 3) == 0)
        {
            /*Takes the information data by data.*/
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            id_space = atol(toks);

            /*Creates an object and saves the data.*/
            object = object_create(id);
            /*Checks that the memory allocacion took place.*/
            if (!object)
            {
                return ERROR;
            }
            object_set_name(object, name);
            object_set_space_id_at(object, id_space);
            game_reader_add_object(game, object);

            /*Adds the object to its location*/
            if (id_space != NO_ID) {
                game_set_object_location(game,id_space);
            }
        }
    }
    /*Close the file.*/
    fclose(file);

    /*Clean exit.*/
    return OK;
}
