/**
 * @brief Link test function module.
 *
 * @file link_test.h
 * @author Irene García 
 * @version 1
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

#include "link.h"

/**
 * @test Test for the create link function.
 * @pre Input-> id=4.
 * @post Output-> Pointer to the link.
 */
void test1_link_create();

/**
 * @test Test for the create link function.
 * @pre Input-> id=4.
 * @post Checks that the arguments were set to default values.
 */
void test2_link_create();

/**
 * @test Test for the create link function.
 * @pre Input-> id=NO_ID.
 * @post Output-> NULL.
 */
void test3_link_create();

/**
 * @test Test for the get id function.
 * @pre Input-> Link= NON NULL | id = 4.
 * @post Output-> id = 4.
 */
void test1_link_get_id();

/**
 * @test Test for the get id function.
 * @pre Input-> Link=NULL .
 * @post Output-> id = ID_ERROR.
 */
void test2_link_get_id();

/**
 * @test Test for the get name function.
 * @pre Input-> Link= NON NULL | name = "merchant".
 * @post Output-> name= "merchant".
 */
void test1_link_get_name();

/**
 * @test Test for the get name function.
 * @pre Input-> Link= NULL .
 * @post Output-> name = NULL.
 */
void test2_link_get_name();

/**
 * @test Test for the get origin function.
 * @pre Input-> Link= NON NULL | origin_id= 13.
 * @post Output-> origin_id = 13.
 */
void test1_link_get_origin();

/**
 * @test Test for the get origin.
 * @pre Input->Link= NULL.
 * @post Output-> origin_id = ID_ERROR.
 */
void test2_link_get_origin();

/**
 * @test Test for the get destination function.
 * @pre Input-> Link= NON NULL | destination_id= 13.
 * @post Output-> destination_id = 13.
 */
void test1_link_get_destination();

/**
 * @test Test for the get destination function.
 * @pre Input-> Link= NULL.
 * @post Output-> destination_id = ID_ERROR.
 */
void test2_link_get_destination();

/**
 * @test Test for the get direction function.
 * @pre Input-> Link= NON NULL | direction_id= 13.
 * @post Output-> direction_id = 13.
 */
void test1_link_get_direction();

/**
 * @test Test for the get direction function.
 * @pre Input-> Link= NULL .
 * @post Output-> destination_id = UNK_DIRECTION.
 */
void test2_link_get_direction();

/**
 * @test Test for the get state function.
 * @pre Input-> Link= NON NULL | state = TRUE.
 * @post Output-> destination_id = TRUE.
 */
void test1_link_get_state();

/**
 * @test Test for the get state function.
 * @pre Input-> Link= NULL.
 * @post Output-> state = FALSE.
 */
void test2_link_get_state();

/**
 * @test Test for the set origin function.
 * @pre Input-> Link= NON NULL | new_origin= NO_ID.
 * @post Output-> Status=OK.
 */
void test1_link_set_origin();

/**
 * @test Test for the set origin function.
 * @pre Input-> Link= NULL 
 * @post Output-> Status=ERROR.
 */
void test2_link_set_origin();

/**
 * @test Test for the set origin function.
 * @pre Input-> Link= NON NULL | new_origin= 5.
 * @post Output-> Status=OK.
 */
void test3_link_set_origin();

/**
 * @test Test for the set origin function.
 * @pre Input-> Link= NON NULL | new_origin= ID_ERROR.
 * @post Output-> Status=ERROR.
 */
void test4_link_set_origin();

/**
 * @test Test for the set name function.
 * @pre Input-> Link= NON NULL | new_name= merchant.
 * @post Output-> Status=OK.
 */
void test1_link_set_name();

/**
 * @test Test for the set name function.
 * @pre Input-> Link= NULL | new_name= merchant.
 * @post Output-> Status=ERROR.
 */
void test2_link_set_name();

/**
 * @test Test for the set name function.
 * @pre Input-> Link= NON NULL | new_name= owo | previous_name =merchant.
 * @post Output-> Status=ERROR.
 */
void test3_link_set_name();

/**
 * @test Test for the set name function.
 * @pre Input-> Link= NON NULL | new_name= NULL.
 * @post Output-> Status=ERROR.
 */
void test4_link_set_name();

/**
 * @test Test for the set destination function.
 * @pre Input-> Link= NON NULL | new_destination=13.
 * @post Output-> Status=OK.
 */
void test1_link_set_destination();

/**
 * @test Test for the set destination function.
 * @pre Input-> Link= NULL | new_destination=13.
 * @post Output-> Status=ERROR.
 */
void test2_link_set_destination();

/**
 * @test Test for the set destination function.
 * @pre Input-> Link= NON NULL | new_destination=13 | previous_destiantion=12.
 * @post Output-> Status=OK.
 */
void test3_link_set_destination();

/**
 * @test Test for the set destination function.
 * @pre Input-> Link= NON NULL | new_destination=ID_ERROR.
 * @post Output-> Status=ERROR.
 */
void test4_link_set_destination();

/**
 * @test Test for the set direction function.
 * @pre Input-> Link= NON NULL | new_direction=N.
 * @post Output-> Status=OK.
 */
void test1_link_set_direction();

/**
 * @test Test for the set direction function.
 * @pre Input-> Link= NULL | new_direction=UNK_DIRECTION.
 * @post Output-> Status=ERROR.
 */
void test2_link_set_direction();

/**
 * @test Test for the set state function.
 * @pre Input-> Link= NON NULL | new_state=TRUE.
 * @post Output-> Status=OK.
 */
void test1_link_set_state();

/**
 * @test Test for the set state function.
 * @pre Input-> Link= NULL | new_state=TRUE.
 * @post Output-> Status=ERROR.
 */
void test2_link_set_state();
#endif