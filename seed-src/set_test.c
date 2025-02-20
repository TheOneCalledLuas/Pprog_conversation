/**
 * @brief It tests space module
 *
 * @file set_test.c
 * @author Saul Lopez Romero
 * @version 0.0
 * @date 19-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "types.h"
#include "set_test.h"
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
 * @author Saul Lopez Romero
 */
int main(int argc, char **argv)
{
    int test = 0;
    int all = 1;

    /*Decides which tests to execute.*/
    if (argc < 2)
    {
        /*Runs all.*/
        printf("Running all test for the module set.c:\n");
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
        test1_set_create();
    if (all || test == 2)
        test1_set_add();
    if (all || test == 3)
        test2_set_add();
    if (all || test == 4)
        test3_set_add();
    if (all || test == 5)
        test4_set_add();
    if (all || test == 6)
        test5_set_add();
    if (all || test == 7)
        test1_set_increment();
    if (all || test == 8)
        test1_set_len();
    if (all || test == 9)
        test2_set_len();
    if (all || test == 10)
        test3_set_len();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_set_create()
{
    /*Creates a set.*/
    Set *s = NULL;
    s = set_create();
    /*Checks creation.*/
    PRINT_TEST_RESULT(s != NULL);
    /*Frees memory.*/
    set_destroy(s);
}

void test1_set_len()
{
    /*Creates a set.*/
    Set *s = NULL;
    s = set_create();
    /*Checks creation.*/
    PRINT_TEST_RESULT(set_len(s) == 0);
    /*Frees memory.*/
    set_destroy(s);
}

void test2_set_len()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;
    s = set_create();
    set_add(s, id);
    /*Checks creation.*/
    PRINT_TEST_RESULT(set_len(s) == 1);
    /*Frees memory.*/
    set_destroy(s);
}

void test3_set_len()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;
    s = set_create();
    set_add(s, id);
    set_take(s,id);
    /*Checks creation.*/
    PRINT_TEST_RESULT(set_len(s) == 0);
    /*Frees memory.*/
    set_destroy(s);
}

void test1_set_increment()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id1 = 1, id2 = 2;
    int len1 = 0, len2 = 0;
    s = set_create();

    /*Teest management.*/
    set_add(s, id1);
    len1 = set_len(s);
    set_add(s, id2);
    len2 = set_len(s);
    PRINT_TEST_RESULT(len1 + 1 == len2);

    /*Frees memory.*/
    set_destroy(s);
}

void test1_set_add()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;
    s = set_create();
    PRINT_TEST_RESULT(set_add(s, id) == OK);
    /*Frees memory.*/
    set_destroy(s);
}

void test2_set_add()
{
    /*Creates a NULL set.*/
    Set *s = NULL;
    Id id = 1;
    PRINT_TEST_RESULT(set_add(s, id) == ERROR);
}

void test3_set_add()
{
    /*Creates a NULL set.*/
    Set *s = NULL;
    int i = 0;
    Id id = 1;

    s = set_create();

    /*Makes the set full.*/
    for (i = 0; i < 50; i++)
    {
        set_add(s, id);
        id++;
    }

    PRINT_TEST_RESULT(set_add(s, id) == ERROR);
    /*Frees memory.*/
    set_destroy(s);
}

void test4_set_add()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;
    int n_id = 0;
    s = set_create();

    /*Adds the id for the first time.*/
    set_add(s, id);
    n_id = set_len(s);

    PRINT_TEST_RESULT(set_add(s, id) == OK && n_id == set_len(s));

    /*Frees memory.*/
    set_destroy(s);
}

void test5_set_add()
{
    /*Creates a set.*/
    Set *s = NULL;
    s = set_create();

    PRINT_TEST_RESULT(set_add(s, -2) == ERROR);

    /*Frees memory.*/
    set_destroy(s);
}

void test1_set_find()
{
}