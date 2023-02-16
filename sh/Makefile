# SPDX-License-Identifier: GPL-3.0-or-later
include ../config.mk

# Commands
# ========

all: clean sh

sh: sh.o
	$(CC) $(CFLAGS) *.o -o sh
	rm -f version.h

clean:
	rm -f *.o
	rm -Rf sh

# Utilities
# =========

sh.o:
	echo "#ifndef VERSION_H"                 > version.h
	echo "#define VERSION_H"                >> version.h
	echo "#define COMPILETIME \"$$(date)\"" >> version.h
	echo                                    >> version.h
	echo "#endif"                           >> version.h
	for s in *.c; do $(CC) $(CFLAGS) $(NOLINKER) $$s -o $${s%.c}.o; done
