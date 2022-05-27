#include "wdl/load_npc.h"

/* load_npc_inventory
 * loads the NPC's inventory
 *
 * parameters:
 * - inventory_lst_obj: list of item IDs
 * - npc: an NPC
 * - g: game (required for access to all_items)
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_npc_inventory(obj_t *inventory_lst_obj, npc_t *npc, game_t *g)
{
    char *item_id;
    item_t *item;
    obj_t *curr;

    // verify the inventory list's attributes
    if (list_type_check(inventory_lst_obj, inventory_type_check) != SUCCESS) {
        fprintf(stderr, "NPC's inventory fails type checking. NPC: %s\n",
                npc->npc_id);
        return FAILURE;
    }

    // check if each item is currently in the game, and if so, add them to the
    // NPC's inventory
    DL_FOREACH(inventory_lst_obj->data.lst, curr)
    {
        item_id = obj_get_str(curr, "item_id");

        item = get_item_from_game(g, item_id);
        if (item == NULL) {
            fprintf(stderr, "Failed to add item to NPC. Item %s could not be "
                    "found. NPC: %s\n", item_id, npc->npc_id);
            return FAILURE;
        }

        if (add_item_to_npc(npc, item) != SUCCESS) {
            fprintf(stderr, "Failed to add item %s to NPC: %s\n", item_id,
                    npc->npc_id);
            return FAILURE;
        }
    }

    return SUCCESS;
}

/* load_node_actions
 * loads node actions into the given node
 *
 * parameters:
 * - actions_obj: the actions object
 * - convo: a convo
 * - node_id: the node's ID
 * - npc: the NPC (for item checking)
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_node_actions(obj_t *actions_obj, convo_t *convo, char *node_id,
                      npc_t *npc)
{
    char *action, *action_id;
    obj_t *curr;

    // verify the node action list's attributes
    if (list_type_check(actions_obj, node_action_type_check) != SUCCESS) {
        fprintf(stderr, "Node actions fail type checking. Node: %s. NPC: %s\n",
                node_id, npc->npc_id);
        return FAILURE;
    }

    // add the actions to the node
    DL_FOREACH(actions_obj->data.lst, curr)
    {
        action = obj_get_str(curr, "action");
        action_id = obj_get_str(curr, "action_id");

        if (strcmp(action, "GIVE_ITEM") == 0) {
            // check if the item is present in the NPC's inventory, and if so,
            // add the GIVE_ITEM flag to the node
            if (item_in_npc_inventory(npc, action_id) == false) {
                fprintf(stderr, "[Node actions] The item you intend to give "
                        "to the player is missing from the NPC's inventory. "
                        "Node: %s. NPC: %s\n", node_id, npc->npc_id);
                return FAILURE;
            }
            add_give_item(convo, node_id, action_id);
        }
        else if (strcmp(action, "TAKE_ITEM") == 0) {
            add_take_item(convo, node_id, action_id);
        }
        else {
            fprintf(stderr, "Specified action not currently supported. "
                    "Action: %s. Node ID: %s\n", action, node_id);
            return FAILURE;
        }
    }

    return SUCCESS;
}

/* load_dialogue
 * loads dialogue into the given NPC
 *
 * parameters:
 * - dialogue_obj: the dialogue object
 * - npc: an NPC
 * - g: game (for load_quest_dialogue to build conditions)
 *
 * returns:
 * - A convo initialized by the dialogue obj OR NULL if there is an error
 */
convo_t *load_dialogue(obj_t *dialogue_obj, npc_t *npc, game_t *g)
{
    convo_t *convo = convo_new();

    // verify the dialogue object's attributes
    if (dialogue_type_check(dialogue_obj) == FAILURE) {
        fprintf(stderr, "Dialogue object failed typechecking, or the two "
                "required attributes (nodes, edges) are missing. NPC: %s\n",
                npc->npc_id);
        return NULL;
    }

    obj_t *nodes_obj = obj_get_attr(dialogue_obj, "nodes", false);
    obj_t *edges_obj = obj_get_attr(dialogue_obj, "edges", false);
    char *id, *npc_dialogue;
    char *quip, *from_id, *to_id;
    obj_t *curr;
    obj_t *actions_obj;
    obj_t *conditions_obj;
    condition_t *conditions;

    // build nodes
    DL_FOREACH(nodes_obj->data.lst, curr)
    {
        id = obj_get_str(curr, "id");
        npc_dialogue = obj_get_str(curr, "npc_dialogue");

        // create node
        if (add_node(convo, id, npc_dialogue) != SUCCESS) {
            fprintf(stderr, "Could not add node with ID: %s. NPC: %s\n", id,
                    npc->npc_id);
            return NULL;
        }

        // load node actions, if any
        if ((actions_obj = obj_get(curr, "actions")) != NULL) {
            if (load_node_actions(actions_obj, convo, id, npc) != SUCCESS) {
                fprintf(stderr, "Could not add actions to node with ID: %s. "
                        "NPC: %s\n", id, npc->npc_id);
                return NULL;
            }
        }
    }

    // build edges
    DL_FOREACH(edges_obj->data.lst, curr)
    {
        quip = obj_get_str(curr, "quip");
        from_id = obj_get_str(curr, "from_id");
        to_id = obj_get_str(curr, "to_id");

        conditions = NULL;

        // build conditions, if any
        if ((conditions_obj = obj_get(curr, "conditions")) != NULL) {
            if ((conditions = build_conditions(conditions_obj, g)) == NULL) {
                fprintf(stderr, "Could not build conditions on edge with "
                        "quip: %s. NPC: %s\n", quip, npc->npc_id);
                return NULL;
            }
        }
        // create edge
        if (add_edge(convo, quip, from_id, to_id, conditions) != SUCCESS) {
            fprintf(stderr, "Could not add edge with quip: %s. NPC: %s\n",
                    quip, npc->npc_id);
            return NULL;
        }
    }
    return convo;
}


