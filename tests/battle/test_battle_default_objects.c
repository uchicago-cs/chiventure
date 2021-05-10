#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_default_objects.h"

Test(battle_default_objects, default_weapon) 
{
    battle_item_t *test_item = get_random_default_weapon();
    
    cr_assert_not_null(test_item, "get_random_default_weapon() failed");

    int id = test_item->id; 

    cr_assert_eq(test_item->quantity, 1, "get_random_default_weapon() did not set quantity to 1");
    
    if (id == 1)
    {
        // Stick
        cr_assert_eq(test_item->durability, 10, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Stick", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Stick", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 10, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 15, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 20, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 2)
    {
        // Hammer
        cr_assert_eq(test_item->durability, 20, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Hammer", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Hammer", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 20, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 25, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 30, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 3)
    {
        // Shiv
        cr_assert_eq(test_item->durability, 30, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Shiv", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Shiv", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 30, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 35, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 40, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 4)
    {
        // Club
        cr_assert_eq(test_item->durability, 40, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Club", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Club", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 40, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 45, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 50, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 5)
    {
        // Bow & Arrow
        cr_assert_eq(test_item->durability, 50, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Bow & Arrow", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Bow & Arrow", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 50, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 55, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 60, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 6)
    {
        // Spear
        cr_assert_eq(test_item->durability, 60, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Spear", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Spear", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 60, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 65, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 70, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 7)
    {
        // Axe
        cr_assert_eq(test_item->durability, 70, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Axe", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Axe", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 70, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 75, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 80, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 8)
    {
        // Trident
        cr_assert_eq(test_item->durability, 80, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Trident", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Trident", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 80, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 85, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 90, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 9)
    {
        // Sword
        cr_assert_eq(test_item->durability, 90, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Sword", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Sword", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 90, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 95, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 100, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else if (id == 10)
    {
        // Shield
        cr_assert_eq(test_item->durability, 100, "get_random_default_weapon() did not set durability correctly");   
        cr_assert_str_eq(test_item->name, "Shield", "get_random_default_weapon() did not set name correctly");
        cr_assert_str_eq(test_item->description, "It is a Shield", "get_random_default_weapon() did not set description correctly");
        cr_assert_eq(test_item->battle, true, "get_random_default_weapon() did not set durability correctly");
        cr_assert_eq(test_item->attack, 100, "get_random_default_weapon() did not set attack correctly");
        cr_assert_eq(test_item->defense, 105, "get_random_default_weapon() did not set defense correctly");
        cr_assert_eq(test_item->hp, 110, "get_random_default_weapon() did not set hp correctly");
        cr_assert_null(test_item->next, "get_random_default_weapon() did not set item->next correctly");
        cr_assert_null(test_item->prev, "get_random_default_weapon() did not set item->prev correctly");
    }
    else
    {
        cr_assert_fail("get_random_default_weapon() did not set id correctly");
    }
}

Test(battle_default_objects, default_consumables)
{
    item_t *test_item = get_random_default_consumable();
    
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
        cr_assert_str_eq(test_item->name, "Strength Up", "get_random_default_consumable() did not set name correctly");
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
        cr_assert_eq(test_move->damage, 10, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 15, "get_random_default_move() did not set defense correctly");                                            
    }        
    else if (id == 2)
    {
        // JAB
        cr_assert_str_eq(test_move->info, "JAB", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 20, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 25, "get_random_default_move() did not set defense correctly");                                            
    }      
    else if (id == 3)
    {
        // KICK
        cr_assert_str_eq(test_move->info, "KICK", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 30, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 35, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 4)
    {
        // HEADBUTT
        cr_assert_str_eq(test_move->info, "HEADBUTT", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 40, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 45, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 5)
    {
        // GRAPPLE
        cr_assert_str_eq(test_move->info, "GRAPPLE", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 50, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 55, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 6)
    {
        // UPPERCUT
        cr_assert_str_eq(test_move->info, "UPPERCUT", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 60, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 65, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 7)
    {
        // HAMMERFIST
        cr_assert_str_eq(test_move->info, "HAMMERFIST", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 70, "get_random_default_move() did not set damage correctly");
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
        cr_assert_eq(test_move->damage, 90, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 95, "get_random_default_move() did not set defense correctly");                                            
    }     
    else if (id == 10)
    {
        // THROW
        cr_assert_str_eq(test_move->info, "THROW", "get_random_default_move() did not set info correctly");
        cr_assert_eq(test_move->attack, true, "get_random_default_move() did not set attack correctly");
        cr_assert_eq(test_move->damage, 100, "get_random_default_move() did not set damage correctly");
        cr_assert_eq(test_move->defense, 105, "get_random_default_move() did not set defense correctly");                                            
    }     
    else
    {
        cr_assert_fail("get_random_default_weapon() did not set id correctly");
    }
}
