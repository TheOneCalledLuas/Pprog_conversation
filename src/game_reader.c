/**
 * @brief It loads and makes all the actions related to space management.
 *
 * @file game_reader.c
 * @author Saúl López Romero, Raquel Anguita Martínez de Velasco
 * @version 3
 * @date 30-01-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"
#include "game.h"
#include "link.h"
#include "gamerules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Maximun size of a description line.
 */
#define DESC_SIZE 9
#define DESC_LINES 5        /*!< Max description lines. */
#define DESC_LENGTH 10      /*!< Max description length. */
#define IDENTIFIER_LENGTH 3 /*!< Number of characters the identifier occupies in the data file. */

Status game_reader_load_spaces(Game *game, char *filename)
{
    FILE *file = NULL;
    int i = 0;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    char desc[DESC_LINES][DESC_LENGTH];
    Id id = NO_ID;
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
        if (strncmp("#s:", line, IDENTIFIER_LENGTH) == 0)
        {
            /*Takes the information data by data and saves it.*/
            toks = strtok(line + IDENTIFIER_LENGTH, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            /*Takes the graphic description.*/
            for (i = 0; i < DESC_LINES; i++)
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
            printf("Leido: %ld|%s|\n", id, name);
            for (i = 0; i < DESC_LINES; i++)
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
                game_add_space(game, space);
                for (i = 0; i < DESC_LINES; i++)
                {
                    space_set_gdesc_line(space, i, desc[i]);
                }
#ifdef DEBUG
                for (i = 0; i < DESC_LINES; i++)
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
    char desc[WORD_SIZE] = "";
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
        if (strncmp("#o:", line, IDENTIFIER_LENGTH) == 0)
        {
            /*Takes the information data by data.*/
            toks = strtok(line + IDENTIFIER_LENGTH, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            space_id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(desc, toks);

            /*Creates an object and saves the data.*/
            object = object_create(id);
            /*Checks that the memory allocacion took place.*/
            if (!object)
            {
                fclose(file);
                return ERROR;
            }
            object_set_name(object, name);
            object_set_description(object, desc);
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

Status game_reader_load_characters(Game *game, char *name_file)
{
    FILE *file = NULL;
    Character *character;
    Id id = NO_ID, id_sp = NO_ID;
    Bool friendly = FALSE;
    int health = 0;
    char data[WORD_SIZE] = "";
    char *toks = NULL;

    /*Opens the file.*/
    if (!name_file || !(file = fopen(name_file, "r")) || !game)
    {
        return ERROR;
    }

    while (fgets(data, WORD_SIZE, file))
    {
        if (strncmp("#c:", data, IDENTIFIER_LENGTH) == 0)
        {
            /*Gets the id of the character and creates it.*/
            toks = strtok(data + IDENTIFIER_LENGTH, "|");
            id = atol(toks);
            if (!(character = character_create(id)))
            {
                return ERROR;
                fclose(file);
            }
            toks = strtok(NULL, "|");

            /*Gets the name of the character and sets it.*/
            if ((character_set_name(character, toks)) == ERROR)
            {
                return ERROR;
                fclose(file);
            }

            /*Gets the description of the character and sets it.*/
            toks = strtok(NULL, "|");
            if ((character_set_description(character, toks)) == ERROR)
            {
                return ERROR;
                fclose(file);
            }

            /*Gets the space where the character is at and sets it there.*/
            toks = strtok(NULL, "|");
            id_sp = atol(toks);
            if ((space_add_character(game_get_space(game, id_sp), id)) == ERROR)
            {                return ERROR;
                fclose(file);}

            /*Gets the amount of health of the character and sets it.*/
            toks = strtok(NULL, "|");
            health = atoi(toks);
            if ((character_set_health(character, health)) == ERROR)
            {
                return ERROR;
                fclose(file);
            }

            /*Gets the status of friendly for that character and sets it.*/
            toks = strtok(NULL, "|");
            friendly = atoi(toks);
            if ((character_set_friendly(character, friendly)) == ERROR)
            {
                return ERROR;
                fclose(file);
            }

            /*Gets the message of the player and sets it.*/
            toks = strtok(NULL, "|");
            if ((character_set_message(character, toks)) == ERROR)
            {
                return ERROR;
                fclose(file);
            }

            game_add_character(game, character);
        }
    }
    fclose(file);
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
    int player_inventory = 0, player_health = 0;

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
        if (strncmp("#p:", line, IDENTIFIER_LENGTH) == 0)
        {
            /*Takes the information data by data.*/
            toks = strtok(line + IDENTIFIER_LENGTH, "|");
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
            player_set_inventory_capacity(player, player_inventory);
            /*Adds the player to the space.*/
            game_add_player(game, player);
        }
    }
    /*Close the file.*/
    fclose(f);

    /*Clean exit.*/
    return OK;
}

Status game_reader_load_links(Game *game, char *filename)
{
    FILE *f = NULL;
    Link *link = NULL;
    char name[WORD_SIZE];
    char line[WORD_SIZE];
    Id dest_id = 0, origin_id = 0, id = 0;
    char *toks = NULL;
    Direction direction;
    Bool state;

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
        if (strncmp("#l:", line, IDENTIFIER_LENGTH) == 0)
        {
            /*Takes the information data by data.*/
            toks = strtok(line + IDENTIFIER_LENGTH, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            origin_id = atol(toks);
            toks = strtok(NULL, "|");
            dest_id = atol(toks);
            toks = strtok(NULL, "|");
            direction = atol(toks);
            toks = strtok(NULL, "|");
            state = atol(toks);

            /*Creates an object and saves the data.*/
            link = link_create(id);
            /*Checks that the memory allocacion took place.*/
            if (!link)
            {
                return ERROR;
            }
            link_set_name(link, name);
            link_set_origin(link, origin_id);
            link_set_destination(link, dest_id);
            link_set_direction(link, direction);
            link_set_state(link, state);
            /*Adds the player to the space.*/
            game_add_link(game, link);
        }
    }
    /*Close the file.*/
    fclose(f);

    /*Clean exit.*/
    return OK;
}

Status game_reader_load_gamerules(Game *game, char *filename)
{
    FILE *f = NULL;
    Gamerule *gr = NULL;
    char name[WORD_SIZE];
    char line[WORD_SIZE];
    Id id = 0;
    char *toks = NULL;
    int value = 0;
    Bool is_valid = 0, do_once = 0;

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
        if (strncmp("#g:", line, IDENTIFIER_LENGTH) == 0)
        {
            /*Takes the information data by data.*/
            toks = strtok(line + IDENTIFIER_LENGTH, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            is_valid = atol(toks);
            toks = strtok(NULL, "|");
            do_once = atol(toks);
            toks = strtok(NULL, "|");
            value = atol(toks);

            /*Creates an object and saves the data.*/
            gr = gamerules_gamerule_create(id);
            /*Checks that the memory allocacion took place.*/
            if (!gr)
            {
                return ERROR;
            }
            gamerules_set_name(gr, name);
            gamerules_set_valid(gr, is_valid);
            gamerules_set_do_once(gr, do_once);
            gamerules_set_value(gr, value);
            
            /*Assigns the gamerule func to the structure.*/
            switch (id)
            {
            case 20:
                gamerules_gamerule_set_func(gr, gamerules_open_gate);
                break;

            default:
                break;
            }
            /*Adds the gamerule to the game.*/
            gamerules_values_add(game_get_game_values(game), gr);
        }
    }
    /*Close the file.*/
    fclose(f);

    /*Clean exit.*/
    return OK;
}
