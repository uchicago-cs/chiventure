/*
 * Sample effect_t functions for testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/skilltrees/effect.h"

char* effect_unlock_door(char* args) {
    char* msg = "unlocked the door!";
    unsigned int rlen = strlen(args) + strlen(msg) + 2;
    char* res = (char*)malloc(sizeof(char) * rlen);
    sprintf(res, "%s %s", args, msg);
    return res;
}

char* effect_defuse_bomb(char* args) {
    return "Bomb defused!";
}

char* effect_chop_tree(char* args) {
    return "Tree chopped!";
}

char* effect_inner_peace(char* args) {
    return "Maintaining inner peace.";
}


Test(effect_tests, define_move_effect_test)
{
    move_t *move = move_new("abc", 1, NULL, true, 10, 55);
    cr_assert_not_null(move, "Error: move_new failed to create move");
    move_effect_t* moveeffect = define_move_effect(move);
    cr_assert_not_null(moveeffect, "Error: define_move_effect failed to create move effect");

}

Test(effect_tests, make_move_effect_test)
{
    move_t *move = move_new("abc", 1, NULL, true, 10, 55);
    cr_assert_not_null(move, "Error: move_new failed to create move");
    move_effect_t* moveeffect = define_move_effect(move);
    cr_assert_not_null(moveeffect, "Error: define_move_effect failed to create move effect");
    effect_t* effect = make_move_effect(moveeffect);
    cr_assert_eq(effect->effect_type, MOVE_UNLOCK, "Error: make_move_effect failed to set effect type");
    cr_assert_not_null(effect, "Error: make_move_effect failed to create effect");

}