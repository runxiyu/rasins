/*	date - Show the date and time.
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

/*
 *	TODO: return proper error codes (0 and 1 are incorrect)
 *	https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html
 */

#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

ssize_t print(char *string)
	{ return write(STDOUT_FILENO, string, strlen(string)); }

void printUsage() {
		print("Ferass' Base System.\n\n"
			"Usage: date\n\n"
			"Print the date and time.\n\n"
		);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		struct tm *date;
		time_t epoch;
		epoch = time(NULL);
		date = localtime(&epoch);
		print(asctime(date));
	}
	else {
		printUsage();
	}
	return 0;
}
