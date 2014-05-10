/*

  The Revisionist - MS word document metadata analysis system
  -----------------------------------------------------------

  Copyright (C) 2004-2006 by Michal Zalewski <lcamtuf@coredump.cx>

  This program uses libOLE to extract user information from documents.
  There is more to it than meets the eye, so this needs to be improved
  at some point.

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libole2/ms-ole.h>
#include <libole2/ms-ole-summary.h>

static void do_summary (MsOle *ole) {
  MsOleSummary        *si;
  gboolean             ok;
  gchar               *txt;

  si = ms_ole_summary_open (ole);
  if (!si) return;

  txt = ms_ole_summary_get_string (si, MS_OLE_SUMMARY_AUTHOR, &ok);
  if (ok && strlen(txt)) printf("%s\n",txt);
  g_free (txt);
  txt = ms_ole_summary_get_string (si, MS_OLE_SUMMARY_LASTAUTHOR, &ok);
  if (ok && strlen(txt)) printf("%s\n",txt);
  g_free (txt);
  ms_ole_summary_close (si);
}


int main (int argc, char **argv) {
  MsOle *ole;
  if (argc!=2) {
    fprintf(stderr,"-- This is a component of therev - run the main program instead --\n");
    exit(1);
  }

  if (ms_ole_open_vfs (&ole, argv[1], TRUE, NULL) != MS_OLE_ERR_OK) {
    fprintf(stderr,"Cannot open OLE container.\n");
    exit(1);
  }
  do_summary (ole);
  ms_ole_destroy (&ole);
  return 0;
}
