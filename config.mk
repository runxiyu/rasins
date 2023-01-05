#
#	Copyright (C) 2022, 2023 Ferass EL HAFIDI
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

# Configuration
# =============
VERSION=r"$$(git rev-list --count HEAD)"."$$(git rev-parse --short HEAD)"
CC=cc # C Compiler
FORCEC99=-std=c99 # Force POSIX C99
# OPTIMIZE=-O3 # Experimental optimizations (Disabled by default)
CFLAGS=-D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\" -I. -Wall -Werror -Wextra -g $(FORCEC99) $(OPTIMIZE) # C Compiler flags
NOLINKER=-c # C Compiler flag to disable the linker
# Core utilities
CORE=\
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

INCLUDE_EXTRA=n # Should extra utils be included inside fasesiab?
# Extra utilities
EXTRA=\
	errno\
	yes

# Destination directory
DESTDIR=
PREFIX=/usr/local
# Prefix
