/*	mv - move files.
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
#include <fcntl.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int argument, file;
	char cmd, param[256];
	setvbuf(stdout, NULL, _IONBF, 0);
	for (int i = 0; i < 256; i++) param[i] = 0; /* Initialise param, 
	                                         * very important. */
	while ((argument = getopt(argc, argv, "if")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		param[argument] = argument;
		if (argument == 'f') param['i'] = 0;
		if (argument == 'i') param['f'] = 0;
	}
	if (!param['f']) param['i'] = 'i';
	if (argc < 3) {
		printUsage();
		return 1;
	}
	if ((file = open(argv[2], O_RDONLY)) != -1 && param['i']) {
		printf("File exists, override it? (y/n) ");
		read(STDIN_FILENO, &cmd, 3);
		if (cmd == 'n' || cmd == 'N') {
			close(file);
			return 0;
		}
	}
	close(file); /* In case it hasn't been closed */

	rename(argv[1], argv[2]); /* Technically, moving files == renaming files */
	if (errno) return errno;
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: mv [-if] file1 file2\n\n"
	"Move <file1> to <file2>.\n\n"
	"\t-i\tIf <file2> exists, ask for confirmation\n"
	"\t-f\tNever ask for confirmation\n", COMPILETIME);
}
