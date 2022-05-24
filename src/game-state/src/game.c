#include "game-state/game.h"
#include "game-state/room.h"
#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "game-state/mode.h"
#include "npc/npc.h"
#include "battle/battle_flow_structs.h"
#include "cli/util.h"
#include "quests/quests_state.h"

/* see game.h */
game_t *game_new(char *desc)
{
    game_t *game = malloc(sizeof(game_t));
    memset(game, 0, sizeof(game_t));
    game->start_desc = strndup(desc, MAX_START_DESC_LEN);

    player_t *player1 = player_new("player1");
    add_player_to_game(game, player1);
    set_curr_player(game, player1);

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
        return FAILURE; //this player id is already in use.
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
    return add_item_to_all_items_hash(&(game->all_items), item);
}

/* See game.h */
int add_npc_to_game(game_t *game, npc_t *npc)
{
    npc_t *check;
    HASH_FIND(hh, game->all_npcs, npc->npc_id,
              strnlen(npc->npc_id, MAX_ID_LEN), check);

    if (check != NULL)
    {
        return FAILURE; //this npc id is already in use.
    }

    HASH_ADD_KEYPTR(hh, game->all_npcs, npc->npc_id,
                    strnlen(npc->npc_id, MAX_ID_LEN), npc);
    return SUCCESS;
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
quest_t *get_quest(game_t *game, char *quest_id)
{
    return get_quest_from_hash(quest_id, game->all_quests);
}

/* See game.h */
int add_quest_to_game(game_t *game, quest_t *quest)
{
    return add_quest_to_hash(quest, &game->all_quests);
}

/* See game.h */
int add_end_condition_to_game(game_t *game, condition_t *end_condition)
{
    int valid = valid_condition(game, end_condition);
    if(valid == SUCCESS)
    {
        end_condition->next = game->end_conditions;
        game->end_conditions = end_condition;

        return SUCCESS;
    }
    else
    {
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
int add_battle_ctx_to_game(game_t *game, battle_ctx_t *battle_ctx)
{
    if (battle_ctx == NULL)
    {
        return FAILURE;
    }

    game->battle_ctx = battle_ctx;

    return SUCCESS;
}

/* See game.h */
bool end_conditions_met(game_t *game)
{
    if(game->end_conditions == NULL)
    {
        return false;
    }
    else
    {
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
int create_connection(game_t *game, char *src_room, char *to_room,
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
room_t *find_room_from_game(game_t *game, char *room_id)
{
    char *room_id_case = case_insensitized_string(room_id);
    room_t *r;
    HASH_FIND(hh, game->all_rooms, room_id_case, strnlen(room_id_case, MAX_ID_LEN), r);
    free(room_id_case);
    return r;
}

/* See game.h */
item_t *get_item_from_game(game_t *game, char *item_id)
{
    item_t *i;
    char *insensitized_id = case_insensitized_string(item_id);
    HASH_FIND(hh_all_items, game->all_items, insensitized_id,
              strnlen(item_id, MAX_ID_LEN), i);
    free(insensitized_id);
    return i;
}

/* See game.h */
npc_t *get_npc(game_t *game, char *npc_id)
{
    npc_t *n;
    char *insensitized_id = case_insensitized_string(npc_id);
    HASH_FIND(hh, game->all_npcs, insensitized_id,
              strnlen(npc_id, MAX_ID_LEN), n);
    free(insensitized_id);
    return n;
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

    // Update quests on room transition
    for(player_hash_t *cur = game->all_players; cur != NULL; cur = cur->hh.next) {
        cur->crnt_room = new_room->room_id;
        quest_ctx_t *qctx = quest_ctx_new(cur, game->all_quests);
        update_player_quests(qctx);
    }

    if(new_room == game->final_room)
    {
        game->curr_room = new_room;
        return FINAL_ROOM;
    }
    game->curr_room = new_room;
    return SUCCESS;
}

/* Deletes the game->all_items hash table, as well as free all the individual
 * item structs.
 *
 * Parameters:
 *  pointer to the game->all_items hash table
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int delete_all_items_from_game(item_hash_t *all_items)
{
    item_t *current_item, *tmp;
    HASH_ITER(hh_all_items, all_items, current_item, tmp)
    {
        item_t *iter = current_item;

        while(iter != NULL)
        {
            current_item = iter;
            iter = current_item->next;

            remove_item_from_all_items_hash(&(all_items), current_item);
            item_free(current_item);
        }
    }
    all_items = NULL;
    return SUCCESS;
}

/* See game.h */
int game_free(game_t *game)
{
    delete_all_rooms(&(game->all_rooms));
    delete_all_players(game->all_players);
    delete_all_npcs(game->all_npcs);
    delete_condition_llist(game->end_conditions);
    delete_all_items_from_game(game->all_items);
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
int add_item_to_player(player_t *player, item_t *item, game_t *game)
{
    int rc = add_item_to_player_without_checks(player, item);
    quest_ctx_t *qctx = quest_ctx_new(player, game->all_quests);
    update_player_quests(qctx);
    quest_ctx_free(qctx);
    return rc;
}

/* See game.h */
item_list_t *get_all_items_in_game(game_t *game)
{
    item_list_t *head;

    head = get_all_items_in_hash(&(game->all_items));

    return head;
}

/* see game.h */
int add_effect(game_t *game, char *action_name, char *item_src_name,
               char *item_modify_name, char *attribute_name, attribute_value_t *new_value)
{
    item_t *item_src = get_item_from_game(game, item_src_name);
    agent_t *agent = malloc(sizeof(agent_t));
    agent->item = item_src;
    if(item_src == NULL)
    {
        return ITEM_SRC_NULL;
    }
    item_t *item_modify = get_item_from_game(game, item_modify_name);
    if(item_modify == NULL)
    {
        return ITEM_MODIFY_NULL;
    }
    game_action_t *action = get_action(agent, action_name);
    if(action == NULL)
    {
        return ACTION_NULL;
    }
    attribute_t *attribute = get_attribute(item_modify, attribute_name);
    if(attribute == NULL)
    {
        return ATTRIBUTE_NULL;
    }
    int check = add_action_effect(action, agent->item, attribute, new_value);

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
    if(valid == SUCCESS)
    {
        int check = add_action_condition(action, condition);

        return check;
    }
    else
    {
        return valid;
    }
}

/**********************************************
 *       DIALOGUE EXECUTION FUNCTIONS         *
 **********************************************/

/* Executes all actions on a node.
 *
 * Parameters:
 *  - n: node
 *  - game: the Chiventure game being run
 *
 * Returns:
 *  - SUCCESS if the action executed successfully, FAILURE if an error occured
 */
int do_node_actions(node_t *n, game_t *game)
{
    node_action_t *cur_action = n->actions;

    while (cur_action != NULL)
    {

        switch(cur_action->action)
        {

        case GIVE_ITEM:
            ;
            npc_t *npc = get_npc_in_room(game->curr_room,
                                         game->mode->mode_ctx);
            item_t *item = get_item_in_hash(npc->inventory,
                                            cur_action->action_id);
            if (item == NULL) return FAILURE;
            if (remove_item_from_npc(npc, item) != SUCCESS) return FAILURE;
            if (add_item_to_player(game->curr_player, item, game) != SUCCESS)
                return FAILURE;
            break;

        case TAKE_ITEM:
            npc = get_npc_in_room(game->curr_room, game->mode->mode_ctx);
            item = get_item_in_hash(game->curr_player->inventory,
                                    cur_action->action_id);
            if (item == NULL) return FAILURE;
            if (remove_item_from_player(game->curr_player, item) != SUCCESS)
                return FAILURE;
            if (add_item_to_npc(npc, item) != SUCCESS) return FAILURE;
            break;

        case START_QUEST:
            // to do
            break;

        case START_BATTLE:
            // to do
            break;

        default:
            return FAILURE;
        }

        cur_action = cur_action->next;
    }

    return SUCCESS;
}

/* Checks each edge and updates their availability status, then counts the
 * total number of available edges.
 *
 * Parameters:
 *  - n: node
 *
 * Returns:
 *  - SUCCESS if the action executed successfully, FAILURE if an error occured
 */
int update_edge_availabilities(node_t *n)
{
    if (n == NULL) return FAILURE;

    int num_avail_edges = 0;
    edge_list_t *cur_edge = n->edges;

    while (cur_edge != NULL)
    {
        if (cur_edge->availability != EDGE_DISABLED)
        {
            if (cur_edge->edge->conditions != NULL)
            {
                // true = 1 = EDGE_AVAILABLE, false = 0 = EDGE_UNAVAILABLE
                cur_edge->availability =
                    all_conditions_met(cur_edge->edge->conditions);
            }
            if (cur_edge->availability) num_avail_edges++;
        }
        cur_edge = cur_edge->next;
    }

    n->num_available_edges = num_avail_edges;

    return SUCCESS;
}

/* Creates a return string containing NPC dialogue and dialogue options
 * (to be printed by the CLI).
 *
 * SAMPLE OUTPUT:
 * Pick an item: a sword or a shield?
 * 1. Sword
 * 2. Shield
 * Enter your choice:
 *
 * Parameters:
 *  - n: pointer to a node
 *  - is_leaf: 1 or 0, indicating whether c->cur_node is a leaf
 *
 * Returns:
 *  - A string that can be directly printed by the CLI
 */
char *create_return_string(node_t *n, int is_leaf)
{
    char *input_prompt = "Enter your choice: ";
    int totlen = 0;
    int len_lst[n->num_available_edges + 2];
    edge_list_t *cur_edge = n->edges;
    int i = 0;
    int option_number = 1;

    // Compute buffer length
    totlen += (len_lst[i++] = strlen(n->npc_dialogue));
    totlen += 1;
    while (cur_edge != NULL)
    {
        if (cur_edge->availability == EDGE_AVAILABLE)
        {
            totlen += (int) log10(option_number++) + 1;
            totlen += (len_lst[i++] = strlen(cur_edge->edge->quip));
            totlen += 3;
        }
        cur_edge = cur_edge->next;
    }
    if (!is_leaf) totlen += (len_lst[i] = strlen(input_prompt));
    totlen += 1;

    // Create return string
    char *buf, *p;
    char temp[5];
    cur_edge = n->edges;
    i = 0;
    option_number = 1;

    if ((buf = malloc(sizeof(char) * totlen)) == NULL) return NULL;
    p = buf;

    memcpy(p, n->npc_dialogue, len_lst[i]);
    p += len_lst[i++];
    *p++ = '\n';
    while (cur_edge != NULL)
    {
        if (cur_edge->availability == EDGE_AVAILABLE)
        {
            sprintf(temp, "%d", option_number);
            memcpy(p, temp, (int) log10(option_number) + 1);
            p += (int) log10(option_number++) + 1;
            *p++ = '.';
            *p++ = ' ';
            memcpy(p, cur_edge->edge->quip, len_lst[i]);
            p += len_lst[i++];
            *p++ = '\n';
        }
        cur_edge = cur_edge->next;
    }
    if (!is_leaf)
    {
        memcpy(p, input_prompt, len_lst[i]);
        p += len_lst[i];
    }
    *p = '\0';

    return buf;
}

/* See game.h */
char *start_conversation(convo_t *c, int *rc, game_t *game)
{
    if (c == NULL)
    {
        *rc = -1;
        return NULL;
    }

    char *ret_str;

    // Step 1: Set current node to first node
    c->cur_node = c->all_nodes->node;

    // Step 2: Execute actions (item, quest, battle, etc.), if any
    if (do_node_actions(c->cur_node, game) != SUCCESS)
    {
        *rc = -1;
        return NULL;
    }

    // Step 3: Recheck the availability of each edge, count total avail. edges
    if (update_edge_availabilities(c->cur_node) != SUCCESS)
    {
        *rc = -1;
        return NULL;
    }

    // Step 4: Prepare return code and return string
    if (c->cur_node->num_available_edges == 0) *rc = 1;
    else *rc = 0;

    ret_str = create_return_string(c->cur_node, *rc);
    if (ret_str == NULL) *rc = -1;

    return ret_str;
}

/* See game.h */
char *run_conversation_step(convo_t *c, int input, int *rc, game_t *game)
{
    if (input > c->cur_node->num_available_edges)
        input = c->cur_node->num_available_edges;

    char *ret_str;
    edge_list_t *cur_edge;

    // Step 1: Traverse to the player's selected node
    cur_edge = c->cur_node->edges;
    // The logic here works as follows:
    // (1) We only decrement input when we encounter an available edge, until
    //     input become 1
    // (2) However, we could end up on an unavailable edge, which is where
    //     "|| cur_edge->availability != EDGE_AVAILABLE" comes in
    // (3) Overall, this code ensures that we arrive at the player's selected
    //     edge
    while (input > 1 || cur_edge->availability != EDGE_AVAILABLE)
    {
        if (cur_edge->availability == EDGE_AVAILABLE) input--;
        cur_edge = cur_edge->next;
    }

    c->cur_node = cur_edge->edge->to;

    // Step 2: Disable edge if the node it leads to has an action
    // NOTE: This is a temporary solution that prevents issues like being able
    //       to receive multiple copies of items, starting the same quest twice.
    //       This SHOULD be changed / made more complex in the future.
    if (c->cur_node->actions != NULL)
    {
        cur_edge->availability = EDGE_DISABLED;
    }

    // Step 3: Execute actions (item, quest, battle, etc.), if any
    if (do_node_actions(c->cur_node, game) != SUCCESS)
    {
        *rc = -1;
        return NULL;
    }

    // Step 4: Recheck the availability of each edge, count total avail. edges
    if (update_edge_availabilities(c->cur_node) != SUCCESS)
    {
        *rc = -1;
        return NULL;
    }

    // Step 5: Prepare return code and return string
    if (c->cur_node->num_available_edges == 0) *rc = 1;
    else *rc = 0;

    ret_str = create_return_string(c->cur_node, *rc);
    if (ret_str == NULL) *rc = -1;

    return ret_str;
}

