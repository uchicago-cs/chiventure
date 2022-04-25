#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_management/actionmanagement.h"
#include "action_management/action_structs.h"
#include "game-state/item.h"
#include "game-state/player.h"
#include "common/ctx.h"

// might end up not using a couple of these
#define BUFFER_SIZE (100)
#define WRONG_KIND (2)
#define NOT_ALLOWED_DIRECT (3)
#define NOT_ALLOWED_INDIRECT (4)
#define NOT_ALLOWED_PATH (5)
#define CONDITIONS_NOT_MET (6)
#define EFFECT_NOT_APPLIED (7)

int check_npc_item_action(chiventure_ctx_t *c, action_type_t *a, npc_t *npc, char **ret_string)
{
    return;
}

Test(npc_actions, wrong_kind_1)
{
}

Test(npc_actions, conditions_not_met_1)
{
}
