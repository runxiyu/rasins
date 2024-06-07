/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT		/* Require errprint() from ../common/common.h */
#define DESCRIPTION "Create directories."
#define OPERANDS    "directory ..."
#include "../common/common.h"

int main(int argc, char *const argv[])
{
	int success, argument, i = 0;
	char *argv0 = strdup(argv[0]);
	if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}

	while ((argument = getopt(argc, argv, "p")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 0;
		}
	}
	argc -= optind;
	argv += optind;

	for (; i < argc; i++) {
		if (argv[i][0] != '-')
			success =
			    !mkdir(argv[i],
				   S_IRWXU | S_IRWXG | S_IRWXO) ? 0 : 1;
		if (success == 1) {
			return errprint(argv0, argv[i], errno);
		}

	}

	return 0;
}
