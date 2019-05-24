#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_rooms.h"

obj_t *get_doc_obj()
{
    obj_t *obj = obj_new("doc");
    parse_game("../examples/sample_yaml/connected_rooms.yaml", obj);
    return obj;
}

Test(rooms, test)
{
   obj_t *doc = get_doc_obj();
   game_t *g = game_new();
   add_rooms_to_game(doc, g);
   room_t *r = find_room(g, "room A");
   char *s = get_sdesc(r);
   printf("%s\n", s);
}
