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

void printUsage() {
	printf("Ferass' Base System.\n\n"
		"Usage: date\n\n"
		"Print the date and time.\n\n"
	);
}

int main() {
	time_t epoch = time(NULL);
	struct tm* date = localtime(&epoch);

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("%s", asctime(date));
	return 0;
}
