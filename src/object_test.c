/**
 * @brief It tests the object module
 *
 * @file object_test.c
 * @author Fernando Mijangos
 * @version 3.2
 * @date 02-04-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object_test.h"
#include "object.h"
#include "test.h"

/**
 * Total test number.
 */
#define MAX_TESTS 46

/**
 * @brief Main function which manages the tests.
 *
 *  You can decide which test you want to run
 *  or run all the tests.
 *
 * @author Fernando Mijangos.
 */
int main(int argc, char **argv)
{
    int test = 0;
    int all = 1;

    /*Decides which tests to execute.*/
    if (argc < 2)
    {
        /*Runs all.*/
        printf("Running all test for the module object.c:\n");
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
        test1_object_create();
    if (all || test == 2)
        test2_object_create();
    if (all || test == 3)
        test3_object_create();
    if (all || test == 4)
        test1_object_get_gdesc();
    if (all || test == 5)
        test2_object_get_gdesc();
    if (all || test == 6)
        test3_object_get_gdesc();
    if (all || test == 7)
        test1_object_set_description();
    if (all || test == 8)
        test2_object_set_description();
    if (all || test == 9)
        test3_object_set_description();
    if (all || test == 10)
        test4_object_set_description();
    if (all || test == 11)
        test1_object_get_name();
    if (all || test == 12)
        test2_object_get_name();
    if (all || test == 13)
        test3_object_get_name();
    if (all || test == 14)
        test1_object_set_name();
    if (all || test == 15)
        test2_object_set_name();
    if (all || test == 16)
        test3_object_set_name();
    if (all || test == 17)
        test4_object_set_name();
    if (all || test == 18)
        test1_object_get_id();
    if (all || test == 19)
        test2_object_get_id();
    if (all || test == 20)
        test3_object_get_id();
    if (all || test == 21)
        test1_object_set_health();
    if (all || test == 22)
        test1_object_get_health();
    if (all || test == 23)
        test1_object_set_movable();
    if (all || test == 24)
        test1_object_get_movable();
    if (all || test == 25)
        test2_object_get_movable();
    if (all || test == 26)
        test1_object_set_dependency();
    if (all || test == 27)
        test2_object_set_description();
    if (all || test == 28)
        test1_object_get_dependency();
    if (all || test == 29)
        test1_object_set_open();
    if (all || test == 30)
        test2_object_set_open();
    if (all || test == 31)
        test1_object_get_open();
    if(all || test == 32)
        test1_object_set_texture_line();
    if(all || test == 33)
        test2_object_set_texture_line();
    if(all || test == 34)
        test3_object_set_texture_line();
    if(all || test == 35)   
        test4_object_set_texture_line();
    if(all || test == 36)
        test1_object_get_texture_line();
    if(all || test == 37)
        test2_object_get_texture_line();
    if(all || test == 38)
        test3_object_get_texture_line();
    if(all || test == 39)
        test1_object_set_is_used();
    if(all || test == 40)
        test2_object_set_is_used();
    if(all || test == 41)
        test1_object_get_is_used();
    if(all || test == 42)
        test2_object_get_is_used();
    if(all || test == 43)
        test1_object_set_special_use();
    if(all || test == 44)
        test2_object_set_special_use();
    if(all || test == 45)
        test1_object_get_special_use();
    if(all || test == 46)   
        test2_object_get_special_use();


    /*Prints the passed perecentage.*/
    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_object_create()
{
    /*Creates an object.*/
    Object *o = NULL;
    o = object_create(5);
    /*Checks creation.*/
    PRINT_TEST_RESULT(o != NULL);
    /*Frees the memory.*/
    object_destroy(o);
}

void test2_object_create()
{
    /*Puts an invalid id*/
    Object *o = NULL;
    o = object_create(NO_ID);
    /*Checks creation.*/
    PRINT_TEST_RESULT(o == NULL);
}

void test3_object_create()
{
    /*Puts an invalid id*/
    Object *o = NULL;
    o = object_create(ID_ERROR);
    /*Checks creation.*/
    PRINT_TEST_RESULT(o == NULL);
}

void test1_object_get_gdesc()
{
    /*Creates an object.*/
    Object *o = NULL;
    o = object_create(5);
    /*Sets the gdesc*/
    object_set_description(o, "potato");
    /*Checks.*/
    PRINT_TEST_RESULT(0 == strcmp("potato", object_get_description(o)));
    /*Frees the memory.*/
    object_destroy(o);
}

void test2_object_get_gdesc()
{
    /*Creates an object.*/
    Object *o = NULL;
    o = object_create(5);
    /*Checks.*/
    PRINT_TEST_RESULT(0 != strcmp("potato", object_get_description(o)));
    /*Frees the memory.*/
    object_destroy(o);
}

void test3_object_get_gdesc()
{
    /*Creates an object.*/
    Object *o = NULL;
    o = object_create(5);
    /*Sets the gdesc*/
    object_set_description(o, "potato");
    /*Checks, but passes a NULL as object.*/
    PRINT_TEST_RESULT(object_get_description(NULL) == NULL);
    /*Frees the memory.*/
    object_destroy(o);
}

void test1_object_set_description()
{
    /*Creates an object.*/
    Object *o = NULL;
    o = object_create(5);
    /*Sets the gdesc and checks*/
    PRINT_TEST_RESULT(OK == object_set_description(o, "potato"));
    /*Frees the memory.*/
    object_destroy(o);
}

void test2_object_set_description()
{
    /*Creates an object.*/
    Object *o = NULL;
    o = object_create(5);
    /*Sets the gdesc and checks*/
    PRINT_TEST_RESULT(ERROR == object_set_description(o, NULL));
    /*Frees the memory.*/
    object_destroy(o);
}

void test3_object_set_description()
{
    /*Creates an object.*/
    Object *o = NULL;
    o = object_create(5);
    /*Sets the gdesc and checks*/
    PRINT_TEST_RESULT(ERROR == object_set_description(NULL, "patata"));
    /*Frees the memory.*/
    object_destroy(o);
}

void test4_object_set_description()
{
    Object *o = NULL;
    char str[305];
    /*Creates an object.*/
    o = object_create(5);
    /*Creates an oversized string.*/
    sprintf(str, "%300s", "a");
    /*Sets the gdesc and checks*/
    PRINT_TEST_RESULT(ERROR == object_set_description(o, str));
    /*Frees the memory.*/
    object_destroy(o);
}

void test1_object_get_name()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the name.*/
    object_set_name(o, "potato");
    /*Compares the results*/
    PRINT_TEST_RESULT(!(strcmp("potato", object_get_name(o))));
    /*Frees the memory.*/
    object_destroy(o);
}

void test2_object_get_name()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Puts the name to NULL, althought its already initialized to NULL.*/
    object_set_name(o, NULL);
    /*Compares the results, with a NULL as string*/
    PRINT_TEST_RESULT(0 != (strcmp("potato", object_get_name(o))));
    /*Frees the memory.*/
    object_destroy(o);
}

