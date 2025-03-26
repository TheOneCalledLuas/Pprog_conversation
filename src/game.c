/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Saul Lopez Romero, Fernando Mijangos
 * @version 3
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "character.h"
#include "game_reader.h"
#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Temporal character data. (This will be eventually changed).*/
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
#define ID_PLAYER 5

#define MAX_PLAYERS 10

/**
   Game interface implementation.
*/
struct _Game
{
    Player *players[MAX_PLAYERS];          /*!< Array with all the players. */
    Space *spaces[MAX_SPACES];             /*!< An array with the information of every space. */
    Object *objects[MAX_OBJECTS];          /*!< An array with the information of every objects.*/
    Character *characters[MAX_CHARACTERS]; /*!< Array with all the character of the game.*/
    Link *links[MAX_LINKS];                /*!< Array with all the links information.*/
    int n_spaces;                          /*!< Number of spaces.*/
    int n_objects;                         /*!< Number of objects.*/
    int n_characters;                      /*< Number of characters.*/
    int n_links;
    Command *last_cmd; /*!< A pointer to the last command entered by the user.*/
    Bool finished;     /*!< Whether the game has finished or not.*/
    int turn;          /*!< Actual turn.*/
    int n_players;     /*!< Number of players,*/
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
    if ((*game) == NULL)
    {
        return ERROR;
    }

    for (i = 0; i < MAX_SPACES; i++)
    {
        (*game)->spaces[i] = NULL;
    }
    for (i = 0; i < MAX_CHARACTERS; i++)
    {
        (*game)->characters[i] = NULL;
    }
    for (i = 0; i < MAX_OBJECTS; i++)
    {
        (*game)->objects[i] = NULL;
    }
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        (*game)->players[i] = NULL;
    }
    for (i = 0; i < MAX_LINKS; i++)
    {
        (*game)->links[i] = NULL;
    }

    /*Initializes all members of the game structure.*/
    (*game)->n_spaces = 0;
    (*game)->n_objects = 0;
    (*game)->n_characters = 0;
    (*game)->n_players = 0;
    (*game)->n_links = 0;
    (*game)->turn = 0;
    (*game)->last_cmd = command_create();
    (*game)->finished = FALSE;

    return OK;
}

Id *game_get_characters(Game *game)
{
    Id *characters = NULL;
    int n_elements, i;

    /*Error handling.*/
    if (!game)
    {
        return NULL;
    }
    n_elements = MAX_CHARACTERS;

    /*Memory allocation.*/
    if (!(characters = (Id *)calloc(n_elements, sizeof(Id))))
    {
        return NULL;
    }

    /*Gets thhe character's id.*/
    for (i = 0; i < n_elements; i++)
    {
        characters[i] = character_get_id(game->characters[i]);
    }

    /*Clean exit.*/
    return characters;
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
    if (!game || id == ID_ERROR)
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

    /*Destroys the players.*/
    for (i = 0; i < (*game)->n_players; i++)
    {
        player_destroy((*game)->players[i]);
    }

    /*Destroys the objects.*/
    for (i = 0; i < (*game)->n_objects; i++)
    {
        object_destroy((*game)->objects[i]);
    }
    /*Destroys the links.*/
    for (i = 0; i < (*game)->n_links; i++)
    {
        link_destroy((*game)->links[i]);
    }

    command_destroy((*game)->last_cmd);
    free(*game);
    return OK;
}

int game_get_turn(Game * game) {
    /*Error handling.*/
    if (!game) return -1;

    /*Returns the game.*/
    return game->turn;
}

int game_get_n_players(Game *game)
{
    /*Error handling.*/
    if (!game)
        return -1;
    /*Returns the value.*/
    return game->n_players;
}

Status game_next_turn(Game *game)
{
    /*Error handling.*/
    if (!game)
        return ERROR;
    /*Goes to the next turn.*/
    game->turn = ((game->turn) + 1 == game->n_players ? 0 : (game->turn) + 1);
    return OK;
}

int game_get_next_turn(Game *game)
{
    /*Error handling.*/
    if (!game)
        return -1;
    /*Returns the next turn.*/
    return ((game->turn) + 1 == game->n_players ? 0 : (game->turn) + 1);
}

Status game_add_player(Game *game, Player *player)
{
    /*Error management.*/
    if (!player || game == NULL)
    {
        return ERROR;
    }

    game->players[(game->n_players)++] = player;

    return OK;
}

Player *game_get_actual_player(Game *game)
{
    /*Error management.*/
    if (game == NULL)
    {
        return NULL;
    }

    /*Returns a pointer to the player.*/
    return game->players[game->turn];
}

