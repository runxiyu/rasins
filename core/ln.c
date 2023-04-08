/* SPDX-License-Identifier: BSD-3-Clause */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Link files."
#define OPERANDS    "[-fs] [-P|-L] source_file target_file"
#include "../common/common.h"

int  getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *const argv[]) {
	int argument;
	char param[256], *buffer = NULL, *argv0 = strdup(argv[0]);

	if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	while ((argument = getopt(argc, argv, params)) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;
	} argc -= optind; argv += optind;
	/* TODO: Fix error handling. */
	for (int i = 0; i < argc; i++) {
		if (param['f']) remove(argv[argc - 1]);
		if (errno) return errprint(argv0, argv[i], errno);
		if (param['s']) symlink(argv[i], argv[argc - 1]);
		/* The -P option is the default behavior (at least on musl), 
		 * so no if statement. 
		 */
		else if (param['L']) {
			readlink(argv[i], buffer, strlen(buffer)); /* Read the link */
			if (errno) return errprint(argv0, argv[i], errno);
			link(buffer, argv[argc - 1]);
		}
		else link(argv[i], argv[argc - 1]);
		if (errno) return errprint(argv0, argv[i], errno);
	}
	return 0;
}
