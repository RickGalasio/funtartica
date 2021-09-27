#include "gensprite.h"
#include "inifiles.h"
#include "debug.h"
#include "rnd.h"

SDL_Texture *gensprite( char *spriteN, SDL_Renderer *rendscr){
	DBG("GENERATING:%s", spriteN);
	// Dimensions of internal pixels (the final sprite is staggered)
	spriteh = ini_get_int(spriteN, "pixel:h", 16);
	spritew = ini_get_int(spriteN, "pixel:w", 16);
	npixels = ini_get_int(spriteN, "pixel:n", 16 * 16 * 0.20);
	pixelcolors = ini_get_int(spriteN, "pixel:colors", 1);

	// INI feed random generator with the seed----
	//
	TVARS(spriteN);
	char seed[50];
	LETS(seed, ini_get_str(spriteN, "pixel:seed", "rnd"));
	TVARS(seed);

	if (!strcasecmp(seed, "rnd") || !strcasecmp(seed, "random")){

		if (lastseed == 0){
			lastseed = time(0);
			DBG("INI SEED: %d", lastseed);
			msrand(lastseed);
		}else{
			DBG("LST SEED: %d", lastseed);
			msrand(lastseed);
		}
	}else{
		DBG("FIX SEED: %s", seed);
		msrand(atoi(seed));
	}

	// END feed random generator with the seed----

	mirror = ini_get_bool(spriteN, "pixel:mirror", false);
	lake = ini_get_bool(spriteN, "pixel:lake", false);

	int pixelx, pixely;
	int x, y;
	SDL_Texture *genspritetexture;
	SDL_Surface *tmpsurface;

	colors = ini_get_int(spriteN, "pixel:colors", 1);

	SDL_Color *pcolor;
	pcolor = (SDL_Color *)malloc(sizeof(SDL_Color) * colors);

	TVARD(colors);
	for (int i = 1; i <= colors; i++){
		LETSF(xcolor, "pixel:color%d", i);
		ini_get_color(&pcolor[i-1], spriteN, xcolor, "ff,ff,ff,ff");
	}

	//--------------------------------------------------------------------
	FILE *myinline;
	char linha[1024];

	TVARS(spriteN);

	char mapspritename[512];
	LETS(mapspritename, ini_get_str(spriteN, "pixel:map", "ship"));
	TVARS(mapspritename);
	myinline = ini_fopen_inline("maps", mapspritename);

	y = 0;
	x = 0;
	if ((pixmask = (unsigned char *)malloc(sizeof(unsigned char) * spriteh * spritew)) == NULL){
		ERR("Out of Memory.");
		exit(1);
	}
	bzero(pixmask, sizeof(unsigned char) * spriteh * spritew);
	y = 0;
	for (;;){
		LETS(linha, ini_get_next_inline(myinline, false));
		if (!strlen(linha)){
			break;
		}
		// DBG("map:%0.2d[%s]", y, linha);
		for (x = 0; x < spritew; x++){
			if (linha[x] != '.'){
				PIXMASK(x, y) = 1;
			}
		}
		y++;
	}
	fclose(myinline);
	// free(linha);
	//--------------------------------------------------------------------
	//  DBG("END TEST MAP PIXEL");
	// exit(1);

	if ((pixel = (unsigned char *)malloc(sizeof(unsigned char) * spriteh * spritew)) == NULL){
		ERR("Out of Memory.");
		exit(1);
	}
	bzero(pixel, sizeof(char) * spriteh * spritew);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	tmpsurface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
	tmpsurface = SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif

	int retry = 0;

	// INI RND -----------------------------------
	for (int i = 0; i < npixels; i++){
		int actualcolor;
		retry++;

		if (retry > spritew * spriteh) break;

		lastseed = mrand();
		pixelx = 1 + (lastseed) % (spritew - 2);
		lastseed = mrand();
		pixely = 1 + (lastseed) % (spriteh - 2);
		lastseed = mrand();
		actualcolor = 1 + (lastseed) % (pixelcolors);
		// TVARD(actualcolor);
		if (PIXMASK(pixelx, pixely) != 0){
			PIXEL(pixelx, pixely) = actualcolor;
		}

		if (mirror && MPIXMASK(pixelx, pixely) != 0){
			MPIXEL(pixelx, pixely) = actualcolor;
		}
	}
	// END RND -----------------------------------

	// INI Draw borders ---------------------------------------
	for (int x = 0; x < spritew; x++){
		for (int y = 0; y < spriteh; y++){
			if (PIXEL(x, y) != 0 && PIXEL(x, y) != CHAR_BORDER){
				if (PIXEL(x - 1, y) == 0) PIXEL(x - 1, y) = CHAR_BORDER;
				if (PIXEL(x + 1, y) == 0) PIXEL(x + 1, y) = CHAR_BORDER;
				if (PIXEL(x, y - 1) == 0) PIXEL(x, y - 1) = CHAR_BORDER;
				if (PIXEL(x, y + 1) == 0) PIXEL(x, y + 1) = CHAR_BORDER;
			}
		}
	} // END Draw borders---------------------------------------

	char *xline;
	xline = (char *)malloc(sizeof(char) * spritew + 1);

	if (xline == NULL){
		ERR("Memory allocation fault.");
		exit(1);
	}

	for (int y1 = 0; y1 < spriteh; y1++){
		bzero(xline, (sizeof(char) * spritew + 1));
		for (int x1 = 0; x1 < spritew; x1++){

			switch (PIXEL(x1, y1)){
			case CHAR_BORDER:
				setpixel(tmpsurface, spritew, spriteh, x1, y1, pcolor[0]);
				xline[x1] = '_';
				break;

			default:
				if (PIXEL(x1, y1) > 0){
					setpixel(tmpsurface, spritew, spriteh, x1, y1, pcolor[PIXEL(x1, y1)]);
					xline[x1] = '0' + PIXEL(x1, y1);
				}else{
					xline[x1] = ' ';
				}
				break;
			}
		}
		xline[spritew + 1] = 0;
		// DBG("%0.2d[%s]", y1, xline);
	}
	free(xline);

	genspritetexture = SDL_CreateTextureFromSurface(rendscr, tmpsurface);
	
	DBG("############################");
#ifdef STB_SPRINTF_H_INCLUDE
    DBG("stb_sprintf in use");
#endif

	free(pixel);
	free(pixmask);
	free(pcolor);
	SDL_FreeSurface(tmpsurface);
	return genspritetexture;
}

int setpixel(SDL_Surface *sptsurface, int spritew, int spriteh,int pixelx, int pixely,
	SDL_Color pxcolor){
	int ret=0;
	SDL_Rect tmprect;
 
	tmprect.w = width/spritew;
	tmprect.h = height/spriteh;
	tmprect.x = (width - (pixelx * tmprect.w) - tmprect.w);
	tmprect.y = pixely*tmprect.h;

	SDL_FillRect(sptsurface, &tmprect, SDL_MapRGB(sptsurface->format, pxcolor.r, pxcolor.g, pxcolor.b));

	ret=1;
	return ret;
}

// - EOF
