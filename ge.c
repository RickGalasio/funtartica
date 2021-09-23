#include <strings.h>
#include <math.h>
#include "ge.h"
#include "gelua.h"
#include "inifiles.h"
#include "globals.h"
#include "debug.h"
#include "config.h"
#include "inputs.h"
#include "getileset.h"
#include "gensprite.h"

//---------------------------------------------------------------v
// fast parse variables in strigs
char *parservar(char *intext){
	char xvarname[DMAXVARNAME_I];
	char svalor[255];
	int a=0, b=0, c=0, o=0;
	size_t outlen=1*sizeof(char);  
	bool conta=true;
	while(intext[a]!='\0'){
	   if(intext[a]=='%') {
		   outlen+=12*sizeof(char);
		   conta=false;
	   }  
	   if(intext[a]==' ') conta=true;
	   if(conta) outlen+=1*sizeof(char);
	   a++;
	}
	a=0;
    char *outtext=(char *)malloc(outlen*sizeof(char));
	bzero(svalor, sizeof(svalor));
	while (intext[a] != '\0'){
		if (intext[a] == '\0'){
			outtext[o] = '\0';
			break;
		}
		while (intext[a] != '%' && intext[a] != '\0'){
			outtext[o++] = intext[a++];
		}
		outtext[o] = '\0';
		if (intext[a] == '%'){
			a++;
			b = 0;
			bzero(xvarname, sizeof(xvarname));
			while(intext[a]!=' ' && intext[a]!='\0'){
				xvarname[b++] = intext[a++];
			}
			LETSF(svalor, "%d", getGEvarI(xvarname));
			for (c = 0; isdigit(svalor[c]); c++){
				outtext[o++] = svalor[c];
			}
			outtext[o] = '\0';
		}
	}
	outtext[o] = '\0';
	outtext=realloc(outtext,sizeof(char)*strlen(outtext)+1);
	return outtext;
}
//---------------------------------------------------------------^

void GE_load_fonts(void){
	// Carrega fonte default
	fonts = ini_get_int(configfile, "global", "fonts", 1) - 1;
	for (int nf = 0; nf <= fonts; nf++){
		// unsigned int r, g, b;
		char filenamefont[50];
		char sfont[7];
		int fstyle;
		LETSF(sfont, "font%d", nf + 1);

		LETS(filenamefont, ini_get_str(configfile, sfont, "file", "./ttf/Arcade.ttf"));
		font[nf].x = ini_get_int(configfile, sfont, "x", 0);
		font[nf].y = ini_get_int(configfile, sfont, "y", 0);
		font[nf].hide = ini_get_bool(configfile, sfont, "hide", hide);

		MALETS(font[nf].text, ini_get_str(configfile, sfont, "text", "NULL"));

		ini_get_color(&font[nf].color, configfile, sfont, "color", "00,FF,00,00");

		// font[nf].color.a=a;
		font[nf].color.a = 0; // Verificar se transparencia funciona;
		if ((font[nf].body = TTF_OpenFont(filenamefont, ini_get_int(configfile, sfont, "size", 12))) == NULL){
			ERR("Error opening file:%s", filenamefont);
			exit(1);
		}

		fstyle = 0;
		fstyle = ini_get_int(configfile, sfont, "bold", false) * 1;
		fstyle += ini_get_int(configfile, sfont, "italic", false) * 2;
		fstyle += ini_get_int(configfile, sfont, "underline", false) * 4;
		fstyle += ini_get_int(configfile, sfont, "strikethrough", false) * 8;
		TTF_SetFontStyle(font[nf].body, fstyle);
		TTF_SetFontOutline(font[nf].body, ini_get_int(configfile, sfont, "outline", 0));

		char hinting[7];
		LETS(hinting, ini_get_str(configfile, sfont, "hinting", "normal"));

		if (!strcasecmp(hinting, "normal")){
			TTF_SetFontHinting(font[nf].body, TTF_HINTING_NORMAL);
		}else if (!strcasecmp(hinting, "light")){
			TTF_SetFontHinting(font[nf].body, TTF_HINTING_LIGHT);
		}else if (!strcasecmp(hinting, "mono")){
			TTF_SetFontHinting(font[nf].body, TTF_HINTING_MONO);
		}else if (!strcasecmp(hinting, "none")){
			TTF_SetFontHinting(font[nf].body, TTF_HINTING_NONE);
		}else{
			ERR("hinting in [%s], strange parameter:%s", sfont, hinting);
		}
	}

}

