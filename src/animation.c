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
    int height;           /*!< Animation height.*/
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
    /*Error handling.*/
    if (am == NULL || anim == NULL || am->n_animations >= MAX_ANIMATIONS)
    {
        return ERROR;
    }

    /*Adding the animation to the list.*/
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
    anim->height = 0;
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

Id animation_get_id(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return NO_ID;

    /*Clean exit.*/
    return anim->id;
}
char *animation_get_name(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return NULL;

    /*Clean exit.*/
    return anim->name;
}

Status animation_set_name(Animation *anim, char *name)
{
    /*Error handling.*/
    if (!anim || !name || strlen(name) == 0 || strlen(name) > MAX_LINE)
    {
        return ERROR;
    }

    /*Copies the name.*/
    strcpy(anim->name, name);

    /*Clean exit.*/
    return OK;
}

char *animation_get_file_name(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return NULL;

    /*Clean exit.*/
    return anim->animation_file;
}

Status animation_set_file_name(Animation *anim, char *filename)
{
    /*Error handling.*/
    if (!anim || !filename || strlen(filename) == 0 || strlen(filename) > MAX_LINE)
    {
        return ERROR;
    }

    /*Copies the new file name.*/
    strcpy(anim->animation_file, filename);

    /*Clean exit.*/
    return OK;
}

int animation_get_n_images(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->n_images;
}

Status animation_set_n_images(Animation *anim, int n_images)
{
    /*Error handling.*/
    if (!anim || n_images < 0)
    {
        return ERROR;
    }

    /*Sets the number of images.*/
    anim->n_images = n_images;

    /*Clean exit.*/
    return OK;
}

int animation_get_width(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->widht;
}

Status animation_set_width(Animation *anim, int width)
{
    /*Error handling.*/
    if (!anim || width < 0)
    {
        return ERROR;
    }

    /*Sets the width.*/
    anim->widht = width;

    /*Clean exit.*/
    return OK;
}

int animation_get_height(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->height;
}

Status animation_set_height(Animation *anim, int height)
{
    /*Error handling.*/
    if (!anim || height < 0)
    {
        return ERROR;
    }

    /*Sets the height.*/
    anim->height = height;

    /*Clean exit.*/
    return OK;
}

int animation_get_side_padding(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->side_padding;
}

Status animation_set_side_padding(Animation *anim, int side_padding)
{
    /*Error handling.*/
    if (!anim || side_padding < 0)
    {
        return ERROR;
    }

    /*Sets the side padding.*/
    anim->side_padding = side_padding;

    /*Clean exit.*/
    return OK;
}

int animation_get_height_padding(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->height_padding;
}

Status animation_set_height_padding(Animation *anim, int height_padding)
{
    /*Error handling.*/
    if (!anim || height_padding < 0)
    {
        return ERROR;
    }

    /*Sets the height padding.*/
    anim->height_padding = height_padding;

    /*Clean exit.*/
    return OK;
}

float animation_get_refresh_rate(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->refresh_rate;
}

Status animation_set_refresh_rate(Animation *anim, float refresh_rate)
{
    /*Error handling.*/
    if (!anim || refresh_rate < 0)
    {
        return ERROR;
    }

    /*Sets the refresh rate.*/
    anim->refresh_rate = refresh_rate;

    /*Clean exit.*/
    return OK;
}

int animation_get_background_color(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->background_color;
}

Status animation_set_background_color(Animation *anim, int background_color)
{
    /*Error handling.*/
    if (!anim || background_color < 0)
    {
        return ERROR;
    }

    /*Sets the background color.*/
    anim->background_color = background_color;

    /*Clean exit.*/
    return OK;
}

int animation_get_font_color(Animation *anim)
{
    /*Error handling.*/
    if (!anim)
        return -1;

    /*Clean exit.*/
    return anim->font_color;
}

Status animation_set_font_color(Animation *anim, int font_color)
{
    /*Error handling.*/
    if (!anim || font_color < 0)
    {
        return ERROR;
    }

    /*Sets the font color.*/
    anim->font_color = font_color;

    /*Clean exit.*/
    return OK;
}

int animation_manager_get_n_animations(Animation_Manager *am)
{
    /*Error handling.*/
    if (!am)
        return -1;

    /*Clean exit.*/
    return am->n_animations;
}

Animation *animation_manager_get_animation_by_id(Animation_Manager *am, Id id)
{
    int i = 0;
    /*Error handling.*/
    if (!am || id == NO_ID)
        return NULL;

    /*Searches for the animation to be returned.*/
    for (i = 0; i < am->n_animations; i++)
    {
        if (am->animations[i]->id == id)
        {
            /*The animation was found, and thus is returned.*/
            return am->animations[i];
        }
    }

    /*The animation wasn't found.*/
    return NULL;
}

Animation *animation_manager_get_animation_by_name(Animation_Manager *am, char *name)
{
    int i = 0;
    /*Error handling.*/
    if (!am || !name || strlen(name) == 0 || strlen(name) > MAX_LINE)
        return NULL;

    /*Searches for the animation to be returned.*/
    for (i = 0; i < am->n_animations; i++)
    {
        if (strcmp(am->animations[i]->name, name) == 0)
        {
            /*The animation was found, and thus is returned.*/
            return am->animations[i];
        }
    }

    /*The animation wasn't found.*/
    return NULL;
}
