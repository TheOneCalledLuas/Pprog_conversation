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
#include "gamerules.h"
#include "animation.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#define MAX_PLAYERS 8       /*!<Max number of players.*/
#define IDENTIFIER_LENGHT 3 /*!<Size of the weord that identifies a str*/

/**
   Game interface implementation.
*/
struct _Game
{
    Player *players[MAX_PLAYERS];                    /*!< Array with all the players. */
    Space *spaces[MAX_SPACES];                       /*!< An array with the information of every space. */
    Object *objects[MAX_OBJECTS];                    /*!< An array with the information of every objects.*/
    Character *characters[MAX_CHARACTERS];           /*!< Array with all the character of the game.*/
    Link *links[MAX_LINKS];                          /*!< Array with all the links information.*/
    int n_spaces;                                    /*!< Number of spaces.*/
    int n_objects;                                   /*!< Number of objects.*/
    int n_characters;                                /*!< Number of characters.*/
    int n_links;                                     /*!< Number of links.*/
    int n_commands;                                  /*!< Number of commands.*/
    Command *commands[MAX_PLAYERS * COMMANDS_SAVED]; /*!< Commands created.*/
    Command *last_cmd[MAX_PLAYERS][COMMANDS_SAVED];  /*!< Array with the last commands executed by the players.*/
    int command_num[MAX_PLAYERS];                    /*!< Array which determines the last command.*/
    Bool finished;                                   /*!< Whether the game has finished or not.*/
    int turn;                                        /*!< Actual turn.*/
    int n_players;                                   /*!< Number of players.*/
    Game_values *game_values;                        /*!< Structure whiZch holds all the gamerule handling inside.*/
    char savefiles[MAX_SAVEFILES][WORD_SIZE];        /*!< Maximum number of savefiles that can exist.*/
    char current_savefile[WORD_SIZE];                /*!< Name of the current savefile.*/
    int n_savefiles;                                 /*!< Number of savefiles that currently exist.*/
    Animation_Manager *animation_manager;            /*!< Animation manager.*/
    int n_teams;                                     /*!< Number of teams.*/
    Bool is_determined;                              /*!< Whether the game is determined or not.*/
};

int game_get_n_teams(Game *game)
{
    /*Error management.*/
    if (!game)
    {
        return -1;
    }

    /*Returns the number of teams.*/
    return game->n_teams;
}

Status game_set_n_teams(Game *game, int n_teams)
{
    /*Error management.*/
    if (!game || n_teams < 0)
    {
        return ERROR;
    }

    /*Sets the number of teams.*/
    game->n_teams = n_teams;

    return OK;
}

Bool game_get_determined(Game *game)
{
    /*Error management.*/
    if (!game)
    {
        return FALSE;
    }

    /*Returns the value of the determined mode. */
    return game->is_determined;
}

Status game_set_determined(Game *game, Bool is_determined)
{
    /*Error management.*/
    if (!game)
    {
        return ERROR;
    }

    /*Sets the value of the determined mode. */
    game->is_determined = is_determined;

    return OK;
}

Status game_create_team(Game *game, Id player_leader, Id player_member)
{
    /*Error management.*/
    if (!game || player_leader <= NO_ID || player_member <= NO_ID)
    {
        return ERROR;
    }
    if (player_leader == player_member)
        return ERROR;

    /*Teams the players.*/
    player_set_team(game_get_player_by_id(game, player_leader), player_leader);
    player_set_team(game_get_player_by_id(game, player_member), player_leader);

    /*Actualises the number of teams.*/
    game_set_n_teams(game, game_get_n_teams(game) + 1);

    /*Clean exit.*/
    return OK;
}

Status game_destroy_team(Game *game, Id player)
{
    Id player_member = NO_ID;

    /*Error management.*/
    if (!game || player <= NO_ID)
    {
        return ERROR;
    }

    /*Checks that the players are in a team.*/
    if (player_get_team(game_get_player(game, player)) == NO_ID)
    {
        return ERROR;
    }

    /*Searches for the player member of the team. */
    player_member = game_get_teammate_from_player(game, player);

    /*Destroys the team.*/
    player_set_team(game_get_player(game, player), NO_ID);
    player_set_team(game_get_player(game, player_member), NO_ID);

    /*Actualises the number of teams.*/
    game_set_n_teams(game, game_get_n_teams(game) - 1);

    /*Clean exit.*/
    return OK;
}

