/* SPDX-License-Identifier: BSD-3-Clause */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define REQ_ERRPRINT
#include "../common/common.h"

int main(int argc, char *const argv[]) {
	int i = 1;

	for (i = 1; i != argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");
	return errprint(argv[0], NULL, errno);
}
