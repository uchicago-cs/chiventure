#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/reader.h"
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "skilltrees/inventory.h"
#include "skilltrees/effect.h"
#include "test_init.h"

// TO DO : check test line 194, 211 for passability 

/* Test reader_effect_new for attribute reader */
Test(reader_tests, reader_effect_new_test_attr){
    reader_type_t type = READER_ATTRIBUTE;
    stat_reader_effect_t* sr = NULL;
    attr_reader_effect_t *ar = attr_reader_effect_new("undead", 6, READ_PLAYER);

    reader_effect_t *new = reader_effect_new(type, ar, sr);
    cr_assert_eq(new->type,READER_ATTRIBUTE,
        "Error: failed test reader_effect_new_test_attr on new->type\n");
    cr_assert_eq(new->attr_reader,ar,
        "Error: failed test reader_effect_new_test_attr on new->attr_reader\n");
    cr_assert_eq(new->stat_reader,NULL,
        "Error: failed test reader_effect_new_test_attr on new->stat_reader\n");
}

/* Test reader_effect_new for statistic reader */
Test(reader_tests, reader_effect_new_test_stat){
    reader_type_t type = READER_STATISTIC;
    attr_reader_effect_t* ar = NULL;
    stat_reader_effect_t *sr = stat_reader_effect_new(50, SPEED, GREATER, READ_PLAYER);

    reader_effect_t *new = reader_effect_new(type, ar, sr);
    cr_assert_eq(new->type,READER_STATISTIC,
        "Error: failed test reader_effect_new_test_stat on new->type\n");
    cr_assert_eq(new->attr_reader,NULL,
        "Error: failed test reader_effect_new_test_stat on new->attr_reader\n");
    cr_assert_eq(new->stat_reader,sr,
        "Error: failed test reader_effect_new_test_stat on new->stat_reader\n");
}

// int reader_effect_init(reader_effect_t* reader, reader_type_t type, attr_reader_effect_t* attr_reader,
//                   stat_reader_effect_t* stat_reader)


/* Test reader_effect_init for attribute reader */
Test(reader_tests, reader_effect_init_test_attr){
    reader_effect_t* new = (reader_effect_t*)malloc(sizeof(reader_effect_t));
    reader_type_t type = READER_ATTRIBUTE;
    attr_reader_effect_t *ar = attr_reader_effect_new("undead", 6, READ_PLAYER);
    stat_reader_effect_t *sr = NULL;

    int rc = reader_effect_init(new, type, ar, sr);
    cr_assert_eq(rc,SUCCESS,
        "Error: failed test reader_effect_new_test_attr, initialization failed\n");
    cr_assert_eq(new->type,READER_ATTRIBUTE,
        "Error: failed test reader_effect_new_test_attr on new->type\n");
    cr_assert_eq(new->attr_reader,ar,
        "Error: failed test reader_effect_new_test_attr on new->attr_reader\n");
    cr_assert_eq(new->stat_reader,NULL,
        "Error: failed test reader_effect_new_test_attr on new->stat_reader\n");
}

/* Test reader_effect_init for statistics reader */
Test(reader_tests, reader_effect_init_test_stat){
    reader_effect_t* new = (reader_effect_t*)malloc(sizeof(reader_effect_t));
    reader_type_t type = READER_STATISTIC;
    attr_reader_effect_t* ar = NULL;
    stat_reader_effect_t *sr = stat_reader_effect_new(50, SPEED, GREATER, READ_PLAYER);

    int rc = reader_effect_init(new, type, ar, sr);
    cr_assert_eq(rc,SUCCESS,
        "Error: failed test reader_effect_init_test_stat, initialization failed\n");
    cr_assert_eq(new->type,READER_STATISTIC,
        "Error: failed test reader_effect_new_test_stat on new->type\n");
    cr_assert_eq(new->attr_reader,NULL,
        "Error: failed test reader_effect_new_test_stat on new->attr_reader\n");
    cr_assert_eq(new->stat_reader,sr,
        "Error: failed test reader_effect_new_test_stat on new->stat_reader\n");
}

/* Test reader_effect_free for stat freeing*/
Test(reader_tests, reader_effect_free_test_stat){
    stat_reader_effect_t *sr = stat_reader_effect_new(50, SPEED, GREATER, READ_PLAYER);
    int rc = stat_reader_effect_free(sr);
    cr_assert_eq(rc, SUCCESS, "Error: failed test reader_effect_free_test for stat\n"); 
}

