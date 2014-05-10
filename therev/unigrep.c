/*

  The Revisionist - MS word document metadata analysis system
  -----------------------------------------------------------
 
  Copyright (C) 2004-2006 by Michal Zalewski <lcamtuf@coredump.cx>
 
  This program removes superfluous Unicode zeros from Office files to
  perform a quick and dirty search for strings.

  Because we FILE* I/O is heavily buffered, we can afford a lame
  solution. Or can we...

  The script takes file name and lowercase keyword as parameters.

 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char ibuf[128*1024];

int main(int argc,char** argv) {
  FILE* f;
  int c;
  int cp=0,ml;

  if (argc-3) { 
    fprintf(stderr,"-- This is a component of therev - run the main program instead --\n");
    fprintf(stderr,"Usage: %s filename lc_keyword\n",argv[0]); 
    exit(1); 
  }
  
  ml=strlen(argv[2]);

  for (c=0;c<ml;c++) if (argv[2][c] == '+') argv[2][c]=' ';

  f = fopen(argv[1],"r");
  if (!f) { perror(argv[1]); exit(1); }

  setbuffer(f,ibuf,sizeof(ibuf));

  while ((c=fgetc(f))!=EOF) if (c) {
    if (tolower(c) == argv[2][cp]) cp++; else cp=0;
    if (cp >= ml) return 0;
  }
  return 1;

}
