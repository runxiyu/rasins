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
#include <errno.h>
#include <string.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int file, argument, i = 1, length;
	char s[4096];

	while ((argument = getopt(argc, argv, "u")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		else if (argument == 'u')
			setvbuf(stdout, NULL, _IONBF, 0);
		else
			setvbuf(stdout, NULL, _IOFBF, 0);
	}

	
	if (argc < 2) {
		while (read(STDIN_FILENO, s, 4096) > 0) {
			printf("%s", s);
			for (; i <= 4096 && (s[i] = 0); i++)
				/* (Re)initialise the buffer. */ ;
		}
	}

	for (i = 1; i != argc; i++) {
		if (strcmp(argv[i], "-u")) {
			if (strcmp(argv[i], "-")) file = open(argv[i], O_RDONLY);
			else file = STDIN_FILENO;
			if (file == -1) return errno; /* Something went wrong */
			while ((length = read(file, s, 4096)) > 0)
				write(STDOUT_FILENO, s, length);
			close(file);
		}
	}
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: cat [file]\n\n"
	"Concatenate <file> to standard output.\n"
	"When no file is specified or file is '-', read standard input\n\n"
	"\t-u\tPrint unbuffered\n", COMPILETIME);
}
