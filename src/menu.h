#ifndef _MENU_H_
#define _MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#define DCONTEXT extern
#include "globals.h"
#include "inifiles.h"
#include "debug.h"

typedef struct _GEmenu{
   int id;
   char *title;
   char *alttext;
   char *scriptname;
   char *scriptline;
} GEmenu;



#endif
// - EOF