void GE_load_debug_box(void){
    ldebug = ini_get_bool(configfile, "global", "debug", false);
	hide = ini_get_bool(configfile, "global", "hide", false);
	showbox = ini_get_bool(configfile, "global", "showbox", false);
	consoleborder = ini_get_int(configfile, "global", "consoleborder",20);

    if(showbox){
		ini_get_color(&sptboxcolor,configfile, "global", "sptboxcolor", "ff,ff,ff,ff");
   		ini_get_color(&attackboxcolor,configfile, "global", "attackboxcolor", "ff,ff,ff,ff");
	    ini_get_color(&defenseboxcolor, configfile, "global", "defenseboxcolor", "ff,ff,ff,ff");
	}
}

void GE_load_sprites(void){
	//===Load sprites==========================================================================================v
	DBG("GE_loadsprites()");
	for (sprites = 0; sprites < ini_get_int(configfile, "global", "sprites", 1); sprites++){
		LETSF(spriteN, "sprite%d", sprites + 1);

		// Load Sprite variables in inifile
		MALETS(GE_sprite[sprites].name, ini_get_str(configfile, spriteN, "name", "noname"));
		// TVARS(GE_sprite[sprites].name);
		GE_sprite[sprites].hide = ini_get_bool(configfile, spriteN, "hide", hide);
		GE_sprite[sprites].showbox = ini_get_bool(configfile, spriteN, "showbox", showbox);

		//## Load Lua scripts
		GE_sprite[sprites].script = false;
		MALETS(GE_sprite[sprites].filestart, ini_get_str(configfile, spriteN, "start", ""));
		MALETS(GE_sprite[sprites].fileupdate, ini_get_str(configfile, spriteN, "update", ""));
		MALETS(GE_sprite[sprites].fileend, ini_get_str(configfile, spriteN, "end", ""));

		char spritetype[10];
		LETS(spritetype, ini_get_str(configfile, spriteN, "type", "character"));
		// DBG("SELECT [%s] type: %s",spriteN,spritetype);
		if (!strcasecmp(spritetype, "character")){
			GE_sprite[sprites].spritetype = character;
		}
		else if (!strcasecmp(spritetype, "prop")){
			GE_sprite[sprites].spritetype = prop;
		}else if (!strcasecmp(spritetype, "mosaic")){
			GE_sprite[sprites].spritetype = mosaic;
		}else if (!strcasecmp(spritetype, "tile")){
			GE_sprite[sprites].spritetype = tile;
		}else if (!strcasecmp(spritetype, "bar")){
			GE_sprite[sprites].spritetype = bar;
		}else if (!strcasecmp(spritetype, "gauge")){
			GE_sprite[sprites].spritetype = bar;
		}else if (!strcasecmp(spritetype, "procedural") || !strcasecmp(spritetype, "proc")){
			GE_sprite[sprites].spritetype = procedural;
		}else if (!strcasecmp(spritetype, "composed")){
			GE_sprite[sprites].spritetype = composed;
		}

		GE_sprite[sprites].flip = ini_get_bool(configfile, spriteN, "flip", "false");
		GE_sprite[sprites].tick = ini_get_int(configfile, spriteN, "tick", 0);
		GE_sprite[sprites].life = ini_get_int(configfile, spriteN, "life", 0);
		GE_sprite[sprites].showbox = ini_get_int(configfile, spriteN, "showbox", showbox);
		GE_sprite[sprites].pos.x = ini_get_int(configfile, spriteN, "x", 0);
		GE_sprite[sprites].pos.y = ini_get_int(configfile, spriteN, "y", 0);
		GE_sprite[sprites].pos.w = ini_get_int(configfile, spriteN, "w", 0);
		GE_sprite[sprites].pos.h = ini_get_int(configfile, spriteN, "h", 0);
		GE_sprite[sprites].boxattack.x = ini_get_int(configfile, spriteN, "attack_x", 0);
		GE_sprite[sprites].boxattack.y = ini_get_int(configfile, spriteN, "attack_y", 0);
		GE_sprite[sprites].boxattack.w = ini_get_int(configfile, spriteN, "attack_w", 0);
		GE_sprite[sprites].boxattack.h = ini_get_int(configfile, spriteN, "attack_h", 0);
		GE_sprite[sprites].boxdefense.x = ini_get_int(configfile, spriteN, "defense_x", 0);
		GE_sprite[sprites].boxdefense.y = ini_get_int(configfile, spriteN, "defense_y", 0);
		GE_sprite[sprites].boxdefense.w = ini_get_int(configfile, spriteN, "defense_w", 0);
		GE_sprite[sprites].boxdefense.h = ini_get_int(configfile, spriteN, "defense_h", 0);
		GE_sprite[sprites].animationidx = ini_get_int(configfile, spriteN, "defaultanimation", 1) - 1;

		//Sprite is a mosaic (tiled sprite)
		if (GE_sprite[sprites].spritetype == mosaic){

			//tcolor is an temporary color RGBA value for tilemap.
			// DBG("tcolor is an temporary color RGBA value for tilemap.");
			SDL_Color mtcolor = {0, 0, 0, 0};

			ini_get_color(&mtcolor,configfile, spriteN, "color", "ff,00,00,ff");

			GE_sprite[sprites].animation[0].textFrame[0] = getilemap(configfile,
				 spriteN, rendscr, mtcolor, width, height);
		}else if (GE_sprite[sprites].spritetype == procedural){

     DBG("GENSPRITE [sprite%d]",sprites+1);

			GE_sprite[sprites].animation[0].textFrame[0] = gensprite(configfile,
				spriteN,
				rendscr
			);

		}else{ // if character or prop
			// if Sprite is a character or prop
			for (int animations = 0;
				 (GE_sprite[sprites].spritetype == character 
				 || GE_sprite[sprites].spritetype == prop)
				 && animations < ini_get_int(configfile, spriteN, "animations", 1);
				 animations++)
			{
				char paramx[20];
				char sanitype[20];
				LETSF(paramx, "anima%dtype", animations + 1)
				LETS(sanitype, ini_get_str(configfile, spriteN, paramx, "none"));

				if (!strcasecmp("none", sanitype)){
					GE_sprite[sprites].animation[animations].anitype = none;
				}else if (!strcasecmp("loop", sanitype)){
					GE_sprite[sprites].animation[animations].anitype = loop;
				}else if (!strcasecmp("forward", sanitype)){
					GE_sprite[sprites].animation[animations].anitype = forward;
				}else{
					ERR("invalid anima%dtype in sprite[%s]", animations + 1, spriteN);
					GE_sprite[sprites].animation[animations].anitype = none;
				}

				GE_sprite[sprites].animation[animations].frameidx = 0;
				LETSF(animationSTUFFS, "anima%dspeed", animations + 1);
				GE_sprite[sprites].animation[0].speed = ini_get_int(configfile, spriteN, animationSTUFFS, 150);

				LETSF(animationSTUFFS, "anima%dframes", animations + 1);
				GE_sprite[sprites].animation[animations].maxframes = ini_get_int(configfile, spriteN, animationSTUFFS, 1);

				for (int frame = 0; frame < GE_sprite[sprites].animation[animations].maxframes; frame++){
					SDL_Surface *surfacetemp;
					LETSF(animaNframeN, "anima%dframe%d", animations + 1, frame + 1);
					LETS(filename, ini_get_str(configfile, spriteN, animaNframeN, "./img/not_found.png"));

					// Carrega imagem de fundo padrão.
					if ((surfacetemp = IMG_Load((const char *)filename)) == NULL){
						ERR("Unable to open sprite-frame file: %s", filename);
						exit(0);
					}else{
						// DBG("carrega imagem: %s",filename);
						GE_sprite[sprites].animation[animations].textFrame[frame] = (SDL_Texture *)SDL_CreateTextureFromSurface(rendscr, surfacetemp);
						SDL_FreeSurface(surfacetemp);
					}
				}
			} // for animations
		} // if character or prop
	} // for(sprites ...) load sprite-frames
	//===GE Load sprites==========================================================================================^
	// DBG("Load GE_sprites END");	
}
//---------------------------------------------------------------v
int main(int argc, char *argv[]){
	DBG_INIT("START G.ENGINE");
	
	DBG("srand");
	srand(time(0));
	msrand(time(0));

	//--parametrer of command line----------------------v
	MALETS(configfile, "./ge.ini");
	for (int i = 1; argv[i]; ++i){
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "-help")){
			MSG(DHELP);
			exit(0); 
		}else if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "-config")){
			i++;
			FREESEC(configfile);
			MALETS(configfile, argv[i]);
			// TVARS(argv[i]);
		}else{
			ERR("Parameter does not exist!: %s", argv[i]);
			exit(1);
		}
	}
	//--parametrer of command line----------------------^

	//##
	// MSG("ANTES DO INI");
	// exit(1);

	//---Init SDL2----------v
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0){
		ERR("Unable to start SDL2: %s", SDL_GetError());
		exit(1);
	}else{
		DBG("SDL2 started.");
	}

	width = ini_get_int(configfile, "global", "w", 1024);
	height = ini_get_int(configfile, "global", "h", 768);

	if (SDL_CreateWindowAndRenderer(width, height, 
	 SDL_RENDERER_ACCELERATED |
	 SDL_WINDOW_SHOWN |
	 SDL_WINDOW_INPUT_FOCUS, &windscr, &rendscr)){
		ERR("Couldn't create window and renderer: %s", SDL_GetError());
		return 0;
	}

	if (windscr == NULL){
		ERR("Unable to open window: %s", SDL_GetError());
		return 0;
	}else{
		DBG("Window, ok.");
	}
	//---Init SDL2----------^

    //--Init ID Window-----v
	char project[200];
	LETS(project, ini_get_str(configfile, "global", "name", "GEngine version:" PG_VER));

	SDL_SetWindowTitle(windscr, (const char *)project);

	char fileicon[25];
	LETS(fileicon, ini_get_str(configfile, "global", "icon", "./img/GE.png"));
	if ((icon = IMG_Load((const char *)fileicon)) == NULL){
		ERR("Unable to open icon file:%s", fileicon);
	}else{
		MSG("Icon file, ok (w:%d,h:%d)", icon->w, icon->h);
		SDL_SetWindowIcon(windscr, icon);
	}
	//--Init ID Window-----^
	
		
	//--Init TTF lib-----v
	if (TTF_Init() < 0){
		ERR("Unable to start SDL2_TFF: %s", SDL_GetError());
		return 0;
	}else{
		DBG("SDL_ttf, ok.");
	}
	//--Init TTF lib-----^

    //--init Audio------v
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) < 0){
		ERR("Unable to Mix_OpenAudio(): %s\n", SDL_GetError());
		return 0;
	}else{
		MSG("Mix_OpenAudio, ok.");
		MSG("TODO: Colocar parametros de audio em .INI");
	}
	//--init Audio------^

	GE_load_sounds();

    GE_load_fonts();

    GE_load_debug_box();

	GE_load_sprites();

	// DBG("Load bullets from GE_sprite[SPT_BULLET]");
	//==Load bullets from GE_sprite[SPT_BULLET]============================================================================v
	LETS(filename, ini_get_str(configfile, "sprite4", "anima1frame1", "./img/not_found.png"));
	for (int i = 0; i < DBULLETS; i++){
		SDL_Surface *surfacetemp;
		bullets[i].animation->anitype = none;
		if ((surfacetemp = IMG_Load((const char *)filename)) == NULL){
			ERR("Unable to bullet file: %s", filename);
			return 0;
		}else{
			bullets[i].animation[0].textFrame[0] = SDL_CreateTextureFromSurface(rendscr, surfacetemp);
			SDL_FreeSurface(surfacetemp);
		}
		bullets[i].pos.x = GE_sprite[SPT_BULLET].pos.x;
		bullets[i].pos.y = GE_sprite[SPT_BULLET].pos.y;
		bullets[i].pos.w = GE_sprite[SPT_BULLET].pos.w;
		bullets[i].pos.h = GE_sprite[SPT_BULLET].pos.h;
		bullets[i].boxattack.x = GE_sprite[SPT_BULLET].boxattack.x;
		bullets[i].boxattack.y = GE_sprite[SPT_BULLET].boxattack.y;
		bullets[i].boxattack.w = GE_sprite[SPT_BULLET].boxattack.w;
		bullets[i].boxattack.h = GE_sprite[SPT_BULLET].boxattack.h;
		bullets[i].boxdefense.x = GE_sprite[SPT_BULLET].boxdefense.x;
		bullets[i].boxdefense.y = GE_sprite[SPT_BULLET].boxdefense.y;
		bullets[i].boxdefense.w = GE_sprite[SPT_BULLET].boxdefense.w;
		bullets[i].boxdefense.h = GE_sprite[SPT_BULLET].boxdefense.h;
		bullets[i].showbox = GE_sprite[SPT_BULLET].showbox;
		bullets[i].hide = true;
		bullets[i].animation->frameidx = 0;
	}
	//==Load bullets from GE_sprite[SPT_BULLET]============================================================================^
	// DBG("Load bullets from GE_sprite[SPT_BULLET] END");
	// DBG("Sprites CARREGADOS...");

	//--Init. mov. actor vars----v
	//--Init. mov. actor vars--- ^

	//-Init. FPS---v
	tstart = SDL_GetTicks(); // inicia contadores de FPS
	fps = 0;
	setGEvarI("fps", 0);
	//-Init. FPS---^

	int clearbg = ini_get_int(configfile, "global", "clear", 0) - 1;

	ini_get_color(&bgcolor,configfile, "global", "color", "ff,00,00,ff");
	//========================================================================================VVVV
	SDL_Rect rect;
	SDL_Rect a, b;

	// start script
	int texW = 0;
	int texH = 0;
	SDL_Rect textrect;
	int nf, ibullet;
	char *prog;

    DBG("INICIANDO sistema unico de scripts...(sem threads)");
	MALETS(filescript, ini_get_str(configfile, "scripts", "start", ""));
	if (strlen(filescript)){
		DBG("Creating GLSCRIPT from %s file",filescript);
		GLSCRIPT = Create_GElua(filescript, true);
		DBG("Global Start Script: %s", filescript);
	}else{
		prog=ini_get_lua(configfile, "scripts", "start");
		if(prog){
		DBG("Creating GLSCRIPT from inline start{.. of [scripts] section of %s ini file.",configfile);
		GLSCRIPT = Create_GEluaS(prog, true);
		free(prog);
		}else{
		   ERR("There is no start script file");
		}
	}
	free(filescript); // for reuse in update script in main loop
	
	// DBG("ADD AND RUN SPRITES SCRIPTS ### REFAC:%d", sprites);
	for (int i = 0; i < sprites; i++){
		if (strlen(GE_sprite[i].filestart)){
			DBG("[Sprite:(%s) start script:{%s}]", GE_sprite[i].name, GE_sprite[i].filestart);
			if(GLSCRIPT){
			   DBG("Rodando script start (%s) de sprite (%s)",GE_sprite[i].filestart, GE_sprite[i].name);
			   if (luaL_dofile(GLSCRIPT, GE_sprite[i].filestart)){
				   ERR("%s\n", lua_tostring(GLSCRIPT, -1));
			   }
			}else{
				MSG("Sprite script não iniciado, falta definir start script");
			}
		}
	}

	DBG("Carrega o script update global para ser executado pelo main loop.");
	MALETS(filescript, ini_get_str(configfile, "scripts", "update", ""));
	if (strlen(filescript)){
		gupdateok = true;
		MSG("Update script:%s", filescript);
	}else{
		gupdateok = false;
		MSG("There is no update script file");
	}

    DBG("Carrega o script end global para ser executado no final do main loop. TODO");
	MALETS(filescriptend, ini_get_str(configfile, "scripts", "end", ""));
	if (strlen(filescriptend)){
		// gendok = true;
		MSG("End script:%s", filescriptend);
	}else{
		// gendok = false;
		MSG("There is no end script file");
	}

	// free(filescriptend);
	//##
	// ERR("SAIDA FORÇADA");
	// goto Quit_GE;
