/*	chmod - change file modes
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

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int argument, i = 0;
	mode_t modes, owner_modes, group_modes, other_modes;
	if (argc == 1) {
		printUsage();
		return 1;
	}
	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
	}
	/* I know there's a better way of doing it, please let me know if you 
	 * know a better way of doing it 
	 */
	if (argv[1][i] == '0') i++;
	switch (argv[1][i]) {
		/* Owner modes */
		case '7':
			owner_modes = S_IRWXU;
			break;
		case '4':
			owner_modes = S_IRUSR;
			break;
		case '2':
			owner_modes = S_IWUSR;
			break;
		case '1':
			owner_modes = S_IXUSR;
			break;
		default:
			printUsage();
			return 1;
	}
	i++;
	switch (argv[1][i]) {
		/* Group modes */
		case '7':
			group_modes = S_IRWXG;
			break;
		case '4':
			group_modes = S_IRGRP;
			break;
		case '2':
			group_modes = S_IWGRP;
			break;
		case '1':
			group_modes = S_IXGRP;
			break;
		default:
			printUsage();
			return 1;
	}
	i++;
	switch (argv[1][i]) {
		/* Other modes */
		case '7':
			other_modes = S_IRWXO;
			break;
		case '4':
			other_modes = S_IROTH;
			break;
		case '2':
			other_modes = S_IWOTH;
			break;
		case '1':
			other_modes = S_IXOTH;
			break;
		default:
			printUsage();
			return 1;
	}

	chmod(argv[2], owner_modes | group_modes | other_modes);
	return 0;
}

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: chmod mode file\n\n"
	"Change file modes.\n\n");
}
