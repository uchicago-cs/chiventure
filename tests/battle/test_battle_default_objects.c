#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_default_objects.h"

Test(battle_default_objects, default_consumables)
{
    battle_item_t *test_item = get_random_default_consumable();
    
    cr_assert_not_null(test_item, "get_random_default_consumable() failed");

    int id = test_item->id; 

    cr_assert_leq(test_item->quantity, 4, "get_random_default_consumable() did not set quantity correctly");
    cr_assert_geq(test_item->quantity, 1, "get_random_default_consumable() did not set quantity correctly");
    
    if (id == 1)
    {
        // Elixir of Life
        cr_assert_eq(test_item->durability, 0, "get_random_default_consumable() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Elixir of Life", "get_random_default_consumable() did not set name correctly");
        cr_assert_str_eq(test_item->description, "Adds 50 to your HP!", "get_random_default_consumable() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_consumable() did not set durability correctly");
        cr_assert_eq(test_item->attack, 0, "get_random_default_consumable() did not set attack correctly");
        cr_assert_eq(test_item->defense, 0, "get_random_default_consumable() did not set defense correctly");
        cr_assert_eq(test_item->hp, 50, "get_random_default_consumable() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_consumable() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_consumable() did not set item->prev correctly");
    }
    else if (id == 2)
    {
        // Healing Potion
        cr_assert_eq(test_item->durability, 0, "get_random_default_consumable() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Healing Potion", "get_random_default_consumable() did not set name correctly");
        cr_assert_str_eq(test_item->description, "Adds 20 to your HP!", "get_random_default_consumable() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_consumable() did not set durability correctly");
        cr_assert_eq(test_item->attack, 0, "get_random_default_consumable() did not set attack correctly");
        cr_assert_eq(test_item->defense, 0, "get_random_default_consumable() did not set defense correctly");
        cr_assert_eq(test_item->hp, 20, "get_random_default_consumable() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_consumable() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_consumable() did not set item->prev correctly");
    }
    else if (id == 3)
    {
        // Defense Up
        cr_assert_eq(test_item->durability, 0, "get_random_default_consumable() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Defense Up", "get_random_default_consumable() did not set name correctly");
        cr_assert_str_eq(test_item->description, "Adds 5 to your defense!", "get_random_default_consumable() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_consumable() did not set durability correctly");
        cr_assert_eq(test_item->attack, 0, "get_random_default_consumable() did not set attack correctly");
        cr_assert_eq(test_item->defense, 5, "get_random_default_consumable() did not set defense correctly");
        cr_assert_eq(test_item->hp, 0, "get_random_default_consumable() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_consumable() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_consumable() did not set item->prev correctly");
    }
    else if (id == 4)
    {
        // Strength Up
        cr_assert_eq(test_item->durability, 0, "get_random_default_consumable() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "strength up ", "get_random_default_consumable() did not set name correctly");
        cr_assert_str_eq(test_item->description, "Adds 5 to your strength!", "get_random_default_consumable() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_consumable() did not set durability correctly");
        cr_assert_eq(test_item->attack, 5, "get_random_default_consumable() did not set attack correctly");
        cr_assert_eq(test_item->defense, 0, "get_random_default_consumable() did not set defense correctly");
        cr_assert_eq(test_item->hp, 0, "get_random_default_consumable() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_consumable() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_consumable() did not set item->prev correctly");
    }
    else
    {
        cr_assert_fail("get_random_default_consumable() did not set id correctly");
    }
}

Test(battle_default_objects, default_weapon)
{
    battle_item_t *test_weapon = get_random_default_weapon();
    
    cr_assert_not_null(test_weapon, "get_random_weapon() failed");

    int id = test_weapon->id; 

    cr_assert_leq(test_weapon->quantity, 4, "get_random_default_consumable() did not set quantity correctly");
    cr_assert_geq(test_weapon->quantity, 1, "get_random_default_consumable() did not set quantity correctly");    
    if (id == 1)
    {
        // SWORD
        cr_assert_eq(test_weapon->is_weapon, true, "get_random_weapon() did not set is_weapon correctly"); 
        cr_assert_eq(test_weapon->durability, 100, "get_random_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_weapon->name, "Sword", "get_random_weapon() did not set name correctly");
        cr_assert_str_eq(test_weapon->description, "Reduces enemy's HP by 20", "get_random_weapon() did not set description correctly");
        cr_assert_eq(test_weapon->battle, true, "get_random_weapon() did not set durability correctly");
        cr_assert_eq(test_weapon->attack, 0, "get_random_weapon() did not set attack correctly");
        cr_assert_eq(test_weapon->defense, 0, "get_random_weapon() did not set defense correctly");
        cr_assert_eq(test_weapon->hp, -20, "get_random_weapon() did not set hp correctly");
        cr_assert_null(test_weapon->next, "get_random_weapon() did not set item->next correctly");
        cr_assert_null(test_weapon->prev, "get_random_weapon() did not set item->prev correctly");
    }
    else if (id == 2)
    {
        // HAMMER
        cr_assert_eq(test_weapon->is_weapon, true, "get_random_weapon() did not set is_weapon correctly"); 
        cr_assert_eq(test_weapon->durability, 80, "get_random_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_weapon->name, "Hammer", "get_random_weapon() did not set name correctly");
        cr_assert_str_eq(test_weapon->description, "Reduces enemy's HP by 10", "get_random_weapon() did not set description correctly");
        cr_assert_eq(test_weapon->battle, true, "get_random_weapon() did not set durability correctly");
        cr_assert_eq(test_weapon->attack, 0, "get_random_weapon() did not set attack correctly");
        cr_assert_eq(test_weapon->defense, 0, "get_random_weapon() did not set defense correctly");
        cr_assert_eq(test_weapon->hp, -10, "get_random_weapon() did not set hp correctly");
        cr_assert_null(test_weapon->next, "get_random_weapon() did not set item->next correctly");
        cr_assert_null(test_weapon->prev, "get_random_weapon() did not set item->prev correctly");
    }
    else if (id == 3)
    {
        // SLIME
        cr_assert_eq(test_weapon->is_weapon, true, "get_random_weapon() did not set is_weapon correctly"); 
        cr_assert_eq(test_weapon->durability, 60, "get_random_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_weapon->name, "Slime", "get_random_weapon() did not set name correctly");
        cr_assert_str_eq(test_weapon->description, "Reduces enemy's ATTACK by 5", "get_random_weapon() did not set description correctly");
        cr_assert_eq(test_weapon->battle, true, "get_random_weapon() did not set durability correctly");
        cr_assert_eq(test_weapon->attack, -5, "get_random_weapon() did not set attack correctly");
        cr_assert_eq(test_weapon->defense, -2, "get_random_weapon() did not set defense correctly");
        cr_assert_eq(test_weapon->hp, 0, "get_random_weapon() did not set hp correctly");
        cr_assert_null(test_weapon->next, "get_random_weapon() did not set item->next correctly");
        cr_assert_null(test_weapon->prev, "get_random_weapon() did not set item->prev correctly");
    }
    else if (id == 4)
    {
        // SLEEPING GAS
        cr_assert_eq(test_weapon->is_weapon, true, "get_random_weapon() did not set is_weapon correctly"); 
        cr_assert_eq(test_weapon->durability, 40, "get_random_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_weapon->name, "Sleeping gas", "get_random_weapon() did not set name correctly");
        cr_assert_str_eq(test_weapon->description, "Reduces enemy's ATTACK by 10", "get_random_weapon() did not set description correctly");
        cr_assert_eq(test_weapon->battle, true, "get_random_weapon() did not set durability correctly");
        cr_assert_eq(test_weapon->attack, -10, "get_random_weapon() did not set attack correctly");
        cr_assert_eq(test_weapon->defense, -5, "get_random_weapon() did not set defense correctly");
        cr_assert_eq(test_weapon->hp, 0, "get_random_weapon() did not set hp correctly");
        cr_assert_null(test_weapon->next, "get_random_weapon() did not set item->next correctly");
        cr_assert_null(test_weapon->prev, "get_random_weapon() did not set item->prev correctly");
    }
    else if (id == 5)
    {
        // SQUID INK
        cr_assert_eq(test_weapon->is_weapon, true, "get_random_weapon() did not set is_weapon correctly"); 
        cr_assert_eq(test_weapon->durability, 30, "get_random_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_weapon->name, "Squid ink", "get_random_weapon() did not set name correctly");
        cr_assert_str_eq(test_weapon->description, "Reduces enemy's DEFENSE by 10", "get_random_weapon() did not set description correctly");
        cr_assert_eq(test_weapon->battle, true, "get_random_weapon() did not set durability correctly");
        cr_assert_eq(test_weapon->attack, 0, "get_random_weapon() did not set attack correctly");
        cr_assert_eq(test_weapon->defense, -10, "get_random_weapon() did not set defense correctly");
        cr_assert_eq(test_weapon->hp, 0, "get_random_weapon() did not set hp correctly");
        cr_assert_null(test_weapon->next, "get_random_weapon() did not set item->next correctly");
        cr_assert_null(test_weapon->prev, "get_random_weapon() did not set item->prev correctly");
    }
    else if (id == 6)
    {
        // LAUGHING GAS
        cr_assert_eq(test_weapon->is_weapon, true, "get_random_weapon() did not set is_weapon correctly"); 
        cr_assert_eq(test_weapon->durability, 20, "get_random_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_weapon->name, "Laughing gas", "get_random_weapon() did not set name correctly");
        cr_assert_eq(test_weapon->battle, true, "get_random_weapon() did not set durability correctly");
        cr_assert_str_eq(test_weapon->description, "Reduces enemy's DEFENSE by 15", "get_random_weapon() did not set description correctly");
        cr_assert_eq(test_weapon->attack, 0, "get_random_weapon() did not set attack correctly");
        cr_assert_eq(test_weapon->defense, -15, "get_random_weapon() did not set defense correctly");
        cr_assert_eq(test_weapon->hp, 0, "get_random_weapon() did not set hp correctly");
        cr_assert_null(test_weapon->next, "get_random_weapon() did not set item->next correctly");
        cr_assert_null(test_weapon->prev, "get_random_weapon() did not set item->prev correctly");
    }
    
    else
    {
        cr_assert_fail("get_random_weapon() did not set id correctly");
    }
}

Test(battle_default_objects, default_moves)
{
    move_t *test_move = get_random_default_move();

    char *name_array[] = {"SLAP", "JAB", "KICK", "HEADBUTT", "GRAPPLE", 
                          "UPPERCUT", "HAMMERFIST", "BITE", "THRASH", "THROW"};          

    int id = test_move->id;

    if (id == 1)
    {
        // SLAP
        cr_assert_str_eq(test_move->info, "SLAP", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 45, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 15, "get_random_default_move() did not set defense correctly");                                            
    }        
    else if (id == 2)
    {
        // JAB
        cr_assert_str_eq(test_move->info, "JAB", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 50, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 25, "get_random_default_move() did not set defense correctly");                                            
    }      
    else if (id == 3)
    {
        // KICK
        cr_assert_str_eq(test_move->info, "KICK", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 55, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 35, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 4)
    {
        // HEADBUTT
        cr_assert_str_eq(test_move->info, "headbutt", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 60, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 45, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 5)
    {
        // GRAPPLE
        cr_assert_str_eq(test_move->info, "GRAPPLE", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 65, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 55, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 6)
    {
        // UPPERCUT
        cr_assert_str_eq(test_move->info, "UPPERCUT", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 70, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 65, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 7)
    {
        // HAMMERFIST
        cr_assert_str_eq(test_move->info, "HAMMERFIST", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 75, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 75, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 8)
    {
        // BITE
        cr_assert_str_eq(test_move->info, "BITE", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 80, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 85, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 9)
    {
        // THRASH
        cr_assert_str_eq(test_move->info, "THRASH", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 85, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 95, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 10)
    {
        // THROW
        cr_assert_str_eq(test_move->info, "THROW", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 90, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 105, "get_random_default_move() did not set defense correctly");                                            
    }     
    else
    {
        cr_assert_fail("get_random_default_weapon() did not set id correctly");
    }
}