console=false;
gepause=false;
inputmode=play;
clearconsoletext();
//== LOOP ======================================================================================vvvv
DBG("Main Loop...");

// if (ldebug) {
// 	DBG("################################ Cake rage quit...");
// 	goto  Quit_GE;
// }

while (!quit){
	// TVARD(gepause);

	if (inputs()) goto Quit_GE;

	if (!gepause){
		//-run-global-update-script------------v
		if (gupdateok){
			if (GLSCRIPT){
				if (luaL_dofile(GLSCRIPT, filescript)){
					ERR("%s\n", lua_tostring(GLSCRIPT, -1));
					goto Quit_GE;
				}
			}else{
				MSG("Script lua não iniciado anteriormente.");
			}
		}
		//-run-global-update-script------------^

		//-run-sprites-update-scripts------------v
		//-run-sprites-update-scripts------------^

		//-Move Bullet ------------------v
		for (ibullet = 0; ibullet < DBULLETS; ibullet++)
		{
			//---check bullet colision---------------------------------------------v
			//DBG("bullets[%d].hide=%d",ibullet,bullets[ibullet].hide);
			if (bullets[ibullet].hide == false)
			{
				bullets[ibullet].pos.y -= 1;
				if (bullets[ibullet].pos.y < 0)
				{
					bullets[ibullet].hide = true;
					bullets[ibullet].pos.y = 0;
				}
				if (!GE_sprite[SPT_BUG].hide)
				{
					a.x = bullets[ibullet].pos.x + bullets[ibullet].boxattack.x;
					a.y = bullets[ibullet].pos.y + bullets[ibullet].boxattack.y;
					a.w = bullets[ibullet].boxattack.w;
					a.h = bullets[ibullet].boxattack.h;
					a.x = bullets[ibullet].pos.x + bullets[ibullet].boxdefense.x;
					a.y = bullets[ibullet].pos.y + bullets[ibullet].boxdefense.y;
					a.w = bullets[ibullet].boxdefense.w;
					a.h = bullets[ibullet].boxdefense.h;
					b.x = GE_sprite[SPT_BUG].pos.x + GE_sprite[SPT_BUG].boxdefense.x;
					b.y = GE_sprite[SPT_BUG].pos.y + GE_sprite[SPT_BUG].boxdefense.y;
					b.w = GE_sprite[SPT_BUG].boxdefense.w;
					b.h = GE_sprite[SPT_BUG].boxdefense.h;
					if (SDL_HasIntersection(&a, &b))
					{
						GE_sprite[SPT_BUG].hide = false;
						bullets[ibullet].hide = true;
						playSound(1, 3, 0); // Play boom.ogdefenseg
						setGEvarI("sprt_bug_life", getGEvarI("sprt_bug_life") - 1);
						if (getGEvarI("sprt_bug_life") <= 0){
							setGEvarI("sprt_bug_hide", true);
							playSound(3, 0, 0); // Play ???
						}
						retractexplosion = SDL_GetTicks() + 400;
						setGEvarI("sprt_explosion_hide", false);
						setGEvarI("sprt_explosion_x", getGEvarI("sprt_bug_x"));
						setGEvarI("sprt_explosion_y", getGEvarI("sprt_bug_y"));
						//## Implementar Variaveis sprt_NAME_animationX
						GE_sprite[SPT_EXPLOSION].animation[0].frameidx = 0;
					}
				}
			}//---check bullet colision---------------------------------------------v
		}//-move bullet------------------^
	}

	// Clear background.
	if (clearbg == -1){
		SDL_SetRenderDrawColor(rendscr, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a);
	}

	//-Render GE_sprites---------------------------------------------V
	for (int sprti = 0; sprti < sprites; sprti++){
		if (!GE_sprite[sprti].hide){
			// Script Sprite Update-------------------------------------v
			if (strlen(GE_sprite[sprti].fileupdate)){
				//MSG("[Sprite:(%s) update script:{%s}]",GE_sprite[sprti].name,GE_sprite[sprti].fileupdate );
				//GE_sprite[sprites].SPRTSCRIPT=Create_GElua(GE_sprite[sprites].filestart,true);
				if(!gepause){
					if (GLSCRIPT){
						if (luaL_dofile(GLSCRIPT, GE_sprite[sprti].fileupdate)){
							ERR("%s\n", lua_tostring(GLSCRIPT, -1));
						}
					}else{
						MSG("Script lua não iniciado anteriormente.");
					}
				}
			}
			// Script Sprite Update-------------------------------------
			if (sprti == clearbg){
				SDL_RenderCopy(rendscr,
							   GE_sprite[sprti].animation[0].textFrame[GE_sprite[sprti].animation[0].frameidx],
							   NULL, NULL);
			}else{
				if (GE_sprite[sprti].flip){
					SDL_RenderCopyEx(rendscr,
									 GE_sprite[sprti].animation[0].textFrame[GE_sprite[sprti].animation[0].frameidx],
									 NULL, &GE_sprite[sprti].pos,
									 0,
									 NULL,
									 SDL_FLIP_HORIZONTAL);
				}else{
					SDL_RenderCopy(rendscr,
								   GE_sprite[sprti].animation[0].textFrame[GE_sprite[sprti].animation[0].frameidx],
								   NULL, &GE_sprite[sprti].pos);
				}
			}
			//--step-for-Sprite-animations--------v
			// if(GE_sprite[sprti].animation[0].anitype!=none) // Not animated
			if (GE_sprite[sprti].animation[0].anitype == loop &&
				GE_sprite[sprti].tick < SDL_GetTicks())
			{
				GE_sprite[sprti].tick = SDL_GetTicks() + GE_sprite[sprti].animation[0].speed;

				if (!gepause) GE_sprite[sprti].animation[0].frameidx++;

				if (GE_sprite[sprti].animation[0].frameidx >= GE_sprite[sprti].animation[0].maxframes){
					GE_sprite[sprti].animation[0].frameidx = 0;
				}
			}else if (GE_sprite[sprti].animation[0].anitype == forward && GE_sprite[sprti].tick < SDL_GetTicks()){
				GE_sprite[sprti].tick = SDL_GetTicks() + GE_sprite[sprti].animation[0].speed;

				if (!gepause) GE_sprite[sprti].animation[0].frameidx++;

				if (GE_sprite[sprti].animation[0].frameidx >= GE_sprite[sprti].animation[0].maxframes){
					GE_sprite[sprti].animation[0].frameidx = GE_sprite[sprti].animation[0].maxframes - 1;
				}
			}
			//--step-for-Sprite-animations--------^

			//-----Draw boxes in sprites----------------------v
			//### -- Calcular direito o tamanho dos boxes
			if (GE_sprite[sprti].showbox){
				rect.x = GE_sprite[sprti].pos.x;
				rect.y = GE_sprite[sprti].pos.y;
				rect.w = GE_sprite[sprti].pos.w;
				rect.h = GE_sprite[sprti].pos.h;
				SDL_SetRenderDrawColor(rendscr,
									   sptboxcolor.r,
									   sptboxcolor.g,
									   sptboxcolor.b, 255);
				SDL_RenderDrawRect(rendscr, &rect);
				rect.x = GE_sprite[sprti].boxdefense.x;
				rect.y = GE_sprite[sprti].boxdefense.y;
				rect.w = GE_sprite[sprti].boxdefense.w;
				rect.h = GE_sprite[sprti].boxdefense.h;
				SDL_SetRenderDrawColor(rendscr,
									   defenseboxcolor.r,
									   defenseboxcolor.g,
									   defenseboxcolor.b, 255);
				SDL_RenderDrawRect(rendscr, &rect);
				rect.x = GE_sprite[sprti].boxattack.x;
				rect.y = GE_sprite[sprti].boxattack.y;
				rect.w = GE_sprite[sprti].boxattack.w;
				rect.h = GE_sprite[sprti].boxattack.h;
				SDL_SetRenderDrawColor(rendscr,
									   attackboxcolor.r,
									   attackboxcolor.g,
									   attackboxcolor.b, 255);
				SDL_RenderDrawRect(rendscr, &rect);
			}
			//-----Draw boxes in sprites----------------------^
		}
	}
	//-Render GE_sprites---------------------------------------------^

	//-Render bullets---------------------------------------------v
	for (ibullet = 0; ibullet < DBULLETS; ibullet++){
		if (!bullets[ibullet].hide){
			// Transparency
			// SDL_SetTextureAlphaMod(bullets[ibullet].animation[0].textFrame[bullets[ibullet].animation[0].frameidx],50);
			SDL_RenderCopy(rendscr, bullets[ibullet].animation[0].textFrame[bullets[ibullet].animation[0].frameidx],
						   NULL, &bullets[ibullet].pos);
		}
	}
	//-Render bullets---------------------------------------------^

	//-Render ttf-------------------------------------------------v
	for (nf = 0; nf <= fonts; nf++){
		if (!font[nf].hide){
			SDL_Surface *sttftmp;
			linetext = parservar(font[nf].text);
			sttftmp = TTF_RenderText_Blended(font[nf].body,
											 linetext,
											 font[nf].color);
			free(linetext);
			texturefont = SDL_CreateTextureFromSurface(rendscr, sttftmp);
			SDL_QueryTexture(texturefont, NULL, NULL, &texW, &texH); // Get texturefont dimensions
			textrect.x = font[nf].x;
			textrect.y = font[nf].y;
			textrect.w = texW;
			textrect.h = texH;
			SDL_RenderCopy(rendscr, texturefont, NULL, &textrect);

			SDL_DestroyTexture(texturefont); // TODO: Recreate only if linetext has changes.
			texturefont = NULL;
			SDL_FreeSurface(sttftmp);
			// sttftmp = NULL;
		}
	}
	//-Render ttf-------------------------------------------------^

	//-Rener console----------------------------------------------v
	renderconsole(rendscr, width, height, consoleborder);
	//-Rener console----------------------------------------------^

	//### -- Atualiza a tela
	// DBG("MODO TESTE CORPORATIVO");
	// goto Quit_GE;
	SDL_RenderPresent(rendscr); // Atualiza para tela real e mostra tudo.

	//-Calculate FPS----------------------------------------v
	tnow = SDL_GetTicks() - tstart;
	if (tnow >= SECOND){
		setGEvarI("fps", fps);
		fps = 0;
		tstart = SDL_GetTicks();
	}
	fps++;
	//-Calculate FPS----------------------------------------^
}
//== FIM LOOP ==================================================================================^^^^

