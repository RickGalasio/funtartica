#ifndef _CCGMMO_H_
#define _CCGMMO_H_

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
#include "gelua.h"
#include "rnd.h"
#include "console.h"

#ifdef EMCC
#include <emscripten.h>
#endif

bool quit=false;

// bool createdconsole=false;
int consoleborder;

//Parameters for FPS calculation
Uint32 tstart, tnow, retractexplosion;

#define SECOND 1000 // 1 second = 1000 miliseconds

SDL_Window *windscr;
SDL_Renderer *rendscr;
SDL_Texture *texturefont;
SDL_Surface *icon;

SDL_Color bgcolor = { 0x00, 0x00, 0x00, 0xff };
//char ccolor[12]="00,00,00,00";
unsigned int cr,cg,cb,ca;
char *linetext;

// lua_State* GLSCRIPT;
bool gupdateok;

char *filescript;
char *filescriptend;

char *parservar(char *intext);

void GE_load_debug_box(void);


char spriteN[9]; //"sprite1" ... "sprite99"
char animationSTUFFS[20];
char animaNframeN[15]; //"anima1frame1" .. "anima99frame99"
char filename[50];

void GE_load_sprites(void);

int fonts;
void GE_load_fonts(void);

int main(int argc, char *argv[]);

#endif




// - EOF
