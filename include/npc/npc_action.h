#ifndef _NPC_ACTION_H
#define _NPC_ACTION_H

#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "npc/npc.h"


// NPC ACTION STRUCTURE DEFINITION --------------------------------------------

/* An enumeration of all supported npc actions. Inspired by, but not directly
 * related to, actions KIND 1, 2, 3, in action management code.
 * 
 * KIND 4 ACTIONS - ACTION <npc>
 * KIND 5 ACTIONS - ACTION <npc> <item>
 * KIND 6 ACTIONS - ACTION <npc> <item> <item>
 */
enum npc_actions {
    // KIND 4 ACTIONS
    TALK_TO,
    IGNORE,
    // ATTACK,
    
    // KIND 5 ACTIONS
    GIVE,
    STEAL,

    // KIND 6 ACTIONS
    TRADE,
    BUY
};

/* Each enum corresponds to a different "KIND" of npc action */
enum npc_action_kind {
    NPC = 4,
    NPC_ITEM = 5,
    NPC_ITEM_ITEM = 6
};

/* An npc action struct that contains the following:
 * - c_name: the 'canonical' string that should call the enum
 * - kind: an enumeration of the kind of action
 */
typedef struct npc_action {
    char *c_name; // e.g. "ignore"
    enum npc_action_kind kind;
} npc_action_t;


// STRUCT FUNCTIONS -----------------------------------------------------------

npc_action_t *npc_action_new(char *c_name, enum npc_action_kind kind);

int npc_action_init(npc_action_t *a, char *c_name, enum npc_action_kind kind);

int npc_action_free(npc_action_t *a);

#endif