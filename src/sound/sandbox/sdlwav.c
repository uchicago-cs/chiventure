#include "SDL2/SDL.h"
#include "SDL_thread.h"
#include "SDL2/SDL_mixer.h"

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* set this to any of 512,1024,2048,4096              */
/* the lower it is, the more FPS shown and CPU needed */
#define BUFFER 1024
#define W 640 /* NEVER make this be less than BUFFER! */
#define H 480
#define H2 (H/2)
#define H4 (H/4)
#define Y(sample) (((sample)*H)/4/0x7fff)

Sint16 stream[2][BUFFER*2*2];
int len=BUFFER*2*2, done=0, need_refresh=0, bits=0, which=0,
	sample_size=0, position=0, rate=0;
SDL_Surface *s=NULL;
Uint32 flips=0;
Uint32 black,white;
float dy;

/******************************************************************************/
/* some simple exit and error routines                                        */

void errorv(char *str, va_list ap)
{
	vfprintf(stderr,str,ap);
	fprintf(stderr,": %s.\n", SDL_GetError());
}

void cleanExit(char *str,...)
{
	va_list ap;
	va_start(ap, str);
	errorv(str,ap);
	va_end(ap);
	Mix_CloseAudio();
	SDL_Quit();
	exit(1);
}

/******************************************************************************/
/* the postmix processor, only copies the stream buffer and indicates         */
/* a need for a screen refresh                                                */

static void postmix(void *udata, Uint8 *_stream, int _len)
{
	position+=_len/sample_size;
	/* fprintf(stderr,"pos=%7.2f seconds \r",position/(float)rate); */
	if(need_refresh)
		return;
	/* save the stream buffer and indicate that we need a redraw */
	len=_len;
	memcpy(stream[(which+1)%2],_stream,len>s->w*4?s->w*4:len);
	which=(which+1)%2;
	need_refresh=1;
}

/******************************************************************************/
/* redraw the wav and reset the need_refresh indicator                        */

void refresh()
{
	int x;
	Sint16 *buf;

	/*fprintf(stderr,"len=%d   \r",len); */

	buf=stream[which];
	need_refresh=0;
	
	SDL_LockSurface(s);
	/* clear the screen */
	/*SDL_FillRect(s,NULL,black); */

	/* draw the wav from the saved stream buffer */
	for(x=0;x<W*2;x++)
	{
		const int X=x>>1, b=x&1 ,t=H4+H2*b;
		int y1,h1;
		if(buf[x]<0)
		{
			h1=-Y(buf[x]);
			y1=t-h1;
		}
		else
		{
			y1=t;
			h1=Y(buf[x]);
		}
		{
			SDL_Rect r={X,H2*b,1};
			r.h=y1-r.y;
			SDL_FillRect(s,&r,0);
		}
		{
			SDL_Rect r={X,y1,1,h1};
			SDL_FillRect(s,&r,white);
		}
		{
			SDL_Rect r={X,y1+h1,1};
			r.h=H2+H2*b-r.y;
			SDL_FillRect(s,&r,0);
		}
	}
	SDL_UnlockSurface(s);
	//SDL_Flip(s);
	flips++;
}

/******************************************************************************/

void print_init_flags(int flags)
{
#define PFLAG(a) if(flags&MIX_INIT_##a) printf(#a " ")
	PFLAG(FLAC);
	PFLAG(MOD);
	PFLAG(MP3);
	PFLAG(OGG);
	if(!flags)
		printf("None");
	printf("\n");
}

/******************************************************************************/

