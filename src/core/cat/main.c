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
#include <stdio.h>  /* To print the file's contents to stdout */
#include <stdlib.h> /* For opening files */
#include <string.h> /* To check for arguments */

int main(int argc, char *argv[]) {
	/* Check for arguments */
	if(argc == 2) {
		if (!strcmp(argv[1], "--help")) {
			/* Print the help message */
			printf("Ferass' Base System.\n");
			printf("\n");
			printf("Usage: %s [FILE]\n", argv[0]);
			printf("\n");
			printf("Concatenate FILE to stdout.\n");
			printf("\n");
		}
		else {
			FILE *file; /* Define 'file' */
			char s;
			file=fopen(argv[1], "r"); /* Open the file in read-only mode */
			if(file==NULL) /* Check if the file has been opened successfully */
			{
				printf("cat: %s: No such file or directory\n", argv[1]);
				exit(1); /* If not, exit. */
			}
			do
			{
				s=getc(file);
				/* Print the file's contents line by line to stdout */
				printf("%c", s); 
			}
		while(s!=EOF); /* Until the end of the file */
		fclose(file); /* Close the file */
		}
	}
	else if(argc == 1)
	{
		/* Enter in a loop where each line typed gets printed to stdout */
		while(1) {
			char stdin_char;
			scanf("%s", &stdin_char);
			printf("%s\n", &stdin_char);
		}
	}
	return 0;
}
