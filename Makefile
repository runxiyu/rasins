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
CFLAGS=-Wall -Wextra -g $(FORCEC99) #-I.
NOLINKER=-c
SRC=cat\
	ls\
	date\
	yes\
	echo\
	true\
	mkdir

DESTDIR=
PREFIX=/usr/local

# Commands
# ========

all: clean mkdir head cat ls date yes box

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

mkdir: mkdir.o
	$(CC) $(CFLAGS) mkdir.o -o mkdir

echo: echo.o
	$(CC) $(CFLAGS) echo.o -o echo

true: true.o
	$(CC) $(CFLAGS) true.o -o true

prepbox:
	mkdir -p box_tmp
	for f in ${SRC}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < ""$$f".c" | sed "s/printUsage()/$$(echo "$$f")_printUsage()/g" > "box_tmp/"$$f"_box.c"; done

box: box.o
	$(CC) $(CFLAGS) box_tmp/*.c box.o -o box 

clean:
	rm -f mkdir head echo date cat ls clean yes box *.o
	rm -Rf box_tmp

install: box
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f box $(DESTDIR)$(PREFIX)/bin

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

mkdir.o:
	$(CC) $(CFLAGS) $(NOLINKER) mkdir.c -o mkdir.o

echo.o:
	$(CC) $(CFLAGS) $(NOLINKER) echo.c -o echo.o

true.o:
	$(CC) $(CFLAGS) $(NOLINKER) true.c -o true.o

box.o: prepbox
	$(CC) $(CFLAGS) $(NOLINKER) box.c -o box.o
