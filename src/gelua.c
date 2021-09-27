#include "globals.h"
#include "gelua.h"
#include "debug.h"

//=====================================================
lua_State* Create_GElua(char *filename, bool readglobal){
   char tmp[DMAXLINESCRIPT];
   // initialize Lua interpreter
   lua_State *L=malloc(sizeof(lua_State *));
   L = luaL_newstate();

   // load Lua base libraries (print / math / etc)
   luaL_openlibs(L);

   lua_register(L, "seti", LsetGEvarI);

   if (readglobal){
      // Carrega variaveis globais int no script
      MSG("Carregando variaveis globais no script");
      for (int i = 0; i < DMAXVAR_I && strcmp(GEVARNAME_I[i], "NULL") != 0; i++){
         snprintf(tmp, DMAXLINESCRIPT, "%s = \"%d\";", GEVARNAME_I[i], getGEI(i));
         luaL_dostring(L, tmp);
      }
//---------------------------------------------------
      for (int i = 0 ; i < sprites; i++){
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_hide=%d", GE_sprite[i].name, GE_sprite[i].hide);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_x=%d", GE_sprite[i].name,GE_sprite[i].pos.x);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_y=%d", GE_sprite[i].name,GE_sprite[i].pos.y);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_w=%d", GE_sprite[i].name,GE_sprite[i].pos.w);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_h=%d", GE_sprite[i].name,GE_sprite[i].pos.h);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_life=%d", GE_sprite[i].name,GE_sprite[i].life);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_showbox=%d", GE_sprite[i].name,GE_sprite[i].showbox);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_x=%d", GE_sprite[i].name,GE_sprite[i].boxattack.x);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_y=%d", GE_sprite[i].name,GE_sprite[i].boxattack.y);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_w=%d", GE_sprite[i].name,GE_sprite[i].boxattack.w);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_h=%d", GE_sprite[i].name,GE_sprite[i].boxattack.h);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_x=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.x);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_y=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.y);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_w=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.w);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_h=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.h);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_flip=%d", GE_sprite[i].name,GE_sprite[i].flip);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_tick=%d", GE_sprite[i].name,GE_sprite[i].tick);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
      }
//---------------------------------------------------
   }else 
      MSG("Carregando variaveis globais no script");

   //Executa script start
   if (strlen(filename)){
      if (luaL_dofile(L, filename)){
         ERR("%s\n", lua_tostring(L, -1));
      }
   }else{
    MSG("There is no start script");
   }

   return(L);
}
//=====================================================
lua_State* Create_GEluaS(char *prog, bool readglobal){
   char tmp[DMAXLINESCRIPT];
   // initialize Lua interpreter
   lua_State *L=malloc(sizeof(lua_State *));
   L = luaL_newstate();

   // load Lua base libraries (print / math / etc)
   luaL_openlibs(L);

   lua_register(L, "seti", LsetGEvarI);

   if (readglobal){
      // Carrega variaveis globais int no script
      MSG("Carregando variaveis globais no script");
      for (int i = 0; i < DMAXVAR_I && strcmp(GEVARNAME_I[i], "NULL") != 0; i++){
         snprintf(tmp, DMAXLINESCRIPT, "%s = \"%d\";", GEVARNAME_I[i], getGEI(i));
         luaL_dostring(L, tmp);
      }
//---------------------------------------------------
      for (int i = 0 ; i < sprites; i++){
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_hide=%d", GE_sprite[i].name, GE_sprite[i].hide);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_x=%d", GE_sprite[i].name,GE_sprite[i].pos.x);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_y=%d", GE_sprite[i].name,GE_sprite[i].pos.y);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_w=%d", GE_sprite[i].name,GE_sprite[i].pos.w);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_h=%d", GE_sprite[i].name,GE_sprite[i].pos.h);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_life=%d", GE_sprite[i].name,GE_sprite[i].life);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_showbox=%d", GE_sprite[i].name,GE_sprite[i].showbox);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_x=%d", GE_sprite[i].name,GE_sprite[i].boxattack.x);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_y=%d", GE_sprite[i].name,GE_sprite[i].boxattack.y);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_w=%d", GE_sprite[i].name,GE_sprite[i].boxattack.w);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_h=%d", GE_sprite[i].name,GE_sprite[i].boxattack.h);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_x=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.x);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_y=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.y);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_w=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.w);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_h=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.h);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_flip=%d", GE_sprite[i].name,GE_sprite[i].flip);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
         snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_tick=%d", GE_sprite[i].name,GE_sprite[i].tick);
         // TVARS(tmp);
         luaL_dostring(L, tmp);
      }
//---------------------------------------------------
   }else 
      MSG("Carregando variaveis globais no script");

	if (luaL_dostring(L, prog)){
		ERR("%s\n", lua_tostring(L, -1));
	}else{
      MSG("There is no start script");  
   }

   return(L);
}
//=====================================================
int destroy_GElua(lua_State *L){
   luaL_dostring(L, "print(\"End Script\")");
   lua_close(L);
   return(0);
}

//=====================================================
static int LsetGEvarI(lua_State *L){
   char VarNameString[DMAXVARNAME_I];
   int varValorI;
   int ret;

   snprintf(VarNameString, sizeof(char)*DMAXVARNAME_I, "%s", luaL_checkstring(L, 1));
   varValorI = luaL_checkinteger(L, 2);
   ret = setGEvarI(VarNameString, varValorI);

   return (ret);
}




// - EOF
