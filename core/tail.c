/*	tail - copy the last part of files 
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
#include <stdlib.h>

/* Functions Prototypes */
int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int argument, i = 1, lines, file_lines;
	FILE *file;

	char s[4096];

	while ((argument = getopt(argc, argv, "n:")) != -1) {
		if (argument == '?' || argument == ':') {
			printUsage();
			return 1;
		}
		else if (argument == 'n') {
			lines = strtol(optarg, NULL, 10);
			if (errno) return errno;
		}
		else
			lines = 10;
	}
	if (argc < 2) {
		while (read(STDIN_FILENO, s, 4096) > 0)
			printf("%s", s);
	}
	if (!lines) lines = 10;
	for (i = 1; i != argc; i++) {
		if (strcmp(argv[i], "-n")) {
			if (strcmp(argv[i], "-")) file = fopen(argv[i], "r");
			else while (read(STDIN_FILENO, s, 4096) > 0) printf("%s", s);
			if (file == NULL) return errno; /* Something went wrong */
			while (fgets(s, 4096, file) != NULL) 
				file_lines++; /* Get number of lines */
			fclose(file);
			file_lines = file_lines - lines;
			if (strcmp(argv[i], "-")) file = fopen(argv[i], "r");
			while (fgets(s, 4096, file) != NULL) {
				if (errno) return errno;
				if (file_lines == 0) printf("%s", s);
				else file_lines--;
			}
		}
		else i++;
	}

	return 0;
}

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: head [-n number] [file]\n\n"
	"Copy file to standard output until <number> lines.\n\n"
	"\t-n number\tNumber of lines to be copied to standard output\n");
}
