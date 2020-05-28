/* Team RPG-Openworld
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
#include "common/utlist.h"
#include "common/uthash.h"
#include "game-state/room.h"
#include "openworld/autogenerate.h"
#include "openworld/gen_structs.h"
#include "openworld/default_rooms.h"

/* See autogenerate.h */
bool any_paths(room_t *r)
{
	assert(r != NULL && "any_paths: Given room is NULL");
	return (r->paths != NULL);
}

/* See autogenerate.h */
room_t* roomspec_to_room(game_t *game, roomspec_t *roomspec)
{
	room_t *res = room_new(roomspec->room_name, roomspec->short_desc, roomspec->long_desc);
	res->items = roomspec->items;
	res->paths = NULL;

	return res;
}

/* See autogenerate.h */
int room_generate(game_t *game, gencontext_t *context, char *bucket)
{
	/* Implement simple single-room autogeneration */
	if (!any_paths(game->curr_room))
	{
		roomspec_t *hash = make_default_room(bucket, NULL, NULL);
		context->speclist = speclist_from_hash(hash);
		// Specify roomspec content from speclist
		roomspec_t *r = random_room_content(context->speclist);
		// Adds one generated room from the head of the speclist only
		room_t *new_room = roomspec_to_room(game, r);

		// Add addRoom to gameNew
		assert(SUCCESS == add_room_to_game(game, new_room));

		// Add path from the current room to addRoom
		path_t* path_to_room = path_new(new_room, context->speclist->spec->room_name);
		assert(SUCCESS == add_path_to_room(game->curr_room, path_to_room));

		return SUCCESS; /* room added */
	}

	return FAILURE; /* room not added */
}

/* See autogenerate.h */
int multi_room_generate(game_t *game, gencontext_t *context, char *bucket)
{
	/* If game->curr_room is not a dead end or there are no roomspec_t elements
	* in context->speclist, then do not autogenerate */
	if (any_paths(game->curr_room) || context->speclist == NULL)
	{
		return FAILURE;
	}

	// Save the head of the context's speclist
	speclist_t *speclist_head = context->speclist;

	while (context->speclist != NULL) {
		room_generate(game, context, bucket);

		// Go to next roomspec in context->speclist
		context->speclist = context->speclist->next;
	}

	// Restore the original head of context->speclist
	context->speclist = speclist_head;

	return SUCCESS;
}

/* See autogenerate.h */
speclist_t *speclist_from_hash(roomspec_t *hash) {
	if (hash == NULL) {
		return NULL;
	}
	else {
		speclist_t *spec = NULL;
		roomspec_t *current_room = NULL, *tmp = NULL;
		HASH_ITER(hh, hash, current_room, tmp) {
			speclist_t *s = speclist_new(current_room);
			DL_APPEND(spec, s);
		}
		return spec;
	}
}

/* See autogenerate.h */
roomspec_t *random_room_content(speclist_t *spec) {
	roomspec_t *room = random_room_lookup(spec);
	item_hash_t *items = random_items(room);
	room->items = items;
	return room;
}

/* See autogenerate.h */
roomspec_t *random_room_lookup(speclist_t *spec) {
	int count;
	speclist_t *tmp = NULL, *random = NULL;

	DL_COUNT(spec, tmp, count);
	int idx = rand() % count, i = 0;

	DL_FOREACH(spec, tmp) {
		if (i == idx) {
			item_hash_t *items =  NULL;
			items = random_items(tmp->spec);
			roomspec_t *r = roomspec_new(tmp->spec->room_name,
				tmp->spec->short_desc,
				tmp->spec->long_desc,
				items);
			return r;
		}
		i++;
	}
	return NULL;
}

/* See autogenerate.h */
item_hash_t *random_items(roomspec_t *room) {
	int count = HASH_COUNT(room->items);
	int num_items = rand() % 6;
	item_hash_t *items = NULL;
	for (int i = 0; i < num_items; i++) {
		int rand_count = rand() % count;
		int rc = random_item_lookup(items, room->items, rand_count);
	}
	return items;
}

/* See autogenerate.h */
int random_item_lookup(item_hash_t *dst, item_hash_t *src, int num_iters) {
	item_hash_t *current = NULL, *tmp = NULL;
	int i = 0;
	HASH_ITER(hh, src, current, tmp) {
		printf("STATUS: %d, %d\n", i, num_iters);
		if (i == num_iters) {
			int rc = copy_item_to_hash(&dst, src, tmp->item_id);
			printf("RC STATUS: %x\n", rc);
			return SUCCESS;
		}
		i++;
	}

	return FAILURE;
}
