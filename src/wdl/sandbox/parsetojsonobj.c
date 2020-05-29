#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "parsetojsonobj.h"
#define MAX_DIRECTORY_LENGTH 100
#define MAX_BYTES 4096


void makejsonobj(struct json_object *jobject, char* filename, zip_t* dir){
    zip_file_t* zipfile = zip_fopen(dir, filename, 0);
    assert(zipfile);
    char*  game_buffer = malloc(sizeof(char) * MAX_BYTES);
    zip_int64_t chars =  zip_fread(zipfile,game_buffer, MAX_BYTES);
    if(chars == 0){
        printf("Tried making a JSON obj but file is empty! \n");
    }
    jobject = json_tokener_parse(game_buffer);
    assert(jobject);
    free(game_buffer);
    zip_fclose(zipfile);
}

int main() {

    char game_buffer[MAX_BYTES];
    //This pointer will hold an int value if zip_t fails.
    int* p = malloc(sizeof(int));
    zip_t* dir = zip_open("game1.wdz", 0, p);

    struct json_object *actions_obj;
    struct json_object *globalconditions_obj;
    struct json_object *items_obj;
    struct json_object *player_obj;
    struct json_object *rooms_obj;

    makejsonobj(actions_obj, "game1/game/actions.json", dir);
    makejsonobj(globalconditions_obj, "game1/game/globalconditions.json", dir);
    makejsonobj(items_obj, "game1/game/items.json", dir);
    makejsonobj(player_obj, "game1/game/player.json", dir);
    makejsonobj(rooms_obj, "game1/game/rooms.json", dir);
    


    
    /*
    Alternative implementation that is more adaptable for larger number of files
    Gets files for .JSON files. This is inefficent and may need to use something like:
    
    And loop through the indexes to look for names that end in .json
    
    zip_int64_t zipfiles = zip_get_num_entries(zip_t *archive, zip_flags_t flags);
    for (int i = 0; i < zipfiles; i++){
        char* name = malloc(sizeof(char)*MAX_DIRECTORY_LENGTH);

        name = zip_get_name(dir, i,0);
        //Some way to check for .json and other types of files
        free(name)
    }

    */
    


    
  
    
    /*
    json_object_object_get_ex(game_document, "GAME", &game_obj);
    json_object_object_get_ex(game_document, "ROOMS", &rooms_obj);
    json_object_object_get_ex(game_document, "ITEMS", &items_obj);
    */
  
    zip_close(dir);
    
    return 0;
}
