/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#define _POSIX_C_SOURCE 200809L

/* POSIX Header Files */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

/* sh Header Files */
#include "parser.h"
#include "commands.h"

int parseCommand(int, char **);
int splitCommand(char [4096], char *[4096]);

/* Parse a shell command and determine if the command to run is built-in or
 * external. It then runs the command accordinately. 
 * <It also could in the future handle tokens.>
 */

int parseCommand(int argc, char *argv[]) {
	struct sigaction signal_action;
	int status_code = 0, err = 0;
	pid_t isparent;
	if (argc == 0) return 0; /* There's no argument. */
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
		exit(-errno);
	}
	/* This code may be used to store the exit value in $?. */
	//if (errno != EINTR && WEXITSTATUS(status_code) !=) return WEXITSTATUS(status_code);
	//else return 0;
	err = WEXITSTATUS(status_code);
	if (err-256 == -E2BIG || err-256 == -EACCES || err-256 == -EINVAL || 
			err-256 == -ELOOP || 
			err-256 == -ENAMETOOLONG || err-256 == -ENOENT || err-256 == -ENOTDIR)
		printf("sh: %s: %s\n", argv[0], strerror(-(err-256)));
	return err;
}

/* This splits a command string in multiple words.
 * The array command can then be ran using execvp(3). It 
 * also returns an int that can be used as argc.
 */

int splitCommand(char name[4096], char *splitted_name[4096]) {
	long unsigned int array_index = 1;
	char *token;
	if ((token = strtok(name, " ")) != NULL && token[0] != '#')
		splitted_name[0] = token;
	else return 0;
	/* WARNING: Not thread-safe! */
	for (; (token = strtok(NULL, " ")) != NULL && 
			token[0] != '#' &&
			(splitted_name[array_index] = token); array_index++)
		/* Do nothing. */ ;
	return array_index;
}

