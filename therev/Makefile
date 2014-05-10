#
# The Revisionist - MS word document metadata analysis system
# -----------------------------------------------------------
#
# Copyright (C) 2004-2006 by Michal Zalewski <lcamtuf@coredump.cx>
#

CC     = gcc
CFLAGS = -Wall -O3 -fomit-frame-pointer
L_OLE  = -lgnomeole2 `pkg-config --libs glib-2.0`

PROGS  = cntdelal unigrep showauth getmacdoc

all: $(PROGS) info

showauth: showauth.c
	@echo "* NOTE: If this step fails, please install libole2 (see README) - otherwise,"
	@echo "* you won't be able to extract username data from documents."
	$(CC) $(CFLAGS) -I. `pkg-config --cflags --libs glib-2.0` $@.c -o $@ $(L_OLE) || true

info:
	@echo
	@echo "Compilation successful. Run 'therev' or read README for more"
	@echo "information."
	@echo

install:
	@echo "Installation is not supported yet - see README"

publish: clean
	tar cfvz /tmp/therev.tgz /therev
	scp -p /tmp/therev.tgz lcamtuf@coredump.cx:/export/www/lcamtuf/soft/

clean:
	rm -f $(PROGS) master.html *.o core core.* *~ .*-*
	rm -rf document.*
