/*	chown - change the file ownership
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

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: chown owner file\n\n"
	"Change file ownership.\n\n");
}

int main(int argc, char *const argv[]) {
	int argument;
	struct passwd *user;
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
	if ((user = getpwnam(argv[1])) == NULL && (user = getpwuid(strtol(argv[1], NULL, 10))) == NULL)
		return errno; /* User doesn't exist */
	/* User found! */
	else if ((user = getpwnam(argv[1])) != NULL)
		chown(argv[2], user->pw_uid, user->pw_gid);
	else if ((user = getpwuid(strtol(argv[1], NULL, 10))) != NULL)
		chown(argv[2], user->pw_uid, user->pw_gid);
	if (errno) return errno;

	return 0;
}
