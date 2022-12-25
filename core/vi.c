/*	vi/ex - visual/text editor
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
#include <time.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <libgen.h>

/*** ANSI VT100 escape codes ***/
/*           Colors            */
#define ANSI_WHITEBG "\33[38;5;0;48;5;255m"
#define ANSI_RESET   "\33[m"
/*     Other escape codes      */
#define ANSI_CLEARLINE "\33[2K\r"
#define ANSI_CLEARALL  "\e[1;1H\e[2J"

/********** Common - used by both vi and ex **********/
int print_string(char *string);

int print_string(char *string) {
	return write(STDOUT_FILENO, string, strlen(string));
}

/********************** ex mode **********************/
int _ex_main(int argc, char *argv[]);

int _ex_main(int argc, char *argv[]) {
	print_string("<Not implemented>\n");
	return 0; /* Not implemented yet. */
}

/********************** vi mode **********************/
struct cursor_pos {
	/* Neat way to keep track of the cursor's position. */
	unsigned int x;
	unsigned int y;
};

int  _vi_main(int argc, char *argv[]);
int  _vi_set_cursor_pos(unsigned int x, unsigned int y);
int  _vi_init(unsigned int lines, unsigned int columns, 
		char buffer[BUFSIZ], struct cursor_pos cposition, long int offset_position, 
		FILE *filstr);
void _vi_printUsage();
int _vi_print_buffer_line(char s[BUFSIZ], unsigned int numlines);

int _vi_main(int argc, char *argv[]) {
	int argument, offset;
	char cmd;
	FILE *filstr;
	char buffer[BUFSIZ];
	struct sigaction signal_action;
	struct termios oldattr, newattr;
	struct winsize w;
	struct cursor_pos cposition, fposition;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	unsigned int lines   = w.ws_row - 1;
	unsigned int columns = w.ws_col - 1;

	while ((argument = getopt(argc, argv, "")) != -1) {
		if (argument == '?') {
			_vi_printUsage();
			return 1;
		}
	}
	argc -= optind;
	argv += optind;

	signal_action.sa_handler = SIG_IGN;
	sigemptyset(&signal_action.sa_mask);
	sigaction(SIGINT, &signal_action, NULL);
	setvbuf(stdout, NULL, _IONBF, 0);
	/* Initialise vi */
	if (argv[0]) {
		filstr = fopen(argv[0], "r+");
		if (errno) {
			if (errno != ENOENT)
				return errno;
		}
	} _vi_init(lines, columns, buffer, cposition, offset, filstr);	
	for (;;) {
		/* Get a character */
		tcgetattr(0, &oldattr); /* Get previous terminal parameters */
		newattr = oldattr;
		newattr.c_lflag &= ~( ICANON | ECHO ); /* Disable ECHO and ICANON */
		tcsetattr(0, TCSANOW, &newattr); /* Set net parameters */
		cmd = getchar();
		switch (cmd) {
			/*********************** Moving the cursor ***********************/
			case 'k': /* up */
				if (fposition.y > 0) fposition.y--;
				else break;
				if (cposition.y != 1)
					_vi_set_cursor_pos(cposition.x, (cposition.y = cposition.y - 1));
				else if (fposition.y == 0) {
					_vi_set_cursor_pos(1, 1);
					print_string(ANSI_CLEARALL); /* Clear screen */
					fposition.y--; /* Say, 118 */
					for (unsigned int i = lines - 1 /* 79 */; i > 0; i--) {
						_vi_print_buffer_line(buffer, fposition.y - i); /* 120 - 78 */
					}
					_vi_set_cursor_pos(cposition.x, cposition.y);
				}
				break;
			case 'j': /* down */
				if (cposition.y != (lines - 1) && fposition.y++)
					_vi_set_cursor_pos(cposition.x, (cposition.y = cposition.y + 1));
				else if (cposition.y == lines - 1) {
					_vi_set_cursor_pos(1, 1);
					print_string(ANSI_CLEARALL); /* Clear screen */
					fposition.y++; /* Say, 120 */
					for (unsigned int i = lines - 1 /* 79 */; i > 0; i--) {
						_vi_print_buffer_line(buffer, fposition.y - i); /* 120 - 78 */
					}
					_vi_set_cursor_pos(cposition.x, cposition.y);
				}
				break;
			case 'l': /* right */
				if (cposition.x != columns && fposition.x++)
					_vi_set_cursor_pos((cposition.x = cposition.x + 1), cposition.y);
				break;
			case 'h': /* left */
				if (cposition.x != 1 && fposition.x--)
					_vi_set_cursor_pos((cposition.x = cposition.x - 1), cposition.y);
				break;
			/************************* Command mode: *************************/
			case ':':
				_vi_set_cursor_pos(1, lines);
				print_string(ANSI_CLEARLINE ":");
				tcsetattr(0, TCSANOW, &oldattr); /* Restore old parameters */
				cmd = getchar();
				switch (cmd) { 
					case '\33':
						_vi_set_cursor_pos(1, lines);
						print_string(ANSI_CLEARLINE);
						break;
					case 'q':
						print_string(ANSI_CLEARALL); /* Clear screen */
						_vi_set_cursor_pos(1, 1); /* Reset the cursor position */
						if (filstr) fclose(filstr);
						return 0;
					case '\n':
						break;
					default:
						_vi_set_cursor_pos(1, lines);
						print_string("unknown command");
						break;
				}
				_vi_set_cursor_pos(cposition.x, cposition.y);
		}
		tcsetattr(0, TCSANOW, &oldattr); /* Restore old parameters */
	}
	return 0;
}

int _vi_init(unsigned int lines, unsigned int columns, 
		char buffer[BUFSIZ], struct cursor_pos cposition, 
		long int offset_position, FILE *filstr) {
	int status = 0;
	print_string(ANSI_CLEARALL); /* Clear screen */
	_vi_set_cursor_pos(1, 1);
	if (filstr) {
		fread(buffer, BUFSIZ, 1, filstr);
		//if (fgets(buffer, 4096, filstr) != NULL) {
		//	offset_position = ftell(filstr);
		//	fputs(buffer, stdout);
		//}
		for (unsigned int i = 0; i < lines - 1; i++)
			_vi_print_buffer_line(buffer, i);
	} else {
		for (unsigned int i = 1; i < (lines ); i++)
			fputs("~\n", stdout);
		status = 2; /* No file */
	} _vi_set_cursor_pos((cposition.x = 1), (cposition.y = 1));
	return status;
}

int _vi_set_cursor_pos(unsigned int x, unsigned int y) {
	return printf("\033[%u;%uH", (y), (x));
}

void _vi_printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: vi [filename]\n"
	"Visual editor.\n", VERSION);
}

int _vi_print_buffer_line(char s[BUFSIZ], unsigned int numlines) {
	unsigned int lines_found, chars;
	/* Search for <numlines> - 1 lines and skip them entirely. */
	for (chars = 0, lines_found = 0; 
			s[chars] && lines_found < numlines; s[chars] == '\n' && lines_found++, chars++)
		/* TODO: Use strchr(). */ ;
	/* Print the last line found. */
	for (; s[chars] && s[chars] != '\n'; chars++) putchar((int)s[chars])
		/* TODO: Do not print character-by-character. */ ;
	putchar((int)'\n');
	return 0;
}

/************ main() ************/
int main(int argc, char *argv[]) {
	if (!strcmp(basename(argv[0]), "ex")) return _ex_main(argc, argv);
	else /* Default to vi */              return _vi_main(argc, argv);
	return 0; /* Never reached. */
}
