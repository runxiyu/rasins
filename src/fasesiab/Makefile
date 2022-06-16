include ../config.mk

build:
	# Find 'main(' and replace it by '<UTIL>_main(' to prevent conflicting function names. Remove print() definitions.
	for f in ${SRC}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < "../"$$f"/main.c" | sed "s/ssize_t print(char \*string) { return write(STDOUT_FILENO, string, strlen(string)); }/ssize_t print(char \*);/g" > ""$$f".c"; done
	# Remove print() declarations
	# Compile
	$(CC) $(CFLAGS) -o fasesiab *.c || echo "Did you perhaps forget to generate the main.c file?"
	rm $(SRC:=.c)

gen:
	echo "/*	fasesiab - Ferass' Base System in a box "             > main.c
	echo " *	Copyright (C) 2022 Ferass EL HAFIDI"                 >> main.c
	echo " *"                                                        >> main.c
	echo " *	This program is free software: you can redistribute it and/or modify"           >> main.c
	echo " *	it under the terms of the GNU General Public License as published by"           >> main.c
	echo " *	the Free Software Foundation, either version 3 of the License, or"              >> main.c
	echo " *	(at your option) any later version."                 >> main.c
	echo " *"                                                        >> main.c
	echo " *	This program is distributed in the hope that it will be useful,"                >> main.c
	echo " *	but WITHOUT ANY WARRANTY; without even the implied warranty of"                 >> main.c
	echo " *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"                  >> main.c
	echo " *	GNU General Public License for more details."        >> main.c
	echo " *"                                                        >> main.c
	echo " *	You should have received a copy of the GNU General Public License"              >> main.c
	echo " *	along with this program.  If not, see <https://www.gnu.org/licenses/>."         >> main.c
	echo " */"                                                       >> main.c
	echo                                                             >> main.c
	echo "/* Generated on $$(date) */"                               >> main.c
	echo "#include <string.h>"                                       >> main.c
	echo "#include <unistd.h>"                                       >> main.c
	echo "#include <libgen.h>"                                       >> main.c
	echo "#include <stdio.h>"                                        >> main.c
	echo                                                             >> main.c
	echo "ssize_t print(char *string) { return write(STDOUT_FILENO, string, strlen(string)); }" >> main.c
	for u in ${SRC}; do echo "int $${u%.c}_main(int, char**);"; done >> main.c
	echo                                                             >> main.c
	echo "int main(int argc, char *argv[]) {"                        >> main.c
	echo "	if (!strcmp(basename(argv[0]),\"fasesiab\") && argc > 1) {">> main.c
	echo "	{"                                                       >> main.c
	echo "		argc--;"                                             >> main.c
	echo "		argv++;"                                             >> main.c
	echo "	} if(0);"                                                >> main.c
	for u in ${SRC}; do echo "	else if(!strcmp(argv[0], \"$${u%.c}\")) return $${u%.c}_main(argc, argv);"; done >> main.c
	echo "	else {"                                                  >> main.c
	echo "		print(\"Ferass' Base System in a box\n\n\");"        >> main.c
	echo "		print(\"Usage: fasesiab <COMMAND> [ARGUMENTS]\n\n\");">> main.c
	echo "		print(\"Commands available:\n\");"                   >> main.c
	echo "		print(\"[ \");"                                      >> main.c
	for u in ${SRC}; do echo "		print(\"$${u%.c} \");"; done     >> main.c
	echo "		print(\"]\n\");"                                     >> main.c
	echo "	}"                                                       >> main.c
	echo "}"                                                         >> main.c

clear:
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
	echo "/* This file must be generated using \`make\`; use \`make gen\` to generate it */">> main.c

