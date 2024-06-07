/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 * Copyright (C) 2022 Leah Rowe <leah@libreboot.org>
 */
#include <time.h>
#include <stdio.h>
#include <errno.h>

#define REQ_ERRPRINT
#include "common.h"

int main(int argc, char *argv[])
{
	time_t epoch = time(NULL);
	struct tm *date = localtime(&epoch);
	char date_s[31];
	const char *format;
	if (argc == 2 && argv[1][0] == '+') {
		argv[1]++;
		format = argv[1];
	} else {
		format = "%a %b %e %H:%M:%S %Z %Y";
	}
	strftime(date_s, 31, format, date);
	printf("%s\n", date_s);
	return errprint(argv[0], NULL, errno);
}
