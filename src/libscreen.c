#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libscreen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

/* Global variables */
int ROWS = 23;         /*!<Rows of the area*/
int MENU_ROWS = 23;    /*!<Rows of the area in menu mode*/
int COLUMNS = 80;      /*!<Columns of the area*/
int MENU_COLUMNS = 80; /*!<Columns of the area in menu mode*/

#define TOTAL_DATA (ROWS * COLUMNS) + 1                       /*!< Total data/points of the screen */
#define BG_CHAR '~'                                           /*!< Background base character */
#define FG_CHAR ' '                                           /*!< Foreground base characters */
#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))           /*!<Function to get the information of a point in the area*/
#define ACCESS_MENU(d, x, y) (d + ((y) * MENU_COLUMNS) + (x)) /*!<Function to get the information of a point in the area when in menu mode*/

/**
 * @brief It defines the area type
 */
struct _Area
{
  int x, y, width, height; /*!< Area position and size */
  char *cursor;            /*!< Pointer to the cursor of that area */
};

char *__data;      /*!<Pointer to the information of the whole area*/
char *__data_menu; /*!<Pointer to the information of the whole area in menu mode*/

/****************************/
/*     Private functions    */
/****************************/

/**
 * @brief It looks if the cursor is out of bounds
 * @author Profesores PPROG
 *
 * @param area the area to be checked
 * @return 1 if the cursor is out of bounds, 0 otherwise
 */
int screen_area_cursor_is_out_of_bounds(Area *area);

/**
 * @brief It moves the information of the area up
 * @author Profesores PPROG
 *
 * @param area the area to be moved
 */
void screen_area_scroll_up(Area *area);

/**
 * @brief It replaces the special characters in a string
 * @author Profesores PPROG
 *
 * @param str the string to be modified
 */
void screen_utils_replaces_special_chars(char *str);

/**
 * @brief It changes a color into its respective string
 * @author Profesores PPROG
 *
 * @param color the color to be changed
 * @return the string with the color
 */
char *frame_color_to_string(Frame_color color);

/**
 * @brief It looks if the cursor is out of bounds in menu mode
 * @author Fernando Mijangos
 *
 * @param area the area to be checked
 * @return 1 if the cursor is out of bounds, 0 otherwise
 */
int screen_area_cursor_is_out_of_bounds_menu(Area *area);

/**
 * @brief It moves the information of the area up in menu mode
 * @author Fernando Mijangos
 *
 * @param area the area to be moved
 * @return 1 if the cursor is out of bounds, 0 otherwise
 */
void screen_area_scroll_up_menu(Area *area);

/****************************/
/* Functions implementation */
/****************************/
void screen_init(int rows, int columns)
{
  screen_destroy(); /* Dispose if previously initialized */
  ROWS = rows;
  COLUMNS = columns;
  __data = (char *)malloc(sizeof(char) * TOTAL_DATA);

  if (__data)
  {
    memset(__data, (int)BG_CHAR, TOTAL_DATA); /*Fill the background*/
    *(__data + TOTAL_DATA - 1) = '\0';        /*NULL-terminated string*/
  }
}

void screen_destroy()
{
  if (__data)
    free(__data);
}

void screen_menu_init(int rows, int columns)
{
  screen_menu_destroy(); /* Dispose if previously initialized */
  MENU_ROWS = rows;
  MENU_COLUMNS = columns;
  __data_menu = (char *)malloc(sizeof(char) * (MENU_ROWS * MENU_COLUMNS + 1));

  if (__data_menu)
  {
    memset(__data_menu, (int)BG_CHAR, MENU_ROWS * MENU_COLUMNS); /*Fill the background*/
    *(__data_menu + (MENU_ROWS * MENU_COLUMNS)) = '\0';          /*NULL-terminated string*/
  }
}

void screen_menu_destroy()
{
  if (__data_menu)
    free(__data_menu);
}

void screen_menu_paint(Frame_color color)
{
  char *src = NULL;
  char *dest;
  int i = 0;

  if (!(dest = (char *)malloc(sizeof(char) * (MENU_COLUMNS + 1))))
  {
    return;
  }

  memset(dest, 0, MENU_COLUMNS + 1);

  if (__data_menu)
  {
    /* puts(__data); */ /*Dump data directly to the terminal*/
    /*It works fine if the terminal window has the right size*/

    puts("\033[2J"); /*Clear the terminal*/
    for (src = __data_menu; src < (__data_menu + (MENU_ROWS * MENU_COLUMNS)); src += MENU_COLUMNS)
    {
      memcpy(dest, src, MENU_COLUMNS);
      /* printf("%s\n", dest); */
      for (i = 0; i < MENU_COLUMNS; i++)
      {
        if (dest[i] == BG_CHAR)
        {
          printf("%s%c\033[0m", frame_color_to_string(color), dest[i]); /* fg:blue(34);bg:blue(44) */
        }
        else
        {
          printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:black(30);bg:white(47)*/
        }
      }
      printf("\n");
    }
  }
  free(dest);
}

