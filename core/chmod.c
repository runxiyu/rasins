/* SPDX-License-Identifier: BSD-3-Clause */
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Change file modes."
#define OPERANDS    "mode file"
#include "../common/common.h"

int main(int argc, char *const argv[]) {
	int argument, i = 0;
	mode_t owner_modes, group_modes, other_modes;
	char *argv0 = strdup(argv[0]);
	if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
	} argc -= optind; argv += optind;
	/* I know there's a better way of doing it, please let me know if you 
	 * know a better way of doing it 
	 */
	if (argv[0][i] == '0') i++;
	switch (argv[0][i]) {
		/* Owner modes */
		case '7':
			owner_modes = S_IRWXU;
			break;
		case '4':
			owner_modes = S_IRUSR;
			break;
		case '2':
			owner_modes = S_IWUSR;
			break;
		case '1':
			owner_modes = S_IXUSR;
			break;
		default:
			print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
			return 1;
	}
	i++;
	switch (argv[0][i]) {
		/* Group modes */
		case '7':
			group_modes = S_IRWXG;
			break;
		case '4':
			group_modes = S_IRGRP;
			break;
		case '2':
			group_modes = S_IWGRP;
			break;
		case '1':
			group_modes = S_IXGRP;
			break;
		default:
			print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
			return 1;
	}
	i++;
	switch (argv[0][i]) {
		/* Other modes */
		case '7':
			other_modes = S_IRWXO;
			break;
		case '4':
			other_modes = S_IROTH;
			break;
		case '2':
			other_modes = S_IWOTH;
			break;
		case '1':
			other_modes = S_IXOTH;
			break;
		default:
			print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
			return 1;
	}

	chmod(argv[1], owner_modes | group_modes | other_modes);
	return errprint(argv[0], "chmod()", errno);
}
