# SPDX-License-Identifier: GPL-3.0-or-later
# Configuration
# =============
VERSION=r"$$(git rev-list --count HEAD)"."$$(git rev-parse --short HEAD)"
CC=cc # C Compiler
FORCEC99=-std=c99 # Force POSIX C99
# OPTIMIZE=-O3 # Experimental optimizations (Disabled by default)
CFLAGS=-D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\" -I. -Wall -Werror -Wextra -g $(FORCEC99) $(OPTIMIZE) # C Compiler flags
NOLINKER=-c # C Compiler flag to disable the linker
# Core utilities
CORE=\
	basename\
	[\
	cat\
	chmod\
	chown\
	date\
	dirname\
	echo\
	ed\
	false\
	head\
	link\
	ln\
	ls\
	mkdir\
	more\
	mv\
	printf\
	rm\
	sleep\
	tail\
	test\
	true\
	uname\
	unlink\
	wc
	# vi\ doesn't work for now #

INCLUDE_EXTRA=n # Should extra utils be included inside fasesiab?
# Extra utilities
EXTRA=\
	errno\
	yes

# Destination directory
DESTDIR=
PREFIX=/usr/local
# Prefix
