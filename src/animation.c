/**
 * @brief It implements animations into the game.
 *
 * @file animation.c
 * @author Saúl López Romero
 * @version 1
 * @date 14-04-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "animation.h"
#include "types.h"

#define MAX_LINE 128      /*!< Max number of cheracters per line.*/
#define ESCAPE_CODE_LEN 6 /*!< Escape code lenght with the final /0.*/

/**
 * @brief This struct is in charge of handling all the game animations.
 */
struct _Animation_Manager
{
    Animation *animations;           /*!< Animation list.*/
    int n_animations;                /*!< Number of animations.*/
    char animations_route[MAX_LINE]; /*!< Path to the animation dir.*/
    char *animation_files;           /*!< file with all the animation file names.*/
};

/**
 * @brief Animation stucture.
 */
struct _Animation
{
    Id id;                  /*!< Animation id.*/
    char *animation_file;   /*!< Animation file, where the data is stored.*/
    long n_images;          /*!< Number of frames for the animation.*/
    int widht;              /*!< Animation widht.*/
    int lenght;             /*!< Animation lenght.*/
    int side_padding;       /*!< Number of white spaces left to the left, set to zero by default.*/
    int height_padding;     /*!< Number of white spaces left bellow the animation, set to zero by default.*/
    float refresh_rate;     /*!< Seconds left between each frame.*/
    char *background_color; /*!< Background color during the animation.*/
};
