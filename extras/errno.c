/* SPDX-License-Identifier: BSD-3-Clause */
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define DESCRIPTION "Give information about error codes."
#define OPERANDS    "code"
#include "../common/common.h"

int main(int argc, char *argv[]) {
	long int error_code = 0;
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc == 2) {
		error_code = strtol(argv[1], NULL, 10);
		printf("errno %ld: %s\n", error_code, strerror(error_code));
	}
	else return print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
	return 0;
}
