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
