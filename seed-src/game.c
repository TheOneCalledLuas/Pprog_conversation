/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Saul Lopez Romero, Fernando Mijangos Varas
 * @version 3
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "character.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARACTER_ID_1 3
#define CHARACTER_HEALTH_1 5
#define CHARACTER_NAME_1 "Litle Ant"
#define CHARACTER_MSG_1 "I'm a litle ant."
#define CHARACTER_DESCR_1 "mO^"
#define SPACE_C1 121
#define CHARACTER_ID_2 4
#define CHARACTER_HEALTH_2 5
#define CHARACTER_NAME_2 "Spider"
#define CHARACTER_MSG_2 "\0"
#define CHARACTER_DESCR_2 "/\\oo/\\"
#define SPACE_C2 123

/**
   Game interface implementation.
*/
struct _Game
{
    Player *player;                        /*!< Pointer to the player. */
    Space *spaces[MAX_SPACES];             /*!< An array with the information of every space. */
    Object *objects[MAX_OBJECTS];          /*!< An array with the information of every objects.*/
    Character *characters[MAX_CHARACTERS]; /*!< Array with all the character of the game.*/
    int n_spaces;                          /*!< Number of spaces.*/
    int n_objects;                         /*!< Number of objects.*/
    int n_characters;                      /*< Number of characters.*/
    Command *last_cmd;                     /*!< A pointer to the last command entered by the user.*/
    Bool finished;                         /*!< Whether the game has finished or not.*/
};

Status game_create(Game **game)
{
    int i;

    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
    }
    /*Memory allocation.*/
    (*game) = (Game *)malloc(sizeof(Game));

    for (i = 0; i < MAX_SPACES; i++)
    {
        (*game)->spaces[i] = NULL;
    }
    /*Initializes all members of the game structure.*/
    (*game)->n_spaces = 0;
    (*game)->n_objects = 0;
    (*game)->n_characters = 0;
    (*game)->player = player_create(5);
    (*game)->last_cmd = command_create();
    (*game)->finished = FALSE;

    return OK;
}

Character **game_get_array_characters(Game *game)
{
    return (game ? game->characters : NULL);
}

Character *game_get_character(Game *game, Id id)
{
    int i = 0;
    /*Error handling.*/
    if (!game || id == -1)
        return NULL;

    /*Searches for the id.*/
    for (i = 0; i < game->n_objects; i++)
    {
        if (character_get_id(game->characters[i]) == id)
        {
            return game->characters[i];
        }
    }

    /*The id wasn't found.*/
    return NULL;
}

Status game_add_character(Game *game, Character *character)
{
    /*Error handling.*/
    if (!game || !character || game->n_characters == MAX_CHARACTERS)
    {
        return ERROR;
    }

    /*Adds tthe character.*/
    game->characters[game->n_characters++] = character;

    /*CLeean exit.*/
    return OK;
}

int game_get_num_characters(Game *game)
{
    /*Error handling.*/
    if (!game)
        return -1;

    /*Returns the value.*/
    return game->n_characters;
}

Space *game_get_space(Game *game, Id id)
{
    int i = 0;

    /*Checks the pointer.*/
    if (!game)
    {
        return NULL;
    }

    /*Validates the id.*/
    if (id == NO_ID || id == ID_ERROR)
    {
        return NULL;
    }

    /*Searchs for the space.*/
    for (i = 0; i < game->n_spaces; i++)
    {
        if (id == space_get_id(game->spaces[i]))
        {
            /*Returns the space when found.*/
            return game->spaces[i];
        }
    }
    /*The space wasn't found.*/
    return NULL;
}

Status game_add_space(Game *game, Space *space)
{
    /*Checks the pointers.*/
    if ((space == NULL) || (!game) || (!space) || (game->n_spaces >= MAX_SPACES))
    {
        return ERROR;
    }
    /*Adds the space to the game structure and increments the space number.*/
    game->spaces[game->n_spaces] = space;
    game->n_spaces++;

    return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
    /*Checks the arguments and possible errors.*/
    if (position < 0 || position >= game->n_spaces || (!game))
    {
        return ID_ERROR;
    }
    /*Returns the id of the space with that position.*/
    return space_get_id(game->spaces[position]);
}

