/**
 * @brief It tests player module.
 *
 * @file player_test.c
 * @author Saul Lopez Romero
 * @version 1.0
 * @date 27-03-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player_test.h"
#include "player.h"
#include "test.h"

/**
 * Total test number.
 */
#define MAX_TESTS 50

#define MAX_WORD 30 /*!<Maximun word length.*/

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
        printf("Running all test for the module player.c:\n");
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
        player_test_create_1();
    if (all || test == 2)
        player_test_create_2();
    if (all || test == 3)
        player_test_set_player_name_1();
    if (all || test == 4)
        player_test_set_player_name_2();
    if (all || test == 5)
        player_test_set_player_name_3();
    if (all || test == 6)
        player_test_get_player_name_1();
    if (all || test == 7)
        player_test_get_player_name_2();
    if (all || test == 8)
        player_test_get_player_name_3();
    if (all || test == 9)
        player_test_set_player_location_1();
    if (all || test == 10)
        player_test_set_player_location_2();
    if (all || test == 11)
        player_test_set_player_location_3();
    if (all || test == 12)
        player_test_get_player_location_1();
    if (all || test == 13)
        player_test_get_player_location_2();
    if (all || test == 14)
        player_test_get_player_location_3();
    if (all || test == 15)
        player_test_add_object_1();
    if (all || test == 16)
        player_test_add_object_2();
    if (all || test == 17)
        player_test_add_object_3();
    if (all || test == 18)
        player_test_add_object_4();
    if (all || test == 19)
        player_test_add_object_5();
    if (all || test == 20)
        player_test_get_n_object_1();
    if (all || test == 21)
        player_test_get_n_object_2();
    if (all || test == 22)
        player_test_get_n_object_3();
    if (all || test == 23)
        player_test_get_n_object_4();
    if (all || test == 24)
        player_test_del_object_1();
    if (all || test == 25)
        player_test_del_object_2();
    if (all || test == 26)
        player_test_del_object_3();
    if (all || test == 27)
        player_test_del_object_4();
    if (all || test == 28)
        player_test_del_object_5();
    if (all || test == 29)
        player_test_set_player_gdesc_1();
    if (all || test == 30)
        player_test_set_player_gdesc_3();
    if (all || test == 31)
        player_test_get_player_gdesc_1();
    if (all || test == 32)
        player_test_set_player_gdesc_2();
    if (all || test == 33)
        player_test_get_player_gdesc_2();
    if (all || test == 34)
        player_test_get_player_gdesc_3();
    if (all || test == 35)
        player_test_get_id_1();
    if (all || test == 36)
        player_test_get_id_2();
    if (all || test == 37)
        player_test_get_id_3();
    if (all || test == 38)
        player_test_get_inventory_1();
    if (all || test == 39)
        player_test_get_inventory_2();
    if (all || test == 40)
        player_test_get_inventory_3();
    if (all || test == 41)
        player_test_player_has_object_1();
    if (all || test == 42)
        player_test_player_has_object_2();
    if (all || test == 43)
        player_test_player_has_object_3();
    if (all || test == 44)
        player_test_player_has_object_4();
    if (all || test == 45)
        player_test_player_has_object_5();
    if (all || test == 46)
        player_test_set_health_1();
    if (all || test == 47)
        player_test_set_health_2();
    if (all || test == 48)
        player_test_get_health_1();
    if (all || test == 49)
        player_test_get_health_2();
    if (all || test == 50)
        player_test_set_inventory_capacity_1();
    if (all || test == 47)
        player_test_set_inventory_capacity_2();
    if (all || test == 48)
        player_test_set_inventory_capacity_3();
    if (all || test == 49)
        player_test_get_inventory_capacity_1();
    if (all || test == 50)
        player_test_get_inventory_capacity_2();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void player_test_create_1()
{
    Player *player = NULL;
    Id id = 1;
    /*Creates the player.*/
    player = player_create(id);

    /*Checks the result.*/
    PRINT_TEST_RESULT(player != NULL);

    /*Frees the memory.*/
    player_destroy(player);
}

void player_test_create_2()
{
    Player *player = NULL;
    Id id = -1;
    /*Creates the player.*/
    player = player_create(id);

    /*Checks the result.*/
    PRINT_TEST_RESULT(player == NULL);
}

