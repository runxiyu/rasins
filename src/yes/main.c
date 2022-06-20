/*	yes - Repeatedly output a line with all specified STRING or 'y'.
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
#include <string.h>
#include <unistd.h>

ssize_t print(char *string)
	{ return write(STDOUT_FILENO, string, strlen(string)); }

int main(int argc, char *argv[]) {
	if (argc > 1 && !strcmp(argv[1], "-h")) {
		print("Ferass' Base System.\n\n"
				"Usage: ");
		print(argv[0]);
		print(" [STRING]\n\n"
		"Repeatedly output a line with specified STRING or 'y'.\n\n");
	}
	else {
		if (argc > 1) {
			while(1) {
				print(argv[1]);
				print("\n");
			}
		}
		else {
			while(1) {
				print("y\n");
			}
		}
	}
	return 0;
}
