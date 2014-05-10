/*

  The Revisionist - MS word document metadata analysis system
  -----------------------------------------------------------
    
  Copyright (C) 2004-2006 by Michal Zalewski <lcamtuf@coredump.cx>
      
  This program mqnuqlly grabs a part of document's GUID (usually
  associated with MAC address of author's machine).

 */
	     
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE (128*1024)

char buf[BUFSIZE+80];

int main(int argc,char** argv) {
  int i;
  while ((i=read(0,buf,BUFSIZE))>0) {
    int j;
    for (j=0;j<i;j++) {
      if (buf[j]=='{') {
        if (buf[j+18]=='-' && buf[j+38]=='-' &&
            buf[j+48]=='-' && buf[j+74]=='}') {
            printf("%c%c:%c%c:%c%c:%c%c:%c%c:%c%c\n",
               buf[j+50],buf[j+52],buf[j+54],buf[j+56],buf[j+58],
               buf[j+60],buf[j+62],buf[j+64],buf[j+66],buf[j+68],
               buf[j+70],buf[j+72]);
            exit(0);
        }
      }
      j++;
    }
  }
  return 0;
}

