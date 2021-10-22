#ifndef _GEGLOBALS_H_
#define _GEGLOBALS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "config.h"

//sctrings
#define LETS(a, b) snprintf(a , sizeof( a ), "%s", b )< 0 ? abort() : (void)0;
#define LETSF(a, ...) snprintf(a , sizeof( a ), __VA_ARGS__)< 0 ? abort() : (void)0;

//Dynamic allocated of strings
#define MALETS(a, b) a=malloc(sizeof(char)*(1+strlen( b )));snprintf( a , sizeof(char) * (1+strlen( b )), "%s", b );
#define REALETS(a, b) a=realloc(a, sizeof(char)*(1+strlen( b )));sprintf( a ,"%s", b );

#define ADDLETS(a, b) a=realloc(a, sizeof(char)*(1+strlen( a ))+sizeof(char)*(1+strlen( b )));sprintf( a ,"%s%s", a , b );
#define ADDLETSNL(a, b) a=realloc(a, sizeof(char)*(1+strlen( a ))+sizeof(char)*(2+strlen( b )));sprintf( a ,"%s%s\n", a , b );

#define FREESEC( a ) if(a != NULL) free( a ); a=NULL;

DCONTEXT lua_State* GLSCRIPT;

DCONTEXT int sprites;

//Engine Global Variables
DCONTEXT Uint32 fps;
DCONTEXT int maxvars;

DCONTEXT char GEVARNAME_I[DMAXVAR_I][DMAXVARNAME_I];

char *getvarnamei(int idx);
DCONTEXT int GEI[DMAXVAR_I];
int getGEI(int idx);

DCONTEXT enum _inputmode{
    terminal,
    menu,
    play
} inputmode;

DCONTEXT enum _anitype{
   loop,
   forward,
   none
} _anitype;

DCONTEXT enum _spritetype{
   character,
   prop,
   mosaic,
   tile,
   bar,
   gauge,
   procedural,
   composed
} _spritetype;

typedef struct animation{
  int maxframes;
  int frameidx;
  Uint32 speed;
  enum _anitype anitype;
  bool ended;
  // char *startscript;
  // char *updatescript;
  // char *endscript;
  SDL_Texture *textFrame[DMAXANIFRAME];
}GE_animation;

DCONTEXT bool gepause;

//---------------------------Define sprites---v
typedef struct _sprite {
  char *name;
  enum _spritetype spritetype;
  bool hide;
  bool flip;
  bool vflip;
  SDL_Rect pos;
  int speed;
  Uint32 tick;
  bool showbox;
  // --- status of sprite -- v
  int life;
  int ammo;
  // --- status of sprite -- ^
  SDL_Rect boxattack;
  SDL_Rect boxdefense;
  GE_animation animation[DMAXSPRTANIMATION];  
  int animationidx;
  //Scripts do sprite -----v    
  bool script;
  char *filestart;
  char *fileupdate;
  char *fileend;
  //Scripts fo sprite -----^
}sprite;
//---------------------------Define sprites---^

typedef struct _Clone{
  sprite sprite;
  struct _Clone *nextchain;
} Clone;

typedef struct _cloneChain{
   Clone startchain;
} cloneChain;

DCONTEXT sprite GE_sprite[DMAXSPRT];
DCONTEXT sprite bullets[DBULLETS];

DCONTEXT bool hide;
DCONTEXT bool showbox;
DCONTEXT int width;
DCONTEXT int height;

DCONTEXT SDL_Color defenseboxcolor;
DCONTEXT SDL_Color attackboxcolor;
DCONTEXT SDL_Color sptboxcolor;
DCONTEXT SDL_Color textboxcolor;

DCONTEXT bool console;
DCONTEXT int history;
DCONTEXT char consoletxt[256];
DCONTEXT char consoletxt_[256];

DCONTEXT char tmp[512];
DCONTEXT char tmp_[512];
DCONTEXT struct term_{
    char txt[256];
    char txt_[256];
 }term[DTERMLINES];

DCONTEXT SDL_Event e;

typedef struct _font{
   TTF_Font *body;
   int x,y; 
   bool hide;
   char *text;
   SDL_Color color;
}_font;
DCONTEXT _font font[10];

//-----------------------------------------
int regexcmp(char *myregex, char *inputstring);

Clone *CreateClone( sprite sptr, int x, int y);
void DestryClone(Clone *cl);
void UpdateClone(Clone *cl); // O update é feito de acordo com o script update do sprite pai
void showClone(Clone *cl, SDL_Renderer *window);
void DestroyCloneChain(cloneChain *clc);

// Engine Functions
void * alocstr(char *a);
void * realocstr(void * retaloc, char *a);

int initGE(void);

int setGEvarI(char *VarNameString, int varValorI);
int getGEvarI(char *VarNameString);
int Quit_GE(void);

#endif

// - EOF
