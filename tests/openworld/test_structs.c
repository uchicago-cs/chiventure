#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include <string.h>
#include "openworld/gen_structs.h"

/* Tests the gencontext_new function to validate that a gencontext
 * can be made successfully. */
Test(gencontext, new)
{

    path_t *path = path_new(NULL, "north");

    cr_assert_not_null(path, "path was NULL\n");

    gencontext_t *context = gencontext_new(path, 10, 10, NULL);

    cr_assert_not_null(context, "failed to create new gencontext_t\n");
}

/* Tests the init_gencontext function to validate that a gencontext
 * can be initialized successfully. */
Test(gencontext, init)
{

    path_t *path = path_new(NULL, "north");

    cr_assert_not_null(path, "path was NULL\n");

    gencontext_t *context = calloc(1, sizeof(gencontext_t));

    if (context == NULL) {
        fprintf(stderr, "failed to calloc for context. \n");
    }

    int check = init_gencontext(context, path, 10, 10, NULL);

    cr_assert_eq(check, SUCCESS, "failed to initialize a gencontext\n");
}

/* Tests the gencontext_free function to validate that a gencontext can
 * be freed properly */
Test(gencontext, free)
{

    path_t *path = path_new(NULL, "north");

    cr_assert_not_null(path, "path was NULL\n");

    gencontext_t *context = gencontext_new(path, 10, 10, NULL);

    cr_assert_not_null(context, "failed to create new gencontext_t\n");

    int check = gencontext_free(context);

    cr_assert_eq(check, SUCCESS, "failed to free a gencontext\n");
}

/* Tests the roomspec_new function to validate that a roomspec
 * can be made successfully. */
Test(roomspec, new1)
{

    roomspec_t *spec = roomspec_new("room_name", "short desc", "long desc", NULL);

    cr_assert_not_null(spec, "failed to create new roomspec_t\n");
}

/* Tests the init_roomspec function to validate that a roomspec
 * can be initialized successfully. */
Test(roomspec, init1)
{

    roomspec_t *spec = calloc(1, sizeof(roomspec_t));

    if (spec == NULL) {
        fprintf(stderr, "failed to calloc for spec. \n");
    }

    int check = init_roomspec(spec, "room_name", "short desc", "long desc", NULL);

    cr_assert_eq(check, SUCCESS, "failed to initialize a roomspec_t\n");
}

/* Tests the roomspec_free func to validate that a roomspec can be
 * freed successfully. */
Test(roomspec, free1)
{

    roomspec_t *spec = roomspec_new("room_name", "short desc", "long desc", NULL);

    cr_assert_not_null(spec, "failed to create new roomspec_t\n");

    int check = roomspec_free(spec);

    cr_assert_eq(check, SUCCESS, "failed to free a roomspec_t\n");
}

/* Tests the edges_init function to validate that an adjacency matrix (edges) can
 * be initialized successfully. */
Test(edges, init)
{
    int* array=(int*)malloc(9*sizeof(int));
    array[0]=5;
    array[1]=4;
    array[2]=5;
    array[3]=0;
    array[4]=5;
    array[5]=3;
    array[6]=4;
    array[7]=3;
    array[8]=5;
    //array={5,4,5,0,5,3,4,3,5};

    int **edges=(int**)malloc(3*sizeof(int*));
    for(int i=0; i<3; i++){
        edges[i]=(int*)malloc(3*sizeof(int));
    } 
    int rc=edges_init(edges, array, 3, 3);

    cr_assert_eq(rc, SUCCESS, "failed to initialize edges\n");
    cr_assert_eq(edges[0][0], 5, "failed to set edges [0][0] correctly\n");
    cr_assert_eq(edges[0][1], 4, "failed to set edges [0][1] correctly\n");
    cr_assert_eq(edges[0][2], 5, "failed to set edges [0][2] correctly\n");
    cr_assert_eq(edges[1][0], 0, "failed to set edges [1][0] correctly\n");
    cr_assert_eq(edges[1][1], 5, "failed to set edges [1][1] correctly\n");
    cr_assert_eq(edges[1][2], 3, "failed to set edges [1][2] correctly\n");
    cr_assert_eq(edges[2][0], 4, "failed to set edges [2][0] correctly\n");
    cr_assert_eq(edges[2][1], 3, "failed to set edges [2][1] correctly\n");
    cr_assert_eq(edges[2][2], 5, "failed to set edges [2][2] correctly\n");
}