//##
Quit_GE:
	MSG("Finaliza GE ...");
	//--Free bullets-------------------v
	MSG("Free bullets");
	for (int i = 0; i < DBULLETS; i++){ SDL_DestroyTexture(bullets[i].animation[0].textFrame[0]); }
	//--Free bullets-------------------^

	//--Free sprites-------------------V
	// int maxsprites=ini_get_int(configfile, "global", "sprites", 1);
	int maxanimations;
	int maxframes;
	for (int i = 0; i < sprites; i++){
		LETSF(spriteN, "sprite%d", i + 1);
		maxanimations=ini_get_int(configfile, spriteN, "animations", 1);
		for (int animations = 0; animations < maxanimations; animations++){
			LETSF(animationSTUFFS, "anima%d", animations + 1);
			// TVARS(animationSTUFFS);
			maxframes=ini_get_int(configfile, spriteN, animationSTUFFS, 1);
			FREESEC(GE_sprite[i].fileupdate);
			FREESEC(GE_sprite[i].filestart);
			FREESEC(GE_sprite[i].fileend);
			for (int frame = 0; frame < maxframes; frame++){
				// TVARD(i); TVARS(GE_sprite[i].name); TVARS(GE_sprite[i].filestart); TVARS(GE_sprite[i].fileupdate); TVARS(GE_sprite[i].fileend); TVARS(GE_sprite[i].fileupdate); TVARS(GE_sprite[i].filestart); TVARS(GE_sprite[i].fileend);
				SDL_DestroyTexture(GE_sprite[i].animation[animations].textFrame[frame]);
			}
		}
	}
	//--Free sprites-------------------^
    
	//--Free fonts-------------------v
	for (nf = 0; nf <= fonts; nf++) 
		FREESEC(font[nf].text); 
	//--Free fonts-------------------^

    MSG("SDL_DestroyTexture(textureconsole)");
	freeconsole();
    
	MSG("Unload sounds...");
	Quit_sound();

	MSG("Unload GE functions");
	Quit_GE();

	if (GLSCRIPT!=NULL){
		MSG("Unload LUA Scripts");
		destroy_GElua(GLSCRIPT);
	}

	MSG("Unload icon...");
	SDL_FreeSurface(icon);

	MSG("Unload Window..."); 
	SDL_DestroyWindow(windscr);

	MSG("Unload render de tela...");
	SDL_DestroyRenderer(rendscr);	

	MSG("Unload Mix Audio...");
	Mix_CloseAudio();
    
	MSG("IMG_Quit()");
	IMG_Quit();

	MSG("SDL_Quit()");
	SDL_Quit();

    MSG("free configfile...[%s]",configfile);
	FREESEC(configfile);
	
	MSG("free(filescriptend)");
	FREESEC(filescriptend);

	MSG("free(filescript)");
	FREESEC(filescript);
	
	DBG("END.");
	return 0;
}
// - EOF
