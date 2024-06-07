/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Return directory portion of <string>."
#define OPERANDS    "string"
#include "common.h"

int main(int argc, char *argv[])
{
	char *dirnamestr;

	if (argc != 2) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	dirnamestr = dirname(argv[1]);

	printf("%s\n", dirnamestr);
	return errprint(argv[0], NULL, errno);
}
