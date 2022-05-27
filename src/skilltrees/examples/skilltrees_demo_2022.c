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
#include "skilltrees/reader.h"
#include "skilltrees/complex_skills.h"
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
    game_t* game = game_new("You sit at the entrance to Skills Academy. You have arrived in order to "
                            "improve your skills, as you are pretty lacking. "
                            "Room progression is always (GO) NORTHward.");
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    /* Create example rooms */
    room_t* start_room = room_new("Start Room", "", "Once you get past this door, you will meet "
                                                    "your new mentor!");

    room_t* combined_room = room_new("Combined Skill Room", "", "You see your new mentor, in the middle of a large hallway.");

    room_t* sequential_room = room_new("Sequential Skill Room", "", "You enter a room with a training dummy.\nYour mentor begins to train "
                                                                    "you a powerful combo move, one that stuns your opponent,\n then summons "
                                                                    "a mighty tornado!");

    room_t* conditional_room = room_new("Conditional Skill Room", "", "Your mentor brings the dummy into the next room for some reason.\nHe begins rambling " 
                                                                        "something about how orcs are good at smashing things. ");

    room_t* classes_room = room_new("Classes Room", "", "You enter a large library, filled wall to wall with books.");

    room_t* final_room = room_new("Reader Room", "", "You and your mentor go into the next room, and you sense his anger. He's enraged you destroyed his dummy! "
                                                      "How were you supposed to know it was a family heirloom?! He attacks!\n"
                                                      "You remember how you had to check if you were an orc to smash things... can you read his weakness?");

    /* Add example rooms to example game */
    add_room_to_game(game, start_room);
    add_room_to_game(game, combined_room);
    add_room_to_game(game, sequential_room);
    add_room_to_game(game, conditional_room);
    add_room_to_game(game, classes_room);
    add_room_to_game(game, final_room);



    create_connection(game, "Start Room", "Combined Skill Room", "NORTH");
    create_connection(game, "Combined Skill Room", "Start Room", "SOUTH");
    create_connection(game, "Combined Skill Room", "Sequential Skill Room", "NORTH");
    create_connection(game, "Sequential Skill Room", "Combined Skill Room", "SOUTH");
    create_connection(game, "Sequential Skill Room", "Conditional Skill Room", "NORTH");
    create_connection(game, "Conditional Skill Room", "Sequential Skill Room", "SOUTH");
    create_connection(game, "Conditional Skill Room", "Classes Room", "NORTH");
    create_connection(game, "Classes Room", "Conditional Skill Room", "SOUTH");
    create_connection(game, "Classes Room", "Reader Room", "NORTH");
    create_connection(game, "Reader Room", "Classes Room", "SOUTH");


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
    class_t* test_class = class_new("NOTHING YET", "", "", NULL, NULL, NULL);
    test_class->skilltree = skill_tree_new(1001, "TEST Tree", 3);
    player->level = 1;
    player->player_class = test_class;
    player->player_skills = inventory_new(5,5);
    player -> player_effects = (effects_hash_t*)malloc(sizeof(effects_hash_t));
    add_player_to_game(game, player);
    set_curr_player(game, player);

    //Dummy Battle code for reading classes
    class_t* class_p = class_new("NOTHING YET", "", "", NULL, NULL, NULL);
    
    class_t* class_v = class_new("Vampire", "", "", NULL, NULL, NULL);

    combatant_t* p = combatant_new("TEST", true, class_p,
            NULL, NULL, NULL, NULL, NULL, NULL, 0);

    //Mentor is a vampire, spoiler alert.
    combatant_t* m = combatant_new("Mentor", true, class_v,
            NULL, NULL, NULL, NULL, NULL, NULL, 0);

    battle_t* battle = battle_new(p, m, 0, 0);

    battle_game_t* battle_game = new_battle_game();
    battle_game->battle = battle;

    battle_ctx_t* battle_ctx = (battle_ctx_t*)malloc(sizeof(battle_ctx_t));
    battle_ctx->game = battle_game;

    game->battle_ctx = battle_ctx;

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

/****************************************************************************************************************/
/*SKILL CODE*/
/****************************************************************************************************************/

