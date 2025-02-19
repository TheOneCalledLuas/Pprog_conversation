/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Saul Lopez Romero, Fernando Mijangos Varas
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Game interface implementation.
*/
struct _Game
{
    Player *player;               /*!< Pointer to the player. */
    Object *object;               /*!< Pointer to the object. */
    Space *spaces[MAX_SPACES];    /*!< An array with the information of every space. */
    Object *objects[MAX_OBJECTS]; /*!< An array with the information of every objects.*/
    int n_spaces;                 /*!< Number of spaces.*/
    int n_objects;                /*!< Number of objects.*/
    Command *last_cmd;            /*!< A pointer to the last command entered by the user.*/
    Bool finished;                /*!< Whether the game has finished or not.*/
};

Status game_create(Game **game)
{
    int i;

    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
    }
    /*memory allocation*/
    (*game) = (Game *)malloc(sizeof(Game));

    for (i = 0; i < MAX_SPACES; i++)
    {
        (*game)->spaces[i] = NULL;
    }
    /*Initializes all members of the game structure.*/
    (*game)->n_spaces = 0;
    (*game)->n_objects = 0;
    (*game)->player = player_create(5);
    (*game)->object = object_create(13);
    (*game)->last_cmd = command_create();
    (*game)->finished = FALSE;

    return OK;
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
    if (id == NO_ID)
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
        return NO_ID;
    }
    /*Returns the id of the space with that position.*/
    return space_get_id(game->spaces[position]);
}

Status game_destroy(Game **game)
{
    int i = 0;

    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
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

    if ((*game)->object)
    {
        /*Destroys the object.*/
        object_destroy((*game)->object);
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

Id game_get_object_location(Game *game)
{
    int i = 0;
    /*Error management*/
    if (game == NULL)
    {
        return NO_ID;
    }

    /*Searches for the id where the object is and returns it, if it doesnt find it, it returns NO_ID.*/
    for (i = 0; i < game->n_spaces; i++)
    {
        if (space_get_object(game->spaces[i]) != NO_ID || space_get_object(game->spaces[i]) != NO_ID)
        {
            return space_get_id(game->spaces[i]);
        }
    }
    return NO_ID;
}

Status game_set_object_location(Game *game, Id space_id)
{
    Id idaux;
    Object *object=game_get_object(game);
    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
    }

    /*It first sets the pointer of the object of the space where the object was to NULL.*/
    idaux = game_get_object_location(game);
    space_set_object(game_get_space(game, idaux), NO_ID);

    /*Changes the pointer of the object of the new space where the object will be to the real object.*/
    if(space_id!=NO_ID) 
    {
        space_set_object(game_get_space(game, space_id), object_get_id(object));
    }
    return OK;
}

Object *game_get_object(Game *game)
{
    /*Error management.*/
    if (!game)
    {
        return NULL;
    }

    /*It returns the object.*/
    return game->object;
}

Status game_set_object(Game *game, Object *object)
{
    /*Error management.*/
    if (!game)
    {
        return ERROR;
    }

    /*It sets the object to a different one.*/
    game->object = object;
    return OK;
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

    printf("=> Object id: %d\n", (int)object_get_id(game->object));
    printf("=> Player id: %d\n", (int)player_get_player_id(game->player));
    return;
}

Status game_create_from_file(Game **game, char *filename)
{
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

    /*The player and the object are located in the first space.*/
    player_set_player_location(game_get_player(*game), game_get_space_id_at(*game, 0));
    game_set_object_location(*game, game_get_space_id_at(*game, 0));

    return OK;
}