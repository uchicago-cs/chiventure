#include <stdio.h>

#include "wdl/load_npc.h"

/* See load_item.h */
int load_npcs(obj_t *doc, game_t *g)
{
    // we use extract_objects() instead of obj_list_attr() because the former does type checking
    obj_t *npcs_obj = extract_objects(doc, "NPCS");
    if (npcs_obj == NULL)
    {
        fprintf(stderr, "NPCs fail type checking\n");
    }

    // if NPC list is empty then return -1
    if (npcs_obj == NULL)
    {
        fprintf(stderr, "NPCs list is empty\n");
        return FAILURE;
    }

    // while list of NPCs exists, create new NPC, add NPC to room
    obj_t *curr, *tmp;
    HASH_ITER(hh, npcs_obj->data.obj.attr, curr, tmp)
    {
        // get id, short_desc, and long_desc
        char *id = curr->id;
        char *short_desc = obj_get_str(curr, "short_desc");
        char *long_desc = obj_get_str(curr, "long_desc");
        int health = obj_get_int(curr, "health");

        // create new NPC
        npc_t *npc = npc_new(id, short_desc, long_desc, health, NULL, NULL);

        // load dialogue into NPC
        if(load_dialogue(curr, npc) == FAILURE)
        {
            fprintf(stderr, "Dialogue was not loaded properly\n");
            return FAILURE;
        }

        // retrieve the pointer for the room that the NPC is located in
        // room_t *item_room = find_room_from_game(g, in);

        // add NPC to game
        // add_item_to_room(item_room, item);
    }
    return SUCCESS;
}


/* See load_npc.h */
int load_dialogue(obj_t *npc_obj, npc_t *npc)
{
    convo_t *convo = convo_new();

    obj_t *dialogue = get_npc_dialogue(npc_obj);
    if (dialogue == NULL)
    {
        fprintf(stderr, "Dialogue fails type checking, nodes/edges are missing, "
                "or one of the node/edge attributes (id, npc_dialogue, quip, "
                "from_id, to_id) are missing.\n");
        return FAILURE;
    }

    obj_t *nodes_obj = obj_get_attr(dialogue, "nodes", false);
    obj_t *edges_obj = obj_get_attr(dialogue, "edges", false);
    char *id, *npc_dialogue;
    char *quip, *from_id, *to_id;
    obj_t *curr;

    DL_FOREACH(nodes_obj->data.lst, curr)
    {
        id = obj_get_str(curr, "id");
        npc_dialogue = obj_get_str(curr, "npc_dialogue");

        if (add_node(convo, id, npc_dialogue) != SUCCESS) {
            fprintf(stderr, "Could not add node.\n");
            return FAILURE;
        }
    }

    DL_FOREACH(edges_obj->data.lst, curr)
    {
        quip = obj_get_str(curr, "quip");
        from_id = obj_get_str(curr, "from_id");
        to_id = obj_get_str(curr, "to_id");

        if (add_edge(convo, quip, from_id, to_id) != SUCCESS) {
            fprintf(stderr, "Could not add edge.\n");
            return FAILURE;
        }
    }

    if (add_convo_to_npc(npc, convo) != SUCCESS) {
        fprintf(stderr, "Could not add convo to NPC.\n");
        return FAILURE;
    }

    return SUCCESS;
}
