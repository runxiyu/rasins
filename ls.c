/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 * Copyright (C) 2022 Leah Rowe <leah@libreboot.org>
 */
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/ioctl.h>

#define REQ_PRINT_USAGE		/* Require print_usage() from common.h */
#define REQ_ERRPRINT		/* Require errprint() from common.h */
#define DESCRIPTION "Print <directory>'s contents to standard output.\
	If no directory is specified, print the current directory's contents."
#define OPERANDS    "[-1aACimlpgno] [directory]"
#include "common.h"

char *argv0;
char param[256];
int ls(char *path);
void printUsage(char *params);

int main(int argc, char *argv[])
{
	int status = 0;
	int success = 0;
	int argument, i;
	argv0 = strdup(argv[0]);
	for (i = 0; i < 256; i++) {
		param[i] = 0;
	}

	while ((argument = getopt(argc, argv, OPERANDS)) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		param[argument] = argument;

		if (argument == 'C') {
			param['1'] = 0;
			param['m'] = 0;
		} else if (argument == '1' || argument == 'g'
			   || argument == 'n') {
			param['m'] = 0;
			param['C'] = 0;
		} else if (argument == 'm') {
			param['1'] = 0;
			param['C'] = 0;
		}
		if (argument == 'o' || argument == 'n' || argument == 'g') {
			param['l'] = 'l';
		}
	}
	argc -= optind;
	argv += optind;
	if (status) {
		if (!param['1'])
			printf("\n");
		return status;
	}

	if (!param['C'] && !param['m'] && !param['1'])
		param['1'] = '1';

	if (param['l'] || param['g']) {
		param['m'] = 0;
		param['C'] = 0;
		param['1'] = '1';
	}

	for (i = 0; i < argc; i++) {
		if ((success |= (argv[i][0] != '-' ? 1 : 0))) {
			if (!strcmp(argv[i], "."))
				status |= ls("./");
			else
				status |= ls(argv[i]);
		}
	}

	i = success ? status : ls("./");
	if (!param['1'])
		printf("\n");

	return i;
}

int ls(char *path)
{
	int file, dotname, cwdname, prevdir, dot;
	long unsigned int cols_used;
	DIR *directory;
	struct stat file_status;
	struct dirent *dirtree;
	struct winsize columns;
	char *name, file_moddate[256];
	char file_modes[] = "----------";
	directory = opendir(path);

	if (param['C']) {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &columns);
		cols_used = 0;
	}

	if (directory == NULL) {
		file = open(path, O_RDONLY);
		if (file == -1)
			return errprint(argv0, path, errno);
		printf("%s\n", path);
		if (close(file) == -1)
			return errprint(argv0, path, errno);
	}

	while ((dirtree = readdir(directory)) != NULL) {
		name = dirtree->d_name;

		cwdname = strcmp(name, ".") ? 0 : 1;
		prevdir = strcmp(name, "..") ? 0 : 1;
		dotname = (name[0] == '.' && !cwdname && !prevdir) ? 1 : 0;
		dot = dotname | prevdir | cwdname;

		if (dot && !param['a'] && !param['A'])
			continue;
		if ((cwdname || prevdir) && param['A'])
			continue;

		if (param['i'])
			printf("%lu ", dirtree->d_ino);
		if (param['l']) {
			char *fullpath =
			    malloc(strlen(path) + strlen(name) + 2);
			if (fullpath) {
				strcpy(fullpath, path);
				if (path[strlen(path) - 1] != '/')
					strcat(fullpath, "/");
				strcat(fullpath, name);
			}
			lstat(fullpath, &file_status);
			/* File modes */
			/* File type */
			{
				if (S_ISBLK(file_status.st_mode))
					file_modes[0] = 'b';
				else if (S_ISCHR(file_status.st_mode))
					file_modes[0] = 'c';
				else if (S_ISDIR(file_status.st_mode))
					file_modes[0] = 'd';
				else if (S_ISFIFO(file_status.st_mode))
					file_modes[0] = 'p';
				else if (S_ISREG(file_status.st_mode))
					file_modes[0] = '-';
				else if (S_ISLNK(file_status.st_mode))
					file_modes[0] = 'l';
				else
					file_modes[0] = 's';
			}
			/* User */
			{
				if (file_status.st_mode & S_IRUSR)
					file_modes[1] = 'r';
				if (file_status.st_mode & S_IWUSR)
					file_modes[2] = 'w';
				if (file_status.st_mode & S_IXUSR)
					file_modes[3] = 'x';
			}
			/* Group */
			{
				if (file_status.st_mode & S_IRGRP)
					file_modes[4] = 'r';
				if (file_status.st_mode & S_IWGRP)
					file_modes[5] = 'w';
				if (file_status.st_mode & S_IXGRP)
					file_modes[6] = 'x';
			}
			/* Others */
			{
				if (file_status.st_mode & S_IROTH)
					file_modes[7] = 'r';
				if (file_status.st_mode & S_IWOTH)
					file_modes[8] = 'w';
				if (file_status.st_mode & S_IXOTH)
					file_modes[9] = 'x';
			}
			printf("%s ", file_modes);
			/* Number of links */
			printf("%lu ", (long unsigned int)file_status.st_nlink);
			/* Owner name/uid */
			if (!param['g'])
				/* This recursiveness is needed for whatever reason, 
				 * else it doesn't work... 
				 */
				if (!param['n'])
					printf("%s ",
					       getpwuid(file_status.st_uid)->
					       pw_name);
			if (param['n'])
				printf("%u ", file_status.st_uid);
			/* Group name/gid */
			if (!param['o'])
				if (!param['n'])
					printf("%s ",
					       getgrgid(file_status.st_gid)->
					       gr_name);
			if (param['n'])
				printf("%u ", file_status.st_gid);
			/* Size of file */
			printf("%lu ", file_status.st_size);
			/* Date and time */
			int strftime_status =
			    strftime(file_moddate, sizeof(file_moddate),
				     "%b %e %H:%MM",
				     localtime(&file_status.st_mtime));
			/* It should be st_mtim right? */
			file_moddate[strlen(file_moddate) - 1] = 0;	/* Remove newline */
			printf("%s ",
			       strftime_status ? file_moddate :
			       "<strftime() returned 0>");
			free(fullpath);
		}
		printf("%s", name);
		if (param['p']) {
			char *fullpath =
			    malloc(strlen(path) + strlen(name) + 2);
			if (fullpath) {
				strcpy(fullpath, path);
				if (path[strlen(path) - 1] != '/')
					strcat(fullpath, "/");
				strcat(fullpath, name);
			}
			stat(fullpath, &file_status);
			if (S_ISDIR(file_status.st_mode))
				printf("/");
			free(fullpath);
		}
		if (param['C']) {
			if (cols_used <
			    (long unsigned int)((columns.ws_col) / 12)) {
				for (long unsigned int i = strlen(name); i < 11;
				     i++)
					printf(" ");
				cols_used++;
			}
			if (cols_used ==
			    (long unsigned int)((columns.ws_col) / 12)) {
				printf("\n");
				cols_used = 0;
			}
		} else if (param['1'])
			printf("\n");
		else if (param['m'])
			printf(", ");
	}
	closedir(directory);

	return errprint(argv0, path, errno);
}
