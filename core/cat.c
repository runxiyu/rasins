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

#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  cat(int flides, int unbuffered);
void printUsage();

int main(int argc, char *const argv[]) {
	int file, argument, i = 1, unbuffered;

	while ((argument = getopt(argc, argv, "u")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		else if (argument == 'u')
			unbuffered = 1;
	}

	
	if (argc < 2) {
		cat(STDIN_FILENO, unbuffered);
	}

	for (i = 1; i != argc; i++) {
		if (strcmp(argv[i], "-u")) {
			if (strcmp(argv[i], "-")) file = open(argv[i], O_RDONLY);
			else file = STDIN_FILENO;
			if (file == -1) return errno; /* Something went wrong */
			cat(file, unbuffered);
			close(file);
		}
	}
	return 0;
}

int cat(int fildes, int unbuffered) {
	char s[4096];
	FILE *filstr;
	size_t length;
	if (unbuffered) while ((length = read(fildes, s, 4096)) > 0)
		write(STDOUT_FILENO, s, length);
	else {
		filstr = fdopen(fildes, "r");
		while ((length = fread(s, 4096, 1, filstr)) > 0)
			fwrite(s, length, 1, stdout);
	}
	if (errno) return errno;
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: cat [file]\n\n"
	"Concatenate <file> to standard output.\n"
	"When no file is specified or file is '-', read standard input\n\n"
	"\t-u\tPrint unbuffered\n", COMPILETIME);
}
