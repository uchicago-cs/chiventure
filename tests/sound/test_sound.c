#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sound/sound.h"


/* Testing if load_wav can load background music successfully */
Test(sound, load_music)
{
    sound_t *sound = malloc(sizeof(sound_t));
    char song_name[] = "glamorous_fergie.mp3";
    sound->name = song_name;
    sound->type = BACKGROUND;
    sound_type_t *loaded = load_wav(sound);
    cr_assert_not_null(loaded, "load_wav fails; music did not load");
    cr_assert_not_null(loaded->backgroundSound, "load_wav fails; wrong sound type");
}

/* Testing if load_wav can load sound effect successfully */
Test(sound, load_sound_effect)
{
    sound_t *sound = malloc(sizeof(sound_t));
    char song_name[] = "wav_example.wav";
    sound->name = song_name;
    sound->type = SOUND_EFFECT;
    sound_type_t *loaded = load_wav(sound);
    cr_assert_not_null(loaded, "load_wav fails; music did not load");
    cr_assert_not_null(loaded->soundEffect, "load_wav fails; wrong sound type");
}

/* Testing for sound_free function */
Test(sound, free)
{
    
}

/* Testing for play_sound function */
Test(sound, play)
{

}
