# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2024 Runxi Yu <me@runxiyu.org>
# Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
# Copyright (C) 2022 Leah Rowe <leah@libreboot.org>

.POSIX:
.SUFFIXES: .o .c

include config.mk

OBJ=$(UTILS:=.o)
all: clean $(UTILS)
$(UTILS): $(@:=.o)


$(OBJ): config

config:
	@echo "VERSION       = $(VERSION)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "CC            = $(CC)"
	@echo "DESTDIR       = $(DESTDIR)"
	@echo "PREFIX        = $(PREFIX)"
	@echo "INCLUDE_EXTRA = $(INCLUDE_EXTRA)"

.o:
	[ ! -e $< ] || $(CC) $(CFLAGS) $< common.c -o $@

.c.o:
	[ ! -e $< ] || $(CC) $(CFLAGS) $(NOLINKER) $< -o $@

clean:
	rm -f *.o version.h $(UTILS)
