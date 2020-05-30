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