Id game_get_teammate_from_player(Game *game, Id player)
{
    Id team = NO_ID, act_team;
    int i = 0;

    /*Error management.*/
    if (!game || player <= NO_ID)
    {
        return NO_ID;
    }

    act_team = player_get_team(game_get_player_by_id(game, player));

    /*Searches for the player. */
    for (i = 0; i < game->n_players; i++)
    {
        if (player_get_team(game->players[i]) == act_team && player_get_player_id(game->players[i]) != player)
        {
            team = player_get_player_id(game->players[i]);
            break;
        }
    }

    /*Returns the id of the team, which will be NO_ID if the teeammate wasn't found. */
    return team;
}

Status game_create(Game **game)
{
    int i = 0;

    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
    }
    if (*game != NULL)
    {
        game_destroy(game);
        *game = NULL;
    }
    /*Memory allocation.*/
    (*game) = (Game *)malloc(sizeof(Game));
    if ((*game) == NULL)
    {
        return ERROR;
    }

    if (((*game)->game_values = gamerules_values_init()) == NULL)
    {
        free(*game);
        return ERROR;
    }

    if (((*game)->animation_manager = animation_manager_init("anim/")) == NULL)
    {
        free((*game)->game_values);
        free(*game);
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
    for (i = 0; i < MAX_PLAYERS * COMMANDS_SAVED; i++)
    {
        (*game)->commands[i] = NULL;
        (*game)->last_cmd[i / COMMANDS_SAVED][i % COMMANDS_SAVED] = NULL;
    }
    for (i = 0; i < MAX_SAVEFILES; i++)
    {
        (*game)->savefiles[i][0] = '\0';
    }

    /*Initializes all members of the game structure.*/
    (*game)->n_spaces = 0;
    (*game)->n_objects = 0;
    (*game)->n_characters = 0;
    (*game)->n_players = 0;
    (*game)->n_links = 0;
    (*game)->n_commands = 0;
    (*game)->turn = 0;
    (*game)->finished = FALSE;
    (*game)->n_savefiles = 0;
    (*game)->n_teams = 0;
    (*game)->is_determined = FALSE;
    return OK;
}

Status game_add_savefile(Game *game, char *name)
{
    int i;
    /*Error management*/
    if (!(game) || !name || game->n_savefiles >= MAX_SAVEFILES)
        return ERROR;
    /*Looks that the savefile doesnt exist already.*/
    for (i = 0; i < game->n_savefiles; i++)
    {
        if (strcmp(name, game->savefiles[i]) == 0)
            return ERROR;
    }
    /*Adds the savfile*/
    strcpy(game->savefiles[i], name);
    game->n_savefiles++;
    return OK;
}

Status game_set_current_savefile(Game *game, char *name)
{ /*Error management*/
    if (!(game) || !name)
        return ERROR;
    /*Sets the name of the current savefile*/
    strcpy(game->current_savefile, name);
    return OK;
}

int game_random_int(int start, int end)
{
    /*Srand was called beforehand.*/

    /*Returns the number.*/
    return (start + rand() % (start - end + 1));
}

char *game_get_current_savefile(Game *game)
{
    /*Error management*/
    if (!(game))
        return NULL;
    /*Returns the name of the current savefile*/
    return game->current_savefile;
}

Status game_add_new_savefile(Game *game, char *name)
{
    FILE *f = NULL;
    int i = 0;
    char str[WORD_SIZE] = "";
    /*Error management*/
    if (!game || !name || game->n_savefiles >= MAX_SAVEFILES)
        return ERROR;
    /*Tries to open the file with the savefiles names*/
    if (!(f = fopen(SAVEFILES_NAMES, "a")))
        return ERROR;
    /*Checks the it doesnt exist alreay*/
    for (i = 0; i < game->n_savefiles; i++)
    {
        if (strcmp(name, game->savefiles[i]) == 0)
            return ERROR;
    }
    /*Adds the new savefile to the game structure*/
    if (game_add_savefile(game, name) == ERROR)
        return ERROR;
    /*Prints that name into the savefiles_names.txt*/
    fprintf(f, "%s\n", name);
    /*Prints the command that will be inputed into the terminal*/
    sprintf(str, ">data/%s.dat", name);
    system(str);
    fclose(f);
    return OK;
}

