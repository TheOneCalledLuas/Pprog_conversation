/** 
 * @brief It declares the tests for the set module
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
 * @pre Pointer to Null.
 * @post Non NULL pointer to set.
 */
void test1_set_create();

/**
 * @test Test Set creation.
 * @pre Pointer to NULL of Set type.
 * @post the set was initialised empty.
 */
void test2_set_create();

/**
 * @test Test Set lenght.
 * @pre pointer to empty set (initialised).
 * @post set len == 0.
 */
void test1_set_len();

/**
 * @test Test Set lenght.
 * @pre pointer to non empty set.
 * @post set len == 1.
 */
void test2_set_len();

/**
 * @test Test Set lenght.
 * @pre sSet that has been emptied.
 * @post set len == 0.
 */
void test3_set_len();

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
 * @post int returned different from -1.
 */
void test1_set_find();

/**
 * @test Test Set search of an id.
 * @pre Non Existent Id in set.
 * @post -1 returned.
 */
void test2_set_find();

/**
 * @test Test Set search of an id.
 * @pre Empty set.
 * @post -1 returned.
 */
void test3_set_find();

/**
 * @test Test Set search of an id.
 * @pre set with more than one element.
 * @post position of the second id.
 */
void test4_set_find();

/**
 * @test Test Set search of an id.
 * @pre NULL set.
 * @post -1 returned.
 */
void test5_set_find();

/**
 * @test Test Set take an id from the set.
 * @pre Pointer to the set whith an id.
 * @post id taken out.
 */
void test1_set_take();

/**
 * @test Test Set take an id from the set.
 * @pre NULL set.
 * @post ID_ERROR returned.
 */
void test2_set_take();

/**
 * @test Test Set take an id from the set.
 * @pre Pointer to set whithout id 1.
 * @post ID_ERROR returned.
 */
void test3_set_take();

/**
 * @test Test Set take an id from the set.
 * @pre Pointer to set where an id was taken out.
 * @post ID_ERROR returned.
 */
void test4_set_take();

/**
 * @test Test Set take an id from the set.
 * @pre Pointer to set where multiple elements are taken out.
 * @post all ids were taken out correctly.
 */
void test5_set_take();

/**
 * @test Test Set return of the ids it has.
 * @pre Pointer to set where multiple elements are placed.
 * @post Clean exit of the function.
 */
void test1_set_get_content();

/**
 * @test Test Set return of the ids it has.
 * @pre Invalid set.
 * @post NULL response.
 */
void test2_set_get_content();

/**
 * @test Test Set return of the ids it has.
 * @pre Set with 0 elements.
 * @post NULL response.
 */
void test3_set_get_content();



#endif