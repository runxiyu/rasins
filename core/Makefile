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

ver:
	echo "#ifndef VERSION_H"                 > version.h
	echo "#define VERSION_H"                >> version.h
	echo "#define COMPILETIME \"$$(date)\"" >> version.h
	echo                                    >> version.h
	echo "#endif"                           >> version.h

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

unlink: unlink.o
	mkdir -p bin
	$(CC) $(CFLAGS) unlink.o -o bin/unlink

mv: mv.o
	mkdir -p bin
	$(CC) $(CFLAGS) mv.o -o bin/mv

rm: rm.o
	mkdir -p bin
	$(CC) $(CFLAGS) rm.o -o bin/rm

more: more.o
	mkdir -p bin
	$(CC) $(CFLAGS) more.o -o bin/more

chown: chown.o
	mkdir -p bin
	$(CC) $(CFLAGS) chown.o -o bin/chown

tail: tail.o
	mkdir -p bin
	$(CC) $(CFLAGS) tail.o -o bin/tail

[: test.o
	mkdir -p bin
	$(CC) $(CFLAGS) test.o -o bin/\[

test: test.o
	mkdir -p bin
	$(CC) $(CFLAGS) test.o -o bin/test

clean:
	rm -f *.o
	rm -Rf bin

# Utilities
# =========

head.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) head.c -o head.o

cat.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) cat.c -o cat.o

ls.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) ls.c -o ls.o

date.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) date.c -o date.o

yes.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) yes.c -o yes.o

mkdir.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) mkdir.c -o mkdir.o

echo.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) echo.c -o echo.o

true.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) true.c -o true.o

false.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) false.c -o false.o

sleep.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) sleep.c -o sleep.o

printf.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) printf.c -o printf.o

uname.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) uname.c -o uname.o

link.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) link.c -o link.o

ln.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) ln.c -o ln.o

chmod.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) chmod.c -o chmod.o

basename.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) basename.c -o basename.o

unlink.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) unlink.c -o unlink.o

mv.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) mv.c -o mv.o

rm.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) rm.c -o rm.o

more.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) more.c -o more.o

chown.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) chown.c -o chown.o

tail.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) tail.c -o tail.o

test.o: ver
	$(CC) $(CFLAGS) $(NOLINKER) test.c -o test.o
