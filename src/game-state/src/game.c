#include "game.h"
#include "common-player.h"
#include "common-room.h"

/* see game.h */
game_t *game_new(char *desc) {
    game_t *game = malloc(sizeof(game_t));
    game->all_players = NULL; //helper fxn to get list of players
    game->all_rooms = NULL;
    game->start_desc = malloc(MAX_LDESC_LEN * sizeof(char));

    strncpy(game->start_desc, desc, strlen(desc));

    /* read from the file using interface from WDL team */

    return game;
}

/* See game.h */
void game_quit(game_t *game) {
    if (game != NULL) game_free(game);
    exit(0);
}


/* See game.h */
int add_player_to_game(game_t *game, player_t *player) {
    player_t *check;
    HASH_FIND(hh, game->all_players, player->player_id, strlen(player->player_id), check);
    if (check != NULL) {
        /* WARNING */
        fprintf(stderr, "add_room_to_game: this room id is already in use.\n");
        exit(1);
    }
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id, strlen(player->player_id), player);
    return SUCCESS;
}

/* See game.h */
int add_room_to_game(game_t *game, room_t *room) {
    room_t *check;
    HASH_FIND(hh, game->all_rooms, room->room_id, strlen(room->room_id), check);

    if (check != NULL) {
        /* WARNING */
        fprintf(stderr, "add_room_to_game: this room id is already in use.\n");
        exit(1);
    }
    HASH_ADD_KEYPTR(hh, game->all_rooms, room->room_id, strlen(room->room_id), room);
    return SUCCESS;
}

/* See game.h */
int create_connection(game_t *game, char* src_room, char* to_room, char* direction) {
    room_t *src = find_room(game, src_room);
    if (src == NULL)
        exit(1);
    room_t *to = find_room(game, to_room);
    if (to == NULL)
        exit(2);
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
    player_hash_t plyr_hash = game->all_players;

    HASH_FIND_STR(plyr_hash, player_id, s);

    if (s == NULL) {
      return NULL;
    }

    return s;
}

/* See game.h */
room_t *find_room(game_t *game, char* room_id) {
    room_t *r;
    HASH_FIND(hh, game->all_rooms, room_id, strlen(room_id), r);
    return r;
}


/* See game.h */
void move_room(game_t *game, room_t *new_room) {
    if(game != NULL && new_room != NULL) {
        room_t *check = find_room(game, new_room->room_id);
        if(check != NULL)
            game->curr_room = new_room;
    }
}

/* See game.h */
int game_free(game_t *game) {
    delete_all_rooms(game->all_rooms);
    // delete_all_players(game->all_players);
    uthash_free(game->all_players, sizeof(game->all_players));
    free(game);
    return SUCCESS;
}


