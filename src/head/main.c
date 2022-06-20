/*	head - print file until a certain line
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
#include <stdio.h>  /* To print the file's contents to stdout */
#include <stdlib.h> /* For opening files */
#include <string.h> /* To check for arguments */

int main(int argc, char *argv[]) {
	/* Check for arguments */
	if (argc >= 2) {
		char args;        /* Number of supported arguments */
		int usedargs = 0; /* Number of used arguments */
		int arg_lines;    /* Number of lines to print */
		for (int i = 1; argv[i]; i++) { /* For loop */
			if (argv[i][usedargs + 1] == 'n' && argv[i + 1]) {
					args = 'n'; 
					arg_lines = strtol(argv[i + 1], NULL, 0);
					usedargs++;
			}
			if (argv[i][usedargs + 1] == 'h') {
				/* Print the help message */
				printf("Ferass' Base System.\n");
				printf("\n");
				printf("Usage: %s [FILE] [-n NUMBER]\n", argv[0]);
				printf("\n");
				printf("Print FILE's contents until line NUMBER.\n");
				printf("\n");
				printf("\t-n NUMBER\tPrint first NUMBER line(s).\n");
				exit(0);
			}
		}
		FILE *file; /* Define 'file' */
		char s[512];
		int i = 0;  /* Integer used for the 'for' loop */
		file=fopen(argv[1], "r"); /* Open the file in read-only mode */
		if (file == NULL) { /* Check if the file has been opened successfully */
			printf("head: %s: No such file or directory\n", argv[1]);
			exit(1); /* If not, exit. */
		}
		while (i != arg_lines && (fgets(s, 512, file)) != NULL) {
			s[strcspn(s, "\n")] = 0; /* Remove trailing newline */
			/* Print the file's contents line by line to stdout */
			puts(s); 
			i++;
		}
		fclose(file); /* Close the file */
	}
	else if (argc == 1) {
		/* Enter in a loop where each line typed gets printed to stdout */
		while (1) {
			/* Read user output */
			char input[80];
			fgets(input, 80, stdin);
			/* Print it */
			printf("%s", input);
		}
	}
	return 0;
}
