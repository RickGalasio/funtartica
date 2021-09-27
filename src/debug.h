#ifndef _DEBUG_H_
#define _DEBUG_H_

//#include "tests/stb/stb_sprintf.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define DBG_INIT( ...) snprintf(dbg_mess,sizeof(dbg_mess), __VA_ARGS__); __dbg_init__( dbg_mess, __FILE__, __LINE__ )
#define DBG( ...) snprintf(dbg_mess,sizeof(dbg_mess), __VA_ARGS__)< 0 ? abort() : (void)0; __dbg__(dbg_mess, __FILE__, __LINE__) 
#define MSG( ...) snprintf(dbg_mess,sizeof(dbg_mess), __VA_ARGS__)< 0 ? abort() : (void)0; __dbg__(dbg_mess, __FILE__, __LINE__) 
#define LOG( ...) snprintf(dbg_mess,sizeof(dbg_mess), __VA_ARGS__)< 0 ? abort() : (void)0; __dbg__(dbg_mess, __FILE__, __LINE__) 
#define ERR( ...) snprintf(dbg_mess,sizeof(dbg_mess), "ERR: " __VA_ARGS__)< 0 ? abort() : (void)0; __dbg__(dbg_mess, __FILE__, __LINE__)
#define DB DBG(".")

#define TVARS( a ) snprintf(dbg_mess,sizeof(dbg_mess), # a ":%s", a )< 0 ? abort() : (void)0; __dbg__(dbg_mess, __FILE__, __LINE__)
#define TVARD( a ) snprintf(dbg_mess,sizeof(dbg_mess), # a ":%d", a )< 0 ? abort() : (void)0; __dbg__(dbg_mess, __FILE__, __LINE__)

void __dbg_init__( char *log_mess, char *n_file ,int n_line);

void __dbg__( char *log_mess, char *n_file ,int n_line );

char dbg_mess[ 255 ];

#endif





// - EOF
