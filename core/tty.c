/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define REQ_ERRPRINT		/* Require errprint() from ../common/common.h */
#include "../common/common.h"

int main(int argc, char *argv[])
{
	char *terminalname = ttyname(STDIN_FILENO);
	if (argc != 1) {
	}			/* workaround... */
	if (errno == ENOTTY) {
		/* POSIX says that if the stdin isn't a tty then the error shall be 
		 * written to stdout, not stderr.
		 */
		printf("not a tty\n");
		return 1;
	} else if (errno)
		return errprint(argv[0], NULL, errno);
	printf("%s\n", terminalname);
	return errprint(argv[0], NULL, errno);
}
