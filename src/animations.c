/**
 * @brief It implements animations into the game.
 *
 * @file animations.c
 * @author Saúl López Romero
 * @version 1
 * @date 14-04-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "animations.h"
#include "types.h"

#define MAX_LINE 128 /*!< Max nimber of cheracters per line.*/

/**
 * @brief This struct is in charge of handling all the game animations.
 */
struct _Animation_Manager
{
    Animation *animations;           /*!< Animation list.*/
    int n_animations;                /*!< Number of animations.*/
    char animations_route[MAX_LINE]; /* Path to the animation dir.*/
};

/**
 * @brief Animation stucture.
 */
struct _Animation
{
    Id id;                /*!< Animation id.*/
    char *animation_file; /*!< Animation file, where the data is stored.*/
    long n_images;        /*!< Number of frames for the animation.*/
    int widht;            /*!< Animation widht.*/
    int lenght;           /*!< Animation lenght.*/
    int side_padding;     /*!< Number of white spaces left to the left, set to zero by default.*/
    int height_padding;   /*!< Number of white spaces left bellow the animation, set to zero by default.*/
    float refresh_rate;   /*!< Seconds left between each frame.*/
};

