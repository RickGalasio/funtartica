#ifndef _GENSPRITE_H_
#define _GENSPRITE_H_
#include "globals.h"
#include "debug.h"
#include "config.h"

// SDL_Texture *gensprite(
// 	char *configfile,
// 	char *spriteN,
// 	SDL_Renderer *rendscr
// 	);

// int setpixel(SDL_Surface *sptsurface, int spritew, int spriteh,int pixelx, int pixely,
// 	SDL_Color pxcolor);

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
static char cxcolor[12];
static char xcolor[15];

SDL_Texture *gensprite(char *configfile, char *spriteN, SDL_Renderer *rendscr);

int setpixel(SDL_Surface *sptsurface, int spritew, int spriteh,int pixelx, int pixely,
	SDL_Color pxcolor);

static unsigned int lastseed=0;
static unsigned int mseed=0;
void msrand(int zseed);
unsigned int mrand(void);
// - EOF
#endif