void test3_object_get_name()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the name.*/
    object_set_name(o, "potato");
    /*Compares the results, but the object the thing is searching is NULL*/
    PRINT_TEST_RESULT(object_get_name(NULL) == NULL);
    /*Frees the memory.*/
    object_destroy(o);
}

void test1_object_set_name()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the name and checks.*/
    PRINT_TEST_RESULT(object_set_name(o, "potato") == OK);
    /*Frees the memory.*/
    object_destroy(o);
}

void test2_object_set_name()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the name to NULL and checks.*/
    PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
    /*Frees the memory.*/
    object_destroy(o);
}

void test3_object_set_name()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the name and checks, but it uses a NULL as object.*/
    PRINT_TEST_RESULT(object_set_name(NULL, "potato") == ERROR);
    /*Frees the memory.*/
    object_destroy(o);
}

void test4_object_set_name()
{
    Object *o = NULL;
    char str[102];
    /*Creates an object.*/
    o = object_create(5);
    /*Creates an oversized string.*/
    sprintf(str, "%100s", "a");
    /*Sets the name and checks.*/
    PRINT_TEST_RESULT(object_set_name(o, str) == ERROR);
    /*Frees the memory.*/
    object_destroy(o);
}

void test1_object_get_id()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Checks the id.*/
    PRINT_TEST_RESULT(5 == object_get_id(o));
    /*Frees the memory.*/
    object_destroy(o);
}

void test2_object_get_id()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Checks the id, but the object is set to NULL.*/
    PRINT_TEST_RESULT(ID_ERROR == object_get_id(NULL));
    /*Frees the memory.*/
    object_destroy(o);
}

void test3_object_get_id()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(-6);
    /*Checks the id again , cause why not.*/
    PRINT_TEST_RESULT(-6 == object_get_id(o));
    /*Frees the memory.*/
    object_destroy(o);
}

