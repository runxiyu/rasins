# SPDX-License-Identifier: GPL-3.0-or-later
# Special
.POSIX:
.SUFFIXES: .o .c

# config.mk
include ../config.mk

# Utilities
all: clean $(CORE)

OBJ=$(CORE:=.o)
$(CORE): $(@:=.o)
$(OBJ): config

config:
	@echo "VERSION       = $(VERSION)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "CC            = $(CC)"
	@echo "DESTDIR       = $(DESTDIR)"
	@echo "PREFIX        = $(PREFIX)"
	@echo "INCLUDE_EXTRA = $(INCLUDE_EXTRA)"

.o:
	[ ! -e $< ] || $(CC) $(CFLAGS) $< ../common/common.c -o $@

.c.o:
	[ ! -e $< ] || $(CC) $(CFLAGS) $(NOLINKER) $< -o $@

# Cleaning
clean:
	rm -f *.o version.h $(CORE)
