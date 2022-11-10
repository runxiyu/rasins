/*	rm - remove files.
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
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int argument, i = 1;
	char param[256];

	while ((argument = getopt(argc, argv, "Rr")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		param[argument] = argument;
	}
	if (argc <= 1) {
		printUsage();
		return 1;
	}

	for (; i < argc; i++) {
		if (!param['r'] || !param['R']) unlink(argv[i]);
		else                            remove(argv[i]); /* TODO: Actually 
		                                                  * recursively remove 
		                                                  * the directory */
	}

	if (errno) return errno;
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: rm [-Rr] file ...\n\n"
	"Remove <file>.\n\n"
	"\t-R\tRecursively remove the directory tree\n"
	"\t-r\tEnable the -R option\n", COMPILETIME);
}
