/** 
 * @brief It declares the tests for the player module
 * 
 * @file player_test.h
 * @author Saul Lopez Romero
 * @version 1.0 
 * @date 27-03-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Player creation test.
 * @pre NULL pointer to a player.
 * @post Initialised player.
 */
void player_test_create_1();

/**
 * @test Player creation test.
 * @pre NULL pointer to a player and an invalid id.
 * @post NULL pointer.
 */
void player_test_create_2();

/**
 * @test Player name test
 * @pre Initialised player and a name.
 * @post Set name to player.
 */
void player_test_set_player_name_1();

/**
 * @test Player name test
 * @pre Initialised player and an invalid name.
 * @post ERROR is returned.
 */
void player_test_set_player_name_2();

/**
 * @test Player name test
 * @pre Initialised player and an invalid id.
 * @post ERROR is returned.
 */
void player_test_set_player_name_3();

/**
 * @test Player name test
 * @pre Initialised player and a name.
 * @post The name was set and its returned correctly.
 */
void player_test_get_player_name_1();

/**
 * @test Player name test
 * @pre Uninitialised player and a name.
 * @post Error when getting the name.
 */
void player_test_get_player_name_2();

/**
 * @test Player name test
 * @pre Initialised player and an invalid name.
 * @post Empty name is returned.
 */
void player_test_get_player_name_3();

/**
 * @test Player location test.
 * @pre Initilised player and valid place.
 * @post The position is set correctly.
 */
void player_test_set_player_location_1();

/**
 * @test Player location test.
 * @pre Uninitilised player and valid place.
 * @post The setter returns ERROR.
 */
void player_test_set_player_location_2();


/**
 * @test Player location test.
 * @pre Initilised player and invalid place.
 * @post The setter returns ERROR.
 */
void player_test_set_player_location_3();

/**
 * @test Player location test
 * @pre Initialised player and a location.
 * @post The location was set and its returned correctly.
 */
void player_test_get_player_location_1();

/**
 * @test Player location test
 * @pre Uninitialised player and a location.
 * @post Error when getting the location.
 */
void player_test_get_player_location_2();

/**
 * @test Player location test
 * @pre Initialised player and an invalid location.
 * @post Default location is returned.
 */
void player_test_get_player_location_3();

/**
 * @test Player object addition test
 * @pre Initialised player and an valid object.
 * @post Object is added.
 */
void player_test_add_object_1();

/**
 * @test Player object addition test
 * @pre Uninitialised player and an valid object.
 * @post Object isn't added.
 */
void player_test_add_object_2();

/**
 * @test Player object addition test
 * @pre Initialised player and an invalid object.
 * @post Object isn't added.
 */
void player_test_add_object_3();

/**
 * @test Player object addition test
 * @pre Initialised player and an valid objects.
 * @post Objects are added.
 */
void player_test_add_object_4();

/**
 * @test Player object addition test
 * @pre Initialised player with a limited inventory capacity and an valid objects.
 * @post Objects are added while they fit in.
 */
void player_test_add_object_5();

/**
 * @test Player object number test.
 * @pre Initialised player and valid objects, first empty and then with an object.
 * @post The amount of objects.
 */
void player_test_get_n_object_1();

/**
 * @test Player object number test.
 * @pre Uninitialised player and valid objects.
 * @post ERROR returned.
 */
void player_test_get_n_object_2();

/**
 * @test Player object number test.
 * @pre Initialised player and valid objects which are taken.
 * @post The correct amount of objects.
 */
void player_test_get_n_object_3();

/**
 * @test Player object number test.
 * @pre Initialised player and valid objects.
 * @post The correct amount of objects.
 */
void player_test_get_n_object_4();

/**
 * @test Player object obliteration test.
 * @pre Initialised player and valid objects.
 * @post The object is taken out.
 */
void player_test_del_object_1();

/**
 * @test Player object obliteration test.
 * @pre Uninitialised player and valid objects.
 * @post  Error is returned.
 */
void player_test_del_object_2();

/**
 * @test Player object obliteration test.
 * @pre Initialised player and invalid objects.
 * @post ERROR is returned.
 */
void player_test_del_object_3();

