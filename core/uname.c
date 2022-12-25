/*	uname - return system name
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
#include <sys/utsname.h>
#include <errno.h>
#include "print_usage.h"

#define DESCRIPTION "Return system name."
#define OPERANDS    "[-amnrsv]"

int  getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *const argv[]) {
	int argument;
	struct utsname name;
	char param[256];
	for (int i = 0; i < 256; i++) param[i] = 0;

	while ((argument = getopt(argc, argv, "amnrsv")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;
		if (argument == 'a') {
			param['s'] = 's';
			param['n'] = 'n';
			param['r'] = 'r';
			param['v'] = 'v';
			param['m'] = 'm';
		}
	}

	uname(&name);
	if (errno) return errno;
	if (argc > 1) {
		if (param['s']) printf("%s ", name.sysname);
		if (param['n']) printf("%s ", name.nodename);
		if (param['r']) printf("%s ", name.release);
		if (param['v']) printf("%s ", name.version);
		if (param['m']) printf("%s", name.machine);
		printf("\n");
	}
	else
		printf("%s\n", name.sysname);

	return 0;
}
