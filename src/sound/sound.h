#include <stdlib.h>
 #include <stdbool.h>
 #include <assert.h>
 #include <math.h>
 #include <stdint.h>
 #include <SDL2/SDL.h>

 typedef struct{
     // name of sound
     char* name;
     // wav file information
     SDL_AudioSpec wavSpec;
     uint32_t wavLength;
     uint8_t *wavBuffer;



     //below for hash table
     int id; 
     // makes struct hashable
     UT_hash_handle hh; 
 } sound_t;