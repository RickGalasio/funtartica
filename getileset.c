#include "getileset.h"
#include "inifiles.h"
#include "debug.h"
SDL_Texture *getilemap(
	char *configfile,
	char *spriteN,
	SDL_Renderer *rendscr,
	SDL_Color tcolor,
	int width, int height)
{
	DBG("TILES");
	SDL_Texture *tilemap;
	char mosaicname[20];
	char linelegend[255];
	char legendN[50];

	SDL_Rect myrect = {0, 0, 32, 32};
	myrect.w = ini_get_int(configfile, spriteN, "tilew", 32);
	myrect.h = ini_get_int(configfile, spriteN, "tileh", 32);

	// int mosaicw = ini_get_int(configfile, spriteN, "mosaicw", 1);
	// int mosaich = ini_get_int(configfile, spriteN, "mosaich", 1);
	LETS(mosaicname, ini_get_str(configfile, spriteN, "mosaic", ""));
	MSG("Mosaic:%s", mosaicname);
	// DBG("Load Tiles.");

	_getile *getile;

	if (!(getile = malloc(sizeof(_getile) * ini_get_int(configfile, spriteN, "legends", 0)))){
		ERR("getile malloc :%d", ini_get_int(configfile, spriteN, "legends", 0));
		exit(1);
	}

	for (int i = 1; i <= ini_get_int(configfile, spriteN, "legends", 0); i++){
		LETSF(legendN, "legend%d", i);
		LETS(linelegend, ini_get_str(configfile, spriteN, legendN, " "));
		TVARS(linelegend);
		getile[i - 1].legend = linelegend[0];

		//## mosaic Carrega imagem de fundo padrão.
		if ((getile[i - 1].tile = IMG_Load((const char *)linelegend + 2)) == NULL){
			ERR("Unable to open Tile: %s", linelegend + 2);

			// LETS(filename, "./img/not_found.png");
			// if ((getile[i - 1].tile = IMG_Load((const char *)filename)) == NULL){
			// 	ERR("Unable to open file ./img/not_found.png");
			// 	exit(1);
			// }
			exit(1);
		}
	}

	// DBG("Create bg image");
	if ((tilemap = (SDL_Texture *)SDL_CreateTexture(
			 rendscr, 
			// SDL_PIXELFORMAT_RGBA8888,
			  SDL_PIXELFORMAT_ARGB8888,
			 SDL_TEXTUREACCESS_STREAMING,
			 width,
			 height)))
	{
	//------------------------------------------------------------------------------v
    // Initialize texture pixels to a AGRB (no RGBA) value
    unsigned char* bytes = NULL;
    int pitch = 0;
    SDL_LockTexture(tilemap, NULL, (void **)&bytes, &pitch);

	// TVARD(tcolor.r);
    // TVARD(tcolor.g);
	// TVARD(tcolor.b);

    unsigned char rgba[4] = { tcolor.b, tcolor.g, tcolor.r, tcolor.a };
    for(register int y = 0; y < height; ++y) {
        for (register int x = 0; x < width; ++x) {
            memcpy(&bytes[(y * width + x )*sizeof(rgba)], rgba, sizeof(rgba));
        }
    }
	SDL_UnlockTexture(tilemap);
    //------------------------------------------------------------------------------^    
		// DBG("Merge tile[0]");
		char linha[1024];
		FILE *myinline;
		// char inlinename[15];
		// DBG("##############################################################");
		TVARS(configfile);
		myinline = ini_fopen_inline(configfile, "sprite1", mosaicname);
		bzero(linha, sizeof(linha));
		while (true){
			LETS(linha, ini_get_next_inline(myinline, false));
			if (!strlen(linha))
				break;
			//MSG("INLINE:%s:%d",linha,i++);
			for (int c = 0; c < strlen(linha); c++){
				myrect.x = c * myrect.w;
				int l = 0;
				for (l = 0; l < ini_get_int(configfile, spriteN, "legends", 0); l++){
					if (getile[l].legend == linha[c])
						break;
				}
                // SDL_SetTextureBlendMode(tilemap,150);
				SDL_UpdateTexture(
					tilemap,
					&myrect,
					getile[l].tile->pixels,
					getile[l].tile->pitch);
			}
			myrect.y += myrect.h;
			// printf("\n");
		}
		fclose(myinline);
		// DBG("##############################################################");
	}
	
	for (int i = 1; i < ini_get_int(configfile, spriteN, "legends", 0); i++){
		SDL_FreeSurface(getile[i - 1].tile);
	}

	free(getile);

	return tilemap;
}




// - EOF
