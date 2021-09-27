#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
// #include <time.h>
#include "globals.h"
#include "inifiles.h"
#include "debug.h"

#define DTERMLINES 100

bool console;
bool consolesolid;
bool createdconsole;
int termlinesview;
int termlineini;
SDL_Texture *textureconsole;

TTF_Font *bodyconsolefont;

SDL_Color consolecolor;
char consoletxt[256];
char consoletxt_[256];
int history;

char tmp[512];
char tmp_[512];

typedef struct term_{
  char txt[256];
  char txt_[256];
}term_;

term_ term[DTERMLINES];

void toggleconsole(void);
bool consoleon(void);
void setconsole(bool state);
void renderconsole(SDL_Renderer *rendscr, int width, int height, int borders);
void freeconsole(void);
void clearconsoletext(void);

bool execconsole(char *line);
void termprint(char *txt);
void termclean(void);

// Render the terminal console into screen.
void renderconsole(SDL_Renderer *rendscr, int width, int height, int borders);
void freeconsole(void);

// Execute all terminal console comands
bool execconsole(char *line);
void slashrun(char *xcommand);

#endif

// - EOF

