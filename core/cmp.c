/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* Requirements in common.h */
#define REQ_PRINT_USAGE
#define REQ_ERRPRINT 
#include "../common/common.h"

#define DESCRIPTION "Compare two files."
#define OPERANDS    "[-l|-s] file1 file2"

int main(int argc, char *argv[]) {
	FILE *file1, *file2;
	int argument, char_pos = 1, line_pos = 1, param_l, param_s, differ;
	char *argv0 = strdup(argv[0]);
	int ch1, ch2;

	while ((argument = getopt(argc, argv, "ls")) != -1) {
		if (argument == '?')
			return print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
		else if (argument == 'l') param_l = 1;
		else if (argument == 's') param_s = 1;
	} argc -= optind; argv += optind;
	if (argc != 2) return print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);

	/* Open the files. */
	file1 = fopen(argv[0], "r");
	file2 = fopen(argv[1], "r");
	if (file1 == NULL)
		return errprint(argv0, argv[0], errno);
	else if (file2 == NULL)
		return errprint(argv0, argv[1], errno);

	/* Compare! */
	while ((ch1 = fgetc(file1) != EOF) && (ch2 = fgetc(file2)) != EOF) {
		if (ch1 != ch2) {
			differ = 1;
			if (param_l)
				printf("%d %o %o\n", char_pos, ch1, ch2);
			else if (!param_s)
				printf("%s %s differ: char %d, line %d\n", argv[0], argv[1], 
					char_pos, line_pos);
			if (!param_l) break;
		}
		if (ch1 == '\n' && ch2 == '\n')
			line_pos++;
		char_pos++;
	}
	return differ;
}
