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
#include "skilltrees/complex_skills.h"

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
    game_t* game = game_new("This is the 2022 demo "
                            "Room progression is always (GO) NORTHward.");
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    /* Create example rooms */
    room_t* start_room = room_new("Start Room", "", "Your skills have gotten stronger and more complex thanks to my training");
    room_t* combined_room = room_new("Combined Skill Room", "", "Now your skills should have more of a kick!");

    /* Add example rooms to example game */
    add_room_to_game(game, start_room);
    add_room_to_game(game, combined_room);

    create_connection(game, "Start Room", "Combined Skill Room", "NORTH");
    create_connection(game, "Combined Skill Room", "Start Room", "SOUTH");


    /* Set initial room */
    game->curr_room = start_room;

    /* Set player */
    player_t *player = player_new("demo_player");
    stats_global_t *gs_health = stats_global_new("max_health", 100);
    stats_t* gs_health_stat = stats_new(gs_health, 100);
    stats_global_t *player_health = stats_global_new("current_health", 50);
    stats_t* player_health_stat = stats_new(player_health, 50);
    stats_global_t *player_strength = stats_global_new("strength", 50);
    stats_t* player_strength_stat = stats_new(player_strength, 50);
    stats_global_t *player_defense= stats_global_new("defense", 50);
    stats_t* player_defense_stat = stats_new(player_defense, 50);
   
    /* Adding to hash table */
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_health->name, strlen(gs_health->name), gs_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, gs_health_stat->key, strlen(gs_health_stat->key), gs_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_health->name, strlen(player_health->name), player_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_health_stat->key, strlen(player_health_stat->key), player_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_strength->name, strlen(player_strength->name), player_strength);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_strength_stat->key, strlen(player_strength_stat->key), player_strength_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_defense->name, strlen(player_defense->name), player_defense);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_defense_stat->key, strlen(player_defense_stat->key), player_defense_stat);
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id, strlen(player->player_id), player);

    /*Initializing class */
    class_t* test_class = class_new("TEST", "", "", NULL, NULL, NULL);
    test_class->skilltree = skill_tree_new(1001, "TEST Tree", 2);
    player->level = 1;
    player->player_class = test_class;
    player->player_skills = inventory_new(5,5);
    player -> player_effects = (effects_hash_t*)malloc(sizeof(effects_hash_t));
    add_player_to_game(game, player);
    set_curr_player(game, player);

    /* Checking if everything works */
    stats_global_t* stat_test;
    HASH_FIND_STR(game->curr_stats, "defense", stat_test);
    if (stat_test->max != 100) 
    {
        printf("ERROR");
    }
    stats_t*  player_test;
    HASH_FIND_STR(game->curr_player->player_stats, "defense", player_test);
    if (player_test->val != 50) 
    {
        printf("ERROR 2");
    }
    /* Create example chiventure context */
    return ctx;
}

int execute_skill(chiventure_ctx_t* ctx, int sid)
{
    player_t* player = ctx->game->curr_player;
    skill_node_t* skill_node = player->player_class->skilltree->nodes[0];
    skill_t* skill = skill_node->skill;
    
    /*Find the correct skill */
    int i = 1;
    while ((skill->sid != sid)&&(i<=1)) 
    {
        skill_node = player->player_class->skilltree->nodes[i];
        skill = skill_node->skill;
    }
    if(skill->sid != sid) 
    {
        return FAILURE;
    }
    /* Execute the effect */
    skill_execute(skill_node->skill, ctx);
    return SUCCESS;
}

