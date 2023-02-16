/* SPDX-License-Identifier: BSD-3-Clause */
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc > 1) {
		if (!strcmp(argv[1], "--")) {
			if (--argc == 1) goto yes;
			argv = &argv[1];
		}
		while(1) {
			for (int i = 1; i < argc; i++) printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
		}
	} else {
yes:
		while(1) printf("y\n");
	}
	return 0;
}
