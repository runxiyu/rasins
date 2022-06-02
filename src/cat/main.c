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

/* Define a `print()` macro */
ssize_t print(char *string) { return write(STDOUT_FILENO, string, strlen(string)); }

int main(int argc, char *argv[]) {
	/* Check for arguments */
	if(argc == 2) {
		if (!strcmp(argv[1], "-h")) {
			/* Print the help message */
			print("Ferass' Base System.\n\n"
					"Usage: ");
			print(argv[0]);
			print(" [FILE]\n\n"
					"Concatenate FILE to stdout\n\n");
		}
		else {
			int file; /* Define 'file' */
			char s[200000]; /* Stupid character limit that will be removed soon */
			file=open(argv[1], O_RDONLY); /* Open the file(argv[1]) in read-only(O_RDONLY) mode */
			if(file == -1) /* Check if the file has been opened successfully */
			{
				print("cat: ");
				print(argv[1]);
				print(": No such file or directory\n");
				return 1; /* If not, exit. */
			}
			while(read(file, s, 200000) > 0)
			{
				/* Print the file's contents line by line to stdout */
				print(s);
			}
			close(file); /* Close the file */
		}
	}
	else if(argc == 1)
	{
		/* Enter in a loop where each line typed gets printed to stdout */
		while(1) {
			/* Read user input */
			char input[200000];
			read(STDIN_FILENO, input, 200000);
			/* Print it */
			print(input);
		}
	}
	return 0;
}
