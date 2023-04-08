# SPDX-License-Identifier: GPL-3.0-or-later
# Special
.POSIX:
.SUFFIXES: .o .c

# config.mk
include ../config.mk

# Utilities
OBJ=$(EXTRA:=.o)
all: clean $(EXTRA)
$(EXTRA): $(@:=.o)

include ../common.mk
