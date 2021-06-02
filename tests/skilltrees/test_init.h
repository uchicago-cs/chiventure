#ifndef _INCLUDE_TEST_INIT_H_
#define _INCLUDE_TEST_INIT_H_

#include "skilltrees/effect.h"
#include "common/ctx.h"
#include "common/uthash.h"
#include "game-state/stats.h"
#include "game-state/item.h"

chiventure_ctx_t* create_player_and_stats();

item_t* add_item (chiventure_ctx_t* ctx);

#endif /*TEST_INIT_H_*/