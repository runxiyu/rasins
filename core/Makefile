# SPDX-License-Identifier: GPL-3.0-or-later
# Special
.POSIX:
.SUFFIXES: .o .c

# config.mk
include ../config.mk

# Utilities
OBJ=$(CORE:=.o)
all: clean $(CORE)
$(CORE): $(@:=.o)

include ../common.mk