int execute_skill(chiventure_ctx_t* ctx, int sid)
{
    player_t* player = ctx->game->curr_player;
    skill_node_t* skill_node = player->player_class->skilltree->nodes[0];
    skill_t* skill = skill_node->skill;
    
    /*Find the correct skill */
    int i = 1;
    while ((skill->sid != sid)&&(i<=2)) 
    {
        skill_node = player->player_class->skilltree->nodes[i];
        i += 1;
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
    skill_t* stat_skill3 = skill_new(0, PASSIVE, "Combined Stat Skill", "Modifies several statistics", 10, 5, NULL, complex_stat_skill);
    
    skill_node_t* stat_node = skill_node_new(stat_skill3, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);
}

char* create_combined_player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_combined_skill(ctx);
    return "Learned a combined skill!";
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
    while ((skill->sid != sid)&&(i<=2)) 
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
        print_to_cli(ctx, "Learned the combined boost skill!");
        print_to_cli(ctx, "You feel your health is boosted!");
        print_to_cli(ctx, "You feel your strength is boosted!");
        print_to_cli(ctx, "You feel your defense is boosted!");
        print_to_cli(ctx, "Mentor: Wow! You look jacked now. Before, you would have to boost each of your stats individually. "
        "But there is still much for you to learn!");
        return "";
    }
}

//Sequential skill functions
void create_sequential_skill(chiventure_ctx_t* ctx)
{
    /*Skill will consist of 2 moves*/

    skill_t* skill_0 = skill_new(1, ACTIVE, "stun", 
                                     "You stun your opponent.", 1, 100, 
                                     NULL, NULL);
    skill_t* skill_1 = skill_new(1, ACTIVE, "tornado", 
                                     "You set a tornado to your opponent", 1, 
                                     150, NULL, NULL);


    skill_t** skills = (skill_t**) malloc(sizeof(skill_t*)*2);
    skills[0] = skill_0;
    skills[1] = skill_1;

    complex_skill_t* complex_stat_skill = complex_skill_new(SEQUENTIAL, skills, 3, NULL);
    skill_t* sequential_skill = skill_new(1, PASSIVE, "Sequential Moves Skill", "Tries to stun and use tornado on opponent", 10, 5, NULL, complex_stat_skill);
    
    skill_node_t* node = skill_node_new(sequential_skill, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, node);
}

char* create_sequential_player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_sequential_skill(ctx);
    return "Learn a sequential skill!";
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
        print_to_cli(ctx, "Learned the sequential combo skill!");
        print_to_cli(ctx, "You attempt to stun the training dummy...");
        print_to_cli(ctx, "And you completely fail.");
        print_to_cli(ctx, "Mentor: What did you expect! You can't stun a dummy.");
        print_to_cli(ctx, "Mentor: And I wasn't going to let you summon a tornado indoors!");
        return "";
    }
}

//Conditonal Skill code
void create_conditional_skill(chiventure_ctx_t* ctx)
{
    /*Skill will check if player is an orc*/

    skill_t* skill_0 = skill_new(1, ACTIVE, "Orc Smash", 
                                     "You smash your opponent with all your might!", 1, 100, 
                                     NULL, NULL);
    skill_t* skill_1 = skill_new(1, ACTIVE, "Pathetic Slap", 
                                     "Even with your strength boost, the dummy remains.", 1, 
                                     150, NULL, NULL);

    skill_t** skills = (skill_t**) malloc(sizeof(skill_t*)*3);
    skills[0] = skill_0;
    skills[1] = skill_1;

    //Creation of Reader that checks if player is an orc.
    attr_reader_effect_t* attr_reader = attr_reader_effect_new("Orc", 3, READ_PLAYER);

    reader_effect_t* orc_reader = reader_effect_new(READER_ATTRIBUTE, attr_reader, NULL);

    complex_skill_t* complex_stat_skill = complex_skill_new(COMPLEX_CONDITIONAL, skills, 3, orc_reader);
    skill_t* stat_skill3 = skill_new(2, PASSIVE, "Conditional Skill", "Different smashes depending if you're an orc or not", 10, 5, NULL, complex_stat_skill);
    
    /* Showcase leveling functionality */
    skill_node_t* stat_node = skill_node_new(stat_skill3, 0, 2, 0); 
    skill_tree_node_add(ctx->game->curr_player->player_class->skilltree, stat_node);

    add_skill_to_player(ctx, 2);
}

char* create_conditional_player_stat_effect_operation(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    create_conditional_skill(ctx);
    return "Learned a conditional skill!";
}

