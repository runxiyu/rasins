# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
# Copyright (C) 2022 Leah Rowe <leah@libreboot.org>

# Configuration
# =============
VERSION="rasins v0.1r"$$(git rev-list --count HEAD)"."$$(git rev-parse --short HEAD)""
CC=cc # C Compiler
FORCEC99=-std=c99 # Force POSIX C99
# OPTIMIZE=-O3 # Experimental optimizations (Disabled by default)
CFLAGS=-D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\" -I. -Wall -Werror -Wextra -g -pedantic $(FORCEC99) $(OPTIMIZE) # C Compiler flags
NOLINKER=-c # C Compiler flag to disable the linker
# Core utilities
UTILS=\
	[\
	basename\
	cat\
	chmod\
	chown\
	cmp\
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
	tee\
	test\
	touch\
	tput\
	true\
	tty\
	uname\
	unlink\
	wc\
	errno\
	yes

# Destination directory
DESTDIR=
PREFIX=/usr/local
# Prefix
