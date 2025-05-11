/**
 * @brief It defines sets for the whole project
 *
 * @file set.h
 * @author Saúl López Romero && Fernando Mijangos
 * @version 1
 * @date 27-0122025
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
 * Maximun number of elements per set.
 */
 #define MAX_SET 50

/**
 * @brief Set TAD.
 * @author Saúl Lopez Romero.
 */
typedef struct _Set Set;

/**
 * @brief Creates a new set structure.
 * @author Saúl Lopez Romero.
 *
 * @return Pointer to the new set, NULL if an error takes place.
 */
Set *set_create();

/**
 * @brief Frees the memory.
 * @author Saúl Lopez Romero.
 *
 * @param set Pointer to the set.
 */
void set_destroy(Set *set);

/**
 * @brief Searches for an id in a set.
 * @author Saúl Lopez Romero.
 *
 * @param set Pointer to the set.
 * @param id Id to be searched.
 * @return position of the id in the set if found, FUNCTION_ERROR otherwise.
 */
int set_find(Set *set, Id id);

/**
 * @brief Adds an element to the set.
 * @author Saúl Lopez Romero.
 *
 * @param set Pointer to the set.
 * @param element Id to be added.
 * @returns Ok if the element was added or already was in the set, ERROR otherwise.
 */
Status set_add(Set *set, Id element);

/**
 * @brief Takes an element out of the set.
 * @author Saúl Lopez Romero.
 *
 * @param set Pointer to the set.
 * @param id Id to be taken out.
 * @return Id taken out, -2 if it wasnt found or an error took place.
 */
Id set_take(Set *set, Id id);

/**
 * @brief Gets the number of ids in the set.
 * @author Saúl Lopez Romero.
 * 
 * @param set Pointer to the set.
 * @return Number of Ids in the set, FUNCTION_ERROR otherwise.
 */
int set_len(Set * set);

/**
 * @brief Returns an array of ids with the content of the set.
 *          IMPORTANT free the array after using it.
 * @author Fernando Mijangos.
 * 
 * @param set Pointer to the set.
 * @return Array of ids with the content of the set.
 */
Id *set_get_content(Set *set);

/**
 * @brief Prints set information.
 * @author Saúl Lopez Romero.
 * 
 * @param s Pointer to the set.
 * @return OK if everything goes as it should, ERROR otherwise.
 */
Status set_print(Set *s);


#endif
