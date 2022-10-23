/*	fasesiab - Ferass' Base System in a box 
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
/* START */

#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <stdio.h>
/*  END  */
int test_main(int, char**);
int basename_main(int, char**);
int cat_main(int, char**);
int chmod_main(int, char**);
int chown_main(int, char**);
int date_main(int, char**);
int dirname_main(int, char**);
int echo_main(int, char**);
int false_main(int, char**);
int head_main(int, char**);
int link_main(int, char**);
int ln_main(int, char**);
int ls_main(int, char**);
int mkdir_main(int, char**);
int more_main(int, char**);
int mv_main(int, char**);
int printf_main(int, char**);
int rm_main(int, char**);
int sleep_main(int, char**);
int tail_main(int, char**);
int test_main(int, char**);
int true_main(int, char**);
int uname_main(int, char**);
int unlink_main(int, char**);
/* START */
int main(int argc, char *argv[]) {
	if (!strcmp(basename(argv[0]),"box") && argc > 1) {
		argc--;
		argv++;
	} if(0);
/*  END  */
	else if(!strcmp(basename(argv[0]), "[")) return test_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "basename")) return basename_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "cat")) return cat_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "chmod")) return chmod_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "chown")) return chown_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "date")) return date_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "dirname")) return dirname_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "echo")) return echo_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "false")) return false_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "head")) return head_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "link")) return link_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "ln")) return ln_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "ls")) return ls_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "mkdir")) return mkdir_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "more")) return more_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "mv")) return mv_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "printf")) return printf_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "rm")) return rm_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "sleep")) return sleep_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "tail")) return tail_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "test")) return test_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "true")) return true_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "uname")) return uname_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "unlink")) return unlink_main(argc, argv);
/* START */
	else if (!strcmp(basename(argv[0]), "box") && argc == 1) {
		printf("Ferass' Base System in a box\n\n");
		printf("Usage: box <COMMAND> [ARGS]\n\n");
		printf("Commands available:\n");
/*  END  */
		printf("[ ");
		printf("basename ");
		printf("cat ");
		printf("chmod ");
		printf("chown ");
		printf("date ");
		printf("dirname ");
		printf("echo ");
		printf("false ");
		printf("head ");
		printf("link ");
		printf("ln ");
		printf("ls ");
		printf("mkdir ");
		printf("more ");
		printf("mv ");
		printf("printf ");
		printf("rm ");
		printf("sleep ");
		printf("tail ");
		printf("test ");
		printf("true ");
		printf("uname ");
		printf("unlink ");
/* START */
		printf("\n");
	}
	else {
		printf("box: %s: Not found or not implemented.\n", argv[0]);
	}
	return 0;
}
/*  END  */
/* Generated on Sun 23 Oct 19:30:23 CEST 2022 */
