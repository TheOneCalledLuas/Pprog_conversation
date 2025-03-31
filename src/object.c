/**
 * @brief It implements the object functionality.
 *
 * @file object.c
 * @author Saúl López Romero
 * @version 2
 * @date 01-02-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRIPTION 64 /*Maximun word description.*/

/**
 * @brief Object
 *
 * Object structure with all the relevant information regarding the object.
 */
struct _Object
{
    Id id;                    /*!< Id of the object, it must be unique. */
    char name[WORD_SIZE + 1]; /*!< Object name. */
    char *description;        /*!< Object description.*/
};

Object *object_create(Id id)
{
    Object *object = NULL;

    /*Checks that the id is at least valid.*/
    if (id <= 0)
    {
        return NULL;
    }

    /*Allocates memory and checks if it goes alright.*/
    object = (Object *)malloc(sizeof(Object));
    if (!object)
    {
        return NULL;
    }

    /*Allocates memory for the description.*/
    object->description = (char *)calloc(MAX_DESCRIPTION, sizeof(char));
    if (!object->description)
    {
        free(object);
        return NULL;
    }

    /*Sets the vaues to default ones and establishes the id.*/
    object->id = id;
    object->name[0] = '\0';
    object->description[0] = '\0';

    /*Clean exit.*/
    return object;
}

Status object_destroy(Object *object)
{

    /*Checks the arguments.*/
    if (!object)
    {
        return ERROR;
    };

    /*Frees the memory.*/
    free(object->description);
    free(object);

    /*Clean exit.*/
    return OK;
}

char *object_get_description(Object *object)
{
    /*Checks the arguemnts*/
    if (!object)
    {
        return NULL;
    }

    /*Returns the value.*/
    return object->description;
}

Status object_set_description(Object * object, char * desc) {
    /*Checks the arguemnts*/
    if (!object || !desc || strlen(desc) >= MAX_DESCRIPTION)
    {
        return ERROR;
    }

    /*Sets the value.*/
    strcpy(object->description,desc);
    return OK;
}

char *object_get_name(Object *object)
{
    /*Checks the arguments.*/
    if (!object)
    {
        return ERROR;
    }

    /*Returns a pointer to the object's name.*/
    return object->name;
}

Status object_set_name(Object *object, char *name)
{
    /*Checks the arguments.*/
    if (!object || !name)
    {
        return ERROR;
    }

    /*Sets the name.*/
    if (!(strcpy(object->name, name)))
    {
        return ERROR;
    }

    /*Clean exit.*/
    return OK;
}

Id object_get_id(Object *object)
{
    /*Checks the arguments.*/
    if (!object)
    {
        return ID_ERROR;
    }

    /*Returns the id.*/
    return object->id;
}

Status object_print_info(Object *object)
{
    /*Checks the arguments.*/
    if (!object)
    {
        return ERROR;
    }

    /*Prints the info.*/
    fprintf(stdout, "%s : %ld", object->name, object->id);

    /*Clean exit.*/
    return OK;
}