/* Tests the edges_init function to validate that an adjacency matrix (edges) can
 * be initialized successfully. (2 by 2 matrix)*/
Test(edges, init2)
{
    int* array=(int*)malloc(4*sizeof(int));
    array[0]=2;
    array[1]=0;
    array[2]=1;
    array[3]=5;

    int **edges=(int**)malloc(2*sizeof(int*));
    for(int i=0; i<2; i++){
        edges[i]=(int*)malloc(2*sizeof(int));
    }
    int rc=edges_init(edges, array, 2, 2);

    cr_assert_eq(rc, SUCCESS, "failed to initialize edges\n");
    cr_assert_eq(edges[0][0], 2, "failed to set edges [0][0] correctly\n");
    cr_assert_eq(edges[0][1], 0, "failed to set edges [0][1] correctly\n");
    cr_assert_eq(edges[1][0], 1, "failed to set edges [1][0] correctly\n");
    cr_assert_eq(edges[1][1], 5, "failed to set edges [1][1] correctly\n");
}

/* Tests the edges_init function to validate that an adjacency matrix (edges) can
 * be initialized successfully. (1 by 1 matrix)*/
Test(edges, init3) 
{
    int* array=(int*)malloc(1*sizeof(int));
    array[0]=5;

    int **edges=(int**)malloc(sizeof(int*));
    for(int i=0; i<1; i++){
        edges[i]=(int*)malloc(sizeof(int));
    }
    int rc=edges_init(edges, array, 1, 1);

    cr_assert_eq(rc, SUCCESS, "failed to initialize edges\n");
    cr_assert_eq(edges[0][0], 5, "failed to set edges [0][0] correctly\n");
}

/* Tests the edges_init function to validate that an adjacency matrix (edges) can
 * be initialized successfully. (4 by 4 matrix)*/
Test(edges, init4)
{
    int* array=(int*)malloc(16*sizeof(int));
    array[0]=5;
    array[1]=4;
    array[2]=5;
    array[3]=0;
    array[4]=5;
    array[5]=3;
    array[6]=4;
    array[7]=3;
    array[8]=5;
    array[9]=4;
    array[10]=0;
    array[11]=3;
    array[12]=4;
    array[13]=2;
    array[14]=2;
    array[15]=1;
    //array={5,4,5,0,5,3,4,3,5};

    int **edges=(int**)malloc(4*sizeof(int*));
    for(int i=0; i<4; i++){
        edges[i]=(int*)malloc(4*sizeof(int));
    } 
    int rc=edges_init(edges, array, 4, 4);

    cr_assert_eq(rc, SUCCESS, "failed to initialize edges\n");
    cr_assert_eq(edges[0][0], 5, "failed to set edges [0][0] correctly\n");
    cr_assert_eq(edges[0][1], 4, "failed to set edges [0][1] correctly\n");
    cr_assert_eq(edges[0][2], 5, "failed to set edges [0][2] correctly\n");
    cr_assert_eq(edges[0][3], 0, "failed to set edges [0][3] correctly\n");
    cr_assert_eq(edges[1][0], 5, "failed to set edges [1][0] correctly\n");
    cr_assert_eq(edges[1][1], 3, "failed to set edges [1][1] correctly\n");
    cr_assert_eq(edges[1][2], 4, "failed to set edges [1][2] correctly\n");
    cr_assert_eq(edges[1][3], 3, "failed to set edges [1][3] correctly\n");
    cr_assert_eq(edges[2][0], 5, "failed to set edges [2][0] correctly\n");
    cr_assert_eq(edges[2][1], 4, "failed to set edges [2][1] correctly\n");
    cr_assert_eq(edges[2][2], 0, "failed to set edges [2][2] correctly\n");
    cr_assert_eq(edges[2][3], 3, "failed to set edges [2][3] correctly\n");
    cr_assert_eq(edges[3][0], 4, "failed to set edges [3][0] correctly\n");
    cr_assert_eq(edges[3][1], 2, "failed to set edges [3][1] correctly\n");
    cr_assert_eq(edges[3][2], 2, "failed to set edges [3][2] correctly\n");
    cr_assert_eq(edges[3][3], 1, "failed to set edges [3][3] correctly\n");
}

