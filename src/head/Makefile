# Makefile to build head

build:
	cc --std=c99 main.c -o head

clean:
	rm ./head

install-alongside:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f head ${DESTDIR}${PREFIX}/bin/head-fases
	chmod 755 ${DESTDIR}${PREFIX}/bin/head-fases

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f head ${DESTDIR}${PREFIX}/bin/head
	chmod 755 ${DESTDIR}${PREFIX}/bin/head

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/head-fases
	# rm ${DESTDIR}${PREFIX}/dwqbin/head

