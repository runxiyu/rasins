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
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int getopt(int argc, char *const argv[], const char *optstring);

ssize_t print(char *string)
	{ return write(STDOUT_FILENO, string, strlen(string)); }

int main(int argc, char *const argv[]) {
	if (argc == 2) {
		int arguments;
		while ((arguments = getopt(argc, argv, "h")) != -1) {
			if (arguments == 'h') {
				/* Print the help message */
				print("Ferass' Base System.\n\n"
						"Usage: ");
				print(argv[0]);
				print(" [FILE]\n\n"
					"Concatenate FILE to stdout\n\n");
				return 0;
			} else {
				return 1;
			}
		}
		int file;
		char s[4096];
		file=open(argv[1], O_RDONLY);

		if (file == -1) {
			print("cat: ");
			print(argv[1]);
			print(": No such file or directory\n");
			return 1;
		}
		while (read(file, s, 4096) > 0)
			print(s);

		close(file);
	}
	else if (argc == 1) {
		/* Each line typed gets printed to stdout */
		/* ^C will terminate the execution */
		while (1) {
			char input[4096];
			read(STDIN_FILENO, input, 4096);
			print(input);
		}
	}
	return 0;
}
