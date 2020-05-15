#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "battle/battle_state.h"


/* See battle_state.h */
character_t *character_new(char *name, char_t ct, stat_t *stats,
    move_t *moves, item_t *items, character_t *next)
{
    character_t *c;
    int rc;
    c = malloc(sizeof(character_t));

    if(c == NULL)
    {
        fprintf(stderr, "Could not allocate memory for character\n");
        return NULL;
    }

    rc = character_init(name, ct, stats, moves, items, next);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize character\n");
        return NULL;
    }

    return c;
}

/* See battle_state.h */
int character_init(character_t *c, char *name, char_t type, stat_t *stats,
    move_t *moves, item_t *items, character_t *next)
{
    assert(c != NULL);

    c->name = malloc(50);
    strcpy(c->name, name);
    c->type = type;
    c->stats = stats;
    c->moves = moves;
    c->items = items;
    c->next = next;

    return SUCCESS;
}

/* See battle_state.h */
void free_character(character_t *c)
{
    assert(c != NULL);

    free(c->name);
    free(c->stats);
    free(c->moves);
    free(c->items);
    free(c->next)
    free(c);

    return SUCCESS;
}

/* See battle_state.h */
battle_t *battle_new(character_t *p, character_t *ene,
    environment_t env, char_t t)
{
    battle_t *b;
    int rc;
    b = malloc(sizeof(battle_t));

    if(b == NULL)
    {
        fprintf(stderr, "Could not allocate memory for battle struct\n");
        return NULL;
    }

    rc = battle_init(b, p, ene, env, t);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize battle struct\n");
        return NULL;
    }

    return b;
}

/* See battle_state.h */
int *battle_init(battle_t *b, character_t *p, character_t *ene,
    environment_t env, char_t t)
{
    assert(b != NULL);

    b->player = p;
    b->enemy = ene;
    b->environment = env;
    b->turn = t;

    return SUCCESS;
}

/* See battle_state.h */
void free_battle(battle_t *b)
{
    assert(b != NULL);

    character_free(b->player);
    character_free(b->enemy);
    free(b);

    return SUCCESS;
}

