/*	[ - evaluate expression
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
#include <libgen.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int  getopt(int argc, char *const argv[], const char *optstring);

/* For readability reasons, define true, false */
int true  = 0;
int false = 1;

int main(int argc, char *argv[]) {
	char param[256];
	struct stat file_status;

	for (int i = 0; i < 256; i++) param[i] = 0;
	
	if (!strcmp(basename(argv[0]), "[")) {
		if (strcmp(argv[argc - 1], "]")) {
			/* FIXME: Is printing an error message POSIX-compliant? */
			fprintf(stderr, "[: No matching ]\n");
			return 1;
		}
		argc--;
		argv[argc] = 0;
	}
	
	if (argc < 2) return false;
	if (!strcmp(argv[1], "!")) {
		true  = 1;
		false = 0;
		argc--;
		argv++;
	}
	if (argc == 3) {
		param[(uint8_t)argv[1][1]] = argv[1][1];
		                            /*     Files     */
		stat(argv[2], &file_status);
		if (!errno) {
			if (param['b'] && S_ISBLK(file_status.st_mode) != 0)       return true;
			else if (param['c'] && S_ISCHR(file_status.st_mode) != 0)  return true;
			else if (param['d'] && S_ISDIR(file_status.st_mode) != 0)  return true;
			/* Just return true, if -e is used. If it was false, stat() would 
			 * have failed. If it failed, there's a check about which value 
			 * to return. Return false if -e is used, otherwise, return errno 
			 */
			else if (param['e'])                                       return true;
			else if (param['f'] && S_ISREG(file_status.st_mode) != 0)  return true;
			else if (param['g'] && file_status.st_mode & S_ISGID)      return true;
			else if ((param['h'] || param['L']) 
					&& S_ISLNK(file_status.st_mode) != 0)              return true;
			else if (param['p'] && S_ISFIFO(file_status.st_mode) != 0) return true;
			/* TODO: Better check for -r/-w. */
			else if (param['r'] && (file_status.st_mode & S_IRUSR
						|| file_status.st_mode & S_IROTH))             return true;
			else if (param['S'] && S_ISSOCK(file_status.st_mode) != 0) return true;
			else if (param['s'] && file_status.st_size > 0)            return true;
			else if (param['u'] && S_ISDIR(file_status.st_mode)
					&& file_status.st_mode & S_ISUID)                  return true;
			else if (param['w'] && (file_status.st_mode & S_IWUSR
						|| file_status.st_mode & S_IWOTH))             return true;
			else if (param['x'] && (file_status.st_mode & S_IXUSR
						|| file_status.st_mode & S_IXOTH))             return true;
		}
		else if (errno && param['e']) return false;
		if (param['t']) {
			if (isatty(strtol(argv[2], NULL, 10)))                     return true;
			else                                                       return false;
		}
		                           /*    Strings     */
		if (param['n'] && strlen(argv[2]))       return true;
		else if (param['z'] && !strlen(argv[2])) return true;
	}

	else if (argc == 4) {
		if (!strcmp(argv[2], "=") && !strcmp(argv[1], argv[3]))        return true;
		else if (!strcmp(argv[2], "!=") && strcmp(argv[1], argv[3]))   return true;
		else if (!strcmp(argv[2], "-eq") && !strcmp(argv[1], argv[3])) return true;
		else if (!strcmp(argv[2], "-ne") && strcmp(argv[1], argv[3]))  return true;
		else if (!strcmp(argv[2], "-gt") && 
				strtol(argv[1], NULL, 10) > strtol(argv[3], NULL, 10)) return true;
		else if (!strcmp(argv[2], "-ge") && 
				strtol(argv[1], NULL, 10)>= strtol(argv[3], NULL, 10)) return true;
		else if (!strcmp(argv[2], "-lt") && 
				strtol(argv[1], NULL, 10) < strtol(argv[3], NULL, 10)) return true;
		else if (!strcmp(argv[2], "-le") && 
				strtol(argv[1], NULL, 10)<= strtol(argv[3], NULL, 10)) return true;
	}

	/* TODO: Better error handling. */
	return false;
}