/* Tests the edges_new function to validate that an adjacency matrix (edges) can
 * be made successfully. */
Test(edges, new)
{
    int* array=(int*)malloc(9*sizeof(int));
    array[0]=5;
    array[1]=4;
    array[2]=5;
    array[3]=0;
    array[4]=5;
    array[5]=3;
    array[6]=4;
    array[7]=3;
    array[8]=5;

    int **edges=edges_new(array, 3, 3);

    cr_assert_not_null(edges, "failed to create new edges\n");    
    cr_assert_eq(edges[0][1], 4, "failed to set edges [0][1] correctly\n");
    cr_assert_eq(edges[0][2], 5, "failed to set edges [0][2] correctly\n");
    cr_assert_eq(edges[1][0], 0, "failed to set edges [1][0] correctly\n");
    cr_assert_eq(edges[1][1], 5, "failed to set edges [1][1] correctly\n");
    cr_assert_eq(edges[1][2], 3, "failed to set edges [1][2] correctly\n");
    cr_assert_eq(edges[2][0], 4, "failed to set edges [2][0] correctly\n");
    cr_assert_eq(edges[2][1], 3, "failed to set edges [2][1] correctly\n");
    cr_assert_eq(edges[2][2], 5, "failed to set edges [2][2] correctly\n");
}

/* Tests the edges_new function to validate that an adjacency matrix (edges) can
 * be made successfully. (2 by 2 matrix)*/
Test(edges, new2)
{
    int* array=(int*)malloc(4*sizeof(int));
    array[0]=2;
    array[1]=0;
    array[2]=1;
    array[3]=5;

    int** edges = edges_new(array, 2, 2);

    cr_assert_not_null(edges, "failed to create new edges\n");
    cr_assert_eq(edges[0][0], 2, "failed to set edges [0][0] correctly\n");
    cr_assert_eq(edges[0][1], 0, "failed to set edges [0][1] correctly\n");
    cr_assert_eq(edges[1][0], 1, "failed to set edges [1][0] correctly\n");
    cr_assert_eq(edges[1][1], 5, "failed to set edges [1][1] correctly\n");

}

/* Tests the edges_new function to validate that an adjacency matrix (edges) can
 * be made successfully. (1 by 1 matrix)*/
Test(edges, new3)
{
    int* array=(int*)malloc(1*sizeof(int));
    array[0]=5;

    int** edges = edges_new(array, 2, 2);
    cr_assert_not_null(edges, "failed to create new edges\n");
    cr_assert_eq(edges[0][0], 5, "failed to set edges [0][0] correctly\n");

}

/* Tests the edges_new function to validate that an adjacency matrix (edges) can
 * be made successfully. (4 by 4 matrix)*/
