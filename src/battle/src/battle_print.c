#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_print.h"

#define BUFFER_SIZE (200) // copied from actionmanagement.c, changed to 200

/* see battle_print.h */
char *print_start_battle(battle_t *b)
{
    char *enemy_name = b->enemy->name;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;

    char *string = calloc(BUFFER_SIZE + 1, sizeof(char));

    snprintf(string, BUFFER_SIZE, "You have encountered %s!\n\n"
                    "Let the battle begin!\n",
                    enemy_name);

    int rc = print_hp(b, string);
    assert(rc == SUCCESS);

    return string;
}

/* see battle_print.h */
int print_hp(battle_t* b, char* string)
{
    int player_hp = b->player->stats->hp;

    int slen = strnlen(string);
    int n;

    char temp[BUFFER_SIZE + 1];

    n = snprintf(temp, BUFFER_SIZE, "-- Your HP: %d\n", player_hp);
    strncat(string, temp, BUFFER_SIZE - slen);
    slen += n;

    snprintf(temp, BUFFER_SIZE, "ENEMY HP\n");
    strncat(string, temp, BUFFER_SIZE - slen);
    slen += n;

    combatant_t *enemies = b->enemy;
    combatant_t *enemy_elt;
    DL_FOREACH(enemies, enemy_elt)
    {
        char* name = enemy_elt->name;
        int enemy_hp = enemy_elt->stats->hp;

        n = snprintf(temp, BUFFER_SIZE, "-- %s's HP: %d\n", name, enemy_hp);
        strncat(string, temp, BUFFER_SIZE - slen);
        slen += n;
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

    char *string = calloc(BUFFER_SIZE + 1, sizeof(char));

    snprintf(string, BUFFER_SIZE, "%s used %s! It did %d damage.\n",
                    combatant_name, move_name, damage);

    int rc = print_hp(b, string);
    assert(rc == SUCCESS);

    return string;
}

/* see battle_print.h */
char *print_battle_winner(battle_status_t status, int xp)
{
    char *string = calloc(BUFFER_SIZE + 1, sizeof(char));

    if (status == BATTLE_VICTOR_PLAYER)
    {
        snprintf(string, BUFFER_SIZE, "You've won! You gain %d XP!\n",xp);
    } else if (status == BATTLE_VICTOR_ENEMY)
    {
        snprintf(string, BUFFER_SIZE, "You have been defeated!\n");
    }

    return string;
}
