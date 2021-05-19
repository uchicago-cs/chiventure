#include "game-state/game.h"
#include "game-state/room.h"
#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "game-state/mode.h"

/* see game.h */
game_t *game_new(char *desc)
{
    game_t *game = malloc(sizeof(game_t));
    memset(game, 0, sizeof(game_t));
    game->start_desc = strndup(desc, MAX_START_DESC_LEN);

    /* read from the file using interface from WDL team */

    return game;
}

/* See game.h */
int game_quit(game_t *game)
{

    if (game != NULL)
    {
        game_free(game);
        return SUCCESS;
    }
    return FAILURE;
}

/* See game.h */
int add_player_to_game(game_t *game, player_t *player)
{
    player_t *check;
    HASH_FIND(hh, game->all_players, player->player_id,
              strnlen(player->player_id, MAX_ID_LEN), check);
    if (check != NULL)
    {
        return FAILURE; //this plauer id is already in use.
    }
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id,
                    strnlen(player->player_id, MAX_ID_LEN), player);
    return SUCCESS;
}

/* See game.h */
int add_room_to_game(game_t *game, room_t *room)
{
    room_t *check;
    HASH_FIND(hh, game->all_rooms, room->room_id, strnlen(room->room_id, MAX_ID_LEN),
              check);

    if (check != NULL)
    {
        return FAILURE; //this room id is already in use.
    }

    HASH_ADD_KEYPTR(hh, game->all_rooms, room->room_id, strnlen(room->room_id, MAX_ID_LEN),
                    room);
    return SUCCESS;
}

/* See game.h */
int add_item_to_game(game_t *game, item_t *item)
{
    int rc;
    
    rc = add_item_to_hash(&(game->all_items), item);
    
    return rc;
}

/* See game.h */
int add_final_room_to_game(game_t *game, room_t *final_room)
{
    room_t *check;
    HASH_FIND(hh, game->all_rooms, final_room->room_id,
              strnlen(final_room->room_id, MAX_ID_LEN),
              check); // checks if the room exists within the list of game rooms

    if (check == NULL)
    {
        fprintf(stderr, "add_final_room_to_game: this room does not exist"
                "in the list of rooms\n");
        return FAILURE;
    }
    game->final_room = final_room;
    if (game->final_room != NULL)
        return SUCCESS;
    return FAILURE;
}

/* See game.h */
int add_quest_to_game(game_t *game, quest_t *quest)
{
	quest_t *check;

	//call to get_quest function
	check = NULL; //dummy NULL for now

	if (check == NULL) 
	{
		return FAILURE; //quest id is already in the hash table
	}

	HASH_ADD_KEYPTR(hh, game->all_quests, quest->quest_id,
		            strlen(quest->quest_id, MAX_ID_LEN), quest);

	return SUCCESS;ss
}

/* See game.h */
int add_end_condition_to_game(game_t *game, condition_t *end_condition)
{
    int valid = valid_condition(game, end_condition);
    if(valid == SUCCESS){
        end_condition->next = game->end_conditions;
        game->end_conditions = end_condition;

        return SUCCESS;
    } else {
        return valid;
    }

}

/* See game.h */
int add_stat_to_game(game_t *game, stats_global_t *gs)
{
    stats_global_t *check;
    HASH_FIND(hh, game->curr_stats, gs->name, 
              strlen(gs->name), check);

    if (check != NULL)
    {
        return FAILURE; //the stat already exists in the game
    }

    HASH_ADD_KEYPTR(hh, game->curr_stats, gs->name,
                    strlen(gs->name), gs);
    return SUCCESS;
}

/* See game.h */
int add_effect_to_game(game_t *game, effects_global_t *effect)
{
    effects_global_t *check;
    HASH_FIND(hh, game->all_effects, effect->name, 
              strlen(effect->name), check);

    if (check != NULL)
    {
        return FAILURE; //the effect already exists in the game
    }

    HASH_ADD_KEYPTR(hh, game->all_effects, effect->name,
                    strlen(effect->name), effect);
    return SUCCESS;
}

/* See game.h */
bool end_conditions_met(game_t *game)
{
    if(game->end_conditions == NULL){
        return false;
    } else {
        return all_conditions_met(game->end_conditions);
    }
}

/* See game.h */
bool is_game_over(game_t *game)
{
    bool end_case1, end_case2, end_case3;
    
    /* end_case1: Both a final room and end conditions exist */
    end_case1 = game->final_room != NULL && game->final_room == game->curr_room && 
            end_conditions_met(game);
    /* end_case2: A final room exists, but end conditions do not */
    end_case2 = game->final_room != NULL && game->final_room == game->curr_room && 
            game->end_conditions == NULL;
    /* end_case3: End conditions exist, but a final room does not */
    end_case3 = game->final_room == NULL && end_conditions_met(game);
    
    return end_case1 || end_case2 || end_case3;
}