Id game_get_character_location(Game *game, Id id)
{
    int i = 0;
    /*Error handling.*/
    if (!game || id == -2)
        return ID_ERROR;

    /*Searches for the object.*/
    for (i = 0; i < game->n_spaces; i++)
    {
        if (space_get_character(game->spaces[i]) == id)
            return space_get_id(game->spaces[i]);
    }
    /*The character wasn't found in any space.*/
    return NO_ID;
}

Status game_destroy(Game **game)
{
    int i = 0;

    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
    }

    /*Destroys the characters.*/
    for (i = 0; i < (*game)->n_characters; i++)
    {
        character_destroy((*game)->characters[i]);
    }

    /*Destroys the spaces.*/
    for (i = 0; i < (*game)->n_spaces; i++)
    {
        space_destroy((*game)->spaces[i]);
    }

    if ((*game)->player)
    {
        /*Destroys the player structure.*/
        player_destroy((*game)->player);
    }

    for (i = 0; i < (*game)->n_objects; i++)
    {
        object_destroy((*game)->objects[i]);
    }

    command_destroy((*game)->last_cmd);
    free(*game);
    return OK;
}

Status game_set_player(Game *game, Player *player)
{
    /*Error management.*/
    if (!player || game == NULL)
    {
        return ERROR;
    }

    game->player = player;

    return OK;
}

Player *game_get_player(Game *game)
{
    /*Error management.*/
    if (game == NULL)
    {
        return NULL;
    }

    /*Returns a pointer to the player.*/
    return game->player;
}

Id game_get_object_location(Game *game, Id id)
{
    int i = 0;
    /*Error management*/
    if (game == NULL)
    {
        return ID_ERROR;
    }

    /*Searches for the id where the object is and returns it, if it doesnt find it, it returns NO_ID.*/
    for (i = 0; i < game->n_spaces; i++)
    {
        if (space_find_object(game->spaces[i], id) != -1)
        {
            return space_get_id(game->spaces[i]);
        }
    }
    return NO_ID;
}

Id *game_get_objects(Game *game)
{
    Id *res = NULL;
    int i = 0, len = 0;
    /*Error handling.*/
    if (!game)
        return NULL;

    len = game_get_n_objects(game);
    if (len == 0)
        return NULL;

    /*Allocates memory.*/
    if (!(res = (Id *)calloc(game_get_n_objects(game), sizeof(Id))))
        return NULL;

    for (i = 0; i < len; i++)
    {
        res[i] = object_get_id(game->objects[i]);
    }

    /*Clean exit.*/
    return res;
}

int game_has_object(Game *game, Id id)
{
    int i = 0, len = 0;
    /*Error management.*/
    if (!game || id == NO_ID || id == ID_ERROR)
        return -1;
    len = game_get_n_objects(game);

    /*Searches for the object.*/
    for (i = 0; i < len; i++)
    {
        if (object_get_id(game->objects[i]) == id)
        {
            return i;
        }
    }

    /*The object wasn't found.*/
    return -1;
}

int game_get_n_objects(Game *game)
{
    /*Error handling.*/
    if (!game)
        return -1;

    /*Returns the value.*/
    return game->n_objects;
}

Id game_get_object_by_name(Game *game, char *word)
{
    int i;
    if (!game || !word)
    {
        return ID_ERROR;
    }
    for (i = 0; i < game->n_objects; i++)
    {
        if (!(strcmp(word, object_get_name(game->objects[i]))))
        {
            return (object_get_id(game->objects[i]));
        }
    }
    return NO_ID;
}

Status game_set_n_objects(Game *game, int n_objects)
{
    /*Error management.*/
    if (!game || n_objects < 0)
        return ERROR;

    /*Sets the value.*/
    game->n_objects = n_objects;

    /*Clean exit.*/
    return OK;
}

