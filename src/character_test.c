/**
 * @brief It tests the character module
 *
 * @file character_test.c
 * @author Fernando Mijangos
 * @version 1
 * @date 23-02-2025
 * @copyright GNU Public License
 */

#include "character.h"
#include "types.h"
#include "test.h"
#include "character_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 30 /*!<Maximun number of tests.*/

/**
 * @brief Main function for CHRACTER unit tests.
 *
 * You may execute ALL or a SINGLE test:
 *   1.- No parameter -> ALL test are executed.
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed.
 *
 */
int main(int argc, char **argv)
{

    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all test for module Character:\n");
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
        test1_character_create();
    if (all || test == 2)
        test2_character_create();
    if (all || test == 3)
        test1_character_get_id();
    if (all || test == 4)
        test2_character_get_id();
    if (all || test == 5)
        test1_character_set_name();
    if (all || test == 6)
        test2_character_set_name();
    if (all || test == 7)
        test3_character_set_name();
    if (all || test == 8)
        test4_character_set_name();
    if (all || test == 9)
        test1_character_get_name();
    if (all || test == 10)
        test2_character_get_name();
    if (all || test == 11)
        test1_character_set_description();
    if (all || test == 12)
        test2_character_set_description();
    if (all || test == 13)
        test3_character_set_description();
    if (all || test == 14)
        test4_character_set_description();
    if (all || test == 15)
        test1_character_get_description();
    if (all || test == 16)
        test2_character_get_description();
    if (all || test == 17)
        test1_character_set_friendly();
    if (all || test == 18)
        test2_character_set_friendly();
    if (all || test == 19)
        test3_character_set_friendly();
    if (all || test == 20)
        test4_character_set_friendly();
    if (all || test == 21)
        test1_character_get_friendly();
    if (all || test == 22)
        test2_character_get_friendly();
    if (all || test == 23)
        test1_character_set_message();
    if (all || test == 24)
        test2_character_set_message();
    if (all || test == 25)
        test3_character_set_message();
    if (all || test == 26)
        test4_character_set_message();
    if (all || test == 27)
        test1_character_get_message();
    if (all || test == 28)
        test2_character_get_message();
    if (all || test == 29)
        test1_character_get_follow();
    if (all || test == 30)
        test2_character_get_follow();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_character_create()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character!=NULL);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_create()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(-1);
    PRINT_TEST_RESULT(character == NULL);
}

void test1_character_get_id()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_get_id(character) == 5);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_get_id()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_id(character) == ID_ERROR);
}

void test1_character_set_name()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_name(character, "SI") == OK);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_set_name()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_name(character, NULL) == ERROR);
    /*Frees the character.*/
    character_destroy(character);;
}

void test3_character_set_name()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    PRINT_TEST_RESULT(character_set_name(character, "SI") == ERROR);
}

void test4_character_set_name()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    PRINT_TEST_RESULT(character_set_name(character, NULL) == ERROR);
}

void test1_character_get_name()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    character_set_name(character, "SI");
    PRINT_TEST_RESULT(strcmp(character_get_name(character), "SI") == 0);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_get_name()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    character_set_name(character, "SI");
    PRINT_TEST_RESULT(strcmp(character_get_name(character), "NO") != 0);
    /*Frees the character.*/
    character_destroy(character);;
}

void test1_character_set_description()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_description(character, "SI") == OK);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_set_description()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    PRINT_TEST_RESULT(character_set_description(character, "SI") == ERROR);
}

void test3_character_set_description()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_description(character, NULL) == ERROR);
    /*Frees the character.*/
    character_destroy(character);;
}

void test4_character_set_description()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    PRINT_TEST_RESULT(character_set_description(character, NULL) == ERROR);
    /*Frees the character.*/
    character_destroy(character);;
}

void test1_character_get_description()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    character_set_description(character, "SI");
    PRINT_TEST_RESULT(strcmp(character_get_description(character), "SI") == 0);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_get_description()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_description(character) == NULL);
}

void test1_character_set_friendly()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_friendly(character, TRUE) == OK);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_set_friendly()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    PRINT_TEST_RESULT(character_set_friendly(character, TRUE) == ERROR);
}

void test3_character_set_friendly()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_friendly(character, FALSE) == OK);
    /*Frees the character.*/
    character_destroy(character);;
}

void test4_character_set_friendly()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_friendly(character, -1) == ERROR);
    /*Frees the character.*/
    character_destroy(character);;
}

void test1_character_get_friendly()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    character_set_friendly(character, TRUE);
    PRINT_TEST_RESULT(character_get_friendly(character) == TRUE);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_get_friendly()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character_set_friendly(character, TRUE);
    PRINT_TEST_RESULT(character_get_friendly(character) ==FALSE);
}

void test1_character_set_message()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_message(character, "SI") == OK);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_set_message()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_set_message(character, NULL) == ERROR);
    /*Frees the character.*/
    character_destroy(character);;
}

void test3_character_set_message()
{
    Character *character=NULL;
    PRINT_TEST_RESULT(character_set_message(character, "SI")==ERROR);
}

void test4_character_set_message()
{
    Character *character=NULL;
    PRINT_TEST_RESULT(character_set_message(character, NULL)==ERROR);
    /*Frees the character.*/
    character_destroy(character);;
}

void test1_character_get_message()
{
    Character *character=NULL;
    character=character_create(5);
    character_set_message(character, "SI");
    PRINT_TEST_RESULT(strcmp(character_get_message(character), "SI")==0);
    /*Frees the character.*/
    character_destroy(character);;
}

void test2_character_get_message()
{
    Character *character=NULL;
    character_set_message(character, "SI");
    PRINT_TEST_RESULT(character_get_message(character)==NULL);
}

void test1_character_get_follow()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_get_follow(character, 3) == OK);
    /*Frees the character.*/
    character_destroy(character);
}

void test2_character_get_follow()
{
    /*Initializes the variables.*/
    Character *character = NULL;
    character = character_create(5);
    PRINT_TEST_RESULT(character_get_id(character, ID_ERROR) == ID_ERROR);
    /*Frees the character*/
    character_destroy(character);
}
