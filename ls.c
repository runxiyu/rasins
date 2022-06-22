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
	int column = 0;
	int file, dotname, cwdname, prevdir, dot;
	DIR *directory;
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

	while ((dirtree = readdir(directory)) != NULL) {
		name = dirtree->d_name;

		cwdname = strcmp(name, ".") ? 0 : 1;
		prevdir = strcmp(name, "..") ? 0 : 1;
		dotname = (name[0]=='.' && !cwdname && !prevdir) ? 1 : 0;
		dot = dotname | prevdir | cwdname;

		if (dot && !param['a'] && !param['A']) continue;
		if ((cwdname || prevdir) && param['A']) continue;

		printf("%s", name);

		if (param['C']) {
			++column;
			if (column == 5) {
				column = 0;
				printf("\n");
			}
			else printf("\t\t");
		}
		else printf("\n");
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
	char unsupported[256];

	for(i=0; i<256; i++) {
		param[i]=0;
		unsupported[i]=1;
	}
	for(i=0; i<3; i++) unsupported[(int)params[i]] = 0;

	setvbuf(stdout, NULL, _IONBF, 0);

	while (1) {
		argument = getopt(argc, argv, params);
		if (argument == -1) break;
		if(unsupported[argument]) status = 1;
		if (argument == 'h') {
			printUsage();
			return 0;
		}
		param[argument] = argument;	
	}
	if (status) return 1;

	for (i = 1; i < argc; i++)
		if ((success |= (argv[i][0] != '-' ? 1 : 0)))
			status |= ls(argv[i]);

	return success ? status : ls(".");
}