Test(edges, new4)
{
    int* array=(int*)malloc(16*sizeof(int));
    array[0]=5;
    array[1]=4;
    array[2]=5;
    array[3]=0;
    array[4]=5;
    array[5]=3;
    array[6]=4;
    array[7]=3;
    array[8]=5;
    array[9]=4;
    array[10]=0;
    array[11]=3;
    array[12]=4;
    array[13]=2;
    array[14]=2;
    array[15]=1;

    int** edges = edges_new(array, 4, 4);
    cr_assert_not_null(edges, "failed to create new edges\n");
    cr_assert_eq(edges[0][0], 5, "failed to set edges [0][0] correctly\n");
    cr_assert_eq(edges[0][1], 4, "failed to set edges [0][1] correctly\n");
    cr_assert_eq(edges[0][2], 5, "failed to set edges [0][2] correctly\n");
    cr_assert_eq(edges[0][3], 0, "failed to set edges [0][3] correctly\n");
    cr_assert_eq(edges[1][0], 5, "failed to set edges [1][0] correctly\n");
    cr_assert_eq(edges[1][1], 3, "failed to set edges [1][1] correctly\n");
    cr_assert_eq(edges[1][2], 4, "failed to set edges [1][2] correctly\n");
    cr_assert_eq(edges[1][3], 3, "failed to set edges [1][3] correctly\n");
    cr_assert_eq(edges[2][0], 5, "failed to set edges [2][0] correctly\n");
    cr_assert_eq(edges[2][1], 4, "failed to set edges [2][1] correctly\n");
    cr_assert_eq(edges[2][2], 0, "failed to set edges [2][2] correctly\n");
    cr_assert_eq(edges[2][3], 3, "failed to set edges [2][3] correctly\n");
    cr_assert_eq(edges[3][0], 4, "failed to set edges [3][0] correctly\n");
    cr_assert_eq(edges[3][1], 2, "failed to set edges [3][1] correctly\n");
    cr_assert_eq(edges[3][2], 2, "failed to set edges [3][2] correctly\n");
    cr_assert_eq(edges[3][3], 1, "failed to set edges [3][3] correctly\n");
}

/* Tests the edges_free function to validate that an adjacency matrix (edges) can
 * be freed successfully. */
Test(edges, free)
{
    int* array=(int*)malloc(9*sizeof(int));
    array[0]=5;
    array[1]=4;
    array[2]=5;
    array[3]=0;
    array[4]=5;
    array[5]=3;
    array[6]=4;
    array[7]=3;
    array[8]=5;

    int **edges=edges_new(array, 3, 3);

    cr_assert_not_null(edges, "failed to create new edges\n");

    int rc=edges_free(edges, 3);
    cr_assert_eq(rc, SUCCESS, "failed to free edges\n");
}

/* Tests the edges_free function to validate that an adjacency matrix (edges) can
 * be freed successfully. (2 by 2 matrix)*/
Test(edges, free2)
{
    int* array=(int*)malloc(4*sizeof(int));
    array[0]=2;
    array[1]=0;
    array[2]=1;
    array[3]=5;

    int** edges = edges_new(array, 2, 2);

    cr_assert_not_null(edges, "failed to create new edges\n");

    int rc=edges_free(edges, 2);
    cr_assert_eq(rc, SUCCESS, "failed to free edges\n");
}

/* Tests the edges_free function to validate that an adjacency matrix (edges) can
 * be freed successfully. (1 by 1 matrix)*/
Test(edges, free3)
{
    int* array=(int*)malloc(1*sizeof(int));
    array[0]=5;

    int** edges = edges_new(array, 2, 2);
    cr_assert_not_null(edges, "failed to create new edges\n");

    int rc=edges_free(edges, 2);
    cr_assert_eq(rc, SUCCESS, "failed to free edges\n");
}

/* Tests the edges_free function to validate that an adjacency matrix (edges) can
 * be freed successfully. (4 by 4 matrix)*/
Test(edges, free4)
{
    int* array=(int*)malloc(16*sizeof(int));
    array[0]=5;
    array[1]=4;
    array[2]=5;
    array[3]=0;
    array[4]=5;
    array[5]=3;
    array[6]=4;
    array[7]=3;
    array[8]=5;
    array[9]=4;
    array[10]=0;
    array[11]=3;
    array[12]=4;
    array[13]=2;
    array[14]=2;
    array[15]=1;

    int** edges = edges_new(array, 4, 4);
    cr_assert_not_null(edges, "failed to create new edges\n");

    int rc=edges_free(edges, 4);
    cr_assert_eq(rc, SUCCESS, "failed to free edges\n");

}

