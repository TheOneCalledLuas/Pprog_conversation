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
    size_t size;      /* <! Size in bits of each element.*/
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
        set->size++;
        set->content = (Object *)realloc(set->content, (set->size) * sizeof(Object *));

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