int execute_conditional_skill(chiventure_ctx_t* ctx, int sid)
{
    player_t* player = ctx->game->curr_player;
    skill_node_t* skill_node = player->player_class->skilltree->nodes[0];
    skill_t* skill = skill_node->skill;
    
    /*Find the correct skill */
    int i = 1;
    while ((skill->sid != sid)&&(i<=2)) 
    {
        skill_node = player->player_class->skilltree->nodes[i];
        i += 1;
        skill = skill_node->skill;
    }
    if(skill->sid != sid) 
    {
        return FAILURE;
    }
    /* Execute the effect */
    int check = execute_reader_effect(skill->complex->reader, ctx);


    if(check == 1){
        //Text when user smashes dummy
        print_to_cli(ctx, "You smash the dummy to pieces. Your honor is restored. ");
        print_to_cli(ctx, "Mentor: ... Your tuition has just doubled. ");

    } else if (check == 0){
        //Text when user fails to smash dummy
        print_to_cli(ctx, "You smash the dummy, but you're not an orc. Even with your strength boost, "
                            "it remains, taunting you.");
        print_to_cli(ctx, "Mentor: I'm not sure why you wanted to learn that, only orcs are powerful enough "
                            "to learn this legendary technique. ");

    } else if (check == -1){
        print_to_cli(ctx, "READER ERROR: ORC NOT FOUND");
    }


    skill_execute(skill_node->skill, ctx);
    return SUCCESS;
}

char* use_conditional_skill(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = execute_conditional_skill(ctx, 2);
    return "";
}

// fix to smash window
int execute_conditional_window_skill(chiventure_ctx_t* ctx, int sid)
{
    player_t* player = ctx->game->curr_player;
    skill_node_t* skill_node = player->player_class->skilltree->nodes[0];
    skill_t* skill = skill_node->skill;
    
    /*Find the correct skill */
    int i = 1;
    while ((skill->sid != sid)&&(i<=2)) 
    {
        skill_node = player->player_class->skilltree->nodes[i];
        i += 1;
        skill = skill_node->skill;
    }
    if(skill->sid != sid) 
    {   
        return FAILURE;
    }
    /* Execute the effect */
    int check = execute_reader_effect(skill->complex->reader, ctx);

    if(check == 1){
        //Text when user smashes window
        print_to_cli(ctx, "You move the drapes aside and smash the windows, allowing sunlight to permeate the room");
        print_to_cli(ctx, "Your mentor screams in agony, disintegrating into fine particles of dust");
        print_to_cli(ctx, "Mentor: Oh no! I forgot you can do that! AAAAAAAAAAAAAA");
        print_to_cli(ctx, "Mentor: Go forth and conquer with your new skills.");
        print_to_cli(ctx, "Victory! You won! And you don't even have to pay tuition anymore!");

    } else if (check == 0){
        //Text when user fails to smash window
        print_to_cli(ctx, "You attempt to smash the windows, but you're not an orc. Even with your current skills, "
                            "they remain whole.");
        print_to_cli(ctx, "Mentor: You could never beat me, when you're not an "
                          "orc you're not even strong enough to break a window. ");

    } else if (check == -1){
        print_to_cli(ctx, "READER ERROR: ORC NOT FOUND");
    }


    skill_execute(skill_node->skill, ctx);
    return SUCCESS;
}

char* use_conditional_window_skill(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = execute_conditional_window_skill(ctx, 2);
    return "";
}

/****************************************************************************************************************/
/*READER CODE*/
/****************************************************************************************************************/

int use_reader(chiventure_ctx_t* ctx){
    attr_reader_effect_t* attr_reader = attr_reader_effect_new("Vampire", 7, READ_SINGLE_TARGET);

    reader_effect_t* vamp_reader = reader_effect_new(READER_ATTRIBUTE, attr_reader, NULL);
    int rt = execute_reader_effect(vamp_reader, ctx);
    if(rt == 1){
        print_to_cli(ctx, "You use the power of eyesight to see your mentor's weakness.");
        print_to_cli(ctx, "You notice he has fangs... He's a vampire!");
        return SUCCESS;
    } else if (rt == 0){
        print_to_cli(ctx, "READER ERROR: MENTOR IS NOT VAMPIRE");
    } else {
        print_to_cli(ctx, "READER ERROR: MENTOR HAS NO CLASS. VAMPIRIZE HIM");
    }
    return FAILURE;
}

