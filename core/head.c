/*	head - copy the first part of files 
 *	Copyright (C) 2022, 2023 Ferass EL HAFIDI
 *	Copyright (C) 2022 Leah Rowe
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

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define REQ_PRINT_USAGE /* Require print_usage() from common.h */
#define REQ_ERRPRINT /* Require errprint() from common.h */
#define DESCRIPTION "Copy file to standard output until <number> lines."
#define OPERANDS    "[-n number] [file] ..."
#include "common.h"

int main(int argc, char *const argv[]) {
	int argument, i, lines, lines_printed;
	FILE *file;
	char s[4096], *argv0 = strdup(argv[0]);

	while ((argument = getopt(argc, argv, "n:")) != -1) {
		if (argument == '?' || argument == ':') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		else if (argument == 'n') {
			lines = strtol(optarg, NULL, 10);
			if (errno) return errprint(argv[0], "strtol()", errno);
		}
		else
			lines = 10;
	} argc -= optind; argv += optind;
	if (argc < 2) {
		while (read(STDIN_FILENO, s, 4096) > 0)
			printf("%s", s);
	}
	if (!lines) lines = 10;
	for (i = 0; i != argc; i++) {
		if (strcmp(argv[i], "-")) file = fopen(argv[i], "r");
		else while (read(STDIN_FILENO, s, 4096) > 0) printf("%s", s);
		if (file == NULL) 
			return errprint(argv0, argv[i], errno); /* Something went wrong */
		for (lines_printed = 1; lines_printed <= lines; lines_printed++) {
			if (fgets(s, 4096, file) != NULL)
				printf("%s", s);
			else if (errno)
				return errprint(argv0, "fgets()", errno);
			fclose(file);
		}
	}
	return 0;
}
