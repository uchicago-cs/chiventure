#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "skilltrees/inventory.h"
#include "skilltrees/effect.h"
#include "common/ctx.h"
#include "common/uthash.h"
#include "game-state/stats.h"
#include "game-state/item.h"

//just item_stat and player_stat_effect
//define_item_att_effect(item_t* item, char* att_id, enum attribute_tag att_tag, attribute_value_t attribute_mod)

void testmethod()
{
    item_t* bombitem = item_new("BOMB", "An armed bomb", "5 seconds till detonation") ;
    enum attribute_tag bombatt_tag = BOOLE ;
    attribute_value_t bombmod;
    bombmod.bool_val = false;
    item_attr_effect_t* itemdefusebombeffect = define_item_attr_effect(bombitem, "ARMED", bombatt_tag, bombmod);

    effect_t* defusebombeffect = make_item_attr_effect(itemdefusebombeffect);

    //chop tree effect
    item_t* choptreeitem = item_new("Axe", "An armed Axe", "Use this to cut down trees!");
    enum attribute_tag choptree_tag = BOOLE;
    attribute_value_t choptreemod;
    choptreemod.bool_val = false;

    item_attr_effect_t* itemchoptreeeffect = define_item_attr_effect(choptreeitem, "CHOP", choptree_tag, choptreemod);

    effect_t* choptreeeffect = make_item_attr_effect(itemdefusebombeffect);

    char* innerpeace_stats[2] = {"current_health", "peace_level"};

    double innerpeace_mod[2] = {250, 15};

    int innerpeace_duration[2] = {8, 8};

    chiventure_ctx_t* ctx;

    player_stat_effect_t* playerstatpeace = define_player_stat_effect("innerpeace", innerpeace_stats,
                                                                        innerpeace_mod, innerpeace_duration, 2, ctx);

    effect_t* innerpeace = make_player_stat_effect(playerstatpeace);
}