/**
 * @test Player object obliteration test.
 * @pre Initialised player and valid objects (plural).
 * @post The object is taken out.
 */
void player_test_del_object_4();

/**
 * @test Player object obliteration test.
 * @pre Initialised player and valid objects, where we take out one which doesn't exist.
 * @post ERROR is returned and the object isn't taken.
 */
void player_test_del_object_5();

/**
 * @test Player object description test.
 * @pre Initialised player and valid description.
 * @post The description is set.
 */
void player_test_set_player_gdesc_1();

/**
 * @test Player object description test.
 * @pre Uninitialised player and valid description.
 * @post ERROR takes place.
 */
void player_test_set_player_gdesc_3();

/**
 * @test Player object description test.
 * @pre Initialised player and invalid description.
 * @post ERROR takes place.
 */
void player_test_set_player_gdesc_2();

/**
 * @test Player object description test.
 * @pre Initialised player and valid description.
 * @post Description is returned.
 */
void player_test_get_player_gdesc_1();

/**
 * @test Player object description test.
 * @pre Uninitialised player and valid description.
 * @post ERROR is returned.
 */
void player_test_get_player_gdesc_2();

/**
 * @test Player object description test.
 * @pre Initialised player and invalid description.
 * @post Default description is returned.
 */
void player_test_get_player_gdesc_3();

/**
 * @test Player id test.
 * @pre Initialised player and valid id.
 * @post The id is returned.
 */
void player_test_get_id_1();

/**
 * @test Player id test.
 * @pre Initialised player and invalid id.
 * @post ERROR is returned.
 */
void player_test_get_id_2();

/**
 * @test Player id test.
 * @pre Uninitialised player and valid id.
 * @post ERROR is returned.
 */
void player_test_get_id_3();

/**
 * @test Player inventoy array getter test.
 * @pre Initialised player with objects.
 * @post The ids are returned.
 */
void player_test_get_inventory_1();

/**
 * @test Player inventoy array getter test.
 * @pre Uninitialised player with objects.
 * @post The ids aren't returned.
 */
void player_test_get_inventory_2();

/**
 * @test Player inventoy array getter test.
 * @pre Initialised player without objects.
 * @post NULL is returned.
 */
void player_test_get_inventory_3();

/**
 * @test Player object checker test.
 * @pre Initialised player with object.
 * @post The object is found.
 */
void player_test_player_has_object_1();

/**
 * @test Player object checker test.
 * @pre Initialised player with object, we search a non added one.
 * @post The object isn't found.
 */
void player_test_player_has_object_2();

/**
 * @test Player object checker test.
 * @pre Initialised player with invalid object.
 * @post The object isn't found.
 */
void player_test_player_has_object_3();

/**
 * @test Player object checker test.
 * @pre Initialised player with objects (plural).
 * @post The object is found.
 */
void player_test_player_has_object_4();

/**
 * @test Player object checker test.
 * @pre Uninitialised player with object.
 * @post The object isn't found.
 */
void player_test_player_has_object_5();

/**
 * @test Player health test.
 * @pre Initialised player and valid health.
 * @post The health is set.
 */
void player_test_set_health_1();

/**
 * @test Player health test.
 * @pre Uninitialised player and valid health.
 * @post The health isn't set.
 */
void player_test_set_health_2();

/**
 * @test Player health test.
 * @pre Initialised player and valid health.
 * @post The health is returned.
 */
void player_test_get_health_1();

/**
 * @test Player health test.
 * @pre Uninitialised player and valid health.
 * @post The health is returned.
 */
void player_test_get_health_2();

/**
 * @test Player capacity test.
 * @pre Initialised player and valid capacity.
 * @post The capacity is set.
 */
void player_test_set_inventory_capacity_1();

/**
 * @test Player capacity test.
 * @pre Uninitialised player and valid capacity.
 * @post The capacity isn't set.
 */
void player_test_set_inventory_capacity_2();

/**
 * @test Player capacity test.
 * @pre Initialised player and invalid capacity.
 * @post The capacity isn't set.
 */
void player_test_set_inventory_capacity_3();

/**
 * @test Player capacity test.
 * @pre Initialised player and valid capacity.
 * @post The capacity isn't returned.
 */
void player_test_get_inventory_capacity_1();

#endif

