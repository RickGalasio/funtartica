#include "console.h"

void clearconsoletext(void){
    memset(consoletxt, 0, sizeof(consoletxt));
    memset(consoletxt_, 0, sizeof(consoletxt_));
}

void termprint(char *txt){
            TVARS(txt);
            history++;
            if (history>DTERMLINES & history<0) history=0;
            if(history>termlinesview+termlineini) 
                termlineini+=termlinesview+1;
            TVARD(history);
            LETS(term[history].txt,txt);

            term[history].txt_[0]='\0';
}

void termclean(void){
            // Clean history: TODO - load history
            for (int i = 0; i < DTERMLINES; i++){
                // term[i].txt[0] = '\0';
                term[i].txt_[0] = '\0';
                 LETSF(term[i].txt, "%d:", i);
            }
            // consoletxt[0]='\0';
            // consoletxt_[0]='\0';
            LETS(consoletxt,term[0].txt);
            LETS(consoletxt_,term[0].txt_);
            history = 0;
}

void slashrun(char *xcommand){
    FILE *fp;
    char line[512];
    int iline;
    int ch;

    if (NULL == (fp = popen(xcommand, "r")))
        ERR("impossível criar processo.");

    iline=0;
    do{
        ch=fgetc(fp);
        if(ch=='\n' || feof(fp)){
            line[iline]='\0';
            //DBG("[%s]",line);
            termprint(line);
            iline=0;
        }else{
            line[iline++]=ch;
            if(iline>sizeof(line)){
                 line[sizeof(line)-1]='\0';
                 termprint(line);
                 iline=0;
            }
        }
    }while(!feof(fp));

    if(pclose(fp) == -1){
      ERR("Error reported by pclose()");
    }
}

void renderconsole(SDL_Renderer *rendscr, int width, int height, int borders){
    SDL_Rect termrect = {borders, borders, width - borders * 2, height - borders * 2};
    SDL_Surface *consolesurface;
    SDL_Texture *consoletexture;
    SDL_Rect textrect;
    int texW = 0, texH = 0;
    //int cr,cg,cb,ca;

    if (console){
        // Create textureconsole only once.
        if (!createdconsole && (textureconsole = (SDL_Texture *)SDL_CreateTexture(
                rendscr,
                SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_STREAMING,
                8, 8))
            )
        {
            DBG("Creating terminal.");
            createdconsole = true;
            unsigned char *bytes = NULL;
            int pitch = 0; 
            SDL_LockTexture(textureconsole, NULL, (void **)&bytes, &pitch);
            unsigned char abgr[4];
            SDL_Color rgba;
             ini_get_color(&rgba, "global", "terminalcolor", "0A,0A,FF,FF");

            abgr[0]=(char) rgba.a;
            abgr[1]=(char) rgba.b;
            abgr[2]=(char) rgba.g;
            abgr[3]=(char) rgba.r;

            for (int y = 0; y < 8; ++y){
                for (int x = 0; x < 8; ++x){
                    memcpy(&bytes[(y * 8 + x) * sizeof(abgr)], abgr, sizeof(abgr));
                }
            }

            SDL_UnlockTexture(textureconsole);

            char fontname[256];
            LETS(fontname, ini_get_str("global", "terminalfont", "ttf/Arcade.ttf"));
            TVARS(fontname);
            if (
                (bodyconsolefont = TTF_OpenFont(fontname,
                    ini_get_int( "global", "terminalfontsize", 12))) == NULL)
            {
                ERR("Error opening console font file");
                exit(1);
            }

            termclean();
            
            // load color of terminal font 
            ini_get_color(&consolecolor, "global", "terminalfontcolor", "0A,0A,FF,FF");

            termlinesview=ini_get_int( "global", "termlinesview", 30);
            termlineini=0;
            consolesolid=ini_get_bool("global", "termsolid", false);
            //AQUI INICIO TERMINAL
        }

        // Draw green console
        if(consolesolid) {
            // SDL_SetTextureBlendMode(textureconsole, SDL_BLENDMODE_NONE);
            SDL_SetTextureBlendMode(textureconsole, SDL_BLENDMODE_INVALID);
        }else {
            SDL_SetTextureBlendMode(textureconsole, SDL_BLENDMODE_MOD);
        }
        SDL_RenderCopy(rendscr, textureconsole, NULL, &termrect);
        
        for (int line = termlineini; line < termlinesview+termlineini; line++){

            // Print text
            if (line-termlineini == history){
                // Blink cursor on the odd miliseconds.
                if (SDL_GetTicks() % 1000 / 100 % 2){
                    LETSF(tmp, "]%s_%s", consoletxt, consoletxt_);
                }else{
                    LETSF(tmp, "]%s %s", consoletxt, consoletxt_);
                }
            }else{
                LETSF(tmp, "%s%s", term[line].txt, term[line].txt_);
            }

            consolesurface = TTF_RenderUTF8_Solid(bodyconsolefont,tmp,consolecolor);
            consoletexture = SDL_CreateTextureFromSurface(rendscr,consolesurface);

            SDL_QueryTexture(consoletexture, NULL, NULL, &texW, &texH); // Get texturefont dimensions
            textrect.h = texH;
            textrect.w = texW;
            textrect.x = borders;
            textrect.y = texH * (line-termlineini) + borders;
            SDL_RenderCopy(rendscr, consoletexture, NULL, &textrect);
            
            if ((line-termlineini) == history){
                SDL_SetRenderDrawColor(rendscr, 255, 255, 255, 255);
                SDL_RenderDrawRect(rendscr, &textrect);
            }

            SDL_DestroyTexture(consoletexture); // TODO: Recreate only if linetext has changes.
            consoletexture = NULL;

            SDL_FreeSurface(consolesurface);
            consolesurface = NULL;
        }
    }
}

