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

item_t* bombitem;


effect_t* defusebombeffect;

//chop tree effect
item_t* choptreeitem;

item_attr_effect_t* itemchoptreeeffect;

effect_t* choptreeeffect;

char* innerpeace_stats[];

double innerpeace_mod[];

int innerpeace_duration[];

player_stat_effect_t* playerstatpeace;
effect_t* innerpeace;