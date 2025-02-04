#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_NAME_SIZE 30

#include "types.h"

typedef struct _Player Player;

Player *player_create(Id id);

Status player_destroy(Player* player);

Status player_set_player_name(Player* player, char name[PLAYER_NAME_SIZE]);

Status player_set_player_location(Player* player, Id id);

Status player_set_objects_id(Player* player, Id id);

Id player_get_player_id(Player* player);

char *player_get_player_name(Player* player);

Id player_get_player_location(Player* player);

Id player_get_object_id(Player* player);

#endif