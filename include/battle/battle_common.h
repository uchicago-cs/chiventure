#ifndef BATTLE_COMMON_H
#define BATTLE_COMMON_H

/* AI move strategy options */
typedef enum difficulty
{
    BATTLE_AI_NONE = 0,
    BATTLE_AI_GREEDY = 1,
    BATTLE_AI_RANDOM = 2
} difficulty_t;

/* A combatant struct that contains the following:
 * name: combatant name
 * is_friendly: whether combatant is the player or enemy
 * class: class type
 * stats: pointer to stats module (stub)
 * moves: pointer to moves module (stub)
 * items: pointer to items module (stub)
 * ai: combatant's ai move strategy
 * next: allows for combatant lists using utlist.h
 * prev: allows for combatant lists using utlist.h
 */
typedef struct combatant
{
    char *name;
    bool is_friendly;
    class_t *class;
    stat_t *stats;
    move_t *moves;
    item_t *items;
    difficulty_t ai;
    struct combatant *next;
    struct combatant *prev;
} combatant_t;