char* read_weakness(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{
    int check = use_reader(ctx);
    return "";
}

/****************************************************************************************************************/
/*CLASS CODE*/
/****************************************************************************************************************/

//Functions to change classes for conditional example and class demo
char* change_class_to_orc(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{   
    ctx->game->curr_player->player_class->name = "Orc";
    return "Mentor: Not sure how you managed to do that, but alright, you're an Orc now.";
}

char* change_class_to_orc_again(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{   
    ctx->game->curr_player->player_class->name = "Orc";
    return "You turn into an orc again. It's orcin' time!";
}

//Change class to something else
char* read_book(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{   
    print_to_cli(ctx, "You pick up a book about a legendary mage, and think it's pretty neat!");
    print_to_cli(ctx, "You feel your orcishness disappearing as you become a mage.");
    print_to_cli(ctx, "Mentor: Seriously, how do you do that?");

    ctx->game->curr_player->player_class->name = "Mage";
    return "";

}

/****************************************************************************************************************/
/*MISC CODE*/
/****************************************************************************************************************/

char* combined_monologue(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{   
    print_to_cli(ctx, "Mentor:Hello my young pupil! We shall begin immediately. "
                        "Over the last year, we have made even more powerful, "
                        "complicated skills! In this room, you can learn Combined "
                        "Skills! Many smaller skills wrapped into one. "
                        "Lets teach you a large stat boost!");
    return "";
}

//Random Skills lecture -- random code wasn't merged soon enough to use in the 
//demo, however we put a brief acknowledgement of it here
char* random_monologue(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{   
    print_to_cli(ctx, "Mentor: Random skills are a recent addition to our "
                        "curriculum. However, only distinguished pupils may " 
                        "learn these powerful skills, and you are a novice. "
                        "Perhaps in 20 years you'll be ready.");
    return "";
}

//Lecture by Mentor about documentation
char* mentor_monolouge(char* tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx)
{   
    print_to_cli(ctx, "Mentor: This is the library! In the past year we've gained a lot of books detailing the skills of legendary warriors.");
    print_to_cli(ctx, "Mentor: Druids, elementalists, knights, sorcerors, so much is documented about their legendary skills!");
    print_to_cli(ctx, "Mentor: We've even made tools here that detail their skilltrees down to a high level, all for the sake of knowledge!");
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

/****************************************************************************************************************/
/*MAIN CODE*/
/****************************************************************************************************************/

void main()
{
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    add_entry("LEARN_COMBINED", create_combined_player_stat_effect_operation, NULL, ctx->cli_ctx->table);
    add_entry("USE_COMBINED_BOOST", add_combined_player_stat_operation, NULL, ctx->cli_ctx->table);
    add_entry("LEARN_SEQUENTIAL", create_sequential_player_stat_effect_operation, NULL, ctx->cli_ctx->table);
    add_entry("USE_SEQUENTIAL_MOVE", add_sequential_player_stat_operation, NULL, ctx->cli_ctx->table);
    add_entry("LEARN_CONDITIONAL", create_conditional_player_stat_effect_operation, NULL, ctx->cli_ctx->table);
    add_entry("SMASH_DUMMY!", use_conditional_skill, NULL, ctx->cli_ctx->table);
    add_entry("SMASH_WINDOW!", use_conditional_window_skill, NULL, ctx->cli_ctx->table);
    add_entry("TALK_TO_MENTOR", combined_monologue, NULL, ctx->cli_ctx->table);
    add_entry("TURN_INTO_ORC", change_class_to_orc , NULL, ctx->cli_ctx->table);
    add_entry("TURN_INTO_ORC_AGAIN", change_class_to_orc_again , NULL, ctx->cli_ctx->table);
    add_entry("LISTEN_TO_LECTURE", mentor_monolouge, NULL, ctx->cli_ctx->table);
    add_entry("READ_TOME", read_book, NULL, ctx->cli_ctx->table);
    add_entry("ASK_ABOUT_RANDOM_SKILLS", random_monologue, NULL, ctx->cli_ctx->table);
    add_entry("READ_WEAKNESS", read_weakness , NULL, ctx->cli_ctx->table);

    //Start UI for example chiventure context
    start_ui(ctx, banner);
}
