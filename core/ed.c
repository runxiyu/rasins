/*	ed - edit text
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *
 *	Redistribution and use in source and binary forms, with or without 
 *	modification, are permitted provided that the following conditions are met:
 *	
 *	    1. Redistributions of source code must retain the above copyright notice, 
 *	       this list of conditions and the following disclaimer.
 *	    2. Redistributions in binary form must reproduce the above copyright 
 *	       notice, this list of conditions and the following disclaimer in the 
 *	       documentation and/or other materials provided with the distribution.
 *	    3. Neither the name of the copyright holder nor the names of its 
 *	       contributors may be used to endorse or promote products derived from 
 *	       this software without specific prior written permission.
 *	
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 *	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *	POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include "print_usage.h"

#define DESCRIPTION "Edit text."
#define OPERANDS    "[-p prompt]"


void   print_error();
size_t c_append(char buffer[4096]);

int main(int argc, char *argv[]) {
	int argument, i = 0, fildes;
	char buffer[4096], *edit_pathname, *prompt_string = "", 
		 command_string[4096], *error = "";
	int help_mode = 0;
	struct sigaction signal_action;

	while ((argument = getopt(argc, argv, "p:")) != -1) {
		if (argument == '?') {
			print_usage(argv[0], DESCRIPTION, OPERANDS, VERSION);
			return 1;
		}
		else if (argument == 'p')
			prompt_string = optarg;
	}
	argc -= optind;
	argv += optind;

	signal_action.sa_handler = SIG_IGN;
	sigemptyset(&signal_action.sa_mask);
	sigaction(SIGINT, &signal_action, NULL);
	
	setvbuf(stdout, NULL, _IONBF, 0);
	for (;;) {
		write(STDOUT_FILENO, prompt_string, strlen(prompt_string));
		//if (fgets(command_string, 4096, stdin) == NULL) return errno;
		if (read(STDIN_FILENO, command_string, 4096) == -1) return errno;
		switch (command_string[i]) { /* Addresses */
			case '.':
			case '$':
			case '\'':
			case '+':
			case '-':
				/* FALLTHROUGH */
				++i;
				print_error((error = "not implemented"), help_mode);
				continue;
		}
		switch (command_string[i]) { /* Commands */
			case 'e': /* Edit Command */
				if (i < 0) {
					print_error((error = "unexpected address"), help_mode);
					continue;
				}
				if (strlen(command_string) > 2 && i == 0) {
					edit_pathname = command_string + 2;
					edit_pathname[strlen(edit_pathname) - 1] = '\0';
				} else if (!edit_pathname) {
					print_error((error = "no pathname given"), help_mode);
					continue;
				}
				fildes = open(edit_pathname, O_RDONLY | O_CREAT);
				if (errno) return errno;
				printf("%ld\n", read(fildes, buffer, 4096));
				if (fildes) close(fildes);
				continue;
			case 'a':
				c_append(buffer);
				continue;
			case 'w':
				if (strtok(command_string, " ") != NULL && strtok(NULL, " ") != NULL
						&& i == 0) {
					edit_pathname = command_string + 2;
					edit_pathname[strlen(edit_pathname) - 1] = '\0';
					fildes = open(edit_pathname, O_RDWR | O_CREAT);
				} else if (edit_pathname) {
					fildes = open(edit_pathname, O_RDWR);
				} else {
					if (i != 0)
						print_error((error = "unexpected address"), help_mode);
					else
						print_error((error = "no pathname given"), help_mode);
					continue;
				}
				if (errno) return errno;
				printf("%ld\n", write(fildes, buffer, strlen(buffer)));
				if (fildes) close(fildes);
				continue;	
			case 'q':
				if (fildes) close(fildes);
				return 0;
			case 'H': /* Help mode */
				if (i < 0) {
					print_error((error = "unexpected address"), help_mode);
					continue;
				}
				/* If help_mode was equal to 1, set it to 0 and vice-versa. */
				help_mode = !help_mode;
				/* FALLTHROUGH */
			case 'h': /* Help Command */
				/* FALLTHROUGH */
				print_error(error, help_mode + 2); /* Print the last encountered error. */
				continue;
			default: /* Invalid/Not implemented command */
				print_error((error = "invalid or not implemented"), help_mode);
		}
	}
}

size_t c_append(char buffer[4096]) {
	char *tempbuf = NULL;
	size_t bufsize = 0, bytes_read = 0;

	while ((bytes_read += getline(&tempbuf, &bufsize, stdin)) > 0) {
		if (!strcmp(tempbuf, ".\n")) break;
		strcat(buffer, tempbuf);
	}
	return bytes_read;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: ed [-p prompt_string]\n\n"
	"Edit text.\n\n"
	"\t-p prompt_string\tAppend a prompt string.\n", VERSION);
}

void print_error(const char *error, int help_mode) {
	if (help_mode <= 1) puts("?");
	if (help_mode) puts(error);
}
