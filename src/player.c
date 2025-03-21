/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Fernando Mijangos, Saúl López Romero.
 * @version 3
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#include "player.h"
#include "object.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GDESC 10

/**
 * @brief Player
 *
 * It stores all the information related to a player.
 */
struct _Player
{
    Id player_id;                       /*!< Id of the player.*/
    char player_name[PLAYER_NAME_SIZE]; /*!< Name of the player.*/
    Id player_location;                 /*!< id of the space where the player is at.*/
    Id object;                          /*!< Id of the object the player has.*/
    int health;                         /*!< Health points the player has.*/
    char gdesc[MAX_GDESC];              /*!< Graphic description for the player.*/
};

Player *player_create(Id id)
{
    Player *player;

    /*Allocation of memory for player and error management*/
    player = (Player *)malloc(sizeof(Player));
    if (player == NULL)
    {
        return NULL;
    }

    /*Initialization of the values*/
    player->player_id = id;
    player->player_name[0] = '\0';
    player->player_location = NO_ID;
    player->object = NO_ID;
    player->health = 20;

    return player;
}

Status player_destroy(Player *player)
{
    /*Error management*/
    if (player == NULL)
    {
        return ERROR;
    }

    /*Free the memory*/

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

Status player_set_object(Player *player, Id object)
{
    /*Error management*/
    if (player == NULL)
    {
        return ERROR;
    }

    /*Copy of the values*/
    player->object = object;
    return OK;
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
    strcpy(player->gdesc,gdesc);
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

Id player_get_object(Player *player)
{
    /*Error management.*/
    if (player == NULL)
    {
        return ID_ERROR;
    }

    return player->object;
}

int player_get_health(Player *player)
{
    /*Error management.*/
    if (!player)
        return -1;

    /*Returns the health data.*/
    return player->health;
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
    if (player->object)
    {
        fprintf(stdout, "--> Player has the object with id %ld \n", player->object);
    }
    else
    {
        fprintf(stdout, "--> Player does't have the object\n");
    }
    return OK;
}