//Combined skill functions
void create_combined_skill(chiventure_ctx_t* ctx)
{
    /*Skill will buff multiple stats of the player*/

    /*Health buff */
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {100, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    if (health_boost == NULL) {
        print_to_cli(ctx, "HEALTH NULL EFFECT");
    }
    effect_t* stat_effect0 = make_player_stat_effect(health_boost);
    /* Making a skill */
    skill_t* stat_skill0 = skill_new(0, PASSIVE, "Stat Skill", "Modifies health", 10, 5, stat_effect0, NULL);

    /*Strength buff*/
    char* stats_to_change1[] = {"strength"};
    double mods1[] = {100, 100};
    int durations1[] = {5, 5};
    player_stat_effect_t* strength_boost = define_player_stat_effect("strength boost", stats_to_change1, mods1, durations1, 1, ctx);
    if (strength_boost == NULL) {
        print_to_cli(ctx, "STRENGTH NULL EFFECT");
    }
    effect_t* stat_effect1 = make_player_stat_effect(strength_boost);
    /* Making a skill */
    skill_t* stat_skill1 = skill_new(0, PASSIVE, "Stat Skill", "Modifies strength", 10, 5, stat_effect1, NULL);

    /*Defense buff*/
    char* stats_to_change2[] = {"defense"};
    double mods2[] = {100, 100};
    int durations2[] = {5, 5};
    player_stat_effect_t* defense_boost = define_player_stat_effect("defense boost", stats_to_change2, mods2, durations2, 1, ctx);
    if (defense_boost == NULL) {
        print_to_cli(ctx, "DEFENSE NULL EFFECT");
    }
    effect_t* stat_effect2 = make_player_stat_effect(defense_boost);
    /* Making a skill */
    skill_t* stat_skill2 = skill_new(0, PASSIVE, "Stat Skill", "Modifies defense", 10, 5, stat_effect2, NULL);

    skill_t** skills = (skill_t**) malloc(sizeof(skill_t*)*3);
    skills[0] = stat_skill0;
    skills[1] = stat_skill1;
    skills[2] = stat_skill2;

    complex_skill_t* complex_stat_skill = complex_skill_new(COMBINED, skills, 3, NULL);
    skill_t* stat_skill3 = skill_new(0, PASSIVE, "Complex Stat Skill", "Modifies several statistics", 10, 5, NULL, complex_stat_skill);
    
    /* Showcase leveling functionality */
    skill_node_t* stat_node = skill_node_new(stat_skill3, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

char* create_combined_player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_combined_skill(ctx);
    return "Created a combined skill!";
}

int add_skill_to_player(chiventure_ctx_t* ctx, int sid)
{
    player_t* player = ctx->game->curr_player;
    skill_node_t* skill_node = player->player_class->skilltree->nodes[0];
    if (skill_node == NULL) 
    {
        print_to_cli(ctx, "Skills not made yet !");
        return FAILURE;
    }
    skill_t* skill = skill_node->skill;
    
    /*Find the correct skill */
    int i = 1;
    while ((skill->sid != sid)&&(i<=1)) 
    {
        skill_node = player->player_class->skilltree->nodes[i];
        i +=1;
        skill = skill_node->skill;
    }

    /* Add to inventory */
    inventory_skill_add(ctx->game->curr_player->player_skills, skill_node -> skill);
    
     return SUCCESS;
}

char* add_combined_player_stat_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = add_skill_to_player(ctx, 0);
    if (check == FAILURE) 
    {
        return "Could not add skill!";
    }
    else 
    {
        execute_skill(ctx, 0);
        print_to_cli(ctx, "Added skill!");
        print_to_cli(ctx, "Health is boosted!");
        print_to_cli(ctx, "Strength is boosted!");
        print_to_cli(ctx, "Defense is boosted!");
        return "";
    }
}

//Sequential skill functions
void create_sequential_skill(chiventure_ctx_t* ctx)
{
    // /*Skill will buff multiple stats of the player*/

    // /*Health buff */
    // char* stats_to_change[] = {"max_health", "current_health"};
    // double mods[] = {100, 100};
    // int durations[] = {5, 5};
    // player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    // if (health_boost == NULL) {
    //     print_to_cli(ctx, "HEALTH NULL EFFECT");
    // }
    // effect_t* stat_effect0 = make_player_stat_effect(health_boost);
    // /* Making a skill */
    // skill_t* stat_skill0 = skill_new(0, PASSIVE, "Stat Skill", "Modifies health", 10, 5, stat_effect0, NULL);

    // /*Strength buff*/
    // char* stats_to_change1[] = {"strength"};
    // double mods1[] = {100, 100};
    // int durations1[] = {5, 5};
    // player_stat_effect_t* strength_boost = define_player_stat_effect("strength boost", stats_to_change1, mods1, durations1, 1, ctx);
    // if (strength_boost == NULL) {
    //     print_to_cli(ctx, "STRENGTH NULL EFFECT");
    // }
    // effect_t* stat_effect1 = make_player_stat_effect(strength_boost);
    // /* Making a skill */
    // skill_t* stat_skill1 = skill_new(0, PASSIVE, "Stat Skill", "Modifies strength", 10, 5, stat_effect1, NULL);

    // /*Defense buff*/
    // char* stats_to_change2[] = {"defense"};
    // double mods2[] = {100, 100};
    // int durations2[] = {5, 5};
    // player_stat_effect_t* defense_boost = define_player_stat_effect("defense boost", stats_to_change2, mods2, durations2, 1, ctx);
    // if (defense_boost == NULL) {
    //     print_to_cli(ctx, "DEFENSE NULL EFFECT");
    // }
    // effect_t* stat_effect2 = make_player_stat_effect(defense_boost);
    // /* Making a skill */
    // skill_t* stat_skill2 = skill_new(0, PASSIVE, "Stat Skill", "Modifies defense", 10, 5, stat_effect2, NULL);

    // skill_t** skills = (skill_t**) malloc(sizeof(skill_t*)*3);
    // skills[0] = stat_skill0;
    // skills[1] = stat_skill1;
    // skills[2] = stat_skill2;

    // complex_skill_t* complex_stat_skill = complex_skill_new(COMBINED, skills, 3, NULL);
    // skill_t* stat_skill3 = skill_new(1, PASSIVE, "Complex Stat Skill", "Modifies several statistics", 10, 5, NULL, complex_stat_skill);
    
    // /* Showcase leveling functionality */
    // skill_node_t* stat_node = skill_node_new(stat_skill3, 0, 2, 0); 
    // skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

char* create_sequential_player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_sequential_skill(ctx);
    return "Created a squential skill!";
}

char* add_sequential_player_stat_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = add_skill_to_player(ctx, 1);
    if (check == FAILURE) 
    {
        return "Could not add skill!";
    }
    else 
    {
        execute_skill(ctx, 1);
        return "";
    }
}

