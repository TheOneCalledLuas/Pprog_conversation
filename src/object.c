/**
 * @brief It implements the object functionality.
 *
 * @file object.c
 * @author Saúl López Romero, Irene García
 * @version 2
 * @date 01-02-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Maximun word description.*/
#define MAX_DESCRIPTION 64
#define MAX_NAME 64 /*!< Max name length.*/

/**
 * @brief Object
 *
 * Object structure with all the relevant information regarding the object.
 */
struct _Object
{
    Id id;                               /*!< Id of the object, it must be unique. */
    char name[WORD_SIZE + 1];            /*!< Object name. */
    char *description;                   /*!< Object description.*/
    int health;                          /*!< Determines the amount of health the object gives or takes.*/
    Bool movable;                        /*!< Determines wether a object can be moved or not.*/
    Id dependency;                       /*!< Determines if the object needs another object to be taken.*/
    Id open;                             /*!< Determines if the object can open a link.*/
    Bool is_used;                        /*!< Determines if the object is used or not. */
    Bool special_use;                    /*!< Determines if the object is used in a special way, gamerule intended.*/
    char *texture[OBJECT_TEXTURE_LINES]; /*!< Strings which create the texture of the space*/
    char *__texture_data;                /*!< Actual matrix with the texture*/
};

Object *object_create(Id id)
{
    Object *object = NULL;
    int i = 0;

    /*Checks that the id is at least valid.*/
    if (id == NO_ID || id == ID_ERROR)
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
    object->health = 0;
    object->movable = FALSE;
    object->dependency = NO_ID;
    object->open = NO_ID;
    object->is_used = FALSE;
    object->special_use = FALSE;
    /*Allocates memory for the textures.*/
    if (!(object->__texture_data = (char *)calloc(OBJECT_TEXTURE_LINES * OBJECT_TEXTURE_SIZE, sizeof(char))))
    {
        free(object->description);
        free(object);
        return NULL;
    }
    /*Sets the array so that it's more accesible.*/
    for (i = 0; i < OBJECT_TEXTURE_LINES; i++)
    {
        object->texture[i] = &(object->__texture_data[i * OBJECT_TEXTURE_SIZE]);
    }

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
    free(object->__texture_data);
    free(object);

    /*Clean exit.*/
    return OK;
}

Status object_set_special_use(Object *object, Bool special_use)
{
    /*Checks the arguments.*/
    if (!object || (special_use != TRUE && special_use != FALSE))
    {
        return ERROR;
    }

    /*Sets the value. */
    object->special_use = special_use;

    /*Clean exit.*/
    return OK;
}

Bool object_get_special_use(Object *object)
{
    /*Checks the arguments.*/
    if (!object)
    {
        return FALSE;
    }

    /*Returns the value. */
    return object->special_use;
}

Status object_set_is_used(Object *object, Bool is_used)
{
    /*Checks the arguments.*/
    if (!object || (is_used != TRUE && is_used != FALSE))
    {
        return ERROR;
    }

    /*Sets the value. */
    object->is_used = is_used;

    /*Clean exit.*/
    return OK;
}

Bool object_get_is_used(Object *object)
{
    /*Checks the arguments.*/
    if (!object)
    {
        return FALSE;
    }

    /*Returns the value. */
    return object->is_used;
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

Status object_set_description(Object *object, char *desc)
{
    /*Checks the arguemnts*/
    if (!object || !desc || strlen(desc) >= MAX_DESCRIPTION)
    {
        return ERROR;
    }

    /*Sets the value.*/
    strcpy(object->description, desc);
    return OK;
}

Status object_set_texture_line(Object *object, int line, char *str)
{
    /*Checks the arguments.*/
    if (!object || line < 0 || line > OBJECT_TEXTURE_LINES - 1 || !str || strlen(str) != OBJECT_TEXTURE_SIZE - 1)
    {
        return ERROR;
    }

    /*Sets the line.*/
    strcpy(object->texture[line], str);

    /*Clean exit.*/
    return OK;
}

char *object_get_texture_line(Object *object, int line)
{
    /*Checks the arguments.*/
    if (!object || line < 0 || line > OBJECT_TEXTURE_LINES - 1)
    {
        return NULL;
    }

    /*Returns the line.*/
    return object->texture[line];
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
    if (!object || !name || strlen(name) >= MAX_NAME)
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

Status object_set_health(Object *object, int health)
{
    /*Error handling.*/
    if (!object)
    {
        return ERROR;
    }
    object->health = health;

    return OK;
}

int object_get_health(Object *object)
{
    /*Error handling.*/
    if (!object)
    {
        return ERROR;
    }

    return object->health;
}

Status object_set_movable(Object *object, Bool movable)
{
    /*Error handling.*/
    if (!object || (movable != TRUE && movable != FALSE))
    {
        return ERROR;
    }
    object->movable = movable;

    return OK;
}

Bool object_get_movable(Object *object)
{
    return (object ? object->movable : FALSE);
}

Status object_set_dependency(Object *object, Id dependency)
{
    /*Error handling.*/
    if (!object || dependency <= ID_ERROR)
    {
        return ERROR;
    }

    /*Sets the value.*/
    object->dependency = dependency;
    return OK;
}

Id object_get_dependency(Object *object)
{
    /*Error handling.*/
    if (!object)
    {
        return ID_ERROR;
    }
    /*Returns the value.*/
    return object->dependency;
}

Status object_set_open(Object *object, Id open)
{
    /*Error handling.*/
    if (!object || open <= ID_ERROR)
    {
        return ERROR;
    }

    /*Sets the value.*/
    object->open = open;
    return OK;
}

Id object_get_open(Object *object)
{
    /*Error handling.*/
    if (!object)
    {
        return ID_ERROR;
    }
    /*Returns the value.*/
    return object->open;
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
