/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT		/* Require errprint() from ../common/common.h */
#define DESCRIPTION "Move files."
#define OPERANDS    "[-if] source dest"
#include "../common/common.h"

int main(int argc, char *const argv[])
{
	int argument, file;
	char cmd, param[256], *argv0 = strdup(argv[0]);
	setvbuf(stdout, NULL, _IONBF, 0);
	for (int i = 0; i < 256; i++)
		param[i] = 0;	/* Initialise param, 
				 * very important. */
	while ((argument = getopt(argc, argv, "if")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;
		if (argument == 'f')
			param['i'] = 0;
		if (argument == 'i')
			param['f'] = 0;
	}
	argc -= optind;
	argv += optind;
	if (!param['f'])
		param['i'] = 'i';
	if (argc < 2) {
		print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	if ((file = open(argv[1], O_RDONLY)) != -1 && param['i']) {
		printf("File exists, override it? (y/n) ");
		read(STDIN_FILENO, &cmd, 1);
		if (cmd == 'n' || cmd == 'N') {
			close(file);
			return 0;
		}
	}
	close(file);		/* In case it hasn't been closed */

	if (rename(argv[0], argv[1]))
		/* Technically, moving files == renaming files */
		return errprint(argv0, NULL, errno);
	return 0;
}
