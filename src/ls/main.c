/*	ls - list files and directories in the given path
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
 *	along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include <unistd.h> /* Unix standard library */
#include <string.h> /* Strings */
#include <dirent.h> /* Manipulating directories */
#include <fcntl.h>  /* Manipulating files */

/* For `getopt()` */
int getopt(int argc, char *const argv[], const char *optstring);

/* Define a `print()` function */
ssize_t print(char *string) { return write(STDOUT_FILENO, string, strlen(string)); }

/* `ls()` function for listing files and directories. */
int ls(char *dirname, char params[3]) {
	DIR *directory;
	directory = opendir(dirname); /* Open the directory */
	struct dirent *dirtree;
	if (directory != NULL) { /* Did the directory open successfully? */
		while ((dirtree = readdir(directory)) != NULL) {
			/* Column counter for `-C` */
			int column;
			/* Yes, `print()` every file/directory */
			if (dirtree->d_name[0] != '.' && 
					params[0] != 'a' && params[0] != 'A') { 
				/* Unless they start with a dot */
				print(dirtree->d_name);
				if (params[1] != 'C')
					print("\n"); /* Print a newline if `-C` isn't used */
			}
			if (params[0] == 'a') {
				/* Print names starting with a dot if the `-a` option is used */
				print(dirtree->d_name);
				if (params[1] != 'C')
					print("\n"); /* Print a newline if `-C` isn't used */
			}
			if (params[0] == 'A' && 
					strcmp(dirtree->d_name, ".") && strcmp(dirtree->d_name, "..")) {
				/* Print names starting with a dot 
				 * (unless it's '.' or '..' if they exist) 
				 * if the `-A` option is used 
				 */
				print(dirtree->d_name);
				if (params[1] != 'C')
					print("\n"); /* Print a newline if `-C` isn't used */
			}
			if (params[1] == 'C' && 
					params[0] != 'a' && params[0] != 'A' && 
					dirtree->d_name[0] != '.') {
				/* Print in columns: unless the file starts with a dot and 
				 * `-a`/`-A` are unspecified, print tab characters until 
				 * the 4th column 
				 */
				if (column > 5)
					print("\n");
				else
					print("\t\t");
				column++;
			}
			else if (params[1] == 'C' && 
					(params[0] == 'a' || (params[0] == 'A' && strcmp(dirtree->d_name, "." )
										  && strcmp(dirtree->d_name, "..")))) {
				/* Print in columns: if `-a` or `-A` are specified, print
				 * tab characters for files starting with a dot (more info 
				 * in the 'a' or 'A' `if` block) 
				 */
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
		print("\n"); /* Print newline in case it hasn't been printed. */
	}
	else { /* It didn't open. Maybe it's a file? */
		int file;
		file = open(dirname, O_RDONLY);
		if (file == -1) { /* Nope, it doesn't exist. Gracefully exit. */
			print("ls: ");
			print(dirname);
			print(": No such file or directory\n");
			return 1;
		}
		print(dirname); /* The file exists, print its name */
		print("\n");
		close(file); /* Close file */
	}
	closedir(directory); /* Close directory */
	return 0;
}

int main(int argc, char *argv[]) {
	/* Check for arguments */
	if (argc > 1) {
		int arguments;
		char params[6];
		while ((arguments = getopt(argc, argv, "haAC")) != -1) {
			switch (arguments) {
				case 'h': /* Print help message */
					print("Ferass' Base System.\n\n"
							"Usage: ");
					print(argv[0]);
					print(" [DIRECTORY] ...\n\n"
							"Print DIRECTORY's contents to stdout\n\n");
					print("	-a	Include names starting with a dot, including '.' and '..'\n");
					print("	-A	Same as `-a` but don't include '.' and '..'\n");
					print("	-C	Print in columns\n");
					return 0;
					break;
				case 'a':
					params[0] = 'a';
					break;
				case 'A':
					params[0] = 'A';
					break;
				case 'C':
					params[1] = 'C';
					break;
			}
		}
		for (int i = 1; i < argc; i++) {
			/* List every file/directory the user wants to list */
			if (argv[i][0] != '-') { /* Discard options starting with '-' */
				ls(argv[i], params);
			}
			if (argc == 2 && argv[i][0] == '-') {
				ls(".", params);
			}
		}
	}
	else { /* No other arguments. */
		char params[3];
		ls(".", params);
	}
	return 0;
}
