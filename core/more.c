/* SPDX-License-Identifier: BSD-3-Clause */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Display files in a page-by-page basis."
#define OPERANDS    "file ..."
#include "../common/common.h"

int main(int argc, char *const argv[]) {
	int i = 0, argument, success, read_file;
	long int /* columns, */ lines;
	char buffer[4096], cmd, *argv0 = strdup(argv[0]);
	struct winsize w;
	FILE *file;
	struct termios oldattr, newattr;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (getenv("LINES")) lines = strtol(getenv("LINES"), NULL, 10) - 1;
	else lines = w.ws_row - 1;
	//if (getenv("COLUMNS")) columns = strtol(getenv("COLUMNS"), NULL, 10);
	//else columns = w.ws_col - 1;

	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
	} argc -= optind; argv += optind;
	if (argc != 1) {
		print_usage(argv0, DESCRIPTION, OPERANDS, VERSION); return 1;
	}
	file = fopen(argv[0], "r");
	if (errno) return errprint(argv0, argv[0], errno);
	success = 0;
	while (!success) {
		if (!read_file) read_file = 1; /* 1 => read on a page-by-page basis
		                                * 0 => don't read at all 
									    * 2 => read on a line-by-line basis
									    */
		for (i = 0; i < lines && read_file != 0; i++) {
			if (fgets(buffer, 4096, file) != NULL) {
				printf("%s", buffer);
			}
			else if (errno) return errprint(argv0, "fgets()", errno);
			else {
				success = 1;
				break;
			} /* EOF, end while and for loop */
			if (read_file == 2) {
				break;
			}
		}
		read_file = 0;
		
		/* Get a character */
		tcgetattr(0, &oldattr); /* Get previous terminal parameters */
		newattr = oldattr;
		newattr.c_lflag &= ~( ICANON | ECHO ); /* Disable ECHO and ICANON */
		tcsetattr(0, TCSANOW, &newattr); /* Set net parameters */
		cmd = getchar();
		tcsetattr(0, TCSANOW, &oldattr); /* Restore old parameters */

		if (errno) return errprint(argv0, NULL, errno);
		switch (cmd) {
			case 'q':
				return 0;
			case 'h':
				print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
				read_file = 0;
				break;
			case ' ':
				read_file = 1; /* page-by-page */
				break;
			default:
				read_file = 2; /* line-by-line */
				break;
		}
	}
	return 0;
}