//Conditonal Skill code
void create_conditional_skill(chiventure_ctx_t* ctx)
{
    // /*Skill will buff multiple stats of the player*/

    // /*Health buff */
    // char* stats_to_change[] = {"max_health", "current_health"};
    // double mods[] = {100, 100};
    // int durations[] = {5, 5};
    // player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    // if (health_boost == NULL) {
    //     print_to_cli(ctx, "HEALTH NULL EFFECT");
    // }
    // effect_t* stat_effect0 = make_player_stat_effect(health_boost);
    // /* Making a skill */
    // skill_t* stat_skill0 = skill_new(0, PASSIVE, "Stat Skill", "Modifies health", 10, 5, stat_effect0, NULL);

    // /*Strength buff*/
    // char* stats_to_change1[] = {"strength"};
    // double mods1[] = {100, 100};
    // int durations1[] = {5, 5};
    // player_stat_effect_t* strength_boost = define_player_stat_effect("strength boost", stats_to_change1, mods1, durations1, 1, ctx);
    // if (strength_boost == NULL) {
    //     print_to_cli(ctx, "STRENGTH NULL EFFECT");
    // }
    // effect_t* stat_effect1 = make_player_stat_effect(strength_boost);
    // /* Making a skill */
    // skill_t* stat_skill1 = skill_new(0, PASSIVE, "Stat Skill", "Modifies strength", 10, 5, stat_effect1, NULL);

    // /*Defense buff*/
    // char* stats_to_change2[] = {"defense"};
    // double mods2[] = {100, 100};
    // int durations2[] = {5, 5};
    // player_stat_effect_t* defense_boost = define_player_stat_effect("defense boost", stats_to_change2, mods2, durations2, 1, ctx);
    // if (defense_boost == NULL) {
    //     print_to_cli(ctx, "DEFENSE NULL EFFECT");
    // }
    // effect_t* stat_effect2 = make_player_stat_effect(defense_boost);
    // /* Making a skill */
    // skill_t* stat_skill2 = skill_new(0, PASSIVE, "Stat Skill", "Modifies defense", 10, 5, stat_effect2, NULL);

    // skill_t** skills = (skill_t**) malloc(sizeof(skill_t*)*3);
    // skills[0] = stat_skill0;
    // skills[1] = stat_skill1;
    // skills[2] = stat_skill2;

    // complex_skill_t* complex_stat_skill = complex_skill_new(COMBINED, skills, 3, NULL);
    // skill_t* stat_skill3 = skill_new(2, PASSIVE, "Complex Stat Skill", "Modifies several statistics", 10, 5, NULL, complex_stat_skill);
    
    // /* Showcase leveling functionality */
    // skill_node_t* stat_node = skill_node_new(stat_skill3, 0, 2, 0); 
    // skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

char* create_conditional_player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_conditional_skill(ctx);
    return "Created a squential skill!";
}