Status game_delete_savefile(Game *game, char *name)
{
    FILE *f = NULL;
    int i = 0;
    char str[WORD_SIZE] = "";
    /*Error management*/
    if (!(game) || !(name) || game->n_savefiles <= 0)
        return ERROR;

    /*Tries to open the file with the savefiles names*/
    if (!(f = fopen(SAVEFILES_NAMES, "w")))
        return ERROR;

    /*Finds the savefile with that name and deletes it*/
    for (i = 0; i < game->n_savefiles; i++)
    {
        /*If it finds it do this*/
        if (strcmp(name, game->savefiles[i]) == 0)
        {
            /*1-Deletes it from the list of names in the game structure*/
            while (i < game->n_savefiles - 1)
            {
                strcpy(game->savefiles[i], game->savefiles[i + 1]);
                i++;
            }
            game->n_savefiles--;
            game->savefiles[game->n_savefiles][0] = '\0';
            /*2-Creates the command that will be used in terminal*/
            sprintf(str, "rm data/%s.dat", name);
            system(str);
            /*3-Prints in the savefile_names text file the real savefiles*/
            for (i = 0; i < game->n_savefiles; i++)
            {
                fprintf(f, "%s\n", game->savefiles[i]);
            }
            fclose(f);
            return OK;
        }
    }
    fclose(f);
    return ERROR;
}

int game_get_n_savefiles(Game *game)
{
    /*Error management and returns the value*/
    return (game ? game->n_savefiles : -1);
}

Status game_set_n_savefiles(Game *game, int n)
{
    /*Error managment*/
    if (!(game) || n < 0 || n > MAX_SAVEFILES)
        return ERROR;

    /*Sets the new value*/
    game->n_savefiles = n;
    return OK;
}

char *game_get_savefile(Game *game, int n)
{
    /*Error management*/
    if (!(game) || n < 0 || n >= MAX_SAVEFILES)
        return NULL;
    /*Returns what was asked*/
    return game->savefiles[n];
}

Link *game_get_link(Game *game, Id link)
{
    int i;
    /*Error management*/
    if (!(game) || !(link))
        return NULL;

    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_id(game->links[i]) == link)
            return game->links[i];
    }
    return NULL;
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

    /*Gets the character's id.*/
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
    for (i = 0; i < game->n_characters; i++)
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

Id game_get_character_by_name(Game *game, char *word)
{
    int i;
    /*Error handling.*/
    if (!game || !word)
    {
        return ID_ERROR;
    }
    /*Searches the character by its name.*/
    for (i = 0; i < game->n_characters; i++)
    {
        if (!(strcasecmp(word, character_get_name(game->characters[i]))))
        {
            /*Returns the character id.*/
            return (character_get_id(game->characters[i]));
        }
    }
    /*The character wasn't found.*/
    return NO_ID;
}

Game_values *game_get_game_values(Game *game)
{
    /*Error handling.*/
    if (!game)
        return NULL;

    /*Returns the game values.*/
    return game->game_values;
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
        if (space_find_character(game->spaces[i], id) != -1)
            return space_get_id(game->spaces[i]);
    }
    /*The character wasn't found in any space.*/
    return NO_ID;
}

Animation_Manager *game_get_animation_manager(Game *game)
{
    /*Error handling.*/
    if (!game)
        return NULL;

    /*Returns the animation manager. */
    return game->animation_manager;
}

Status game_destroy(Game **game)
{
    int i = 0;
    Gamerule *gr = NULL;

    /*Error management.*/
    if (game == NULL)
    {
        return ERROR;
    }
    if (!(*game))
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
    /*Destroys the command.*/
    for (i = 0; i < (*game)->n_commands; i++)
    {
        command_destroy((*game)->commands[i]);
    }

    /*Destroys the gamerules and game values.*/
    if ((*game)->game_values)
    {
        while (gamerules_get_n_gamerules((*game)->game_values) > 0)
        {
            gr = gamerules_values_delete_last((*game)->game_values);
            gamerules_gamerule_destroy(gr);
        }
        gamerules_values_destroy((*game)->game_values);
    }
    (*game)->game_values = NULL;

    /*Destroys the animation manager and all the animations.*/
    for (i = 0; i < game_get_n_animations(*game); i++)
    {
        animation_manager_del_animation((*game)->animation_manager, i);
    }

    if ((*game)->animation_manager)
    {
        animation_manager_destroy((*game)->animation_manager);
        (*game)->animation_manager = NULL;
    }

    /*Sets the pointer to NULL. */
    free(*game);
    (*game) = NULL;

    /*Clean exit.*/
    return OK;
}

int game_get_n_animations(Game *game)
{
    /*Error handling.*/
    if (!game)
        return -1;

    /*Returns the number of animations. */
    return animation_manager_get_n_animations(game->animation_manager);
}

