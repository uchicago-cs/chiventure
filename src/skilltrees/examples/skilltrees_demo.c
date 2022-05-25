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
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    /* Create example rooms */
    room_t* start_room = room_new("Start Room", "", "A deadly dragon awaits! "
                                  "See how you can use the new effects system to create a skill"
                                  "that lets you kill it!");
    room_t* design_room = room_new("Skill Design Room", "", "Make an effect that can kill a dragon!  Good Luck!");
    room_t* level_up_room = room_new("Level Up Room", "", "Level Up to Level 2 to unlock and add your created skills !");
    room_t* kill_room = room_new("Dragon's Lair", "", "Kill the dragon!");
    room_t* win_room = room_new("Win Room","", "You Win !");

    /* Add example rooms to example game */
    add_room_to_game(game, start_room);
    add_room_to_game(game, design_room);
    add_room_to_game(game, level_up_room);
    add_room_to_game(game, kill_room);
    add_room_to_game(game, win_room);

    create_connection(game, "Start Room", "Skill Design Room", "NORTH");
    create_connection(game, "Skill Design Room", "Start Room", "SOUTH");
    create_connection(game, "Skill Design Room", "Level Up Room", "NORTH");
    create_connection(game, "Level Up Room", "Skill Design Room", "SOUTH");
    create_connection(game, "Level Up Room", "Dragon's Lair", "NORTH");
    create_connection(game, "Dragon's Lair", "Level Up Room", "South");

    /* Set initial room */
    game->curr_room = start_room;

    /* Set player */
    player_t *player = player_new("demo_player");
    stats_global_t *gs_health = stats_global_new("max_health", 100);
    stats_t* gs_health_stat = stats_new(gs_health, 100);
    stats_global_t *player_health = stats_global_new("current_health", 50);
    stats_t* player_health_stat = stats_new(player_health, 50);
   
    /* Adding to hash table */
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_health->name, strlen(gs_health->name), gs_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, gs_health_stat->key, strlen(gs_health_stat->key), gs_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_health->name, strlen(player_health->name), player_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_health_stat->key, strlen(player_health_stat->key), player_health_stat);
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
    HASH_FIND_STR(game->curr_stats, "max_health", stat_test);
    if (stat_test->max != 100) 
    {
        printf("ERROR");
    }
    stats_t*  player_test;
    HASH_FIND_STR(game->curr_player->player_stats, "current_health", player_test);
    if (player_test->val != 50) 
    {
        printf("ERROR 2");
    }
    /* Create example chiventure context */
    return ctx;
}

void add_item(chiventure_ctx_t* ctx)
{
    /* Creating item and attribute */
    game_t* game = ctx -> game;
    game->all_items = NULL;
    item_t* dragon = item_new("DRAGON", "A scary dragon", "Is very hungry");
    attribute_t* is_alive = bool_attr_new("ALIVE", true);
    
    /* Adding things to hash tables */
    add_attribute_to_hash(dragon, is_alive);
    add_item_to_hash(&(game->all_items), dragon);

    /* Add dragon to room */
    room_t* room;
    HASH_FIND_STR(ctx->game->all_rooms, "dragon's lair", room);
    add_item_to_room(room, dragon);
}

void create_player_skill(chiventure_ctx_t* ctx)
{
    /*Creating an effect with a hardcoded value of 100 */
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {100, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    if (health_boost == NULL) {
        print_to_cli(ctx, "NULL EFFECT");
    }
    effect_t* stat_effect = make_player_stat_effect(health_boost);
    /* Making a skill */
    skill_t* stat_skill = skill_new(0, PASSIVE, "Stat Skill", "Modifies statistics", 10, 5, stat_effect, NULL);
    
    /* Showcase leveling functionality */
    skill_node_t* stat_node = skill_node_new(stat_skill, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

char* create_player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_player_skill(ctx);
    return "Created a statistic modifying effect!";
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
    
    /* Check the level */
    if (player->level<skill_node->prereq_level) 
    {
        print_to_cli(ctx, "Level too low!");
        return FAILURE;
    }

    /* Add to inventory */
    inventory_skill_add(ctx->game->curr_player->player_skills, skill_node -> skill);
    
     return SUCCESS;
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

char* add_player_stat_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = add_skill_to_player(ctx, 0);
    if (check == FAILURE) 
    {
        return "Could not add skill!";
    }
    else 
    {
        execute_skill(ctx, 0);
        return "Added skill!";
    }
}

void create_attr_skill(chiventure_ctx_t* ctx)
{
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;
    item_t* dragon = get_item_in_hash(ctx->game->all_items, "dragon");
    if (dragon == NULL)
    {
        print_to_cli(ctx, "NO DRAGON");
    }
    item_attr_effect_t* slay_dragon = define_item_attr_effect(dragon, "ALIVE", att_tag, mod);
    effect_t* attribute_effect = make_item_attr_effect(slay_dragon);
    skill_t*  attribute_skill = skill_new(1, ACTIVE, "Attribute Skill", "Slays Dragon", 10, 10, attribute_effect, NULL);
    
    /* Showcase leveling functionality */
    skill_node_t* attr_node = skill_node_new(attribute_skill, 0, 3, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, attr_node);
}

char* create_attr_skill_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_attr_skill(ctx);
    return "Created Attribute modifying skill!";
}

char* add_attr_skill_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = add_skill_to_player(ctx, 1);
    if (check == FAILURE)
    {
        return "Could not add skill!";
    }
    else
    {
        return "Added skill!";
    }
}

char* execute_attr_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = execute_skill(ctx, 1);
    item_t* dragon = get_item_in_hash(ctx->game->all_items, "dragon");
    if(dragon == NULL)
    {
        fprintf(stderr, "NO DRAGON");
    }
    bool is_alive = dragon->attributes->attribute_value.bool_val;
    if (is_alive == true)
    {
        check = FAILURE;
    }
    
    if (check == SUCCESS)
    {
        create_connection(ctx->game, "Dragon's Lair", "Win Room", "NORTH");
        return "Killed Dragon!  Go to next room to celebrate";
    }
    else
    {
        return "Oh no....";
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
    add_item(ctx);

    add_entry("DESIGN", design_operation, NULL, ctx->cli_ctx->table);
    add_entry("SKILLS", skills_operation, NULL, ctx->cli_ctx->table);
    add_entry("STATISTIC", create_player_stat_effect_operation, NULL, ctx->cli_ctx->table);
    add_entry("ATTRIBUTE", create_attr_skill_operation, NULL, ctx->cli_ctx->table);
    add_entry("ADD", add_operation, NULL, ctx->cli_ctx->table);
    add_entry("ADD_HEALTH_BOOST", add_player_stat_operation, NULL, ctx->cli_ctx->table);
    add_entry("ADD_SLAY_DRAGON", add_attr_skill_operation, NULL, ctx->cli_ctx->table);
    add_entry("LEVEL_UP", level_up_operation, NULL, ctx->cli_ctx->table);
    add_entry("KILL_DRAGON", execute_attr_operation, NULL, ctx->cli_ctx->table);
    //Start UI for example chiventure context
    start_ui(ctx, banner);
}
