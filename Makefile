# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
# Copyright (C) 2022 Leah Rowe <leah@libreboot.org>

.POSIX:

# Commands

all: config clean prepbox genbox box
include ./config.mk

config:
	@echo "VERSION       = $(VERSION)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "CC            = $(CC)"
	@echo "DESTDIR       = $(DESTDIR)"
	@echo "PREFIX        = $(PREFIX)"
	@echo "INCLUDE_EXTRA = $(INCLUDE_EXTRA)"

genbox:
	cat "box-templates/box_1-23.c"                                    > box.c
	test ${INCLUDE_CORE} == n || for u in ${CORE}; do echo "int $${u%.c}_main(int, char**);" | sed "s/\[_/test_/g"; done>> box.c
	test ${INCLUDE_EXTRA} == n || for u in ${EXTRA}; do echo "int $${u%.c}_main(int, char**);"; done>> box.c
	cat "box-templates/box_45-49.c"                                  >> box.c
	test ${INCLUDE_CORE} == n || for u in ${CORE}; do echo "	else if(!strcmp(basename(argv[0]), \"$${u%.c}\")) return $${u%.c}_main(argc, argv);" | sed "s/\[_/test_/g"; done >> box.c
	test ${INCLUDE_EXTRA} == n || for u in ${EXTRA}; do echo "	else if(!strcmp(argv[0], \"$${u%.c}\")) return $${u%.c}_main(argc, argv);"; done >> box.c
	cat "box-templates/box_70-73.c"                                  >> box.c
	test ${INCLUDE_CORE} == n || for u in ${CORE}; do echo "		printf(\"$${u%.c} \");"; done    >> box.c
	test ${INCLUDE_EXTRA} == n || for u in ${EXTRA}; do echo "		printf(\"$${u%.c} \");"; done    >> box.c
	test ${INCLUDE_CORE} == n && test ${INCLUDE_EXTRA} == n && echo "		printf(\"¯\\\\_(ツ)_/¯ No commands found.\");" >> box.c || true
	cat "box-templates/box_94-96.c"                                  >> box.c
	echo "/* Generated on $$(date) */"                               >> box.c

prepbox:
	mkdir -p box_tmp
	test ${INCLUDE_CORE} == n || for f in ${CORE}; do (sed "s/^int main(/int $$(echo "$$f")_main(/" < "core/"$$f".c" | sed "s/\"..\/common/\"common/g" | sed "s/\[_/test_/g") > "box_tmp/"$$f"_box.c"; done
	rm -f "box_tmp/[_box.c"
	test ${INCLUDE_EXTRA} == n || for f in ${EXTRA}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < "extras/"$$f".c" | sed "s/printUsage()/$$(echo "$$f")_printUsage()/g" > "box_tmp/"$$f"_box.c"; done

box: box.o
	test ${INCLUDE_CORE} = n && test ${INCLUDE_EXTRA} = n && $(CC) $(CFLAGS) common/common.c box.o -o box || $(CC) $(CFLAGS) box_tmp/*.c common/common.c box.o -o box
	rm -f version.h

clean:
	rm -f box *.o
	rm -Rf box_tmp
	for f in $(CORE); do rm -f core/$$f; done
	for f in $(EXTRA); do rm -f extras/$$f; done

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -r core/bin/* $(DESTDIR)$(PREFIX)/bin

install-box:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -r box $(DESTDIR)$(PREFIX)/bin

links:
	for u in ${CORE}; do ln -s "$(DESTDIR)$(PREFIX)/bin/box" "$(DESTDIR)$(PREFIX)/bin/$$u"; done

remove:
	rm -f $(DESTDIR)$(PREFIX)/bin/box
	for u in ${CORE}; do rm -f "$(DESTDIR)$(PREFIX)/bin/$$u"; done


# Utilities
# =========

box.o: prepbox
	$(CC) $(CFLAGS) $(NOLINKER) box.c -o box.o
