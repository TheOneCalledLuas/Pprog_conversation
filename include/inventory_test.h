/**
 * @brief It declares the tests for the inventory module
 *
 * @file inventory_test.h
 * @author Raquel Anguita Martínez de Velasco
 * @version 1
 * @date 20-03-2025
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Test inventory creation.
 * @pre Pointer to NULL.
 * @post Non NULL pointer to inventory.
 */
void test1_inventory_create();

/**
 * @test Test inventory max_obj setter.
 * @pre Pointer to initialized inventory and a valid value.
 * @post Output = OK.
 */
void test1_inventory_set_max_objs();

/**
 * @test Test inventory max_obj setter.
 * @pre Pointer to initialized inventory and a negative value.
 * @post Output = ERROR.
 */
void test2_inventory_set_max_objs();

/**
 * @test Test inventory max_obj setter.
 * @pre Pointer to initialized inventory and a value greater than the overall max.
 * @post Output = ERROR.
 */
void test3_inventory_set_max_objs();

/**
 * @test Test inventory max_obj setter.
 * @pre Pointer to NULL inventory and a valid value.
 * @post Output = ERROR.
 */
void test4_inventory_set_max_objs();

/**
 * @test Test inventory max_obj getter.
 * @pre Pointer to initialized inventory with the set value.
 * @post Output = 1 (correct).
 */
void test1_inventory_get_max_objs();

/**
 * @test Test inventory max_obj getter.
 * @pre Pointer to initialized inventory with base value.
 * @post Output = 0 (correct).
 */
void test2_inventory_get_max_objs();

/**
 * @test Test inventory max_obj getter.
 * @pre Pointer to null inventory.
 * @post Output = -1 (error).
 */
void test3_inventory_get_max_objs();

/**
 * @test Tests the find function.
 * @pre Pointer to initialized inventory with an object.
 * @post Output different to -1 (correct).
 */
void test1_inventory_find();

/**
 * @test Tests the find function.
 * @pre Pointer to initialized inventory with an object different to the one checked.
 * @post Output = -1 (error).
 */
void test2_inventory_find();

/**
 * @test Tests the find function.
 * @pre Pointer to initialized inventory without objects.
 * @post Output = -1 (error).
 */
void test3_inventory_find();

/**
 * @test Tests the find function.
 * @pre Pointer to initialized inventory with many objects (one checked).
 * @post Output = 1 (correct).
 */
void test4_inventory_find();

/**
 * @test Tests the find function.
 * @pre Pointer to null inventory.
 * @post Output = -1 (error).
 */
void test5_inventory_find();

/**
 * @test Test inventory add function.
 * @pre Pointer to initialized inventory with a valid max value and id.
 * @post Output = OK.
 */
void test1_inventory_add();

/**
 * @test Test inventory add function.
 * @pre Pointer to initialized inventory with a valid max value and invalid id.
 * @post Output = ERROR.
 */
void test2_inventory_add();

/**
 * @test Test inventory add function.
 * @pre Pointer to null inventory.
 * @post Output = ERROR.
 */
void test3_inventory_add();

/**
 * @test Test inventory add function.
 * @pre Pointer to initialized inventory with an invalid max value and valid id.
 * @post Output = ERROR.
 */
void test4_inventory_add();

/**
 * @test Test inventory add function.
 * @pre Pointer to initialized inventory with a valid max value and an already added id to check if it works.
 * @post Output = OK.
 */
void test5_inventory_add();

/**
 * @test Test inventory add function.
 * @pre Pointer to initialized inventory with a valid max value and an already added id to check the length.
 * @post Length doesn't change.
 */
void test6_inventory_add();

/**
 * @test Test inventory take function.
 * @pre Pointer to initialized inventory with the id to take already in it.
 * @post Output = 1 (correct).
 */
void test1_inventory_take();

/**
 * @test Test inventory take function.
 * @pre Pointer to initialized inventory with the id to take not in it.
 * @post Output = ID_ERROR (error).
 */
void test2_inventory_take();

/**
 * @test Test inventory take function.
 * @pre Pointer to initialized inventory with the id to take already taken out.
 * @post Output = ID_ERROR (error).
 */
void test3_inventory_take();

/**
 * @test Test inventory take function.
 * @pre Pointer to null inventory.
 * @post Output = ID_ERROR (error).
 */
void test4_inventory_take();

/**
 * @test Test inventory get content function.
 * @pre Pointer to initialized inventory with many ids.
 * @post Output not null (correct).
 */
void test1_inventory_get_content();

/**
 * @test Test inventory get content function.
 * @pre Pointer to initialized inventory with no ids.
 * @post Output = null (error).
 */
void test2_inventory_get_content();

/**
 * @test Test inventory get content function.
 * @pre Pointer to null inventory.
 * @post Output = null (error).
 */
void test3_inventory_get_content();

#endif