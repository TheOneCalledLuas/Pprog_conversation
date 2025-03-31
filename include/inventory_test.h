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
 * @test Test Inventory creation.
 * @pre Pointer to Null.
 * @post Non NULL pointer to set.
 */
void test1_inventory_create();

void test1_inventory_set_max_objs();

void test2_inventory_set_max_objs();

void test3_inventory_set_max_objs();

void test4_inventory_set_max_objs();

void test1_inventory_get_max_objs();

void test2_inventory_get_max_objs();

void test3_inventory_get_max_objs();

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