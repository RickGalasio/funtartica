#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"
#include "inifiles.h"
/*************************************************************************/
void ini_set_configfile(char *fname){
   MALETS(sname_file, fname);	
}

char *ini_get_str(	const char *section,
					const char *svalue,
				  	const char *sdefault)
{
	FILE *inifile;
	char sread[255], ch;
	char term1[255], term2[255], term3[255];
	char t_section[255];
	size_t l_section, i, xx;

	l_section = strlen(section) + 2;

	snprintf(t_section, sizeof(char) * 255, "[%s]", section);

	// bzero(sread, 255);
	memset(sread,0, 255);
	// TVARS(sname_file);
	if ((inifile = fopen(sname_file, "r")) == NULL){
		ERR("INI File Read Error: %s\n", sname_file);
		exit(1);
	}

	if (strlen(section)){
		// INI search section
		while (!feof(inifile)){
			for (i = 0; i < l_section - 1; i++) 
				sread[i] = sread[i + 1];
			ch = getc(inifile);
			sread[l_section - 1] = ch;
			if (!strcasecmp(sread, t_section)){
				ch = getc(inifile); // Jump the ']'
				break;
			}
		}
	}else{
		ch = getc(inifile);
	}

	if (!feof(inifile)){
		// loop while not end of section
		while (!feof(inifile) && ch != '['){
			//skip remarks in the .ini file ....
			if (ch == '#' || ch == ';')
				while (!feof(inifile) && (ch = getc(inifile) != 10));;

			// read lines of section
			if (isprint(ch) && !isspace(ch)){
				xx = 0;
				bzero(term1, 255);
				while (!feof(inifile) && ('=' != ch) && (isprint(ch))){

					if (isalnum(ch) || ch == '_' || ch == ':' ) term1[xx++] = ch;

					if (ch == 32){
						while (!feof(inifile) && ch == 32) 
							ch = getc(inifile);

						if (ch != '='){
							term1[xx++] = ' ';
							term1[xx++] = ch;
						}
					}else{
						ch = getc(inifile);
					}
				}

				bzero(term2, 255);
				if (ch == '=') term2[0] = ch;

				ch = getc(inifile);
				xx = 0;

				bzero(term3, 255);

				// skip the initial spaces
				if (ch == ' ') while (!feof(inifile) && isspace(ch = getc(inifile)));;

				while (!feof(inifile) && (isprint(ch))){
					term3[xx++] = ch;
					ch = getc(inifile);
				}

				if ((strcasecmp(term2, "=")) ||
					(strchr(term1, '#') != NULL) ||
					(strchr(term3, '#') != NULL))
				{
					snprintf(sret, sizeof(sret), "%s", sdefault);
				}else{
					if (!strcasecmp(term1, svalue)){
						snprintf(sret, sizeof(sret), "%s", term3);
						goto exit_ini_get_str;
					}
				}
			}
			ch = getc(inifile);
		}
	}
	snprintf(sret, sizeof(sret), "%s", sdefault);
exit_ini_get_str:
	fclose(inifile);
	return sret;
}
//=============================================
void *ini_get_malloc_str(
	const char *section,
	const char *svalue,
	const char *sdefault)
{
	FILE *inifile;
	char ch;
	char *spatt;
    ERR("WARNING ini_get_malloc_str() CAUSES UNESPECTED ERRORS !!! (REIMPLEMENT)");
	if (!(spatt = malloc(sizeof(char) * (strlen(svalue) + 1))))
	{
		ERR("Out of memory reading ini file:%s [%s] - %s ",
			sname_file,
			section,
			svalue);
		exit(1);
	}
  
	// DBG("%lu bytes Reserved", sizeof(char) * (strlen(svalue) + 1));

	bzero(spatt, sizeof(char) * (strlen(svalue) + 1));
	char *buffer;
	long int i = 0;
	size_t ta;
	int match = 0;
	ta = (1 * sizeof(char)) + (strlen(svalue) * sizeof(char));
	buffer = malloc(ta);
	if (buffer == NULL)
	{
		ERR("Out of memory: (%s)\n", svalue);
		exit(1);
	}
	bzero(buffer, ta);
	if ((inifile = fopen(sname_file, "r")) == NULL)
	{
		ERR("INI File Read Error: %s\n", sname_file);
		exit(1);
	}
	match = 0;
	do
	{
		ch = getc(inifile);
		if (ch != 10 && ch != 13)
		{
			size_t ii;
			for (ii = 0; ii < (strlen(svalue) * sizeof(char)); ii++)
			{
				spatt[ii] = spatt[ii + 1];
			}
			spatt[ii] = ch;
		}

		if (match == 0)
		{
			//skip remarks in the .ini file ....
			if (ch == '#')
				while (!feof(inifile) && (ch = getc(inifile) != 10))
					;
			;
			//    TVARS(svalue);
			//    TVARS(spatt);
			if (!strncmp(svalue, spatt, strlen(svalue)))
			{
				match = 1;
				do
				{
					ch = getc(inifile);
				} while (ch == ' ' || ch == 10);
			}
		}

		if (match == 1)
		{
			if (ch == 10)
				break;
			if (ch != 10 && ch != 13)
				buffer[i++] = ch;
			if (i >= ta)
			{
				ta = ta + 512 * sizeof(char);
				buffer = realloc(buffer, ta);
			}
		}

	} while ((!feof(inifile)));
	; // loop while not end of file
	if (match == 1)
		buffer[i] = 0;
	if (match == 0)
		memcpy(buffer, sdefault, 1 + strlen(sdefault));
	fclose(inifile);

	free(spatt);
	return buffer;
}
//=============================================

