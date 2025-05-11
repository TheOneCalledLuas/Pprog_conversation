/**
 * @brief It defines common types for the whole project
 *
 * @file set.c
 * @author Saúl López Romero
 * @version 2
 * @date 18-02-2025
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "set.h"

/**
 * Set TAD.
 */
struct _Set
{
    int n_ids;   /*!<Number of ids in the set.*/
    Id *content; /*!<Set content.*/
};

Set *set_create()
{
    /*Allocates memory.*/
    Set *set = (Set *)malloc(sizeof(Set));
    /*Sets the values to default ones.*/
    if (set)
    {
        set->n_ids = 0;
    }

    /*If the content wasn't allocated it undoes the allocation.*/
    if (!(set->content = (Id *)calloc(MAX_SET, sizeof(Id))))
    {
        free(set);
        return NULL;
    }

    /*Clean exit.*/
    return set;
}

void set_destroy(Set *set)
{
    /*Checks the parameters.*/
    if (!set)
    {
        return;
    }
    /*Frees the memory.*/
    if (set->content)
    {
        free(set->content);
    }
    free(set);
}

int set_find(Set *set, Id id)
{
    int i = 0;
    /*Error management.*/
    if (!set)
        return FUNCTION_ERROR;

    /*Searches for the id.*/
    for (i = 0; i < set->n_ids; i++)
    {
        if (set->content[i] == id)
            return i;
    }
    /*The id wasn't found.*/
    return FUNCTION_ERROR;
}

Status set_add(Set *set, Id element)
{
    /*Checks the parameters.*/
    if (!set || element <= NO_ID)
    {
        return ERROR;
    }

    /*Checks if the id already is in the set.*/
    if (set_find(set, element) != NO_ID)
    {
        return OK;
    }

    /*Checks that the set isn't full.*/
    if (set->n_ids == MAX_SET)
    {
        return ERROR;
    }

    /*Adds the element to the set.*/
    set->content[set->n_ids] = element;
    set->n_ids++;

    /*Clean exit.*/
    return OK;
}

Id set_take(Set *set, Id id)
{
    int pos = 0, i = 0;
    Id id_aux = 0;
    /*Error management.*/
    if (!set)
        return ID_ERROR;

    /*Searches for the element.*/
    if ((pos = set_find(set, id)) == NO_POSITION)
    {
        return ID_ERROR;
    }

    /*Reordenates the set and returns the value.*/
    id_aux = set->content[pos];

    for (i = pos; i < set->n_ids - 1; i++)
    {
        set->content[i] = set->content[i + 1];
    }
    set->n_ids--;
    return id_aux;
}

int set_len(Set *set)
{
    /*Error handling.*/
    if (!set)
        return FUNCTION_ERROR;

    /*Returns the value.*/
    return set->n_ids;
}

Id *set_get_content(Set *set)
{
    Id *elements;
    int i;

    /*Error management.*/
    if (!set || set->n_ids <= NO_THINGS)
    {
        return NULL;
    }

    /*Allcates mmory*/
    if (!(elements = (Id *)calloc(set->n_ids, sizeof(Id))))
    {
        return NULL;
    }

    /*Fills the array in.*/
    for (i = 0; i < set->n_ids; i++)
    {
        elements[i] = set->content[i];
    }

    /*And returns it.*/
    return elements;
}

Status set_print(Set *s)
{
    int i = 0, len = 0;
    /*Error management.*/
    if (!s)
    {
        return ERROR;
    }
    len = set_len(s);

    /*Prints the info.*/
    printf("Set formed by %d elements: ", len);
    for (i = 0; i < len; i++)
    {
        printf("%ld ", s->content[i]);
    }
    printf("\n");
    return OK;
}
