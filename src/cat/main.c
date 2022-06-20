/*	cat - concatenate a file to stdout 
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

/*
 *	TODO: return proper error codes (0 and 1 are incorrect)
 *	https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html
 */

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
		"Usage: cat [FILE]\n\n"
		"Concatenate FILE to stdout\n\n");
}

int main(int argc, char *const argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);

	if (argc == 2) {
		int argument;
		while ((argument = getopt(argc, argv, "h")) != -1) {
			if (argument == 'h') {
				/* Print the help message */
				printUsage();
				return 0;
			} else {
				return 1;
			}
		}
		int file;
		char s[4096];
		file=open(argv[1], O_RDONLY);

		if (file == -1) {
			printf("cat: %s: No such file or directory\n", argv[1]);
			return 1;
		}
		while (read(file, s, 4096) > 0)
			printf("%s", s);

		close(file);
	}
	else if (argc == 1) {
		/* Each line typed gets printed to stdout */
		/* ^C will terminate the execution */
		while (1) {
			char input[4096];
			read(STDIN_FILENO, input, 4096);
			printf("%s", input);
		}
	}
	return 0;
}
