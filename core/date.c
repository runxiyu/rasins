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

#include <time.h>
#include <stdio.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

void printUsage();

int main(int argc, char *argv[]) {
	time_t epoch = time(NULL);
	struct tm* date = localtime(&epoch);
	char date_s[31];
	const char *format;
	if (argc == 2 && argv[1][0] == '+') {
		argv[1]++;
		format = argv[1];
	}
	else {
		format = "%a %b %e %H:%M:%S %Z %Y";
	}
	strftime(date_s, 31, format, date);
	printf("%s\n", date_s);
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: date [+format]\n\n"
	"Output the date and time.\n\n", COMPILETIME);
}
