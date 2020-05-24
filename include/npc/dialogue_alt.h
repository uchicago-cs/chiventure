#ifndef _DIALOGUE_ALT_H
#define _DIALOGUE_ALT_H



int* used = NULL; 


typedef struct convo
{
  int node_count;	
  struct node *head[];
} convo_t;

typedef struct node
{
  enum scene tag;
  char *dialog;
  int connection_count;
  struct edge *connections[];
} node_t;

typedef struct edge
{
  node_t *toward;
  char *keyword;
  char *quip;
} edge_t;










convo_t* convo_init (int num_nodes, int num_edges); 



void set_node (convo_t * c, char *dialogue, enum scene tag, int num_nodes); 


void set_edge (convo_t * c, enum scene from, enum scene toward,
	  char *keyword, char *quip, int num_nodes);




#endif 
