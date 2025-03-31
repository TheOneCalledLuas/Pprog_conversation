/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Fernando Mijangos && Saul Lopez
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"
#include "object.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Number of graphic description lines.
*/
#define G_DESC_LINES 5

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
    Id id;                     /*!< Id number of the space, it must be unique. */
    char name[WORD_SIZE + 1];  /*!< Name of the space. */
    Set *objects;              /*!< A set with the objects the space has */
    char *gdesc[G_DESC_LINES]; /*!< Strings which create the space's graphic description. */
    char *__gdesc_data;        /*!< Actual matrix with the gdesc.*/
    Id character;              /*!< Character id.*/
    Bool discovered;           /*!< True if visited, False if never visited.*/
};

Space *space_create(Id id)
{
    Space *newSpace = NULL;
    int i = 0;

    /* Error control.*/
    if (id == NO_ID || id == ID_ERROR)
        return NULL;
    /*Allocates memory for the space.*/
    newSpace = (Space *)malloc(sizeof(Space));
    if (newSpace == NULL)
    {
        return NULL;
    }

    /*Initialization of an empty space.*/
    newSpace->id = id;
    newSpace->name[0] = '\0';
    newSpace->objects = set_create();
    newSpace->character = NO_ID;
    newSpace->discovered = FALSE;

    /*Initialisation of gdesc. I chose to do it this way because if
      we manage to get a decent amount of spaces, storing them in the
      stack will definitely be a potencial problem.*/
    if (!(newSpace->__gdesc_data = (char *)calloc(50, sizeof(char))))
    {
        free(newSpace);
        return NULL;
    }
    /*Sets the array so that it's more accesible.*/
    for (i = 0; i < 5; i++)
    {
        newSpace->gdesc[i] = &(newSpace->__gdesc_data[i * 10]);
    }

    return newSpace;
}

void space_destroy(Space *space)
{

    /*Frees the memory.*/
    if (space)
    {
        if (space->__gdesc_data)
            free(space->__gdesc_data);
        if (space->objects)
        {
            set_destroy(space->objects);
        }
        free(space);
    }
}

char *space_get_gdesc_line(Space *space, int line)
{
    /*Error handling*/
    if (!space || line < 0 || line > 4)
        return NULL;

    /*Returns the line.*/
    return space->gdesc[line];
}

Status space_set_gdesc_line(Space *space, int line, char *str)
{
    /*Error handling*/
    if (!space || line < 0 || line > 4 || !str || strlen(str) != 9)
        return ERROR;

    /*Sets the line.*/
    strcpy(space->gdesc[line], str);

    /*Clean Exit.*/
    return OK;
}

Id space_get_id(Space *space)
{
    /*Error handling.*/
    if (!space)
    {
        return ID_ERROR;
    }
    /*Returns the value.*/
    return space->id;
}

Status space_set_name(Space *space, char *name)
{
    /*Error handling.*/
    if (!space || !name)
    {
        return ERROR;
    }

    /*Sets the name.*/
    if (!strcpy(space->name, name))
    {
        return ERROR;
    }
    return OK;
}

const char *space_get_name(Space *space)
{
    /*Error handling.*/
    if (!space)
    {
        return NULL;
    }
    /*Returns the value.*/
    return space->name;
}

Id *space_get_objects(Space *space)
{
    Id *set_objects;
    if (!space)
    {
        return NULL;
    }
    /*Error handling.*/
    if (!(set_objects = set_get_content(space->objects)))
    {
        return NULL;
    }
    return set_objects;
}

Status space_add_object(Space *space, Id object)
{
    if (!space || object == NO_ID || object == ID_ERROR)
    {
        return ERROR;
    }
    return ((set_add(space->objects, object)) ? OK : ERROR);
}

int space_find_object(Space *space, Id object)
{
    if (!space || object == NO_ID || object == ID_ERROR)
    {
        return -1;
    }
    return set_find(space->objects, object);
}

Id space_take_object(Space *space, Id object)
{
    if (!space || object == NO_ID || object == ID_ERROR)
    {
        return ID_ERROR;
    }
    return set_take(space->objects, object);
}

Id space_get_character(Space *space)
{
    /*Error handling.*/
    if (!space)
        return ID_ERROR;

    /*Returns the value.*/
    return space->character;
}

int space_get_n_objects(Space *space)
{
    return (!space ? -1 : set_len(space->objects));
}

Status space_set_character(Space *space, Id id)
{
    /*Error handling.*/
    if (!space || id == ID_ERROR)
    {
        return ERROR;
    }

    /*Sets the value.*/
    space->character = id;

    /*Clean exit.*/
    return OK;
}

Bool space_is_discovered(Space *space)
{
    /*Error management and returns the condition.*/
    return (space ? space->discovered : FALSE);
}

Status space_set_discovered(Space *space, Bool value)
{
    /*Error managment*/
    if (!space)
        return ERROR;

    /*Sets the value*/
    space->discovered = value;
    return OK;
}

Status space_print(Space *space)
{
    Set *set_aux = NULL;
    int i = 0;

    /* Error Control */
    if (!space)
    {
        return ERROR;
    }

    /* 1. Print the id and the name of the space */
    fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

    /* 2. Prints the set of objects the space has*/
    set_aux = space->objects;
    if (set_aux)
    {
        set_print(set_aux);
    }
    else
    {
        fprintf(stdout, "---> No object in the space.\n");
    }

    /* 4. Print the graphic description of the space.*/
    fprintf(stdout, "Graphic description: \n");
    for (i = 0; i < 5; i++)
    {
        fprintf(stdout, "%s\n", space->gdesc[i]);
    }

    /*5. Prints whether the space has been visited or not*/
    fprintf(stdout, "Space discovered: %s \n", (space->discovered == TRUE ? "TRUE" : "FALSE"));

    return OK;
}