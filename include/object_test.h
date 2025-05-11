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
 * @pre Pointer to object=Non NULL | Object_new_health=7
 * @post OK.
 */
void test1_object_set_health();

/**
 * @test Test get health function.
 * @pre Pointer to object=Non NULL | Object_health=7
 * @post 7.
 */
void test1_object_get_health();

/**
 * @test Test set movable function.
 * @pre Pointer to object=Non NULL | New_movable_cond=FALSE
 * @post OK.
 */
void test1_object_set_movable();

/**
 * @test Test set movable function.
 * @pre Pointer to object=Non NULL | Movable_cond=TRUE
 * @post TRUE.
 */
void test1_object_get_movable();

/**
 * @test Test get movable function.
 * @pre Pointer to object=NULL | Movable_cond=FALSE
 * @post FALSE.
 */
void test2_object_get_movable();

/**
 * @test Test set dependency function.
 * @pre Pointer to object=Non NULL | New_dependency=1
 * @post OK.
 */
void test1_object_set_dependency();

/**
 * @test Test set dependency function.
 * @pre Pointer to object=Non NULL | New_dependency=ID_ERROR
 * @post ERROR.
 */
void test2_object_set_dependency();

/**
 * @test Test get dependency function.
 * @pre Pointer to object=Non NULL | Dependency=1
 * @post 1.
 */
void test1_object_get_dependency();

/**
 * @test Test set open function.
 * @pre Pointer to object=Non NULL | Link_that_opens=1
 * @post OK.
 */
void test1_object_set_open();

/**
 * @test Test set open function.
 * @pre Pointer to object=Non NULL | Link_that_opens=ID_ERROR
 * @post ERROR.
 */
void test2_object_set_open();

/**
 * @test Test get open function.
 * @pre Pointer to object=Non NULL | Link_that_opens=1
 * @post 1.
 */
void test1_object_get_open();

/**
 * @test Test set texture line function.
 * @pre Pointer to object=Non NULL | Line=1 | Texture="potato"
 * @post ERROR.
 */
void test1_object_set_texture_line();

/**
 * @test Test set texture line function.
 * @pre Pointer to object=Non NULL | Line=1 | Texture=NULL
 * @post ERROR.
 */
void test2_object_set_texture_line();

/**
 * @test Test set texture line function.
 * @pre Pointer to object=NULL | Line=70 | Texture="potato"
 * @post ERROR.
 */
void test3_object_set_texture_line();

/**
 * @test Test set texture line function.
 * @pre Pointer to object=Non NULL | Line=72 (not a valid line) | Texture="potato"
 * @post ERROR.
 */
void test4_object_set_texture_line();

/**
 * @test Test get texture line function.
 * @pre Pointer to object=Non NULL | Line=1 | Texture="potato"
 * @post "potato".
 */
void test1_object_get_texture_line();

/**
 * @test Test get texture line function.
 * @pre Pointer to object=NULL | Line=10
 * @post NULL.
 */
void test2_object_get_texture_line();

/**
 * @test Test get texture line function.
 * @pre Pointer to object=Non NULL | Line=10
 * @post NULL.
 */
void test3_object_get_texture_line();

/**
 * @test Test get texture line function.
 * @pre Pointer to object=Non NULL | used_new_value=TRUE
 * @post OK.
 */
void test1_object_set_is_used();

/**
 * @test Test set is_used function.
 * @pre Pointer to object=NULL | used_new_value=TRUE
 * @post ERROR.
 */
void test2_object_set_is_used();

/**
 * @test Test get is_used function.
 * @pre Pointer to object=Non NULL | used_value=TRUE
 * @post TRUE.
 */
void test1_object_get_is_used();

/**
 * @test Test get is_used function.
 * @pre Pointer to object=NULL | used_value=TRUE
 * @post FALSE.
 */
void test2_object_get_is_used();

/**
 * @test Test set special_use function.
 * @pre Pointer to object=Non NULL | special_use_new_value=TRUE
 * @post OK.
 */
void test1_object_set_special_use();

/**
 * @test Test set special_use function.
 * @pre Pointer to object=NULL | special_use_new_value=TRUE
 * @post ERROR.
 */
void test2_object_set_special_use();

/**
 * @test Test get special_use function.
 * @pre Pointer to object=Non NULL | special_use_value=TRUE
 * @post TRUE.
 */
void test1_object_get_special_use();

/**
 * @test Test get special_use function.
 * @pre Pointer to object=NULL | special_use_value=TRUE
 * @post FALSE.
 */
void test2_object_get_special_use();

#endif
