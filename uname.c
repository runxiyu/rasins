/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Return system name."
#define OPERANDS    "[-amnrsv]"
#include "common.h"

int main(int argc, char *const argv[])
{
	int argument;
	struct utsname name;
	char param[256];
	for (int i = 0; i < 256; i++)
		param[i] = 0;
	char *argv0 = strdup(argv[0]);
	while ((argument = getopt(argc, argv, "amnrsv")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;
		if (argument == 'a') {
			param['s'] = 's';
			param['n'] = 'n';
			param['r'] = 'r';
			param['v'] = 'v';
			param['m'] = 'm';
		}
	}
	argc -= optind;
	argv += optind;

	uname(&name);
	if (errno)
		return errprint(argv0, NULL, errno);
	if (param['s']
	    || !(param['m'] && param['v'] && param['r'] && param['n']))
		printf("%s ", name.sysname);
	if (param['n'])
		printf("%s ", name.nodename);
	if (param['r'])
		printf("%s ", name.release);
	if (param['v'])
		printf("%s ", name.version);
	if (param['m'])
		printf("%s", name.machine);
	printf("\n");
	return errprint(argv0, NULL, errno);
}
