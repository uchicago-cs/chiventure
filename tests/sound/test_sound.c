#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sound/sound.h"


/* Testing if sound_new works with background music */
Test(sound, new_background)
{
    char song_name[] = "../../src/sound/sandbox/c'est_la_vie_khaled.mp3";
    sound_t *sound = sound_new(BACKGROUND, song_name);
     cr_assert_not_null(sound, "sound_new failed");
}

/* Testing if sound_new works with sound effects */
Test(sound, new_sound_effect)
{
    char song_name[] = "../../src/sound/sandbox/wav_example.wav";
    sound_t *sound = sound_new(SOUND_EFFECT, song_name);
    cr_assert_not_null(sound, "sound_new failed");
}
