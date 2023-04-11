/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <stdio.h>
#include <string.h>
#include "common.h"

int print_usage(char *name, char *desc, char *params, char *version) {
	printf("fases %s (%s): %s\n"
	"Usage: %s %s\n", name, version, desc, name, params);
	return 1; /* This function is mostly called on error so return 1 */
}

int errprint(char *argv0, char *prefix, int err) {
	if (err == 0) return 0;
	if (prefix != NULL)
		fprintf(stderr, "%s: %s: %s\n", argv0, prefix, strerror(err));
	else
		fprintf(stderr, "%s: %s\n", argv0, strerror(err));
	return err;
}
