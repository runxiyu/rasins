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
#include <fcntl.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: mv [-if] <FILE1> <FILE2>\n\n"
	"Move FILE1 to FILE2.\n\n"
	"\t-i\tIf FILE2 exists, ask for confirmation\n"
	"\t-f\tNever ask for confirmation\n");
}

int main(int argc, char *const argv[]) {
	int argument, file;
	char cmd, param[256];
	setvbuf(stdout, NULL, _IONBF, 0);
	while ((argument = getopt(argc, argv, "if")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		param[argument] = argument;
		if (argument == 'f') param['i'] = 0;
		if (argument == 'i') param['f'] = 0;
	}
	if (!param['f']) param['i'] = 'i';
	if (argc < 3) {
		printUsage();
		return 1;
	}
	if ((file = open(argv[2], O_RDONLY)) != -1 && param['i']) {
		printf("File exists, override it? (y/n) ");
		read(STDIN_FILENO, &cmd, 3);
		if (cmd == 'n' || cmd == 'N') {
			close(file);
			return 0;
		}
	}
	close(file); /* In case it hasn't been closed */

	rename(argv[1], argv[2]); /* Technically, moving files == renaming files */
	if (errno) return errno;
	return 0;
}
