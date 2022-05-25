#include "../include/battle/battle_test_utility.h"

/* Creates a sample class. Taken from test_class.c */
class_t *generate_test_class()
{
    class_t *c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
               " relying on physical strength and years of training to "
               "deal with any obstacle. Mechanically, the warrior focuses "
               "on up-close physical damage with weapons and survives enemy "
               "attacks using heavy armor.\n";

    c = class_new(name, shortdesc, longdesc, NULL, NULL, NULL);

}

class_t *create_test_class()
{
    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                    NULL, NULL, NULL);
}

class_t *make_wizard()
{
    return class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
}

/* Creates a sample class. Taken from test_class.c */
class_t *generate_npcbattle_test_class()
{
    class_t *c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
                " relying on physical strength and years of training to "
                "deal with any obstacle. Mechanically, the warrior focuses "
                "on up-close physical damage with weapons and survives enemy "
                "attacks using heavy armor.\n";

    c = class_new(name, shortdesc, longdesc, NULL, NULL, NULL);

}

/*-----------------------------------------------------------------------------------------------------------------*/

/* Creates + initializes a battle_item */
 battle_item_t *create_battle_item(int id, int quantity, char* description, 
                                        char *name, bool attack, stat_changes_t *changes)
 {
     battle_item_t* item = (battle_item_t*) calloc(1, sizeof(battle_item_t));

     item->id = id;
     item->name = name;
     item->description = description;
     item->quantity = quantity;
     item->description = description;
     item->attack = attack;
     item->attributes = changes;

     return item;
 }

/* Creates + initializes a battle_item */
 battle_item_t *create_npc_battle_item(int id, int quantity, char* description, 
                                        char *name, bool attack, stat_changes_t *changes)
 {
     battle_item_t* item = (battle_item_t*) calloc(1, sizeof(battle_item_t));

     item->id = id;
     item->name = name;
     item->description = description;
     item->quantity = quantity;
     item->description = description;
     item->attack = attack;
     item->attributes = changes;

     return item;
 }

/* Creates example hardcoded battle_items for the player*/
battle_item_t* create_player_battle_items()
{
    battle_item_t *head, *dagger, *tea_leaves, *medicine;
    head = NULL;
    stat_changes_t *dagger_changes = stat_changes_new();
    dagger_changes->phys_atk = 20;
    dagger_changes->phys_def = 5;
    dagger_changes->hp = 0;
    dagger = create_battle_item(1, 20, "A hearty dagger sure to take your breath away... for good", "Dagger",
                                true, dagger_changes);

    stat_changes_t *tea_changes = stat_changes_new();
    tea_changes->hp = 10;
    tea_changes->phys_atk = 0;
    tea_changes->phys_def = 0;
    tea_leaves = create_battle_item(2, 1, "Make yourself a warm cup of tea to heal your wounds!", "Tea Leaves",
                                    true, tea_changes);

    stat_changes_t *medicine_changes = stat_changes_new();
    medicine_changes->hp = 30;
    medicine_changes->phys_atk = 0;
    medicine_changes->phys_def = 0;
    medicine = create_battle_item(3, 1, "A first aid kit, straight from your doctor!", "Medicine",
                                true, medicine_changes);
    DL_APPEND(head, dagger);
    DL_APPEND(head, tea_leaves);
    DL_APPEND(head, medicine);
    return head;
}

