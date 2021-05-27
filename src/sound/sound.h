#include <stdlib.h>
 #include <stdbool.h>
 #include <assert.h>
 #include <math.h>
 #include <stdint.h>
 #include <SDL/SDL.h>

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

/*
loads wav on the SDL audio queue
Inputs: 
- sound: sound struct 
returns: 
- 0 on success 1 on failure
*/
int load_wav(sound_t *sound);

/*
frees sound 
Inputs: 
- sound_t* sound to free 
*/
int sound_free(sound_t* sound); 


/*
Plays sound 
Input: 
delay (int): time to delay before playing the sound when the function is called
sound: (char*) the hash id of the sound
Returns:
- 0 on success 1 on failure
*/
int play_sound(sound_t* sound, int delay); 