/* Tests the specgraph_init function to validate that a specgraph can
 * be initialized successfully. */
Test(specgraph, init)
{
    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    roomspec_t *roomspecs[3]={spec1, spec2, spec3};

    int **edges=(int**)malloc(3*sizeof(int*));
    for(int i=0; i<3; i++){
        edges[i]=(int*)malloc(3*sizeof(int));
    } 
    edges[0][0]=5;
    edges[0][1]=4;
    edges[0][2]=5; 
    edges[1][0]=0; 
    edges[1][1]=5;  
    edges[1][2]=3;
    edges[2][0]=4; 
    edges[2][1]=3;  
    edges[2][2]=5;

    specgraph_t specgraph;

    int rc = specgraph_init(&specgraph, 3, roomspecs, edges);

    cr_assert_eq(rc, SUCCESS, "failed to initialize a specgraph_t\n");
}

/* Tests the specgraph_new function to validate that a specgraph can
 * be made successfully. */
Test(specgraph, new)
{

    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    roomspec_t *roomspecs[3]={spec1, spec2, spec3};

    int **edges=(int**)malloc(3*sizeof(int*));
    for(int i=0; i<3; i++){
        edges[i]=(int*)malloc(3*sizeof(int));
    } 
    edges[0][0]=5;
    edges[0][1]=4;
    edges[0][2]=5; 
    edges[1][0]=0; 
    edges[1][1]=5;  
    edges[1][2]=3;
    edges[2][0]=4; 
    edges[2][1]=3;  
    edges[2][2]=5;

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);

    cr_assert_not_null(specgraph, "failed to create new specgraph_t\n");
    cr_assert_eq(specgraph->num_roomspecs, 3, "specgraph_new() failed gathering num_roomspecs");
    cr_assert_eq(specgraph->roomspecs, roomspecs, "specgraph_new() failed gathering roomspecs");
    cr_assert_eq(specgraph->edges, edges, "specgraph_new() failed gathering edges");
} 

/* Tests the specgraph_free function to validate that a specgraph can
 * be freed successfully. */
Test(specgraph, free)
{
    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    roomspec_t *roomspecs[3]={spec1, spec2, spec3};

    int **edges=(int**)malloc(3*sizeof(int*));
    for(int i=0; i<3; i++){
        edges[i]=(int*)malloc(3*sizeof(int));
    } 
    edges[0][0]=5;
    edges[0][1]=4;
    edges[0][2]=5; 
    edges[1][0]=0; 
    edges[1][1]=5;  
    edges[1][2]=3;
    edges[2][0]=4; 
    edges[2][1]=3;  
    edges[2][2]=5;

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);

    cr_assert_not_null(specgraph, "failed to create new specgraph_t\n");

    int check = specgraph_free(specgraph);

    cr_assert_eq(check, SUCCESS, "failed to free a specgraph_t\n");
}

/* Tests the free_all_specgraphs function to validate that it can
 * free all of the elements in the doubly linked list. */
/*Test(specgraph, free_all)
{

    specgraph_t *list = specgraph_new(NULL);
    specgraph_t *list1 = specgraph_new(NULL);
    specgraph_t *list2 = specgraph_new(NULL);

    cr_assert_not_null(list, "failed to create new specgraph_t\n");
    cr_assert_not_null(list1, "failed to create new specgraph_t\n");
    cr_assert_not_null(list2, "failed to create new specgraph_t\n");

    specgraph_t *head = NULL;

    DL_APPEND(head, list);
    DL_APPEND(head, list1);
    DL_APPEND(head, list2);

    int check = specgraph_free_all(list);

    cr_assert_eq(check, SUCCESS, "failed to free the entire specgraph. \n");
}*/