/* Test reader_effect_free for attr freeing*/
Test(reader_tests, reader_effect_free_test_attr){
    attr_reader_effect_t *ar = attr_reader_effect_new("undead", 6, READ_PLAYER);
    int rc = attr_reader_effect_free(ar);
    cr_assert_eq(rc, SUCCESS, "Error: failed test stat_reader_effect_free_test\n");
}

/* Test stat_reader_effect_new */
Test(reader_tests, stat_reader_effect_new_test){
    stat_reader_effect_t *sr = stat_reader_effect_new(50, SPEED, GREATER, READ_PLAYER);

    cr_assert_eq(sr->value,50,
        "Error: failed test stat_reader_effect_new_test on sr->value\n");
    cr_assert_eq(sr->stat_type,SPEED,
        "Error: failed test stat_reader_effect_new_test on sr->stat_type\n");
    cr_assert_eq(sr->comparison,GREATER,
        "Error: failed test stat_reader_effect_new_test on sr->comparison\n");
    cr_assert_eq(sr->location,READ_PLAYER,
        "Error: failed test stat_reader_effect_new_test on sr->location\n");
}

/* Test stat_reader_effect_init */
Test(reader_tests, stat_reader_effect_init_test){
    stat_reader_effect_t* sr = (stat_reader_effect_t*)malloc(sizeof(stat_reader_effect_t));
    int rc = stat_reader_effect_init(sr, 50, SPEED, GREATER, READ_PLAYER);

    cr_assert_eq(rc,SUCCESS,
        "Error: failed test stat_reader_effect_init_test, initialization failed\n");
    cr_assert_eq(sr->value,50,
        "Error: failed test stat_reader_effect_init_test on sr->value\n");
    cr_assert_eq(sr->stat_type,SPEED,
        "Error: failed test stat_reader_effect_init_test on sr->stat_type\n");
    cr_assert_eq(sr->comparison,GREATER,
        "Error: failed test stat_reader_effect_init_test on sr->comparison\n");
    cr_assert_eq(sr->location,READ_PLAYER,
        "Error: failed test stat_reader_effect_init_test on sr->location\n");
}

/* Test stat_reader_effect_free */
Test(reader_tests, stat_reader_effect_free_test){
    stat_reader_effect_t *sr = stat_reader_effect_new(50, SPEED, GREATER, READ_PLAYER);
    int rc = stat_reader_effect_free(sr);
    cr_assert_eq(rc, SUCCESS, "Error: failed test stat_reader_effect_free_test\n");
}

/* Test attr_reader_effect_new */
Test(reader_tests, attr_reader_effect_new_test){
    attr_reader_effect_t *ar = attr_reader_effect_new("undead", 6, READ_PLAYER);

    cr_assert_str_eq(ar->value,"undead",
        "Error: failed test attr_reader_effect_new_test on ar->value\n");
    cr_assert_eq(ar->str_len,6,
        "Error: failed test attr_reader_effect_new_test on ar->str_len\n");
    cr_assert_eq(ar->location,READ_PLAYER,
        "Error: failed test attr_reader_effect_new_test on ar->location\n");
}

/* Test attr_reader_effect_init */
Test(reader_tests, attr_reader_effect_init_test){
    attr_reader_effect_t *ar = (attr_reader_effect_t*)malloc(sizeof(attr_reader_effect_t));
    int rc = attr_reader_effect_init(ar, "undead", 6, READ_PLAYER);
    
    cr_assert_eq(rc,SUCCESS,
        "Error: failed test attr_reader_effect_init_test, initialization failed\n");
    cr_assert_str_eq(ar->value,"undead",
        "Error: failed test attr_reader_effect_init_test on ar->value\n");
    cr_assert_eq(ar->str_len,6,
        "Error: failed test attr_reader_effect_init_test on ar->str_len\n");
    cr_assert_eq(ar->location,READ_PLAYER,
        "Error: failed test attr_reader_effect_init_test on ar->location\n");
}

/* Test attr_reader_effect_free */
Test(reader_tests, attr_reader_effect_free_test){
    attr_reader_effect_t *ar = attr_reader_effect_new("undead", 6, READ_PLAYER);
    int rc = attr_reader_effect_free(ar);
    cr_assert_eq(rc, SUCCESS, "Error: failed test stat_reader_effect_free_test\n");
}

