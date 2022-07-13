#
#	Copyright (C) 2022 Ferass EL HAFIDI
#	Copyright (C) 2022 Leah Rowe
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

include ./config.mk

# Commands
# ========

all: clean box

genbox:
	echo "/*	fasesiab - Ferass' Base System in a box "             > box.c
	echo " *	Copyright (C) 2022 Ferass EL HAFIDI"                 >> box.c
	echo " *"                                                        >> box.c
	echo " *	This program is free software: you can redistribute it and/or modify"           >> box.c
	echo " *	it under the terms of the GNU General Public License as published by"           >> box.c
	echo " *	the Free Software Foundation, either version 3 of the License, or"              >> box.c
	echo " *	(at your option) any later version."                 >> box.c
	echo " *"                                                        >> box.c
	echo " *	This program is distributed in the hope that it will be useful,"                >> box.c
	echo " *	but WITHOUT ANY WARRANTY; without even the implied warranty of"                 >> box.c
	echo " *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"                  >> box.c
	echo " *	GNU General Public License for more details."        >> box.c
	echo " *"                                                        >> box.c
	echo " *	You should have received a copy of the GNU General Public License"              >> box.c
	echo " *	along with this program.  If not, see <https://www.gnu.org/licenses/>."         >> box.c
	echo " */"                                                       >> box.c
	echo                                                             >> box.c
	echo "/* Generated on $$(date) */"                               >> box.c
	echo "#include <string.h>"                                       >> box.c
	echo "#include <unistd.h>"                                       >> box.c
	echo "#include <libgen.h>"                                       >> box.c
	echo "#include <stdio.h>"                                        >> box.c
	echo                                                             >> box.c
	for u in ${CORE}; do echo "int $${u%.c}_main(int, char**);"; done>> box.c
	test ${INCLUDE_EXTRA} == n || for u in ${EXTRA}; do echo "int $${u%.c}_main(int, char**);"; done>> box.c
	echo                                                             >> box.c
	echo "int main(int argc, char *argv[]) {"                        >> box.c
	echo "	if (!strcmp(basename(argv[0]),\"box\") && argc > 1) {"   >> box.c
	echo "		argc--;"                                             >> box.c
	echo "		argv++;"                                             >> box.c
	echo "	} if(0);"                                                >> box.c
	for u in ${CORE}; do echo "	else if(!strcmp(basename(argv[0]), \"$${u%.c}\")) return $${u%.c}_main(argc, argv);"; done >> box.c
	test ${INCLUDE_EXTRA} == n || for u in ${EXTRA}; do echo "	else if(!strcmp(argv[0], \"$${u%.c}\")) return $${u%.c}_main(argc, argv);"; done >> box.c
	echo "	else {"                                                  >> box.c
	echo "		printf(\"Ferass' Base System in a box\n\n\");"       >> box.c
	echo "		printf(\"Usage: box <COMMAND> [ARGS]\n\n\");"        >> box.c
	echo "		printf(\"Commands available:\n\");"                  >> box.c
	for u in ${CORE}; do echo "		printf(\"$${u%.c} \");"; done    >> box.c
	test ${INCLUDE_EXTRA} == n || for u in ${EXTRA}; do echo "		printf(\"$${u%.c} \");"; done    >> box.c
	echo "		printf(\"\\n\");"                                    >> box.c
	echo "	}"                                                       >> box.c
	echo "}"                                                         >> box.c

prepbox:
	mkdir -p box_tmp
	for f in ${CORE}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < "core/"$$f".c" | sed "s/printUsage()/$$(echo "$$f")_printUsage()/g" > "box_tmp/"$$f"_box.c"; done
	test ${INCLUDE_EXTRA} == n || for f in ${EXTRA}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < "core/"$$f".c" | sed "s/printUsage()/$$(echo "$$f")_printUsage()/g" > "box_tmp/"$$f"_box.c"; done

box: box.o
	$(CC) $(CFLAGS) box_tmp/*.c box.o -o box 

clean:
	rm -f box *.o extras-bin core-bin
	rm -Rf box_tmp */bin/*

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -r core/bin/* $(DESTDIR)$(PREFIX)/bin

install-box:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -r box $(DESTDIR)$(PREFIX)/bin

links:
	for u in ${CORE}; do ln -s "$(DESTDIR)$(PREFIX)/bin/box" "$(DESTDIR)$(PREFIX)/bin/$$u"; done

remove:
	rm -f $(DESTDIR)$(PREFIX)/bin/box
	for u in ${CORE}; do rm -f "$(DESTDIR)$(PREFIX)/bin/$$u"; done


# Utilities
# =========

box.o: prepbox
	$(CC) $(CFLAGS) $(NOLINKER) box.c -o box.o
