/*	ln - link files
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
#include <string.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: ln [-s] <SOURCE> ... <TARGET>\n\n"
	"Link SOURCE-s to TARGET.\n\n"
	"\t-s\tCreate symbolic links instead of hard links\n"
	"\t-f\tIf TARGET exists, override the file");
}

int main(int argc, char *const argv[]) {
	int argument;
	char param[256], *params = "s";

	if (argc == 1) {
		printUsage();
		return 1;
	}
	while ((argument = getopt(argc, argv, params)) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		param[argument] = argument;
	}

	for (int i = 1; i < argc - 1; i++) {
		if (argv[argc - 1] == '-') argc--;
		if (argv[i][0] != '-') {
			if (param['f']) remove(argv[argc - 1]);
			if (param['s']) symlink(argv[i], argv[argc - 1]);
			else link(argv[i], argv[argc - 1]);
			if (errno) return errno;
		}
	}
	return 0;
}
