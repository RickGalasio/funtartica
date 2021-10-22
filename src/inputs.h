#ifndef _INPUTS_H_
#define _INPUTS_H_

#include "config.h"
#include "playsound.h"
#include "debug.h"
#include "console.h"
#include "ge.h"

#define DCONTEXT extern
#include "globals.h"

static bool pressed_fire;
static const Uint8 *state;
// static Uint32 autoshot;

int inputs(void);

#endif

// - EOF
