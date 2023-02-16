# SPDX-License-Identifier: GPL-3.0-or-later
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