Player *game_get_last_player(Game *game)
{
    /*Error management.*/
    if (game == NULL)
    {
        return NULL;
    }

    /*Returns a pointer to the player.*/
    return (game->turn == 0 ? game->players[game->n_players - 1] : game->players[game->turn - 1]);
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
        if (space_find_object(game->spaces[i], id) != NO_ID)
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
    return NO_ID;
}

int game_get_n_objects(Game *game)
{
    /*Error handling.*/
    if (!game)
        return NO_ID;

    /*Returns the value.*/
    return game->n_objects;
}

Id game_get_object_by_name(Game *game, char *word)
{
    int i;
    /*Error handling.*/
    if (!game || !word)
    {
        return ID_ERROR;
    }
    /*Searches the object by its name.*/
    for (i = 0; i < game->n_objects; i++)
    {
        if (!(strcmp(word, object_get_name(game->objects[i]))))
        {
            /*Returns the object id.*/
            return (object_get_id(game->objects[i]));
        }
    }
    /*The object wasn't found.*/
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
    if ((position = game_has_object(game, id)) == NO_ID)
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

    /*1.-Spaces.*/
    printf("=> Spaces: \n");
    for (i = 0; i < game->n_spaces; i++)
    {
        space_print(game->spaces[i]);
    }

    /*2.-Objects.*/
    printf("=> Number of objects: %d\n", game_get_n_objects(game));
    printf("    Their info is: ");
    for (i = 0; i < game_get_n_objects(game); i++)
    {
        object_print_info(game->objects[i]);
    }

    /*3.-Players.*/
    printf("=> Players:\n");
    for (i = 0; i < game->n_players; i++)
    {
        player_print(game->players[i]);
        printf("\n");
    }
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

    if (game_reader_load_players(*game, filename) == ERROR)
    {
        return ERROR;
    }

    if (game_reader_load_links(*game, filename) == ERROR)
    {
        return ERROR;
    }

    /*Loads the characters where they are supposed to be (TEMPORAL).*/
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

    /*Clean exit.*/
    return OK;
}

Status game_add_link(Game *game, Link *link)
{
    /*Error management.*/
    if (!game || !link)
        return ERROR;

    if (game->n_links == MAX_LINKS)
        return ERROR;

    /*Puts the new link and increases the number of links.*/
    game->links[game->n_links] = link;
    game->n_links++;

    /*Return OK.*/
    return OK;
}

Status game_delete_link(Game *game, int position)
{
    /*Error management*/
    if (!(game) || position < 0)
        return ERROR;

    /*Destroys the link.*/
    return link_destroy(game->links[position]);
}

Link *game_find_link(Game *game, Id link_id)
{
    int i;
    /*Error management*/
    if (!(game) || link_id == NO_ID || link_id == ID_ERROR)
        return NULL;

    /*Finds the link and returns it.*/
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_id(game->links[i]) == link_id)
            return game->links[i];
    }

    /*If it doesn't find it, returns NULL.*/
    return NULL;
}

Id game_get_north_from_space(Game *game, Id space)
{
    int i;
    /*Error managment.*/
    if (!(game) || space == NO_ID || space == ID_ERROR)
        return ID_ERROR;

    /*Finds the links with origin the space given, and if they are facing north, returns the destination.*/
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_origin(game->links[i]) == space && link_get_direction(game->links[i]) == N)
            return link_get_destination(game->links[i]);
    }

    /*If it doesn't find a north connection, returns NO_ID.*/
    return NO_ID;
}

Id game_get_east_from_space(Game *game, Id space)
{
    int i;
    /*Error managment.*/
    if (!(game) || space == NO_ID || space == ID_ERROR)
        return ID_ERROR;

    /*Finds the links with origin the space given, and if they are facing north, returns the destination.*/
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_origin(game->links[i]) == space && link_get_direction(game->links[i]) == E)
            return link_get_destination(game->links[i]);
    }

    /*If it doesn't find a north connection, returns NO_ID.*/
    return NO_ID;
}

Id game_get_south_from_space(Game *game, Id space)
{
    int i;
    /*Error managment.*/
    if (!(game) || space == NO_ID || space == ID_ERROR)
        return ID_ERROR;

    /*Finds the links with origin the space given, and if they are facing north, returns the destination.*/
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_origin(game->links[i]) == space && link_get_direction(game->links[i]) == S)
            return link_get_destination(game->links[i]);
    }

    /*If it doesn't find a north connection, returns NO_ID.*/
    return NO_ID;
}

Id game_get_west_from_space(Game *game, Id space)
{
    int i;
    /*Error managment.*/
    if (!(game) || space == NO_ID || space == ID_ERROR)
        return ID_ERROR;

    /*Finds the links with origin the space given, and if they are facing north, returns the destination.*/
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_origin(game->links[i]) == space && link_get_direction(game->links[i]) == W)
            return link_get_destination(game->links[i]);
    }

    /*If it doesn't find a north connection, returns NO_ID.*/
    return NO_ID;
}
