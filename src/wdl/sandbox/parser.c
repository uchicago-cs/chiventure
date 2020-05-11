#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "parser.h"

/* DEBUG is 0 normally, 1 to print debugging statements */
#define DEBUG 1

/* Helper function: to print debugging statements only when debugging */
int my_print(char *string) {
    
    if (DEBUG) {
        printf("%s\n",string);
    }

    return 0;

}

json_object *parse(char* filename) {
   FILE *fp;
   char buffer[4096];
   
   /* The main json_objects for storing top level information*/
   struct json_object *game_document;
   struct json_object *game;
   struct json_object *rooms;
   struct json_object *items;
   
   /* json_objects for storing game object information */
   struct json_object *intro;

   /* reads the input file */
   fp = fopen(filename, "r");
   assert(fp);
   fread(buffer, 4096, 1, fp);
   fclose(fp);

   game_document = json_tokener_parse(buffer);
   
   assert(game_document);

   json_object_object_get_ex(game_document, "GAME", &game);
   json_object_object_get_ex(game_document, "ROOMS", &rooms);
   json_object_object_get_ex(game_document, "ITEMS", &items);

   assert(game);

   json_object_object_get_ex(game, "intro", &intro);

   assert(intro);

   my_print("Intro:");
   my_print((char*)json_object_get_string(intro));

   return game_document;

}

int main(int argc, char **argv) {

    if(argc > 1) {

         parse(argv[1]);

    }

    return 0;

}
