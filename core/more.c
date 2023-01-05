/*	more - display files in a page-by-page basis.
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
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

#define REQ_PRINT_USAGE /* Require print_usage() from common.h */
#define REQ_ERRPRINT /* Require errprint() from common.h */
#define DESCRIPTION "Display files in a page-by-page basis."
#define OPERANDS    "file ..."
#include "common.h"

int  getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *const argv[]) {
	int i = 0, argument, success, read_file;
	long int /* columns, */ lines;
	char buffer[4096], cmd;
	struct winsize w;
	FILE *file;
	struct termios oldattr, newattr;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (getenv("LINES")) lines = strtol(getenv("LINES"), NULL, 10) - 1;
	else lines = w.ws_row - 1;
	//if (getenv("COLUMNS")) columns = strtol(getenv("COLUMNS"), NULL, 10);
	//else columns = w.ws_col - 1;

	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
	}
	if (argc != 2) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION); return 1;
	}
	file = fopen(argv[1], "r");
	if (errno) return errprint(argv[0], argv[1], errno);
	success = 0;
	while (!success) {
		if (!read_file) read_file = 1; /* 1 => read on a page-by-page basis
		                                * 0 => don't read at all 
									    * 2 => read on a line-by-line basis
									    */
		for (i = 0; i < lines && read_file != 0; i++) {
			if (fgets(buffer, 4096, file) != NULL) {
				printf("%s", buffer);
			}
			else if (errno) return errprint(argv[0], "fgets()", errno);
			else {
				success = 1;
				break;
			} /* EOF, end while and for loop */
			if (read_file == 2) {
				break;
			}
		}
		read_file = 0;
		
		/* Get a character */
		tcgetattr(0, &oldattr); /* Get previous terminal parameters */
		newattr = oldattr;
		newattr.c_lflag &= ~( ICANON | ECHO ); /* Disable ECHO and ICANON */
		tcsetattr(0, TCSANOW, &newattr); /* Set net parameters */
		cmd = getchar();
		tcsetattr(0, TCSANOW, &oldattr); /* Restore old parameters */

		if (errno) return errprint(argv[0], NULL, errno);
		switch (cmd) {
			case 'q':
				return 0;
			case 'h':
				print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
				read_file = 0;
				break;
			case ' ':
				read_file = 1; /* page-by-page */
				break;
			default:
				read_file = 2; /* line-by-line */
				break;
		}
	}
	return 0;
}
