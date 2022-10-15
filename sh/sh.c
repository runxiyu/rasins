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

/* Here's the POSIX specification of sh: */
/* https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html */

/* Define feature test macro. It doesn't compile with gcc without that for 
 * some reason.
 */
#define _POSIX_C_SOURCE 200809L

/* POSIX Header files */
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
#include <signal.h>

/* Our own header files */
#include "parser.h"
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

#warning "This shell implementation is really buggy and incomplete. \
 Please don't use this as a /bin/sh replacement."

void  commandLoop();
int   getopt(int argc, char *const argv[], const char *optstring);
char *pathSearch(const char *path, const char *name);
void  printUsage();

int main(int argc, char *const argv[]) {
	int argument, i = 1;
	FILE *file;
	char param[256];
	struct sigaction signal_action;
	signal_action.sa_handler = SIG_IGN;
	sigemptyset(&signal_action.sa_mask);
	for (; i <= 256; i++) param[i] = 0;

	while ((argument = getopt(argc, argv, "c")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		param[(uint8_t)argument] = argument;
	}
	argc -= optind;
	argv += optind;

	sigaction(SIGINT, &signal_action, NULL);
	if (errno) return errno;

	if (argv[0]) {
		file = fopen(argv[0], "r");
		if (errno) return errno;
		commandLoop(file);
	}
	else commandLoop(stdin);
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

void commandLoop(FILE *filstr) {
	struct sigaction signal_action;
	char *prompt = getenv("PS1");
	char *path   = getenv("PATH");
	char *token, *tokenstate;
	char *command[4096];
	pid_t isparent;
	char name[4096], tempstr[4096];
	int return_code;
	int command_argc;
	if (prompt == NULL) prompt = "$ ";
	for (;;) {
		for (int i = 0; i <= 4096; i++) {
			name[i]    = 0; /* (Re)Initialise name and command, 
			                 * very important. */
			command[i] = 0;
		}
		setvbuf(stdout, NULL, _IONBF, 0);
		if (filstr == stdin && isatty(STDIN_FILENO)) printf(prompt);
		if (fgets(name, 4096, filstr) == NULL)
			break;
		//read(fildes, name, 4096);
		if (!strcmp(name, "\n"))
			continue;
		else if (*name == 0 || *name == EOF) {
			putchar('\n');
			break;
		}
		name[strlen(name) - 1] = 0;
		strcpy(tempstr, name); /* We don't want to override `name`. */
		if (strtok(tempstr, ";") != NULL && strtok(NULL, ";") != NULL) {
			/* Hacky wacky hack. */
			strcpy(tempstr, name);
			token = strtok_r(tempstr, ";", &tokenstate);
			for (; token != NULL;) {
				command_argc = splitCommand(token, command); /* See parser.c */
				parseCommand(command_argc, command); /* See parser.c */
				token = strtok_r(NULL, ";", &tokenstate);
			}
		}
		else {
			command_argc = splitCommand(name, command); /* See parser.c */
			if ((errno = parseCommand(command_argc, command)) != 0 /* See parser.c */ )
				printf("sh: %s: %s\n", command[0], strerror(errno));
		}
	}
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: sh [-c command_string]\n\n"
	"The standard command language interpreter.\n\n"
	"\t-c command_string\tExecute command_string and exit.\n", COMPILETIME);
}