/*********************************************/
int ini_get_int( char *section, char *svalue,
		const int idefault){
    char xdefault[255];
	
    snprintf(xdefault,sizeof(char)*255, "%d", idefault);
	return atoi(ini_get_str(section, svalue, xdefault));
}
/**********************************************/

//---------------------------------------------------------------v
bool ini_get_bool( char *section, char *svalue,
		const bool idefault){
	char *xvar=ini_get_str(section,svalue,idefault==true?"true":"false");
    if(!strcasecmp(xvar,"true")){
		return true;
	}else if(!strcasecmp(xvar,"false")){
		return false;
	}else if(!strcasecmp(xvar,"1")){
		return true;
	}else if(!strcasecmp(xvar,"0")){
		return false;
	}else if(!strcasecmp(xvar,"yes")){
		return true;
	}else if(!strcasecmp(xvar,"no")){
		return false;
	}else if(!strcasecmp(xvar,"on")){
		return true;
	}else if(!strcasecmp(xvar,"off")){
		return false;
	}else if(!strcasecmp(xvar,"enable")){
		return true;
	}else if(!strcasecmp(xvar,"disable")){
		return false;
	}else if(!strcasecmp(xvar,"set")){
	    return true;	
	}else if(!strcasecmp(xvar,"unset")){
	    return false;	
	}else if(!strcasecmp(xvar,"y")){
		return true;
	}else if(!strcasecmp(xvar,"n")){
		return false;
	}else if(!strcasecmp(xvar,"t")){
		return true;
	}else if(!strcasecmp(xvar,"f")){
		return false;
	}else if(!strcasecmp(xvar,"positive")){
		return true;
	}else if(!strcasecmp(xvar,"negative")){
		return false;
	}else{
	    return idefault;
	}
}
//---------------------------------------------------------------^

//---------------------------------------------------------------v
bool ini_get_nsession( char *section, int ene){
	FILE *inifile;
	int ii=0,isect=0;
	char ch;
	char csect[20];

    if ((inifile = fopen(sname_file, "r")) == NULL) {
	   ERR("INI File Read Error: %s\n",sname_file);
	}
	// bzero(csect,sizeof(csect));
	while(1){
       ch = getc(inifile);
	   if(feof(inifile)) break;
       if(ch!='[') continue;
       while(1){
          ch = getc(inifile);
	      if(feof(inifile)||ch==']'){
			  csect[isect]='\0';
			  isect=0;
			  if(ene==ii++){
				snprintf(section,sizeof(csect),"%s",csect);
	            fclose(inifile);
				return true;
		      }
			//   MSG("Section %d: {%s}",ii++,csect);
			  break;
		  }
		  csect[isect++]=ch;
	   }
	}
	fclose(inifile);
return false;
}
//---------------------------------------------------------------^

