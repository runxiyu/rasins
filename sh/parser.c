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

#define _POSIX_C_SOURCE 200809L

/* POSIX Header Files */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

/* sh Header Files */
#include "parser.h"
#include "commands.h"

int parseCommand(int, char **);
int splitCommand(char [4096], char *[4096]);

/* USAGE
 * -----
 * parseCommand(name);
 *
 * DESCRIPTION
 * -----------
 * Parse a shell command and determine if the command to run is built-in or
 * external. It then runs the command accordinately. 
 * <It also could in the future handle tokens.>
 */

int parseCommand(int argc, char *argv[]) {
	struct sigaction signal_action;
	int status_code = 0;
	pid_t isparent;
	if (!strcmp(argv[0], "cd")) return builtin_cd(argc, argv);
	/* The command isn't built-in. */
	isparent = fork();
	wait(&status_code);
	if (!isparent) {
		/* Do not ignore SIGINT when in a child process. */
		signal_action.sa_handler = SIG_DFL; 
		sigemptyset(&signal_action.sa_mask);
		sigaction(SIGINT, &signal_action, NULL);
		/* Some sh implementations manually search for the command in PATH.
		 * This is not needed here because execvp is going to search for 
		 * that command in PATH anyway.
		 */
		status_code = execvp(argv[0], argv);
		/* If the child process is still alive, we know execvp(3) failed. */
		exit(127);
	}
	/* This code may be used to store the exit value in $?. */
	//if (errno != EINTR && WEXITSTATUS(status_code) !=) return WEXITSTATUS(status_code);
	//else return 0;
	if (WEXITSTATUS(status_code) == 127) return 127;
	return 0;
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

