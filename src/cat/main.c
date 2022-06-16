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
#include <fcntl.h>  /* For opening files */
#include <string.h> /* To check for arguments */
#include <unistd.h> /* POSIX-compliant library */

/* For getopt */
int getopt(int argc, char *const argv[], const char *optstring);

/* Define a `print()` macro */
ssize_t print(char *string) { return write(STDOUT_FILENO, string, strlen(string)); }

int main(int argc, char *const argv[]) {
	/* Check for arguments */
	if (argc == 2) {
		int arguments;
		while ((arguments = getopt(argc, argv, "h")) != -1) {
			switch (arguments) {
				case 'h':
					/* Print the help message */
					print("Ferass' Base System.\n\n"
							"Usage: ");
					print(argv[0]);
					print(" [FILE]\n\n"
							"Concatenate FILE to stdout\n\n");
					return 0;
					break;
				default:
					return 1;
			}
		}
		int file; /* Define 'file' */
		char s[4096];
		file=open(argv[1], O_RDONLY); /* Open the file(argv[1]) in read-only(O_RDONLY) mode */
		if (file == -1) { /* Check if the file has been opened successfully */
			print("cat: ");
			print(argv[1]);
			print(": No such file or directory\n");
			return 1; /* If not, exit. */
		}
		while (read(file, s, 4096) > 0)
			/* Print the file's contents to stdout */
			print(s);

		close(file); /* Close the file */
	}
	else if (argc == 1) {
		/* Enter in a loop where each line typed gets printed to stdout */
		while (1) {
			/* Read user input */
			char input[4096];
			read(STDIN_FILENO, input, 4096);
			/* Print it */
			print(input);
		}
	}
	return 0;
}
