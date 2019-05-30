#include "game.h"
#include "common-room.h"
#include "game_state_common.h"

/* see game.h */
game_t *game_new(char *desc) {
    game_t *game = malloc(sizeof(game_t));
    game->all_players = NULL; //helper fxn to get list of players
    game->all_rooms = NULL;
    game->start_desc = malloc(MAX_START_DESC_LEN * sizeof(char));

    strncpy(game->start_desc, desc, strnlen(desc, MAX_ID_LEN));

    /* read from the file using interface from WDL team */

    return game;
}

/* See game.h */
int game_quit(game_t *game) {

    if (game != NULL) {
        game_free(game);
        return SUCCESS;
    }
    return FAILURE;
}


/* See game.h */
int add_player_to_game(game_t *game, player_t *player) {
    player_t *check;
    HASH_FIND(hh, game->all_players, player->player_id,
        strnlen(player->player_id, MAX_ID_LEN), check);
    if (check != NULL) {
        /* WARNING */
        fprintf(stderr, "add_room_to_game: this room id is already in use.\n");
        return FAILURE;
    }
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id,
        strnlen(player->player_id, MAX_ID_LEN), player);
    return SUCCESS;
}

/* See game.h */
int add_room_to_game(game_t *game, room_t *room) {
    room_t *check;
    HASH_FIND(hh, game->all_rooms, room->room_id, strnlen(room->room_id, MAX_ID_LEN),
    check);

    if (check != NULL) {
        /* WARNING */
        fprintf(stderr, "add_room_to_game: this room id is already in use.\n");
        return FAILURE;
    }
    HASH_ADD_KEYPTR(hh, game->all_rooms, room->room_id, strnlen(room->room_id, MAX_ID_LEN),
    room);
    return SUCCESS;
}

/* See game.h */
int create_connection(game_t *game, char* src_room, char* to_room,
    char* direction)
{
    room_t *src = find_room(game, src_room);
    if (src == NULL) {
        return 2;
    }
    room_t *to = find_room(game, to_room);
    if (to == NULL) {
        return 3;
    }
    path_t *connection = path_new(to, direction);
    int check = add_path_to_room(src, connection);
    return check;
}


/* See game.h */
int set_curr_player(game_t *game, player_t *player) {
    game->curr_player = player;
    if (game->curr_player != NULL)
        return SUCCESS;
    return FAILURE;
}

/* See game.h */
player_t *get_player(game_t *game, char *player_id) {
    player_t *s;
    HASH_FIND(hh, game->all_players, player_id, strnlen(player_id, MAX_ID_LEN), s);
    return s;
}

/* See game.h */
room_t *find_room(game_t *game, char* room_id) {
    room_t *r;
    HASH_FIND(hh, game->all_rooms, room_id, strnlen(room_id, MAX_ID_LEN), r);
    // if (r == NULL) {
    //     return NULL;
    // }
    return r;
}


/* See game.h */
int move_room(game_t *game, room_t *new_room) {
    if(game == NULL) {
        return FAILURE;
    }
    if(new_room == NULL)
        return FAILURE;
    room_t *check = find_room(game, new_room->room_id);
    if(check == NULL) {
        return FAILURE;
    }
    return SUCCESS;
}

/* See game.h */
int game_free(game_t *game) {
    delete_all_rooms(game->all_rooms);
    delete_all_players(game->all_players);
    // room_free(game->curr_room);
    // player_free(game->curr_player);
    free(game->start_desc);
    free(game);
    return SUCCESS;
}

/* See game.h */
room_list_t *get_all_rooms(game_t *game) {
    room_list_t *head = NULL;
    room_t *ITTMP_ROOM, *curr_room;
    room_list_t *tmp;
    HASH_ITER(hh, game->all_rooms, curr_room, ITTMP_ROOM) {
        tmp = malloc(sizeof(room_list_t));
        tmp->room = curr_room;
        LL_APPEND(head, tmp);
    }
    return head;
}

/* See game.h */
int delete_room_llist(room_list_t *head) {
    room_list_t *elt, *tmp;
    LL_FOREACH_SAFE(head, elt, tmp) {
        LL_DELETE(head, elt);
        free(elt);
    }
    return SUCCESS;
}
