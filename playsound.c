#include "playsound.h"
#include "debug.h"
#include "globals.h"
#include "inifiles.h"

void GE_load_sounds(void){
  if (Mix_AllocateChannels(ini_get_int(configfile, "sound", "channels", 2)) < 0){
    ERR("Unable to allocate mixing channels: %s\n", SDL_GetError());
    return;
  }else{
    DBG("Mixing channels, Ok.");
  }

  // Load waveforms
  memset(sound, 0, sizeof(Mix_Chunk *) * DMAXSOUNDS);
  for (int i = 0; i < ini_get_int(configfile, "sound", "sounds", 1); i++){
    char partmp[25];
    char samplefile[25];
    LETSF(partmp, "sound%d", i + 1);
    LETS(samplefile, ini_get_str(configfile, "sound", partmp, "./sound/error.wav"));
    sound[i] = Mix_LoadWAV(samplefile);
    if (sound[i] == NULL){
      ERR("Unable to load wave file: %s\n", samplefile);
    }else{
      DBG("Sample file %s, ok.", samplefile);
    }
  }
}

//---------------------------------------
void Quit_sound(void){
    
    for( int i = 0; i < ini_get_int(configfile,"sound","sounds",1); i++ ){    
        Mix_FreeChunk(sound[i]);
        sound[i]=NULL;
    }
}
//----------------------------------------
void playSound(int channel, int soundidx, int loops){
   Mix_PlayChannel(channel, sound[soundidx], loops); // Boom
}




// - EOF