int game_get_turn(Game *game)
{
    /*Error handling.*/
    if (!game)
        return -1;

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

Player *game_get_player(Game *game, int player_number)
{
    /*Error handling.*/
    if (!game || player_number < 0 || player_number >= game->n_players)
        return NULL;

    /*Returns the player.*/
    return game->players[player_number];
}

Status game_next_turn(Game *game)
{
    /*Error handling.*/
    if (!game)
        return ERROR;

    /*Goes to the next last command.*/
    if (!game_next_command(game))
        return ERROR;
    /*Goes to the next turn.*/
    game->turn = ((game->turn) + 1 == game->n_players ? 0 : (game->turn) + 1);
    return OK;
}

Status game_set_turn(Game *game, int turn)
{
    /*Error handling.*/
    if (!game || turn < 0 || turn >= game->n_players)
        return ERROR;

    /*Sets the turn.*/
    game->turn = turn;
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
        if (!(strcasecmp(word, object_get_name(game->objects[i]))))
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
    return game->last_cmd[game->turn][game->command_num[game->turn]];
}

Status game_set_last_command(Game *game, Command *command)
{
    /*Error management.*/
    if (game == NULL || command == NULL)
    {
        return ERROR;
    }

    /*It sets the last command to what you want.*/
    game->last_cmd[game->turn][game->command_num[game->turn]] = command;

    return OK;
}

Status game_next_command(Game *game)
{
    if (!game)
        return ERROR;

    /*Actualises the last command.*/
    game->command_num[game->turn] = (game->command_num[game->turn] + 1) % COMMANDS_SAVED;

    return OK;
}

Command *game_get_previous_command(Game *game, int command_num)
{
    int aux = 0;
    /*Error management.*/
    if (!game)
        return NULL;

    aux = (game->command_num[game->turn] - command_num + COMMANDS_SAVED) % COMMANDS_SAVED;

    return game->last_cmd[game->turn][aux];
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

Link *game_get_link_by_name(Game *game, char *name)
{
    int i = 0;
    /*Error management.*/
    if (!(game) || name == NULL)
        return NULL;

    /*Searches for the link and returns it. */
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_name(game->links[i]) && strcmp(link_get_name(game->links[i]), name) == 0)
            return game->links[i];
    }

    /*The link wasn't found */
    return NULL;
}

