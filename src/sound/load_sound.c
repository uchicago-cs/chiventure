#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "common.h"
#include "load_sound.h"


/* See load_sound.h */
sound_t* load_sound (raw_file){

    
}




/* See load_sound.h */
int free(sound_t* sound){
    assert(sound != NULL);

    free(sound);

    return SUCCESS;

}