/* Tests the roomlevel_new function to validate that a roomlevel
 * can be made successfully. */
Test(roomlevel, new)
{
    roomlevel_t *roomlevel = roomlevel_new("excellent_name", 4);

    cr_assert_not_null(roomlevel, "failed to create new roomlevel_t\n");
}


/* Tests the init_roomlevel function to validate that a roomlevel can
 * be initialized successfully. */
Test(roomlevel, init)
{
    roomlevel_t *roomlevel = calloc(1, sizeof(roomlevel_t));
    if (!roomlevel) { 
        printf("failed to calloc for roomlevel\n");
    }
    roomlevel->room_name = calloc(1, sizeof(char) * MAX_SDESC_LEN);
    if (!(roomlevel->room_name)) { 
        printf("failed to calloc for roomlevel->room_name\n");
    }

    int check = init_roomlevel(roomlevel, "excellent_name", 4);
    cr_assert_str_eq(roomlevel->room_name, "excellent_name", 
                 "failed to initialize roomlevel->room_name\n");
    cr_assert_eq(4, roomlevel->difficulty_level, 
                 "failed to initialize roomlevel->difficulty_level\n");
    cr_assert_eq(check, SUCCESS, "failed to initialize a roomlevel_t\n");
}


/* Tests the roomlevel_free func to validate that a roomlevel can be
 * freed successfully. */
Test(roomlevel, free)
{
    roomlevel_t *roomlevel = roomlevel_new("excellent_name", 4);

    cr_assert_not_null(roomlevel, "failed to create new roomlevel_t\n");

    int check = roomlevel_free(roomlevel);

    cr_assert_eq(check, SUCCESS, "failed to free a roomlevel_t\n");
}


/* Tests add_roomlevel_to_hash for
   room name = "A"
   difficulty_level = 4 */
Test(roomlevel, add_roomlevel_to_hash_one)
{
    roomlevel_hash_t *roomlevel_hash = NULL;
    char *name = "A"; 

    add_roomlevel_to_hash(&roomlevel_hash, name, 4);
    
    roomlevel_t *out;
    HASH_FIND_STR(roomlevel_hash, name, out);
    cr_assert_not_null(out, "failed to add room A\n");
}


/* Tests add_roomlevel_to_hash for
   room name = "Good"
   difficulty_level = 1 */
Test(roomlevel, add_roomlevel_to_hash_two)
{
    roomlevel_hash_t *roomlevel_hash = NULL;
    char *name = "Good"; 

    add_roomlevel_to_hash(&roomlevel_hash, name, 1);
    roomlevel_t *out;
    HASH_FIND_STR(roomlevel_hash, name, out);
    cr_assert_not_null(out, "failed to add room Good\n");
}



/* Tests the levelspec_new function to validate that 
 * a levelspec can be made successfully. */
Test(levelspec, new)
{
    int num_thresholds = 3;
    int thresholds[3] = {0, 5, 10};
    levelspec_t *levelspec = levelspec_new(num_thresholds, thresholds);

    cr_assert_not_null(levelspec, "failed to create new levelspec_t\n");
    cr_assert_eq(NULL, levelspec->roomlevels, "levelspec->roomlevels hash should be NULL\n");
}


/* Tests the init_levelspec function to validate that 
 * a levelspec can be initialized successfully. */
Test(levelspec, init)
{
    int num_thresholds = 4;
    int thresholds[4] = {0, 10, 20, 30};
    
    levelspec_t *levelspec = calloc(1, sizeof(levelspec_t));
    if (!levelspec) { 
        printf("failed to calloc for levelspec\n");
    }

    levelspec->thresholds = calloc(1, sizeof(int) * num_thresholds);
    if (!(levelspec->thresholds)) { 
        printf("failed to calloc for levelspec->thresholds\n");
    }

    int check = init_levelspec(levelspec, num_thresholds, thresholds);
    cr_assert_eq(levelspec->num_thresholds, num_thresholds,
                 "failed to initialize levelspec->num_thresholds\n");
    for (int i = 0; i < num_thresholds; i++) {
        cr_assert_eq(levelspec->thresholds[i], thresholds[i],
                     "failed to initialize levelspec->threshold[%d]\n", i);
    }
    cr_assert_eq(check, SUCCESS, "failed to initialize a levelspec_t\n");
}


