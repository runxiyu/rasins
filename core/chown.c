/*	chown - change the file ownership
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

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include "version.h"
#include "print_usage.h"

#define DESCRIPTION "Change file ownership."
#define OPERANDS    "owner file"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *const argv[]) {
	int argument;
	struct passwd *user;
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
	if ((user = getpwnam(argv[1])) == NULL && (user = getpwuid(strtol(argv[1], NULL, 10))) == NULL)
		return errno; /* User doesn't exist */
	/* User found! */
	else if ((user = getpwnam(argv[1])) != NULL)
		chown(argv[2], user->pw_uid, user->pw_gid);
	else if ((user = getpwuid(strtol(argv[1], NULL, 10))) != NULL)
		chown(argv[2], user->pw_uid, user->pw_gid);
	if (errno) return errno;

	return 0;
}