/* See game.h */
int create_connection(game_t *game, char* src_room, char* to_room,
			char* direction)
{
    room_t *src = find_room_from_game(game, src_room);
    if (src == NULL)
    {
        return ROOM_SRC_NULL;
    }
    room_t *to = find_room_from_game(game, to_room);
    if (to == NULL)
    {
        return ROOM_DEST_NULL;
    }
    path_t *connection = path_new(to, direction);
    int check = add_path_to_room(src, connection);
    return check;
}


/* See game.h */
int set_curr_player(game_t *game, player_t *player)
{
    game->curr_player = player;
    if (game->curr_player != NULL)
        return SUCCESS;
    return FAILURE;
}

/* See game.h */
player_t *get_player(game_t *game, char *player_id)
{
    player_t *s;
    HASH_FIND(hh, game->all_players, player_id,
              strnlen(player_id, MAX_ID_LEN), s);
    return s;
}

/* See game.h */
room_t *find_room_from_game(game_t *game, char* room_id)
{
    room_t *r;
    HASH_FIND(hh, game->all_rooms, room_id, strnlen(room_id, MAX_ID_LEN), r);
    return r;
}

/* See game.h */
item_t *get_item_from_game(game_t *game, char *item_id)
{
    item_t *i;
    HASH_FIND(hh, game->all_items, item_id, strnlen(item_id, MAX_ID_LEN), i);
    return i;
}

/* See game.h */
int move_room(game_t *game, room_t *new_room)
{
    if(game == NULL)
    {
        return GAME_NULL;
    }
    if(new_room == NULL)
    {

        return ROOM_NULL;
    }
    room_t *check = find_room_from_game(game, new_room->room_id);
    if(check == NULL)
    {
        return FAILURE;
    }
    if(new_room == game->final_room) {
        game->curr_room = new_room;
        return FINAL_ROOM;
    }
    game->curr_room = new_room;
    return SUCCESS;
}

/* See game.h */
int game_free(game_t *game)
{
    delete_all_rooms(game->all_rooms);
    delete_all_players(game->all_players);
    delete_condition_llist(game->end_conditions);
    delete_all_items(&(game->all_items));
    game_mode_free(game->mode);
    free(game->start_desc);
    free(game);
    return SUCCESS;
}

/* See game.h */
room_list_t *get_all_rooms(game_t *game)
{
    room_list_t *head = NULL;
    room_t *ITTMP_ROOM, *curr_room;
    room_list_t *tmp;
    HASH_ITER(hh, game->all_rooms, curr_room, ITTMP_ROOM)
    {
        tmp = malloc(sizeof(room_list_t));
        tmp->room = curr_room;
        LL_APPEND(head, tmp);
    }
    return head;
}

/* See game.h */
int delete_room_llist(room_list_t *head)
{
    room_list_t *elt, *tmp;
    LL_FOREACH_SAFE(head, elt, tmp)
    {
        LL_DELETE(head, elt);
        free(elt);
    }
    return SUCCESS;
}

/* See game.h */
item_list_t *get_all_items_in_game(game_t *game)
{
    item_list_t *head;
    
    head = get_all_items_in_hash(&(game->all_items));
    
    return head;
}

/* see game.h */
int add_effect(game_t *game, char* action_name, char* item_src_name,
               char* item_modify_name, char* attribute_name, attribute_value_t new_value)
{

    item_t *item_src = get_item_from_game(game, item_src_name);
    if(item_src == NULL)
    {
        return ITEM_SRC_NULL;
    }
    item_t *item_modify = get_item_from_game(game, item_modify_name);
    if(item_modify == NULL)
    {
        return ITEM_MODIFY_NULL;
    }
    game_action_t *action = get_action(item_src, action_name);
    if(action == NULL)
    {
        return ACTION_NULL;
    }
    attribute_t *attribute = get_attribute(item_modify, attribute_name);
    if(attribute == NULL)
    {
        return ATTRIBUTE_NULL;
    }
    int check = add_action_effect(action, item_src, attribute, new_value);

    return check;
}

/* see game.h */
int add_condition(game_t *game, game_action_t *action, condition_t *condition)
{
    if(action == NULL)
    {
        return ACTION_NULL;
    }

    int valid = valid_condition(game, condition);
    if(valid == SUCCESS){
        int check = add_action_condition(action, condition);

        return check;
    } else {
        return valid;
    }
}
