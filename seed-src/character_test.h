/**
 * @brief It tests space character
 *
 * @file character_test.h
 * @author Fernando Mijangos Varas
 * @version 1
 * @date 23-02-2025
 * @copyright GNU Public License
 */

#include "character.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @test Test Character creation
 * @pre id==5
 * @post character = non null
 */
void test1_character_create();

/**
 * @test Test Character creation
 * @pre id==-1
 * @post character = null
 */
void test2_character_create();

/**
 * @test Test Character_get_id
 * @pre Pointer to character = NON NULL 
 * @post Returns correctly the id
 */
void test1_character_get_id();

/**
 * @test Test Character_get_id
 * @pre Pointer to character = NULL
 * @post Returns ID_ERROR
 */
void test2_character_get_id();

/**
 * @test Test Character_set_name
 * @pre Pointer to the character = Non NULL ; pointer to new character = Non NULL
 * @post Returns OK
 */
void test1_character_set_name();

/**
 * @test Test Character_set_name
 * @pre Pointer to the character = NULL ; pointer to new character = Non NULL
 * @post Returns ERROR
 */
void test2_character_set_name();

/**
 * @test Test Character_set_name
 * @pre Pointer to the character = Non NULL ; pointer to new character = NULL
 * @post Returns ERROR
 */
void test3_character_set_name();

/**
 * @test Test Character_set_name
 * @pre Pointer to the character = NULL ; pointer to new character = NULL
 * @post Returns OK
 */
void test4_character_set_name();

/**
 * @test Test Character_get_name
 * @post Pointer to the character = Non NULL; 
 * @post Returns the name
 */
void test1_character_get_name();

/**
 * @test Test Character_get_name
 * @post Pointer to the character = NULL; 
 * @post Returns NULL
 */
void test2_character_get_name();

/**
 * @test Test character_set_description
 * @pre Pointer to the character = non NULL ; pointer to the new description = non NULL
 * @post Returns OK
 */
void test1_character_set_description();

/**
 * @test Test character_set_description
 * @pre Pointer to the character = NULL ; pointer to the new description = non NULL
 * @post Returns ERROR
 */
void test2_character_set_description();

/**
 * @test Test character_set_description
 * @pre Pointer to the character = non NULL ; pointer to the new description = NULL
 * @post Returns ERROR
 */
void test3_character_set_description();

/**
 * @test Test character_set_description
 * @pre Pointer to the character = NULL ; pointer to the new description = NULL
 * @post Returns ERROR
 */
void test4_character_set_description();

/**
 * @test Test character_get_description
 * @pre Pointer to the character = Non NULL;
 * @post Returns the description
 */
void test1_character_get_description();

/**
 * @test Test character_get_description
 * @pre Pointer to the character = NULL;
 * @post Returns NULL
 */
void test2_character_get_description();

/**
 * @test Test character_set_friendly
 * @pre Pointer to the character = Non NULL; New value= TRUE
 * @post Returns OK
 */
void test1_character_set_friendly();

/**
 * @test Test character_set_friendly
 * @pre Pointer to the character = NULL; New value= TRUE
 * @post Returns OK
 */
void test2_character_set_friendly();

/**
 * @test Test character_set_friendly
 * @pre Pointer to the character = Non NULL; New value= FALSE
 * @post Returns OK
 */
void test3_character_set_friendly();

/**
 * @test Test character_set_friendly
 * @pre Pointer to the character = Non NULL; New value= FALSE
 * @post Returns OK
 */
void test4_character_set_friendly();

/**
 * @test Test character_get_friendly
 * @pre Pointer to the new character= Non NULL
 * @post Returns the correct Bool value
 */
void test1_character_get_friendly();

/**
 * @test Test character_get_friendly
 * @pre Pointer to the new character= NULL
 * @post Returns FALSE
 */
void test2_character_get_friendly();

/**
 * @test Test character_set_message
 * @pre Pointer to the new character = NON NULL ; pointer to new message = NON NULL
 * @post Returns OK
 */
void test1_character_set_message();

/**
 * @test Test character_set_message
 * @pre Pointer to the new character = NON NULL ; pointer to new message = NULL
 * @post Returns ERROR
 */
void test2_character_set_message();

/**
 * @test Test character_set_message
 * @pre Pointer to the new character =NULL ; pointer to new message = NON NULL
 * @post Returns ERROR
 */
void test3_character_set_message();

/**
 * @test Test character_set_message
 * @pre Pointer to the new character = NULL ; pointer to new message =  NULL
 * @post Returns NULL
 */
void test4_character_set_message();

/**
 * @test Test character_get_message
 * @pre Pointer to the new character = Non NULL;
 * @post Returns the correct message
 */
void test1_character_get_message();

/**
 * @test Test character_get_mesage
 * @pre Pointer to the new chearacter = NULL;
 * @post Returns NULL
 */
void test2_character_get_message();
