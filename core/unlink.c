/*	unlink - call the unlink() function
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
	"Usage: unlink <FILE>\n\n"
	"Call the unlink() function.\n\n");
}

int main(int argc, char *const argv[]) {
	int argument, i = 1;

	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?' || argc != 2) {
			printUsage();
			return 1;
		}
	}
	unlink(argv[1]);
	if (errno) return errno;
	return 0;
}
