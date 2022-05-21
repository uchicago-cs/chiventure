#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "test_init.h"


/* Tests for move unlock effects */
Test(effect_tests, define_move_effect_test)
{
    move_t *move = move_new(1, "abc", "", PHYS, NO_TARGET, NO_TARGET, 
                            SINGLE, 0, NULL, 55, 100, NULL, NULL, NULL, NULL);
    cr_assert_not_null(move, "Error: move_new failed to create move");
    move_effect_t* moveeffect = define_move_effect(move);
    cr_assert_not_null(moveeffect, "Error: define_move_effect failed to create move effect");

}

Test(effect_tests, make_move_effect_test)
{
    move_t *move = move_new(1, "abc", "", PHYS, NO_TARGET, NO_TARGET, 
                            SINGLE, 0, NULL, 55, 100, NULL, NULL, NULL, NULL);
    cr_assert_not_null(move, "Error: move_new failed to create move");
    move_effect_t* moveeffect = define_move_effect(move);
    cr_assert_not_null(moveeffect, "Error: define_move_effect failed to create move effect");
    effect_t* effect = make_move_effect(moveeffect);
    cr_assert_eq(effect->effect_type, MOVE_UNLOCK, "Error: make_move_effect failed to set effect type");
    cr_assert_not_null(effect, "Error: make_move_effect failed to create effect");

}

/* Tests for execute_move_effect function */

/* This test checks if execute_move_effect correctly adds a move effect to an empty list */

Test(effect_tests, execute_move_effect_test_empty_list)
{
    chiventure_ctx_t* ctx = create_player_and_stats();

    move_t *move = move_new(1, "abc", "", PHYS, NO_TARGET, NO_TARGET, 
                            SINGLE, 0, NULL, 55, 100, NULL, NULL, NULL, NULL);
    cr_assert_not_null(move, "Error: move_new failed to create move");
    move_effect_t* moveeffect = define_move_effect(move);
    cr_assert_not_null(moveeffect, "Error: define_move_effect failed to create move effect");
    
    int check = execute_move_effect(ctx, moveeffect);
    cr_assert_eq(check, SUCCESS, "Error: Failure of execute_move_effect");
}

/* This test checks if execute_move_effect correctly adds a move effect to an existing list of effects */

Test(effect_tests, execute_move_effect_test_existing_list)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    
    move_t *old_move = move_new(2, "def", "", PHYS, NO_TARGET, NO_TARGET, 
                                SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    cr_assert_not_null(old_move, "Error: move_new failed to create move");
    move_effect_t* moveeffect1 = define_move_effect(old_move);
    cr_assert_not_null(moveeffect1, "Error: define_move_effect failed to create move effect");
    
    int check1 = execute_move_effect(ctx, moveeffect1);
    cr_assert_eq(check1, SUCCESS, "Error: Failure of execute_move_effect");

    move_t *new_move = move_new(3, "ghi", "", PHYS, NO_TARGET, NO_TARGET, 
                                SINGLE, 0, NULL, 1, 100, NULL, NULL, NULL, NULL);
    
    cr_assert_not_null(new_move, "Error: move_new failed to create move");
    move_effect_t* moveeffect2 = define_move_effect(new_move);
    cr_assert_not_null(moveeffect2, "Error: define_move_effect failed to create move effect");
    
    int check2 = execute_move_effect(ctx, moveeffect2);
    cr_assert_eq(check2, SUCCESS, "Error: Failure of execute_move_effect");
    
    move_t *new_move2 = move_new(6, "pqr", "", PHYS, NO_TARGET, NO_TARGET, 
                                SINGLE, 0, NULL, 1, 100, NULL, NULL, NULL, NULL);
    cr_assert_not_null(new_move2, "Error: move_new failed to create move");
    move_effect_t* moveeffect3 = define_move_effect(new_move2);
    cr_assert_not_null(moveeffect3, "Error: define_move_effect failed to create move effect");
    
    int check3 = execute_move_effect(ctx, moveeffect3);
    cr_assert_eq(check3, SUCCESS, "Error: Failure of execute_move_effect");
}
   
//Tests for stat mod effects

/* This test checks if the define function works correctly if all values provided are valid */
Test(effect_tests, define_player_stat_effect_correct_vals) 
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    
    /* Checking if values are set correctly */
    cr_assert_not_null(health_boost, "Error: define_player_stat failed");
    cr_assert_eq(health_boost->player_stat_effect_name, "health boost", "Error: Name not assigned correctly");
    cr_assert_eq(health_boost->modifications[0], 150, "Error:  First modification is wrong");
    cr_assert_eq(health_boost->modifications[1], 100, "Error:  Second modification is wrong");
    cr_assert_eq(health_boost->durations[0], 5, "Error: First Duration is wrong");
    cr_assert_eq(health_boost->durations[1], 5, "Error: Second Duration is wrong");
    cr_assert_eq(health_boost->num_stats, 2, "Number of stats is wrong");
}

/* This test checks if the define function works correctly if a value provided is invalid */
Test(effect_tests, define_player_stat_effect_incorrect_vals)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "max_attack"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    cr_assert_eq(health_boost, NULL, "Error: Health boost should be null due to incorrect input");
}

