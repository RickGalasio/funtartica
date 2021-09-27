#include <stdlib.h>
#include "config.h"
#include "debug.h"


static FILE *logfile;
static struct tm *ptr;
static time_t lt;
static char TNow[80];

void __dbg__( char *log_mess, char *n_file ,int n_line ){
char filelogname[255];

   snprintf(filelogname, sizeof filelogname, FILELOG );

   if ((logfile = fopen( filelogname ,"a")) == (FILE*)NULL ){
      fprintf(stderr, "\nERR: Opening log file: %s  \n",filelogname);
   }else{
      lt=time(NULL);
      ptr=localtime(&lt);
      sprintf(TNow,"%s",asctime(ptr));
      TNow[strlen(TNow)-1]='\0';

      fprintf(logfile, "%s-:%s:%d:%s\n", TNow,n_file,n_line,log_mess);
      fprintf(stderr, "%s-:%s:%d:%s\n", TNow,n_file,n_line,log_mess);
	  fflush(logfile);
      fclose(logfile);
   }
}
//-----------------------------------------------------------------------------------------
void __dbg_init__( char *log_mess, char *n_file ,int n_line ){
//static char text[80];
char filelogname[255];

snprintf(filelogname, sizeof filelogname, FILELOG);
   if ((logfile = fopen( filelogname ,"a")) == (FILE*)NULL ){
      lt=time(NULL);
      ptr=localtime(&lt);
      sprintf(TNow,"%s",asctime(ptr));
      TNow[strlen(TNow)-1]='\0';

      fprintf( stderr, "\n%s - ERR: Creating log file: %s\n",filelogname, TNow);
   }else{
      lt=time(NULL);
      ptr=localtime(&lt);
      sprintf(TNow,"%s",asctime(ptr));
      TNow[strlen(TNow)-1]='\0';

      fprintf( logfile, DEBUGBANNER "[DBG] (%s)-:%s:%d:%s\n", TNow,n_file,n_line,log_mess);
      fprintf( stderr, DEBUGBANNER "[DBG] (%s)-:%s:%d:%s\n", TNow,n_file,n_line,log_mess);

      fclose(logfile);
   }
}

/**********************************************************************/




// - EOF