/* Test execute_reader_effect for statistic reader, true */
Test(reader_tests, execute_reader_effect_with_stat_test_true){
    chiventure_ctx_t* ctx = create_player_and_stats();
    stat_reader_effect_t *sr = stat_reader_effect_new(50, HP, EQUALS, READ_PLAYER);
    reader_effect_t *effect = reader_effect_new(READER_STATISTIC, NULL, sr);
    int rc = execute_reader_effect(effect, ctx);
    cr_assert_eq(rc, 1, "Error: failed test execute_reader_effect_test_true for stat\n");  
}

/* Test execute_reader_effect for statistic reader, false */
Test(reader_tests, execute_reader_effect_with_stat_test_false){
    chiventure_ctx_t* ctx = create_player_and_stats();
    stat_reader_effect_t *sr = stat_reader_effect_new(50, HP, NOT, READ_PLAYER);
    reader_effect_t *effect = reader_effect_new(READER_STATISTIC, NULL, sr);
    int rc = execute_reader_effect(effect, ctx);
    cr_assert_eq(rc, 0, "Error: failed test execute_reader_effect_test_false for stat\n");
}

// Not sure this will work because of the case coverage in reader.c -- come back to this!
/* Test execute_reader_effect for attribute reader, true */
Test(reader_tests, execute_reader_effect_with_attr_test_true){
    chiventure_ctx_t* ctx = create_player_and_stats();
    attr_reader_effect_t *ar = attr_reader_effect_new("TEST CHARACTER", 14, READ_PLAYER);
    reader_effect_t *effect = reader_effect_new(READER_ATTRIBUTE, ar, NULL);
    int rc = execute_reader_effect(effect, ctx);
    cr_assert_eq(rc, 1, "Error: failed test execute_attr_reader_effect_test for true\n");
}

/* Test execute_reader_effect for attribute reader, false */
Test(reader_tests, execute_reader_effect_with_attr_test_false){
    chiventure_ctx_t* ctx = create_player_and_stats();
    attr_reader_effect_t *ar = attr_reader_effect_new("undead", 6, READ_PLAYER);
    reader_effect_t *effect = reader_effect_new(READER_ATTRIBUTE, ar, NULL);
    int rc = execute_reader_effect(effect, ctx);
    cr_assert_eq(rc, 0, "Error: failed test execute_reader_effect_test_false for attr\n");
}

// Not sure this will work because of the case coverage in reader.c -- come back to this!
/* Test execute_attr_reader_effect for true*/
Test(reader_tests, execute_attr_reader_effect_test_true){
    chiventure_ctx_t* ctx = create_player_and_stats();
    attr_reader_effect_t *ar = attr_reader_effect_new("TEST CHARACTER", 14, READ_PLAYER);
    int rc = execute_attr_reader_effect(ar, ctx);
    cr_assert_eq(rc, 1, "Error: failed test execute_attr_reader_effect_test for true\n");
}

/* Test execute_attr_reader_effect for false*/
Test(reader_tests, execute_attr_reader_effect_test_false){
    chiventure_ctx_t* ctx = create_player_and_stats();
    attr_reader_effect_t *ar = attr_reader_effect_new("undead", 6, READ_PLAYER);
    int rc = execute_attr_reader_effect(ar, ctx);
    cr_assert_eq(rc, 0, "Error: failed test execute_attr_reader_effect_test for false\n");
}

/* Test execute_stat_reader_effect for true*/
Test(reader_tests, execute_stat_reader_effect_test_true){
    chiventure_ctx_t* ctx = create_player_and_stats();
    stat_reader_effect_t *sr = stat_reader_effect_new(50, HP, EQUALS, READ_PLAYER);
    int rc = execute_stat_reader_effect(sr, ctx);
    cr_assert_eq(rc, 1, "Error: failed test execute_stat_reader_effect_test for true\n");
}

/* Test execute_stat_reader_effect for false*/
Test(reader_tests, execute_stat_reader_effect_test_false){
    chiventure_ctx_t* ctx = create_player_and_stats();
    stat_reader_effect_t *sr = stat_reader_effect_new(50, HP, NOT, READ_PLAYER);
    int rc = execute_stat_reader_effect(sr, ctx);
    cr_assert_eq(rc, 0, "Error: failed test execute_stat_reader_effect_test for false\n");
}
