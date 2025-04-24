/**
 * @brief It implements animations into the game.
 *
 * @file animation.h
 * @author Saúl López Romero
 * @version 1
 * @date 14-04-2025
 * @copyright GNU Public License
 */

#ifndef ANIMATIONS_H
#define ANIMATIONS_H /*!< Animations lib.*/

#define MAX_ANIMATIONS 100 /*!< Max animation number.*/

typedef struct _Animation_Manager Animation_Manager; /*!< Animation manager type.*/
typedef struct _Animation Animation;                 /*!< Animation type.*/

/**
 * @brief Initialises the animator manager.
 * @author Saúl López Romero.
 *
 * @param animation_route Directory route where the animations are stored.
 * @return Pointer to the struct of NULL.
 */
Animation_Manager *animation_manager_init(char *animation_route);

/**
 * @brief Destroys the animator manager.
 * @author Saúl López Romero.
 *
 * @param am Animator manager to destroy.
 */
void animation_manager_destroy(Animation_Manager *am);

/**
 * @brief Adds a certain animation to the manager.
 * @author Saúl López Romero.
 *
 * @param am Animator manager.
 * @param anim Pointer to the animation.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_manager_add_animation(Animation_Manager *am, Animation *anim);

/**
 * @brief Deletes a certain animation from the manager.
 * @author Saúl López Romero.
 *
 * @param am Animator manager.
 * @param pos Position of the animation to delete.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_manager_del_animation(Animation_Manager *am, int pos);

/**
 * @brief Runs a certain animation.
 * @author Saúl López Romero.
 *
 * @param am Animator manager.
 * @param anim_id Aniamtion id.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_run(Animation_Manager *am, Id anim_id);

/**
 * @brief Initialises an animation.
 * @author Saúl López Romero.
 *
 * @param id Animation id.
 * @param filename File where the animation is stored.
 */
Animation *animation_init(Id id, char *filename);

/**
 * @brief Destroys an animation.
 * @author Saúl López Romero.
 *
 * @param anim Animation to destroy.
 */
void animation_destroy(Animation *anim);

#endif