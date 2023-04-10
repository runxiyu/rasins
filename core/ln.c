/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Link files."
#define OPERANDS    "[-fs] [-P|-L] source_file target_file"
#include "../common/common.h"

int  getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *const argv[]) {
	int argument;
	char param[256], *buffer = NULL, *argv0 = strdup(argv[0]);

	if (argc != 3) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	while ((argument = getopt(argc, argv, "fsPL")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;
	} argc -= optind; argv += optind;
	if (param['f']) remove(argv[1]);
	if (errno && errno != ENOENT) return errprint(argv0, argv[0], errno);
	errno = 0; /* Not reached if errno == ENOENT (no such file) */
	if (param['s']) symlink(argv[0], argv[1]);
	/* The -P option is the default behavior (at least on musl), 
	 * so no if statement. 
	 */
	else if (param['L']) {
		readlink(argv[0], buffer, strlen(buffer)); /* Read the link */
		if (errno) return errprint(argv0, argv[0], errno);
		link(buffer, argv[1]);
	}
	else link(argv[0], argv[1]);
	return errprint(argv0, argv[1], errno);
}
