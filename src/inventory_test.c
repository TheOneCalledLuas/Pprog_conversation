/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @author Raquel Anguita Martínez de Velasco
 * @version 1
 * @date 20-03-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "types.h"
#include "inventory_test.h"
#include "test.h"

/**
 * Total test number.
 */
#define MAX_TESTS 26

/**
 * @brief Main function which manages the tests.
 *
 *  You can decide which test you want to run
 *  or run all the tests.
 *
 * @author Raquel Anguita Martínez de Velasco
 */
int main(int argc, char **argv)
{
    int test = 0;
    int all = 1;

    /*Decides which tests to execute.*/
    if (argc < 2)
    {
        /*Runs all.*/
        printf("Running all test for the module inventory.c:\n");
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
        test1_inventory_create();
    if (all || test == 2)
        test1_inventory_set_max_objs();
    if (all || test == 3)
        test2_inventory_set_max_objs();
    if (all || test == 4)
        test3_inventory_set_max_objs();
    if (all || test == 5)
        test4_inventory_set_max_objs();
    if (all || test == 6)
        test1_inventory_get_max_objs();
    if (all || test == 7)
        test2_inventory_get_max_objs();
    if (all || test == 8)
        test3_inventory_get_max_objs();
    if (all || test == 9)
        test1_inventory_find();
    if (all || test == 10)
        test2_inventory_find();
    if (all || test == 11)
        test3_inventory_find();
    if (all || test == 12)
        test4_inventory_find();
    if (all || test == 13)
        test5_inventory_find();
    if (all || test == 14)
        test1_inventory_add();
    if (all || test == 15)
        test2_inventory_add();
    if (all || test == 16)
        test3_inventory_add();
    if (all || test == 17)
        test4_inventory_add();
    if (all || test == 18)
        test5_inventory_add();
    if (all || test == 19)
        test6_inventory_add();
    if (all || test == 20)
        test1_inventory_take();
    if (all || test == 21)
        test2_inventory_take();
    if (all || test == 22)
        test3_inventory_take();
    if (all || test == 23)
        test4_inventory_take();
    if (all || test == 24)
        test1_inventory_get_content();
    if (all || test == 25)
        test2_inventory_get_content();
    if (all || test == 26)
        test3_inventory_get_content();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_inventory_create()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Checks creation. */
    PRINT_TEST_RESULT(in != NULL);
    /* Frees memory. */
    inventory_destroy(in);
}

void test1_inventory_set_max_objs()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Checks the setter. */
    PRINT_TEST_RESULT(inventory_set_max_objs(in, 1) == OK);
    /* Frees memory. */
    inventory_destroy(in);
}

void test2_inventory_set_max_objs()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Checks the setter. */
    PRINT_TEST_RESULT(inventory_set_max_objs(in, -1) == ERROR);
    /* Frees memory. */
    inventory_destroy(in);
}

void test3_inventory_set_max_objs()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Checks the setter. */
    PRINT_TEST_RESULT(inventory_set_max_objs(in, MAX_SET + 1) == ERROR);
    /* Frees memory. */
    inventory_destroy(in);
}

void test4_inventory_set_max_objs()
{
    /* Creates a null inventory. */
    Inventory *in = NULL;
    /* Checks the setter. */
    PRINT_TEST_RESULT(inventory_set_max_objs(in, 1) == ERROR);
}

void test1_inventory_get_max_objs()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Sets the value to get. */
    inventory_set_max_objs(in, 1);
    /* Checks the getter. */
    PRINT_TEST_RESULT(inventory_get_max_objs(in) == 1);
    /* Frees memory. */
    inventory_destroy(in);
}

void test2_inventory_get_max_objs()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Checks the getter with the initial value. */
    PRINT_TEST_RESULT(inventory_get_max_objs(in) == 0);
    /* Frees memory. */
    inventory_destroy(in);
}

void test3_inventory_get_max_objs()
{
    /* Creates a null inventory. */
    Inventory *in = NULL;
    /* Checks the getter. */
    PRINT_TEST_RESULT(inventory_get_max_objs(in) == -1);
}

void test1_inventory_find()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Adds an id. */
    inventory_add(in, 1);
    PRINT_TEST_RESULT(inventory_find(in, 1) != -1);
    /* Frees memory. */
    inventory_destroy(in);
}

void test2_inventory_find()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Adds an id. */
    inventory_add(in, 1);
    /* Checks for a different id than added. */
    PRINT_TEST_RESULT(inventory_find(in, 2) == -1);
    /* Frees memory. */
    inventory_destroy(in);
}

void test3_inventory_find()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /*Searches for an id that hasn't been added.*/
    PRINT_TEST_RESULT(inventory_find(in, 1) == -1);
    /* Frees memory. */
    inventory_destroy(in);
}

