#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_move_maker.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"
#include "battle/battle_logic.h"
#include "battle/battle_default_objects.h"

battle_equipment_t *make_zenith()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->phys_atk = 30;
    battle_equipment_t *zenith = new_battle_equipment(1, "Zenith", 
    "A sword that's so sharp and well-forged that it increases the user's physical attack", 
    user_stat_changes, WEAPON);
    return zenith;
}

battle_equipment_t *make_lunar_wand()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->mag_atk = 15;
    user_stat_changes->max_sp = -15;
    battle_equipment_t *lunar_wand = new_battle_equipment(2, "Lunar Wand", 
    "A wand that harnesses the power of the moon and increases the user's magic attack but decreases the max sp", 
    user_stat_changes, WEAPON);
    return lunar_wand;
}

battle_equipment_t *make_cape_of_wisdom()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->mag_def = 20;
    user_stat_changes->phys_def = 20;
    user_stat_changes->sp = 15;
    battle_equipment_t *cape_of_wisdom = new_battle_equipment(3, "Cape of Wisdom", 
    "A cape that is so wise it increases the physical defense, magical defense and sp of the user", 
    user_stat_changes, ARMOR);
    return cape_of_wisdom;
}

battle_equipment_t *make_ninja_armor()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->phys_def = 25;
    user_stat_changes->crit = 5;
    user_stat_changes->accuracy = 5;
    battle_equipment_t *ninja_armor = new_battle_equipment(4, "Ninja Armor", 
    "A suit of armor that belonged to a famous ninja. It increases the user's physical defense, crit, and accuracy", 
    user_stat_changes, ARMOR);
    return ninja_armor;
}

battle_equipment_t *make_razor_claw()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->crit = 25;
    battle_equipment_t *razor_claw = new_battle_equipment(5, "Razor Claw", 
    "A claw that belonged to the chief of the cat tribe, making it super sharp. Increases the user's crit stat.", 
    user_stat_changes, ACCESSORY);
    return razor_claw;
}

battle_equipment_t *make_omni_crown()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->max_sp = 5;
    user_stat_changes->sp = 5;
    user_stat_changes->phys_atk = 5;
    user_stat_changes->mag_atk = 5;
    user_stat_changes->phys_def = 5;
    user_stat_changes->mag_def = 5;
    user_stat_changes->crit = 5;
    user_stat_changes->accuracy = 5;
    user_stat_changes->hp = 5;
    user_stat_changes->max_hp = 5;
    user_stat_changes->speed = 5;
    battle_equipment_t *omni_crown = new_battle_equipment(6, "Omni Crown", 
    "A suit of armor that belonged to a famous ninja. It increases the user's physical defense, crit, and accuracy", 
    user_stat_changes, ACCESSORY);
    return omni_crown;
}

battle_item_t *make_items(){
    stat_changes_t *smoke_bomb_stats = stat_changes_new();
    smoke_bomb_stats->phys_def = -10;
    smoke_bomb_stats->mag_def = -10;
    smoke_bomb_stats->accuracy = -15;
    battle_item_t *smoke_bomb = new_battle_item(1, "Smoke Bomb", 
    "Prevents the enemy from seeing, decreasing their defense and accuracy", 
    smoke_bomb_stats, 2, TRUE, NULL, NULL);
    stat_changes_t *beserk_potion_stats = stat_changes_new();
    beserk_potion_stats->mag_atk = 50;
    beserk_potion_stats->phys_atk = 50;
    beserk_potion_stats->crit = 50;
    beserk_potion_stats->mag_def = -40;
    beserk_potion_stats->phys_def = -40;
    battle_item_t *beserk_potion = new_battle_item(2, "Beserk Potion", 
    "Makes the user go berserk, losing all sanity. Increases all attack stats but decreases all defense stats", 
    beserk_potion_stats, 1, FALSE, NULL, smoke_bomb);
    stat_changes_t *sp_restore_stats = stat_changes_new();
    sp_restore_stats->sp = 20;
    battle_item_t *sp_restore = new_battle_item(3, "SP Restore", 
    "Restores the user's SP.", sp_restore_stats, 3, 
    FALSE, NULL, beserk_potion);
    beserk_potion->next = sp_restore;
    smoke_bomb->next = beserk_potion;
    sp_restore->next = NULL;
    return smoke_bomb;
}