/* Tests the levelspec_free func to validate that a levelspec can be
 * freed successfully. */
Test(levelspec, free)
{
    int num_thresholds = 3;
    int thresholds[3]= {0, 5, 10};
    levelspec_t *levelspec = levelspec_new(num_thresholds, thresholds);
    cr_assert_not_null(levelspec, "failed to create new levelspec_t\n");

    int check = levelspec_free(levelspec);

    cr_assert_eq(check, SUCCESS, "failed to free a levelspec_t\n");
}



/* Tests that the init_itemspec function can
 * initialize a given itemspec given valid params. */
Test(itemspec, init_success)
{
    itemspec_t *itemspec = calloc(1, sizeof(itemspec_t));
    if (itemspec == NULL) 
    { 
        printf("failed to allocate memory for itemspec\n");
    }

    itemspec->item_name = malloc((MAX_SDESC_LEN + 1) * sizeof(char));
    if (itemspec->item_name == NULL) 
    { 
        printf("failed to allocate memory for itemspec->item_name\n");
    }

    int check = init_itemspec(itemspec, "item_name", 0.5, 1, 3);
    cr_assert_eq(check, SUCCESS, "failed to initialize itemspec");
}


/* Tests that the init_itemspec function returns FAILURE
 * when any param requirement is violated. */
Test(itemspec, init_fail)
{
    int check;
    
    itemspec_t *itemspec = NULL;

    check = init_itemspec(itemspec, "item_name", 0.5, 1, 3);
    cr_assert_eq(check, FAILURE, "init should fail when itemspec is NULL");

    itemspec = calloc(1, sizeof(itemspec_t));
    if (itemspec == NULL) 
    { 
        printf("failed to allocate memory for itemspec\n");
    }

    itemspec->item_name = malloc((MAX_SDESC_LEN + 1) * sizeof(char));
    if (itemspec->item_name == NULL) 
    { 
        printf("failed to allocate memory for itemspec->item_name\n");
    }

    check = init_itemspec(itemspec, "item_name", 1.5, 1, 3);
    cr_assert_eq(check, FAILURE, "init should fail when spawn_chance is invalid");
    
    check = init_itemspec(itemspec, "item_name", 0.5, 3, 1);
    cr_assert_eq(check, FAILURE, "init should fail when min_num > max_num");
}


/* Tests that the itemspec_new function can
 * create an itemspec given valid params. */
Test(itemspec, new_success)
{
    itemspec_t *itemspec = itemspec_new("item_name", 0.5, 1, 3);

    cr_assert_not_null(itemspec, "failed to create new itemspec_t\n");
}


/* Tests that the itemspec_new function returns NULL
 * when any param requirement is violated. */
Test(itemspec, new_fail)
{
    itemspec_t *itemspec1 = itemspec_new("item1_name", 1.5, 1, 3);
    cr_assert_null(itemspec1, "new itemspec should be NULL when spawn_chance is invalid");
    
    itemspec_t *itemspec2 = itemspec_new("item2_name", 0.5, 3, 1);
    cr_assert_null(itemspec2, "new itemspec should be NULL when min_num > max_num");
}


/* Tests that the itemspec_free function can 
 * free a given itemspec successfully. */
Test(itemspec, free)
{
    itemspec_t *itemspec = itemspec_new("item_name", 0.5, 1, 3);

    cr_assert_not_null(itemspec, "failed to create new itemspec_t\n");

    int check = itemspec_free(itemspec);

    cr_assert_eq(check, SUCCESS, "failed to free an itemspec_t\n");
}

