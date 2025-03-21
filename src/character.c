/**
 * @brief It implements the character module.
 *
 * @file character.c
 * @author Fernando Mijangos
 * @version 2
 * @date 23-02-2025
 * @copyright GNU Public License
 */

#include "character.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_DESC 7
#define MAX_MESSAGE 100

struct _Character
{
    Id id;                      /*!< Id of the character.*/
    char name[MAX_NAME];        /*!< Name of the character.*/
    char description[MAX_DESC]; /*!< Description of the character.*/
    Bool friendly;              /*!< Whether the character is friendly or not.*/
    char message[MAX_MESSAGE];  /*!< Message of the character.*/
    int health;                 /*!< Amount of health of the character.*/
};

Character *character_create(Id id)
{
    Character *character = NULL;
    /*Error management.*/
    if (id < 0)
        return NULL;

    /*Memory allocation.*/
    if (!(character = (Character *)malloc(sizeof(Character))))
    {
        return NULL;
    }

    /*Establishes the values to default ones.*/
    character->id = id;
    character->name[0] = '\0';
    character->description[0] = '\0';
    character->friendly = FALSE;
    character->message[0] = '\0';
    /*Clean exit.*/
    return character;
}

void character_destroy(Character *character)
{
    /*Error management.*/
    if (character)
    {
        free(character);
    }
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
    character->name[MAX_NAME-1]='\0';
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
    character->description[MAX_DESC-1]='\0';

    return OK;
}

char *character_get_description(Character *character)
{
    return (character ? character->description : NULL);
}

Status character_set_friendly(Character *character, Bool value)
{
    /*Error management.*/
    if (!character || (value !=TRUE && value != FALSE))
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
    character->message[MAX_MESSAGE-1]='\0';

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
    return (character ? character->health : -1);
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

    return OK;
}