void freeconsole(void){
    SDL_DestroyTexture(textureconsole);
}

bool execconsole(char *line){
   bool ret=true;

   // [/q|/quit|/exit] - Exit of engine.
   if( !strcasecmp("/x",line) || !strcasecmp("/q",line) ||
       !strcasecmp("/quit",line) || !strcasecmp("/exit",line) ){
       GE_quit(0);

   // [/cls|/clean|/home] - Clean terminal, history and go to line 0 in terminal
   } else if (!strcasecmp("/cls",line) || !strcasecmp("/clean",line) || !strcasecmp("/clear",line) || !strcasecmp("/home",line) ){
       termclean();

   // [/run |!]<system commands> - Run system/OS commands.  
   } else if (!strncasecmp("!",line,1)){
       LETSF(tmp,"%s &",line+1);
       slashrun(tmp);
   } else if (!strncasecmp("/run ",line,5)){
       LETSF(tmp,"%s &",line+4);
       slashrun(tmp);

    } else if (!strncasecmp("@",line,1)){
       LETSF(tmp,"%s",line+1);
       luaL_dostring(GLSCRIPT,tmp);

    } else if (!strncasecmp("/lua ",line,5)){
       LETSF(tmp,"%s",line+5);
       luaL_dostring(GLSCRIPT,tmp);

//    [/ls|/show] <variable> - List all variables or specified <variable> 
   } else if (!strcasecmp("/show",line)||!strcasecmp("/ls",line)){
       DBG("Sprite Variables:");
       for (int i = 0 ; i < sprites; i++){
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_hide=%d", GE_sprite[i].name, GE_sprite[i].hide);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_x=%d", GE_sprite[i].name,GE_sprite[i].pos.x);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_y=%d", GE_sprite[i].name,GE_sprite[i].pos.y);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_w=%d", GE_sprite[i].name,GE_sprite[i].pos.w);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_h=%d", GE_sprite[i].name,GE_sprite[i].pos.h);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_life=%d", GE_sprite[i].name,GE_sprite[i].life);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_showbox=%d", GE_sprite[i].name,GE_sprite[i].showbox);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_x=%d", GE_sprite[i].name,GE_sprite[i].boxattack.x);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_y=%d", GE_sprite[i].name,GE_sprite[i].boxattack.y);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_w=%d", GE_sprite[i].name,GE_sprite[i].boxattack.w);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_attack_h=%d", GE_sprite[i].name,GE_sprite[i].boxattack.h);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_x=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.x);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_y=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.y);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_w=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.w);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_defense_h=%d", GE_sprite[i].name,GE_sprite[i].boxdefense.h);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_flip=%d", GE_sprite[i].name,GE_sprite[i].flip);
            termprint(tmp);
            snprintf(tmp, DMAXLINESCRIPT, "sprt_%s_tick=%d", GE_sprite[i].name,GE_sprite[i].tick);
            termprint(tmp);
        }
        DBG("Global Variables:");
        for (int i = 0 ; i < maxvars; i++){
           snprintf(tmp, DMAXLINESCRIPT,"%s=%d",getvarnamei(i),getGEI(i));
           termprint(tmp);
        }
   }else if (!strncasecmp("/show ",line,6)){
       snprintf(tmp, DMAXLINESCRIPT,"%s=%d",line+6,getGEvarI(line+6));
       termprint(tmp);
   }else if (!strncasecmp("/ls ",line,4)){
       snprintf(tmp, DMAXLINESCRIPT,"%s=%d",line+4,getGEvarI(line+4));
       termprint(tmp);

   // [/set <variable> <integer>] - Set/create an engine integer variable.
   }else if (!strncasecmp("/set ",line,5)){
       int i=5,j=0;
       char varname[50];
       memset(varname, 0,sizeof(varname));
       do{ 
           varname[j++]=line[i];
           i++;
        } while(line[i]!=' ' && i<strlen(line));
        DBG("set [%s] [%d]",varname, atoi(line+i));
        setGEvarI(varname,atoi(line+i) );

     }else if (!strcasecmp("/pause",line) ||
                !strcasecmp("/stop",line) 
              ){
        DBG("paused..");
        gepause=true;
    }else if (!strcasecmp("/unpause",line) ||
               !strcasecmp("/continue",line) ||
               !strcasecmp("/cont",line) ||
               !strcasecmp("/start",line) 
             ){
        DBG("unpaused..");
        gepause=false;

   }else {
    //    LETSF(tmp,"%s",line);
       luaL_dostring(GLSCRIPT,line);
//       ret=false;
   }

   return ret;
}

// - EOF

