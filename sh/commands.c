/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
/* POSIX Header Files */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/* sh Header Files */
#include "commands.h"

int builtin_cd(int argc, char *argv[]);

/* *** COMMANDS *** */

/* cd - change directory */

int builtin_cd(int argc, char *argv[])
{
	if (argc > 1 && chdir(argv[1]) == -1 && errno) {
		printf("sh: cd: %s\n", strerror(errno));
		return errno;
	}
	return 0;
}
