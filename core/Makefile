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

include ../config.mk

# Commands
# ========

all: clean $(CORE)

head: head.o
	mkdir -p bin
	$(CC) $(CFLAGS) head.o -o bin/head

cat: cat.o
	mkdir -p bin
	$(CC) $(CFLAGS) cat.o -o bin/cat

ls: ls.o
	mkdir -p bin
	$(CC) $(CFLAGS) ls.o -o bin/ls

date: date.o
	mkdir -p bin
	$(CC) $(CFLAGS) date.o -o bin/date

yes: yes.o
	mkdir -p bin
	$(CC) $(CFLAGS) yes.o -o bin/yes

mkdir: mkdir.o
	mkdir -p bin
	$(CC) $(CFLAGS) mkdir.o -o bin/mkdir

echo: echo.o
	mkdir -p bin
	$(CC) $(CFLAGS) echo.o -o bin/echo

true: true.o
	mkdir -p bin
	$(CC) $(CFLAGS) true.o -o bin/true

false: false.o
	mkdir -p bin
	$(CC) $(CFLAGS) false.o -o bin/false

sleep: sleep.o
	mkdir -p bin
	$(CC) $(CFLAGS) sleep.o -o bin/sleep

printf: printf.o
	mkdir -p bin
	$(CC) $(CFLAGS) printf.o -o bin/printf

uname: uname.o
	mkdir -p bin
	$(CC) $(CFLAGS) uname.o -o bin/uname

link: link.o
	mkdir -p bin
	$(CC) $(CFLAGS) link.o -o bin/link

ln: ln.o
	mkdir -p bin
	$(CC) $(CFLAGS) ln.o -o bin/ln

chmod: chmod.o
	mkdir -p bin
	$(CC) $(CFLAGS) chmod.o -o bin/chmod

basename: basename.o
	mkdir -p bin
	$(CC) $(CFLAGS) basename.o -o bin/basename

clean:
	rm -f *.o
	rm -Rf bin

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

false.o:
	$(CC) $(CFLAGS) $(NOLINKER) false.c -o false.o

sleep.o:
	$(CC) $(CFLAGS) $(NOLINKER) sleep.c -o sleep.o

printf.o:
	$(CC) $(CFLAGS) $(NOLINKER) printf.c -o printf.o

uname.o:
	$(CC) $(CFLAGS) $(NOLINKER) uname.c -o uname.o

link.o:
	$(CC) $(CFLAGS) $(NOLINKER) link.c -o link.o

ln.o:
	$(CC) $(CFLAGS) $(NOLINKER) ln.c -o ln.o

chmod.o:
	$(CC) $(CFLAGS) $(NOLINKER) chmod.c -o chmod.o

basename.o:
	$(CC) $(CFLAGS) $(NOLINKER) basename.c -o basename.o
