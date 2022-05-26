#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill-example.h"
#include "skilltrees/complex_skills.h"
#include "skilltrees/reader.h"
#include "playerclass/class_structs.h"
#include "playerclass/class_prefabs.h"

/*
 * SKILL EXAMPLES FOR BATTLES DEMO
 */

/* See skill-example.h */
char* effect_diss_track(char* args){
    return "8";
}


/* See skill-example.h */
char* effect_fireball(char* args){
    return "10";
}


/* See skill-example.h */
char* effect_sword_slash(char* args){
    return "9";
}


/* See skill-example.h */
skill_inventory_t* bard_inventory() {
    skill_inventory_t *bard_inv = inventory_new(1, 0);

    skill_t *diss_track = skill_new(0, ACTIVE, "Diss Track", "A Bard attack spell that deals 8 damage.", 2, 5, effect_diss_track);

    inventory_skill_add(bard_inv, diss_track);

    return bard_inv;
}


/* See skill-example.h */
skill_inventory_t* wizard_inventory() {
    skill_inventory_t *wizard_inv = inventory_new(1, 0);

    skill_t *fireball = skill_new(1, ACTIVE, "Fireball", "A Wizard attack spell that deals 10 damage.", 2, 5, effect_fireball);

    inventory_skill_add(wizard_inv, fireball);

    return wizard_inv;
}


/* See skill-example.h */
skill_inventory_t* knight_inventory() {
    skill_inventory_t *knight_inv = inventory_new(1, 0);

    skill_t *sword_slash = skill_new(2, ACTIVE, "Sword Slash", "A Knight attack that deals 9 damage.", 2, 5, effect_sword_slash);

    inventory_skill_add(knight_inv, sword_slash);

    return knight_inv;
}


/*
EXAMPLES MAKING THE USE OF COMPLEX SKILLS
*/

/* see skill-example.h */
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
    skill[0] = skill_0;
    skill[1] = skill_1;
    skill[2] = skill_2;

    complex_skill_t* complex_comb_skill = complex_skill_new(COMBINED, skills, 3, NULL);
    skill_t* combined_skill = skill_new(0, PASSIVE, "Combined complex Skill", "Several skills are performed",
                                        10, 5, NULL, complex_comb_skill);

    skill_node_t* stat_node = skill_node_new(combined_skill, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

/* see skill-example.h */
void sequential_skill(chiventure_ctx_t* ctx)
{
    sid_t skill_id = 4500;

    skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "stun", 
                                     "You stun your opponent.", 1, 100, 
                                     NULL, NULL);
    skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "tornado", 
                                     "You set a tornado to your opponent", 1, 150, 
                                     NULL, NULL);
    
    skill_t** skills;
    skills[0] = skill_0;
    skills[1] = skill_1;

    complex_skill_t* complex_seq_skill = complex_skill_new(SEQUENTIAL, skills, 2, NULL);
    skill_t* sequential_skill = skill_new(0, PASSIVE, "Complex Stat Skill",
                                "Performs one skill after the other", 10, 5, NULL, complex_seq_skill);


    skill_node_t* stat_node = skill_node_new(sequential_skill, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

/* see skill-example.h */
void conditional_skill(chiventure_ctx_t* ctx)
{
    sid_t skill_id = 5000;

    attr_reader_effect_t* attr_reader = attr_reader_effect_new("orc", 3, 
                                                                READ_PLAYER);
    
    skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "club smash", 
                                     "You smack your opp with a club", 
                                     1, 100, NULL, NULL);
    skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "mid move", 
                                    "You do a mid attack cuz you're not an orc", 
                                    1, 100, NULL, NULL);
    
    skill_t** skills;
    skills[0] = skill_0;
    skills[1] = skill_1;

    complex_skill_t* cond_skill = complex_skill_new(COMPLEX_CONDITIONAL, skills,
                                                    2, attr_reader);

    skill_node_t* cond_node = skill_node_new(cond_skill, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, 
                        cond_node);
}
