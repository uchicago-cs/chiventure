#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "wdlparser.h"
#define MAX_DIRECTORY_LENGTH 100
#define MAX_BYTES 4096


void makejsonobj(struct json_object *jobject, char filename, zip_t* dir){
    zip_file_t* zipfile = zip_fopen(dir, filename, 0);
    assert(zipfile);
    char*  game_buffer = malloc(sizeof(char) * MAX_BYTES);
    zip_int64_t chars =  zip_fread(file, buffer, MAX_BYTES);
    if(chars == 0){
        printf("Tried making a JSON obj but file is empty! \n");
    }
    jobject = json_tokener_parse(buffer);
    assert(jobject);
    free(game_buffer);
    zip_fclose(zipfile);
}

objtype getobj_type(char* name){
    int n = strlen(name);
    //takes file to see if it includes keynames "action", "globalconditions", etc.
    for(int i = n; i > 0; i--){
        if (s[i] == '.'){
            char subbuff[17];
            memcpy( subbuff, &s[i-7], 7);
            subbuff[6] = '\0';
            printf("\nSub is: %s", subbuff);
            if(!strcmp("action", subbuff)){
                return TYPE_ACTION
            }
            memcpy( subbuff, &s[i-16], 16);
            subbuff[16] = '\0';
            if(!strcmp("globalconditions", subbuff)){
                 return TYPE_GCONDITION
            }
            memcpy( subbuff, &s[i-6], 6);
            subbuff[6] = '\0';
            if(!strcmp("player", player)){
                 return TYPE_PLAYER
            }
            memcpy( subbuff, &s[i-4], 4);
            subbuff[4] = '\0';
            if(!strcmp("item", subbuff)){
                 return TYPE_ITEM
            }
            memcpy( subbuff, &s[i-4], 4);
            subbuff[4] = '\0';
            if(!strcmp("room", subbuff)){
                 return TYPE_ROOM
            }
            /*SLOTS FOR NPC AND DIALOG TREE TYPES*/
            /*
            memcpy( subbuff, &s[i-16], 16);
            subbuff[16] = '\0';
            if(!strcmp("globalconditions", subbuff)){
                 printf("This is OK");
            }
            memcpy( subbuff, &s[i-16], 16);
            subbuff[16] = '\0';
            if(!strcmp("globalconditions", subbuff)){
                 printf("This is OK");
            }
            */
        }
        
    }
    return TYPE_NONE
}

int parse(const char *zipdirname) {

    char game_buffer[MAX_BYTES];
    //This pointer will hold an int value if zip_t fails.
    int* p = malloc(sizeof(int));
    zip_t* dir = zip_open(filename, 0, p);
    assert(dir);

    
    /*
    Alternative implementation that is more adaptable for larger number of files
    Gets files for .JSON files. This is inefficent and may need to use something like:
    
    And loop through the indexes to look for names that end in .json
    */
    zip_int64_t zipfiles = zip_get_num_entries(dir, 0);
    for (int i = 0; i < zipfiles; i++){
        //Gets name of each directory
        char* name = malloc(sizeof(char)*MAX_DIRECTORY_LENGTH);

        name = zip_get_name(dir, i,0);
        int n = strlen(name);
        //takes file character by character to see if it ends in .json or other endings
        for(int i = 0; i < n; i++){
            if (s[i] == '.'){
                if(s[i+1] == 'j' && s[i+2] == 's' && s[i+3] == 'o' && s[i+4] == 'n' && s[i+5] == '\0'){
                    //Parse into a JSON file
                    struct json_object *THEJSONOBJ;
                    makejsonobj(THEJSONOBJ, name, dir);

                    //Get objtype e type using its name
                    objtype filetype = get_objtype(name);

                    //Gets each object in the .json file (Such as actions.json) and adds to obj_store
                    json_object_object_foreach(THEJSONOBJ, key, val){
                        if (json_object_is_type(json_object_get_type (val), json_type_boolean )	){
                            //add boolean object with id key and objtype filetype
                        }
                        else if (json_object_is_type(json_object_get_type (val), json_type_int )	){
                            //add int object with id key and objtype filetype
                        }
                        else if (json_object_is_type(json_object_get_type (val), json_type_double )	){
                            //add double object with id key and objtype filetype
                        }
                        else if (json_object_is_type(json_object_get_type (val), json_type_string )	){
                            //add string object with id key and objtype filetype
                        }
                        else if (json_object_is_type(json_object_get_type (val), json_type_array )	){
                            //add array object with id key and objtype filetype
                        }
                        else if (json_object_is_type(json_object_get_type (val), json_type_object )	){
                            //add object with id key and objtype filetype
                            //will need to make this object (a json object) in a libobj
                        }

                    }	
                }
            }
            
        }
      
                
        free(name)
    }

    
    


    
  
    
    /*
    json_object_object_get_ex(game_document, "GAME", &game_obj);
    json_object_object_get_ex(game_document, "ROOMS", &rooms_obj);
    json_object_object_get_ex(game_document, "ITEMS", &items_obj);
    */
  
    zip_close(dir);
    
    return 0;
}
