#ifndef _INPUTS_H_
#define _INPUTS_H_
#include "globals.h"

enum _inputmode{
    terminal,
    menu,
    play
} inputmode;

// static SDL_Event e;

bool pressed_fire;
const Uint8 *state;
Uint32 autoshot;

int inputs(void);

#endif

// - EOF