#include <stdio.h>
#include <strings.h>
#include "globals.h"
#include "debug.h"
#include "gelua.h"

//-------------------------------------------------------------------
int regexcmp(char *myregex, char *inputstring) {
	/* aloca espaço para a estrutura do tipo regex_t */
	regex_t reg;
	// compile the Regular Expression of myregex
	// If error, return != 0 (-1)
	if (regcomp(&reg, myregex, REG_EXTENDED | REG_NOSUB | REG_ICASE) != 0) {
		ERR("regcomp");
		return -1;
	}
	// compare regex and inputstring
	return regexec(&reg, inputstring, 0, (regmatch_t *) NULL, 0);
}
///if(!regexcmp("<[[:alnum:]]+>", xval)){ ...}
///if(!regexcmp("([^[:space:]_]+_[^[:space:]_]+)_([[:digit:]]+)_([[:digit:]]+)(_[+-])?", xval)){ ...}
//-------------------------------------------------------------------
//=====================================================v
void *alocstr(char *a){
void *retaloc;
   if ((retaloc=malloc( 1+strlen(a) * sizeof (char))) == NULL) {
      MSG("Sem memoria livre para alocar\n");
      exit(1);
   }
   sprintf((char *)retaloc,"%s",a); 
   return retaloc;
}
//=====================================================^

//=====================================================v
void *realocstr(void *retaloc, char *a){
   if ((retaloc=realloc(retaloc, 1+strlen(a) * sizeof (char))) == NULL) {
      MSG("Sem memoria livre para alocar.\n");
      exit(1);
   }
   sprintf((char *)retaloc,"%s",a); 
   return retaloc;
}
//=====================================================^

int initGE(void){
  varidxs=0;
  varidxi=0;
  GEerr=0;

  for(int i=0;i<DMAXVAR_I;i++){
     GEI[i]=0;
     snprintf(GEVARNAME_I[i],DMAXLENSTRING,"NULL");
  }

  for(int i=0;i<DMAXVAR_S;i++){
     snprintf(GES[i],DMAXLENSTRING,"NULL");
     snprintf(GEVARNAME_S[i],DMAXLENSTRING,"NULL");
  }

  return(0);
}
//=====================================================
int Quit_GE(void){
   return(0);
}

//=====================================================
int setGEvarI(char *VarNameString, int varValorI){
   if (!strncasecmp(VarNameString, "sprt_", 5)){
      //Sprite Variables
      int nv;
      char namevar[DMAXVARNAME_I];
      char namesprite[DMAXSPRTNAME];
      nv = 0;
      // pula de 0-4, sprt_; a partir do indice 5 é o nome do sprite
      for (int i = 5; VarNameString[i] != '_' && VarNameString[i] != '\0'; i++){
         namesprite[nv++] = VarNameString[i];
      }
      namesprite[nv] = '\0';
      LETS(namevar, VarNameString + nv + 6);

      for (int i = 0; i < sprites; i++){
         if (!strcasecmp(namesprite, GE_sprite[i].name)){
            // DBG("sprite encontrado: %s indice: %d",namesprite,i);
            if (!strcasecmp("hide", namevar)){
               GE_sprite[i].hide=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("x", namevar)){
               GE_sprite[i].pos.x=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("y", namevar)){
               GE_sprite[i].pos.y=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("w", namevar)){
               GE_sprite[i].pos.w=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("h", namevar)){
               GE_sprite[i].pos.h=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("life", namevar)){
               GE_sprite[i].life=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("showbox", namevar)){
               GE_sprite[i].showbox=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("attack_x", namevar)){
               GE_sprite[i].boxattack.x=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("attack_y", namevar)){
               GE_sprite[i].boxattack.y=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("attack_w", namevar)){
               GE_sprite[i].boxattack.w=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("attack_h", namevar)){
               GE_sprite[i].boxattack.h=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("defense_x", namevar)){
               GE_sprite[i].boxdefense.x=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("defense_y", namevar)){
               GE_sprite[i].boxdefense.y=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("defense_w", namevar)){
               GE_sprite[i].boxdefense.w=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("defense_h", namevar)){
               GE_sprite[i].boxdefense.h=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("flip", namevar)){
               GE_sprite[i].flip=varValorI;
               goto setGEvarI_END;
            }else if (!strcasecmp("tick", namevar)){
               GE_sprite[i].tick=varValorI;
               goto setGEvarI_END;
            }
         }
      }
   }else{
      // Global Varsiables
      for (int i = 0; i < DMAXVAR_I; i++){
         if (strcasecmp(VarNameString, GEVARNAME_I[i]) == 0){
            GEI[i] = varValorI;
            GEerr = 0;
            return 0;
						goto exitsetGEvarI;

         }
      }

      if (varidxi >= DMAXVAR_I){
         ERR("Too much variables! (%s)\n", VarNameString);
         GEerr = 1;
         return (-1);
      }

      snprintf(GEVARNAME_I[varidxi], DMAXLENSTRING, "%s", VarNameString);
      GEI[varidxi] = varValorI;
      varidxi++; // Add varidx (# of variables)
setGEvarI_END:
      GEerr = 0;
   }
exitsetGEvarI:
	 return 0;
}
//=====================================================