//---------------------------------------------------------------v
bool ini_get_inline( char *section, char *sline, int ene){
	FILE *inifile;
	char sread[255], ch;
	char line[255];
	char t_section[255];
	size_t l_section, i, j, xx;
	bool enable;
	j = 0;
	enable=false;
	l_section = strlen(section) + 2;

	//snprintf(t_section, sizeof(char) * 255, "[%s]", section);
	LETSF(t_section, "[%s]", section);

	bzero(sread, sizeof(sread));

	if ((inifile = fopen(sname_file, "r")) == NULL){
		ERR("INI File Read Error: %s\n", sname_file);
		exit(1);
	}

	if (strlen(section)){
        // INI search section
		while (!feof(inifile)){
			for (i = 0; i < l_section - 1; i++)
				sread[i] = sread[i + 1];

			ch = getc(inifile);
			sread[l_section - 1] = ch;
			if (!strcasecmp(sread, t_section)){
				ch = getc(inifile); // Jump the ']'
				break;
			}
		}
	}else{
		ch = getc(inifile);
	}
	// DBG("Encontrado:%s",sread);

	if (!feof(inifile)){
        // loop while not end of section{
		while (!feof(inifile) && !(ch == '[' && enable==false)){ 

		// read lines of section
           if(ch=='{'){
			    enable=true;
		        ch = getc(inifile);
		   }
           if(ch=='}') enable=false;

		if (isprint(ch) && enable){
			xx = 0;
			bzero(line, sizeof(line));

			while (!feof(inifile) && (isprint(ch))){
				line[xx++] = ch;
				ch = getc(inifile);
			}

			line[xx] = '\0';
			// TVARS(line);
			if (j++ == ene){
				// O ponteiro não pode ser menor que o line...
				snprintf(sline, sizeof(line), "%s", line);
				fclose(inifile);
				return false;
			}
		}
		ch = getc(inifile);
		}
	}

    fclose(inifile);
    return true;
}
//---------------------------------------------------------------^

//---------------------------------------------------------------v
FILE *ini_fopen_inline( char *section, char *inlinesection)
{
	FILE *inifile;
	char sread[255], inlinesread[255], ch;
	char t_section[255];
	size_t l_section, i, xx;
	bool inlineenable = false;
	l_section = strlen(section) + 2;

	LETSF(t_section, "[%s]", section);

	bzero(sread, sizeof(sread));
	bzero(inlinesread, sizeof(inlinesread));

	if ((inifile = fopen(sname_file, "r")) == NULL){
		ERR("INI File Read Error: %s\n", sname_file);
		exit(1);
	}

	if (strlen(section)){
		// INI search section
		while (!feof(inifile)){
			for (i = 0; i < l_section - 1; i++)
				sread[i] = sread[i + 1];

			ch = getc(inifile);
			sread[l_section - 1] = ch;
			if (!strcasecmp(sread, t_section)){
				ch = getc(inifile); // Jump the ']'
				break;
			}
		}
	}else{
		ch = getc(inifile);
	}
	// Search section
search_section:
	// TVARD(jj++);
	xx = 0;
	while (!feof(inifile) && !inlineenable){
		if(ch=='[' && !inlineenable){
			return inifile;
		}
		if (isprint(ch) && ch != '{' && !inlineenable){
			inlinesread[xx++] = ch;
		}else if (!isprint(ch)){
			bzero(inlinesread, sizeof(inlinesread));
			xx = 0;
		}

		if (ch == '{'){
			inlineenable = true;
			break;
		}

		ch = getc(inifile);
		if (feof(inifile) || (!inlineenable && ch == '[')){
			fclose(inifile);
			return NULL;
		}
	}

    // DBG("Inicia Inline e compara nome do inline:");
	if (!strlen(inlinesection)){
		// DBG("Encontrado:[%s]%s %s{...} %s{...} %d", section, sread, inlinesection, inlinesread, inlineenable);
		return inifile;
	}else if (!strcasecmp(inlinesection, inlinesread)){
		// DBG("XEncontrado:[%s]%s %s{...} %s{...} %d", section, sread, inlinesection, inlinesread, inlineenable);
		return inifile;
	}else{
		// DBG("Inline atual não corresponde ao procurado.");
		
		ch = getc(inifile);
		while (!feof(inifile) && ch != '}'){
			ch = getc(inifile);
		}
		// Se for feof() desiste
		if (ch!='}'){
			return inifile;
		}
		inlineenable = false;
		bzero(inlinesread, sizeof(inlinesread));
		xx = 0;
		ch=getc(inifile);
		goto search_section;
	}
}
//---------------------------------------------------------------^

