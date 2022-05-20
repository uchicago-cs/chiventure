#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "battle/battle_moves.h"


/* See battle_moves.h */
int move_init(move_t* move, int id, char* name, char* info, damage_type_t dmg_type,
                 target_type_t stat_mods, target_type_t effects, target_count_t count,
                 int sp_cost, battle_item_t* req_item, int damage, int accuracy,
                 stat_changes_t* user_mods, stat_changes_t* opponent_mods, move_t* prev,
                 move_t* next)
{
    assert(move != NULL);

    move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
    strncpy(move->info, info, MAX_MOVE_INFO_LEN + 1);

    move->id = id;
    move->name = name;

    move->req_item = req_item;

    move->dmg_type = dmg_type;

    move->stat_mods = stat_mods;
    move->effects = effects;

    move->count = count;

    move->user_mods = user_mods;
    move->opponent_mods = opponent_mods;

    move->damage = damage;
    move->accuracy = accuracy;
    move->sp_cost = sp_cost;

    move->next = next;
    move->prev = prev;

    return SUCCESS;
}


/* See battle_moves.h */
move_t* move_new(int id, char* name, char* info, damage_type_t dmg_type,
                 target_type_t stat_mods, target_type_t effects, target_count_t count,
                 int sp_cost, battle_item_t* req_item, int damage, int accuracy,
                 stat_changes_t* user_mods, stat_changes_t* opponent_mods, move_t* prev,
                 move_t* next)
{
    move_t *move;
    int rc;
    move = calloc(1, sizeof(move_t));

    if(move == NULL)
    {
        fprintf(stderr, "Could not allocate memory for move\n");
        return NULL;
    }

    rc = move_init(move, id, name, info, dmg_type, stat_mods, effects, count,
		    sp_cost, req_item, damage, accuracy, user_mods, opponent_mods, NULL, NULL);

    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize move\n");
        return NULL;
    }

    return move;
}


/* See battle_moves.h */
int move_free(move_t *move)
{
    if (move == NULL)
    {
        return SUCCESS;
    }

    battle_item_t *req_item_elt, *req_item_tmp;
    DL_FOREACH_SAFE(move->req_item, req_item_elt, req_item_tmp)
    {
        DL_DELETE(move->req_item, req_item_elt);
        free(req_item_elt);
    }

    stat_changes_t *user_mods_elt, *user_mods_tmp;
    DL_FOREACH_SAFE(move->user_mods, user_mods_elt, user_mods_tmp)
    {
        DL_DELETE(move->user_mods, user_mods_elt);
        free(user_mods_elt);
    }

    stat_changes_t *opponent_mods_elt, *opponent_mods_tmp;
    DL_FOREACH_SAFE(move->opponent_mods, opponent_mods_elt, opponent_mods_tmp)
    {
        DL_DELETE(move->opponent_mods, opponent_mods_elt);
        free(opponent_mods_elt);
    }

    free(move);

    return SUCCESS;
}


 /* Creates test move for bard
  *
  * Parameters:
  *  none, values are hard coded in
  *
  * Returns:
  *  - A pointer to the test move
  *
  */
move_t *test_move_bard()
{
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
    strncpy(move->info, "Diss track", MAX_MOVE_INFO_LEN + 1);

    move->id = 100;
    move->name = "";

    move->req_item = NULL;

    move->dmg_type = MAG;

    move->stat_mods = NO_TARGET;
    move->effects = NO_TARGET;

    move->count = 0;

    move->user_mods = NULL;
    move->opponent_mods = NULL;

    move->damage = 15;
    move->accuracy = 100;
    move->sp_cost = 10;

    return move;
}


/* Creates test move for cleric
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to the test move
 *
 */
move_t *test_move_cleric()
{
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
    strncpy(move->info, "Divine smite", MAX_MOVE_INFO_LEN + 1);

    move->id = 110;
    move->name = "";

    move->req_item = NULL;

    move->dmg_type = MAG;

    move->stat_mods = NO_TARGET;
    move->effects = NO_TARGET;

    move->count = 0;

    move->user_mods = NULL;
    move->opponent_mods = NULL;

    move->damage = 10;
    move->accuracy = 100;
    move->sp_cost = 15;

    return move;
}


/* Creates test move for paladin
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to the test move
 *
 */
move_t *test_move_paladin()
{
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
    strncpy(move->info, "360 no scope", MAX_MOVE_INFO_LEN + 1);
    
    move->id = 120;
    move->name = "";

    move->req_item = NULL;

    move->dmg_type = PHYS;

    move->stat_mods = NO_TARGET;
    move->effects = NO_TARGET;

    move->count = 0;

    move->user_mods = NULL;
    move->opponent_mods = NULL;

    move->damage = 20;
    move->accuracy = 100;
    move->sp_cost = 0;

    return move;
}


/* Creates test move for wizard
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to the test move
 *
 */
move_t *test_move_wizard()
{
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
    strncpy(move->info, "Fireball", MAX_MOVE_INFO_LEN);
    
    move->id = 130;
    move->name = "";

    move->req_item = NULL;
    
    move->dmg_type = MAG;

    move->stat_mods = NO_TARGET;
    move->effects = NO_TARGET;

    move->count = 0;

    move->user_mods = NULL;
    move->opponent_mods = NULL;

    move->damage = 10;
    move->accuracy = 100;
    move->sp_cost = 10;

    return move;
}
