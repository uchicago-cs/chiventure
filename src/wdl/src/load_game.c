#include <stdio.h>
#include <stdlib.h>
#include "validate.h"
#include "parse.h"
#include "load_game.h"
#include "parse_document.h"

/*
 * see load_game.h
 */
void load_rooms(atrr_list_t *rooms, attr_list_t *all_items, game_t *g)
{
  attr_list_t *items_in_room;
  int success;
  while(rooms->next != NULL){
    /* r = create_room(rooms->obj) */
    items_in_room = get_items_in_room(rooms->obj->id, all_items);
    while(items_in_room->next != NULL){
    /* i = create_item(items_in_room->obj) */
    /* add_item_to_room(); */
      items_in_room = items_in_room->next;
    }
    success = add_room_to_game(g, r);
    rooms = rooms->next;
  }
}
      
      
