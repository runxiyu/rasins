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

/* POSIX Header files */
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <sys/wait.h>
#include <spawn.h>
#include <libgen.h>

/* Our own header files */
#include "parser.h"
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

void  commandLoop();
int   getopt(int argc, char *const argv[], const char *optstring);
char *pathSearch(const char *path, const char *name);
void  printUsage();

int main(int argc, char *const argv[]) {
	int argument, i = 1;
	char param[256];
	for (; i <= 256; i++) param[i] = 0;

	while ((argument = getopt(argc, argv, "c")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		param[(uint8_t)argument] = argument;
	}
	commandLoop(1);
	return 0;
}

/* USAGE
 * -----
 * commandLoop()
 *
 * DESCRIPTION
 * -----------
 * This function is the actual command prompt.
 */

void commandLoop(int needprompt) {
	char *prompt = NULL;
	char *path   = getenv("PATH");
	char *command[4096];
	pid_t isparent;
	char name[4096];
	int return_code;
	int command_argc;
	if (prompt == NULL) prompt = "sh$ ";
	for (;;) {
		for (int i = 0; i <= 4096; i++) {
			name[i] = 0; /* (Re)Initialise name, very important. */
		}
		setvbuf(stdout, NULL, _IONBF, 0);
		if (needprompt) printf(prompt);
		read(STDIN_FILENO, name, 4096);
		if (!strcmp(name, "\n")) {
			continue;
		}
		name[strlen(name) - 1] = 0;
		command_argc = splitCommand(name, command); /* See parser.c */
		if (parseCommand(command_argc, command) == 127 /* See parser.c */ ) { 
			isparent = fork();
			wait(NULL);
			if (!isparent) { 
				/* Some sh implementations manually search for the command in PATH.
				 * This is not needed here because execvp is going to search for 
				 * that command in PATH anyway.
				 */
				return_code = execvp(command[0], command);
				/* If the child process is still alive, we know execvp(3) failed. */
				printf("sh: %s: Not found\n", command[0]);
				exit(0);
			}
		}
	}
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: sh [-c command_string]\n\n"
	"The standard command language interpreter.\n\n"
	"\t-c command_string\tExecute command_string and exit.\n", COMPILETIME);
}