char* add_conditional_player_stat_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = add_skill_to_player(ctx, 2);
    if (check == FAILURE) 
    {
        return "Could not add skill!";
    }
    else 
    {
        execute_skill(ctx, 1);
        return "";
    }
}

char* level_up_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    ctx->game->curr_player->level+=1;
    return "Leveled Up!";
}

char* design_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    print_to_cli(ctx, "Enter the type of effect you want to design!");
    print_to_cli(ctx, "Options are:  Statistic Modify and Attribute Modify");
    return "";
}

char* add_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    print_to_cli(ctx, "Enter the type of skill you want to add to your inventory!");
    print_to_cli(ctx, "Options are: Add Health Boost and Add Slay Dragon");
    return "";
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
void current_skills_as_strings(chiventure_ctx_t* ctx) 
{
    assert(ctx != NULL);

    unsigned int i;
    char description[60];

    skill_inventory_t* inventory = ctx->game->curr_player->player_skills;
    print_to_cli(ctx, "-");
    print_to_cli(ctx, "Active Skills:");
    if (!(inventory->num_active))
    {
        print_to_cli(ctx, "You have no active skills.");
    } 
    else 
    {
        for (i = 0; i < inventory->num_active; i++) 
        {
            sprintf(description, "%s: Level %u", inventory->active[i]->name,
                    inventory->active[i]->level);
            print_to_cli(ctx, description);
        }
    }

    print_to_cli(ctx, "-");
    print_to_cli(ctx, "Passive Skills:");
    if (!inventory->num_passive) 
    {
        print_to_cli(ctx, "You have no passive skills.");
    } 
    else 
    {
        for (i = 0; i < inventory->num_passive; i++) 
        {
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
char* skills_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) 
{
    current_skills_as_strings(ctx);
    return "";
}

void main()
{
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    add_entry("DESIGN", design_operation, NULL, ctx->cli_ctx->table);
    add_entry("SKILLS", skills_operation, NULL, ctx->cli_ctx->table);
    add_entry("CREATE_COMBINED", create_combined_player_stat_effect_operation, NULL, ctx->cli_ctx->table);
    add_entry("ADD_COMBINED_BOOST", add_combined_player_stat_operation, NULL, ctx->cli_ctx->table);
    //Start UI for example chiventure context
    start_ui(ctx, banner);
}
