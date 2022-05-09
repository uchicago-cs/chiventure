/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * This examples serves to showcase the situational teleportation that is possible with
 * custom actions. If a player has a certain item in their inventory, they can
 * teleport to other rooms in the game.
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "../include/custom_action.h"

const char *banner = "THIS IS A CUSTOM ACTIONS EXAMPLE PROGRAM";

/* Makes sure the game is loaded */
char *check_game(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    return;
}

/* Defines a teleportation action */
int sample_teleporation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    return;
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    return;
}

int main(int argc, char **argv)
{
    return;
}