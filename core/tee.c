/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

/* Requirements in common.h */
#define REQ_PRINT_USAGE
#define REQ_ERRPRINT
#include "../common/common.h"

#define DESCRIPTION "Duplicate standard input."
#define OPERANDS    "[-ai] [file...]"

int main(int argc, char *argv[]) {
	int argument, length, i = 0, fildes[13], append_or_truncate = O_TRUNC;
	int ret = 0; /* Used for write errors. */
	char *argv0 = strdup(argv[0]), buffer[4096];

	while ((argument = getopt(argc, argv, "ai")) != -1) {
		if (argument == '?')
			return print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
		else if (argument == 'i') {
			struct sigaction signal_action;
			signal_action.sa_handler = SIG_IGN;
			sigemptyset(&signal_action.sa_mask);
			sigaction(SIGINT, &signal_action, NULL);
		} else if (argument == 'a')
			append_or_truncate = O_APPEND;
	} argc -= optind; argv += optind;
	/* Open all files */
	for (i = 0; i < argc && argc != 0 && i <= 13; i++) { /* TODO: No file limit */
		fildes[i] = open(argv[i], O_WRONLY | O_CREAT | append_or_truncate, 0666);
		if (errno) return errprint(argv0, argv[i], errno);
	}
	while ((length = read(STDIN_FILENO, buffer, 4096)) > 0) {
		write(STDOUT_FILENO, buffer, length); /* Write to stdout. */
		/* ...And to all other files */
		for (i = 0; i < argc && argc != 0 && i <= 13; i++) {
			write(fildes[i], buffer, length);
			if (errno) ret = errprint(argv0, argv[i], length);
		}
	}
	for (i = 0; i < argc && argc != 0 && i <= 13; i++) {
		close(fildes[i]);
		if (errno) return errprint(argv0, argv[i], errno);
	}

	return ret;
}
