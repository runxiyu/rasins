/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Link files."
#define OPERANDS    "[-fs] [-P|-L] source_file target_file"
#include "common.h"

int getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *const argv[])
{
	int argument;
	char param[256], *buffer = NULL, *argv0 = strdup(argv[0]);

	while ((argument = getopt(argc, argv, "fsPL")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;
	}
	argc -= optind;
	argv += optind;
	if (argc != 2) {
		print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	if (param['f'])
		remove(argv[1]);
	if (errno && errno != ENOENT)
		return errprint(argv0, argv[0], errno);
	errno = 0;		/* Not reached if errno == ENOENT (no such file) */
	if (param['s'])
		symlink(argv[0], argv[1]);
	else if (param['L']) {
		/* -L intentionally ignored if -s */
		/* FIXME: Buffer is unallocated, so it's completely broken
		 * Note that readlink(2) (on Linux at least) truncates the
		 * contents if the buffer is not long enough. See the NOTES
		 * section in its man page.
		 */
		readlink(argv[0], buffer, strlen(buffer));
		if (errno)
			return errprint(argv0, argv[0], errno);
		link(buffer, argv[1]);
	} else
		/* The -P option is the default behavior (at least on musl),
		 * so no if statement.
		 */
		/*
		 * FIXME: What if the user wants to override a prior -s with -P?
		 * The way fases handles options is unordered, so... idk.
		 */
		link(argv[0], argv[1]);
	return errprint(argv0, argv[0], errno);	// FIXME: This assumes that errno applies to argv[0]
}
