/**
 * @brief It implements the character module.
 *
 * @file character.c
 * @author Fernando Mijangos
 * @version 2
 * @date 23-03-2025
 * @copyright GNU Public License
 */

#include "character.h"
#include "types.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20      /*!<Max name length.*/
#define MAX_DESC 7       /*!<Max description line.*/
#define MAX_MESSAGE 100  /*!<Max message length.*/
#define NO_HEALTH 0      /*!<No health value.*/
#define FIRST_CHAR 0     /*!<Position number 0 of a string, used to intitialize things*/
#define STOP_CHARACTER 1 /*!Size of the \0, cause we need to include it*/

/**
 * Character TAD.
 */
struct _Character
{
    Id id;                                  /*!< Id of the character.*/
    char name[MAX_NAME];                    /*!< Name of the character.*/
    char description[MAX_DESC];             /*!< Description of the character.*/
    Bool friendly;                          /*!< Whether the character is friendly or not.*/
    char message[MAX_MESSAGE];              /*!< Message of the character.*/
    int health;                             /*!< Amount of health of the character.*/
    Id follow;                              /*!< Id of the character it follows.*/
    char *texture[CHARACTER_TEXTURE_LINES]; /*!< Strings which create the texture of the character.*/
    char *__texture_data;                   /*!< Actual matrix with the texture.*/
};

Character *character_create(Id id)
{
    Character *character = NULL;
    int i;
    /*Error management.*/
    if (id <= NO_ID)
        return NULL;

    /*Memory allocation.*/
    if (!(character = (Character *)malloc(sizeof(Character))))
    {
        return NULL;
    }

    /*Establishes the values to default ones.*/
    character->id = id;
    character->name[FIRST_CHAR] = '\0';
    character->description[FIRST_CHAR] = '\0';
    character->friendly = FALSE;
    character->message[FIRST_CHAR] = '\0';
    character->follow = NO_ID;
    character->health = NO_HEALTH;
    character->__texture_data = (char *)calloc(CHARACTER_TEXTURE_SIZE * CHARACTER_TEXTURE_LINES, sizeof(char));
    if (!character->__texture_data)
    {
        free(character);
        return NULL;
    }
    for (i = 0; i < CHARACTER_TEXTURE_LINES; i++)
    {
        character->texture[i] = &(character->__texture_data[i * CHARACTER_TEXTURE_SIZE]);
    }
    /*Clean exit.*/
    return character;
}

void character_destroy(Character *character)
{
    /*Error management.*/
    if (character)
    {
        free(character->__texture_data);
        free(character);
    }
}

Status character_set_texture_line(Character *character, int line, char *str)
{
    /*Error handling.*/
    if (!character || line < 0 || line >= CHARACTER_TEXTURE_LINES || !str)
    {
        return ERROR;
    }
    /*Sets the value.*/
    strncpy(character->texture[line], str, CHARACTER_TEXTURE_SIZE);
    /*Adds a \0 in case the string is to long*/
    character->texture[line][CHARACTER_TEXTURE_SIZE - STOP_CHARACTER] = '\0';
    return OK;
}

char *character_get_texture_line(Character *character, int line)
{
    /*Error handling.*/
    if (!character || line < 0 || line >= CHARACTER_TEXTURE_LINES)
    {
        return NULL;
    }
    /*Returns the value.*/
    return character->texture[line];
}

Id character_get_id(Character *character)
{
    /*Error handling.*/
    if (!character)
    {
        return ID_ERROR;
    }
    /*Returns the value.*/
    return character->id;
}

Status character_set_name(Character *character, char *name)
{
    /*Error management.*/
    if (!character || !name)
    {
        return ERROR;
    }
    /*Sets the value.*/
    strncpy(character->name, name, MAX_NAME);
    character->name[MAX_NAME - STOP_CHARACTER] = '\0';
    return OK;
}

char *character_get_name(Character *character)
{
    return (character ? character->name : NULL);
}

Status character_set_description(Character *character, char *description)
{
    /*Error management.*/
    if (!character || !description)
    {
        return ERROR;
    }

    /*Sets the value.*/
    strncpy(character->description, description, MAX_DESC);
    character->description[MAX_DESC - STOP_CHARACTER] = '\0';

    return OK;
}

char *character_get_description(Character *character)
{
    return (character ? character->description : NULL);
}

Status character_set_friendly(Character *character, Bool value)
{
    /*Error management.*/
    if (!character || (value != TRUE && value != FALSE))
    {
        return ERROR;
    }

    /*Sets the value.*/
    character->friendly = value;

    /*Clean exit.*/
    return OK;
}

Bool character_get_friendly(Character *character)
{
    return (character ? character->friendly : FALSE);
}

Status character_set_message(Character *character, char *message)
{
    /*Error management.*/
    if (!character || !message)
    {
        return ERROR;
    }

    /*Sets the value.*/
    strncpy(character->message, message, MAX_MESSAGE);
    character->message[MAX_MESSAGE - STOP_CHARACTER] = '\0';

    return OK;
}

char *character_get_message(Character *character)
{
    return (character ? character->message : NULL);
}

Status character_set_health(Character *character, int health)
{
    /*Error handling.*/
    if (!character)
    {
        return ERROR;
    }

    /*Sets the value.*/
    character->health = health;
    return OK;
}

int character_get_health(Character *character)
{
    return (character ? character->health : FUNCTION_ERROR);
}

Status character_set_follow(Character *character, Id player)
{
    /*Error handling.*/
    if (!character || player == ID_ERROR)
    {
        return ERROR;
    }

    /*Sets the value.*/
    character->follow = player;
    return OK;
}
Id character_get_follow(Character *character)
{
    /*Error handling.*/
    if (!character)
    {
        return ID_ERROR;
    }
    /*Returns the value.*/
    return character->follow;
}

Status character_print(Character *character)
{
    /*Error management.*/
    if (!character)
    {
        return ERROR;
    }

    /* 1-Print the id and name of the character.*/
    fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);

    /*2-Print the description of the character and its message.*/
    fprintf(stdout, "--> Character description (\"%s\")\n", character->description);
    fprintf(stdout, "--> Character message (\"%s\")\n", character->message);

    /*3-Printf the extra information of the character.*/
    fprintf(stdout, "--> Character state(0=enemy, 1=friendly): %d \n", character->friendly);
    fprintf(stdout, "--> Character follow: (Id: %ld) \n", character->follow);
    return OK;
}
