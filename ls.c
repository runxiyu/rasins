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
#include <stdlib.h>

char param[256];
int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: "
	"ls [-aAC1R] [DIRECTORY] ...\n\n"
	"Print DIRECTORY's contents to stdout\n\n"
	"\t-a\tInclude names starting with a dot, including '.' and '..'\n"
	"\t-A\tSame as `-a` but don't include '.' and '..'\n"
	"\t-C\tPrint in columns\n"
	"\t-1\tPrint in lines\n"
	"\t-R\tRecursively list directories\n");
}

int ls(char *path) {
	int status = 0;
	int file, dotname, cwdname, prevdir, dot;
	DIR *directory, *subdirectory;
	struct dirent *dirtree;
	char* name;

	directory = opendir(path);

	if (directory == NULL) {
		file = open(path, O_RDONLY);
		if (file == -1) {
			printf("ls: %s: No such file or directory\n", path);
			return 1;
		}
		printf("%s\n", path);
		close(file);
		return 0;
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

		if (param['C'])
			printf("%s ", name);
		else if (param['1'])
			printf("%s\n", name);
	}
	closedir(directory);

	/* Recursively list all subdirectories */
	if (param['R']) {
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
				exit(1);
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
			if(!param['l'] && !param['1']) printf("\n");

			status |= ls(subpath);
			free(subpath);
		}
		closedir(directory);
		return status;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	int status = 0;
	int success = 0;
	int argument, i;
	char* params = "haACR1";
	char unsupported[256];

	for(i=0; i<256; i++) {
		param[i]=0;
		unsupported[i]=1;
	}
	for(i=0; (size_t)i<strlen(params); i++)
		unsupported[(int)params[i]] = 0;

	setvbuf(stdout, NULL, _IONBF, 0);

	while ((argument = getopt(argc, argv, params)) != -1) {
		if(unsupported[argument]) status = 1;
		if (argument == 'h') {
			printUsage();
			return 0;
		}
		param[argument] = argument;

		if (argument=='C') {
			param['l'] = 0;
			param['1'] = 0;
		} else if (argument=='l' || argument=='1')
			param['C'] = 0;
	}
	if (status) {
		if(!param['l'] && !param['1']) printf("\n");
		return 1;
	}

	if (!param['C'] && !param['l'] && !param['1'])
		param['C'] = 'C';

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
