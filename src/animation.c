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

#define MAX_LINE 128       /*!< Max number of cheracters per line.*/
#define ESCAPE_CODE_LEN 6  /*!< Escape code lenght with the final /0.*/
#define MAX_ANIMATIONS 100 /*!< Max animation number.*/

/**
 * @brief This struct is in charge of handling all the game animations.
 */
struct _Animation_Manager
{
    Animation **animations;          /*!< Animation list.*/
    int n_animations;                /*!< Number of animations.*/
    char animations_route[MAX_LINE]; /*!< Path to the animation dir.*/
};

/**
 * @brief Animation stucture.
 */
struct _Animation
{
    Id id;                /*!< Animation id.*/
    char *name;           /*!< Animation name.*/
    char *animation_file; /*!< Animation file, where the data is stored.*/
    long n_images;        /*!< Number of frames for the animation.*/
    int widht;            /*!< Animation widht.*/
    int lenght;           /*!< Animation lenght.*/
    int side_padding;     /*!< Number of white spaces left to the left, set to zero by default.*/
    int height_padding;   /*!< Number of white spaces left bellow the animation, set to zero by default.*/
    float refresh_rate;   /*!< Seconds left between each frame.*/
    int background_color; /*!< Background color during the animation.*/
    int font_color;       /*!< Font color during the animation.*/
};

Animation_Manager *animation_manager_init(char *animation_file)
{
    Animation_Manager *am = NULL;

    /* Error handling.*/
    if (animation_file == NULL || strlen(animation_file) == 0 || strlen(animation_file) > MAX_LINE)
    {
        return NULL;
    }

    /* Memory allocation.*/
    if (!(am = (Animation_Manager *)calloc(1, sizeof(Animation_Manager))))
    {
        return NULL;
    }

    /* Memory allocation for the animation list.*/
    if (!(am->animations = (Animation **)calloc(MAX_ANIMATIONS, sizeof(Animation *))))
    {
        free(am);
        return NULL;
    }

    /* Copying the animation route.*/
    strcpy(am->animations_route, animation_file);

    /* Setting the values to their default state.*/
    am->n_animations = 0;

    /*Clean Exit.*/
    return am;
}

void animation_manager_destroy(Animation_Manager *am)
{
    int i;

    /* Error handling.*/
    if (am)
    {
        /* Frees the animation list.*/
        if (am->animations)
            free(am->animations);

        /* Frees the animator manager.*/
        free(am);
    }
}

Status animation_manager_add_animation(Animation_Manager *am, Animation *anim)
{
    /* Error handling.*/
    if (am == NULL || anim == NULL || am->n_animations >= MAX_ANIMATIONS)
    {
        return ERROR;
    }

    /* Adding the animation to the list.*/
    am->animations[am->n_animations] = anim;
    am->n_animations++;

    /* Clean exit.*/
    return OK;
}

Status animation_manager_del_animation(Animation_Manager *am, int pos)
{
    int i = 0;

    /* Error handling.*/
    if (am == NULL || am->n_animations <= 0 || pos < 0 || pos >= am->n_animations)
    {
        return ERROR;
    }

    /*Frees and deletes the animation.*/
    free(am->animations[pos]);
    am->animations[pos] = NULL;
    am->n_animations--;

    /* Clean exit.*/
    return OK;
}

Animation *animation_init(Id id, char *filename)
{
    Animation *anim = NULL;

    /* Error handling.*/
    if (id == NO_ID || filename == NULL || strlen(filename) == 0 || strlen(filename) > MAX_LINE)
    {
        return NULL;
    }

    /* Memory allocation.*/
    if (!(anim = (Animation *)calloc(1, sizeof(Animation))))
    {
        return NULL;
    }

    /* Copying the animation file name.*/
    anim->animation_file = (char *)calloc(strlen(filename) + 1, sizeof(char));
    if (anim->animation_file == NULL)
    {
        free(anim);
        return NULL;
    }
    strcpy(anim->animation_file, filename);

    /* Memory allocation for the animation name.*/
    if (!(anim->name = (char *)calloc(MAX_LINE, sizeof(char))))
    {
        free(anim->animation_file);
        free(anim);
        return NULL;
    }

    /* Setting the values to their default state.*/
    anim->id = id;
    anim->name[0] = '\0';
    anim->n_images = 0;
    anim->widht = 0;
    anim->lenght = 0;
    anim->side_padding = 0;
    anim->height_padding = 0;
    anim->refresh_rate = 0.0;
    anim->background_color = 0;
    anim->font_color = 0;

    /* Clean exit.*/
    return anim;
}

void animation_destroy(Animation *anim)
{
    /* Error handling.*/
    if (anim)
    {
        /* Frees the animation file name.*/
        if (anim->animation_file)
            free(anim->animation_file);

        /* Frees the animation name.*/
        if (anim->name)
            free(anim->name);

        /* Frees the animation struct.*/
        free(anim);
    }
}