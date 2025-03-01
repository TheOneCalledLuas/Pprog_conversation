/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Fernando Mijangos
 * @version 1
 * @date 23-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for north_id setting
 * @pre North Space id = 4
 * @post Output = OK
 */
void test1_space_set_north();

/**
 * @test Test function for north_id setting
 * @pre Pointer to space = NULL
 * @post Output = ERROR
 */
void test2_space_set_north();

/**
 * @test Test function for north_id setting
 * @pre North Space id = NO_ID
 * @post Output = OK
 */
void test3_space_set_north();

/**
 * @test Test function for north_id setting
 * @pre North Space id = ID_ERROR
 * @post Output = ERROR
 */
void test4_space_set_north();

/**
 * @test Test function for south_id setting
 * @pre South Space id = 4
 * @post Output = OK
 */
void test1_space_set_south();

/**
 * @test Test function for south_id setting
 * @pre Pointer to space = NULL
 * @post Output = ERROR
 */
void test2_space_set_south();

/**
 * @test Test function for south_id setting
 * @pre South Space id = NO_ID
 * @post Output = OK
 */
void test3_space_set_south();

/**
 * @test Test function for south_id setting
 * @pre South Space id = ID_ERROR
 * @post Output = ERROR
 */
void test4_space_set_south();

/**
 * @test Test function for east_id setting
 * @pre East Space id = 4
 * @post Output = OK
 */
void test1_space_set_east();

/**
 * @test Test function for east_id setting
 * @pre Pointer to space = NULL
 * @post Output = ERROR
 */
void test2_space_set_east();

/**
 * @test Test function for east_id setting
 * @pre East Space id = NO_ID
 * @post Output = OK
 */
void test3_space_set_east();

/**
 * @test Test function for east_id setting
 * @pre East Space id = ID_ERROR
 * @post Output = ERROR
 */
void test4_space_set_east();

/**
 * @test Test function for west_id setting
 * @pre West Space id = 4
 * @post Output = OK
 */
void test1_space_set_west();

/**
 * @test Test function for west_id setting
 * @pre Pointer to space = NULL
 * @post Output = ERROR
 */
void test2_space_set_west();

/**
 * @test Test function for west_id setting
 * @pre West Space id = NO_ID
 * @post Output = OK
 */
void test3_space_set_west();

/**
 * @test Test function for west_id setting
 * @pre West Space id = ID_ERROR
 * @post Output = ERROR
 */
void test4_space_set_west();

/**
 * @test Test function for id setting
 * @pre Pointer to the space = NON NULL; Space id = 25
 * @post Output = 25
 */
void test1_space_get_id();

/**
 * @test Test function for id setting
 * @pre Ponter to the space = NULL
 * @post Output = ID_ERROR
 */
void test2_space_get_id();

/**
 * @test Test function for the name setting
 * @pre Space_name = "adios" ; Pointer to the space = NON NULL
 * @post Output = 0 (its using a stcmp)
 */
void test1_space_get_name();

/**
 * @test Test function for the name setting
 * @pre Pointer to the space = NULL
 * @post Output = NULL
 */
void test2_space_get_name();

/**
 * @test Test function for the north_id setting
 * @pre North_id=4 ; Pointer to space = NON NULL
 * @post Ooutput = 4
 */
void test1_space_get_north();

/**
 * @test Test function for the north_id setting
 * @pre Pointer to space = NULL
 * @post Output = ID_ERROR
 */
void test2_space_get_north();

/**
 * @test Test function for the south_id setting
 * @pre South_id=2 ; Pointer to space = NON NULL
 * @post Ooutput = 2
 */
void test1_space_get_south();

/**
 * @test Test function for the south_id setting
 * @pre Pointer to space = NULL
 * @post Output = ID_ERROR
 */
void test2_space_get_south();

/**
 * @test Test function for the east_id setting
 * @pre East_id=1 ; Pointer to space = NON NULL
 * @post Output = 1
 */
void test1_space_get_east();