/* Creates example hardcoded items for the enemy*/
battle_item_t* create_enemy_battle_items()
{
    /* I am adding these for a temporary fix, however, these will be changed
 *  *  *        as battle items are no longer weapons */
    battle_item_t *head, *mace, *diamond_sword, *force_shield;
    head = NULL;
    stat_changes_t *mace_changes = stat_changes_new();
    mace_changes->phys_atk = 0;
    mace_changes->phys_def = -30;
    mace_changes->hp = 0;
    mace = create_battle_item(4, 20, "Temporary blindness leaves you quite vulnerable...", "Mace", true,
                                mace_changes);
    stat_changes_t *sword_changes = stat_changes_new();
    sword_changes->phys_atk = 20;
    sword_changes->phys_def = 0;
    sword_changes->hp = 0;
    diamond_sword = create_battle_item(5, 50, "Brings quick death to those who dare battle you...", "Diamond Sword",
        true, sword_changes);

    stat_changes_t *shield_changes = stat_changes_new();
    shield_changes->phys_atk = 0;
    shield_changes->phys_def = 30;
    shield_changes->hp = 5;
    force_shield = create_battle_item(6, 30, "Rest comfortably as this shield protects you for 1 move", "Force Shield",
                                        true, shield_changes);
    DL_APPEND(head, mace);
    DL_APPEND(head, diamond_sword);
    DL_APPEND(head, force_shield);
    return head;
}

 /* Creates + initializes a battle_item */
 battle_item_t *npc_create_battle_item(int id, int quantity, char* description,
                                        char *name, bool attack, stat_changes_t *changes)
 {
     battle_item_t* item = (battle_item_t*) calloc(1, sizeof(battle_item_t));

     item->id = id;
     item->name = name;
     item->description = description;
     item->quantity = quantity;
     item->description = description;
     item->attack = attack;
     item->attributes = changes;

     return item;
 }

/* Creates a sample battle item. Taken from test_battle_ai.c */
battle_item_t *npc_create_battle_item(int id, char *name, char* description,
                                      stat_changes_t *attributes,
                                      int quantity, bool attack)
{
     battle_item_t* item = (battle_item_t*) calloc(1, sizeof(battle_item_t));

     item->id = id;
     item->name = name;
     item->description = description;
     item->attributes = attributes;
     item->quantity = quantity;
     item->attack = attack;


     return item;
 }

/* Creates a sample battle_item. Taken from test_battle_ai.c */
battle_item_t *generate_test_battle_item(int id, int quantity, char* description,
                                         char *name, bool attack, stat_changes_t *changes)
{
     battle_item_t* item = (battle_item_t*) calloc(1, sizeof(battle_item_t));

     item->id = id;
     item->name = name;
     item->description = description;
     item->quantity = quantity;
     item->description = description;
     item->attack = attack;
     item->attributes = changes;

     return item;
}

/*------------------------------------------------------------------------------------------------------------------*/


/* Creates example stats. Taken from test_battle_ai.c */
stat_t *create_enemy_stats()
{
    stat_t *test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;

    return test_stats;
}

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_norm()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_atk = 150;
    test_stats->mag_def = 20;
    test_stats->max_sp = 20;
    test_stats->sp = 20;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;

    return test_stats;
}

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_crit()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_atk = 150;
    test_stats->mag_def = 20;
    test_stats->max_sp = 20;
    test_stats->sp = 20;
    test_stats->crit = 100;
    test_stats->accuracy = 100;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;

    return test_stats;
}

/* Creates example hardcoded stats for the battle_player*/
stat_t* create_battle_player_stats()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));
    test_stats->speed = 50;
    test_stats->phys_def = 30;
    test_stats->phys_atk = 200;
    test_stats->mag_atk = 200;
    test_stats->mag_def = 30;
    test_stats->max_sp = 20;
    test_stats->sp = 20;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->hp = 150;
    test_stats->max_hp = 150;
    test_stats->xp = 0;
    test_stats->level = 1;

    return test_stats;
}

/* Creates example stats. Taken from test_battle_ai.c */
stat_t *create_enemy_stats1()
{
    stat_t *test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_def = 10;
    test_stats->mag_atk = 10;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->sp = 50;
    test_stats->max_sp = 50;

    return test_stats;
}

