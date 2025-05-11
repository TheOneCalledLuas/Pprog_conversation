/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Fernando Mijangos, Saúl López Romero.
 * @version 3
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#include "inventory.h"
#include "object.h"
#include "types.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Maximun lenght of a description string for a player.*/
#define MAX_GDESC 10
#define DEFAULT_HEALTH 20 /*!< Player's default health. */
#define FIRST_CHAR 0      /*!< Position number 0 of a string, used to initialize things*/

/**
 * @brief Player
 *
 * It stores all the information related to a player.
 */
struct _Player
{
    Id player_id;                        /*!< Id of the player.*/
    char player_name[PLAYER_NAME_SIZE];  /*!< Name of the player.*/
    Id player_location;                  /*!< id of the space where the player is at.*/
    Inventory *inventory;                /*!< Player inventory.*/
    int health;                          /*!< Health points the player has.*/
    char gdesc[MAX_GDESC];               /*!< Graphic description for the player.*/
    char *texture[PLAYER_TEXTURE_LINES]; /*!< Texture of the player.*/
    char *__texture;                     /*!< Actual matrix with the gdesc.*/
    Id team;                             /*!< Id of the team the player belongs to. */
};

Player *player_create(Id id)
{
    Player *player;
    int i;

    if (id <= NO_ID)
        return NULL;

    /*Allocation of memory for player and error management*/
    player = (Player *)malloc(sizeof(Player));
    if (player == NULL)
    {
        return NULL;
    }

    /*Initialization of the values*/
    player->player_id = id;
    player->player_name[FIRST_CHAR] = '\0';
    player->player_location = NO_ID;
    player->inventory = inventory_create();
    player->health = DEFAULT_HEALTH;
    player->team = NO_ID;
    if (!(player->__texture = (char *)calloc(PLAYER_TEXTURE_LINES * PLAYER_TEXTURE_SIZE, sizeof(char))))
    {
        return NULL;
    }
    /*Sets the array so that it's more accesible.*/
    for (i = 0; i < PLAYER_TEXTURE_LINES; i++)
    {
        player->texture[i] = &(player->__texture[i * PLAYER_TEXTURE_SIZE]);
    }
    player->gdesc[0] = '\0';

    return player;
}

char *player_get_texture_line(Player *player, int line)
{
    /*Error management*/
    if (player == NULL || line < 0 || line >= PLAYER_TEXTURE_LINES)
    {
        return NULL;
    }

    /*Returns the value.*/
    return player->texture[line];
}

Status player_set_team(Player *player, Id team)
{
    /*Error management*/
    if (player == NULL || team < NO_ID)
    {
        return ERROR;
    }

    /*Sets the value.*/
    player->team = team;

    return OK;
}

Id player_get_team(Player *player)
{
    /*Error management*/
    if (player == NULL)
    {
        return NO_ID;
    }

    /*Returns the value.*/
    return player->team;
}

Status player_set_texture_line(Player *player, int line, char *str)
{
    /*Error management*/
    if (player == NULL || line < 0 || line >= PLAYER_TEXTURE_LINES || str == NULL)
    {
        return ERROR;
    }

    /*Sets the value.*/
    strcpy(player->texture[line], str);
    return OK;
}

Status player_destroy(Player *player)
{
    /*Error management*/
    if (player == NULL)
    {
        return ERROR;
    }

    /*Frees the memory*/
    inventory_destroy(player->inventory);
    free(player->__texture);
    free(player);
    return OK;
}

Status player_set_player_name(Player *player, char name[PLAYER_NAME_SIZE])
{
    /*Error management*/
    if (player == NULL || name == NULL)
    {
        return ERROR;
    }

    /*Copy of the values*/
    if (!strcpy(player->player_name, name))
    {
        return ERROR;
    }

    return OK;
}

Status player_set_player_location(Player *player, Id id)
{
    /*Error management*/
    if (player == NULL || id == NO_ID || id == ID_ERROR)
    {
        return ERROR;
    }

    /*Copy of the values*/
    player->player_location = id;
    return OK;
}

Status player_add_object(Player *player, Id object)
{
    /*Error management*/
    if (player == NULL || object <= NO_ID)
    {
        return ERROR;
    }

    return inventory_add(player->inventory, object);
}

int player_get_n_objects(Player *player)
{
    /*Error handling.*/
    if (!player)
        return FUNCTION_ERROR;

    /*Returns the value.*/
    return inventory_len(player->inventory);
}

char *player_get_gdesc(Player *player)
{
    /*Error handling.*/
    if (!player)
        return NULL;
    /*Returns the string.*/
    return player->gdesc;
}

Status player_set_gdesc(Player *player, char *gdesc)
{
    /*Error handling.*/
    if (!player || !gdesc || strlen(gdesc) >= MAX_GDESC)
        return ERROR;
    /*Sets the value.*/
    strcpy(player->gdesc, gdesc);
    return OK;
}

Id player_get_player_id(Player *player)
{
    /*Error management*/
    if (player == NULL)
    {
        return ID_ERROR;
    }

    return player->player_id;
}

char *player_get_player_name(Player *player)
{
    /*Error management.*/
    if (player == NULL)
    {
        return NULL;
    }

    return player->player_name;
}

Id player_get_player_location(Player *player)
{
    /*Error management.*/
    if (player == NULL)
    {
        return ID_ERROR;
    }

    return player->player_location;
}

Id *player_get_inventory(Player *player)
{
    /*Error management.*/
    if (player == NULL)
    {
        return NULL;
    }

    return inventory_get_content(player->inventory);
}

int player_get_health(Player *player)
{
    /*Error management.*/
    if (!player)
        return FUNCTION_ERROR;

    /*Returns the health data.*/
    return player->health;
}

Bool player_has_object(Player *player, Id object)
{
    /*Error handling.*/
    if (!player || object <= NO_ID)
    {
        return FALSE;
    }

    /*Searches for the object.*/
    return (inventory_find(player->inventory, object) == NO_POSITION ? FALSE : TRUE);
}

Status player_set_inventory_capacity(Player *player, long capacity)
{
    /*Error handling.*/
    if (!player)
        return ERROR;
    /*Sets the value.*/
    return inventory_set_max_objs(player->inventory, capacity);
}

long player_get_inventory_capacity(Player *player)
{
    /*Error handling.*/
    if (!player)
        return FUNCTION_ERROR;
    /*Returns the value.*/
    return inventory_get_max_objs(player->inventory);
}

Status player_del_object(Player *player, Id object)
{
    /*Error handling.*/
    if (!player || object <= NO_ID)
        return ERROR;
    return (inventory_take(player->inventory, object) == object ? OK : ERROR);
}

Status player_set_health(Player *player, int health)
{
    /*Error management.*/
    if (!player)
        return ERROR;

    /*Sets the value.*/
    player->health = health;

    /*Clean exit.*/
    return OK;
}

Status player_print(Player *player)
{
    /* Error Management.*/
    if (!player)
    {
        return ERROR;
    }

    /* 1. Print the id and the name of the player.*/
    fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->player_id, player->player_name);

    /* 2. Print the id of the place the player is at.*/
    fprintf(stdout, "--> Player in the space with id number %ld \n", player->player_location);

    /* 3. Print the information about the object.*/
    if (player->inventory)
    {
        fprintf(stdout, "Player inventory: \n");
        inventory_print(player->inventory);
    }
    return OK;
}
