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

CC=cc # C Compiler
FORCEC99=-std=c99 # Force POSIX C99
# OPTIMIZE=-O3 # Experimental optimizations (Disabled by default)
CFLAGS=-I. -Wall -Wextra -g $(FORCEC99) $(OPTIMIZE) # C Compiler flags
NOLINKER=-c # C Compiler flag to disable the linker
# Core utilities
CORE=\
	basename\
	cat\
	chmod\
	chown\
	date\
	echo\
	false\
	head\
	link\
	ln\
	ls\
	Makefile
	mkdir\
	more\
	mv\
	printf\
	rm\
	sleep\
	true\
	uname\
	unlink

INCLUDE_EXTRA=n # Should extra utils be included inside fasesiab?
# Extra utilities
EXTRA=\
	yes\
	errno

# Destination directory
DESTDIR=
PREFIX=/usr/local
# Prefix