/* Creates example stats. Taken from test_battle_ai.c */
stat_t *create_enemy_stats2()
{
    stat_t *test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_def = 10;
    test_stats->mag_atk = 10;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->sp = 50;
    test_stats->max_sp = 50;

    return test_stats;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**/

/* Creates example hardcoded moves for the enemy*/
move_t* create_enemy_moves()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = move_new(1, "earthquake", "", PHYS, NO_TARGET, NO_TARGET, 
                          SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    poke = move_new(2, "poke", "", PHYS, NO_TARGET, NO_TARGET,
                    SINGLE, 0, NULL, 40, 100, NULL, NULL, NULL, NULL);
    rock_throw = move_new(3, "rock throw", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 90, 100, NULL, NULL, NULL, NULL);
    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw);
    return head;
}

/* Creates example hardcoded stats for the battle_player*/
move_t* create_battle_player_moves()
{
    move_t *head, *fire_blast, *punch, *blaze_kick;
    head = NULL;
    fire_blast = move_new(4, "fire blast", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    punch = move_new(5, "punch", "", PHYS, NO_TARGET, NO_TARGET,
                     SINGLE, 0, NULL, 20, 100, NULL, NULL, NULL, NULL);
    blaze_kick = move_new(6, "blaze kick", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 60, 100, NULL, NULL, NULL, NULL);
    DL_APPEND(head, fire_blast);
    DL_APPEND(head, punch);
    DL_APPEND(head, blaze_kick);
    return head;
}

/* Creates the expected return value for when the AI should return the greediest move*/
move_t* expected_move_greedy()
{
    move_t* earthquake = move_new(1, "earthquake", "", PHYS, NO_TARGET, NO_TARGET,
                                  SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    return earthquake;
}

/* Creates the expected return value for when the AI should return a random move*/
move_t* expected_move_random()
{
    srand(1);
    int randomish = rand() % 3;
    move_t* rock_throw = move_new(randomish, "", "", PHYS, NO_TARGET, 
                                  NO_TARGET, SINGLE, 0, NULL, 90, 100, 
                                  NULL, NULL, NULL, NULL);
    return rock_throw;
}

/* Called by test functions to check give_move returns properly*/
void check_give_move(combatant_t* player, combatant_t* enemy, difficulty_t difficulty, move_t* expected)
{
    move_t *actual_move, *expected_move;
    actual_move = give_move(player, enemy, difficulty);

    cr_assert_eq(actual_move->id, expected->id, "give_move did not return expected move!");
}

/* Creates a sample npc_mov struct. Taken from test_npc_move.c */
npc_mov_t *generate_test_npc_mov()
{
    npc_mov_t *npc_mov;
    char *test_room_id = "test";
    npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room_id);
}

/* Creates example moves. Taken from test_battle_ai.c */
move_t *create_enemy_moves()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = move_new(1, "earthquake", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    poke = move_new(2, "poke", "", PHYS, NO_TARGET, NO_TARGET,
                    SINGLE, 0, NULL, 40, 100, NULL, NULL, NULL, NULL);
    rock_throw = move_new(3, "rock throw", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 90, 100, NULL, NULL, NULL, NULL);
    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw);
}

move_t *create_enemy_moves1()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = move_new(1, "earthquake", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    poke = move_new(2, "poke", "", PHYS, NO_TARGET, NO_TARGET,
                    SINGLE, 0, NULL, 40, 100, NULL, NULL, NULL, NULL);
    rock_throw = move_new(3, "rock throw", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 90, 100, NULL, NULL, NULL, NULL);
    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw);
    return head;
}

/* Creates example moves. Taken from test_battle_ai.c */
move_t *create_enemy_moves2()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = move_new(1, "earthquake", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    DL_APPEND(head, earthquake);
    return head;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Creates sandbox enemy*/
combatant_t* new_enemy()
{
    char* name = "Skeleton";
    bool is_friendly = false;
    class_t *c_type = create_test_class();
    stat_t *stats = create_enemy_stats_norm();
    move_t *moves = create_enemy_moves();
    battle_item_t *items = create_enemy_battle_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, c_type, stats, moves, items, NULL, NULL, NULL, BATTLE_AI_GREEDY);

}

