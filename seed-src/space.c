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
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
    Id id;                    /*!< Id number of the space, it must be unique. */
    char name[WORD_SIZE + 1]; /*!< Name of the space. */
    Id north;                 /*!< Id of the space at the north. */
    Id south;                 /*!< Id of the space at the south. */
    Id east;                  /*!< Id of the space at the east. */
    Id west;                  /*!< Id of the space at the west. */
    Set *objects;              /*!< A set with the objects the space has */
    char *gdesc[5];           /*!< Strings which create the space's graphic description. */
    char *__gdesc_data;       /*!< Actual matrix with the gdesc.*/
};

/** space_create allocates memory for a new space
 *  and initializes its members.
 */
Space *space_create(Id id)
{
    Space *newSpace = NULL;
    int i = 0;

    /* Error control.*/
    if (id == NO_ID)
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
    newSpace->north = NO_ID;
    newSpace->south = NO_ID;
    newSpace->east = NO_ID;
    newSpace->west = NO_ID;
    newSpace->objects = set_create();

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
        if(space->objects)
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
        return NO_ID;
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

Status space_set_north(Space *space, Id id)
{
    /*Error handling.*/
    if (!space || id == NO_ID)
    {
        return ERROR;
    }
    /*Sets the value.*/
    space->north = id;
    return OK;
}

Id space_get_north(Space *space)
{
    /*Error handling.*/
    if (!space)
    {
        return NO_ID;
    }
    /*Returns the value.*/
    return space->north;
}

Status space_set_south(Space *space, Id id)
{
    /*Error handling.*/
    if (!space || id == NO_ID)
    {
        return ERROR;
    }
    /*Gets the value.*/
    space->south = id;
    return OK;
}

Id space_get_south(Space *space)
{
    /*Error handling.*/
    if (!space)
    {
        return NO_ID;
    }
    /*Returns the value.*/
    return space->south;
}

Status space_set_east(Space *space, Id id)
{
    /*Error handling.*/
    if (!space || id == NO_ID)
    {
        return ERROR;
    }
    /*Sets the value.*/
    space->east = id;
    return OK;
}

Id space_get_east(Space *space)
{
    /*Error handling.*/
    if (!space)
    {
        return NO_ID;
    }
    /*Returns the value.*/
    return space->east;
}

Status space_set_west(Space *space, Id id)
{
    /*Error handling.*/
    if (!space || id == NO_ID)
    {
        return ERROR;
    }
    /*Sets the value.*/
    space->west = id;
    return OK;
}

Id space_get_west(Space *space)
{
    /*Error handling.*/
    if (!space)
    {
        return NO_ID;
    }
    return space->west;
}


Set *space_get_objects(Space *space)
{
    /*Error handling.*/
    if (!space)
    {
        return NULL;
    }
    return space->objects;
}

Status space_add_object(Space* space, Id object)
{
    if(!space||object==NO_ID)
    {
        return ERROR;
    }
    return((set_add(space->objects, object))?OK :ERROR);
}

int space_find_object(Space* space, Id object)
{
    if(!space||object==NO_ID)
    {
        return 0;
    }
    return set_find(space->objects, object);
}

Id space_take_object(Space* space, Id object)
{
    if(!space||object==NO_ID)
    {
        return ERROR;
    }
    return set_take(space->objects, object);
}

Status space_print(Space *space)
{
    Id idaux = NO_ID;
    Set *set_aux= NULL;
    int i = 0;

    /* Error Control */
    if (!space)
    {
        return ERROR;
    }

    /* 1. Print the id and the name of the space */
    fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

    /* 2. For each direction, print its link */
    idaux = space_get_north(space);
    if (idaux != NO_ID)
    {
        fprintf(stdout, "---> North link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No north link.\n");
    }
    idaux = space_get_south(space);
    if (idaux != NO_ID)
    {
        fprintf(stdout, "---> South link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No south link.\n");
    }
    idaux = space_get_east(space);
    if (idaux != NO_ID)
    {
        fprintf(stdout, "---> East link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No east link.\n");
    }
    idaux = space_get_west(space);
    if (idaux != NO_ID)
    {
        fprintf(stdout, "---> West link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No west link.\n");
    }

    /* 3. Prints the set of objects the space has*/
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

    return OK;
}