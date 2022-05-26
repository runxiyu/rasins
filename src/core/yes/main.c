/*	yes - Repeatedly output a line with all specified STRING or 'y'.
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
#include <stdio.h>  /* To print STRING to stdout */
#include <string.h> /* To check for arguments */

int main(int argc, char *argv[]) {
	/* Check for arguments */
	if(argc == 2) {
		if (!strcmp(argv[1], "-h")) {
			/* Print the help message */
			printf("Ferass' Base System.\n");
			printf("\n");
			printf("Usage: %s [STRING]\n", argv[0]);
			printf("\n");
			printf("Repeatedly output a line with all specified STRING or 'y'.\n");
			printf("\n");
		}
		else {
			while(1) {
				printf("%s\n", argv[1]);
			}
		}
	}
	else if(argc == 1)
	{
		/* Enter in a loop where each line typed gets printed to stdout */
		while(1) {
			printf("y\n");
		}
	}
	return 0;
}
