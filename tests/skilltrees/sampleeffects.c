#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "skilltrees/inventory.h"
#include "skilltrees/effect.h"

//just item_stat and player_stat_effect
//define_item_att_effect(item_t* item, char* att_id, enum attribute_tag att_tag, attribute_value_t attribute_mod)

item_t* bombitem = item_new("BOMB", "An armed bomb", "5 seconds till detonation")
enum attribute_tag bombatt_tag = BOOLE;
attribute_value_t bombmod;
mod.bool_val = false;

item_att_effect_t* itemdefusebombeffect = define_item_att_effect(bombitem, "ARMED", bombtag, bombmod);

effect_t* defusebombeffect = make_item_att_effect(itemdefusebombeffect);



define_player_stat_effect(char* player_stat_effect_name, char** stat_names, double* modifications, int* durations, int num_stats, chiventure_ctx_t* ctx)

char* innerpeace_stats[] = {"current_health", "peace_level"};

double innerpeace_mod[] = {250, 15};

int innerpeace_duration[] = {8, 8};

player_stat_effect_t* playerstatpeace = define_player_stat_effect("innerpeace", innerpeace_stats,
                                                                    innerpeace_mod, innerpeace_duration, 2, ctx);
effect_t innerpeace = make_player_stat_effect(playerstatpeace);



