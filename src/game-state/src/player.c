#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "utlist.h"

llist_t* new_llist()
{
    llist_t* new_list = (llist_t*)malloc(sizeof(llist_t));
    return new_list;
}

/* See player.h */
int player_init(player_t* plyr, int health)
{
	assert(plyr != NULL);

    plyr->level = 1;
    plyr->health = health;
    plyr->xp = 0;
    plyr->inventory = new_llist();
    plyr->clothes = new_llist();

    if(plyr->inventory == NULL)
    {
        error("Could not allocate memory for inventory list");
        return FAILURE;
    }

    if(plyr->clothes == NULL)
    {
        error("Could not allocate memory for clothes list");
        return FAILURE;
    }

    return SUCCESS;

}

/* See player.h */
player_t* player_new(int health)
{
    player_t *plyr;
    plyr = malloc(sizeof(player_t));

    if(plyr == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }

    int init_bool = player_init(plyr, health);
    if(init_bool != SUCCESS)
    {
        error("Could not initialize player");
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


llist_t* get_inventory(player_t* plyr)
{
	//TODO
	return NULL;
}


llist_t* get_clothes(player_t* plyr)
{
	//TODO
	return NULL;
}