#ifndef _INCLUDE_TEST_INIT_H_
#define _INCLUDE_TEST_INIT_H_

#include "skilltrees/effect.h"
#include "common/ctx.h"
#include "common/uthash.h"
#include "game-state/stats.h"
#include "game-state/item.h"

chiventure_ctx_t* create_player_and_stats();

item_t* add_bomb_item(chiventure_ctx_t* ctx);

effect_t* make_bomb_effect(item_t* bombitem);

item_t* add_chop_item(chiventure_ctx_t* ctx);

effect_t* make_choptree_effect(item_t* tree);

effect_t* make_innerpeace_effect(chiventure_ctx_t* ctx);

#endif /*TEST_INIT_H_*/