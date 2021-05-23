#include <stdio.h>

#include "wdl/load_npc.h"

/* See load_item.h */
int load_npcs(obj_t *doc, game_t *g)
{
    // 
    obj_t *npcs_obj = obj_get_attr(doc, "NPCS", false);
    if (npcs_obj == NULL)
    {
        fprintf(stderr, "NPCs not found\n");
        return FAILURE;
    }
    else if (list_type_check(npcs_obj, npc_type_check) == FAILURE)
    {
        fprintf(stderr, "NPCs fail type checking\n");
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

        add_npc_to_game(g, npc);
    }
    return SUCCESS;
}


/* See load_npc.h */
int load_dialogue(obj_t *npc_obj, npc_t *npc)
{
    convo_t *convo = convo_new();

    // get and verify the dialogue object
    obj_t *dialogue_obj = obj_get_attr(npc_obj, "dialogue", false);
    if (dialogue_obj == NULL)
    {
        fprintf(stderr, "dialogue could not be found for NPC: %s\n",
                npc->npc_id);
        return FAILURE;
    }
    else if (dialogue_type_check(dialogue_obj) == FAILURE)
    {
        fprintf(stderr, "Dialogue object failed typechecking, or the two "
                "required attributes (nodes, edges) are missing, for NPC: %s\n",
                npc->npc_id);
        return FAILURE;
    }

    // build the nodes and edges of the conversation
    obj_t *nodes_obj = obj_get_attr(dialogue_obj, "nodes", false);
    obj_t *edges_obj = obj_get_attr(dialogue_obj, "edges", false);
    char *id, *npc_dialogue;
    char *quip, *from_id, *to_id;
    obj_t *curr;

    DL_FOREACH(nodes_obj->data.lst, curr)
    {
        id = obj_get_str(curr, "id");
        npc_dialogue = obj_get_str(curr, "npc_dialogue");

        if (add_node(convo, id, npc_dialogue) != SUCCESS) {
            fprintf(stderr, "Could not add node with ID: %s. NPC: %s\n", id,
                    npc->npc_id);
            return FAILURE;
        }
    }

    DL_FOREACH(edges_obj->data.lst, curr)
    {
        quip = obj_get_str(curr, "quip");
        from_id = obj_get_str(curr, "from_id");
        to_id = obj_get_str(curr, "to_id");

        if (add_edge(convo, quip, from_id, to_id) != SUCCESS) {
            fprintf(stderr, "Could not add edge with quip: %s. NPC: %s\n",
                    quip, npc->npc_id);
            return FAILURE;
        }
    }

    // assign the conversation to the NPC
    if (add_convo_to_npc(npc, convo) != SUCCESS) {
        fprintf(stderr, "Could not add convo to NPC: %s\n", npc->npc_id);
        return FAILURE;
    }

    return SUCCESS;
}
