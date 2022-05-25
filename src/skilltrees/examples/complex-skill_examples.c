#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/complex-skills_examples.h"
#include "skilltrees/complex_skills.h"
#include "playerclass/class_structs.h"
#include "playerclass/class_prefabs.h"

/*
EXAMPLES MAKING THE USE OF COMPLEX SKILLS
*/

/* see complex-skills_examples.h */
void combined_skill(chiventure_ctx_t* ctx)
{

    sid_t skill_id = 4000;

    skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Freeze!", 
                                     "You freeze your opponent.", 1, 100, 
                                     NULL, NULL);
    skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Fire Spell", 
                                     "You Set fire to your opponent", 1, 150, 
                                     NULL, NULL);
    skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Stone Shard", 
                                     "A hail of stones hit your opponent", 1, 
                                     200, NULL, NULL);
    
    skill_t** skills;
    skills[0] = skill_0;
    skills[1] = skill_1;
    skills[2] = skill_2;

    complex_skill_t* complex_comb_skill = complex_skill_new(COMBINED, skills, 3, 
                                                            NULL);
    skill_t* combined_skill = skill_new(0, PASSIVE, "Combined complex Skill", 
                                        "Several skills are performed",
                                        10, 5, NULL, complex_comb_skill);

    /* Showcase leveling functionality */
    skill_node_t* stat_node = skill_node_new(combined_skill, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, 
                        stat_node);
}

/* see complex-skills_examples.h */
void sequential_skill(chiventure_ctx_t* ctx)
{
    sid_t skill_id = 4500;

    skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "stun", 
                                     "You stun your opponent.", 1, 100, 
                                     NULL, NULL);
    skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "tornado", 
                                     "You set a tornado to your opponent", 1, 
                                     150, NULL, NULL);
    
    skill_t** skills;
    skills[0] = skill_0;
    skills[1] = skill_1;

    complex_skill_t* complex_seq_skill = complex_skill_new(SEQUENTIAL, skills, 
                                                            2, NULL);
    skill_t* sequential_skill = skill_new(0, PASSIVE, "Complex Stat Skill",
                                "Performs one skill after the other", 10, 5, 
                                NULL, complex_seq_skill);

    /* Showcase leveling functionality */
    skill_node_t* stat_node = skill_node_new(sequential_skill, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, 
                        stat_node);
}


void conditional_skill(chiventure_ctx_t* ctx)
{
    sid_t skill_id = 5000;

    int conditional_skill_execute(complex_skill_t* skill, chiventure_ctx_t* ctx) 

    skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "club smash", 
                                     "You smack your opp with a club", 
                                     1, 100, NULL, NULL);
    skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "mid move", 
                                     "You do a mid attack cuz your not an orc", 
                                     1, 150, NULL, NULL);
    
    skill_t** skills;
    skill[0] = skill_0;
    skill[1] = skill_1;

    complex_skill_t* complex_seq_skill = complex_skill_new(SEQUENTIAL, skills, 
                                                           2, NULL);
    skill_t* sequential_skill = skill_new(0, PASSIVE, "Complex Stat Skill",
                                "Performs one skill after the other", 10, 5, 
                                NULL, complex_seq_skill);

}
