/*	mv - move files.
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
#include <errno.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: mv <FILE1> <FILE2>\n\n"
	"Move FILE1 to FILE2.\n\n");
}

int main(int argc, char *const argv[]) {
	int argument;

	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?' || argc != 3) {
			printUsage();
			return 1;
		}
	}
	if (argc != 3) {
		printUsage();
		return 1;
	}
	rename(argv[1], argv[2]); /* Technically, moving files == renaming files */
	if (errno) return errno;
	return 0;
}
