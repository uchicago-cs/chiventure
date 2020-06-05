#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "battle/battle_state.h"
#include "common/utlist.h"

/* See battle_state.h */
combatant_t *combatant_new(char *name, bool is_friendly, class_t *class, stat_t *stats,
    move_t *moves, item_t *items, difficulty_t ai)
{
    combatant_t *c;
    int rc;
    c = calloc(1, sizeof(combatant_t));

    if(c == NULL)
    {
        fprintf(stderr, "Could not allocate memory for combatant\n");
        return NULL;
    }

    rc = combatant_init(c, name, is_friendly, class, stats, moves, items, ai);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize character\n");
        return NULL;
    }

    return c;
}

/* See battle_state.h */
int combatant_init(combatant_t *c, char *name, bool is_friendly, class_t *class, stat_t *stats,
    move_t *moves, item_t *items, difficulty_t ai)
{
    assert(c != NULL);

    c->name = calloc(MAX_NAME_LEN + 1, sizeof(char));
    strncpy(c->name, name, MAX_NAME_LEN);
    c->is_friendly= is_friendly;
    c->class = class;
    c->stats = stats;
    c->moves = moves;
    c->items = items;
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

    if (c->class)
    {
        free(c->class);
    }

    move_t *move_elt, *move_tmp;
    DL_FOREACH_SAFE(c->moves, move_elt, move_tmp)
    {
        DL_DELETE(c->moves, move_elt);
        free(move_elt);
    }

    item_t *item_elt, *item_tmp;
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
