/*	uname - return system name
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
#include <sys/utsname.h>
#include <errno.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  getopt(int argc, char *const argv[], const char *optstring);
void printUsage();

int main(int argc, char *const argv[]) {
	int argument;
	struct utsname name;
	char param[256];
	for (int i = 0; i < 256; i++) param[i] = 0;

	while ((argument = getopt(argc, argv, "amnrsv")) != -1) {
		if (argument == '?') {
			printUsage();
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

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: uname [-amnrsv] \n\n"
	"Return system name.\n\n"
	"\t-a\tSame as -mnrsv\n"
	"\t-m\tWrite the hardware's architecture\n"
	"\t-n\tWrite the network node hostname\n"
	"\t-r\tWrite the operating system release\n"
	"\t-s\tWrite the name of the operating system implementation\n"
	"\t-v\tWrite the current version of this release of the operating "
	"system implementation\n", COMPILETIME);
}
