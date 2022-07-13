/*	mkdir - create directories
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
#include <sys/stat.h>
#include <errno.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: mkdir [-p] [DIRECTORY] ...\n\n"
	"Create DIRECTORY\n\n");
}

int main(int argc, char *const argv[]) {
	char param[256];
	int success, argument, i = 1;
	char *basenamestr[256];

	if (argc == 1) {
		printUsage();
		return 1;
	}

	while ((argument = getopt(argc, argv, "p")) != -1) {
		if (argument == '?') {
			printUsage();
			return 0;
		}
		param[argument] = argument;
	}

	for (; i < argc; i++) {
		printf("Warning: -p ignored.\n");
		if (argv[i][0] != '-')
			success = !mkdir(argv[i], S_IRWXU | S_IRWXG | S_IRWXO) ? 0 : 1; 
		if (success == 1) {
			return errno;
		}

	}

	return 0;
}
