#
#	Copyright (C) 2022 Ferass EL HAFIDI
#	Copyright (C) 2022 Leah Rowe
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Special
.POSIX:
.SUFFIXES: .o .c

# config.mk
include ../config.mk

# Utilities
all: clean $(CORE)

OBJ=$(CORE:=.o)
$(CORE): $(@:=.o)
$(OBJ): config

config:
	@echo "VERSION       = $(VERSION)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "CC            = $(CC)"
	@echo "DESTDIR       = $(DESTDIR)"
	@echo "PREFIX        = $(PREFIX)"
	@echo "INCLUDE_EXTRA = $(INCLUDE_EXTRA)"

.o:
	@mkdir -p bin
	$(CC) $(CFLAGS) $< common.c -o bin/$@

.c.o:
	@[ -e $< ] || echo "$@ is not implemented." ;
	$(CC) $(CFLAGS) $(NOLINKER) $< -o $@

# Cleaning
clean:
	rm -f *.o version.h
	rm -Rf bin

# Test Suite
UTILTOTEST=
ALLUTILS=\
	admin\
	alias\
	ar\
	asa\
	at\
	awk\
	basename\
	batch\
	bc\
	bg\
	c99\
	cal\
	cat\
	cflow\
	chgrp\
	chmod\
	chown\
	cksum\
	cmp\
	comm\
	command\
	compress\
	cp\
	crontab\
	csplit\
	ctags\
	cut\
	cxref\
	date\
	dd\
	delta\
	df\
	diff\
	dirname\
	du\
	echo\
	ed\
	env\
	ex\
	expand\
	expr\
	false\
	fc\
	fg\
	file\
	find\
	fold\
	fort77\
	fuser\
	gencat\
	get\
	getconf\
	getopts\
	grep\
	hash\
	head\
	iconv\
	id\
	ipcrm\
	ipcs\
	jobs\
	join\
	kill\
	lex\
	link\
	ln\
	locale\
	localedef\
	logger\
	logname\
	lp\
	ls\
	m4\
	mailx\
	make\
	man\
	mesg\
	mkdir\
	mkfifo\
	more\
	mv\
	newgrp\
	nice\
	nl\
	nm\
	nohup\
	od\
	paste\
	patch\
	pathchk\
	pax\
	pr\
	printf\
	prs\
	ps\
	pwd\
	qalter\
	qdel\
	qhold\
	qmove\
	qmsg\
	qrerun\
	qrls\
	qselect\
	qsig\
	qstat\
	qsub\
	read\
	renice\
	rm\
	rmdel\
	rmdir\
	sact\
	sccs\
	sed\
	sleep\
	sort\
	split\
	strings\
	strip\
	stty\
	tabs\
	tail\
	talk\
	tee\
	test\
	time\
	touch\
	tput\
	tr\
	true\
	tsort\
	tty\
	type\
	ulimit\
	umask\
	unalias\
	uname\
	uncompress\
	unexpand\
	unget\
	uniq\
	unlink\
	uucp\
	uudecode\
	uuencode\
	uustat\
	uux\
	val\
	vi\
	wait\
	wc\
	what\
	who\
	write\
	xargs\
	yacc\
	zcat

ifeq ($(UTILTOTEST),)
testsuite: $(CORE)
	for util in $(ALLUTILS); do [ -e $${util}.c ] || echo "utility $${util} is missing."; done
	# TODO: See if utilities already implemented are fully POSIX-compliant, from the source to the behaviour.
	#for util in $(CORE); do grep $${util} utilities.csv && $$(grep $${util} utilities.csv | awk -F',' '{ print $$3 }') (bin/$${util} $$(grep $${util} utilities.csv | awk -F',' '{ print $$1 }') || echo "ERR Utility $${util} isn't fully POSIX-compliant.") || echo "ERR Utility $${util} isn't in utilities.csv"; done
else
testsuite: $(UTILTOTEST)
	#@echo "TEST $(UTILTOTEST)"
	#[ -e $(UTILTOTEST) ] && $$(grep $(UTILTOTEST) utilities.csv | awk -F',' '{ print $$3 }') && bin/$(UTILTOTEST) $$(grep $(UTILTOTEST) utilities.csv | awk -F',' '{ print $$1 $$2 }') || echo "ERR Utility $(UTILTOTEST) isn't fully POSIX-compliant."
	#@echo "Done."
	@echo "not implemented."
endif
