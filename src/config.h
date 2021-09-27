#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PG_VER "0.12"
#define PG_DATE  __DATE__ 
#define PG_TIME  __TIME__ 

#define FILELOG "./log/debug.log"
#define DEBUGBANNER "*GE version:" PG_VER "\n**** Compiled at " PG_DATE " - " PG_TIME " Hs \n----------------------------------------------------------------\n"

//-----GLOBAL--------------------

//#define DGES 1 // Define variavel string
//#define DRPG // Funçoes e parametros de RPG

#define DMAXLENSTRING 50  

#define DMAXVAR_S 10 
#define DMAXVARNAME_S 30 

#define DMAXVAR_I 10
#define DMAXVARNAME_I 30

#define DMAXLINESCRIPT 255 

#define DBULLETS 15
//-----GLOBAL--------------------

//-----SOUNDS--------------------
#define DMAXSOUNDS 10
//-----SOUNDS--------------------

//-----SPRT----------------------

//#define DMAXSPRTLENSTRING 15  
#define DMAXSPRT 20 // max. sprites.
#define DMAXSPRTANIMATION 5 // max. sprite animations
#define DMAXANIFRAME 5 //Max frames of animation 

//#define DMAXSPRTVAR_S 10 
//#define DMAXSPRTVARNAME_S 15

#define DMAXSPRTVAR_I 10
#define DMAXSPRTVARNAME_I 15

#define SPT_BACKGROUND 0
#define SPT_SHIP 1 
#define SPT_BUG 2
#define SPT_BULLET 3
#define SPT_EXPLOSION 4
#define SPT_BOY 5
#define SPT_SHEEP 6

//-----SPRT----------------------

#define DSCRIPT "./ini.lua"

#define DHELP " -c - pathname of configfile. Default: ./ge.ini\n "

#endif




// - EOF
