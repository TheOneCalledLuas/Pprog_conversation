/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Fernando Mijangos
 * @version 1
 * @date 23-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "space_test.h"
#include "test.h"
/**
 * Number of tests.
 */
#define MAX_TESTS 51

/**
 * @brief Main function for SPACE unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all test for module Space:\n");
    }
    else
    {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS)
        {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1)
        test1_space_create();
    if (all || test == 2)
        test2_space_create();
    if (all || test == 3)
        test1_space_set_name();
    if (all || test == 4)
        test2_space_set_name();
    if (all || test == 5)
        test3_space_set_name();
    if (all || test == 6)
        test1_space_get_id();
    if (all || test == 7)
        test2_space_get_id();
    if (all || test == 86)
        test1_space_get_objects();
    if (all || test == 97)
        test2_space_get_objects();
    if (all || test == 10)
        test1_space_get_name();
    if (all || test == 11)
        test2_space_get_name();
    if (all || test == 12)
        test1_space_add_object();
    if (all || test == 13)
        test2_space_add_object();
    if (all || test == 14)
        test3_space_add_object();
    if (all || test == 15)
        test4_space_add_object();
    if (all || test == 16)
        test1_space_set_gdesc();
    if (all || test == 17)
        test2_space_set_gdesc();
    if (all || test == 18)
        test3_space_set_gdesc();
    if (all || test == 19)
        test4_space_set_gdesc();
    if (all || test == 20)
        test5_space_set_gdesc();
    if (all || test == 21)
        test1_space_find_object();
    if (all || test == 22)
        test2_space_find_object();
    if (all || test == 23)
        test3_space_find_object();
    if (all || test == 24)
        test4_space_find_object();
    if (all || test == 25)
        test5_space_find_object();
    if (all || test == 26)
        test1_space_take_object();
    if (all || test == 27)
        test2_space_take_object();
    if (all || test == 28)
        test3_space_take_object();
    if (all || test == 29)
        test4_space_take_object();
    if (all || test == 30)
        test5_space_take_object();
    if (all || test == 31)
        test1_space_get_character();
    if (all || test == 32)
        test2_space_get_character();
    if (all || test == 33)
        test3_space_get_character();
    if (all || test == 34)
        test4_space_get_character();
    if (all || test == 35)
        test1_space_set_character();
    if (all || test == 36)
        test2_space_set_character();
    if (all || test == 37)
        test3_space_set_character();
    if (all || test == 38)
        test4_space_set_character();
    if (all || test == 39)
        test1_space_get_n_objects();
    if (all || test == 40)
        test2_space_get_n_objects();
    if (all || test == 41)
        test3_space_get_n_objects();
    if (all || test == 42)
        test4_space_get_n_objects();
    if (all || test == 43)
        test1_space_get_gdesc();
    if (all || test == 44)
        test2_space_get_gdesc();
    if (all || test == 45)
        test3_space_get_gdesc();
    if (all || test == 46)
        test1_space_is_discovered();
    if (all || test == 47)
        test2_space_is_discovered();
    if (all || test == 48)
        test3_space_is_discovered();
    if (all || test == 49)
        test1_space_set_discovered();
    if (all || test == 50)
        test2_space_set_discovered();
    if (all || test == 51)
        test3_space_set_discovered();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_space_create()
{
    int result;
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks if it has been created.*/
    result = s != NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(result);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_create()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(4);
    /*Checks that it has been created with the requested id.*/
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_id(s) == 4);
    /*Frees the memory.*/
    space_destroy(s);
}

void test1_space_set_name()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Sets a name.*/
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_set_name()
{
    /* Does not create the space.*/
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Sets an invalid pointer to the name.*/
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
    /*Frees the memory.*/
    space_destroy(s);
}

void test1_space_get_objects()
{
    /*Creates the space.*/
    Space *s = NULL;
    Id *ids;
    s = space_create(5);
    space_add_object(s, 5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT((ids = space_get_objects(s)) != NULL);
    /*Frees the memory.*/
    free(ids);
    space_destroy(s);
}

void test2_space_get_objects()
{
    Space *s = NULL;
    Id *ids;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT((ids = space_get_objects(s)) == NULL);
}

void test1_space_get_name()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_set_name(s, "adios");
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_get_name()
{
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_add_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_add_object(s, NO_ID) == ERROR);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_add_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_add_object(s, 5) == OK);
    /*Frees the memory.*/
    space_destroy(s);
}

void test3_space_add_object()
{
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_add_object(s, 5) == ERROR);
}

void test4_space_add_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_add_object(s, ID_ERROR) == ERROR);
    /*Frees the memory.*/
    space_destroy(s);
}

void test1_space_find_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_add_object(s, 1);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_find_object(s, 1) == 0);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_find_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_add_object(s, 2);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_find_object(s, 1) == -1);
    /*Frees the memory.*/
    space_destroy(s);
}

void test3_space_find_object()
{
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_find_object(s, 1) == -1);
}

void test4_space_find_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_find_object(s, 1) == -1);
    /*Frees the memory.*/
    space_destroy(s);
}

void test5_space_find_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_find_object(s, NO_ID) == -1);
    /*Frees the memory.*/
    space_destroy(s);
}

void test1_space_take_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_take_object(s, 1) == ID_ERROR);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_take_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_add_object(s, 1);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_take_object(s, 1) == 1);
    /*Frees the memory.*/
    space_destroy(s);
}

