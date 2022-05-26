#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sound/sound.h"


/* Testing if sound_new works with background music */
Test(sound, new_background)
{
    char song_name[] = "c'est_la_vie_khaled.mp3";
    sound_t *sound = sound_new(BACKGROUND, song_name);

     cr_assert_not_null(sound, "sound_new failed");
}

/* Testing if sound_new works with sound effects */
Test(sound, new_sound_effect)
{
    char song_name[] = "wav_example.wav";
    sound_t *sound = sound_new(SOUND_EFFECT, song_name);

     cr_assert_not_null(sound, "sound_new failed");
}

/* Checks that sound_init works for background music */
Test(sound, init_background)
{
    int rc;
    sount_t sound;
    char song_name[] = "glamorous_fergie.mp3";
    
    rc = sound_init(&sound, BACKGROUND, song_name);

    cr_assert_eq(rc, 1, "sound_init failed");
}

/* Checks that sound_init works for sound effects */
Test(sound, init_sound_effect)
{
    int rc;
    sount_t sound;
    char song_name[] = "wav_example.wav";
    
    rc = sound_init(&sound, SOUND_EFFECT, song_name);

    cr_assert_eq(rc, 1, "sound_init failed");
}

/* Testing if load_wav can load background music successfully */
Test(sound, load_music)
{
    char song_name[] = "glamorous_fergie.mp3";
    sound_t *sound = sound_new(BACKGROUND, song_name)
    sound_type_t *loaded = load_wav(sound);
    cr_assert_not_null(loaded, "load_wav fails; music did not load");
    cr_assert_not_null(loaded->backgroundSound, "load_wav fails; wrong sound type");
}

/* Testing if load_wav can load sound effect successfully */
Test(sound, load_sound_effect)
{
    char song_name[] = "wav_example.wav";
    sound_t *sound = sound_new(SOUND_EFFECT, song_name)
    sound_type_t *loaded = load_wav(sound);
    cr_assert_not_null(loaded, "load_wav fails; music did not load");
    cr_assert_not_null(loaded->soundEffect, "load_wav fails; wrong sound type");
}

/* Testing for sound_free function for background music */
Test(sound, free_background)
{
    char song_name[] = "c'est_la_vie_khaled.mp3";
    int rc;

    sound_t *sound = sound_new(BACKGROUND, song_name);

    cr_assert_not_null(sound, "sound_new failed");

    rc = sound_free(BACKGROUND, sound);

    cr_assert_eq(rc, 1, "sound_free failed");

}

/* Testing for sound_free function for sound effects */
Test(sound, free_sound_effect)
{
    char song_name[] = "wav_example.wav";
    int rc;

    sound_t *sound = sound_new(SOUND_EFFECT, song_name);

    cr_assert_not_null(sound, "sound_new failed");

    rc = sound_free(SOUND_EFFECT, sound);

    cr_assert_eq(rc, 1, "sound_free failed");

}

/* Testing for play_sound function for background music with no delay */
Test(sound, play_background)
{
    int rc;
    char song_name[] = "glamorous_fergie.mp3";
    sound_t *sound = sound_new(BACKGROUND, song_name);
    
    rc = play_sound(sound, 0);
    
    cr_assert_eq(rc, 1, "sound_play failed");
}

/* Testing for play_sound function for sound effect with delay */
Test(sound, play_sound_effect)
{
    int rc;
    char song_name[] = "wav_example.wav";
    sound_t *sound = sound_new(SOUND_EFFECT, song_name);
    
    rc = play_sound(sound, 5);

    cr_assert_eq(rc, 1, "sound_play failed");
}