void player_test_set_player_name_1()
{
    Player *player = NULL;
    Id id = 1;
    Status res = 0;
    char name[MAX_WORD] = "MerchAnt";
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_player_name(player, name);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == OK);

    player_destroy(player);
}

void player_test_set_player_name_2()
{
    Player *player = NULL;
    Id id = 1;
    Status res = 0;
    char *name = NULL;
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_player_name(player, name);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == ERROR);
    player_destroy(player);
}

void player_test_set_player_name_3()
{
    Player *player = NULL;
    Status res = 0;
    char name[MAX_WORD] = "MerchAnt";

    /*Sets the test up.*/
    res = player_set_player_name(player, name);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == ERROR);
}

void player_test_get_player_name_1()
{
    Player *player = NULL;
    Id id = 1;
    char name[MAX_WORD] = "MerchAnt";
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_set_player_name(player, name);

    /*Test outcome.*/
    PRINT_TEST_RESULT(strcmp(name, player_get_player_name(player)) == 0);

    player_destroy(player);
}

void player_test_get_player_name_2()
{
    Player *player = NULL;
    char name[MAX_WORD] = "MerchAnt";

    /*Sets the test up.*/
    player_set_player_name(player, name);

    /*Test outcome.*/
    PRINT_TEST_RESULT(player_get_player_name(player) == NULL);
}

void player_test_get_player_name_3()
{
    Player *player = NULL;
    Id id = 1;
    char *name = NULL;
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_set_player_name(player, name);

    /*Test outcome.*/
    PRINT_TEST_RESULT(strcmp("\0", player_get_player_name(player)) == 0);

    player_destroy(player);
}

void player_test_set_player_location_1()
{
    Player *player = NULL;
    Id id = 1, place = 2;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_player_location(player, place);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == OK);

    player_destroy(player);
}

void player_test_set_player_location_2()
{
    Player *player = NULL;
    Id place = 2;
    Status res = 0;

    /*Sets the test up.*/
    res = player_set_player_location(player, place);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == ERROR);
}

void player_test_set_player_location_3()
{
    Player *player = NULL;
    Id id = 1, place = ID_ERROR;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_player_location(player, place);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == ERROR);

    player_destroy(player);
}

void player_test_get_player_location_1()
{
    Player *player = NULL;
    Id id = 1, place = 2;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_set_player_location(player, place);

    /*Test outcome.*/
    PRINT_TEST_RESULT(player_get_player_location(player) == place);

    player_destroy(player);
}

void player_test_get_player_location_2()
{
    Player *player = NULL;
    Id place = 2;

    /*Sets the test up.*/
    player_set_player_location(player, place);

    /*Test outcome.*/
    PRINT_TEST_RESULT(player_get_player_location(player) == ID_ERROR);

    player_destroy(player);
}

void player_test_get_player_location_3()
{
    Player *player = NULL;
    Id id = 1, place = ID_ERROR;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_set_player_location(player, place);

    /*Test outcome.*/
    PRINT_TEST_RESULT(player_get_player_location(player) == NO_ID);

    player_destroy(player);
}

