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

/*
 *	TODO: return proper error codes (0 and 1 are incorrect)
 *	https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html
 */

#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

int getopt(int argc, char *const argv[], const char *optstring);

ssize_t print(char *string)
	{ return write(STDOUT_FILENO, string, strlen(string)); }

void printUsage() {
	print(
	"Ferass' Base System.\n\n"
	"Usage: "
	"ls [DIRECTORY] ...\n\n"
	"Print DIRECTORY's contents to stdout\n\n"
	"\t-a\tInclude names starting with a dot, including '.' and '..'\n"
	"\t-A\tSame as `-a` but don't include '.' and '..'\n"
	"\t-C\tPrint in columns\n"
	);
}

int ls(char *dirname, char params[3]) {
	int file;
	DIR *directory;
	struct dirent *dirtree;

	directory = opendir(dirname);

	if (directory == NULL) {
		file = open(dirname, O_RDONLY);
		if (file == -1) {
			print("ls: ");
			print(dirname);
			print(": No such file or directory\n");
			return 1;
		}
		print(dirname);
		print("\n");
		close(file);
		return 0;
	}

	while ((dirtree = readdir(directory)) != NULL) {
		int column; /* counter column for -C */
		if (dirtree->d_name[0] != '.' && 
				params[0] != 'a' && params[0] != 'A') { 
			print(dirtree->d_name);
			if (params[1] != 'C')
				print("\n");
		}
		if (params[0] == 'a') {
			print(dirtree->d_name);
		} else if (params[0] == 'A' && 
				strcmp(dirtree->d_name, ".") &&
				strcmp(dirtree->d_name, "..")) {
			print(dirtree->d_name);
		}
		if (params[1] != 'C' && (params[0]=='A' || params[1]=='a')) {
			print("\n");
		} else if (params[1] == 'C' && 
				params[0] != 'a' && params[0] != 'A' && 
				dirtree->d_name[0] != '.') {
			if (column > 5)
				print("\n");
			else
				print("\t\t");
			column++;
		}
		else if (params[1] == 'C' && 
				(params[0] == 'a' ||
					(params[0] == 'A' &&
					strcmp(dirtree->d_name, "." )
					&& strcmp(dirtree->d_name, "..")))) {
			if (column > 5) {
				print("\n");
				column = 0;
			}
			else {
				print("\t\t");
				column++;
			}
		}
	}
	print("\n");

	closedir(directory);
	return 0;
}

int main(int argc, char *argv[]) {
	int status = 0;
	int success = 0;
	int argument;
	char params[6];

	if (argc < 2) {
		char params[3];
		return ls(".", params);
	}

	while ((argument = getopt(argc, argv, "haAC")) != -1) {
		if (argument == 'h') {
			printUsage();
			return 0;
		} else if (argument == 'a' || argument == 'A') {
			params[0] = argument;
		} else if (argument == 'C') {
			params[1] = argument;
		}
	}

	for (int i = 1; i < argc; i++)
		if ((success |= (argv[i][0] != '-' ? 1 : 0)))
			status |= ls(argv[i], params);

	if (!success)
		return ls(".", params);

	return status;
}
