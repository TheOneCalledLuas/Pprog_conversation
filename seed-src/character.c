/**
 * @brief It implements the character module
 *
 * @file space.c
 * @author Fernando Mijangos
 * @version 1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "character.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Character
{
    Id id;                                 /*!< Id of the character.*/
    char name[MAX_NAME];                   /*!< Name of the character.*/
    char description[MAX_DESC];            /*!< Description of the character.*/
    Id location;                           /*!< Location of the character.*/
    Bool friendly;                         /*!< Whether the character is friendly or not.*/
    char message[MAX_MESSAGE];             /*!< Message of the character.*/
};

Status character_create(Character *character)
{
    /*Error management*/
    if(!character)
    {
        return ERROR;
    }
    if(!(character=(Character*)malloc(sizeof(Character))))
    {
        return ERROR;
    }
    character->id = NO_ID;
    character->name[0] = '\0';
    character->description[0] = '\0';
    character->location = NO_ID;
    character->friendly = FALSE;
    character->message[0] = '\0';
    return OK;
}

Status character_destroy(Character *character)
{
    /*Error management*/
    if(!character)
    {
        return ERROR;
    }
    free(character);
    character=NULL;
    return OK;
}

Status character_set_id(Character *character, Id id)
{
    /*Error management*/
    if(!character)
    {
        return ERROR;
    }
    character->id=id;
    return OK;
}

Id character_get_id(Character *character)
{
    return(character?character->id:NO_ID);
}

Status character_set_name(Character *character, char* name)
{
    /*Error management*/
    if(!character || !name)
    {
        return ERROR;
    }
    strncpy(character->name, name, MAX_NAME);
    character->name[MAX_NAME]='\0';
    return OK;
}

char *character_get_name(Character *character)
{
    return(character?character->name:NULL);
}

Status character_set_description(Character *character, char* description)
{
    /*Error management*/
    if(!character || !description)
    {
        return ERROR;
    }
    strncpy(character->description, description, MAX_DESC);
    character->description[MAX_DESC]='\0';
    return OK;
}

char *character_get_description(Character *character)
{
    return(character?character->description:NULL);
}

Status character_set_location(Character *character, Id space)
{
    /*Error management*/
    if(!character)
    {
        return ERROR;
    }
    character->location=space;
    return OK;
}

Id character_get_location(Character *character)
{
    return(character?character->location:NO_ID);
}

Status character_set_friendly(Character *character, Bool value)
{
    /*Error management*/
    if(!character)
    {
        return ERROR;
    }
    character->friendly=value;
    return OK;
}

Bool character_get_friendly(Character *character)
{
    return(character?character->friendly:FALSE);
}

Status character_set_message(Character *character, char* message)
{
    /*Error management*/
    if(!character || !message)
    {
        return ERROR;
    }
    strncpy(character->message, message, MAX_MESSAGE);
    character->message[MAX_MESSAGE]='\0';
    return OK;
}

char *character_get_message(Character *character)
{
    return(character?character->message:NULL);
}

Status character_print(Character *character)
{
    if(!character)
    {
        return ERROR;
    }

    /* 1-Print the id and name of the character*/
    fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);

    /*2-Print the description of the character and its message*/
    fprintf(stdout, "--> Character description (\"%s\")\n", character->description);
    fprintf(stdout, "--> Character message (\"%s\")\n", character->message);
    
    /*3-Printf the extra information of the character*/
    fprintf(stdout, "-->Character state(0=enemy, 1=friendly): %d \n", character->friendly);
    fprintf(stdout, "-->Character loction: %ld \n", character->location);

    return OK;
}
