#ifndef _GELUA_H_
#define _GELUA_H_

#include "compile.h"

#ifdef WLUAJIT
#include <luajit-2.1/lua.h>
#include <luajit-2.1/lualib.h>
#include <luajit-2.1/lauxlib.h>
#endif

#ifdef WLUA53
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>
#endif

#ifdef WLUA51
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#endif

// static lua_State *L;
lua_State* GLSCRIPT;

lua_State* Create_GElua(char *filename, bool readglobal);
lua_State* Create_GEluaS(char *prog, bool readglobal);

int destroy_GElua(lua_State *L);
static int LsetGEvarI(lua_State *L);

#endif
// - EOF