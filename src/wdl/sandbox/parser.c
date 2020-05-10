#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* necessary includes to use JSON-C */
#include <json-c/json.h>

int main(int argc, char **argv) {
   FILE *fp;
   char buffer[2048];
   
   struct json_object *game_document;
   struct json_object *game;
   struct json_object *rooms;
   struct json_object *items;
   
   fp = fopen("connected_rooms.json", "r");
   fread(buffer, 2048, 1, fp);
   fclose(fp);

   game_document = json_tokener_parse(buffer);
   
   json_object_object_get_ex(game_document, "GAME", &game);
   json_object_object_get_ex(game_document, "ROOMS", &rooms);
   json_object_object_get_ex(game_document, "ITEMS", &items);

}
