#include <stdio.h>
#include <stdlib.h>
#include <string.h>





convo_t *
convo_init (int num_nodes, int num_edges)
{
  convo_t *c = malloc (104);
  /* TODO: Fix memory allocation
           and problems associated 
	   with flexible member arrays */
  c->node_count = 0;
  
  for (int i = 0; i < num_nodes; ++i){
    c->head[i] = calloc (1, sizeof (*c->head[i]));
  }
    
  for (int j = 0, k = 0; k < num_edges && j < num_nodes; ++k) {
    c->head[j]->connections[k] = 
    calloc(1, sizeof(*c->head[j]->connections[k]));

    if (k == num_edges - 1 && j < num_nodes) { 
        k = -1; 
        ++j;
    }
  }
  return c;
}


void
set_node (convo_t * c, char *dialogue, enum scene tag, int num_nodes)
{
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

  c->head[c->node_count]->tag = tag;
  c->head[c->node_count++]->dialog = dialogue;


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
  }
}

void
set_edge (convo_t * c, enum scene from, enum scene toward,
	  char *keyword, char *quip, int num_nodes)
{
  if (used[num_nodes - 1] == -1) {
    return; 
    // TODO: systematize errors 
  }

  int index = c->head[from]->connection_count;
  c->head[from]->connections[index]->toward = c->head[toward];
  c->head[from]->connections[index]->keyword = keyword;
  c->head[from]->connections[index++]->quip = quip;
}
