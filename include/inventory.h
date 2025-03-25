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
/**
 * @brief Inventory TAD.
 * @author Raquel Anguita Martínez de Velasco.
 */
typedef struct _Inventory Inventory;

/**
 * @brief Creates a new inventory structure.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @return Pointer to the new inventory; NULL in case of error.
 */
Inventory *inventory_create();

/**
 * @brief Destroys the inventory structure and frees the memory.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 */
void inventory_destroy(Inventory *inventory);

/**
 * @brief Sets the inventory's maximum number of objects.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @param max_objs Number to set the inventory's maximum number of objects.
 * @return OK if the value could be correctly set; ERROR otherewise.
 */
Status inventory_set_max_objs(Inventory *inventory, long max_objs);

/**
 * @brief Gets the inventory's maximum number of objects.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @return The inventory's maximum number of objects; -1 if something went wrong.
 */
long inventory_get_max_objs(Inventory *inventory);

/**
 * @brief Searches for an object in an inventory.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @param id Id of the object to be searched.
 * @return Position of the id in the inventory; -1 if not found or anything went wrong.
 */
int inventory_find(Inventory *inventory, Id id);

/**
 * @brief Adds an object to the inventory.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @param id Id of the object to be added.
 * @return OK if the value could be correctly set; ERROR otherewise.
 */
Status inventory_add(Inventory *inventory, Id id);

/**
 * @brief Takes an object out of the inventory.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @param id Id of the object to be taken out.
 * @return Id taken out; -2 if anything went wrong.
 */
Id inventory_take(Inventory *inventory, Id id);

/**
 * @brief Gets the number of objects in the inventory.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @return Number of objects in the inventory; -1 if there were any errors.
 */
int inventory_len(Inventory *inventory);

/**
 * @brief Returns an array of ids with the objects in the inventory. (IMPORTANT: the array has to be freed after using it.)
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @return Array of ids with the content of the inventory.
 */
Id *inventory_get_content(Inventory *inventory);

/**
 * @brief Prints the inventory's information.
 * @author Raquel Anguita Martínez de Velasco.
 *
 * @param inventory Pointer to the inventory to change.
 * @return OK if the value could be correctly set; ERROR otherewise.
 */
Status inventory_print(Inventory *inventory);

#endif