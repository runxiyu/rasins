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

char param[256];
int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: "
	"ls [DIRECTORY] ...\n\n"
	"Print DIRECTORY's contents to stdout\n\n"
	"\t-a\tInclude names starting with a dot, including '.' and '..'\n"
	"\t-A\tSame as `-a` but don't include '.' and '..'\n"
	"\t-C\tPrint in columns\n");
}

int ls(char *path) {
	int file, column;
	DIR *directory;
	struct dirent *dirtree;

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

	while ((dirtree = readdir(directory)) != NULL) {
		if (dirtree->d_name[0] != '.' && 
				!param['a'] && !param['A']) { 
			printf("%s", dirtree->d_name);
			if (!param['C']) printf("\n");
		}
		if (param['a']) {
			printf("%s", dirtree->d_name);
		} else if (param['A'] && 
				strcmp(dirtree->d_name, ".") &&
				strcmp(dirtree->d_name, "..")) {
			printf("%s", dirtree->d_name);
		}
		if (!param['C'] && (param['A'] || param['a'])) {
			printf("\n");
		} else if (param[1] == 'C' && !param['a'] && !param['A'] && 
				dirtree->d_name[0] != '.') {
			if (column++ > 5) printf("\n");
			else printf("\t\t");
		} else if (param['C'] && (param['a'] || (param['A'] &&
					strcmp(dirtree->d_name, "." )
					&& strcmp(dirtree->d_name, "..")))) {
			if (column > 5) {
				printf("\n");
				column = 0;
			} else {
				printf("\t\t");
				column++;
			}
		}
	}
	printf("\n");

	closedir(directory);
	return 0;
}

int main(int argc, char *argv[]) {
	int status = 0;
	int success = 0;
	int argument, i;
	char* params = "haAC";
	char supported[256];

	for(i=0; i<256; i++) {
		param[i]=0;
		supported[i]=0;
	}
	for(i=0; i<3; i++) supported[(int)params[i]] = 1;

	setvbuf(stdout, NULL, _IONBF, 0);

	while (1) {
		argument = getopt(argc, argv, params);
		if (argument == -1) break;
		if(!supported[argument]) return 1;
		if (argument == 'h') {
			printUsage();
			return 0;
		}
		param[argument] = argument;	
	}

	for (i = 1; i < argc; i++)
		if ((success |= (argv[i][0] != '-' ? 1 : 0)))
			status |= ls(argv[i]);

	return success ? status : ls(".");
}