//=====================================================
int getGEvarI(char *VarNameString){
   // Sprite variables
   if (!strncasecmp(VarNameString, "sprt_", 5)){
      int nv;
      char namevar[DMAXVARNAME_I];
      char namesprite[DMAXSPRTNAME];

      nv = 0;
      // pula de 0-4, sprt_; a partir do indice 5 é o nome do sprite
      for (int i = 5; VarNameString[i] != '_' && VarNameString[i] != '\0'; i++){
         namesprite[nv++] = VarNameString[i];
      }
      namesprite[nv] = '\0';
      LETS(namevar, VarNameString + nv + 6);

      for (int i = 0; i < sprites; i++){
         if (!strcasecmp(namesprite, GE_sprite[i].name)){
            // DBG("sprite encontrado: %s indice: %d",namesprite,i);
            if (!strcasecmp("hide", namevar)){
               return GE_sprite[i].hide;
            }else if (!strcasecmp("x", namevar)){
               return GE_sprite[i].pos.x;
            }else if (!strcasecmp("y", namevar)){
               return GE_sprite[i].pos.y;
            }else if (!strcasecmp("w", namevar)){
               return GE_sprite[i].pos.w;
            }else if (!strcasecmp("h", namevar)){
               return GE_sprite[i].pos.h;
            }else if (!strcasecmp("life", namevar)){
               return GE_sprite[i].life;
            }else if (!strcasecmp("showbox", namevar)){
               return GE_sprite[i].showbox;
            }else if (!strcasecmp("defense_x", namevar)){
               return GE_sprite[i].boxdefense.x;
            }else if (!strcasecmp("defense_y", namevar)){
               return GE_sprite[i].boxdefense.y;
            }else if (!strcasecmp("defense_w", namevar)){
               return GE_sprite[i].boxdefense.w;
            }else if (!strcasecmp("defense_h", namevar)){
               return GE_sprite[i].boxdefense.h;
            }else if (!strcasecmp("flip", namevar)){
               return GE_sprite[i].flip;
            }else if (!strcasecmp("tick", namevar)){
               return GE_sprite[i].tick;
            }
         }
      }
      ERR("sprite variable not found! (%s)\n", VarNameString);
      GEerr = 1;
      return (0);
   }else{
      //Global Variables
      for (int i = 0; i < DMAXVAR_I; i++){
         if (strcasecmp(VarNameString, GEVARNAME_I[i]) == 0){
            return (GEI[i]);
         }
      }

      ERR("variable not found! (%s)\n", VarNameString);
      GEerr = 1;
      return (0);
   }
}

//=====================================================

// void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height)
// {
//     SDL_LockSurface(surface);
//     std::vector<uint8_t> pixels(surface->h * surface->pitch, 0);

//     int dy, dx;
//     int maxwidth = width * 3;
//     for (dy = y; dy < height; dy++) {
//         for (dx = x; dx < maxwidth; dx += 3) {
//             pixels[dx + (dy * surface->pitch)] = 0;
//             pixels[dx + (dy * surface->pitch) + 1] = 255;
//             pixels[dx + (dy * surface->pitch) + 2] = 0;
//         }
//     }
//     memcpy(surface->pixels, pixels.data(), surface->pitch * surface->h);

//     SDL_UnlockSurface(surface);
// }

// - EOF
