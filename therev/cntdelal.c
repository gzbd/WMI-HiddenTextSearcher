/*

  The Revisionist - MS word document metadata analysis system
  -----------------------------------------------------------
 
  Copyright (C) 2004-2006 by Michal Zalewski <lcamtuf@coredump.cx>

  This program (rougly) determines the number of alphanumeric characters
  between '[DEL:' and ':DEL]' in input file. No parameters.

 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char buf[128*1024];

int main(int argc,char** argv) {
  int i;
  char docnt=0;
  int sofar=0;
  
  while ((i=read(0,buf,sizeof(buf)-8))>0) {
    int a;

    for (a=0;a<i;a++) {
      if (docnt) {
        if (isalnum(buf[a])) sofar++; else
         if (!strncmp(buf+a,":DEL]",5)) { docnt=0; a += 5; continue; }
      } else 
        if (!strncmp(buf+a,"[DEL:",5)) { docnt=1; a += 5; continue; }
    }

  }

  printf("%d\n",sofar);

  return 1;

}
