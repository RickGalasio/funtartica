#ifndef _GELUA_H_
#define _GELUA_H_

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// static lua_State* GLSCIPT;
static lua_State* GLSCRIPT;

lua_State* Create_GElua(char *filename, bool readglobal);
lua_State* Create_GEluaS(char *prog, bool readglobal);

int destroy_GElua(lua_State *L);
static int LsetGEvarI(lua_State *L);

#endif
// - EOF
