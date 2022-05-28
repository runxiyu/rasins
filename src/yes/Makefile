# Makefile to build yes
include ../config.mk

build:
	$(CC) $(ARGS) main.c -o yes

clean:
	rm ./yes

install-alongside:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f yes ${DESTDIR}${PREFIX}/bin/yes-fases
	chmod 755 ${DESTDIR}${PREFIX}/bin/yes-fases

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f yes ${DESTDIR}${PREFIX}/bin/yes
	chmod 755 ${DESTDIR}${PREFIX}/bin/yes

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/yes-fases
	# rm ${DESTDIR}${PREFIX}/dwqbin/yes

