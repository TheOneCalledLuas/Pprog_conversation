/**
 * @brief It handles inventory related tasks.
 *
 * @file inventory.h
 * @author Raquel Anguita Martínez de Velasco
 * @version 1
 * @date 18-03-2025
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

typedef struct _Inventory Inventory;

Inventory *inventory_create();

 void inventory_destroy(Inventory *inventory);

 Status inventory_set_max_objs(Inventory *inventory, long max_objs);

 long inventory_get_max_objs(Invenotry *inventory);

Status inventory_add(Inventory *inventory, Id id);

Id inventory_take(Inventory *inventory, Id id);

int inventory_len(Inventory *inventory);

Id *inventory_get_content(Inventory *inventory);

Status inventory_print(Inventory *inventory);