Status game_create_from_file(Game **game, char *filename)
{
    int i = 0, j = 0;
    /*Error management.*/
    if (game == NULL || filename == NULL)
    {
        return ERROR;
    }
    if (*game != NULL)
    {
        game_destroy(game);
    }
    *game = NULL;

    /*Creates the game.*/
    if (game_create(game) == ERROR)
    {
        return ERROR;
    }

    /*Loads the spaces.*/
    if (game_reader_load_spaces(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads the objects in.*/
    if (game_reader_load_objects(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads the players.*/
    if (game_reader_load_players(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads the links.*/
    if (game_reader_load_links(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads the characters.*/
    if (game_reader_load_characters(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads all the gamerules.*/
    if (game_reader_load_gamerules(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads all the animations.*/
    if (game_reader_load_animations(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads the savefile names*/
    if (game_reader_load_savefile_names(*game) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Loads the turn*/
    if (game_reader_load_last_turn(*game, filename) == ERROR)
    {
        game_destroy(game);
        return ERROR;
    }

    /*Initialises all the commands.*/
    for (i = 0; i < (*game)->n_players; i++)
    {
        (*game)->command_num[i] = FIRST_LAST_COMMAND;
        for (j = 0; j < COMMANDS_SAVED; j++)
        {
            (*game)->commands[(*game)->n_commands] = command_create();
            if (!((*game)->commands[(*game)->n_commands]))
                return ERROR;
            (*game)->last_cmd[i][j] = (*game)->commands[(*game)->n_commands];
            (*game)->n_commands = (*game)->n_commands + 1;
        }
    }

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

Id game_get_space_at(Game *game, Id space, Direction direction)
{
    int i;
    /*Error managment.*/
    if (!(game) || space == ID_ERROR || direction < 0 || direction > D)
        return ID_ERROR;

    /*Finds the links with origin the space given, and if they are facing that direction, returns the destination.*/
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_origin(game->links[i]) == space && link_get_direction(game->links[i]) == direction)
            return link_get_destination(game->links[i]);
    }

    /*If it doesn't find a north connection, returns NO_ID.*/
    return NO_ID;
}

int game_get_n_followers(Game *game, Id player)
{
    int i = 0, n = 0;
    /*Error management*/
    if (!(game) || player == NO_ID || player == ID_ERROR)
        return -1;

    /*Counts the number of followers.*/
    for (i = 0; i < game->n_characters; i++)
    {
        if (character_get_follow(game->characters[i]) == player)
            n++;
    }
    return n;
}

Link_Property game_get_space_outcoming_connection_info(Game *game, Id space, Direction dir)
{
    int i = 0;
    /*Error handling.*/
    if (!game || space < 0)
        return UNK;
    /*Searches for the link.*/
    for (i = 0; i < game->n_links; i++)
    {
        if (link_get_origin(game->links[i]) == space && link_get_direction(game->links[i]) == dir)
        { /*If the link was found.*/
            /*Clean exit.*/
            return (link_get_state(game->links[i]) == TRUE ? OPENED : CLOSED);
        }
    }
    /*The link wasn't found.*/
    return UNK;
}

Id game_get_player_by_name(Game *game, char *name)
{
    int i = 0;
    /*Error handling.*/
    if (!game || !name)
    {
        return ID_ERROR;
    }
    /*Searches the player by its name.*/
    for (i = 0; i < game->n_players; i++)
    {
        if (!(strcasecmp(name, player_get_player_name(game->players[i]))))
        {
            /*Returns the player id.*/
            return (player_get_player_id(game->players[i]));
        }
    }
    /*The player wasn't found.*/
    return NO_ID;
}

Player *game_get_player_by_id(Game *game, Id id)
{
    int i = 0;
    /*Error handling.*/
    if (!game || id == NO_ID)
        return NULL;

    /*Searches for the player.*/
    for (i = 0; i < game->n_players; i++)
    {
        if (id == player_get_player_id(game->players[i]))
        {
            /*Returns the player when found.*/
            return game->players[i];
        }
    }
    /*The player wasn't found.*/
    return NULL;
}

Id *game_get_players(Game *game)
{
    Id *players = NULL;
    int i = 0, len = 0;
    /*Error handling.*/
    if (!game)
        return NULL;

    len = game->n_players;
    if (len == 0)
        return NULL;

    /*Allocates memory.*/
    if (!(players = (Id *)calloc(len, sizeof(Id))))
        return NULL;

    for (i = 0; i < len; i++)
    {
        players[i] = player_get_player_id(game->players[i]);
    }

    /*Clean exit.*/
    return players;
}

Id *game_get_spaces(Game *game)
{
    Id *spaces = NULL;
    int i = 0, len = 0;
    /*Error handling.*/
    if (!game)
        return NULL;

    len = game->n_spaces;
    if (len == 0)
        return NULL;

    /*Allocates memory.*/
    if (!(spaces = (Id *)calloc(len, sizeof(Id))))
        return NULL;

    for (i = 0; i < len; i++)
    {
        spaces[i] = space_get_id(game->spaces[i]);
    }

    /*Clean exit.*/
    return spaces;
}

Id *game_get_links(Game *game)
{
    Id *links = NULL;
    int i = 0, len = 0;
    /*Error handling.*/
    if (!game)
        return NULL;

    len = game->n_links;
    if (len == 0)
        return NULL;

    /*Allocates memory.*/
    if (!(links = (Id *)calloc(len, sizeof(Id))))
        return NULL;

    for (i = 0; i < len; i++)
    {
        links[i] = link_get_id(game->links[i]);
    }

    /*Clean exit.*/
    return links;
}

Id *game_get_gamerules(Game *game)
{
    /*Error handling.*/
    if (!game)
        return NULL;
    /*Clean exit.*/
    return gamerules_get_all_gamerules(game->game_values);
}

int game_get_n_gamerules(Game *game)
{
    /*Error management and gets the number of gamerules*/
    return (game ? gamerules_get_n_gamerules(game->game_values) : -1);
}

int game_get_n_links(Game *game)
{
    /*ERror management and gets the number of links*/
    return (game ? game->n_links : -1);
}

int game_get_n_spaces(Game *game)
{
    /*Error management and gets the number of spaces*/
    return (game ? game->n_spaces : -1);
}

Status game_move_all_players(Game *game, Id room)
{
    int i = 0;

    /*Error management*/
    if (!game || room <= NO_ID)
    {
        return ERROR;
    }

    /*Moves all the players to the room given*/
    for (i = 0; i < game->n_players; i++)
    {
        player_set_player_location(game->players[i], room);
    }

    /*Clean exit*/
    return OK;
}