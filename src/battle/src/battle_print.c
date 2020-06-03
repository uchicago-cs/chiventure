#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_print.h"

#define BUFFER_SIZE (100) // copied from actionmanagement.c

/* see battle_print.h */
char *print_start_battle(battle_t *b)
{
    char *enemy_name = b->enemy->name;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;

    /* Setting up malloced string - Taken from actionmanagement.c */
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    sprintf(string, "You have encountered %s!\n\n"
                    "Let the battle begin!\n",
                    enemy_name);

    int rc = print_hp(b,string);

    return string;
}

/* see battle_print.h */
int *print_hp(battle_t* b, char* string)
{
    combatant_t *player_hp = b->player->stats->hp;
    string += sprintf(string, "-- Your HP: %d\n", player_hp);

    combatant_t *enemies = b->enemy;
    combatant_t *enemy_elt;
    DL_FOREACH(enemies, enemy_elt)
    {
        char* name = enemy_elt->name;
        char* enemy_hp = enemy_elt->stats->hp;

        string += sprintf(string, "-- %s's HP: %d\n", name, enemy_hp);
    }

    return SUCCESS;
}

/* see battle_print.h */
char *print_battle_move(battle_t *b, turn_t turn, move_t *move)
{
    char *move_name = move->info;
    int damage = move->damage;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;
    char* enemy_name = b->enemy->name;
    char* combatant_name;

    if (turn == PLAYER)
    {
        combatant_name = "You";
    } else
    {
        combatant_name = enemy_name;
    }

    /* Setting up malloced string - Taken from actionmanagement.c */
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    sprintf(string, "%s used %s! It did %d damage.\n",
                    combatant_name, move_name, damage);

    int rc = print_hp(b,string);

    return string;
}

/* see battle_print.h */
char *print_battle_winner(battle_status_t status, int xp)
{
    /* Setting up malloced string - Taken from actionmanagement.c */
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    if (status == BATTLE_VICTOR_PLAYER)
    {
        sprintf(string,"You've won! You gain %d XP!\n",xp);
    } else if (status == BATTLE_VICTOR_ENEMY)
    {
        sprintf(string,"You have been DEFEATED.\n");
    }

    return string;
}
