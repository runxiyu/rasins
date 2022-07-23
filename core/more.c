/*	more - display files in a page-by-page basis.
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int i = 0, argument, success, read_file;
	long int columns, lines;
	char buffer[4096], cmd;
	FILE *file;
	struct termios oldattr, newattr;
	if (getenv("LINES")) lines = strtol(getenv("LINES"), NULL, 10) - 1;
	/* TODO: Calculate terminal size */
	else lines = 80;
	if (getenv("COLUMNS")) columns = strtol(getenv("COLUMNS"), NULL, 10);
	/* TODO: Calculate terminal size */
	else columns = 80;

	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
	}
	if (argc != 2) {
		printUsage(); return 1;
	}
	file = fopen(argv[1], "r");
	if (errno) return errno;
	success = 0;
	while (!success) {
		if (!read_file) read_file = 1; /* 1 => read on a page-by-page basis
		                                * 0 => don't read at all 
									    * 2 => read on a line-by-line basis
									    */
		for (i = 0; i < lines; i++) {
			if (fgets(buffer, 4096, file) != NULL) {
				//printf("%ld ", strcspn(buffer, "\n"));
				//if (read_file == 2)
				//buffer[strcspn(buffer, "\n")] = 0; /* Remove trailing newline */
				printf("%s", buffer);
			}
			else if (errno) return errno;
			else {
				success = 1;
				break;
			} /* EOF, end while and for loop */
			if (read_file == 2) {
				break;
			}
		}
		read_file = 0;
		/* TODO: Find a way of reading user commands 
		 * without having the command printed on the screen or 
		 * having them always at the bottom of the screen like 
		 * other implementations of `more`.
		 */
		
		/* Get a character */
		tcgetattr(0, &oldattr); /* Get previous terminal parameters */
		newattr = oldattr;
		newattr.c_lflag &= ~( ICANON | ECHO ); /* Disable ECHO and ICANON */
		tcsetattr( 0, TCSANOW, &newattr); /* Set net parameters */
		cmd = getchar();
		tcsetattr(0, TCSANOW, &oldattr); /* Restore old parameters */

		if (errno) return errno;
		switch (cmd) {
			case 'q':
				return 0;
			case 'h':
				printUsage();
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

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: more file ...\n\n"
	"Display a file on a page-by-page basis.\n\n");
}
