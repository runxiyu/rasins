# SPDX-License-Identifier: GPL-3.0-or-later
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
	[ ! -e $< ] || $(CC) $(CFLAGS) $< ../common/common.c -o $@

.c.o:
	[ ! -e $< ] || $(CC) $(CFLAGS) $(NOLINKER) $< -o $@

# Cleaning
clean:
	rm -f *.o version.h $(CORE)

# Test Suite
UTILTOTEST=
ALLUTILS=admin alias ar asa at awk basename batch bc bg c99 cal cat cd cflow chgrp chmod chown cksum cmp comm command compress cp crontab csplit ctags cut cxref date dd delta df diff dirname du echo ed env ex expand expr false fc fg file find fold fort77 fuser gencat get getconf getopts grep hash head iconv id ipcrm ipcs jobs join kill lex link ln locale localedef logger logname lp ls m4 mailx make man mesg mkdir mkfifo more mv newgrp nice nl nm nohup od paste patch pathchk pax pr printf prs ps pwd qalter qdel qhold qmove qmsg qrerun qrls qselect qsig qstat qsub read renice rm rmdel rmdir sact sccs sed sh sleep sort split strings strip stty tabs tail talk tee test time touch tput tr true tsort tty type ulimit umask unalias uname uncompress unexpand unget uniq unlink uucp uudecode uuencode uustat uux val vi wait wc what who write xargs yacc zcat

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
