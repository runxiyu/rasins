/* SPDX-License-Identifier: BSD-3-Clause */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Remove files."
#define OPERANDS    "[-Rr] file ..."
#include "../common/common.h"

int main(int argc, char *const argv[]) {
	int argument, i = 0;
	char param[256], *argv0 = strdup(argv[0]);

	while ((argument = getopt(argc, argv, "Rr")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;
	} argc -= optind; argv += optind;
	if (argc < 1) {
		print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}

	for (; i < argc; i++) {
		if (!param['r'] || !param['R']) unlink(argv[i]);
		else                            remove(argv[i]); /* TODO: Actually 
		                                                  * recursively remove 
		                                                  * the directory */
		if (errno) return errprint(argv0, argv[i], errno);
	}

	return 0;
}
