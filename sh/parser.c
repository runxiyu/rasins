/*	sh - the standard command language interpreter
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

/* POSIX Header Files */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* sh Header Files */
#include "parser.h"

int parseCommand(int, char **);
int splitCommand(char [4096], char *[4096]);

/* USAGE
 * -----
 * parseCommand(name);
 *
 * DESCRIPTION
 * -----------
 * Parse a shell command and determine if the command to run is built-in or
 * external. It then runs the command if it's built-in, or returns 127 if the 
 * command isn't built-in.
 */

int parseCommand(int argc, char *argv[]) {
	return 127; /* We don't have any built-in commands yet. */
}

/* USAGE
 * -----
 * splitCommand(name, dest);
 *
 * DESCRIPTION
 * -----------
 * This splits a command string in multiple words.
 * The array command can then be ran using execvp(3). It 
 * also returns an int that can be used as argc.
 */

int splitCommand(char name[4096], char *splitted_name[4096]) {
	long unsigned int array_index = 1;
	char *token;
	if ((token = strtok(name, " ")) != NULL) splitted_name[0] = token;
	/* WARNING: Not thread-safe! */
	for (; (token = strtok(NULL, " ")) != NULL && 
			(splitted_name[array_index] = token); array_index++)
		/* Do nothing. */ ;
	return array_index;
}

