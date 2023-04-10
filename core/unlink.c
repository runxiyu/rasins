/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Call the unlink() function."
#define OPERANDS    "file"
#include "../common/common.h"

int main(int argc, char *const argv[]) {
	if (argc != 2) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	unlink(argv[1]);
	if (errno) return errprint(argv[0], argv[1], errno);
	return 0;
}
