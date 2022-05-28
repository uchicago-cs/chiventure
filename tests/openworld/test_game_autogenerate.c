#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "openworld/autogenerate.h"
#include "openworld/game_autogenerate.h"
#include "openworld/default_rooms.h"
#include "openworld/default_items.h"
#include "openworld/gen_structs.h"

/* Tests the functions in game_autogenerate.h */

Test(randomroom, random_first_room){

    game_t *game=game_new("New Game");

    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");
    spec1->tag=0;

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");
    spec2->tag=1;

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    spec3->tag=2;
    roomspec_t **roomspecs=(roomspec_t**)malloc(3*sizeof(roomspec_t*));

    roomspecs[0]=spec1;
    roomspecs[1]=spec2;
    roomspecs[2]=spec3;

    int *matrix=(int*)malloc(9*sizeof(int));

    matrix[0]=5;
    matrix[1]=4;
    matrix[2]=5; 
    matrix[3]=0; 
    matrix[4]=5;  
    matrix[5]=3;
    matrix[6]=4; 
    matrix[7]=3;  
    matrix[8]=5;

    int **edges=edges_new(matrix, 3, 3);

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);

    int rc=random_first_room(game, specgraph);

    cr_assert_eq(rc, SUCCESS, "failed to autogenerate a random first room\n");
}

Test(randomroom, random_room_from_game){

    game_t *game=game_new("New Game");

    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");
    spec1->tag=0;

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");
    spec2->tag=1;

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    spec3->tag=2;
    roomspec_t **roomspecs=(roomspec_t**)malloc(3*sizeof(roomspec_t*));

    roomspecs[0]=spec1;
    roomspecs[1]=spec2;
    roomspecs[2]=spec3;

    int *matrix=(int*)malloc(9*sizeof(int));

    matrix[0]=5;
    matrix[1]=4;
    matrix[2]=5; 
    matrix[3]=0; 
    matrix[4]=5;  
    matrix[5]=3;
    matrix[6]=4; 
    matrix[7]=3;  
    matrix[8]=5;

    int **edges=edges_new(matrix, 3, 3);

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);

    int rc=random_first_room(game, specgraph);

    room_t *room=random_room_from_game(game);

    int tag=room->tag;

    cr_assert_eq((0!=tag) && (1!=tag) && (2!=tag), 0, "failed to autogenerate a random first room\n");    
}

Test(room, generate_room_in_game){

    game_t *game=game_new("New Game");

    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL,0);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");
    spec1->tag=0;

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL,1);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");
    spec2->tag=1;

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL,2);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    spec3->tag=2;
    roomspec_t **roomspecs=(roomspec_t**)malloc(3*sizeof(roomspec_t*));

    roomspecs[0]=spec1;
    roomspecs[1]=spec2;
    roomspecs[2]=spec3;

    int *matrix=(int*)malloc(9*sizeof(int));

    matrix[0]=5;
    matrix[1]=4;
    matrix[2]=5; 
    matrix[3]=0; 
    matrix[4]=5;  
    matrix[5]=3;
    matrix[6]=4; 
    matrix[7]=3;  
    matrix[8]=5;

    int **edges=edges_new(matrix, 3, 3);

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);

    int rc=autogenerate_room_in_game(game, specgraph);

    cr_assert_eq(rc, SUCCESS, "failed to autogenerate game with a randomly chosen first room\n");
}

/*
Test(game_autogenerate, game_autogenerate_static_random_first_room){

    game_t *game=game_new("New Game");

    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");
    spec1->tag=0;

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");
    spec2->tag=1;

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    spec3->tag=2;
    roomspec_t **roomspecs=(roomspec_t**)malloc(3*sizeof(roomspec_t*));

    roomspecs[0]=spec1;
    roomspecs[1]=spec2;
    roomspecs[2]=spec3;

    int *matrix=(int*)malloc(9*sizeof(int));

    matrix[0]=5;
    matrix[1]=4;
    matrix[2]=5; 
    matrix[3]=0; 
    matrix[4]=5;  
    matrix[5]=3;
    matrix[6]=4; 
    matrix[7]=3;  
    matrix[8]=5;

    int **edges=edges_new(matrix, 3, 3);

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);

    int rc=game_autogenerate_static(game, specgraph, 5, "pickrandomly");

    cr_assert_eq(rc, SUCCESS, "failed to autogenerate game with a randomly chosen first room\n");
}


Test(game_autogenerate, game_autogenerate_static_specific_first_room){

    game_t *game=game_new("New Game");

    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");
    spec1->tag=0;

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");
    spec2->tag=1;

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    spec3->tag=2;
    roomspec_t *roomspecs[3]={spec1, spec2, spec3};

    int *matrix=(int*)malloc(9*sizeof(int));

    matrix[0]=5;
    matrix[1]=4;
    matrix[2]=5; 
    matrix[3]=0; 
    matrix[4]=5;  
    matrix[5]=3;
    matrix[6]=4; 
    matrix[7]=3;  
    matrix[8]=5;

    int **edges=edges_new(matrix, 3, 3);

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);

    int rc=game_autogenerate_static(game, specgraph, 5, "room_name1");

    cr_assert_eq(rc, SUCCESS, "failed to autogenerate game with a specific first room\n");
}

Test(game_autogenerate, game_autogenerate_static_one_roomspec_game){

    game_t *game=game_new("New Game");

    roomspec_t *spec1 = roomspec_new("room_name1", "short desc1", "long desc1", NULL);
    cr_assert_not_null(spec1, "failed to create new roomspec_t\n");
    spec1->tag=0;

    roomspec_t *spec2 = roomspec_new("room_name2", "short desc2", "long desc2", NULL);
    cr_assert_not_null(spec2, "failed to create new roomspec_t\n");
    spec2->tag=1;

    roomspec_t *spec3 = roomspec_new("room_name3", "short desc3", "long desc3", NULL);
    cr_assert_not_null(spec3, "failed to create new roomspec_t\n");
    spec3->tag=2;
    roomspec_t *roomspecs[3]={spec1, spec2, spec3};

    int *matrix=(int*)malloc(9*sizeof(int));

    matrix[0]=5;
    matrix[1]=0;
    matrix[2]=0; 
    matrix[3]=0; 
    matrix[4]=5;  
    matrix[5]=3;
    matrix[6]=4; 
    matrix[7]=3;  
    matrix[8]=5;
    
    int **edges=edges_new(matrix, 3, 3);

    specgraph_t *specgraph = specgraph_new(3, roomspecs, edges);
    
    int rc=game_autogenerate_static(game, specgraph, 5, "room_name1");

    cr_assert_eq(rc, SUCCESS, "failed to autogenerate game with only one roomspec\n");

    room_hash_t *current, *tmp;
    int currtag;
    int num_rooms=0;

    HASH_ITER(hh, game->all_rooms, current, tmp){
        cr_assert_eq(current->tag, 0, "failed to autogenerate game with correct roomspecs\n");
        num_rooms++;
    }
    
    cr_assert_eq(num_rooms, 3, "failed to autogenerate game with correct number of rooms\n");
}
*/