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

# Special
.POSIX:
.SUFFIXES: .o .c

# config.mk
include ../config.mk

# Utilities
OBJ=$(EXTRA:=.o)
all: clean $(EXTRA)

config:
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "CC            = $(CC)"
	@echo "DESTDIR       = $(DESTDIR)"
	@echo "PREFIX        = $(PREFIX)"
	@echo "INCLUDE_EXTRA = $(INCLUDE_EXTRA)"

$(EXTRA): $(@:=.o)
$(OBJ): config

.o:
	$(CC) $(CFLAGS) $< ../common/common.c -o $@

.c.o:
	@[ -e $< ] || echo "$@ is not implemented." ;
	$(CC) $(CFLAGS) $(NOLINKER) $< -o $@

# Cleaning
clean:
	rm -f *.o version.h $(EXTRA)