int main(int argc, char **argv)
{
	int audio_rate,audio_channels;
	Uint16 audio_format;
	Uint32 t;
	Mix_Music *music;
	int volume=SDL_MIX_MAXVOLUME;

	/* initialize SDL for audio and video */
	if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO)<0)
		cleanExit("SDL_Init");
	atexit(SDL_Quit);

	int initted=Mix_Init(0);
	printf("Before Mix_Init SDL_mixer supported: ");
	print_init_flags(initted);
	initted=Mix_Init(~0);
	printf("After  Mix_Init SDL_mixer supported: ");
	print_init_flags(initted);
	Mix_Quit();

	if(argc<2 || argc>4)
	{
		fprintf(stderr,"Usage: %s filename [depth] [any 3rd argument...]\n"
				"    filename is any music file supported by your SDL_mixer library\n"
				"    depth is screen depth, default is 8bits\n"
				"    if there is a third argument given, we go fullscreen for maximum fun!\n",
				*argv);
		return 1;
	}

	/* open a screen for the wav output */
	//if(!(s=SDL_SetVideoMode(W,H,(argc>2?atoi(argv[2]):8),(argc>3?SDL_WINDOW_FULLSCREEN:0)|SDL_HWSURFACE|SDL_DOUBLEBUF)))
		//cleanExit("SDL_SetVideoMode");

		SDL_CreateWindow("sdlwav - SDL_mixer demo",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			W,
			H,
			SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	
	/* hide the annoying mouse pointer */
	SDL_ShowCursor(SDL_DISABLE);
	/* get the colors we use */
	white=SDL_MapRGB(s->format,0xff,0xff,0xff);
	black=SDL_MapRGB(s->format,0,0,0);
	
	/* initialize sdl mixer, open up the audio device */
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,BUFFER)<0)
		cleanExit("Mix_OpenAudio");

	/* we play no samples, so deallocate the default 8 channels... */
	Mix_AllocateChannels(0);
	
	/* print out some info on the formats this run of SDL_mixer supports */
	{
		int i,n=Mix_GetNumChunkDecoders();
		printf("There are %d available chunk(sample) decoders:\n",n);
		for(i=0; i<n; ++i)
			printf("	%s\n", Mix_GetChunkDecoder(i));
		n = Mix_GetNumMusicDecoders();
		printf("There are %d available music decoders:\n",n);
		for(i=0; i<n; ++i)
			printf("	%s\n", Mix_GetMusicDecoder(i));
	}

	/* print out some info on the audio device and stream */
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
	bits=audio_format&0xFF;
	sample_size=bits/8+audio_channels;
	rate=audio_rate;
	printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate,
			bits, audio_channels>1?"stereo":"mono", BUFFER );

	/* calculate some parameters for the wav display */
	dy=s->h/2.0/(float)(0x1<<bits);
	
	/* load the song */
	if(!(music=Mix_LoadMUS(argv[1])))
		cleanExit("Mix_LoadMUS(\"%s\")",argv[1]);

	{
		Mix_MusicType type=Mix_GetMusicType(music);
		printf("Music type: %s\n",
				type==MUS_NONE?"MUS_NONE":
				type==MUS_CMD?"MUS_CMD":
				type==MUS_WAV?"MUS_WAV":
				/*type==MUS_MOD_MODPLUG?"MUS_MOD_MODPLUG":*/
				type==MUS_MOD?"MUS_MOD":
				type==MUS_MID?"MUS_MID":
				type==MUS_OGG?"MUS_OGG":
				type==MUS_MP3?"MUS_MP3":
				//type==MUS_MP3_MAD?"MUS_MP3_MAD":
				type==MUS_FLAC?"MUS_FLAC":
				"Unknown");
	}
	/* set the post mix processor up */
	Mix_SetPostMix(postmix,argv[1]);
	
	SDL_FillRect(s,NULL,black);
	//SDL_Flip(s);
	SDL_FillRect(s,NULL,black);
	//SDL_Flip(s);
	/* start playing and displaying the wav */
	/* wait for escape key of the quit event to finish */
	t=SDL_GetTicks();
	if(Mix_PlayMusic(music, 1)==-1)
		cleanExit("Mix_PlayMusic(0x%p,1)",music);
	Mix_VolumeMusic(volume);

	while((Mix_PlayingMusic() || Mix_PausedMusic()) && !done)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							done=1;
							break;
						case SDLK_LEFT:
							if(e.key.keysym.mod&KMOD_SHIFT)
							{
								Mix_RewindMusic();
								position=0;
							}
							else
							{
								int pos=position/audio_rate-1;
								if(pos<0)
									pos=0;
								Mix_SetMusicPosition(pos);
								position=pos*audio_rate;
							}
							break;
						case SDLK_RIGHT:
							switch(Mix_GetMusicType(NULL))
							{
								case MUS_MP3:
									Mix_SetMusicPosition(+5);
									position+=5*audio_rate;
									break;
								case MUS_OGG:
								case MUS_FLAC:
								/*
								case MUS_MP3_MAD:
								case MUS_MOD_MODPLUG:
									Mix_SetMusicPosition(position/audio_rate+1);
									position+=audio_rate;
									break;
								*/
								default:
									printf("cannot fast-forward this type of music\n");
									break;
							}
							break;
						case SDLK_UP:
							volume=(volume+1)<<1;
							if(volume>SDL_MIX_MAXVOLUME)
								volume=SDL_MIX_MAXVOLUME;
							Mix_VolumeMusic(volume);
							break;
						case SDLK_DOWN:
							volume>>=1;
							Mix_VolumeMusic(volume);
							break;
						case SDLK_SPACE:
							if(Mix_PausedMusic())
								Mix_ResumeMusic();
							else
								Mix_PauseMusic();
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					done=1;
					break;
				default:
					break;
			}
		}
		/* the postmix processor tells us when there's new data to draw */
		if(need_refresh)
			refresh();
		SDL_Delay(0);
	}
	t=SDL_GetTicks()-t;
	
	/* free & close */
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
	/* show a silly statistic */
	printf("fps=%.2f\n",((float)flips)/(t/1000.0));
	return(0);
}