/* This test checks if the make test sets the enum correctly */
Test(effect_tests, make_player_stat_effect_test)
{
    /* Creating player stat effect and making sure everything is set properly */
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    
    cr_assert_not_null(health_boost, "Error: define_player_stat failed");
    cr_assert_eq(health_boost->player_stat_effect_name, "health boost", "Error: Name not assigned correctly");
    cr_assert_eq(health_boost->modifications[0], 150, "Error:  First modification is wrong");
    cr_assert_eq(health_boost->modifications[1], 100, "Error:  Second modification is wrong");
    cr_assert_eq(health_boost->durations[0], 5, "Error: First Duration is wrong");
    cr_assert_eq(health_boost->durations[1], 5, "Error: Second Duration is wrong");
    cr_assert_eq(health_boost->num_stats, 2, "Number of stats is wrong");
    
    /* Running make_player_stat and checking if values are set correctly */
    effect_t* stat_effect = make_player_stat_effect(health_boost);
    cr_assert_not_null(stat_effect, "Error: returns a null effect");
    cr_assert_not_null(stat_effect->data.s, "Error: did not copy over the effect correctly");
    cr_assert_eq(stat_effect->effect_type, PLAYER_STATISTIC_MOD, "Error: Enum value not correct");
}

/* This test checks if the execution function works as expected */
Test(effect_tests, execute_player_stat_effect_test)
{
    /* Creating player stat effect and making sure values are set correctly */
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    
    cr_assert_not_null(health_boost, "Error: define_player_stat failed");
    cr_assert_eq(health_boost->player_stat_effect_name, "health boost", "Error: Name not assigned correctly");
    cr_assert_eq(health_boost->modifications[0], 150, "Error:  First modification is wrong");
    cr_assert_eq(health_boost->modifications[1], 100, "Error:  Second modification is wrong");
    cr_assert_eq(health_boost->durations[0], 5, "Error: First Duration is wrong");
    cr_assert_eq(health_boost->durations[1], 5, "Error: Second Duration is wrong");
    cr_assert_eq(health_boost->num_stats, 2, "Number of stats is wrong");

    /* Running execute_player_stat_effect and making sure it modifies the values as expected */
    int check = execute_player_stat_effect(health_boost, ctx);
    cr_assert_eq(check, SUCCESS, "Error:  Failure of execute_player_stat");
    stats_hash_t* player_stats = ctx->game->curr_player->player_stats;
    stats_t* current_health;
    stats_t* max_health;
    HASH_FIND_STR(player_stats, "max_health", max_health);
    cr_assert_eq(150, max_health->modifier, "Max health not changed correctly");
    HASH_FIND_STR(player_stats, "current_health", current_health);
    cr_assert_eq(100, current_health->modifier, "Current health not changed correctly");
}

/*** TESTS FOR ITEM ATT EFFECT ***/

/* This test checks if define_item_attr_effect works correctly if all values input are correct */
Test(effect_tests, define_item_attr_effect_correct_vals)
{
    /* Creating values to run define_item_attr_effect */
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;
    
    cr_assert_not_null(bomb, "Bomb itself is null");
    /* Running define_item_attr_effect and making sure it gives the correct values */
    item_attr_effect_t* disarm_bomb = define_item_attr_effect(bomb, "ARMED", att_tag, mod);
    cr_assert_not_null(disarm_bomb, "Error: Returned NULL effect");
    
    cr_assert_eq(disarm_bomb->att_tag, BOOLE, "Error : Have not set tag correctly");
    cr_assert_eq(disarm_bomb->attribute_mod.bool_val, false, "Error : Did not set value correctly");
}

// This test checks if define_item_att_effect works correctly if the inputted value is not correct
Test(effect_tests, define_item_attr_effect_invalid_vals)
{    /* Creating values to run define_item_attr_effect */
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    attribute_value_t mod;
    mod.double_val = 15.0;
    enum attribute_tag att_tag = DOUBLE;

    /* Running define_item_attr_effect and making sure it returns NULL */
    item_attr_effect_t* disarm_bomb = define_item_attr_effect(bomb, "BLAST_RADIUS", att_tag, mod);
    cr_assert_eq(disarm_bomb, NULL, "Error : Should return NULL");
}

// This test checks if make_item_attr_effect works correctly
Test(effect_tests, make_item_attr_effect_test)
{
    /*Creating an item_attr_effect and making sure it works as expected */
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;

    item_attr_effect_t* disarm_bomb = define_item_attr_effect(bomb, "ARMED", att_tag, mod);
    cr_assert_not_null(disarm_bomb, "Error : Returned NULL effect");
    cr_assert_eq(disarm_bomb->att_tag, BOOLE, "Error : Have not set tag correctly");
    cr_assert_eq(disarm_bomb->attribute_mod.bool_val, false, "Error : Did not set value correctly");
    
    /*Using created item_attr_effect to check if make_item_attr_effect works correctly */
    effect_t* attribute_effect = make_item_attr_effect(disarm_bomb);
    cr_assert_not_null(attribute_effect, "Error : Returned a NULL effect");
    cr_assert_not_null(attribute_effect->data.i_a, "Error : did not copy over effect correctly");
    cr_assert_eq(attribute_effect->effect_type, ITEM_ATTRIBUTE_MOD, "Error: Enum value not correct");
}

// This test checks if execute_item_attr_effect works correctly
Test(effect_tests, execute_item_attr_effect_test)
{
    /* Creating an item_attr_effect and making sure it works as expected */
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;
    
    item_attr_effect_t* disarm_bomb = define_item_attr_effect(bomb, "ARMED", att_tag, mod);
    cr_assert_not_null(disarm_bomb, "Error : Returned NULL effect");
    cr_assert_eq(disarm_bomb->att_tag, BOOLE, "Error : Have not set tag correctly");
    cr_assert_eq(disarm_bomb->attribute_mod.bool_val, false, "Error : Did not set value correctly");
    
    /* Checking if execute_item_attr_effect works correctly */
    int check = execute_item_attr_effect(disarm_bomb);
    cr_assert_eq(check, SUCCESS, "Error: Did not execute correctly");
    attribute_t* arm_status = get_attribute(bomb, "ARMED");
    cr_assert_eq(arm_status->attribute_value.bool_val, 0, "Error: Did not change value");
}
