/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#define _XOPEN_SOURCE		/* WHY???? */
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

/* Requirements in common.h */
#define REQ_PRINT_USAGE
#define REQ_ERRPRINT
#include "common.h"

#define DESCRIPTION "Change file access and modification times."
#define OPERANDS    "[-acm] [-t [[CC]YY]MMDDhhmm[.SS]] file..."

int main(int argc, char *argv[])
{
	int file, i, argument;
	struct timespec times[2];
	struct tm time_tm = { 0 };	/* Used by strptime() */
	char param[256], *argv0 = strdup(argv[0]), *datefmt, *date_string;
	for (i = 0; i < 256 && (param[i] = 0); i++) ;
	while ((argument = getopt(argc, argv, "acmt:")) != -1) {
		if (argument == '?')
			return print_usage(argv0, DESCRIPTION, OPERANDS,
					   VERSION);
		else if (argument == 't') {
			switch (strlen(optarg)) {
			case 8:	/* MMDDhhmm */
				datefmt = "%m%d%H%M";
				break;
			case 10:	/* YYMMDDhhmm */
				datefmt = "%y%m%d%H%M";
				break;
			case 12:	/* CCYYMMDDhhmm */
				datefmt = "%C%y%m%d%H%M";
				break;
			case 13:	/* MMDDhhmm.SS */
				datefmt = "%m%d%H%M.%S";
				break;
			case 15:	/* YYMMDDhhmm.SS */
				datefmt = "%y%m%d%H%M.%S";
				break;
			case 17:	/* CCYYMMDDhhmm.SS */
				datefmt = "%C%y%m%d%H%M.%S";
				break;
			default:
				return print_usage(argv0, DESCRIPTION, OPERANDS,
						   VERSION);
			}
			date_string = optarg;
		}
		param[(uint8_t) argument] = 1;
	}
	argc -= optind;
	argv += optind;
	if (argc < 1)
		return print_usage(argv0, DESCRIPTION, OPERANDS, VERSION);
	if (param['t']) {
		strptime(date_string, datefmt, &time_tm);
		if (errno)
			return errprint(argv0, "strptime()", errno);
		if (param['a'])
			times[0].tv_sec = mktime(&time_tm);
		if (param['m'])
			times[1].tv_sec = mktime(&time_tm);
		times[0].tv_nsec = 0;
		times[1].tv_nsec = 0;
	} else {
		times[0].tv_sec = time(NULL);
		times[1].tv_sec = time(NULL);
		times[0].tv_nsec = 0;
		times[1].tv_nsec = 0;
	}
	for (i = 0; i < argc; i++) {
		if (access(argv[i], F_OK) == -1 && errno == ENOENT
		    && !param['c']) {
			/* File does not exist */
			file = creat(argv[i],
				     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				     S_IROTH | S_IWOTH);
			futimens(file, times);
		} else if (access(argv[i], F_OK) != -1)
			/* File exists */
			utimensat(AT_FDCWD, argv[i], times, 0);
		else if (errno != ENOENT)
			return errprint(argv0, argv[i], errno);
	}
	return errprint(argv0, NULL, errno);
}
