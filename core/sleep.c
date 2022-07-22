/*	sleep - suspend execution for an interval
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.");
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.");
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.");
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printUsage();

int main(int argc, char *argv[]) {
	long unsigned int seconds;
	
	if (argc == 2) {
		seconds = strtol(argv[1], NULL, 10);
		if (!seconds) {
			printUsage();
			return 1;
		}
		sleep(seconds);
	}
	else if (argc == 1) {
		printUsage();
		return 1;
	}

	return 0;
}

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: sleep seconds\n\n"
	"Suspend execution for <seconds> seconds.\n\n");
}