/* Creates sandbox enemy with crit value 100% */
combatant_t* new_enemy_crit()
{
    char* name = "Skeleton";
    bool is_friendly = false;
    class_t *c_type = create_test_class();
    stat_t *stats = create_enemy_stats_crit();
    move_t *moves = create_enemy_moves();
    battle_item_t *items = create_enemy_battle_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, c_type, stats, moves, items, NULL, NULL, NULL, BATTLE_AI_GREEDY);

}

/* Creates sandbox battle_player*/
combatant_t* new_battle_player()
{
    char* name = "Steve";
    bool is_friendly = true;

    class_t *c_type = create_test_class();
    stat_t *stats = create_battle_player_stats();
    move_t *moves = create_battle_player_moves();
    battle_item_t *items = create_player_battle_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, c_type, stats, moves, items,  NULL, NULL, NULL, BATTLE_AI_NONE);
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*** Dialogue Building Functions ***/

void check_add_node(int num_nodes)
{
    convo_t *c = convo_new();
    char node_id[3];
    char npc_dialogue[3];
    node_list_t *cur;
    int rc;

    strcpy(node_id, "N_");
    strcpy(npc_dialogue, "D_");

    for (int i = 1; i <= num_nodes && i < 10; i++)
    {
        node_id[1] = '0' + i;
        npc_dialogue[1] = '0' + i;

        rc = add_node(c, node_id, npc_dialogue);

        cr_assert_eq(rc, SUCCESS, "add_node() failed for Node %d", i);

        if (i == 1) cur = c->all_nodes;
        else cur = cur->next;

        cr_assert_not_null(cur, "add_node() did not append Node %d to "
                           "all_nodes in the convo", i);

        cr_assert_eq(strcmp(cur->node->node_id, node_id), 0,
                     "Expected %s for the node_id of Node %d but add_node set "
                     "a different value", node_id, i);
        cr_assert_eq(strcmp(cur->node->npc_dialogue, npc_dialogue), 0,
                     "Expected %s for the npc_dialogue of Node %d but add_node "
                     "set a different value", npc_dialogue, i);
    }
}

void check_add_edge(int num_edges)
{
    convo_t *c = convo_new();
    char quip[3];
    edge_list_t *convo_lst_ptr, *node_lst_ptr;
    int rc;

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");

    strcpy(quip, "Q_");

    for (int i = 1; i <= num_edges && i < 10; i++)
    {
        quip[1] = '0' + i;

        rc = add_edge(c, quip, "N1", "N2", NULL);

        cr_assert_eq(rc, SUCCESS, "add_edge() failed for Edge %d", i);

        if (i == 1)
        {
            convo_lst_ptr = c->all_edges;
            node_lst_ptr = c->all_nodes->node->edges;
        }
        else
        {
            convo_lst_ptr = convo_lst_ptr->next;
            node_lst_ptr = node_lst_ptr->next;
        }

        cr_assert_not_null(convo_lst_ptr, "add_edge() did not append Edge %d "
                           "to all_edges in the convo", i);
        cr_assert_not_null(node_lst_ptr, "add_edge() did not append Edge %d "
                           "to edges in Node 1", i);

        cr_assert_eq(strcmp(convo_lst_ptr->edge->quip, quip), 0,
                     "Expected %s for the quip of Edge %d but add_edge set "
                     "a different value", quip, i);
        cr_assert_eq(strcmp(convo_lst_ptr->edge->from->node_id, "N1"), 0,
                     "add_edge set the wrong from node for Edge %d", i);
        cr_assert_eq(strcmp(convo_lst_ptr->edge->to->node_id, "N2"), 0,
                     "add_edge set the wrong to node for Edge %d", i);
    }
}

