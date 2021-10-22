#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PG_VER "0.16"
#define PG_DATE  __DATE__ 
#define PG_TIME  __TIME__ 

#define FILELOG "./log/debug.log"
#define DEBUGBANNER "*Funtartica version:" PG_VER "\n**** Compiled in " PG_DATE " - " PG_TIME " Hs \n----------------------------------------------------------------\n"
//-----GLOBAL--------------------
#define DMAXLENSTRING 50  
#define DMAXVAR_I 100
#define DMAXVARNAME_I 60
#define DMAXLINESCRIPT 255 
#define DBULLETS 15
//-----GLOBAL--------------------
//-----SOUNDS--------------------
#define DMAXSOUNDS 10
//-----SOUNDS--------------------
//-----SPRT----------------------
#define DMAXSPRT 20 // max. sprites.
#define DMAXSPRTANIMATION 5 // max. sprite animations
#define DMAXANIFRAME 5 //Max frames of animation 
#define DMAXSPRTVAR_I 10
#define DMAXSPRTVARNAME_I 15
#define DMAXATACKSPRT 1
#define DMAXDEFENSESPRT 3
#define DMAXSPRTNAME 30
#define SPT_BACKGROUND 0
#define SPT_SHIP 1 
#define SPT_BUG 2
#define SPT_BULLET 3
#define SPT_EXPLOSION 4
#define SPT_BOY 5
#define SPT_SHEEP 6
//-----SPRT----------------------
#define DTERMLINES 100
#define DHELP " -c - pathname of configfile. Default: ./ge.ini\n "
#endif
// - EOF
