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

#include <string.h>
#include <stdio.h>

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: yes [STRING]\n\n"
	"Repeatedly output a line with specified STRING or 'y'.\n\n" );
}

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc > 1) {
		if (!strcmp(argv[1], "-h")) {
			printUsage();
			return 0;
		} else if (!strcmp(argv[1], "--")) {
			if (--argc == 1) goto yes;
			argv = &argv[1];
		}
		while(1) {
			for (int i = 1; i < argc; i++) printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
		}
	} else {
yes:
		while(1) printf("y\n");
	}
	return 0;
}
