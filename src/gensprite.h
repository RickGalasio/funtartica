#ifndef _GENSPRITE_H_
#define _GENSPRITE_H_
#define DCONTEXT extern
#include "globals.h"
#include "debug.h"
#include "config.h"

static unsigned char *pixel, *pixmask;
#define PIXEL( x , y ) (pixel+(x)*spritew+(y))[0]
#define MPIXEL( x , y ) (pixel+(spritew-x-1)*spritew+(y))[0]
#define PIXMASK( x , y ) (pixmask+(x)*spritew+(y))[0]
#define MPIXMASK( x , y ) (pixmask+(spritew-x-1)*spritew+(y))[0]

#define CHAR_BORDER 255

static int spritew;
static int spriteh;
static int npixels;


static bool mirror;
static bool lake;
static unsigned int pixelcolors, actualcolor;

static int colors; 
//static char cxcolor[12];
static char xcolor[15];

SDL_Texture *gensprite(char *spriteN, SDL_Renderer *rendscr);

int setpixel(SDL_Surface *sptsurface, int spritew, int spriteh,int pixelx, int pixely,
	SDL_Color pxcolor);

// - EOF
#endif
