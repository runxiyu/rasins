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

all: clean yes errno

version:
	echo "#ifndef VERSION_H"                 > version.h
	echo "#define VERSION_H"                >> version.h
	echo "#define COMPILETIME \"$$(git show --no-patch --pretty=format:%H)\"" >> version.h
	echo                                    >> version.h
	echo "#endif"                           >> version.h

yes: yes.o
	mkdir -p bin
	$(CC) $(CFLAGS) yes.o -o bin/yes

errno: errno.o
	mkdir -p bin
	$(CC) $(CFLAGS) errno.o -o bin/errno

clean:
	rm -Rf bin/ *.o

# Utilities
# =========

errno.o: version
	$(CC) $(CFLAGS) $(NOLINKER) errno.c -o errno.o

yes.o: version
	$(CC) $(CFLAGS) $(NOLINKER) yes.c -o yes.o
