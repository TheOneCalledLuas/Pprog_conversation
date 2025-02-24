/**
 * @brief It implements the character module
 *
 * @file space.c
 * @author Fernando Mijangos
 * @version 1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"
#define MAX_NAME 20
#define MAX_DESC 6
#define MAX_MESSAGE 100

typedef struct _Character Character;

Status character_create(Character *character);

Status character_destroy(Character *character);

Status character_set_id(Character *character, Id id);

Id character_get_id(Character *character);

Status character_set_name(Character *character, char* name);

char *character_get_name(Character *character);

Status character_set_description(Character *character, char* description);

char *character_get_description(Character *character);

Status character_set_location(Character *character, Id space);

Id character_get_location(Character *character);

Status character_set_friendly(Character *character, Bool value);

Bool character_get_friendly(Character *character);

Status character_set_message(Character *character, char* message);

char *character_get_message(Character *character);


#endif