#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/AI.h"

//creates an example enemy for testing purposes
combatant_t* new_enemy()
{
    char* name = "Skeleton";
    bool is_friendly = false;
    class_t class = bard;
    stat_t *stats = create_player_stats();
    move_t *moves;
    item_t *items = create_enemy_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, class, stats, moves, items);
}


//creates an example player for testing purposes
combatant_t* new_player()
{
    char* name = "Steve";
    bool is_friendly = true;
    class_t class = bard;
    stat_t *stats = create_enemy_stats();
    move_t *moves;
    item_t *items = create_player_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, class, stats, moves, items);
}

stat_t* create_enemy_stats()
{
    stat_t* test_stats = malloc(sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->strength = 150;
    test_stats->dexterity = 10;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;

    return test_stats;
}

stat_t* create_player_stats()
{
    stat_t* test_stats = malloc(sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->strength = 200;
    test_stats->dexterity = 10;
    test_stats->hp = 150;
    test_stats->max_hp = 150;
    test_stats->xp = 0;

    return test_stats;
}

move_t* create_player_items()
{
    item_t *head, *dagger, *tea_leaves, *medicine;
    head = NULL;
    dagger = create_item(1, 1, 20, "A hearty dagger sure to take your breath away... for good",
	true, 20, 5, 0);
	tea_leaves = create_item(2, 1, 1, "Make yourself a warm cup of tea to heal your wounds!", true,
	0, 0, 10);
	medicine = create_item(3, 1, 1, "A first aid kit, straight from your doctor!", true, 0, 0, 30,);
	DL_APPEND(head, dagger);
    DL_APPEND(head, tea_leaves);
    DL_APPEND(head, medicine);
    return head;
}

move_t* create_enemy_items()
{
    item_t *head, *mace, *diamond_sword, *force_shield;
    head = NULL;
    mace = create_item(4, 1, 20, "Temporary blindness leaves you quite vulnerable...", true, 
        0, -30, 0);
	diamond_sword = create_item(5, 1, 50, "Brings quick death to those who dare battle you...", 
        true, 20, 0, 0);
	force_shield = create_item(6, 1, 30, "Rest comfortably as this shield protects you for 1 move", 
        true, 0, 30, 5);
    DL_APPEND(head, mace);
    DL_APPEND(head, diamond_sword);
    DL_APPEND(head, force_shield);
}

//creates the example moves
move_t* expected_move_easy();

move_t* expected_move_hard();

move_t* expected_move_random();

//check for equality
void check_give_move(int difficulty, combatant_t* player, combatant_t* enemy, move_t* expected)
{
    move_t *actual_move, *expected_move;
    actual_move = give_move(difficulty, player, enemy);
    expected_move = move_new();

    cr_assert_eq(actual_move, expected_move, "give_move() failed");
}

//initialize
Test(AI, give_move_easy)
{
    check_give_move(1, 
            new_player(),
            new_enemy(),
            new_move()
            );
}

//initialize
Test(AI, give_move_medium)
{
    check_give_move(2,   
            new_player(),
            new_enemy(),
            new_move());
}

//initialize
Test(AI, give_move_hard)
{
    check_give_move(3,   
            new_player(),
            new_enemy(),
            new_move()
        );
}

//check moves for equality + initialize
Test(AI, easy_move)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = new_player();
    enemy = new_enemy();

    expected_move = new_move(); //put in expected move
    actual_move = easy_move(player, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    //check moves for equality
}

//check moves for equality + initialize
Test(AI, medium_move)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = new_player();
    enemy = new_enemy();

    expected_move = new_move(); //put in expected move
    actual_move = medium_move(player, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    //check moves for equality
}

//check moves for equality + initialize
Test(AI, hard_move)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = new_player();
    enemy = new_enemy();

    expected_move = new_move(); //put in expected move
    actual_move = hard_move(player, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    //check moves for equality
}

//check moves for equality + initialize
Test(AI, find_easy)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = new_player();
    enemy = new_enemy();

    expected_move = new_move(); //put in expected move
    actual_move = find_easy(player, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");


    //check for equality
}

//check moves for equality + initialize
Test(AI, find_hard)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = new_player();
    enemy = new_enemy();

    expected_move = new_move(); //put in expected move
    actual_move = find_hard(player, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    //check moves for equality
    cr_assert_eq(expected_move->attack, actual_move->attack, "bool attack not equal");
    cr_assert_eq(expected_move, actual_move, "bool attack not equal");
}


//completed
Test(AI, damage)
{
    combatant_t *player, *enemy;
    move_t* move;

    player = new_player();
    enemy = new_enemy();
    move = new_move();

    double expected = 0.0;
    double actual = damage(player, move, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");
    cr_assert_not_null(move, "move_new() failed");

    cr_assert_float_eq(actual, expected, 1E-6);
}