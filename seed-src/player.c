#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Player
{
    Id player_id;                           /*!< Id of the player*/
    char player_name[PLAYER_NAME_SIZE];     /*!< Name of the player*/
    Id player_location;                     /*!< id of the space where the player is at*/
    Id object_id;                           /*!< id of the object the player has*/
};

Player *player_create(Id id)
{
    Player *player;
    player = (Player*)malloc(sizeof(Player));
    if(player==NULL)
    {
        return NULL;
    }
    player->player_id = id;
    player->player_name[0] = '\0';
    player->player_location = NO_ID;
    player->object_id = NO_ID;
    return player;
}

Status player_destroy(Player* player)
{
    if(player==NULL)
    {
        return ERROR;
    }
    free(player);
    return OK;
}

Status player_set_player_name(Player* player, char name[PLAYER_NAME_SIZE])
{
    if(player==NULL || name == NULL)
    {
        return ERROR;
    }
    if (!strcpy(player->player_name ,name))
    {
        return ERROR;
    }
    return OK;
}

Status player_set_player_location(Player* player, Id id)
{
    if(player==NULL)
    {
        return ERROR;
    }
    player->player_location = id;
    return OK;
}

Status player_set_object_id(Player* player, Id id)
{
    if(player==NULL)
    {
        return ERROR;
    }
    player->object_id=id;
    return OK;
}

Id player_get_player_id(Player* player)
{
    if(player==NULL)
    {
        return NO_ID;
    }
    return player->player_id;
}

char *player_get_player_name(Player* player)
{
    if(player==NULL)
    {
        return NULL;
    }
    return player->player_name;
}

Id player_get_player_location(Player* player)
{
    if(player==NULL)
    {
        return NO_ID;
    }
    return player->player_location;
}

Id player_get_objects_id(Player* player)
{
    if(player==NULL)
    {
        return NO_ID;
    }
    return player->object_id;
}
