#include <stdio.h>
#include <string.h>
#include "common/ctx.h"
#include "common/uthash.h"
#include "ui/ui.h"
#include "cli/operations.h"
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"
#include "skilltrees/effect.h"
#include "game-state/stats.h"
#include "game-state/item.h"

const char* banner =
    "    ________________________________________________________________________________________\n"
    "  / \\                                                                                       \\\n"
    " |   |                                                                                      |\n"
    "  \\_ |     ███████╗██╗  ██╗██╗██╗     ██╗  ████████╗██████╗ ███████╗███████╗███████╗        |\n"
    "     |      ██╔════╝██║ ██╔╝██║██║     ██║  ╚══██╔══╝██╔══██╗██╔════╝██╔════╝██╔════╝       |\n"
    "     |      ███████╗█████╔╝ ██║██║     ██║     ██║   ██████╔╝█████╗  █████╗  ███████╗       |\n"
    "     |      ╚════██║██╔═██╗ ██║██║     ██║     ██║   ██╔══██╗██╔══╝  ██╔══╝  ╚════██║       |\n"
    "     |      ███████║██║  ██╗██║███████╗███████╗██║   ██║  ██║███████╗███████╗███████║       |\n"
    "     |      ╚══════╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝       |\n"
    "     |   ___________________________________________________________________________________|___\n"
    "     |  /                                                                                      /\n"
    "     \\_/______________________________________________________________________________________/\n";
/* ========================================================================== */
/* Declare skill tree ======================================================= */
/* ========================================================================== */
skill_tree_t* skill_treedemo;



/* ========================================================================== */
/* Functions ================================================================ */
/* ========================================================================== */
/*
 * Creates a sample chiventure context for the skill trees demo game.
 *
 * Parameters:
 *  - None
 *
 * Returns:
 *  - A sample chiventure context containing the rooms/items described in detail
 *    in the README of this directory
 */
chiventure_ctx_t* create_example_ctx() {
    // Create example game
    game_t* game = game_new("Welcome to the skilltrees team's presentation! "
                            "Room progression is always (GO) NORTHward.");

    // Create example rooms
    room_t* level_up_room = room_new("Level Up Room", "", "The dragon at the end up the level"
                                   "looks really strong. You need to level up to get powerful skills"
                                   "before facing the final boss!");
    room_t* stat_skill_room = room_new("Stat Skill Room", "", "Looks like you've leveled up plenty!"
                                           "Level up one more time to unlock a statistic modifying"
                                           "skill.");
    room_t* attribute_skill_room = room_new("Attribute Skill Room", "", "Wow! You're a lot stronger"
                                 "now. Let's unlock an attribute skill and you'll be strong enough"
                                 "to face the dragon!");

    // Add example rooms to example game
    add_room_to_game(game, level_up_room);
    add_room_to_game(game, stat_skill_room);
    add_room_to_game(game, attribute_skill_room);

    // Set initial room
    game->curr_room = level_up_room;

    //Set player
    player_t *player = player_new("demo_player");
    stats_global_t *gs_health = stats_global_new("max_health", 100);
    stats_t* gs_health_stat = stats_new(gs_health, 100);
    stats_global_t *player_health = stats_global_new("current_health", 50);
    stats_t* player_health_stat = stats_new(player_health, 50);
    add_player_to_game(game, player);
    set_curr_player(game, player);

    /* Adding to hash table */
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_health->name, strlen(gs_health->name), gs_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, gs_health_stat->key, strlen(gs_health_stat->key), gs_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_health->name, strlen(player_health->name), player_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_health_stat->key, strlen(player_health_stat->key), player_health_stat);
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id, strlen(player->player_id), player);

    // Create example chiventure context
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

item_t* add_item (chiventure_ctx_t* ctx)
{
    /* Creating item and attribute */
    game_t* game = ctx -> game;
    game->all_items = NULL;
    item_t* dragon = item_new("DRAGON", "A scary dragon", "Is very hungry");
    attribute_t* is_alive = bool_attr_new("ALIVE", true);
    
    /* Adding things to hash tables */
    add_attribute_to_hash(dragon, is_alive);
    add_item_to_hash(&(game->all_items), dragon);

    return dragon;
}

void main(){
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    // Initialize skills
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    effect_t* stat_effect = make_player_stat_effect(health_boost);
    skill_t* stat_skill = skill_new(0, PASSIVE, "Stat Skill", "Modifies statistics", 10, 5, stat_effect);

    item_t* dragon = add_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;
    item_attr_effect_t* slay_dragon = define_item_attr_effect(dragon, "ARMED", att_tag, mod);
    effect_t* attribute_effect = make_item_attr_effect(slay_dragon);
    skill_t*  attribute_skill = skill_new(1, PASSIVE, "Attribute Skill", "Slays Dragon", 10, 10, attribute_effect);


    //Initialize skill nodes
    skillnode_t* stat_node = skill_node_new(stat_skill, 0, 14, 0);
    skillnode_t* attribute_node = skill_node_new(attribute_skill, 0, 19, 0); 
    //14 and 19 are the prereq_levels

    //Initialize Skill Trees
    node_prereq_add(stat_node, attribute_node); //attribute node is a prereq to unlock stat_node

    skill_treedemo = skill_tree_new(1, "Skill Tree For Demo! ", 2); 

    skill_tree_node_add(skill_tree, stat_node);
    skill_tree_node_add(skill_tree, attribute_node);

    printf("Stat Node added into our skill tree, you must be level %d to unlock this stat skill", 
            skill_treedemo->nodes[0]->prereq_level);
    printf("Attribute_node added as a prerequisite to Stat Node, you must be level %d to unlock attribute skill",
            skill_treedemo->nodes[1]->prereq_level);

    printf("Your current level is %d \n", get_level(ctx->game->curr_player)); //Is there a way to access player level here? So I can code in
                                        // whether player is high enough level for that skill


    // Initialize skill inventory

    //Enter the "stat skill room" and level up. Player can now unlock and execute new statistic modifying skill
        //leveling up in the stat skill room done using following function:
        skill_level_up(stat_skill);
        //stat_skill xp points then leveled up using following function:
            //for ex., xp is 50 points here
        skill_xp_up(stat_skill, 50);
    //Enter the "attribute skill room" and level up. Player cna now unlock and execute new attribute modifying skill.
        //leveling up in the "attribute skill room" done using following function:
        skill_level_up(attribute_skill);
        //attribute_skill xp points then leveled up using following function:
            //for ex., xp is 50 points here
        skill_xp_up(attribute_skill, 50);


    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free memory

    return 0;




}