void player_test_add_object_1()
{
    Player *player = NULL;
    Id id = 1, object = 2;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_add_object(player, object);

    PRINT_TEST_RESULT(res == OK);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_add_object_2()
{
    Player *player = NULL;
    Id object = 2;
    Status res = 0;

    /*Sets the test up.*/
    res = player_add_object(player, object);

    PRINT_TEST_RESULT(res == ERROR);
}

void player_test_add_object_3()
{
    Player *player = NULL;
    Id id = 1, object = ID_ERROR;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_add_object(player, object);

    PRINT_TEST_RESULT(res == ERROR);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_add_object_4()
{
    Player *player = NULL;
    Id id = 1, object = 2;
    Status res = 0, res2 = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_add_object(player, object);
    res2 = player_add_object(player, object);

    PRINT_TEST_RESULT(res == OK && res2 == OK);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_add_object_5()
{
    Player *player = NULL;
    Id id = 1, object = 2, object2 = 3;
    Status res = 0, res2 = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_set_inventory_capacity(player, 1);
    res = player_add_object(player, object);
    res2 = player_add_object(player, object2);

    PRINT_TEST_RESULT(res == OK && res2 == ERROR);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_n_object_1()
{
    Player *player = NULL;
    Id id = 1, object = 2;
    int obj = 0, obj1 = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    obj1 = player_get_n_objects(player);
    player_add_object(player, object);
    obj = player_get_n_objects(player);

    PRINT_TEST_RESULT(obj == 1 && obj1 == 0);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_n_object_2()
{
    Player *player = NULL;
    Id object = 2;

    /*Sets the test up.*/
    player_add_object(player, object);

    PRINT_TEST_RESULT(player_get_n_objects(player) == -1);
}

void player_test_get_n_object_3()
{
    Player *player = NULL;
    Id id = 1, object = 2;
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_add_object(player, object);
    player_del_object(player, object);

    PRINT_TEST_RESULT(player_get_n_objects(player) == 0);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_n_object_4()
{
    Player *player = NULL;
    Id id = 1, object = 2, object2 = 3;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_add_object(player, object);
    player_add_object(player, object2);

    PRINT_TEST_RESULT(player_get_n_objects(player) == 2);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_del_object_1()
{
    Player *player = NULL;
    Id id = 1, object = 2;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_add_object(player, object);
    res = player_del_object(player, object);

    PRINT_TEST_RESULT(res == OK && player_get_n_objects(player) == 0);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_del_object_2()
{
    Player *player = NULL;
    Id object = 2;
    Status res = 0;

    /*Sets the test up.*/
    res = player_add_object(player, object);
    res = player_del_object(player, object);

    PRINT_TEST_RESULT(res == ERROR);
}

void player_test_del_object_3()
{
    Player *player = NULL;
    Id id = 1, object = ID_ERROR;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_add_object(player, object);
    res = player_del_object(player, object);

    PRINT_TEST_RESULT(res == ERROR);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_del_object_4()
{
    Player *player = NULL;
    Id id = 1, object = 2, object2 = 3;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_add_object(player, object);
    player_add_object(player, object2);
    res = player_del_object(player, object);

    PRINT_TEST_RESULT(res == OK && player_get_n_objects(player) == 1);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_del_object_5()
{
    Player *player = NULL;
    Id id = 1, object = 2, no_object = 3;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_add_object(player, object);
    res = player_del_object(player, no_object);

    PRINT_TEST_RESULT(res == ERROR && player_get_n_objects(player) == 1);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_set_player_gdesc_1()
{
    Player *player = NULL;
    Id id = 1;
    Status res = 0;
    char desc[MAX_WORD] = "mo'";
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_gdesc(player, desc);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == OK);

    player_destroy(player);
}

void player_test_set_player_gdesc_2()
{
    Player *player = NULL;
    Id id = 1;
    Status res = 0;
    char *desc = NULL;
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_gdesc(player, desc);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == ERROR);
    player_destroy(player);
}

void player_test_set_player_gdesc_3()
{
    Player *player = NULL;
    Status res = 0;
    char name[MAX_WORD] = "mo'";

    /*Sets the test up.*/
    res = player_set_gdesc(player, name);

    /*Test outcome.*/
    PRINT_TEST_RESULT(res == ERROR);
}

void player_test_get_player_gdesc_1()
{
    Player *player = NULL;
    Id id = 1;
    char desc[MAX_WORD] = "mo'";
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_set_gdesc(player, desc);

    /*Test outcome.*/
    PRINT_TEST_RESULT(strcmp(desc, player_get_gdesc(player)) == 0);

    player_destroy(player);
}

void player_test_get_player_gdesc_2()
{
    Player *player = NULL;
    char desc[MAX_WORD] = "mo'";

    /*Sets the test up.*/
    player_set_gdesc(player, desc);

    /*Test outcome.*/
    PRINT_TEST_RESULT(player_get_gdesc(player) == NULL);
}

void player_test_get_player_gdesc_3()
{
    Player *player = NULL;
    Id id = 1;
    char *desc = NULL;
    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_set_gdesc(player, desc);

    /*Test outcome.*/
    PRINT_TEST_RESULT(strcmp("\0", player_get_gdesc(player)) == 0);

    player_destroy(player);
}

void player_test_get_id_1()
{
    Player *player = NULL;
    Id id = 2;

    /*Creates the player.*/
    player = player_create(id);

    /*Checks the outcome.*/
    PRINT_TEST_RESULT(player_get_player_id(player) != ID_ERROR);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_id_2()
{
    Player *player = NULL;
    Id id = 2;

    /*Creates the player.*/
    player = player_create(id);

    /*Checks the outcome.*/
    PRINT_TEST_RESULT(player_get_player_id(player) == id);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_id_3()
{
    Player *player = NULL;

    /*Checks the outcome.*/
    PRINT_TEST_RESULT(player_get_player_id(player) == ID_ERROR);
}

void player_test_get_inventory_1()
{
    Player *player = NULL;
    Id id = 2, obj1 = 3, obj2 = 4, *arr = NULL;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_add_object(player, obj1);
    player_add_object(player, obj2);

    arr = player_get_inventory(player);

    /*Checks the outcome.*/
    PRINT_TEST_RESULT(arr[0] == obj1 && arr[1] == obj2);

    /*Cleanup.*/
    free(arr);
    player_destroy(player);
}

void player_test_get_inventory_2()
{
    Player *player = NULL;
    Id obj1 = 3, obj2 = 4, *arr = NULL;

    /*Sets the test up.*/
    player_add_object(player, obj1);
    player_add_object(player, obj2);

    arr = player_get_inventory(player);

    /*Checks the outcome.*/
    PRINT_TEST_RESULT(arr == NULL);
}

void player_test_get_inventory_3()
{
    Player *player = NULL;
    Id id = 2, *arr = NULL;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    arr = player_get_inventory(player);

    /*Checks the outcome.*/
    PRINT_TEST_RESULT(arr == NULL);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_player_has_object_1()
{
    Player *player = NULL;
    Id id = 1, object = 2;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_add_object(player, object);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(player_has_object(player, object));

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_player_has_object_2()
{
    Player *player = NULL;
    Id id = 1, object = 2, no_object = 3;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_add_object(player, object);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(player_has_object(player, no_object) == FALSE);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_player_has_object_3()
{
    Player *player = NULL;
    Id id = 1, object = 2;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_add_object(player, object);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(player_has_object(player, ID_ERROR) == FALSE);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_player_has_object_4()
{
    Player *player = NULL;
    Id id = 1, object = 2, grain = 4, no_object = 3;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    player_add_object(player, object);
    player_add_object(player, grain);
    player_add_object(player, no_object);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(player_has_object(player, grain) == TRUE);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_player_has_object_5()
{
    Player *player = NULL;
    Id object = 2;

    /*Sets the test up.*/
    player_add_object(player, object);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(player_has_object(player, object) == FALSE);
}

void player_test_set_health_1()
{
    Player *player = NULL;
    Id id = 1;
    int health = 12;
    int res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_health(player, health);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == OK);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_set_health_2()
{
    Player *player = NULL;
    int health = 12;
    int res = 0;

    /*Sets the test up.*/
    res = player_set_health(player, health);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == ERROR);
}

void player_test_get_health_1()
{
    Player *player = NULL;
    Id id = 1;
    int health = 12;
    int res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_health(player, health);
    res = player_get_health(player);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == health);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_health_2()
{
    Player *player = NULL;
    int health = 12;
    int res = 0;

    /*Sets the test up.*/
    res = player_set_health(player, health);
    res = player_get_health(player);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == -1);
}

void player_test_set_inventory_capacity_1()
{
    Player *player = NULL;
    Id id = 1;
    int capacity = 12;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_inventory_capacity(player, capacity);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == OK);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_set_inventory_capacity_2()
{
    Player *player = NULL;
    int cap = 12;
    Status res = 0;

    /*Sets the test up.*/
    res = player_set_inventory_capacity(player, cap);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == ERROR);
}

void player_test_set_inventory_capacity_3()
{
    Player *player = NULL;
    Id id = 1;
    int capacity = -3;
    Status res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_inventory_capacity(player, capacity);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == ERROR);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_inventory_capacity_1()
{
    Player *player = NULL;
    int id = 0;
    int cap = 12;
    int res = 0;

    /*Creates the player.*/
    player = player_create(id);

    /*Sets the test up.*/
    res = player_set_inventory_capacity(player, cap);
    res = player_get_inventory_capacity(player);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == cap);

    /*Cleanup.*/
    player_destroy(player);
}

void player_test_get_inventory_capacity_2()
{
    Player *player = NULL;
    int health = 12;
    int res = 0;

    /*Sets the test up.*/
    res = player_set_inventory_capacity(player, health);
    res = player_get_inventory_capacity(player);

    /*Checks the test out.*/
    PRINT_TEST_RESULT(res == -1);
}