//---------------------------------------------------------------v
char *ini_get_next_inline(FILE *inifile, bool scanfullsection ) {
	size_t xx;
	char ch;
    bool inlineenable=true;

	bzero(sinline, sizeof(sinline));
	ch = getc(inifile);
	while (!feof(inifile)) {   
		if(!isprint(ch)) {
			ch = getc(inifile);
			continue;
		}
		if (ch == '}') {
			if (scanfullsection) {
				inlineenable = false;
				while (!feof(inifile) && ch != '{' && ch != '[') {
					ch = getc(inifile);
				}
			}else{
			    return sinline;	
			}
		}
		if(feof(inifile) || (ch == '[' && !inlineenable)) {
           sinline[0]='\0';
           break;
		} 
		if( ch=='{') {
			inlineenable=true;
			ch=getc(inifile);
		}
		if (isprint(ch) && inlineenable) {
			xx = 0;
			bzero(sinline, sizeof(sinline));
			while (!feof(inifile) && (isprint(ch))) {
				sinline[xx++] = ch;
				ch = getc(inifile);
			}
			sinline[xx] = '\0';
			return sinline;
		}
		ch = getc(inifile);
	}
	return sinline;
}

//---------------------------------------------------------------v
char *ini_get_lua( char *section, char *inlinename){
	FILE *myinline;
	char linha[512];
	size_t offset;
	char *prog;
	MALETS(prog, "");
    // DBG("==================================================================");
	if ((myinline = ini_fopen_inline(section, inlinename))){
		bzero(linha, sizeof(linha));
		while (true){
			LETS(linha, ini_get_next_inline(myinline, false));
			
			if (!strlen(linha))	break;

			//ignore (and don't allocate ram) for ident spaces.
			for(offset=0;linha[offset]==' '||linha[offset]=='\b';offset++){;}

			//Ignore (and don't allocate ram) for remarks.
			if (!strncasecmp("--", linha, 2)) continue;

			// DBG("INLINE:%s:%d", linha, i++);
			ADDLETSNL(prog, linha+offset);
		}
        fclose(myinline);
	    return prog;
	}else{
		ERR("Inline name %s{... does not exist in section [%s] of ini file %s.", inlinename, section, sname_file);
		return NULL;
	}
}
//---------------------------------------------------------------^

int ini_get_color( 
    SDL_Color *color,
    const char *section,
    const char *svalue,
    const char *sdefault){

    char cxcolor[15];
    LETS(cxcolor, ini_get_str(section, svalue, sdefault));
		
	if (sscanf(cxcolor, "%x,%x,%x,%x",
					(unsigned int*)&color->r,
					(unsigned int*)&color->g,
					(unsigned int*)&color->b,
					(unsigned int*)&color->a ) != 4){		
		ERR("Syntax error in color. [%s] %s=%s ",section,svalue,cxcolor);
		if(sscanf(sdefault, "%x,%x,%x,%x",
					(unsigned int*)&color->r,
					(unsigned int*)&color->g,
					(unsigned int*)&color->b,
					(unsigned int*)&color->a ) != 4){

			ERR("  Syntax error in default color: %s",sdefault);
			
			color->r = 0;
			color->g = 0;
			color->b = 0;
			color->a = 255;
		}
	}
	DBG("Color: [%s] %s=%s ",section,svalue,cxcolor);

    return 0;
}

// - EOF
