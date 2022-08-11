/*	[ - evaluate expression
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
void printUsage();

/* For readability reasons, define truee, falsee */
int truee  = 0;
int falsee = 1;

int main(int argc, char *argv[]) {
	int argument;
	char param[256];
	struct stat file_status;

	for (int i = 0; i < 256; i++) param[i] = 0;
	
	if (!strcmp(basename(argv[0]), "[")) {
		if (strcmp(argv[argc - 1], "]")) {
			/* FIXME: Is printing an error message POSIX-compliant? */
			printf("[: No matching ]\n");
			return 1;
		}
		argc--;
		argv[argc] = 0;
	}
	
	if (argc < 2) return falsee;
	if (!strcmp(argv[1], "!")) {
		truee  = 1;
		falsee = 0;
		argc--;
		argv++;
	}
	if (argc == 3) {
		param[(uint8_t)argv[1][1]] = argv[1][1];
		                            /*     Files     */
		stat(argv[2], &file_status);
		if (!errno) {
			if (param['b'] && S_ISBLK(file_status.st_mode) != 0)       return truee;
			else if (param['c'] && S_ISCHR(file_status.st_mode) != 0)  return truee;
			else if (param['d'] && S_ISDIR(file_status.st_mode) != 0)  return truee;
			/* Just return truee, if -e is used. If it was false, stat() would 
			 * have failed. If it failed, there's a check about which value 
			 * to return. Return falsee if -e is used, otherwise, return errno 
			 */
			else if (param['e'])                                       return truee;
			else if (param['f'] && S_ISREG(file_status.st_mode) != 0)  return truee;
			else if (param['g'] && file_status.st_mode & S_ISGID)      return truee;
			else if ((param['h'] || param['L']) 
					&& S_ISLNK(file_status.st_mode) != 0)              return truee;
			else if (param['p'] && S_ISFIFO(file_status.st_mode) != 0) return truee;
			/* TODO: Better check for -r/-w. */
			else if (param['r'] && (file_status.st_mode & S_IRUSR
						|| file_status.st_mode & S_IROTH))             return truee;
			else if (param['S'] && S_ISSOCK(file_status.st_mode) != 0) return truee;
			else if (param['s'] && file_status.st_size > 0)            return truee;
			else if (param['u'] && S_ISDIR(file_status.st_mode)
					&& file_status.st_mode & S_ISUID)                  return truee;
			else if (param['w'] && (file_status.st_mode & S_IWUSR
						|| file_status.st_mode & S_IWOTH))             return truee;
			else if (param['x'] && (file_status.st_mode & S_IXUSR
						|| file_status.st_mode & S_IXOTH))             return truee;
		}
		else if (errno && param['e']) return falsee;
		if (param['t']) printf("unimplemented\n");
		                           /*    Strings     */
		if (param['n'] && strlen(argv[2]))       return truee;
		else if (param['z'] && !strlen(argv[2])) return truee;
	}

	else if (argc == 4) {
		if (!strcmp(argv[2], "=") && !strcmp(argv[1], argv[3]))        return truee;
		else if (!strcmp(argv[2], "!=") && strcmp(argv[1], argv[3]))   return truee;
		else if (!strcmp(argv[2], "-eq") && !strcmp(argv[1], argv[3])) return truee;
		else if (!strcmp(argv[2], "-ne") && strcmp(argv[1], argv[3]))  return truee;
		else if (!strcmp(argv[2], "-gt") && 
				strtol(argv[1], NULL, 10) > strtol(argv[3], NULL, 10)) return truee;
		else if (!strcmp(argv[2], "-ge") && 
				strtol(argv[1], NULL, 10)>= strtol(argv[3], NULL, 10)) return truee;
		else if (!strcmp(argv[2], "-lt") && 
				strtol(argv[1], NULL, 10) < strtol(argv[3], NULL, 10)) return truee;
		else if (!strcmp(argv[2], "-le") && 
				strtol(argv[1], NULL, 10)<= strtol(argv[3], NULL, 10)) return truee;
	}

	/* TODO: Better error handling. */
	return falsee;
}
