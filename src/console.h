#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#define DCONTEXT extern
#include "globals.h"
#include "ge.h"
#include "inifiles.h"
#include "debug.h"

static bool consolesolid;
static bool createdconsole;
static int termlinesview;
static int termlineini;
static SDL_Texture *textureconsole;

static TTF_Font *bodyconsolefont;

static SDL_Color consolecolor;

void renderconsole(SDL_Renderer *rendscr, int width, int height, int borders);
void freeconsole(void);
void clearconsoletext(void);

bool execconsole(char *line);
void termprint(char *txt);
void termclean(void);
void slashrun(char *xcommand);

#endif

// - EOF

