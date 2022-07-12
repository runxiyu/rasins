/*	ls - list files and directories in the given path
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *	Copyright (C) 2022 Leah Rowe
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
 *	along with this program. If not, see <https://www.gnu.org/licenses/>.
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

char param[256];
int getopt(int argc, char *const argv[], const char *optstring);

void printUsage(char *params) {
	printf("Ferass' Base System.\n\n"
	"Usage: "
	"ls [-%s] [DIRECTORY] ...\n\n"
	"Print DIRECTORY's contents to stdout\n\n"
	"\t-a\tInclude names starting with a dot, including '.' and '..'\n"
	"\t-A\tSame as `-a` but don't include '.' and '..'\n"
	"\t-C\tPrint in columns\n"
	"\t-1\tPrint in lines\n"
	"\t-R\tRecursively list directories\n"
	"\t-i\tFor each file, write its serial number\n"
	"\t-m\tList names followed by a comma and space character\n"
	"\t-l\tDo not follow symbolic links named as operands and "
	"write in long format (unfinished)\n"
	"\t-p\tShow '/' after each name if that name is a directory\n"
	"\t-g\tEnable the -l option but don't print the file owner's name\n"
	"\t-n\tEnable the -l option but print the file owner and group's numeric "
	"UID and GID instead of their name\n"
	"\t-o\tEnable the -l option but don't print the file group's name\n", params);
}

int ls(char *path) {
	int file, dotname, cwdname, prevdir, dot;
	DIR *directory, *subdirectory;
	struct stat file_status;
	struct dirent *dirtree;
	char *name, *file_moddate;
	char file_modes[] = "----------";

	directory = opendir(path);

	if (directory == NULL) {
		file = open(path, O_RDONLY);
		if (file == -1) return errno;
		printf("%s\n", path);
		close(file);
		return errno;
	}

	if (param['R'])
		printf("%s:\n", path);

	while ((dirtree = readdir(directory)) != NULL) {
		name = dirtree->d_name;

		cwdname = strcmp(name, ".") ? 0 : 1;
		prevdir = strcmp(name, "..") ? 0 : 1;
		dotname = (name[0]=='.' && !cwdname && !prevdir) ? 1 : 0;
		dot = dotname | prevdir | cwdname;

		if (dot && !param['a'] && !param['A']) continue;
		if ((cwdname || prevdir) && param['A']) continue;
		
		if (param['i']) printf("%lu ", dirtree->d_ino);
		if (param['l']) {
			char *fullpath = malloc(strlen(path) + strlen(name) + 2);
			if (fullpath) {
				strcpy(fullpath, path);
				if (path[strlen(path) - 1] != '/') strcat(fullpath, "/");
				strcat(fullpath, name);
			}
			stat(fullpath, &file_status);
			                     /* File modes */
			/* File type */
			{
				if (S_ISBLK(file_status.st_mode))       file_modes[0] = 'b';
				else if (S_ISCHR(file_status.st_mode))  file_modes[0] = 'c';
				else if (S_ISDIR(file_status.st_mode))  file_modes[0] = 'd';
				else if (S_ISFIFO(file_status.st_mode)) file_modes[0] = 'p';
				else if (S_ISREG(file_status.st_mode))  file_modes[0] = '-';
				else if (S_ISLNK(file_status.st_mode))  file_modes[0] = 'l';
				else                                    file_modes[0] = 's';
			}
			/* User */
			{
				if (file_status.st_mode & S_IRUSR) file_modes[1] = 'r';
				if (file_status.st_mode & S_IWUSR) file_modes[2] = 'w';
				if (file_status.st_mode & S_IXUSR) file_modes[3] = 'x';
			}
			/* Group */
			{
				if (file_status.st_mode & S_IRGRP) file_modes[4] = 'r';
				if (file_status.st_mode & S_IWGRP) file_modes[5] = 'w';
				if (file_status.st_mode & S_IXGRP) file_modes[6] = 'x';
			}
			/* Others */
			{
				if (file_status.st_mode & S_IROTH) file_modes[7] = 'r';
				if (file_status.st_mode & S_IWOTH) file_modes[8] = 'w';
				if (file_status.st_mode & S_IXOTH) file_modes[9] = 'x';
			}
			printf("%s ", file_modes);
			                  /* Number of links */
			printf("%lu ", file_status.st_nlink);
			                   /* Owner name/uid */
			if (!param['g']) 
			/* This recursiveness is needed for whatever reason, 
			 * else it doesn't work... 
			 */
				if (!param['n'])
					printf("%s ", getpwuid(file_status.st_uid)->pw_name);
			if (param['n'])                 printf("%u ", file_status.st_uid);
			                  /* Group name/gid */
			if (!param['o'])
				if (!param['n']) printf("%s ", getgrgid(file_status.st_gid)->gr_name);
			if (param['n']) printf("%u ", file_status.st_gid);
			                   /* Size of file */
			printf("%lu ", file_status.st_size);
			                   /* Date and time */
			/* This code is unreliable because sometimes it segfaults ls, 
			 * that's why that code is commented. Patches welcome.
			 */
			// strftime(file_moddate, 50, "%b %e %H:%M", 
			//		localtime(&file_status.st_mtime));
			// /* It should be st_mtim right? */
			// file_moddate[strlen(file_moddate) - 1] = 0; /* Remove newline */
			// printf("%s ", file_moddate ? file_moddate : "?????????");
			printf("??? ?? ??:?? ");
			free(fullpath);
		}
		printf("%s", name);
		if (param['p']) {
			char *fullpath = malloc(strlen(path) + strlen(name) + 2);
			if (fullpath) {
				strcpy(fullpath, path);
				if (path[strlen(path) - 1] != '/') strcat(fullpath, "/");
				strcat(fullpath, name);
			}
			stat(fullpath, &file_status);
			if (S_ISDIR(file_status.st_mode)) printf("/");
			free(fullpath);
		}
		if (param['C'])
			printf("  "); /* TODO: Calculate based on the terminal's size */
		else if (param['1'])
			printf("\n");
		else if (param['m'])
			printf(", ");
	}
	closedir(directory);

	/* Recursively list all subdirectories */
	if (param['R']) {
		int status;
		directory = opendir(path);
		while ((dirtree = readdir(directory)) != NULL) {
			name = dirtree->d_name;

			cwdname = strcmp(name, ".") ? 0 : 1;
			prevdir = strcmp(name, "..") ? 0 : 1;
			dotname = (name[0]=='.' && !cwdname && !prevdir) ? 1 : 0;
			dot = strcmp(name, "./") ? 0 : 1;
			dot |= dotname | prevdir | cwdname;
			if (dot) continue;

			int offset = path[strlen(path)-1] == '/' ? 0 : 1;
			char* subpath = malloc(
				strlen(path)+strlen(name)+offset);

			if (subpath == NULL) {
				free(subpath);
				closedir(directory);
				printf("ls: Out of memory\n");
				return errno;
			}

			memcpy(subpath, path, strlen(path));
			if (offset) subpath[strlen(path)] = '/';
			memcpy(subpath+strlen(path)+offset, name, strlen(name));

			subdirectory = opendir(subpath);
			if (subdirectory == NULL) {
				free(subpath);
				closedir(subdirectory);
				continue;
			}
			closedir(subdirectory);

			printf("\n");
			if(!param['1']) printf("\n");

			status |= ls(subpath);
			free(subpath);
		}
		closedir(directory);
		return status;
	}

	return errno;
}

