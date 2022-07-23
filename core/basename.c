/*	basename - return non-directory portion of STRING
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
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *argv[]) {
	int argument, status;
	long unsigned int i;
	char *basenamestr;

	if (argc < 2) {
		printUsage();
		return 1;
	}
	basenamestr = basename(argv[1]);
	if (argc == 3) {
		for (i = 1; i <= strlen(argv[2]); ++i) {
			if (argv[1][strlen(argv[1]) - i] ==
				argv[2][strlen(argv[2]) - i])
				/* Check */
				status = 0;
			else status = 1;
		}
		
		if (status == 0) {
			for (i = 1; i <= strlen(argv[2]); ++i) {
				if (argv[1][strlen(argv[1]) - i] ==
					argv[2][strlen(argv[2]) - i]) {
					/* Replace with spaces for now ... */
					argv[1][strlen(argv[1]) - i] = ' '; 
				} // = '\0';
			}
		}
	}

	printf("%s\n", basenamestr);
	return 0;
}

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: basename string [suffix]\n\n"
	"Return non-directory portion of <string>.\n\n");
}
