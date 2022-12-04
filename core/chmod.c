/*	chmod - change file modes
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

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "version.h"
#include "print_usage.h"

#define DESCRIPTION "Change file modes."
#define OPERANDS    "mode file"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *const argv[]) {
	int argument, i = 0;
	mode_t owner_modes, group_modes, other_modes;
	if (argc == 1) {
		print_usage(argv[0], DESCRIPTION, OPERANDS, COMPILETIME);
		return 1;
	}
	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, COMPILETIME);
			return 1;
		}
	}
	/* I know there's a better way of doing it, please let me know if you 
	 * know a better way of doing it 
	 */
	if (argv[1][i] == '0') i++;
	switch (argv[1][i]) {
		/* Owner modes */
		case '7':
			owner_modes = S_IRWXU;
			break;
		case '4':
			owner_modes = S_IRUSR;
			break;
		case '2':
			owner_modes = S_IWUSR;
			break;
		case '1':
			owner_modes = S_IXUSR;
			break;
		default:
			print_usage(argv[0], DESCRIPTION, OPERANDS, COMPILETIME);
			return 1;
	}
	i++;
	switch (argv[1][i]) {
		/* Group modes */
		case '7':
			group_modes = S_IRWXG;
			break;
		case '4':
			group_modes = S_IRGRP;
			break;
		case '2':
			group_modes = S_IWGRP;
			break;
		case '1':
			group_modes = S_IXGRP;
			break;
		default:
			print_usage(argv[0], DESCRIPTION, OPERANDS, COMPILETIME);
			return 1;
	}
	i++;
	switch (argv[1][i]) {
		/* Other modes */
		case '7':
			other_modes = S_IRWXO;
			break;
		case '4':
			other_modes = S_IROTH;
			break;
		case '2':
			other_modes = S_IWOTH;
			break;
		case '1':
			other_modes = S_IXOTH;
			break;
		default:
			print_usage(argv[0], DESCRIPTION, OPERANDS, COMPILETIME);
			return 1;
	}

	chmod(argv[2], owner_modes | group_modes | other_modes);
	return 0;
}
