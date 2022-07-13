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

/* Generated on Wed 13 Jul 16:16:46 CEST 2022 */
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <stdio.h>

int cat_main(int, char**);
int ls_main(int, char**);
int date_main(int, char**);
int echo_main(int, char**);
int true_main(int, char**);
int false_main(int, char**);
int mkdir_main(int, char**);
int head_main(int, char**);
int printf_main(int, char**);
int sleep_main(int, char**);
int ln_main(int, char**);
int uname_main(int, char**);
int link_main(int, char**);
int chmod_main(int, char**);
int basename_main(int, char**);
int yes_main(int, char**);
int errno_main(int, char**);

int main(int argc, char *argv[]) {
	if (!strcmp(basename(argv[0]),"box") && argc > 1) {
		argc--;
		argv++;
	} if(0);
	else if(!strcmp(basename(argv[0]), "cat")) return cat_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "ls")) return ls_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "date")) return date_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "echo")) return echo_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "true")) return true_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "false")) return false_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "mkdir")) return mkdir_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "head")) return head_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "printf")) return printf_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "sleep")) return sleep_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "ln")) return ln_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "uname")) return uname_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "link")) return link_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "chmod")) return chmod_main(argc, argv);
	else if(!strcmp(basename(argv[0]), "basename")) return basename_main(argc, argv);
	else if(!strcmp(argv[0], "yes")) return yes_main(argc, argv);
	else if(!strcmp(argv[0], "errno")) return errno_main(argc, argv);
	else {
		printf("Ferass' Base System in a box\n\n");
		printf("Usage: box <COMMAND> [ARGS]\n\n");
		printf("Commands available:\n");
		printf("cat ");
		printf("ls ");
		printf("date ");
		printf("echo ");
		printf("true ");
		printf("false ");
		printf("mkdir ");
		printf("head ");
		printf("printf ");
		printf("sleep ");
		printf("ln ");
		printf("uname ");
		printf("link ");
		printf("chmod ");
		printf("basename ");
		printf("yes ");
		printf("errno ");
		printf("\n");
	}
}
