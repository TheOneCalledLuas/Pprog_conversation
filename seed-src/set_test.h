/** 
 * @brief It declares the tests for the space module
 * 
 * @file set_test.h
 * @author Saul Lopez Romero
 * @version 0.0 
 * @date 19-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test Set creation.
 * @post Non NULL pointer to set.
 */
void test1_set_create();

/**
 * @test Test Set count number of elements.
 * @pre Full 
 * @post Error when adding.
 */
void test1_set_increment();

/**
 * @test Test Set add element.
 * @pre Id to add.
 * @post Clean exit when adding.
 */
void test1_set_add();

/**
 * @test Test Set add element.
 * @pre Null set pointer.
 * @post Error when adding.
 */
void test2_set_add();

/**
 * @test Test Set add element.
 * @pre Full set.
 * @post Error when adding.
 */
void test3_set_add();

/**
 * @test Test Set add element.
 * @pre Element already in set.
 * @post Clean exit.
 */
void test4_set_add();

/**
 * @test Test Set add element.
 * @pre Invalid Id.
 * @post Error when adding.
 */
void test5_set_add();

/**
 * @test Test Set search of an id.
 * @pre Existent Id in set.
 * @post Id wanted.
 */
void test1_set_find();


#endif