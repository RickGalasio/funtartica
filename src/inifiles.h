#ifndef _INIFILES_H
#define _INIFILES_H
#include "config.h"
#include "globals.h"
#include <stdbool.h>

char sret[255 * 2];
char sinline[1024 * 2];

static char *sname_file;
void ini_set_configfile(char *fname);

typedef struct _L_SECTION {
    char variable[255];
    char value[255];
} _L_SECTION;

typedef struct _INI_section {
    char namesection[40];
    int len;
    _L_SECTION reg[500];
} INI_section;

typedef struct _INI_inifile {
    char namefile[40];
    int len;
    char section[40][500];
} INI_inifile;

// Get pointer for string in file sname_file, at section and variable svalue.
// if section or variable not found; return pointer for string sdefault.
char *ini_get_str(
    const char *section,
    const char *svalue,
    const char *sdefault
);

// Get pointer for string in file sname_file, at section and variable svalue.
// if section or variable not found; return pointer for string sdefault.
void *ini_get_malloc_str(
    const char *section,
    const char *svalue,
    const char *sdefault
);
// Get integer in file sname_file, at section and variable svalue.
// if section or variable not found; return sdefault integer.
int ini_get_int(
    char *section,
    char *svalue,
    const int idefault
);

// Get boolean value in file sname_file, at section and variable svalue.
// if section or variable not found; return sdefault boolean.
// Valid Boolean values:
//______________________
//| TRUE    | FALSE    |
//|---------|----------|
//| "true"  | "false"  | 
//| "1"     | "0"      |
//| "yes"   | "no"     |
//| "on"    | "off"    |
//| "enable"| "disable"|  
//| "set"   | "unset"  |
//| "y"     | "n"      |
//| "t"     | "f"      |
//----------------------
bool ini_get_bool(
    char *section,
    char *svalue,
    const bool idefault
);

//Return in string pointer &section the pointer to string of ninth [section] name (determined by ene) of file sname_file.
//The function returns true if sucess or false if not found the section name.
bool ini_get_nsession(
    char *section,
    int ene
); 

//Returns &sline the nth and nth line in the [section] of the sname_file file.
//If the function returns false, then the parameter ene points to an existing line in the inline,
// if it returns false, ene is greater than the maximum line size of the inline plus 1.
bool ini_get_inline(
    char *section,
    char *sline,
    int ene
);

//Return a pointer for file sname_file.
//Sets the file position indicator for the start of inlinesection{ into the [section] of the ini file sname_file.
//Then you can call the ini_get_next_inline() function to get the inline content.
FILE *ini_fopen_inline(
    char *section,
    char *inlinesection
);

//Returns a pointer to the full content or just the next line of the file passed as parameters in file,
// considering the file's position indicator. If scanfullsection is true, the function returns the full content,
// if it is false, the function returns only the next line.
//ini_get_next_inline() can be called repeatedly to read the inline content line by line.
char * ini_get_next_inline(
    FILE *file,
    bool scanfullsection
);

//Returns a pointer to a string, allocating the necessary memory,
// with the contents of the inline inlinename{ within the [section] of the sname_file file.
//ini_get_lua()treating it like a LUA script. Remove comments and empty lines.
//After using the allocated pointer, the returned pointer must be released with free();
char *ini_get_lua(char *section, char *inlinename);

int ini_get_color( 
    SDL_Color *color,
    const char *section,
    const char *svalue,
    const char *sdefault);
#endif
/*******************************************************/

// - EOF
