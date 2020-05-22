#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/AI.h"

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
            combatant_new(),
            combatant_new(),
            new_move()
            );
}

//initialize
Test(AI, give_move_medium)
{
    check_give_move(2,  
            combatant_new(),
            combatant_new(),
            new_move());
}

//initialize
Test(AI, give_move_hard)
{
    check_give_move(3,  
            combatant_new(),
            combatant_new(),
            new_move()
        );
}

//check moves for equality + initialize
Test(AI, easy_move)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = combatant_new();
    enemy = combtatant_new();

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

    player = combatant_new();
    enemy = combtatant_new();

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

    player = combatant_new();
    enemy = combtatant_new();

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

    player = combatant_new();
    enemy = combtatant_new();

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

    player = combatant_new();
    enemy = combtatant_new();

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

    player = combatant_new();
    enemy = combtatant_new();
    move = new_move();

    double expected = 0.0;
    double actual = damage(player, move, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");
    cr_assert_not_null(move, "move_new() failed");

    cr_assert_float_eq(actual, expected, 1E-6);
}