/* Loads all of the npc's quests into the game
 *
 * Parameters:
 * - npc_obj: an NPC WDL object
 * - npc: the initialized NPC adding the questss to
 * - g: the game struct
 * 
 * Returns:
 * - SUCCESS on success, FAILURE if an error occurs
*/
int load_npc_quests(obj_t *npc_obj, npc_t *npc, game_t *g)
{
    obj_t *quests_list = obj_get_list(npc_obj, "Quests");
    if(quests_list == NULL) {
        fprintf(stderr, "NPC has no quests, but this may not be an error");
        return SUCCESS;
    }
    obj_t *cur;
    DL_FOREACH(quests_list, cur) {
        char *id = obj_get_str(cur, "Quest Name");
        obj_t *quest_dialogue_obj = obj_get(cur, "Dialogue"); 
        convo_t *convo = load_dialogue(quest_dialogue_obj, npc, g);
        npc_quest_t *cur_quest = npc_quest_new(id, convo);
        npc_quest_list_add(npc->quests, cur_quest);
    }
    return SUCCESS;
}

/* Loads all of the npc's tasks into the game
 *
 * Parameters:
 * - npc_obj: an NPC WDL object
 * - npc: the initialized NPC adding the tasks to
 * - g: the game struct
 * 
 * Returns:
 * - SUCCESS on success, FAILURE if an error occurs
*/
int load_npc_tasks(obj_t *npc_obj, npc_t *npc, game_t *g)
{
    obj_t *tasks_list = obj_get_list(npc_obj, "Tasks");
    if(tasks_list == NULL) {
        fprintf(stderr, "NPC has no tasks, but this may not be an error");
        return SUCCESS;
    }
    obj_t *cur;
    DL_FOREACH(tasks_list, cur) {
        char *id = obj_get_str(cur, "Task Name");
        obj_t *task_dialogue_obj = obj_get(cur, "Dialogue"); 
        convo_t *convo = load_dialogue(task_dialogue_obj, npc, g);
        npc_task_t *cur_task = npc_task_new(id, convo);
        npc_task_list_add(npc->tasks, cur_task);
    }
    return SUCCESS;
}

/* See load_npc.h */
int load_npcs(obj_t *doc, game_t *g)
{
    // get and verify NPCS object
    obj_t *npcs_obj = obj_get_attr(doc, "NPCS", false);
    if (npcs_obj == NULL) {
        // the game has no NPCs
        return SUCCESS;
    }
    else if (list_type_check(npcs_obj, npc_type_check) != SUCCESS) {
        fprintf(stderr, "NPCS fail type checking\n");
        return FAILURE;
    }

    // iterate through the hash table of NPCs
    obj_t *curr, *tmp;
    HASH_ITER(hh, npcs_obj->data.obj.attr, curr, tmp)
    {
        // get attributes
        char *id = curr->id;
        char *short_desc = obj_get_str(curr, "short_desc");
        char *long_desc = obj_get_str(curr, "long_desc");

        // create the NPC
        npc_t *npc = npc_new(id, short_desc, long_desc, NULL, NULL, 0);
        if (npc == NULL) {
            fprintf(stderr, "Could not create NPC. NPC: %s\n", id);
            return FAILURE;
        }

        // load NPC's inventory, if any
        obj_t *inventory_lst_obj;
        if ((inventory_lst_obj = obj_get(curr, "inventory")) != NULL) {
            if (load_npc_inventory(inventory_lst_obj, npc, g) != SUCCESS) {
                fprintf(stderr, "Could not load NPC's inventory. NPC: %s\n",
                        id);
                return FAILURE;
            }
        }

        // load dialogue, if any
        obj_t *dialogue_obj;
        if ((dialogue_obj = obj_get(curr, "dialogue")) != NULL) {
            convo_t *convo = load_dialogue(dialogue_obj, npc, g);
            // assign the conversation to the NPC
            if (convo != NULL && add_convo_to_npc(npc, convo) != SUCCESS) {
                fprintf(stderr, "Could not add convo to NPC: %s\n", npc->npc_id);
                return FAILURE;
            }
        }

        // load class
        // to do

        // load movement
        // to do

        // load battle
        // to do

        // load quests
        if (load_npc_quests(curr, npc, g) != SUCCESS) {
            fprintf(stderr, "Quests were not loaded properly. NPC: %s\n",
                    id);
            return FAILURE;
        }

        // load tasks
        if (load_npc_tasks(curr, npc, g) != SUCCESS) {
            fprintf(stderr, "Quests were not loaded properly. NPC: %s\n",
                    id);
            return FAILURE;
        }

        // add NPC to the game
        add_npc_to_game(g, npc);

        // add NPC to the room they are assigned
        char *in = obj_get_str(curr, "in");
        room_t *room = find_room_from_game(g, in);
        if (room == NULL) {
            fprintf(stderr, "Room that NPC belongs to could not be found. "
                    "Room: %s. NPC: %s\n", in, id);
            return FAILURE;
        }
        add_npc_to_room(room->npcs, npc);
    }


    return SUCCESS;
}