Status game_take_object(Game *game, Object *object)
{
    Id id = 0;
    int position = 0;
    /*Error handling.*/
    if (!game || !object)
        return ERROR;

    /*Takes the id.*/
    id = object_get_id(object);

    /*Searches for the object.*/
    if ((position = game_has_object(game, id)) == -1)
        return ERROR;

    /*Takes the object out.*/
    game->objects[position] = NULL;
    game_set_n_objects(game, game_get_n_objects(game) - 1);

    /*Clean exit.*/
    return OK;
}

Status game_add_object(Game *game, Object *object)
{
    /*Error handling.*/
    if (!game || !object || game_get_n_objects(game) >= MAX_OBJECTS)
        return ERROR;

    /*Adds the object.*/
    game->objects[game_get_n_objects(game)] = object;
    game_set_n_objects(game, game_get_n_objects(game) + 1);

    /*Clean exit.*/
    return OK;
}
Object *game_get_object(Game *game, Id id)
{
    int i = 0, len = 0;
    /*Error handling.*/
    if (!game || id == NO_ID || id == ID_ERROR)
        return NULL;

    len = game_get_n_objects(game);

    /*Searches for the object.*/
    for (i = 0; i < len; i++)
    {
        if (object_get_id(game->objects[i]) == id)
        {
            return game->objects[i];
        }
    }

    /*The object wasn't found.*/
    return NULL;
}

Command *game_get_last_command(Game *game)
{
    /*Error management.*/
    if (game == NULL)
    {
        return NULL;
    }

    /*It gets the last command used.*/
    return game->last_cmd;
}

Status game_set_last_command(Game *game, Command *command)
{
    /*Error management.*/
    if (game == NULL || command == NULL)
    {
        return ERROR;
    }

    /*It sets the last command to what you want.*/
    game->last_cmd = command;

    return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished)
{
    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
    }

    /*It sets the state (finished or not) of the game to what you want.*/
    game->finished = finished;
    return OK;
}

void game_print(Game *game)
{
    int i = 0;

    /*It prints all the information about the game.*/
    printf("\n\n-------------\n\n");

    printf("=> Spaces: \n");
    for (i = 0; i < game->n_spaces; i++)
    {
        space_print(game->spaces[i]);
    }

    printf("=> Number of objects: %d\n", game_get_n_objects(game));
    printf("    Their info is: ");
    for (i = 0; i < game_get_n_objects(game); i++)
    {
        object_print_info(game->objects[i]);
    }
    printf("=> Player id: %d\n", (int)player_get_player_id(game->player));
    return;
}

Status game_create_from_file(Game **game, char *filename)
{
    Character *c1 = NULL, *c2 = NULL;
    /*Error management.*/
    if (game == NULL || filename == NULL)
    {
        return ERROR;
    }

    if (game_create(game) == ERROR)
    {
        return ERROR;
    }

    if (game_reader_load_spaces(*game, filename) == ERROR)
    {
        return ERROR;
    }

    if (game_reader_load_objects(*game, filename) == ERROR)
    {
        return ERROR;
    }

    /*The player is located in the first space.*/
    player_set_player_location(game_get_player(*game), game_get_space_id_at(*game, 0));

    /*Loads the characters wheere they are supposed to be.*/
    c1 = character_create(CHARACTER_ID_1);
    character_set_description(c1, CHARACTER_DESCR_1);
    character_set_friendly(c1, TRUE);
    character_set_health(c1, CHARACTER_HEALTH_1);
    character_set_message(c1, CHARACTER_MSG_1);
    character_set_name(c1, CHARACTER_NAME_1);
    game_add_character((*game), c1);
    space_set_character(game_get_space((*game), SPACE_C1), CHARACTER_ID_1);
    c2 = character_create(CHARACTER_ID_2);
    game_add_character((*game), c2);
    character_set_description(c2, CHARACTER_DESCR_2);
    character_set_friendly(c2, FALSE);
    character_set_health(c2, CHARACTER_HEALTH_2);
    character_set_message(c2, CHARACTER_MSG_2);
    character_set_name(c2, CHARACTER_NAME_2);
    space_set_character(game_get_space((*game), SPACE_C2), CHARACTER_ID_2);

    return OK;
}