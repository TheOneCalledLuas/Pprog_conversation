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
#include "animation.h"

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
    FILE *textures = NULL;
    int i = 0;
    char texture_file[WORD_SIZE] = "";
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    char desc[DESC_LINES][DESC_LENGTH];
    char aux[WORD_SIZE] = "";
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
        printf("Error opening the file inside space reader.\n");
        return ERROR;
    }
    /*Searches for the texture file name*/
    status = ERROR;
    while (fgets(line, WORD_SIZE, file) && status == ERROR)
    {
        if (strncmp("#t:", line, IDENTIFIER_LENGTH) == 0)
        {
            status = OK;
            for (i = 3; i < strlen(line) - 2; i++)
            {
                texture_file[i - 3] = line[i];
            }
        }
    }
    if (status == ERROR)
    {
        fclose(file);
        return ERROR;
    }
    /*Opens the texture file.*/
    textures = fopen(texture_file, "r");
    if (textures == NULL)
    {
        fclose(file);
        printf("Error opening the texture file inside space reader.\n");
        return ERROR;
    }
    /*Starts reading the information file from the beggining again.*/
    rewind(file);

    /*Gets the data line by line.*/
    while (fgets(line, WORD_SIZE, file))
    {
        rewind(textures);
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
                /*Looks for the correct texture*/
                sprintf(aux, "#s:%ld", id);
                status = ERROR;
                while (fgets(line, WORD_SIZE, textures) && status == ERROR)
                {
                    if (strncmp(aux, line, strlen(aux)) == 0)
                    {
                        status = OK;
                        /*Sets the texture.*/
                        for (i = 0; i < SPACE_TEXTURE_LINES; i++)
                        {
                            fgets(line, WORD_SIZE, textures);
                            line[SPACE_TEXTURE_SIZE - 1] = '\0';
                            space_set_texture_line(space, i, line);
                        }
                    }
                }
                if (status == ERROR)
                {
                    for (i = 0; i < SPACE_TEXTURE_LINES; i++)
                    {
                        space_set_texture_line(space, i, "  ");
                    }
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
                fclose(file);
                fclose(textures);
                printf("Error reading the file spaces.\n");
                return ERROR;
            }
        }
    }
    status = OK;
    /*If something went wrong while reading the file.*/
    if (ferror(file))
    {
        printf("Error reading the file spaces.\n");
        status = ERROR;
    }
    /*Closes the file.*/
    fclose(textures);
    fclose(file);
    /*Clean exit.*/
    return status;
}

Status game_reader_load_objects(Game *game, char *filename)
{
    FILE *file = NULL;
    FILE *textures = NULL;
    int i = 0;
    char texture_file[WORD_SIZE] = "";
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char desc[WORD_SIZE] = "";
    Id id = NO_ID, space_id = NO_ID;
    Status status = OK;
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
    /*Searches for the name of the textures*/
    status = ERROR;
    while (status == ERROR && fgets(line, WORD_SIZE, file))
    {
        if (strncmp("#t:", line, IDENTIFIER_LENGTH) == 0)
        {
            status = OK;
            for (i = 3; i < strlen(line) - 2; i++)
            {
                texture_file[i - 3] = line[i];
            }
        }
    }
    texture_file[i - 3] = '\0';
    if (status == ERROR)
    {
        fclose(file);
        return ERROR;
    }
    /*Opens the texture file.*/
    if (!(textures = fopen(texture_file, "r")))
    {
        fclose(file);
        return ERROR;
    }
    /*Starts reading the information file from the beggining again.*/
    rewind(file);

    /*Gets the data line by line.*/
    while (fgets(line, WORD_SIZE, file))
    {
        rewind(textures);
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
            /*Looks for the correct texture*/
            status = ERROR;
            sprintf(name, "#o:%ld", id);
            while (status == ERROR && fgets(line, WORD_SIZE, textures))
            {
                if (strncmp(name, line, strlen(name)) == 0)
                {
                    status = OK;
                    /*Sets the texture.*/
                    for (i = 0; i < OBJECT_TEXTURE_LINES; i++)
                    {
                        fgets(line, WORD_SIZE, textures);
                        line[OBJECT_TEXTURE_SIZE - 1] = '\0';
                        object_set_texture_line(object, i, line);
                    }
                }
            }
            if (status == ERROR)
            {
                for (i = 0; i < OBJECT_TEXTURE_LINES; i++)
                {
                    object_set_texture_line(object, i, "  ");
                }
            }
            /*Places the object in its initial place.*/
            if (space_id != -1)
            {
                space_add_object(game_get_space(game, space_id), id);
            }
        }
    }
    status = OK;
    /*Close the file.*/
    if (ferror(file))
    {
        printf("Error reading the file spaces.\n");
        status = ERROR;
    }
    fclose(file);
    fclose(textures);
    /*Clean exit.*/
    return OK;
}

