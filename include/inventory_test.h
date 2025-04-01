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
 * @pre Pointer to initialized inventory and the set value.
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
 */
void test3_inventory_get_max_objs();

/**
 * @test Tests the find function in inventories.
 * @pre Pointer to initialized inventory with an object.
 * @post The find function stumbles upon the object.
 */
void test1_inventory_find();

void test2_inventory_find();

void test3_inventory_find();

void test4_inventory_find();

void test5_inventory_find();

void test1_inventory_add();

void test2_inventory_add();

void test3_inventory_add();

void test4_inventory_add();

void test5_inventory_add();

void test6_inventory_add();

void test1_inventory_take();

void test2_inventory_take();

void test3_inventory_take();

void test4_inventory_take();

void test1_inventory_get_content();

void test2_inventory_get_content();

void test3_inventory_get_content();

#endif