#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "parsetojsonobj.h"




int main() {

    //FILE *fp;
   // char buffer[4096];
    int* p = malloc(sizeof(int));
    zip_t* dir = zip_open("game1.wdz", 0, p);
   // zip_name_locate(dir, "actions.json", 0);
   zip_file_t* file = zip_fopen(dir, "game1/game/items.json", 0);
   assert(file);
   // zip_close(dir);
    
    /* 
    struct json_object *game_document;
    struct json_object *game_obj;
    struct json_object *rooms_obj;
    struct json_object *items_obj;
    struct json_object *intro_obj;
    */
    char* name = malloc(sizeof(char)*100);
    name = zip_get_name(dir, 7,0);
   // zip_int64_t chars =  zip_fread(file, buffer, 4096);
    printf("Name is: %s", name);
   // zip_fclose(file);
    /*
    game_document = json_tokener_parse(buffer);
    
    assert(game_document);
 
    json_object_object_get_ex(game_document, "GAME", &game_obj);
    json_object_object_get_ex(game_document, "ROOMS", &rooms_obj);
    json_object_object_get_ex(game_document, "ITEMS", &items_obj);

    assert(game_obj);
    */
    
    return 0;
}
