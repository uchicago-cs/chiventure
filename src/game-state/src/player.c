#include "player.h"

/* See player.h */
int player_init(player_t* plyr, int health) {
	assert(plyr != NULL);

    plyr->level = 1;
    plyr->health = health;
    plyr->xp = 0;
    plyr->inventory = NULL;

    return SUCCESS;
}

/* See player.h */
player_t* player_new(int health) {
    player_t *plyr;
    plyr = malloc(sizeof(player_t));

    if(plyr == NULL)
    {
        perror("Could not allocate memory");
        return NULL;
    }

    int init_bool = player_init(plyr, health);
    if(init_bool != SUCCESS)
    {
        perror("Could not initialize player");
        return NULL;
    }

    return plyr;
}

/* See player.h */
int player_free(player_t* plyr) {
    assert(plyr != NULL);

    free(plyr->inventory);

    return SUCCESS;
}

void delete_all_players(player_hash_t players) {
    player_t *current_player, *tmp;
    HASH_ITER(hh, players, current_player, tmp) {
        HASH_DEL(players, current_player);  /* delete it (players advances to next) */
        player_free(current_player);             /* free it */
    }
}

/* See player.h */
int get_health(player_t* plyr) {
	return plyr->health;
}

/* See player.h */
int change_health(player_t* plyr, int change, int max) {
    if((plyr->health + change) < max) {
        plyr->health += change;
    } else {
        plyr->health = max;
    }
	return plyr->health;
}

/* See player.h */
int get_level(player_t* plyr) {
    return plyr->level;
}

/* See player.h */
int change_level(player_t* plyr, int change) {
	plyr->level += change;
    return plyr->level;
}

/* See player.h */
int get_xp(player_t* plyr) {
	return plyr->xp;
}

/* See player.h */
int change_xp(player_t* plyr, int points) {
	plyr->xp += points;
	return plyr->xp;
}


/* See player.h */
item_hash_t get_inventory(player_t* plyr) {
	return plyr->inventory;
}


/* See player.h */
int add_player_to_hash(player_hash_t all_players, char *player_id, player_t *player) {
    player_t *s;
    HASH_FIND_STR(all_players, player_id, s);
    if (s != NULL) {
        printf("FATAL: player_id already used!\n");
        exit(1);
    }
    HASH_ADD_STR(all_players, player_id, player);
    return SUCCESS;
}

/* See player.h */
int add_item_to_player(player_t *player, item_t *item) {
    return add_item_to_hash(player->inventory, item->item_id, item);
}


/* DISCARD
IMPLEMENT function to find player given list and pid 
See player_private.h 
player_t *get_player(player_hash_t all_players, char *player_id) {
    player_t
}
*/
