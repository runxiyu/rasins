# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
# Copyright (C) 2022 Leah Rowe <leah@libreboot.org>

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
