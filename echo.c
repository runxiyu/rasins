/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define REQ_ERRPRINT
#include "common.h"

int main(int argc, char *const argv[])
{
	int i = 1;

	for (i = 1; i != argc; i++) {
		printf("%s ", argv[i]);
	}
	putchar('\n');
	return errprint(argv[0], NULL, errno);
}
