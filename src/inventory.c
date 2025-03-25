/**
 * @brief It implements the inventory functionality.
 *
 * @file object.c
 * @author Raquel Anguita Martínez de Velasco
 * @version 1
 * @date 18-03-2025
 * @copyright GNU Public License
 */

#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Inventory
{
    Set *objs;     /*!< Set with the objects in the inventory. */
    long max_objs; /*!< Maximum number of objects a player can carry in the inventory. */
};

Inventory *inventory_create()
{
    Inventory *newInv = NULL;

    /* Memory allocation and error control. */
    if (!(newInv = (Inventory *)malloc(sizeof(Inventory))))
    {
        return NULL;
    }

    /* Initialization of an empty inventory. */
    newInv->objs = set_create();
    newInv->max_objs = 0;

    return newInv;
}

void inventory_destroy(Inventory *inventory)
{
    /* Error control for parameters. */
    if (!inventory)
    {
        return;
    }

    /* Memory free. */
    set_destroy(inventory->objs);
    free(inventory);
}

Status inventory_set_max_objs(Inventory *inventory, long max_objs)
{
    /* Error control for parameters. */
    if (!inventory || max_objs < 0 || max_objs < set_len(inventory->objs) || max_objs > MAX_SET)
    {
        return ERROR;
    }

    /* Asination of the value. */
    inventory->max_objs = max_objs;
    return OK;
}

long inventory_get_max_objs(Inventory *inventory)
{
    /* Error control for parameters. */
    if (!inventory)
    {
        return -1;
    }

    /* Return of the value using the set_len function. */
    return set_len(inventory->objs);
}

int inventory_find(Inventory *inventory, Id id)
{
    /* Error control for parameters. */
    if (!inventory)
    {
        return -1;
    }
}

Status inventory_add(Inventory *inventory, Id id)
{
    /* Error control for parameters and set size. */
    if (!inventory || set_len(inventory->objs) == inventory->max_objs)
    {
        return ERROR;
    }

    /* Return of the status using the set_add function. */
    return set_add(inventory->objs, id);
}

Id inventory_take(Inventory *inventory, Id id)
{
    /* Error control for parameters. */
    if (!inventory)
    {
        return ID_ERROR;
    }

    /* Return of the id using the set_take function. */
    return set_take(inventory->objs, id);
}

int inventory_len(Inventory *inventory)
{
    /* Error control for parameters. */
    if (!inventory)
    {
        return -1;
    }

    /* Return of the length using the set_len function. */
    return set_len(inventory->objs);
}

Id *inventory_get_content(Inventory *inventory)
{
    /* Error control for parameters. */
    if (!inventory)
    {
        return NULL;
    }

    /* Return of the array using the set_get_content function. */
    return set_get_content(inventory->objs);
}

Status inventory_print(Inventory *inventory)
{
    /* Error control for parameters. */
    if (!inventory)
    {
        return ERROR;
    }

    /* Prints the information. */
    prinf("Inventory formed by a maximum number of elements and a set.\n");
    printf("Maximum number of elements: %ld\n", inventory->max_objs);
    return set_print(inventory->objs);
}