/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/* Requirements in common.h */
#define REQ_PRINT_USAGE
#define REQ_ERRPRINT
#include "common.h"

#define DESCRIPTION "Change terminal characteristics."
#define OPERANDS    "init|clear|reset"

int main(int argc, char *argv[])
{
	int argument;
	char *argv0 = strdup(argv[0]);
	if (argc < 2)
		return 1 + print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
	while ((argument = getopt(argc, argv, "")) != -1) {
		/* To be used when -T gets implemented */
		if (argument == '?')
			return 1 + print_usage(argv0,
					       DESCRIPTION, OPERANDS, VERSION);
	}
	argc -= optind;
	argv += optind;
	if (!strcmp(argv[0], "init") || !strcmp(argv[0], "reset"))	/* init/reset */
		/* According to POSIX.1-2017 tput(1):
		 * > The difference between resetting and initializing a 
		 * > terminal is left unspecified
		 */
		write(STDOUT_FILENO, "\033c", 3);
	else if (!strcmp(argv[0], "clear"))	/* clear */
		write(STDOUT_FILENO, "\033[1;1H\033[2J", 11);
	else
		return 3 + print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
	return errprint(argv0, NULL, errno);
}
