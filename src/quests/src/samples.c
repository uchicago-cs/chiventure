#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/samples.h"

/* See samples.h */
task_t *create_sample_task(char *task_id, 
    bool create_mission, char *mission_target_name, mission_types_t mission_type,
    bool create_reward, int reward_xp, item_t *reward_item, 
    bool create_prereq, int prereq_hp, int prereq_level) {

    assert(task_id != NULL);

    mission_t *mission = NULL;
    if(create_mission) {
        mission = mission_new(mission_target_name, mission_type);
    }  

    reward_t *reward = NULL;
    if(create_reward) {
        reward = reward_new(reward_xp, reward_item);
    }

    prereq_t *prereq = NULL;
    if(create_prereq) {
        prereq = prereq_new(prereq_hp, prereq_level);
    }

    return task_new(task_id, mission, reward, prereq);
}

/* See samples.h */
quest_t *create_sample_quest(char *quest_id,
    bool create_reward, int reward_xp, item_t *reward_item,
    bool create_prereq, int prereq_hp, int prereq_level) {
    
    assert(quest_id != NULL);

    reward_t *reward = NULL;
    if(create_reward) {
        reward = reward_new(reward_xp, reward_item);
    }

    prereq_t *prereq = NULL;
    if(create_prereq) {
        prereq = prereq_new(prereq_hp, prereq_level);
    }
    return quest_new(quest_id, reward, prereq);
}

/* See samples.h */
player_t *create_sample_player(char *player_id, int health, int level) {
    player_t* player = player_new(player_id);

    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player, health_stat);

    player->level = level;
    return player;
}

/* See samples.h */
quest_ctx_t *create_sample_ctx() {
    player_t *player = create_sample_player("player", 50, 5);
    return quest_ctx_new(player, NULL);
}