Status game_reader_load_characters(Game *game, char *name_file)
{
    FILE *file = NULL;
    FILE *textures = NULL;
    int i = 0;
    Status status = OK;
    char texture_file[WORD_SIZE] = "";
    Character *character;
    Id id = NO_ID, id_sp = NO_ID;
    Bool friendly = FALSE;
    int health = 0;
    char data[WORD_SIZE] = "";
    char aux[WORD_SIZE] = "";
    char *toks = NULL;

    /*Opens the file.*/
    if (!name_file || !(file = fopen(name_file, "r")) || !game)
    {
        return ERROR;
    }

    /*Gets the name of the texture file*/
    status = ERROR;
    while (fgets(data, WORD_SIZE, file) && status == ERROR)
    {
        if (strncmp("#t:", data, IDENTIFIER_LENGTH) == 0)
        {
            status = OK;
            /*Its up to that -2 to remove the \n and \r that appear*/
            for (i = 3; i < strlen(data) - 2; i++)
            {
                texture_file[i - 3] = data[i];
            }
        }
    }
    texture_file[i] = '\0';
    if (status == ERROR)
    {
        fclose(file);
        return ERROR;
    }
    /*Opens the texture file*/
    if (!(textures = fopen(texture_file, "r")))
    {
        fclose(file);
        return ERROR;
    }
    /*Rewinds the previous file to the top*/
    rewind(file);

    /*Reads the rest of the file*/
    while (fgets(data, WORD_SIZE, file))
    {
        if (strncmp("#c:", data, IDENTIFIER_LENGTH) == 0)
        {
            /*Rewinds the texture file*/
            rewind(textures);
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
            {
                return ERROR;
                fclose(file);
            }

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
            /*Searches for the correct texture to save it*/
            status = ERROR;
            sprintf(aux, "#c:%ld", id);
            while (fgets(data, WORD_SIZE, textures) && status == ERROR)
            {
                if (strncmp(aux, data, strlen(aux)) == 0)
                {
                    status = OK;
                    for (i = 0; i < CHARACTER_TEXTURE_LINES; i++)
                    {
                        fgets(data, WORD_SIZE, textures);
                        data[CHARACTER_TEXTURE_SIZE - 1] = '\0';
                        character_set_texture_line(character, i, data);
                    }
                }
            }
            /*If it didnt find it, fill with spaces.*/
            if (status == ERROR)
            {
                for (i = 0; i < CHARACTER_TEXTURE_LINES; i++)
                {
                    character_set_texture_line(character, i, "  ");
                }
            }
            game_add_character(game, character);
        }
    }
    fclose(textures);
    fclose(file);
    return OK;
}

