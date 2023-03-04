/* SPDX-License-Identifier: BSD-3-Clause */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Copy file to standard output until <number> lines."
#define OPERANDS    "[-n number] [file] ..."
#include "../common/common.h"

int main(int argc, char *const argv[]) {
	int argument, i, lines = 10, lines_printed;
	FILE *file;
	char s[4096], *argv0 = strdup(argv[0]);

	while ((argument = getopt(argc, argv, "n:")) != -1) {
		if (argument == '?' || argument == ':') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		else if (argument == 'n') {
			lines = strtol(optarg, NULL, 10);
			if (errno) return errprint(argv[0], "strtol()", errno);
		}
		else
			lines = 10;
	} argc -= optind; argv += optind;

	for (i = 0; i != argc || argc == 0; i++) {
		if (argc == 0 || !strcmp(argv[i], "-"))
			file = stdin;
		else file = fopen(argv[i], "r");
		if (file == NULL) 
			return errprint(argv0, argv[i], errno); /* Something went wrong */
		for (lines_printed = 1; lines_printed <= lines; lines_printed++) {
			if (fgets(s, 4096, file) != NULL)
				printf("%s", s);
			else return errprint(argv0, "fgets()", errno);
		}
		if (file != stdin) fclose(file);
		if (argc == 0) return 0; /* TODO: Remove this stupid hack. */
	}
	return 0;
}
