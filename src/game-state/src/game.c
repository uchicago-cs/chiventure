#include "game.h"
// #include "common-player.h"
// #include "common-room.h"

/* see game.h */
game_t *game_new() {
    game_t *game = malloc(sizeof(game_t));
    memset(game, 0, sizeof(game_t));

    /* read from the file using interface from WDL team */

    return game;
}


/* See game.h */
void move_room(game_t *game, room_t *new_room) {
    if(game != NULL && new_room != NULL) {
        game->curr_room = new_room;
    }
}

/* See game.h */
void game_quit(game_t *game) {
    if (game != NULL) game_free(game);
    exit(0);
}

/* See game.h */
int game_free(game_t *game) {
    delete_all_rooms(game->all_rooms);
    delete_all_players(game->all_players);
    free(game);
    return SUCCESS;
}

/* See game.h */
int add_player_to_game(game_t *game, player_t *player) {
    return add_player_to_hash(game->all_players, player->player_id, player);
}

/* See game.h */
int add_room_to_game(game_t *game, room_t *room) {
    return add_room_to_hash(game->all_rooms, room->room_id, room);
}


/* See game.h */
int set_curr_player(game_t *game, player_t *player) {
    game->curr_player = player;
    if (game->curr_player != NULL)
        return SUCCESS;
    return FAILURE;
}

// Function to find player given game and player id
player_t *get_player(game_t *game, char *player_id) {
    player_t *s;
    HASH_FIND_STR(game->all_players, player_id, s);
    return s;
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

/* See game.h */
item_list_t *get_all_items_in_game(game_t *game) {
    item_list_t *items = NULL, *items_tmp = NULL;
    room_list_t *rooms = get_all_rooms(game);
    room_list_t *roomwrapped;
    LL_FOREACH(rooms, roomwrapped) {
        items_tmp = get_all_items_in_room(roomwrapped->room);
        LL_CONCAT(items, items_tmp);
    }
    /* **** If multiplayer/npc is supported in the furture,
            please add get_all_players() and modify this    **** */
    items_tmp = get_all_items_in_inventory(game->curr_player);
    LL_CONCAT(items, items_tmp);
    return items;
}
