/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Change file ownership."
#define OPERANDS    "owner file"
#include "common.h"

int main(int argc, char *const argv[])
{
	struct passwd *user;
	if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
		return 1;
	}
	if ((user = getpwnam(argv[1])) == NULL
	    && (user = getpwuid(strtol(argv[1], NULL, 10))) == NULL)
		return errprint(argv[0], argv[1], errno);	/* User doesn't exist */
	/* User found! */
	else if ((user = getpwnam(argv[1])) != NULL)
		chown(argv[2], user->pw_uid, user->pw_gid);
	else if ((user = getpwuid(strtol(argv[1], NULL, 10))) != NULL)
		chown(argv[2], user->pw_uid, user->pw_gid);
	if (errno)
		return errprint(argv[0], argv[2], errno);

	return 0;
}
