/**
 * @brief It defines common types for the whole project
 *
 * @file types.c
 * @author Saúl López Romero
 * @version 0
 * @date 7-02-2025
 * @copyright GNU Public License
 */

#include <stdlib.h>

#include "types.h"
#include "object.h"

struct _Object_set
{
    int num_elements; /* <! Number of elements in the set.*/
    Object **content; /* <! Set content.*/
};

Object_set *types_create_object_set()
{
    /*Allocates memory.*/
    Object_set *set = (Object_set *)malloc(sizeof(Object_set));
    /*Sets the values to default ones.*/
    if (set)
    {
        set->num_elements = 0;
        set->content = (Object **)calloc(1, sizeof(Object *));
    }
    /*If the content wasn't allocated it undoes the allocation.*/
    if (!set->content)
    {
        free(set);
        return NULL;
    }

    /*Clean exit.*/
    return set;
}

void types_object_set_destroy(Object_set *set)
{
    /*Checks the parameters.*/
    if (!set)
    {
        return;
    }
    /*FFrees the memory.*/
    if (set->content)
    {
        free(set->content);
    }
    free(set);
}

Status types_object_set_add_element(Object_set *set, Object *element)
{
    Id id_aux = -1;
    Bool is_unique = TRUE;
    int i = 0;
    /*Checks the parameters.*/
    if (!set || !element)
    {
        return ERROR;
    }

    /*Compares the object with the ones included in the set.*/
    id_aux = object_get_id(element);
    if (id_aux == NO_ID)
    {
        return ERROR;
    }
    for (i = 0; i < set->num_elements; i++)
    {
        is_unique = (object_get_id(set->content[i]) == id_aux ? FALSE : TRUE);
    }

    /*Decides wether to add the object or not.*/
    if (is_unique)
    {
        set->num_elements++;
        set->content = (Object *)realloc(set->content, (set->num_elements) * sizeof(Object *));

        /*Error handling.*/
        if (!(set->content))
        {
            return ERROR;
        }

        /*Clean exit.*/
        return OK;
    }
    else
    {
        /*The element isn't added as it's a repeated object.*/
        return ERROR;
    }
}

Status types_object_set_take_object(Object_set *set, Id id)
{
    int i = 0;
    Bool found = FALSE, break_condition = FALSE;
    /*Checks the parameters.*/
    if (!set || id == NO_ID)
    {
        return ERROR;
    }

    /*Searchs for the object with such id.*/
    for (i = 0; i < set->num_elements; i++)
    {
        if (break_condition)
        {
            break;
        }
        switch (found)
        {
        case FALSE:
            if (id == object_get_id(set->content[i]))
            {
                found = TRUE;
                if (i != set->num_elements - 1)
                { /*Si este no es el ultimo.*/
                    set->content[i] = set->content[i + 1];
                    continue;
                }
            }
            break;
        case TRUE:
            if (i == set->num_elements - 1)
            {
                set->content[i] = NULL;
                break_condition = TRUE;
                break;
            }
            else
            {
                set->content[i] = set->content[i + 1];
                break;
            }

        default:
            break;
        }
    }

    /*If the object wasn't found.*/
    if (found == FALSE)
    {
        return ERROR;
    }

    /*Reallocates the memory.*/
    set->num_elements--;
    set->content = (Object **)realloc(set->content, (set->num_elements) * sizeof(Object *));
    if (!(set->content))
    {
        return ERROR;
    }

    /*Clean exit.*/
    return OK;
}

int types_object_set_get_len(Object_set *set)
{
    /*Checks the parameters.*/
    if (!set)
    {
        return -1;
    }

    return set->num_elements;
}

Object *types_get_object_from_set(Object_set *set, Id id)
{
    int i = 0;
    /*Checks the parameters.*/
    if (!set || id < 0)
    {
        return NULL;
    }

    /*Searches for the object.*/
    for (i = 0; i < set->num_elements; i++)
    {
        if (object_get_id(set->content[i]) == id)
        {
            return set->content[i];
        }
    }

    /*The object wasn't found.*/
    return NULL;
}
