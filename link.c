/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Call the link() function."
#define OPERANDS    "source dest"
#include "common.h"

int main(int argc, char *const argv[])
{
	if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	if (argc >= 2) {
		link(argv[1], argv[2]);
		if (errno)
			return errprint(argv[0], NULL, errno);
	}
	return 0;
}
