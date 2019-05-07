#include "player.h"

/* See player.h */
int player_init(player_t* plyr, int health)
{
	assert(plyr != NULL);

    plyr->level = 1;
    plyr->health = health;
    plyr->xp = 0;
    plyr->inventory = NULL;
    plyr->clothes = NULL;

    return SUCCESS;

}

/* See player.h */
player_t* player_new(int health)
{
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
int player_free(player_t* plyr)
{
    assert(plyr != NULL);

    free(plyr->inventory);
    free(plyr->clothes);

    return SUCCESS;
}

void delete_all_players(all_players_t players) {
    player_t *current_player, *tmp;
    HASH_ITER(hh, players, current_player, tmp) {
        HASH_DEL(players, current_player);  /* delete it (players advances to next) */
        player_free(current_player);             /* free it */
    }
}

/* See player.h */
int get_health(player_t* plyr)
{
	//TODO
	return -1;
}

/* See player.h */
int change_health(player_t* plyr)
{
	//TODO
	return -1;
}

/* See player.h */
int get_level(player_t* plyr)
{
	//TODO
	return -1;
}

/* See player.h */
int change_level(player_t* plyr)
{
	//TODO
	return -1;
}

/* See player.h */
int get_xp(player_t* plyr)
{
	//TODO
	return -1;
}

/* See player.h */
int change_xp(player_t* plyr, int points)
{
	//TODO
	return -1;
}


int add_clothes_object(object_t* item, player_t* plyr)
{
	//TODO
	return -1;
}


int add_inventory_object(object_t* item, player_t* plyr)
{
	//TODO
	return -1;
}


all_objects_t get_inventory(player_t* plyr)
{
	//TODO
	return NULL;
}


all_objects_t get_clothes(player_t* plyr)
{
	//TODO
	return NULL;
}