/**
 * @test Test function for the east_id setting
 * @pre Pointer to space = NULL
 * @post Output = ID_ERROR
 */
void test2_space_get_east();

/**
 * @test Test function for the west_id setting
 * @pre West_id=6 ; Pointer to space = NON NULL
 * @post Output = 6
 */
void test1_space_get_west();

/**
 * @test Test function for the west_id setting
 * @pre Pointer to space = NULL
 * @post Output = ID_ERROR
 */
void test2_space_get_west();

/**
 * @test Test function for the gdesc setting
 * @pre Pointer to the space = NON NULL; line = 0; str ="123456789"
 * @pre Output = OK
 */
void test1_space_set_gdesc();

/**
 * @test Test function for the gdesc setting
 * @pre Pointer to the space = NULL
 * @post Output = ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test function for the gdesc setting
 * @pre Pointer to the space = NON NULL; line = -1; str="123456789"
 * @post Output = ERROR
 */
void test3_space_set_gdesc();

/**
 * @test Test function for the gdesc setting
 * @pre Pointer to the space = NON NULL; line = 0; str=NULL
 * @post Output = ERROR
 */
void test4_space_set_gdesc();

/**
 * @test Test function for the gdesc setting
 * @pre Pointer to the space = NON NULL; line =0; str ="123456789+" (to long)
 * @post Output =ERROR
 */
void test5_space_set_gdesc();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL;
 * @post Output = NON NULL
 */
void test1_space_get_objects();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NULL;
 * @post Output = NON NULL
 */
void test2_space_get_objects();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; id = NO_ID
 * @post Output = ERROR
 */
void test1_space_add_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; id=5
 * @post Output = OK
 */
void test2_space_add_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NULL
 * @post Output = ERROR
 */
void test3_space_add_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL ; id= Id_ERROR
 * @post Output = ERROR
 */
void test4_space_add_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; object_id=1; searching for 1
 * @post Output = 0 (position of that object in the set)
 */
void test1_space_find_object();

/**
 * @test Test funtion for the object_set setting
 * @pre Pointer to the space = NON NULL; object_id=2; searching for 1
 * @post Output = -1 
 */
void test2_space_find_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NULL
 * @post Output = -1
 */
void test3_space_find_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; no objects; searching for 1
 * @post Output = -1
 */
void test4_space_find_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; no object ;searching for NO_ID
 * @post Output = -1
 */
void test5_space_find_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; no object ; taking object with id 1
 * @post Output = ID_ERROR
 */
void test1_space_take_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; object_id=1; taking object with id 1
 * @post Output = 1 (Id of the object that has been taken out)
 */
void test2_space_take_object();

/**
 * @test Test function for the object_Set setting
 * @pre Pointer to the space = NULL
 * @post Output = ID_ERROR
 */
void test3_space_take_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; object_id=1; taking object with id 'NO_ID'
 * @post Output = ID_ERROR
 */
void test4_space_take_object();

/**
 * @test Test function for the object_set setting
 * @pre Pointer to the space = NON NULL; object_id=1; taking object with id 'ID_ERROR'
 * @post Output = ID_ERROR
 */
void test5_space_take_object();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NON NULL; character_id=NO_ID
 * @post Output = NO_ID
 */
void test1_space_get_character();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NON NULL; character_id=5
 * @post Output = 5
 */
void test2_space_get_character();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NULL;
 * @post Output = ID_ERROR
 */
void test3_space_get_character();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NON NULL; character_id=3
 * @post Output = 3
 */
void test4_space_get_character();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NON NULL; new_character_id = NO_ID
 * @post Output = OK
 */
void test1_space_set_character();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NULL; new_character_id = 5
 * @post Output = ERROR
 */
void test2_space_set_character();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NON NULL; new_character_id = 5
 * @post Output = OK
 */
void test3_space_set_character();

/**
 * @test Test function for the character setting
 * @pre Pointer to the space = NON NULL; new_character_id = ID_ERROR
 * @post Output = ERROR
 */
void test4_space_set_character();
#endif
