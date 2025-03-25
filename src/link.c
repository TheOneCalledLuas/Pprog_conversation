/**
 * @brief It implements the link module
 *
 * @file link.c
 * @author Fernando Mijangos
 * @version 1
 * @date 21-03-2025
 * @copyright GNU Public License
 */
#include <stdlib.h>
#include <stdio.h>

#include "link.h"
#include "types.h"

struct _link
{
    Id id;               /*!< Id of the link.*/
    char name[MAX_NAME]; /*!< Name of the link.*/
    Id origin;           /*!< Id of the space of origin.*/
    Id destination;      /*!< Id of the space of destination.*/
    Direction direction; /*!< Direction to where the link points.*/
    Bool state;          /*!< TRUE if the link is open FALSE if not.*/
};

Link *link_create(Id id)
{
    Link *link;

    /*Error management.*/
    if (id == NO_ID || id == ID_ERROR)
        return NULL;

    /*Memory allocation.*/
    if (!(link = (Link *)malloc(sizeof(link))))
        return NULL;

    /*Initializes the variables.*/
    link->id = id;
    link->name[0] = '\0';
    link->origin = NO_ID;
    link->destination = NO_ID;
    link->state = TRUE;
    link->direction = UNK_DIRECTION;

    /*Returns link*/
    return link;
}

Status link_destroy(Link *link)
{
    /*Error management.*/
    if (!(link))
        return ERROR;

    /*Frees the allocated memory.*/
    free(link);
    link = NULL;

    /*Returns OK.*/
    return OK;
}

Id link_get_id(Link *link)
{
    /*Error management and returns the value.*/
    return (link ? link->id : ID_ERROR);
}

char *link_get_name(Link *link)
{
    /*Error management and returns the value.*/
    return (link ? link->name : NULL);
}

Id link_get_origin(Link *link)
{
    /*Error management and returns the value.*/
    return (link ? link->origin : ID_ERROR);
}

Id link_get_destination(Link *link)
{
    /*Error management and returns the value.*/
    return (link ? link->destination : ID_ERROR);
}

Direction link_get_direction(Link *link)
{
    /*Error management and returns the value.*/
    return (link ? link->direction : UNK_DIRECTION);
}

Bool link_get_state(Link *link)
{
    /*Error management and returns the value.*/
    return (link ? link->state : FALSE);
}

Status link_set_origin(Link *link, Id origin)
{
    /*Error management.*/
    if (!link || origin == ID_ERROR)
        return ERROR;

    /*Sets the value.*/
    link->origin = origin;

    /*Returns OK.*/
    return OK;
}

Status link_set_destination(Link *link, Id destination)
{
    /*Error management.*/
    if (!link || destination == ID_ERROR)
        return ERROR;

    /*Sets the value.*/
    link->destination = destination;

    /*Returns OK.*/
    return OK;
}

Status link_set_name(Link *link, char *name)
{
    /*Error management.*/
    if (!link || !name)
        return ERROR;

    /*Sets the value.*/
    strcpy(link->name, name);

    /*Returns OK.*/
    return OK;
}

Status link_set_direction(Link *link, Direction direction)
{
    /*Error management.*/
    if (!(link))
        return ERROR;

    /*Sets the value.*/
    link->direction = direction;

    /*Returns OK.*/
    return OK;
}

Status link_set_state(Link *link, Bool state)
{
    /*Error management.*/
    if (!(link))
        return ERROR;

    /*Sets the value.*/
    link->state = state;

    /*Returns OK.*/
    return OK;
}

void link_print(Link *link)
{
    /*Error management.*/
    if (!(link))
        return;

    /*Prints the information.*/
    printf("Link with id \"%ld\" and name \"%s\" has the following information:\n", link->id, link->name);
    printf("Origin_id: %ld   Destination_id: %ld\n", link->origin, link->destination);
    printf("State: %s", (link->state == TRUE ? "TRUE" : "FALSE"));
    printf("Direction: %s", (link->direction == N ? "NORTH" : (link->direction == S ? "SOUTH" : (link->direction == E ? "EAST" : (link->direction == W ? "WEST" : "UNK_DIRECTION")))));
}