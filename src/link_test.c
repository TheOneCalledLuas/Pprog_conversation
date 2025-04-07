/**
 * @brief It tests link module
 *
 * @file link_test.c
 * @author Irene García
 * @version 3.2
 * @date 19-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "link_test.h"
#include "test.h"

/**
 * Total test number.
 */
#define MAX_TESTS 20

/**
 * @brief Main function which manages the tests.
 *
 *  You can decide which test you want to run
 *  or run all the tests.
 *
 * @author Irene García
 */
int main(int argc, char **argv)
{
    int test = 0;
    int all = 1;

    /*Decides which tests to execute.*/
    if (argc < 2)
    {
        /*Runs all.*/
        printf("Running all test for the module link.c:\n");
    }
    else
    {
        /*Runs a single one.*/
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
        test1_link_create();
    if (all || test == 2)
        test2_link_create();
    if (all || test == 3)
        test3_link_create();
    if (all || test == 4)
        test1_link_get_id();
    if (all || test == 5)
        test2_link_get_id();
    if (all || test == 6)
        test1_link_get_name();
    if (all || test == 7)
        test2_link_get_name();
    if (all || test == 8)
        test1_link_get_origin();
    if (all || test == 9)
        test2_link_get_origin();
    if (all || test == 10)
        test1_link_get_destination();
    if (all || test == 11)
        test2_link_get_destination();
    if (all || test == 12)
        test1_link_get_direction();
    if (all || test == 13)
        test2_link_get_direction();
    if (all || test == 14)
        test1_link_get_state();
    if (all || test == 15)
        test2_link_get_state();
    if (all || test == 16)
        test1_link_set_origin();
    if (all || test == 17)
        test2_link_set_origin();
    if (all || test == 18)
        test3_link_set_origin();
    if (all || test == 19)
        test4_link_set_origin();
    if (all || test == 20)
        test4_link_set_destination();
    if (all || test == 21)
        test1_link_set_destination();
    if (all || test == 22)
        test2_link_set_destination();
    if (all || test == 23)
        test3_link_set_destination();
    if (all || test == 24)
        test1_link_set_name();
    if (all || test == 25)
        test2_link_set_name();
    if (all || test == 26)
        test3_link_set_name();
    if (all || test == 27)
        test4_link_set_name();
    if (all || test == 28)
        test1_link_set_direction();
    if (all || test == 29)
        test2_link_set_direction();
    if (all || test == 30)
        test1_link_set_state();
    if (all || test == 31)
        test2_link_set_state();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_link_create()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    /*Checks creation.*/
    PRINT_TEST_RESULT(l != NULL);
    /*Frees memory.*/
    link_destroy(l);
}

void test2_link_create()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    /*Checks creation.*/
    PRINT_TEST_RESULT(link_get_id(l) == 4 && link_get_origin(l) == NO_ID && link_get_destination(l) == NO_ID);
    /*Frees memory.*/
    link_destroy(l);
}

void test3_link_create()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = NO_ID;
    l = link_create(id);
    /*Checks creation.*/
    PRINT_TEST_RESULT(l == NULL);
}

void test1_link_get_id()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    PRINT_TEST_RESULT(link_get_id(l) == 4);
    /*Frees memory.*/
    link_destroy(l);
}

void test2_link_get_id()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_id(l) == ID_ERROR);
}

void test1_link_get_name()
{
    /*Creates the link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    link_set_name(l, "merchant");
    PRINT_TEST_RESULT(strcmp(link_get_name(l), "merchant") == 0);
    /*Frees the memory.*/
    link_destroy(l);
}

void test2_link_get_name()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_name(l) == NULL);
}

void test1_link_get_origin()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    link_set_origin(l, 13);
    PRINT_TEST_RESULT(link_get_origin(l) == 13);
    /*Frees memory.*/
    link_destroy(l);
}

void test2_link_get_origin()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_origin(l) == ID_ERROR);
}

void test1_link_get_destination()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    link_set_destination(l, 13);
    PRINT_TEST_RESULT(link_get_destination(l) == 13);
    /*Frees memory.*/
    link_destroy(l);
}

void test2_link_get_destination()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_destination(l) == ID_ERROR);
}

void test1_link_get_direction()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    link_set_direction(l, 13);
    PRINT_TEST_RESULT(link_get_direction(l) == 13);
    /*Frees memory.*/
    link_destroy(l);
}

void test2_link_get_direction()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_direction(l) == UNK_DIRECTION);
}

void test1_link_get_state()
{
    /*Creates a link.*/
    Link *l = NULL;
    Id id = 4;
    l = link_create(id);
    link_set_state(l, TRUE);
    PRINT_TEST_RESULT(link_get_state(l) == TRUE);
    /*Frees memory.*/
    link_destroy(l);
}

void test2_link_get_state()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_state(l) == FALSE);
}

void test1_link_set_origin()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_origin(l, NO_ID) == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test2_link_set_origin()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_origin(l, 5) == ERROR);
}

void test3_link_set_origin()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_origin(l, 5) == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test4_link_set_origin()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_origin(l, ID_ERROR) == ERROR);
    /*Frees the memory.*/
    link_destroy(l);
}

void test1_link_set_destination()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_destination(l, 13) == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test2_link_set_destination()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_destination(l, 13) == ERROR);
}

void test3_link_set_destination()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    link_set_destination(l, 12);
    PRINT_TEST_RESULT(link_set_destination(l, 13) == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test4_link_set_destination()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_destination(l, ID_ERROR) == ERROR);
    /*Frees the memory.*/
    link_destroy(l);
}

void test1_link_set_name()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_name(l, "merchant") == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test2_link_set_name()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_name(l, "merchant") == ERROR);
}

void test3_link_set_name()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    link_set_name(l, "merchant");
    PRINT_TEST_RESULT(link_set_name(l, "owo") == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test4_link_set_name()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
    /*Frees the memory.*/
    link_destroy(l);
}

void test1_link_set_direction()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_direction(l, N) == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test2_link_set_direction()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_direction(l, UNK_DIRECTION) == ERROR);
}

void test1_link_set_state()
{
    /*Creates the link.*/
    Link *l = NULL;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_state(l, TRUE) == OK);
    /*Frees the memory.*/
    link_destroy(l);
}

void test2_link_set_state()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_state(l, 0) == ERROR);
}
