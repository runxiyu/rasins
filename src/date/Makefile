# Makefile to build date
include ../config.mk

build:
	$(CC) $(CFLAGS) main.c -o date

clean:
	rm ./date

install-alongside:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f date ${DESTDIR}${PREFIX}/bin/date-fases
	chmod 755 ${DESTDIR}${PREFIX}/bin/date-fases

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f date ${DESTDIR}${PREFIX}/bin/date
	chmod 755 ${DESTDIR}${PREFIX}/bin/date

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/date-fases
	# rm ${DESTDIR}${PREFIX}/dwqbin/date

