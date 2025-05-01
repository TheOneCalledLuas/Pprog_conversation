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

#include "types.h"

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
 * @brief Gets the animation id.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the id from.
 * @returns Animation id or -1 if an error takes place.
 */
Id animation_get_id(Animation *anim);

/**
 * @brief Gets the animation name.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the name from.
 * @returns Animation name or NULL if an error takes place.
 */
char *animation_get_name(Animation *anim);

/**
 * @brief Gets the animation file name.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the file name from.
 * @returns Animation file name or NULL if an error takes place.
 */
char *animation_get_file_name(Animation *anim);

/**
 * @brief Gets the animation number of images.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the number of images from.
 * @returns Animation number of images or -1 if an error takes place.
 */
int animation_get_n_images(Animation *anim);

/**
 * @brief Gets the animation width.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the width from.
 * @returns Animation width or -1 if an error takes place.
 */
int animation_get_width(Animation *anim);

/**
 * @brief Gets the animation height.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the height from.
 * @returns Animation height or -1 if an error takes place.
 */
int animation_get_height(Animation *anim);

/**
 * @brief Gets the animation side padding.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the side padding from.
 * @returns Animation side padding or -1 if an error takes place.
 */
int animation_get_side_padding(Animation *anim);

/**
 * @brief Gets the animation height padding.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the height padding from.
 * @returns Animation height padding or -1 if an error takes place.
 */
int animation_get_height_padding(Animation *anim);

/**
 * @brief Gets the animation refresh rate.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the refresh rate from.
 * @returns Animation refresh rate or -1 if an error takes place.
 */
float animation_get_refresh_rate(Animation *anim);

/**
 * @brief Gets the animation background color.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the background color from.
 * @returns Animation background color or -1 if an error takes place.
 */
int animation_get_background_color(Animation *anim);

/**
 * @brief Gets the animation font color.
 * @author Saúl López Romero.
 *
 * @param anim Animation to get the font color from.
 * @returns Animation font color or -1 if an error takes place.
 */
int animation_get_font_color(Animation *anim);

/**
 * @brief Gets the animation from the manager by its id.
 * @author Saúl López Romero.
 *
 * @param am Animator manager.
 * @param id Animation id.
 * @returns Animation or NULL if an error takes place.
 */
Animation *animation_manager_get_animation_by_id(Animation_Manager *am, Id id);

/**
 * @brief Gets the animation from the manager by its name.
 * @author Saúl López Romero.
 *
 * @param am Animator manager.
 * @param name Animation name.
 * @returns Animation or NULL if an error takes place.
 */
Animation *animation_manager_get_animation_by_name(Animation_Manager *am, char *name);

/**
 * @brief Gets the number of animations in the manager.
 * @author Saúl López Romero.
 *
 * @param am Animator manager.
 * @returns Number of animations or -1 if an error takes place.
 */
int animation_manager_get_n_animations(Animation_Manager *am);

/**
 * @brief Sets the animation name.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the name to.
 * @param name Animation name.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_name(Animation *anim, char *name);

/**
 * @brief Sets the animation file name.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the file name to.
 * @param filename Animation file name.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_file_name(Animation *anim, char *filename);

/**
 * @brief Sets the animation number of images.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the number of images to.
 * @param n_images Animation number of images.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_n_images(Animation *anim, int n_images);

/**
 * @brief Sets the animation width.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the width to.
 * @param width Animation width.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_width(Animation *anim, int width);

/**
 * @brief Sets the animation height.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the height to.
 * @param height Animation height.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_height(Animation *anim, int height);

/**
 * @brief Sets the animation side padding.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the side padding to.
 * @param side_padding Animation side padding.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_side_padding(Animation *anim, int side_padding);

/**
 * @brief Sets the animation height padding.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the height padding to.
 * @param height_padding Animation height padding.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_height_padding(Animation *anim, int height_padding);

/**
 * @brief Sets the animation refresh rate.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the refresh rate to.
 * @param refresh_rate Animation refresh rate.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_refresh_rate(Animation *anim, float refresh_rate);

/**
 * @brief Sets the animation background color.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the background color to.
 * @param background_color Animation background color.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_background_color(Animation *anim, int background_color);

/**
 * @brief Sets the animation font color.
 * @author Saúl López Romero.
 *
 * @param anim Animation to set the font color to.
 * @param font_color Animation font color.
 * @returns OK if everything goes as expected, ERROR otherwise.
 */
Status animation_set_font_color(Animation *anim, int font_color);

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