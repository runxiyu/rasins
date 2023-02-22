/* SPDX-License-Identifier: GPL-3.0-or-later */
/* START */

#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <stdio.h>
/*  END  */
/* START */
int main(int argc, char *argv[]) {
	if (!strcmp(basename(argv[0]),"box") && argc > 1) {
		argc--;
		argv++;
	} if(0);
/*  END  */
/* START */
	else if (!strcmp(basename(argv[0]), "box") && argc == 1) {
		printf("fases box.\n");
		printf("Usage: box command [args] ...\n");
/*  END  */
		printf("¯\\_(ツ)_/¯ No commands found.");
/* START */
		printf("\n");
	}
	else {
		printf("box: %s: Not found or not implemented.\n", argv[0]);
	}
	return 0;
}
/*  END  */
/* Generated on Tue 21 Feb 20:06:57 CET 2023 */
