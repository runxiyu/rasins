/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#define REQ_PRINT_USAGE /* print_usage() from ../common/common.h */
#define DESCRIPTION "Return non-directory portion of <string>."
#define OPERANDS    "string [suffix]"
#include "../common/common.h"

int main(int argc, char *argv[]) {
	int status;
	long unsigned int i;
	char *basenamestr;

	if (argc < 2) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	basenamestr = basename(argv[1]);
	if (argc == 3) {
		for (i = 1; i <= strlen(argv[2]); ++i) {
			if (argv[1][strlen(argv[1]) - i] ==
				argv[2][strlen(argv[2]) - i])
				/* Check */
				status = 0;
			else status = 1;
		}
		
		if (status == 0) {
			for (i = 1; i <= strlen(argv[2]); ++i) {
				if (argv[1][strlen(argv[1]) - i] ==
					argv[2][strlen(argv[2]) - i]) {
					/* Replace with spaces for now ... */
					argv[1][strlen(argv[1]) - i] = ' '; 
				} // = '\0';
			}
		}
	}

	printf("%s\n", basenamestr);
	return 0;
}
