/* SPDX-License-Identifier: BSD-3-Clause */
#include <unistd.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <errno.h>
#include <string.h>

#define REQ_PRINT_USAGE /* Require print_usage() from ../common/common.h */
#define REQ_ERRPRINT /* Require errprint() from ../common/common.h */
#define DESCRIPTION "Return system name."
#define OPERANDS    "[-amnrsv]"
#include "../common/common.h"

int main(int argc, char *const argv[]) {
	int argument;
	struct utsname name;
	char param[256];
	for (int i = 0; i < 256; i++) param[i] = 0;
	char *argv0 = strdup(argv[0]);
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
	} argc -= optind; argv += optind;

	uname(&name);
	if (errno) return errprint(argv0, NULL, errno);
	if (param['s']) printf("%s ", name.sysname);
	if (param['n']) printf("%s ", name.nodename);
	if (param['r']) printf("%s ", name.release);
	if (param['v']) printf("%s ", name.version);
	if (param['m']) printf("%s", name.machine);
	if (argc == 0)  printf("%s ", name.sysname);
	printf("\n");
	return 0;
}
