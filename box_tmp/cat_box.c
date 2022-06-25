/*	cat - concatenate a file to stdout 
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *	Copyright (C) 2022 Leah Rowe
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
#include <unistd.h>
#include <stdio.h>

int getopt(int argc, char *const argv[], const char *optstring);

void cat_printUsage() {
	printf("Ferass' Base System.\n\n"
		"Usage: cat [FILE]\n\n"
		"Concatenate FILE to stdout\n\n");
}

int cat_main(int argc, char *const argv[]) {
	int file, argument;
	char s[4096], input[4096];

	setvbuf(stdout, NULL, _IONBF, 0);
	
	if (argc == 1) {
		while (1) {
			read(STDIN_FILENO, input, 4096);
			printf("%s", input);
		}
	}

	while ((argument = getopt(argc, argv, "h")) != -1) {
		if (argument == 'h') {
			cat_printUsage();
			return 0;
		} else return 1;
	}

	if ((file=open(argv[1], O_RDONLY)) == -1) {
		printf("cat: %s: No such file or directory\n", argv[1]);
		return 1;
	}
	while (read(file, s, 4096) > 0)
		printf("%s", s);

	close(file);
	return 0;
}
