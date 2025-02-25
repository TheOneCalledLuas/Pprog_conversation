/**
 * @brief It tests space module
 *
 * @file set_test.c
 * @author Saul Lopez Romero
 * @version 3.2
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
    if (all || test == 11)
        test1_set_find();
    if (all || test == 12)
        test2_set_find();
    if (all || test == 13)
        test3_set_find();
    if (all || test == 14)
        test4_set_find();
    if (all || test == 15)
        test5_set_find();
    if (all || test == 16)
        test1_set_take();
    if (all || test == 17)
        test2_set_take();
    if (all || test == 18)
        test3_set_take();
    if (all || test == 19)
        test4_set_take();
    if (all || test == 20)
        test5_set_take();

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
    set_take(s, id);
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
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;
    s = set_create();

    /*Adds an id.*/
    set_add(s, id);
    PRINT_TEST_RESULT(set_find(s, id) != -1);

    /*Frees memory.*/
    set_destroy(s);
}
void test2_set_find()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1, no_id = 2;
    s = set_create();

    /*Adds an id.*/
    set_add(s, id);
    PRINT_TEST_RESULT(set_find(s, no_id) == -1);

    /*Frees memory.*/
    set_destroy(s);
}

void test3_set_find()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;
    s = set_create();

    /*Searches for an id.*/
    PRINT_TEST_RESULT(set_find(s, id) == -1);

    /*Frees memory.*/
    set_destroy(s);
}

void test4_set_find()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1, id_2 = 2, id_3 = 3;
    s = set_create();

    set_add(s, id);
    set_add(s, id_2);
    set_add(s, id_3);
    /*Adds an id.*/
    PRINT_TEST_RESULT(set_find(s, id_2) == 1);

    /*Frees memory.*/
    set_destroy(s);
}

void test5_set_find()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;

    /*Adds an id.*/
    PRINT_TEST_RESULT(set_find(s, id) == -1);
}

void test1_set_take()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1,id_res =0;
    s = set_create();

    /*Adds an id.*/
    set_add(s, id);
    id_res = set_take(s,id);
    PRINT_TEST_RESULT(id_res == id);

    /*Frees the memory.*/
    set_destroy(s);
}

void test2_set_take()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1;

    PRINT_TEST_RESULT(set_take(s, id) == ID_ERROR);

    /*Frees the memory.*/
    set_destroy(s);
}

void test3_set_take()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1, s_id = 2;

    s = set_create();

    /*Adds an id.*/
    set_add(s, s_id);
    PRINT_TEST_RESULT(set_take(s, id) == ID_ERROR);

    /*Frees the memory.*/
    set_destroy(s);
}

void test4_set_take()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1, id_2 = 2;

    s = set_create();

    /*Adds an id.*/
    set_add(s, id);
    set_add(s, id_2);
    set_take(s, id);
    PRINT_TEST_RESULT(set_take(s, id) == ID_ERROR);

    /*Frees the memory.*/
    set_destroy(s);
}

void test5_set_take()
{
    /*Creates a set.*/
    Set *s = NULL;
    Id id = 1, id_2 = 2, id_3 = 3, id_taken_1 = 0, id_taken_2 = 0, id_taken_3 = 0, id_taken_4 = 0;

    s = set_create();

    /*Adds an id.*/
    set_add(s, id);
    set_add(s, id_2);
    set_add(s, id_3);
    id_taken_1 = set_take(s, id_2);
    id_taken_2 = set_take(s, id_2);
    set_add(s, id_2);
    id_taken_3 = set_take(s, id);
    id_taken_4 = set_take(s, id_3);
    
    PRINT_TEST_RESULT(id_taken_1 == id_2 && id_taken_2 == ID_ERROR && id_taken_3 == id && id_taken_4 == id_3 && set_len(s) == 1);

    /*Frees the memory.*/
    set_destroy(s);
}