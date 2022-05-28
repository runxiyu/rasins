include ../config.mk

build:
	# Find 'main(' and replace it by '<UTIL>_main(' to prevent conflicting function names
	for f in ${SRC}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < "../"$$f"/main.c" > ""$$f".c"; done
	# Compile
	$(CC) $(CFLAGS) -o fasesiab *.c
	# Remove junk
	rm $(SRC:=.c)

gen:
	echo "/*	fasesiab - Ferass' Base System in a box "             > main.c
	echo " *	Copyright (C) 2022 Ferass EL HAFIDI"                 >> main.c
	echo " *"                                                        >> main.c
	echo " *	This program is free software: you can redistribute it and/or modify"   >> main.c
	echo " *	it under the terms of the GNU General Public License as published by"   >> main.c
	echo " *	the Free Software Foundation, either version 3 of the License, or"      >> main.c
	echo " *	(at your option) any later version."                 >> main.c
	echo " *"                                                        >> main.c
	echo " *	This program is distributed in the hope that it will be useful,"        >> main.c
	echo " *	but WITHOUT ANY WARRANTY; without even the implied warranty of"         >> main.c
	echo " *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"          >> main.c
	echo " *	GNU General Public License for more details."        >> main.c
	echo " *"                                                        >> main.c
	echo " *	You should have received a copy of the GNU General Public License"      >> main.c
	echo " *	along with this program.  If not, see <https://www.gnu.org/licenses/>." >> main.c
	echo " */"                                                       >> main.c
	echo                                                             >> main.c
	echo "/* Generated on $$(date) */"                               >> main.c
	echo "#include <string.h>"                                       >> main.c
	echo "#include <stdio.h>"                                        >> main.c
	echo "#include <libgen.h>"                                       >> main.c
	echo                                                             >> main.c
	for u in ${SRC}; do echo "int $${u%.c}_main(int, char**);"; done >> main.c
	echo                                                             >> main.c
	echo "int main(int argc, char *argv[])"                          >> main.c
	echo "{"                                                         >> main.c
	echo "	if(!strcmp(basename(argv[0]),\"fasesiab\") && argc > 1)" >> main.c
	echo "	{"                                                       >> main.c
	echo "		argc--;"                                             >> main.c
	echo "		argv++;"                                             >> main.c
	echo "	} if(0);"                                                >> main.c
	for u in ${SRC}; do echo "	else if(!strcmp(argv[0], \"$${u%.c}\")) return $${u%.c}_main(argc, argv);"; done >> main.c
	echo "	else"                                                    >> main.c
	echo "	{"                                                       >> main.c
	echo "		printf(\"Ferass' Base System in a box\n\");"         >> main.c
	echo "		printf(\"\n\");"                                     >> main.c
	echo "		printf(\"Usage: fasesiab <COMMAND> [ARGUMENTS]\n\");">> main.c
	echo "		printf(\"\n\");"                                     >> main.c
	echo "		printf(\"Commands available:\n\");"                  >> main.c
	echo "		printf(\"[ \");"                                     >> main.c
	for u in ${SRC}; do echo "		printf(\"$${u%.c} \");"; done    >> main.c
	echo "		printf(\"]\n\");"                                    >> main.c
	echo "	}"                                                       >> main.c
	echo "}"                                                         >> main.c