void test4_inventory_find()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Adds many ids. */
    inventory_add(in, 1);
    inventory_add(in, 2);
    inventory_add(in, 3);
    /* Checks if the position returned is the correct one. */
    PRINT_TEST_RESULT(inventory_find(in, 2) == 1);
    /* Frees memory. */
    inventory_destroy(in);
}

void test5_inventory_find()
{
    /* Creates a null inventory. */
    Inventory *in = NULL;
    /* Checks if a null inventory causes error. */
    PRINT_TEST_RESULT(inventory_find(in, 1) == -1);
}

void test1_inventory_add()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Sets a valid value to max_objs. */
    inventory_set_max_objs(in, 1);
    /* Checks adding an id. */
    PRINT_TEST_RESULT(inventory_add(in, 1) == OK);
    /* Frees memory. */
    inventory_destroy(in);
}

void test2_inventory_add()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Sets a valid value to max_objs. */
    inventory_set_max_objs(in, 1);
    /* Checks adding an invalid id. */
    PRINT_TEST_RESULT(inventory_add(in, ID_ERROR) == ERROR);
    /* Frees memory. */
    inventory_destroy(in);
}

void test3_inventory_add()
{
    /* Creates a null inventory. */
    Inventory *in = NULL;
    /* Checks adding an id. */
    PRINT_TEST_RESULT(inventory_add(in, 1) == ERROR);
}

void test4_inventory_add()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Checks adding an id without enough space. */
    PRINT_TEST_RESULT(inventory_add(in, 1) == ERROR);
    /* Frees memory. */
    inventory_destroy(in);
}

void test5_inventory_add()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Sets a valid value to max_objs. */
    inventory_set_max_objs(in, 2);
    /* Adds an id. */
    inventory_add(in, 1);
    /* Checks if you can add the same id again. */
    PRINT_TEST_RESULT(inventory_add(in, 1));
    /* Frees memory. */
    inventory_destroy(in);
}

void test6_inventory_add()
{
    /* Creates an inventory. */
    Inventory *in;
    long len1, len2;
    in = inventory_create();
    /* Sets a valid value to max_objs. */
    inventory_set_max_objs(in, 2);
    /* Adds the same id twice, checking the inventory size after each. */
    inventory_add(in, 1);
    len1 = inventory_len(in);
    inventory_add(in, 1);
    len2 = inventory_len(in);
    /* Checks if both sizes are equal. */
    PRINT_TEST_RESULT(len1 == len2);
    /* Frees memory. */
    inventory_destroy(in);
}

void test1_inventory_take()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Adds an id. */
    inventory_add(in, 1);
    /* Test if the function works as expected. */
    PRINT_TEST_RESULT(inventory_take(in, 1) == 1);
    /* Frees memory. */
    inventory_destroy(in);
}

void test2_inventory_take()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Test if the function works as expected. */
    PRINT_TEST_RESULT(inventory_take(in, 1) == ID_ERROR);
    /* Frees memory. */
    inventory_destroy(in);
}

void test3_inventory_take()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    /* Adds an id and then takes it out with inventory_take. */
    inventory_add(in, 1);
    inventory_take(in, 1);
    /* Test if the function works as expected. */
    PRINT_TEST_RESULT(inventory_take(in, 1) == ID_ERROR);
    /* Frees memory. */
    inventory_destroy(in);
}

void test4_inventory_take()
{
    /* Creates a null inventory. */
    Inventory *in = NULL;
    /* Test if the function works as expected. */
    PRINT_TEST_RESULT(inventory_take(in, 1) == ID_ERROR);
}

void test1_inventory_get_content()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    Id *ids = NULL;
    /* Adds many ids. */
    inventory_add(in, 1);
    inventory_add(in, 2);
    inventory_add(in, 3);
    /* Test if the function works as expected. */
    PRINT_TEST_RESULT((ids = inventory_get_content(in)) != NULL);
    /* Frees memory. */
    inventory_destroy(in);
    free(ids);
}

void test2_inventory_get_content()
{
    /* Creates an inventory. */
    Inventory *in;
    in = inventory_create();
    Id *ids = NULL;
    /* Test if the function works as expected. */
    PRINT_TEST_RESULT((ids = inventory_get_content(in)) == NULL);
    /* Frees memory. */
    inventory_destroy(in);
    free(ids);
}

void test3_inventory_get_content()
{
    /* Creates a null inventory. */
    Inventory *in = NULL;
    Id *ids = NULL;
    /* "Adds" many ids. */
    inventory_add(in, 1);
    inventory_add(in, 2);
    inventory_add(in, 3);
    /* Test if the function works as expected. */
    PRINT_TEST_RESULT((ids = inventory_get_content(in)) == NULL);
    /* Frees memory. */
    free(ids);
}