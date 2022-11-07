/*	vi/ex - visual/text editor
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
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

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
		char buffer[4096], struct cursor_pos cposition, long int offset_position, 
		FILE *filstr);
long int _vi_go_up(unsigned int lines, unsigned int columns, 
		char buffer[4096], FILE *filstr, long int offset_position);
long int _vi_go_down(unsigned int lines, unsigned int columns, 
		char buffer[4096], FILE *filstr, long int offset_position);
void _vi_printUsage();

int _vi_main(int argc, char *argv[]) {
	int argument, offset;
	char cmd;
	FILE *filstr;
	char buffer[4096];
	struct sigaction signal_action;
	struct termios oldattr, newattr;
	struct winsize w;
	struct cursor_pos cposition;
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
				if (cposition.y != 1)
					_vi_set_cursor_pos(cposition.x, (cposition.y = cposition.y - 1));
				else {
					_vi_set_cursor_pos(1, 1);
					offset = _vi_go_up(lines, columns, buffer, filstr, offset);	
					_vi_set_cursor_pos(cposition.x, cposition.y);
				}
				break;
			case 'j': /* down */
				if (cposition.y != lines - 1)
					_vi_set_cursor_pos(cposition.x, (cposition.y = cposition.y + 1));
				else if (!feof(filstr)) {
					_vi_set_cursor_pos(1, 1);
					offset = _vi_go_down(lines, columns, buffer, filstr, offset);	
					_vi_set_cursor_pos(cposition.x, cposition.y);
				}
				break;
			case 'l': /* right */
				if (cposition.x != columns)
					_vi_set_cursor_pos((cposition.x = cposition.x + 1), cposition.y);
				break;
			case 'h': /* left */
				if (cposition.x != 0)
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
		char buffer[4096], struct cursor_pos cposition, 
		long int offset_position, FILE *filstr) {
	int status = 0;
	print_string(ANSI_CLEARALL); /* Clear screen */
	_vi_set_cursor_pos(1, 0);
	if (filstr) {
		if (fgets(buffer, 4096, filstr) != NULL) {
			offset_position = ftell(filstr);
			fputs(buffer, stdout);
		}
		for (unsigned int i = 1; i < (lines - 1); i++) {
			if (fgets(buffer, 4096, filstr) != NULL) {
				fputs(buffer, stdout);
			}
			else {
				fputs("~\n", stdout);
				status = 1; /* EOF */
			}
		}
	} else {
		for (unsigned int i = 1; i < (lines ); i++)
			fputs("~\n", stdout);
		status = 2; /* No file */
	} _vi_set_cursor_pos((cposition.x = 1), (cposition.y = 1));
	return status;
}

long int _vi_go_up(unsigned int lines, unsigned int columns, 
		char buffer[4096], FILE *filstr, long int offset_position) {
	/* Really hacky stuff. TODO: Rewrite. */
	int status = 0, offset_one_line_before;
	print_string(ANSI_CLEARALL); /* Clear screen */
	rewind(filstr);
	if (ftell(filstr) == offset_position) return offset_position;
	for (; fgets(buffer, 4096, filstr) != NULL && 
			(ftell(filstr) != offset_position && 
			 (offset_one_line_before = ftell(filstr)));)
		/* Do nothing. */ ;
	for (unsigned int i = 0; i < (lines - 1); i++) {
		if (fgets(buffer, 4096, filstr) != NULL) {
			fputs(buffer, stdout);
		}
		else {
			fputs("~\n", stdout);
			status = 1; /* EOF */
		}
	}	/* Hacky hack */
	_vi_set_cursor_pos(1, lines);
	print_string(ANSI_CLEARLINE);
	return offset_one_line_before;
}

long int _vi_go_down(unsigned int lines, unsigned int columns, 
		char buffer[4096], FILE *filstr, long int offset_position) {
	int status = 0;
	print_string(ANSI_CLEARALL); /* Clear screen */
	fseek(filstr, offset_position, SEEK_SET);
	if (fgets(buffer, 4096, filstr) != NULL)
		offset_position = ftell(filstr);

	for (unsigned int i = 0; i < (lines); i++) {
		if (fgets(buffer, 4096, filstr) != NULL) {
			fputs(buffer, stdout);
		}
		else {
			fputs("~\n", stdout);
			status = 1; /* EOF */
		}
	}
	//fposition.start = ftell(filstr);
	//fposition_start_backup = ftell(filstr);
	//if (fgets(buffer, 4096, filstr) != NULL)
	//	fposition.end = ftell(filstr);
	/* Hacky hack */
	_vi_set_cursor_pos(1, lines);
	print_string(ANSI_CLEARLINE);
	return offset_position;
}

int _vi_set_cursor_pos(unsigned int x, unsigned int y) {
	return printf("\033[%u;%uH", (y), (x));
}

void _vi_printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: vi [filename]\n\n"
	"Visual editor.\n\n", COMPILETIME);
}

/************ main() ************/
int main(int argc, char *argv[]) {
	if (!strcmp(basename(argv[0]), "ex")) return _ex_main(argc, argv);
	else /* Default to vi */              return _vi_main(argc, argv);
	return 0; /* Never reached. */
}
