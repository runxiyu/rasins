/*	basename - return non-directory portion of STRING
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
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *argv[]) {
	int argument, status;
	long unsigned int i;
	char *basenamestr;

	if (argc < 2) {
		printUsage();
		return 1;
	}
	basenamestr = basename(argv[1]);
	if (argc == 3) {
		for (i = 1; i <= strlen(argv[2]); ++i) {
			if (argv[1][strlen(argv[1]) - i] ==
				argv[2][strlen(argv[2]) - i])
				/* Check */
				status = 0;
			else status = 1;
		}
		
		if (status == 0) {
			for (i = 1; i <= strlen(argv[2]); ++i) {
				if (argv[1][strlen(argv[1]) - i] ==
					argv[2][strlen(argv[2]) - i]) {
					/* Replace with spaces for now ... */
					argv[1][strlen(argv[1]) - i] = ' '; 
				} // = '\0';
			}
		}
	}

	printf("%s\n", basenamestr);
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: basename string [suffix]\n\n"
	"Return non-directory portion of <string>.\n\n", COMPILETIME);
}
