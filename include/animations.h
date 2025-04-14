/**
 * @brief It implements animations into the game.
 *
 * @file animations.h
 * @author Saúl López Romero
 * @version 1
 * @date 14-04-2025
 * @copyright GNU Public License
 */

#ifndef ANIMATIONS_H
#define ANIMATIONS_H /*!< Animations lib.*/


#define MAX_ANIMATIONS 100 /*!< Max animation number.*/

typedef struct _Animation_Manager Animation_Manager; /*!< Animation manager type.*/
typedef struct _Animation Animation; /*!< Animation type.*/

/**
 * @brief Initialises the animator manager.
 * @author Saúl López Romero.
 * 
 * @param animation_route Directory route where the animations are stored.
 * @return Pointer to the struct of NULL.
 */
Animation_Manager * animations_manager_init(char * animation_route);

/**
 * @brief Destroys the animator manager.
 * @author Saúl López Romero.
 * 
 * @param am Animator manager to destroy.
 */
void animations_manager_destroy(Animation_Manager * am);

/**
 * @brief Runs a certain animation.
 * @author Saúl López Romero.
 * 
 * @param am Animator manager.
 * @param anim_id Aniamtion id.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animations_run(Animation_Manager * am, Id anim_id);

#endif