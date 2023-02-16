/* SPDX-License-Identifier: BSD-3-Clause */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Concatenate a file to standard output. \
	If no file is specified or file is '-', read standard input."
#define OPERANDS    "[-u] [file] ..."
#include "../common/common.h"

int cat(int flides, int unbuffered);

int main(int argc, char *const argv[]) {
	int file, argument, i = 1, unbuffered, err;
	char *argv0 = strdup(argv[0]);
	while ((argument = getopt(argc, argv, "u")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		else if (argument == 'u')
			unbuffered = 1;
	} argc -= optind; argv += optind;

	
	if (argc < 1) {
		return errprint(argv0, "-", cat(STDIN_FILENO, unbuffered));
	}

	for (i = 0; i != argc; i++) {
		if (strcmp(argv[i], "-")) file = open(argv[i], O_RDONLY);
		else file = STDIN_FILENO;
		if (file == -1)
			return errprint(argv0, argv[i], errno); /* Something went wrong */
		err = errprint(argv0, argv[i], cat(file, unbuffered));
		close(file);
	}
	return err;
}

int cat(int fildes, int unbuffered) {
	char s[4096];
	FILE *filstr;
	size_t length;
	if (unbuffered) while ((length = read(fildes, s, 4096)) > 0)
		write(STDOUT_FILENO, s, length);
	else {
		filstr = fdopen(fildes, "r");
		while ((length = fread(s, 4096, 1, filstr)) > 0)
			fwrite(s, length, 1, stdout);
	}
	if (errno) return errno;
	return 0;
}
