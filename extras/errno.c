/*	errno - give information about error codes
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

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define DESCRIPTION "Give information about error codes."
#define OPERANDS    "code"
#include "../common/common.h"

int main(int argc, char *argv[]) {
	long int error_code = 0;
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc == 2) {
		error_code = strtol(argv[1], NULL, 10);
		printf("errno %ld: %s\n", error_code, strerror(error_code));
	}
	else return print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
	return 0;
}
