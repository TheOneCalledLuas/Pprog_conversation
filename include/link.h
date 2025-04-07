/**
 * @brief It defines the link module
 *
 * @file link.h
 * @author Fernando Mijangos, Irene García
 * @version 1
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"
#include <string.h>
#define MAX_NAME 100 /*!<Name length.*/

typedef struct _link Link; /*!<Link type.*/

/**
 * @brief Allocates and returns a link.
 * @author Fernando Mijangos.
 *
 * @param id Id of the new link.
 * @return Pointer to the new link intialised or NULL if error.
 */
Link *link_create(Id id);

/**
 * @brief Destroys an existing link.
 * @author Fernando Mijangos.
 *
 * @param link Pointer to the link that will be destroyed.
 * @return OK if everything went well, ERROR otherwise.
 */
Status link_destroy(Link *link);

/**
 * @brief Gets the id of the link.
 * @author Fernando Mijangos.
 *
 * @param link Pointer to the link.
 * @return Id of the link or ID_ERROR if error
 */
Id link_get_id(Link *link);

/**
 * @brief Gets the name of the link.
 * @author Fernando Mijangos.
 *
 * @param link Pointer to the link.
 * @return Pointer to the name, NULL if error.
 */
char *link_get_name(Link *link);

/**
 * @brief Gets the id of the origin space.
 * @author Irene García.
 *
 * @param link Pointer to the link.
 * @return Id of the space of origin, ID_error if error.
 */
Id link_get_origin(Link *link);

/**
 * @brief Gets the id of the space of destiantion.
 * @author Irene García.
 *
 * @param link ointer to the link.
 * @return Id of the space of destination, ID_ERROR if error.
 */
Id link_get_destination(Link *link);

/**
 * @brief Gets the direction the link is pointing to.
 * @author Irene García.
 *
 * @param link Pointer to the link.
 * @return Direction to where the link points, UNK_DIRECTION if error.
 */
Direction link_get_direction(Link *link);

/**
 * @brief Gets the state of the link.
 * @author Irene García.
 *
 * @param link Pointer to the link.
 * @return TRUE if the link is opened, FALSE if it isn't, FALSE if error.
 */
Bool link_get_state(Link *link);

/**
 * @brief Sets the name of the link.
 * @author Fernando Mijangos.
 *
 * @param link Pointer to the link.
 * @param name Pointer to the new name.
 * @return OK, if everything went well, ERROR otherwise.
 */
Status link_set_name(Link *link, char *name);

/**
 * @brief Sets the id of the origin space.
 * @author Irene García.
 *
 * @param link Pointer to the link.
 * @param origin New id of the origin space.
 * @return OK, if everything went well, ERROR otherwise.
 */
Status link_set_origin(Link *link, Id origin);

/**
 * @brief Sets the id of the destination space.
 * @author Irene García.
 *
 * @param link Ponter to the link
 * @param destination New id of the destination space
 * @return OK, if everything went well, ERROR otherwise.
 */
Status link_set_destination(Link *link, Id destination);

/**
 * @brief Sets the direction the link is pointing to.
 * @author Fernando Mijangos.
 *
 * @param link Pointer to the link.
 * @param direction New direction of the link.
 * @return OK, if everything went well, ERROR otherwise.
 */
Status link_set_direction(Link *link, Direction direction);

/**
 * @brief Sets the state of the link(TRUE=OPEN)(FALSE=CLOSED).
 * @author Fernando Mijangos.
 *
 * @param link Pointer to the link.
 * @param State New state of the link.
 * @return OK, if everything went well, ERROR otherwise.
 */
Status link_set_state(Link *link, Bool State);

/**
 * @brief Prints the link information on the terminal.
 * @author Fernando Mijangos.
 * 
 * @param link Pointer to the link.
 */
void link_print(Link* link);

#endif