int main(int argc, char *argv[]) {
	int status = 0;
	int success = 0;
	int argument, i;
	char* params = "aACR1imlpgno";

	for(i=0; i<256; i++) {
		param[i]=0;
	}

	while ((argument = getopt(argc, argv, params)) != -1) {
		if (argument == '?') {
			printUsage(params);
			return 1;
		}
		param[argument] = argument;

		if (argument=='C') {
			param['1'] = 0;
			param['m'] = 0;
		}
		else if (argument=='1' || argument=='g' || argument=='n') {
			param['m'] = 0;
			param['C'] = 0;
		}
		else if (argument=='m') {
			param['1'] = 0;
			param['C'] = 0;
		}
		if (argument=='o' || argument=='n' || argument=='g') {
			param['l'] = 'l';
		}
	}
	if (status) {
		if(!param['1']) printf("\n");
		return status;
	}

	if (!param['C'] && !param['m'] && !param['1'])
		param['1'] = '1';

	if (param['l'] || param['g']) {
		param['m'] = 0;
		param['C'] = 0;
		param['1'] = '1';
	}

	for (i = 1; i < argc; i++) {
		if ((success |= (argv[i][0] != '-' ? 1 : 0))) {
			if (!strcmp(argv[i],".")) status |= ls("./");
			else status |= ls(argv[i]);
		}
	}

	i = success ? status : ls("./");
	if(!param['1'])
		printf("\n");

	return i;
}
