#ifndef _DEBUG_H_
#define _DEBUG_H_

//#include "tests/stb/stb_sprintf.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define DBG_INIT( ...) sprintf(dbg_mess, __VA_ARGS__); __dbg_init__( dbg_mess, __FILE__, __LINE__ )
#define DBG( ...) sprintf(dbg_mess, __VA_ARGS__); __dbg__(dbg_mess, __FILE__, __LINE__) 
#define MSG( ...) sprintf(dbg_mess, __VA_ARGS__); __dbg__(dbg_mess, __FILE__, __LINE__) 
#define LOG( ...) sprintf(dbg_mess, __VA_ARGS__); __dbg__(dbg_mess, __FILE__, __LINE__) 
#define ERR( ...) sprintf(dbg_mess, "ERR: " __VA_ARGS__); __dbg__(dbg_mess, __FILE__, __LINE__)
#define DB DBG(".")

#define TVARS( a ) sprintf(dbg_mess, # a ":%s", a ); __dbg__(dbg_mess, __FILE__, __LINE__)
#define TVARD( a ) sprintf(dbg_mess, # a ":%d", a ); __dbg__(dbg_mess, __FILE__, __LINE__)

void __dbg_init__( char *log_mess, char *n_file ,int n_line);

void __dbg__( char *log_mess, char *n_file ,int n_line );

char dbg_mess[ 255 ];

#endif





// - EOF
