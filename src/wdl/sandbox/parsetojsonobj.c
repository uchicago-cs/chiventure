#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "parsetojsonobj.h"
#include <zlib.h>



int main() {

    //FILE *fp;
    //char buffer[4096];
    ZZIP_DIR* dir = zzip_dir_open("game1.wdz",0);
    printf(dir);
    /* 
    struct json_object *game_document;
    struct json_object *game_obj;
    struct json_object *rooms_obj;
    struct json_object *items_obj;
    struct json_object *intro_obj;

    fp = fopen(filename, "r");
    assert(fp);
    fread(buffer, 4096, 1, fp);
    fclose(fp);

    game_document = json_tokener_parse(buffer);
    
    assert(game_document);
 
    json_object_object_get_ex(game_document, "GAME", &game_obj);
    json_object_object_get_ex(game_document, "ROOMS", &rooms_obj);
    json_object_object_get_ex(game_document, "ITEMS", &items_obj);

    assert(game_obj);
    */
    
    return 0;
}