void test1_object_set_health()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Test the starting value of health.*/
    PRINT_TEST_RESULT(OK == object_set_health(o, 7));
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_get_health()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    object_set_health(o, 7);
    /*Tests the starting value of health.*/
    PRINT_TEST_RESULT(7 == object_get_health(o));
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_set_movable()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Checks if an object is movable*/
    PRINT_TEST_RESULT(OK == object_set_movable(o, FALSE));
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_get_movable()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    object_set_movable(o, TRUE);
    /*Checks the starting value of movable.*/
    PRINT_TEST_RESULT(TRUE == object_get_movable(o));
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_get_movable()
{
    Object *o = NULL;
    /*Creates an object.*/
    /*Checks if an object is movable*/
    PRINT_TEST_RESULT(object_get_movable(o)==FALSE);
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_set_dependency()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the value.*/
    PRINT_TEST_RESULT(OK == object_set_dependency(o, 1));
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_set_dependency()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Checks dapendency's value*/
    PRINT_TEST_RESULT(ERROR == object_set_dependency(o, ID_ERROR));
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_get_dependency()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the dependency*/
    object_set_dependency(o, 1);
    PRINT_TEST_RESULT(object_get_dependency(o));
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_set_open()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the value.*/
    PRINT_TEST_RESULT(object_set_open(o, 1) == OK);
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_set_open()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets a negative value.*/
    PRINT_TEST_RESULT(object_set_open(o, ID_ERROR) == ERROR);
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_get_open()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the open value*/
    object_set_open(o, 1);
    PRINT_TEST_RESULT(object_get_open(o));
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_set_texture_line()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the value.*/
    PRINT_TEST_RESULT(object_set_texture_line(o, 1, "potato") == OK);
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_set_texture_line()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets a wrong value.*/
    PRINT_TEST_RESULT(object_set_texture_line(o, 1, NULL) == ERROR);
    /*Frees the memory*/
    object_destroy(o);
}

void test3_object_set_texture_line()
{
    Object *o = NULL;
    /*Uses a NULL as object*/
    PRINT_TEST_RESULT(object_set_texture_line(o, 1, "potato") == ERROR);
}

void test4_object_set_texture_line()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the gdesc and checks*/
    PRINT_TEST_RESULT(object_set_texture_line(o, 72, "potato") == ERROR);
    /*Frees the memory.*/
    object_destroy(o);
}

void test1_object_get_texture_line()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the texture line*/
    object_set_texture_line(o, 1, "potato");
    /*Checks the value*/
    PRINT_TEST_RESULT(0 == strcmp("potato", object_get_texture_line(o, 1)));
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_get_texture_line()
{
    Object *o = NULL;
    /*Checks the value, but the object is set to NULL*/
    PRINT_TEST_RESULT(object_get_texture_line(o, 1) == NULL);
}

void test3_object_get_texture_line()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Checks the value*/
    PRINT_TEST_RESULT(NULL==object_get_texture_line(o, 10));
    /*Frees the memory*/
    object_destroy(o);
}

void test1_object_set_is_used()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the value.*/
    PRINT_TEST_RESULT(object_set_is_used(o, TRUE) == OK);
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_set_is_used()
{
    Object *o = NULL;
    /*Uses a NULL object*/
    PRINT_TEST_RESULT(object_set_is_used(o, TRUE) == ERROR);
}

void test1_object_get_is_used()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the value*/
    object_set_is_used(o, TRUE);
    /*Checks the value*/
    PRINT_TEST_RESULT(object_get_is_used(o) == TRUE);
    /*Frees the memory*/
    object_destroy(o);
}
void test2_object_get_is_used()
{
    Object *o = NULL;
    /*Uses a NULL as object*/
    PRINT_TEST_RESULT(object_get_is_used(o) == FALSE);
}

void test1_object_set_special_use()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the value.*/
    PRINT_TEST_RESULT(object_set_special_use(o, TRUE) == OK);
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_set_special_use()
{
    Object *o = NULL;
    /*Uses a NULL object*/
    PRINT_TEST_RESULT(object_set_special_use(o, TRUE) == ERROR);
}

void test1_object_get_special_use()
{
    Object *o = NULL;
    /*Creates an object.*/
    o = object_create(5);
    /*Sets the value*/
    object_set_special_use(o, TRUE);
    /*Checks the value*/
    PRINT_TEST_RESULT(object_get_special_use(o) == TRUE);
    /*Frees the memory*/
    object_destroy(o);
}

void test2_object_get_special_use()
{
    Object *o = NULL;
    /*Uses a NULL as object*/
    PRINT_TEST_RESULT(object_get_special_use(o) == FALSE);
}