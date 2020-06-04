/*
 * Sample effect_t functions for testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
