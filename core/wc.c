/*	wc - word, line, and byte/character count
 *	Copyright (C) 2022, 2023 Ferass EL HAFIDI
 *
 *	Redistribution and use in source and binary forms, with or without 
 *	modification, are permitted provided that the following conditions are met:
 *	
 *	    1. Redistributions of source code must retain the above copyright notice, 
 *	       this list of conditions and the following disclaimer.
 *	    2. Redistributions in binary form must reproduce the above copyright 
 *	       notice, this list of conditions and the following disclaimer in the 
 *	       documentation and/or other materials provided with the distribution.
 *	    3. Neither the name of the copyright holder nor the names of its 
 *	       contributors may be used to endorse or promote products derived from 
 *	       this software without specific prior written permission.
 *	
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 *	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *	POSSIBILITY OF SUCH DAMAGE.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE /* Require print_usage() from common.h */
#define REQ_ERRPRINT /* Require errprint() from common.h */
#define DESCRIPTION "Word, line, and byte/character count."
#define OPERANDS    "[-clwm] [file...]"
#include "common.h"

int main(int argc, char *const argv[]) {
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
		param[(uint8_t)argument] = argument;
	} argc -= optind; argv += optind;
	if (!param['l'] && !param['m'] && !param['c'] && !param['w']) {
		param['l'] = 'l';
		param['m'] = 'm';
		param['c'] = 'c';
		param['w'] = 'w';
	}

	for (int i = 0; i != argc; i++) {
		file = fopen(argv[i], "r");
		if (errno) return errprint(argv0, argv[i], errno);
		while ((length = getline(&line, &len_getd, file)) != -1) {
			if (param['l']) newlines++;
			if (param['c'] || param['m']) bytes += length;
		} rewind(file);
		if (errno) return errprint(argv0, argv[i], errno);
		if (param['w']) while ((length = getdelim(&line, &len_getd, (int)' ', file)) != -1) {
			words++;
		}
		if (errno) return errprint(argv0, argv[i], errno);
		if (param['l']) printf("%zu ", newlines);
		if (param['w']) printf("%zu ", words);
		if (param['m'] || param['c']) printf("%zu ", bytes);
		printf("%s\n", argv[i]);
		fclose(file);
		if (errno) return errprint(argv0, argv[i], errno);
		total_bytes += bytes;
		total_words += words;
		total_newlines += newlines;
		words = 0; bytes = 0; newlines = 0;
	}
	if (total_bytes != bytes) {
		if (param['l']) printf("%zu ", total_newlines);
		if (param['w']) printf("%zu ", total_words);
		if (param['m'] || param['c']) printf("%zu ", total_bytes);
		printf("total\n");
	}
	free(line);
	if (errno) return errprint(argv0, NULL, errno);
	return 0;
}
