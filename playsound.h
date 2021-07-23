#ifndef _PLAYSOUND_H_
#define _PLAYSOUND_H_
#include "globals.h"
#include "config.h"

Mix_Chunk* sound[DMAXSOUNDS];

void initSound(void);

void Quit_sound(void);

void playSound(int channel, int soundidx, int loops);

#endif




// - EOF
