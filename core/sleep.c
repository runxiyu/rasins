/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT		/* Require errprint() from ../common/common.h */
#define DESCRIPTION "Suspend execution for an interval."
#define OPERANDS    "time"
#include "../common/common.h"

int main(int argc, char *argv[])
{
	long unsigned int seconds;

	if (argc == 2) {
		seconds = strtol(argv[1], NULL, 10);
		if (!seconds) {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		sleep(seconds);
	} else if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}

	return errprint(argv[0], NULL, errno);
}
