#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "npc/dialogue_alt.h"


scene* scenes = NULL; 

convo_t *
convo_init (int num_nodes, int num_edges)
{
  convo_t *c = malloc (sizeof(convo_t) + num_nodes * sizeof(node_t*));
  c->node_count = 0;
  /*
  for (int i = 0; i < num_nodes; ++i){
    c->head[i] = calloc (1, (sizeof(c) * num_nodes) + sizeof(*c->head[i]));
  }
    
  for (int j = 0, k = 0; k < num_edges && j < num_nodes; ++k) {
    c->head[j]->connections[k] = 
    calloc(1, sizeof(*c->head[j]->connections[k]));

    if (k == num_edges - 1 && j < num_nodes) { 
        k = -1; 
        ++j;
    }
  }*/ 
  return c;
}


void
set_node (convo_t * c, char *dialogue, char*  tag, int num_nodes)
{
    scene* s;
    HASH_FIND(scenes, &tag, s)
    if (s != NULL) { 
	return FAILURE; 
    } 
 
    sc->id = tag; 
    sc->scene_num = c->node_count; 
    HASH_ADD(scenes, id, s); 

    c->head[c->node_count] = 
    calloc (1, (sizeof(c) * num_nodes) + sizeof(*c->head[c->node_count]));

/*
    if(used == NULL) { 
      used = malloc(num_nodes*sizeof(int)); 
      memset(used, ~0, num_nodes*sizeof(int));
    }

    for(int i = 0; i < num_nodes; i++) { 
        if(used[i] == tag) { 
          printf("ERROR: TODO"); 
          return; 
        } 
        else if (used[i] == -1) { 
          used[i] = tag; 
          break; 
        }
    }
*/
  c->head[c->node_count]->tag = tag;
  c->head[c->node_count++]->dialog = dialogue;

  /*
  if (used[num_nodes -1] != -1) { 
    for (int i = 0; i < num_nodes; i++) {
      for (int j = 0; j < num_nodes; j++) {
        if (c->head[j]->tag > c->head[i]->tag) {
          int tmp = c->head[i]->tag;         
				  c->head[i]->tag = c->head[j]->tag;            
				  c->head[j]->tag = tmp;             
	}  
      }
    }
  } */
}

void
set_edge (convo_t * c, char* from, enum char* toward,
	  char *keyword, char *quip, int num_nodes)
{
  scene* scene1; 
  scene* scene2;
  /*
  if (HASH_COUNT(scenes) != num_nodes) {
    return; 
    // TODO: systematize errors 
  }
  */ 

  HASH_FIND(scenes, &from, scene1); 
  HASH_FIND(scene, &toward, scene2);


  if(scene1 == NULL || scene2 == NULL) { 
    return; 
  }
 
        
  int fr = scene1->scene_num;
  int tw = scene2->scene_num; 
    
  c->head[j]->connections[k] = 
  calloc(1, sizeof(*c->head[j]->connections[k]));

  int index = c->head[fr]->connection_count;
  c->head[fr]->connections[index]->toward = c->head[tw];
  c->head[fr]->connections[index]->keyword = keyword;
  c->head[fr]->connections[index]->quip = quip;
  c->head[fr]->connection_count++; 
}
