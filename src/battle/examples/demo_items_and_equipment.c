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

battle_equipment_t *make_lunar_ward()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->mag_atk = 15;
    user_stat_changes->max_sp = -15;
    battle_equipment_t *lunar_wand = new_battle_equipment(1, "Lunar Wand", 
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
    battle_equipment_t *cape_of_wisdom = new_battle_equipment(1, "Cape of Wisdom", 
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
    battle_equipment_t *ninja_armor = new_battle_equipment(1, "Ninja Armor", 
    "A suit of armor that belonged to a famous ninja. It increases the user's physical defense, crit, and accuracy", 
    user_stat_changes, ARMOR);
    return ninja_armor;
}

battle_equipment_t *make_razor_claw()
{
    stat_changes_t *user_stat_changes = stat_changes_new();
    user_stat_changes->crit = 25;
    battle_equipment_t *razor_claw = new_battle_equipment(1, "Razor Claw", 
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
    battle_equipment_t *omni_crown = new_battle_equipment(1, "Omni Crown", 
    "A suit of armor that belonged to a famous ninja. It increases the user's physical defense, crit, and accuracy", 
    user_stat_changes, ACCESSORY);
    return omni_crown;
}