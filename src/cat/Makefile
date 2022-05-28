# Makefile to build cat
include ../config.mk

build:
	$(CC) $(CFLAGS) main.c -o cat

clean:
	rm ./cat

install-alongside:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f cat ${DESTDIR}${PREFIX}/bin/cat-fases
	chmod 755 ${DESTDIR}${PREFIX}/bin/cat-fases

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f cat ${DESTDIR}${PREFIX}/bin/cat
	chmod 755 ${DESTDIR}${PREFIX}/bin/cat

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/cat-fases
	# rm ${DESTDIR}${PREFIX}/dwqbin/cat

