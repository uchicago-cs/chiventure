#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_move_maker.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"
#include "battle/battle_logic.h"
#include "battle/battle_default_objects.h"

move_t *generate_moves_user_one()
{
    stat_changes_t *user_stat_changes1 = stat_changes_new();
    user_stat_changes1->hp = 35;
    stat_changes_t *opponent_stat_changes1 = stat_changes_new();
    opponent_stat_changes1->hp = -35;
    move_t *move_one = move_new(1, "LifeDrain", "Drains the enemy hp and adds it to the user", NO_DAMAGE,
                                BOTH , NO_TARGET, SINGLE, 0, NULL, 0, 100, user_stat_changes1, opponent_stat_changes1, 
                                NULL, NULL); 
    stat_changes_t *opponent_stat_changes2 = stat_changes_new();
    opponent_stat_changes2->mag_def = -10;
    move_t *move_two = move_new(2, "ShadowBall", "The user gathers dark shadow energy into a ball and sends it to the opponent, decreasing their magical defense", 
                                MAG, TARGET, NO_TARGET, SINGLE, 10, NULL, 80, 100, NULL, opponent_stat_changes2, 
                                move_one, NULL); 
    move_one->next = move_two;
    return move_one;
}

move_t *generate_moves_user_two()
{
    stat_changes_t *user_stat_changes1 = stat_changes_new();
    user_stat_changes1->phys_atk = 40;
    move_t *move_one = move_new(1, "SwordsDance", "The user dances with swords, raising their attack", NO_DAMAGE,
                                USER , NO_TARGET, SINGLE, 0, NULL, 0, 100, user_stat_changes1, NULL, 
                                NULL, NULL); 
    stat_changes_t *opponent_stat_changes1 = stat_changes_new();
    opponent_stat_changes1->phys_def = -10;
    move_t *move_two = move_new(2, "PiercingJab", "The user lunges towards the enemy, piercing their flesh, decreasing their defense", 
                                PHYS, TARGET, NO_TARGET, SINGLE, 0, NULL, 80, 100, NULL, opponent_stat_changes1, 
                                move_one, NULL); 
    move_one->next = move_two;
    return move_one;
}

move_t *generate_moves_enemy_one()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->phys_atk = 10;
    move_t *move_one = move_new(3, "PowerUpPunch", "The user powers up their fist and punches the opponent, raising their physical attack", PHYS,
                                USER , NO_TARGET, SINGLE, 0, NULL, 40, 100, user_stat_changes, NULL, NULL, NULL); 
    return move_one;
}

move_t *generate_moves_enemy_two()
{
    move_t *move_one = move_new(1, "FocusBlast", "The user powers up their fist and punches the opponent, raising their physical attack", MAG,
                                NO_TARGET, NO_TARGET, SINGLE, 10, NULL, 120, 70, NULL, NULL, 
                                NULL, NULL); 
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->speed = 20;
    move_t *move_two = move_new(2, "FlameCharge", "The user surrounds themselves in flames and tackles the opponent, raising their speed", 
                                PHYS, TARGET, NO_TARGET, SINGLE, 0, NULL, 40, 100, user_stat_changes, NULL, 
                                move_one, NULL); 
    move_one->next = move_two;
    return move_one;
}

