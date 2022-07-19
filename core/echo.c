/*	echo - write strings to stdout
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

#include <unistd.h>
#include <stdio.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: echo [string]\n\n"
	"Write <string> to standard output.\n\n");
}

int main(int argc, char *const argv[]) {
	int argument, i = 1;

	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
	}
	for (i = 1; i != argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}
