/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Word, line, and byte/character count."
#define OPERANDS    "[-clwm] [file...]"
#include "common.h"

int main(int argc, char *const argv[])
{
	int argument, length;
	FILE *file;
	size_t len_getd = 4096;
	char *line = NULL, *argv0 = strdup(argv[0]);
	char param[256];
	ssize_t bytes = 0, newlines = 0, words = 0,
	    total_bytes = 0, total_newlines = 0, total_words = 0;
	if (argc < 2)
		return print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
	while ((argument = getopt(argc, argv, "clmw")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[(uint8_t) argument] = argument;
	}
	argc -= optind;
	argv += optind;
	if (!param['l'] && !param['m'] && !param['c'] && !param['w']) {
		param['l'] = 'l';
		param['m'] = 'm';
		param['c'] = 'c';
		param['w'] = 'w';
	}

	for (int i = 0; i != argc; i++) {
		words = 0;
		bytes = 0;
		newlines = 0;
		file = fopen(argv[i], "r");
		if (errno)
			return errprint(argv0, argv[i], errno);
		while ((length = getline(&line, &len_getd, file)) != -1) {
			if (param['l'])
				newlines++;
			if (param['c'] || param['m'])
				bytes += length;
		}
		rewind(file);	/* XXX: Won't work with standard input */
		if (errno)
			return errprint(argv0, argv[i], errno);
		if (param['w'])
			while ((length =
				getdelim(&line, &len_getd, (int)' ',
					 file)) != -1) {
				words++;
			}
		if (errno)
			return errprint(argv0, argv[i], errno);
		if (param['l'])
			printf("%zu ", newlines);
		if (param['w'])
			printf("%zu ", words);
		if (param['m'] || param['c'])
			printf("%zu ", bytes);
		printf("%s\n", argv[i]);
		fclose(file);
		if (errno)
			return errprint(argv0, argv[i], errno);
		total_bytes += bytes;
		total_words += words;
		total_newlines += newlines;
	}
	if (total_bytes != bytes) {
		if (param['l'])
			printf("%zu ", total_newlines);
		if (param['w'])
			printf("%zu ", total_words);
		if (param['m'] || param['c'])
			printf("%zu ", total_bytes);
		printf("total\n");
	}
	free(line);
	if (errno)
		return errprint(argv0, NULL, errno);
	return 0;
}
