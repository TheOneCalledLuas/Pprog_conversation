/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Fernando Mijangos
 * @version 0.0
 * @date 02-04-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test object creation.
 * @pre id_object=5.
 * @post Pointer to object.
 */
void test1_object_create();

/**
 * @test Test object creation.
 * @pre id_object=NO_ID.
 * @post NULL.
 */
void test2_object_create();

/**
 * @test Test object creation.
 * @pre id_object=ID_ERROR.
 * @post NULL.
 */
void test3_object_create();

/**
 * @test Test get gdesc function.
 * @pre Pointer to object=Non NULL | Description="potato".
 * @post "potato".
 */
void test1_object_get_gdesc();

/**
 * @test Test get gdesc function.
 * @pre Pointer to object=Non NULL | Description=NULL.
 * @post NULL.
 */
void test2_object_get_gdesc();

/**
 * @test Test get gdesc function.
 * @pre Pointer to object=NULL | Description="potato".
 * @post NULL.
 */
void test3_object_get_gdesc();

/**
 * @test Test set gdesc function.
 * @pre Pointer to object=Non NULL | New description="potato".
 * @post OK.
 */
void test1_object_set_description();

/**
 * @test Test set gdesc function.
 * @pre Pointer to object=Non NULL | New description=NULL.
 * @post ERROR.
 */
void test2_object_set_description();

/**
 * @test Test set gdesc function.
 * @pre Pointer to object=NULL | New description="potato".
 * @post ERROR.
 */
void test3_object_set_description();

/**
 * @test Test set gdesc function.
 * @pre Pointer to object=Non NULL | New description=+100 character long string.
 * @post ERROR.
 */
void test4_object_set_description();

/**
 * @test Test get name function.
 * @pre Pointer to object=Non NULL | Name="potato".
 * @post "potato".
 */
void test1_object_get_name();

/**
 * @test Test get name function.
 * @pre Pointer to object=Non NULL | Name=NULL.
 * @post NULL.
 */
void test2_object_get_name();

/**
 * @test Test get name function.
 * @pre Pointer to object=NULL | Name="potato".
 * @post NULL.
 */
void test3_object_get_name();

/**
 * @test Test set name function.
 * @pre Pointer to object=Non NULL | New name="potato".
 * @post OK.
 */
void test1_object_set_name();

/**
 * @test Test set name function.
 * @pre Pointer to object=Non NULL | New name=NULL.
 * @post ERROR.
 */
void test2_object_set_name();

/**
 * @test Test set name function.
 * @pre Pointer to object=NULL | New name="potato".
 * @post ERROR.
 */
void test3_object_set_name();

/**
 * @test Test set name function.
 * @pre Pointer to object=Non NULL | New name=+100 character long string.
 * @post ERROR.
 */
void test4_object_set_name();

/**
 * @test Test get id function.
 * @pre Pointer to object=Non NULL | Object id=5
 * @post 5.
 */
void test1_object_get_id();

/**
 * @test Test get id function.
 * @pre Pointer to object=NULL
 * @post ID_ERROR.
 */
void test2_object_get_id();

/**
 * @test Test get id function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test3_object_get_id();

/**
 * @test Test set health function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_set_health();

/**
 * @test Test get health function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_get_health();

/**
 * @test Test set movable function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_set_movable();

/**
 * @test Test set movable function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test2_object_set_movable();

/**
 * @test Test get movable function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_get_movable();

/**
 * @test Test set dependency function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_set_dependency();

/**
 * @test Test set dependency function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test2_object_set_dependency();

/**
 * @test Test get dependency function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_get_dependency();

/**
 * @test Test set open function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_set_open();

/**
 * @test Test set open function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test2_object_set_open();

/**
 * @test Test get open function.
 * @pre Pointer to object=Non NULL | Object id=-6
 * @post 5.
 */
void test1_object_get_open();

#endif
