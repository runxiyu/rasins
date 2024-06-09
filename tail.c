/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Copy the last part of files."
#define OPERANDS    "[-n number] [file] ..."
#include "common.h"

int main(int argc, char *const argv[])
{
	int argument, i = 1, lines = 10, file_lines;
	FILE *file;

	char s[4096], *argv0 = strdup(argv[0]);

	while ((argument = getopt(argc, argv, "n:")) != -1) {
		if (argument == '?' || argument == ':') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		} else if (argument == 'n') {
			lines = strtol(optarg, NULL, 10);
			if (errno)
				return errprint(argv[0], "strtol()", errno);
		}
	}
	argc -= optind;
	argv += optind;
	if (argc < 1) {
		while (read(STDIN_FILENO, s, 4096) > 0)
			printf("%s", s);
	}
	for (i = 0; i != argc; i++) {
		if (strcmp(argv[i], "-"))
			file = fopen(argv[i], "r");
		else
			while (read(STDIN_FILENO, s, 4096) > 0)
				printf("%s", s);
		if (file == NULL)
			return errprint(argv[0], argv[i], errno);	/* Something went wrong */
		while (fgets(s, 4096, file) != NULL)
			file_lines++;	/* Get number of lines */
		fclose(file);
		file_lines = file_lines - lines;
		if (strcmp(argv[i], "-"))
			file = fopen(argv[i], "r");
		while (fgets(s, 4096, file) != NULL) {
			if (errno)
				return errprint(argv0, argv[i], errno);
			if (file_lines == 0)
				printf("%s", s);
			else
				file_lines--;
		}
	}

	return errprint(argv0, NULL, errno);
}
