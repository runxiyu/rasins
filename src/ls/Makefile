# Makefile to build ls
include ../config.mk

build:
	$(CC) $(CFLAGS) main.c -o ls

clean:
	rm ./ls

install-alongside:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ls ${DESTDIR}${PREFIX}/bin/ls-fases
	chmod 755 ${DESTDIR}${PREFIX}/bin/ls-fases

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ls ${DESTDIR}${PREFIX}/bin/ls
	chmod 755 ${DESTDIR}${PREFIX}/bin/ls

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/ls-fases
	# rm ${DESTDIR}${PREFIX}/dwqbin/ls

