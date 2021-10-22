#ifndef _GE_H_
#define _GE_H_

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <math.h>

#define DCONTEXT 
#include "globals.h"

#include "console.h"
#include "rnd.h"
#include "gelua.h"
#include "inifiles.h"
#include "debug.h"
#include "config.h"
#include "inputs.h"
#include "getileset.h"
#include "gensprite.h"

// bool createdconsole=false;
static int consoleborder;

//Parameters for FPS calculation
static Uint32 tstart, tnow, retractexplosion;

#define SECOND 1000 // 1 second = 1000 miliseconds

static SDL_Window *windscr;
static SDL_Renderer *rendscr;
static SDL_Texture *texturefont;
static SDL_Surface *icon;

static SDL_Color bgcolor = { 0x00, 0x00, 0x00, 0xff };

//char ccolor[12]="00,00,00,00";
static unsigned int cr,cg,cb,ca;
static char *linetext;

static bool gupdateok;

static char *filescript;
static char *filescriptend;

char *parservar(char *intext);

void GE_load_debug_box(void);

static char spriteN[9]; //"sprite1" ... "sprite99"
static char animationSTUFFS[20];
static char animaNframeN[15]; //"anima1frame1" .. "anima99frame99"
static char filename[50];

void GE_load_sprites(void);

static int fonts;
void GE_load_fonts(void);

void GE_create_clone_sprites(void);

static int clearbg;
static	SDL_Rect rect;
static	SDL_Rect a, b;
static int nf;
static int ibullet;
// start script
static int texW = 0;
static int texH = 0;
static SDL_Rect textrect;

void GE_loop(void *arg);
void GE_quit(int exitcode);

int main(int argc, char *argv[]);

#endif

// - EOF
