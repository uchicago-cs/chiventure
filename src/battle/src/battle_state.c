#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "battle/battle_state.h"
#include "common/utlist.h"

/* See battle_state.h */
combatant_t *combatant_new(char *name, bool is_friendly, class_t *c_type, 
                            stat_t *stats, move_t *moves, battle_item_t *items, 
                            battle_equipment_t *weapon, battle_equipment_t *accessory, 
                            battle_equipment_t *armor,difficulty_t ai)
{
    combatant_t *c;
    int rc;
    c = calloc(1, sizeof(combatant_t));

    if(c == NULL)
    {
        fprintf(stderr, "Could not allocate memory for combatant\n");
        return NULL;
    }

    rc = combatant_init(c, name, is_friendly, c_type, stats, moves, items, weapon,
                        accessory, armor, ai);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize character\n");
        return NULL;
    }

    return c;
}

/* See battle_state.h */
int combatant_init(combatant_t *c, char *name, bool is_friendly, class_t *c_type, stat_t *stats,
                    move_t *moves, battle_item_t *items, battle_equipment_t *weapon, 
                    battle_equipment_t *accessory, battle_equipment_t *armor,difficulty_t ai)
{
    assert(c != NULL);

    c->name = calloc(MAX_NAME_LEN + 1, sizeof(char));
    strncpy(c->name, name, MAX_NAME_LEN);
    c->is_friendly= is_friendly;
    c->class_type = c_type;
    c->stats = stats;
    c->moves = moves;
    c->items = items;
    c->weapon = weapon;
    c->accessory = accessory;
    c->armor = armor;
    c->ai = ai;
    c->next = NULL;
    c->prev = NULL;

    return SUCCESS;
}

/* battle_state.h */
int combatant_free(combatant_t *c)
{
    if (c == NULL)
    {
        return SUCCESS;
    }

    if (c->name)
    {
        free(c->name);
    }

    if (c->stats)
    {
        free(c->stats);
    }

    if (c->class_type)
    {
        class_free(c->class_type);
    }
    move_t *move_elt, *move_tmp;
    DL_FOREACH_SAFE(c->moves, move_elt, move_tmp)
    {
        DL_DELETE(c->moves, move_elt);
        free(move_elt);
    }

    battle_item_t *item_elt, *item_tmp;
    DL_FOREACH_SAFE(c->items, item_elt, item_tmp)
    {
        DL_DELETE(c->items, item_elt);
        free(item_elt);
    }

    free(c);

    return SUCCESS;
}

/* See battle_state.h */
int combatant_free_all(combatant_t *c)
{
    combatant_t *elt, *tmp;
    DL_FOREACH_SAFE(c, elt, tmp)
    {
        DL_DELETE(c, elt);
        combatant_free(elt);
    }
    return SUCCESS;
}

/* See battle_state.h */
battle_t *battle_new(combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn)
{
    battle_t *b;
    int rc;
    b = calloc(1, sizeof(battle_t));

    if(b == NULL)
    {
        fprintf(stderr, "Could not allocate memory for battle struct\n");
        return NULL;
    }

    rc = battle_init(b, player, enemy, env, turn);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize battle struct\n");
        return NULL;
    }

    return b;
}

/* See battle_state.h */
int battle_init(battle_t *b, combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn)
{
    assert(b != NULL);

    b->player = player;
    b->enemy = enemy;
    b->environment = env;
    b->turn = turn;

    return SUCCESS;
}

/* See battle_state.h */
int battle_free(battle_t *b)
{
    assert(b != NULL);

    combatant_free_all(b->player);
    combatant_free_all(b->enemy);

    free(b);

    return SUCCESS;
}

/* See battle_state.h */
stat_changes_t *stat_changes_new() {
    stat_changes_t* sc;
    int rc;

    sc = calloc(1, sizeof(stat_changes_t));

    if (sc == NULL)
    {
        fprintf(stderr, "Could not allocate memory for stat changes struct\n");
        return NULL;
    }

    rc = stat_changes_init(sc);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize stat changes struct\n");
        return NULL;
    }

    return sc;    
}

/* See battle_state.h */
int stat_changes_init(stat_changes_t *sc) {
    assert(sc != NULL);

    sc->speed = 0;
    sc->max_sp = 0;
    sc->sp = 0;
    sc->phys_atk = 0;
    sc->phys_def = 0;
    sc->mag_atk = 0;
    sc->mag_def = 0;
    sc->crit = 0;
    sc->accuracy = 0;
    sc->hp = 0;
    sc->max_hp = 0;
    sc->turns_left = -1;
    sc->next = NULL;
    sc->prev = NULL;

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_free_node(stat_changes_t *sc) {
    assert(sc != NULL);
        
    free(sc);

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_free_all(stat_changes_t *sc) {
    stat_changes_t *current = sc;
    stat_changes_t *next = NULL;

    while (current->next != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return SUCCESS;
}

/* As somewhat higher level functions, do these still belong here or should I move them? */

/* See battle_state.h */
int stat_changes_append_node(stat_changes_t *base, stat_changes_t *sc) {
    while (base->next != NULL) {
        base = base->next;
    }

    base->next = sc;
    sc->prev = base;

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_add_node(stat_changes_t *sc) {
    stat_changes_t *new_node = stat_changes_new();

    stat_changes_append_node(sc, new_node);

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_remove_node(stat_changes_t *sc) {
    stat_changes_t *after = sc->next;
    stat_changes_t *before = sc->prev;

    before->next = after;

    if (sc->next != NULL) {
        after->prev = before;
    }
    
    stat_changes_free_node(sc);

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_turn_increment(stat_changes_t *sc, combatant_t *c) {
    stat_changes_t *current = sc->next;
    stat_changes_t *remove = sc->next;

    while (current != NULL) {
        current->turns_left -= 1;
        
        
        if (current->turns_left == 0) {
            remove = current;
            current = current->next;

            stat_changes_undo(remove, c);
            stat_changes_remove_node(remove);
        } else {
            current = current->next;
        }
    }

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_undo(stat_changes_t *sc, combatant_t *c)
{
    c->stats->hp -= sc->hp;
    c->stats->max_hp -= sc->max_hp;
    c->stats->phys_atk -= sc->phys_atk;
    c->stats->mag_atk -= sc->mag_atk;
    c->stats->phys_def -= sc->phys_def;
    c->stats->mag_def -= sc->mag_def;
    c->stats->crit -= sc->crit;
    c->stats->accuracy -= sc->accuracy;
    c->stats->sp -= sc->sp;
    c->stats->max_sp -= sc->max_sp;
    c->stats->speed -= sc->speed;

    return SUCCESS;
}
