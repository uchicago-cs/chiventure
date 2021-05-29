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
    /* Create example game */
    game_t* game = game_new("Welcome to the skilltrees team's presentation! "
                            "Room progression is always (GO) NORTHward.");

    /* Create example rooms */
    room_t* start_room = room_new("Start Room", "", "A deadly dragon awaits! "
                                  "See how you can use the new effects system to create a skill"
                                  "that lets you kill it!");
    room_t* design_room = room_new("Skill Design Room", "", "Make an effect that can kill a dragon!  Good Luck!");
    room_t* level_up_room = room_new("Level Up Room", "", "Level Up to Level 5 to unlock your created skill !");
    room_t* kill_room = room_new("Dragon's Lair", "", "Kill the dragon!");

    /* Add example rooms to example game */
    add_room_to_game(game, start_room);
    add_room_to_game(game, design_room);
    add_room_to_game(game, level_up_room);
    add_room_to_game(game, kill_room);

    /* Set initial room */
    game->curr_room = start_room;

    /* Set player */
    player_t *player = player_new("demo_player");
    stats_global_t *gs_health = stats_global_new("max_health", 100);
    stats_t* gs_health_stat = stats_new(gs_health, 100);
    stats_global_t *player_health = stats_global_new("current_health", 50);
    stats_t* player_health_stat = stats_new(player_health, 50);
    class_t* test_class = class_new("TEST", "", "", NULL, NULL, NULL);
    test_class->skilltree = skill_tree_new(1001, "TEST Tree", 2);
    player->player_class = test_class;
    player->inventory = inventory_new(5,5);
    add_player_to_game(game, player);
    set_curr_player(game, player);

    /* Adding to hash table */
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_health->name, strlen(gs_health->name), gs_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, gs_health_stat->key, strlen(gs_health_stat->key), gs_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_health->name, strlen(player_health->name), player_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_health_stat->key, strlen(player_health_stat->key), player_health_stat);
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id, strlen(player->player_id), player);

    /* Create example chiventure context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

item_t* add_item(chiventure_ctx_t* ctx)
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

void create_player_skill(chiventure_ctx_t* ctx)
{
    /*Creating an effect with a hardcoded value of 100 */
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {100, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    effect_t* stat_effect = make_player_stat_effect(health_boost);
    
    /* Making a skill */
    skill_t* stat_skill = skill_new(0, PASSIVE, "Stat Skill", "Modifies statistics", 10, 5, stat_effect);
    
    /* Showcase leveling functionality */
    skill_node_t* stat_node = skill_node_new(stat_skill, 0, 19, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

char* player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_player_skill(ctx);
   
    
    return "Created a statistic modifying effect!";
}

int add_player_stat_skill(chiventure_ctx_t* ctx)
{
    player_t* player = ctx->game->curr_player;
    skill_node_t* skill_node = player->player_class->skilltree->nodes[0];
    if(player->level<skill_node->prereq_level)
    {
        print_to_cli(ctx, "Level too low!");
        return FAILURE;
    }
    /* Add to inventory */
    inventory_skill_add(ctx->game->curr_player->player_skills, skill_node -> skill);

    /* Execute the effect as it is passive */
    skill_execute(skill_node->skill, ctx);
    return SUCCESS;
}

char* add_player_stat_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = add_player_stat_skill(ctx);
    if(check == FAILURE)
    {
        return "Could not add skill!"
    }
    else
    {
        return "Added skill!"
    }
}

char* design_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    print_to_cli(ctx, "Enter the type of effect you want to add!");
    print_to_cli(ctx, "Options are:  Statistic Modify and Attribute Modify");
    return "Design Operation!";
}

/*
 * Prints all skills contained in a skill inventory to the CLI
 *
 * Parameters:
 *  - ctx: A chiventure context
 *
 * Returns:
 *  - None
 */
void current_skills_as_strings(chiventure_ctx_t* ctx){
    assert(ctx != NULL);

    unsigned int i;
    char description[60];

    skill_inventory_t* inventory = ctx->game->curr_player->player_skills;
    print_to_cli(ctx, "-");
    print_to_cli(ctx, "Active Skills:");
    if (!(inventory->num_active)){
        print_to_cli(ctx, "You have no active skills.");
    } else {
        for (i = 0; i < inventory->num_active; i++) {
            sprintf(description, "%s: Level %u", inventory->active[i]->name,
                    inventory->active[i]->level);
            print_to_cli(ctx, description);
        }
    }

    print_to_cli(ctx, "-");
    print_to_cli(ctx, "Passive Skills:");
    if (!inventory->num_passive) {
        print_to_cli(ctx, "You have no passive skills.");
    } else {
        for (i = 0; i < inventory->num_passive; i++) {
            sprintf(description, "%s: Level %u", inventory->passive[i]->name,
                    inventory->passive[i]->level);
            print_to_cli(ctx, description);
        }
    }
}

/*
 * Manifests using the SKILLS operation to the CLI, calling
 * current_skills_as_strings() to list all skills in an inventory to the CLI
 *
 * Parameters:
 *  - tokens: Array of parsed input tokens
 *  - ctx: A chiventure context
 *
 * Returns:
 *  - An empty string (current_skills_as_strings() prints all that is necessary)
 */
char* skills_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    current_skills_as_strings(ctx);
    return "";
}

void main(){
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();
   
    item_t* dragon = add_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;
    item_attr_effect_t* slay_dragon = define_item_attr_effect(dragon, "ARMED", att_tag, mod);
    effect_t* attribute_effect = make_item_attr_effect(slay_dragon);
    skill_t*  attribute_skill = skill_new(1, ACTIVE, "Attribute Skill", "Slays Dragon", 10, 10, attribute_effect);


    //Initialize skill nodes
    
    skill_node_t* attribute_node = skill_node_new(attribute_skill, 0, 14, 0); 



   
    skill_tree_node_add(skill_treedemo, attribute_node);

    printf("Stat Node added into our skill tree, you must be level %d to unlock this stat skill", 
            skill_treedemo->nodes[0]->prereq_level);
    printf("Attribute_node added as a prerequisite to Stat Node, you must be level %d to unlock attribute skill",
            skill_treedemo->nodes[1]->prereq_level);

    player_t* player = ctx->game->curr_player;
    printf("Your current level is %d \n", get_level(player));


    // Initialize skill inventory

        change_xp(player, 50);
    /* Enter the "stat skill room" and level up. Player can now unlock and execute new statistic modifying skill
     * leveling up in the stat skill room done using following function:
     */
        change_level(player, 14);

    /* Enter the "attribute skill room" and level up. Player cna now unlock and execute new attribute modifying skill.
     * leveling up in the "attribute skill room" done using following function:
     */
        change_level(player, 19);


    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free memory

    return 0;
}