void screen_paint(Frame_color color)
{
  char *src = NULL;
  char *dest = NULL;
  int i = 0;

  if (!(dest = (char *)malloc(sizeof(char) * (COLUMNS + 1))))
  {
    return;
  }

  memset(dest, 0, COLUMNS + 1);

  if (__data)
  {
    /* puts(__data); */ /*Dump data directly to the terminal*/
    /*It works fine if the terminal window has the right size*/

    puts("\033[2J"); /*Clear the terminal*/
    for (src = __data; src < (__data + TOTAL_DATA - 1); src += COLUMNS)
    {
      memcpy(dest, src, COLUMNS);
      /* printf("%s\n", dest); */
      for (i = 0; i < COLUMNS; i++)
      {
        if (dest[i] == BG_CHAR)
        {
          printf("%s%c\033[0m", frame_color_to_string(color), dest[i]); /* fg:blue(34);bg:blue(44) */
        }
        else
        {
          printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:black(30);bg:white(47)*/
        }
      }
      printf("\n");
    }
  }
  free(dest);
}

char *frame_color_to_string(Frame_color color)
{
  switch (color)
  {
  case BLACK:
    return "\033[0;30;40m";
    break;
  case RED:
    return "\033[0;34;41m";
    break;
  case GREEN:
    return "\033[0;34;42m";
    break;
  case YELLOW:
    return "\033[0;34;43m";
    break;
  case BLUE:
    return "\033[0;34;44m";
    break;
  case PURPLE:
    return "\033[0;34;45m";
    break;
  case CYAN:
    return "\033[0;34;46m";
    break;
  case WHITE:
    return "\033[0;34;47m";
    break;

  default:
    break;
  }
  return "\033[0;34;40m";
}

Area *screen_area_init(int x, int y, int width, int height)
{
  int i = 0;
  Area *area = NULL;

  if ((area = (Area *)malloc(sizeof(struct _Area))))
  {
    *area = (struct _Area){x, y, width, height, ACCESS(__data, x, y)};

    for (i = 0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int)FG_CHAR, (size_t)area->width);
  }

  return area;
}

Area *screen_area_init_menu(int x, int y, int width, int height)
{
  int i = 0;
  Area *area = NULL;

  if (width > 0 && height > 0)
  {
    if ((area = (Area *)malloc(sizeof(struct _Area))))
    {
      *area = (struct _Area){x, y, width, height, ACCESS_MENU(__data_menu, x, y)};

      for (i = 0; i < area->height; i++)
        memset(ACCESS_MENU(area->cursor, 0, i), (int)FG_CHAR, (size_t)area->width);
    }
  }
  return area;
}

void screen_area_destroy(Area *area)
{
  if (area)
    free(area);
}

void screen_area_clear(Area *area)
{
  int i = 0;

  if (area)
  {
    screen_area_reset_cursor(area);

    for (i = 0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int)FG_CHAR, (size_t)area->width);
  }
}

void screen_area_clear_menu(Area *area)
{
  int i = 0;

  if (area)
  {
    screen_area_reset_cursor_menu(area);

    for (i = 0; i < area->height; i++)
      memset(ACCESS_MENU(area->cursor, 0, i), (int)FG_CHAR, (size_t)area->width);
  }
}

void screen_area_reset_cursor_menu(Area *area)
{
  if (area)
    area->cursor = ACCESS_MENU(__data_menu, area->x, area->y);
}

void screen_area_reset_cursor(Area *area)
{
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

void screen_area_puts(Area *area, char *str)
{
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);

  screen_utils_replaces_special_chars(str);

  if (area->width > 0)
  {
    for (ptr = str; ptr < (str + strlen(str)); ptr += area->width)
    {
      memset(area->cursor, FG_CHAR, area->width);
      len = (strlen(ptr) < area->width) ? strlen(ptr) : area->width;
      memcpy(area->cursor, ptr, len);
      area->cursor += COLUMNS;
    }
  }
}

void screen_area_puts_menu(Area *area, char *str)
{
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds_menu(area))
    screen_area_scroll_up_menu(area);

  screen_utils_replaces_special_chars(str);

  if (area->width > 0)
  {
    for (ptr = str; ptr < (str + strlen(str)); ptr += area->width)
    {
      memset(area->cursor, FG_CHAR, area->width);
      len = (strlen(ptr) < area->width) ? strlen(ptr) : area->width;
      memcpy(area->cursor, ptr, len);
      area->cursor += MENU_COLUMNS;
    }
  }
}

int screen_area_cursor_is_out_of_bounds_menu(Area *area)
{
  return area->cursor > ACCESS_MENU(__data,
                                    area->x + area->width,
                                    area->y + area->height - 1);
}

int screen_area_cursor_is_out_of_bounds(Area *area)
{
  return area->cursor > ACCESS(__data,
                               area->x + area->width,
                               area->y + area->height - 1);
}

void screen_area_scroll_up_menu(Area *area)
{
  for (area->cursor = ACCESS_MENU(__data_menu, area->x, area->y);
       area->cursor < ACCESS_MENU(__data_menu, area->x + area->width, area->y + area->height - 2);
       area->cursor += MENU_COLUMNS)
  {
    memcpy(area->cursor, area->cursor + MENU_COLUMNS, area->width);
  }
}

void screen_area_scroll_up(Area *area)
{
  for (area->cursor = ACCESS(__data, area->x, area->y);
       area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
       area->cursor += COLUMNS)
  {
    memcpy(area->cursor, area->cursor + COLUMNS, area->width);
  }
}

void screen_utils_replaces_special_chars(char *str)
{
  char *pch = NULL;

  /* Replaces acutes and tilde with '??' */
  while ((pch = strpbrk(str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}