void test3_space_take_object()
{
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_take_object(s, 1) == ID_ERROR);
}

void test4_space_take_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_add_object(s, 1);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_take_object(s, NO_ID) == ID_ERROR);
    /*Frees the memory.*/
    space_destroy(s);
}

void test5_space_take_object()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_add_object(s, 1);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_take_object(s, ID_ERROR) == ID_ERROR);
    /*Frees the memory.*/
    space_destroy(s);
}

void test1_space_get_id()
{
    /*Creates the space*/
    Space *s = NULL;
    s = space_create(25);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_id(s) == 25);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_get_id()
{
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_id(s) == ID_ERROR);
}

void test1_space_set_gdesc()
{
    /*Creates the space.*/
    Space *s = space_create(5);

    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_gdesc_line(s, 0, "123456789") == OK);

    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_set_gdesc()
{
    /*Does not create the space.*/
    Space *s = NULL;

    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_gdesc_line(s, 0, "123456789") == ERROR);
}

void test3_space_set_gdesc()
{
    /*Creates the space.*/
    Space *s = space_create(5);
    /*Sets an invalid line.*/
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_gdesc_line(s, -1, "123456789") == ERROR);

    /*Frees the memory.*/
    space_destroy(s);
}

void test4_space_set_gdesc()
{
    /*Creates the space.*/
    Space *s = space_create(5);
    /*Sets an invalid string.*/
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_gdesc_line(s, 0, NULL) == ERROR);

    /*Frees the memory.*/
    space_destroy(s);
}

void test5_space_set_gdesc()
{
    /*Creates the space.*/
    Space *s = space_create(5);
    /*Sets an invalid string (too long).*/
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_gdesc_line(s, 0, ("123456789+")) == ERROR);

    /*Frees the memory.*/
    space_destroy(s);
}

void test1_space_get_character()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_get_character()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_set_character(s, 5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_character(s) == 5);
    /*Frees the memory.*/
    space_destroy(s);
}

void test3_space_get_character()
{
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_character(s) == ID_ERROR);
}

void test4_space_get_character()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_set_character(s, 3);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_character(s) == 3);
    /*Frees the memory.*/
    space_destroy(s);
}

void test1_space_set_character()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_character(s, NO_ID) == OK);
    /*Frees the memory.*/
    space_destroy(s);
}

void test2_space_set_character()
{
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_character(s, 5) == ERROR);
}

void test3_space_set_character()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_character(s, 5) == OK);
    /*Frees the memory.*/
    space_destroy(s);
}

void test4_space_set_character()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_set_character(s, ID_ERROR) == ERROR);
    /*Frees the memory.*/
    space_destroy(s);
}
void test1_space_get_n_objects()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_n_objects(s) == 0);
    /*Frees the memory*/
    space_destroy(s);
}
void test2_space_get_n_objects()
{
    /*Creates the space.*/
    Space *s = NULL;
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_n_objects(s) == -1);
}
void test3_space_get_n_objects()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_add_object(s, 12);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_n_objects(s) == 1);
    /*Frees the memory*/
    space_destroy(s);
}
void test4_space_get_n_objects()
{
    /*Creates the space. */
    Space *s = NULL;
    s = space_create(5);
    space_add_object(s, -1);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_n_objects(s) == 0);
    /*Frees the memory*/
    space_destroy(s);
}

void test1_space_get_gdesc()
{
    /*Creates the space. */
    Space *s = NULL;
    char word[WORD_SIZE] = "potatoess";
    s = space_create(5);
    space_set_gdesc_line(s, 1, word);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(0 == (strcmp(word, space_get_gdesc_line(s, 1))));
    space_destroy(s);
}

void test2_space_get_gdesc()
{
    /*Creates the space. */
    Space *s = NULL;
    s = space_create(5);
    space_set_gdesc_line(s, 1, "potato");
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_gdesc_line(NULL, 1) == NULL);
    space_destroy(s);
}

void test3_space_get_gdesc()
{
    /*Creates the space. */
    Space *s = NULL;
    s = space_create(5);
    space_set_gdesc_line(s, 1, "potato");
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(space_get_gdesc_line(NULL, 1) == NULL);
    space_destroy(s);
}

void test1_space_is_discovered()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_set_discovered(s, TRUE);
    /*Checks what its needed.*/
    PRINT_TEST_RESULT(TRUE == space_is_discovered(s));
    space_destroy(s);
}
void test2_space_is_discovered()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_set_discovered(s, TRUE);
    /*Checks what its needed.*/
    PRINT_TEST_RESULT(FALSE == space_is_discovered(NULL));
    space_destroy(s);
}

void test3_space_is_discovered()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    space_set_discovered(s, FALSE);
    /*Checks what its needed.*/
    PRINT_TEST_RESULT(FALSE == space_is_discovered(s));
    space_destroy(s);
}

void test1_space_set_discovered()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(OK == space_set_discovered(s, TRUE));
    space_destroy(s);
}

void test2_space_set_discovered()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(ERROR == space_set_discovered(NULL, TRUE));
    space_destroy(s);
}

void test3_space_set_discovered()
{
    /*Creates the space.*/
    Space *s = NULL;
    s = space_create(5);
    /*Checks what is needed.*/
    PRINT_TEST_RESULT(OK == space_set_discovered(s, FALSE));
    space_destroy(s);
}