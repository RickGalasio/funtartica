#ifndef _GEGLOBALS_H_
#define _GEGLOBALS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <regex.h>
#include "gelua.h"
#include "playsound.h"
#include "config.h"

//Static sctrings
#define LETS(a, b) snprintf(a , sizeof( a ), "%s", b );
#define LETSF(a, ...) snprintf(a , sizeof( a ), __VA_ARGS__);

//Dynamic allocated of strings
#define MALETS(a, b) a=malloc(sizeof(char)*(1+strlen( b )));snprintf( a , sizeof(char) * (1+strlen( b )), "%s", b );
#define REALETS(a, b) a=realloc(a, sizeof(char)*(1+strlen( b )));sprintf( a ,"%s", b );

// #define MALETSE(a, b) a=alocstr( b );
// #define REALETSE(a, b) a=realocstr(a, b);

#define ADDLETS(a, b) a=realloc(a, sizeof(char)*(1+strlen( a ))+sizeof(char)*(1+strlen( b )));sprintf( a ,"%s%s", a , b );
#define ADDLETSNL(a, b) a=realloc(a, sizeof(char)*(1+strlen( a ))+sizeof(char)*(2+strlen( b )));sprintf( a ,"%s%s\n", a , b );

#define FREESEC( a ) if(a != NULL) free( a ); a=NULL;

//Engine Global Variables
char *configfile;

Uint32 fps;

char GEerr;
int varidxs;
int varidxi;

char GEVARNAME_S[DMAXVAR_S][DMAXVARNAME_S];
char GEVARNAME_I[DMAXVAR_S][DMAXVARNAME_S];
int GEI[DMAXVAR_S];
char GES[DMAXVAR_S][DMAXLENSTRING];
// char gensprite[128][128];

#define DMAXATACKSPRT 1
#define DMAXDEFENSESPRT 3
#define DMAXSPRTNAME 30

enum _anitype{
   loop,
   forward,
   none
}_anitype;

enum _spritetype{
   character,
   prop,
   mosaic,
   tile,
   bar,
   gauge,
   procedural,
   composed
}_spritetype;

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

#ifdef DRPG
typedef struct _element{
  unsigned char FIRE;
  unsigned char EARTH;
  unsigned char WATHER;
  unsigned char AIR;
}element;

typedef struct _rpg_attr{
  unsigned char STR;
  unsigned char DEX;
  unsigned char HP;
  unsigned char IQ;
  unsigned char XP;
  unsigned char LEVEL;
  element MAGIC;
} rpg_attr;
#endif
bool gepause;
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
  #ifdef DRPG
  float angle;
  rpg_attr rpg;
  #endif
  // --- status of sprite -- ^
  SDL_Rect boxattack;
  SDL_Rect boxdefense;
  GE_animation animation[DMAXSPRTANIMATION];  
  int animationidx;
  //------ Variaveis (uso geral) internas do script---v  
#ifdef DGES  
  int varidxs;
  char GEVARNAME_S[DMAXSPRTVAR_S][DMAXSPRTVARNAME_S];
  char GES[DMAXSPRTVAR_S][DMAXSPRTLENSTRING];
#endif
  int varidxi;
  char GEVARNAME_I[DMAXSPRTVAR_I][DMAXSPRTVARNAME_I];
  int GEI[DMAXSPRTVAR_I]; //------ Variaveis (uso geral) internas do script---^  
  //Scripts do sprite -----v    
  bool script;
  lua_State *SPRTSCRIPT;
  char *filestart;
  char *fileupdate;
  char *fileend;
  //Scripts fo sprite -----^
} sprite;
//---------------------------Define sprites---^

typedef struct _Clone{
  sprite sprite;
  struct _Clone *nextchain;
} Clone;

typedef struct _cloneChain{
   Clone startchain;
} cloneChain;

sprite GE_sprite[DMAXSPRT];

sprite bullets[DBULLETS];
int sprites;
bool ldebug;
bool hide;
bool showbox;
int width;
int height;

SDL_Color defenseboxcolor;
SDL_Color attackboxcolor;
SDL_Color sptboxcolor;
SDL_Color textboxcolor;

typedef struct _font{
   TTF_Font *body;
   int x,y; 
   bool hide;
   char *text;
   SDL_Color color;
}_font;

_font font[10];


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

// int setGEvarS(char *VarNameString, char *varValorS);
// char *getGEvarS(char *VarNameString);

int setGEvarI(char *VarNameString, int varValorI);
int getGEvarI(char *VarNameString);
int Quit_GE(void);

// void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height);

#endif

// - EOF
