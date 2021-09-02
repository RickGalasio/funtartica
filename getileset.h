#ifndef _GETILESET_H_
#define _GETILESET_H_

#include "globals.h"
#include "debug.h"
#include "config.h"

enum _tiletype {
	wall,
	hidden,
	paving,
	roof,
	trap,
	shallow,
	deep
}_tiletype;

/*
 SW N NE
   \|/
 W--0--E
   /|\
 NW S SE
*/
enum _acesstile {
	everywere,      //a free way
	no_way,         // blocked way
	only_n,         // only North way
	only_s,         // only South way
	only_e,         // only East way
	only_w,         // only West way
	only_horizontal,
	only_vertical,
	only_in,
	only_out
}_acesstile;

typedef struct getileset{
	char legend;
	enum _tiletype type;
	enum _acesstile acess;
	SDL_Surface *tile;
	char *trapscript;
} _getile;

SDL_Texture *getilemap(
	char *configfile,
    char *spriteN,
	SDL_Renderer *rendscr,
	SDL_Color Tcolor,
	int width,int height
	);

#endif




// - EOF
