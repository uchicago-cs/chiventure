 /*Team RPG-Openworld
 * 
 * autogenerate.c: This file. Function definitions of the functions 
 * specified in chiventure/include/autogenerate.h
 * 
 * Room module that autogenerates string of rooms connected via paths when 
 * a "dead-end" room is entered
 * 
 * See chiventure/include/autogenerate.h header file to see function 
 * prototypes and purposes
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "openworld/gen_structs.h"

/* see gen_structs.h */
int init_gencontext(gencontext_t *context, path_t *open_paths, int level, int num_open_paths, speclist_t *speclist){
    
    if (context == NULL)
        return FAILURE;

    context->level = level;
    context->open_paths = open_paths;
    context->num_open_paths = num_open_paths;
    context->speclist = speclist;
    return SUCCESS;
}


/* see gen_structs.h */
gencontext_t* gencontext_new(path_t *open_paths, int level, int num_open_paths, speclist_t *speclist){

    gencontext_t *contextnew = calloc(1, sizeof(gencontext_t));
     
    if (contextnew == NULL){
        fprintf(stderr, "calloc failed to allocate space for contextnew. \n");
        return NULL;
    }

    init_gencontext(contextnew, open_paths, level, num_open_paths, speclist);
    return contextnew;
}

/* see gen_structs.h */
int gencontext_free(gencontext_t *context){

    if (context == NULL)
	return FAILURE;

    free(context);
    return SUCCESS;
}

/* see gen_structs.h */
int roomspec_free(roomspec_t *spec){

    if (spec == NULL)
        return FAILURE;

    if (spec->short_desc){
	free(spec->short_desc);
    }

    if (spec->long_desc){
        free(spec->long_desc);
    }

    free(spec);
    return SUCCESS;
}

/* see gen_structs.h */
int init_roomspec(roomspec_t *spec, char *short_desc, char *long_desc, item_hash_t *items){
    
    if (spec == NULL)
	return FAILURE;

    spec->short_desc = calloc(MAX_SDESC_LEN + 1, sizeof(char));
    if (spec->short_desc == NULL){
	roomspec_free(spec);
	fprintf(stderr, "calloc failed to allocate space for spec's short_desc. \n");
	return FAILURE;
    }

    spec->long_desc = calloc(MAX_LDESC_LEN + 1, sizeof(char));
    if (spec->long_desc == NULL){
        roomspec_free(spec);
        fprintf(stderr, "calloc failed to allocate space for spec's short_desc. \n");
        return FAILURE;
    }

    strncpy(spec->short_desc, short_desc, MAX_SDESC_LEN);
    strncpy(spec->long_desc, long_desc, MAX_LDESC_LEN);   
    spec->items = items;
    return SUCCESS;
}

/* see gen_structs.h */
roomspec_t* roomspec_new(char *short_desc, char *long_desc, item_hash_t *items){

    roomspec_t *roomspecnew = calloc(1, sizeof(roomspec_t));

    if (roomspecnew == NULL){
        fprintf(stderr, "calloc failed to allocate space for roomspecnew. \n");
        return NULL;
    }

    init_roomspec(roomspecnew, short_desc, long_desc, items);
    return roomspecnew;
}

/* see gen_structs.h */
int init_speclist(speclist_t *list, roomspec_t *spec){

    if (list == NULL)
	return FAILURE;
    
    list->spec = spec;
    list->prev = NULL;
    list->next = NULL;
    return SUCCESS;
}

/* see gen_structs.h */
speclist_t* speclist_new(roomspec_t *spec){

    speclist_t *listnew = calloc(1, sizeof(speclist_t));
    
    if (listnew == NULL){
	fprintf(stderr, "calloc failed to allocate space for listnew. \n");
        return NULL;
    }
   
    init_speclist(listnew, spec); 
    return listnew;
}

/* see gen_structs.h */
int speclist_free(speclist_t *list){
    
    if (list == NULL)
	return FAILURE;

    free(list);
    return SUCCESS;	
}

/* see gen_structs.h */
int speclist_free_all(speclist_t *list){

    if (list == NULL)
	return FAILURE;

    speclist_t *tmp, *ptmp;
    int check = 0;

    for(tmp = list; tmp != NULL; tmp = tmp->next){
	ptmp = tmp;	
        check = speclist_free(ptmp);
        if (check == FAILURE){
   	    return check;
        }
    }

    return speclist_free(list);
}