Status game_reader_load_players(Game *game, char *filename)
{
    FILE *f = NULL;
    FILE *textures = NULL;
    char texture_file[WORD_SIZE] = "";
    Status status = ERROR;
    Player *player = NULL;
    char name[WORD_SIZE];
    char gdesc[WORD_SIZE];
    char line[WORD_SIZE];
    Id player_id = 0, space_id = 0;
    char *toks = NULL;
    int player_inventory = 0, player_health = 0, i = 0;

    /*Error handling.*/
    if (!game || !filename)
        return ERROR;

    /*Opens the file.*/
    if (!(f = fopen(filename, "r")))
        return ERROR;

    /*Searches for the texture file.*/
    status = ERROR;
    while (fgets(line, WORD_SIZE, f))
    {
        if (strncmp("#t:", line, IDENTIFIER_LENGTH) == 0)
        {
            status = OK;
            /*Its up to that -2 to remove the \n and \r that appear*/
            for (i = 3; i < strlen(line) - 2; i++)
            {
                texture_file[i - 3] = line[i];
            }
            texture_file[i] = '\0';
        }
    }
    /*If it didnt find the texture file, return ERROR*/
    if (status == ERROR)
    {
        printf("Couldn't find the texture file in object game reader\n");
        fclose(f);
        return ERROR;
    }
    /*Opens the texture file.*/
    if (!(textures = fopen(texture_file, "r")))
    {
        fclose(f);
        return ERROR;
    }
    /*Rewinds the file*/
    rewind(f);
    /*Gets the data line by line.*/
    while (fgets(line, WORD_SIZE, f))
    {
        /*Checks that the line contains a player.*/
        if (strncmp("#p:", line, IDENTIFIER_LENGTH) == 0)
        {
            /*Rewinds the texture file*/
            rewind(textures);
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
            /*Searches for the player texture.*/
            status = ERROR;
            sprintf(name, "#p:%ld", player_id);
            while (fgets(line, WORD_SIZE, textures) && status == ERROR)
            {
                if (strncmp(name, line, strlen(name)) == 0)
                {
                    status = OK;
                    for (i = 0; i < PLAYER_TEXTURE_LINES; i++)
                    {
                        fgets(line, WORD_SIZE, textures);
                        line[PLAYER_TEXTURE_SIZE - 1] = '\0';
                        player_set_texture_line(player, i, line);
                    }
                }
            }
            /*If it didnt find the texture fills it with spaces.*/
            if (status == ERROR)
            {
                for (i = 0; i < PLAYER_TEXTURE_LINES; i++)
                {
                    player_set_texture_line(player, i, " ");
                }
            }
            /*Adds the player to the space.*/
            game_add_player(game, player);
        }
    }
    /*Close the file.*/
    fclose(textures);
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
    int value = 0, has_exec = 0;
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
            has_exec = atol(toks);
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
            gamerules_set_n_exec_times(gr, has_exec);

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

Status game_reader_load_animations(Game *game, char *filename)
{
    FILE *f = NULL;
    Animation *an = NULL;
    char name[WORD_SIZE],path[WORD_SIZE];
    char line[WORD_SIZE];
    Id id = 0;
    char *toks = NULL;
    int widht, height, frames, widht_padding, height_padding,background_color,font_color;
    float refresh_rate = 0.0;

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
            strcpy(path, toks);
            toks = strtok(NULL, "|");
            widht = atol(toks);
            toks = strtok(NULL, "|");
            height = atol(toks);
            toks = strtok(NULL, "|");
            frames = atol(toks);
            toks = strtok(NULL, "|");
            refresh_rate = (float)atof(toks);
            toks = strtok(NULL, "|");
            widht_padding = atol(toks);
            toks = strtok(NULL, "|");
            height_padding = atol(toks);
            toks = strtok(NULL, "|");
            background_color = atol(toks);
            toks = strtok(NULL, "|");
            font_color = atol(toks);

            /*Creates an object and saves the data.*/
            an = animation_init(id,path);
            /*Checks that the memory allocacion took place.*/
            if (!an)
            {
                return ERROR;
            }

            /*Sets the values.*/
            animation_set_name(an, name);
            animation_set_width(an, widht);
            animation_set_height(an, height);
            animation_set_n_images(an, frames);
            animation_set_refresh_rate(an, refresh_rate);
            animation_set_side_padding(an, widht_padding);
            animation_set_height_padding(an, height_padding);
            animation_set_background_color(an, background_color);
            animation_set_font_color(an, font_color);

            /*Adds the animation to the game.*/
            animation_manager_add_animation(game_get_animation_manager(game), an);
        }
    }
    /*Close the file.*/
    fclose(f);

    /*Clean exit.*/
    return OK;
}