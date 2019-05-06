#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "utlist.h"

/* See player.h */
int player_init(player_t* plyr, int health)
{
	assert(plyr != NULL);

    plyr->level = 1;
    plyr->health = health;
    plyr->xp = 0;
    //create empty llist for inventory + clothes

    poly->points = malloc(INITIAL_ALLOC * sizeof(point_t));

    if(p->inventory == NULL)
    {
        error("Could not allocate memory for inventory list");
        return FAILURE;
    }

    if(p->clothes == NULL)
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

    int init_bool = player_init(plyr);
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
int change_xp(player_t* plyr)
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


llist* get_inventory(player_t* plyr)
{
	//TODO
	return NULL;
}


llist* get_clothes(player_t* plyr)
{
	//TODO
	return NULL;
}