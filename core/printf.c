/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT		/* Require print_usage() from ../common/common.h */
#define DESCRIPTION "Write formatted strings to standard output."
#define OPERANDS    "format [string]"
#include "../common/common.h"

int main(int argc, char *const argv[])
{
	if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	printf(argv[1], argv[2] ? argv[2] : "");
	return errprint(argv[0], NULL, errno);
}
