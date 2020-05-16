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

    rc = character_init(c, name, ct, stats, moves, items, next);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize character\n");
        return NULL;
    }

    return c;
}

/* See battle_state.h */
int character_init(character_t *c, char *name, char_t ct, stat_t *stats,
    move_t *moves, item_t *items, character_t *next)
{
    assert(c != NULL);

    c->name = malloc(50);
    strcpy(c->name, name);
    c->type = ct;
    c->stats = stats;
    c->moves = moves;
    c->items = items;
    c->next = next;

    return SUCCESS;
}

/* battle_state.h */
int free_character(character_t *c)
{
	assert(c != NULL);

	if(c->next != NULL)
	{
		printf("moving\n");
		character_t *next_c = c->next;
		c->name = next_c->name;
		c->stats = next_c->stats;
		c->moves = next_c->moves;
		c->items = next_c->items;
		c->next = next_c->next;
		return free_character(c->next);
	}
	else
	{
		printf("freeing char %s\n",c->name);
		free(c->name);
		free(c->stats);
		free(c->moves);
		free(c->items);
		free(c);
		return SUCCESS;
	}
}

/* See battle_state.h */
int free_characters(character_t *c)
{
    if(c != NULL)
	{
    	free(c->name);
    	free(c->stats);
    	free(c->moves);
    	free(c->items);
    	int rc = free_characters(c->next);
    	free(c);
	}
    return SUCCESS;
}

/* See battle_state.h */
battle_t *battle_new(character_t *p, character_t *ene,
    environment_t env, char_t ct)
{
    battle_t *b;
    int rc;
    b = malloc(sizeof(battle_t));

    if(b == NULL)
    {
        fprintf(stderr, "Could not allocate memory for battle struct\n");
        return NULL;
    }

    rc = battle_init(b, p, ene, env, ct);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize battle struct\n");
        return NULL;
    }

    return b;
}

/* See battle_state.h */
int battle_init(battle_t *b, character_t *p, character_t *ene,
    environment_t env, char_t ct)
{
    assert(b != NULL);

    b->player = p;
    b->enemy = ene;
    b->environment = env;
    b->turn = ct;

    return SUCCESS;
}

/* See battle_state.h */
int free_battle(battle_t *b)
{
    assert(b != NULL);

    free_characters(b->player);
    free_characters(b->enemy);
    free(b);

    return SUCCESS;
}

