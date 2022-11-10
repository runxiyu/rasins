/*	ln - link files
 *	Copyright (C) 2022 Ferass EL HAFIDI
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
#include <errno.h>
#include <string.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int argument;
	char param[256], *params = "s", *buffer;

	if (argc == 1) {
		printUsage();
		return 1;
	}
	while ((argument = getopt(argc, argv, params)) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		param[argument] = argument;
	}

	for (int i = 1; i < argc - 1; i++) {
		if (argv[argc - 1][0] == '-') argc--;
		if (argv[i][0] != '-') {
			if (param['f']) remove(argv[argc - 1]);
			if (param['s']) symlink(argv[i], argv[argc - 1]);
			/* The -P option is the default behavior (at least on musl), 
			 * so no if statement. 
			 */
			else if (param['L']) {
				readlink(argv[i], buffer, strlen(buffer)); /* Read the link */
				if (errno) return errno;
				link(buffer, argv[argc - 1]);
			}
			else link(argv[i], argv[argc - 1]);
			
			if (errno) return errno;
		}
	}
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: ln [-fs] [-P|-L] source_file target_file\n\n"
	"Link files.\n\n"
	"\t-s\tCreate symbolic links instead of hard links\n"
	"\t-f\tIf <target_file> exists, override the file\n"
	"\t-P\tIf <source_file> names a symbolic link, create a hard link to the "
	"symbolic link itself (default)\n"
	"\t-L\tIf <source_file> names a symbolic link, create a hard link to the "
	"file referenced by the symbolic link\n", COMPILETIME);
}
