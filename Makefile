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

# Configuration
# =============

CC=cc
FORCEC99=-std=c99
CFLAGS=-I. -Wall -Wextra -g $(FORCEC99)
NOLINKER=-c
SRC=cat\
	ls\
	date\
	yes

# Commands
# ========

all: clean head cat ls date yes box

head: head.o
	$(CC) $(CFLAGS) head.o -o head

cat: cat.o
	$(CC) $(CFLAGS) cat.o -o cat

ls: ls.o
	$(CC) $(CFLAGS) ls.o -o ls

date: date.o
	$(CC) $(CFLAGS) date.o -o date

yes: yes.o
	$(CC) $(CFLAGS) yes.o -o yes

prepbox:
	mkdir -p box_tmp
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
	echo "ssize_t print(char *string) { return write(STDOUT_FILENO, string, strlen(string)); }" >> box.c
	for u in ${SRC}; do echo "int $${u%.c}_main(int, char**);"; done >> box.c
	echo                                                             >> box.c
	echo "int main(int argc, char *argv[]) {"                        >> box.c
	echo "	if (!strcmp(basename(argv[0]),\"box\") && argc > 1) {"   >> box.c
	echo "		argc--;"                                             >> box.c
	echo "		argv++;"                                             >> box.c
	echo "	} if(0);"                                                >> box.c
	for u in ${SRC}; do echo "	else if(!strcmp(argv[0], \"$${u%.c}\")) return $${u%.c}_main(argc, argv);"; done >> box.c
	echo "	else {"                                                  >> box.c
	echo "		print(\"Ferass' Base System in a box\n\n\");"        >> box.c
	echo "		print(\"Usage: fasesiab <COMMAND> [ARGUMENTS]\n\n\");">> box.c
	echo "		print(\"Commands available:\n\");"                   >> box.c
	echo "		print(\"[ \");"                                      >> box.c
	for u in ${SRC}; do echo "		print(\"$${u%.c} \");"; done     >> box.c
	echo "		print(\"]\n\");"                                     >> box.c
	echo "	}"                                                       >> box.c
	echo "}"                                                         >> box.c
	for f in ${SRC}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < ""$$f".c" | sed "s/printUsage()/$$(echo "$$f")_printUsage()/g" > "box_tmp/"$$f"_box.c"; done

box: box.o
	$(CC) $(CFLAGS) box_tmp/*.c box.o -o box 

clean:
	rm -f head date cat ls clean yes box box.c *.o
	rm -Rf box_tmp

# Utilities
# =========

head.o:
	$(CC) $(CFLAGS) $(NOLINKER) head.c -o head.o

cat.o:
	$(CC) $(CFLAGS) $(NOLINKER) cat.c -o cat.o

ls.o:
	$(CC) $(CFLAGS) $(NOLINKER) ls.c -o ls.o

date.o:
	$(CC) $(CFLAGS) $(NOLINKER) date.c -o date.o

yes.o:
	$(CC) $(CFLAGS) $(NOLINKER) yes.c -o yes.o

box.o: prepbox
	$(CC) $(CFLAGS) $(NOLINKER) box.c -o box.o
