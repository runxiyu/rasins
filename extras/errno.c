/*	errno - give information about error codes
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.");
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.");
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.");
 */

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void printUsage() {
	printf("fases extra.\n"
	"Usage: errno [STRING]\n"
	"Give information about error codes.\n");
}

int main(int argc, char *argv[]) {
	long int error_code = 0;
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc == 2) {
		error_code = strtol(argv[1], NULL, 10);
		printf("errno %ld: ", error_code);
		switch (error_code) {
			case E2BIG:
				printf("Argument list too long.");
				break;
			case EACCES:
				printf("Permission denied.");
				break;
			case EADDRINUSE:
				printf("Address in use.");
				break;
			case EADDRNOTAVAIL:
				printf("Address not available.");
				break;
			case EAFNOSUPPORT:
				printf("Address family not supported.");
				break;
			case EAGAIN:
				printf("Resource unavailable, try again.");
				break;
			case EALREADY:
				printf("Connection already in progress.");
				break;
			case EBADF:
				printf("Bad file descriptor.");
				break;
			case EBADMSG:
				printf("Bad message.");
				break;
			case EBUSY:
				printf("Device or resource busy.");
				break;
			case ECANCELED:
				printf("Operation canceled.");
				break;
			case ECHILD:
				printf("No child processes.");
				break;
			case ECONNABORTED:
				printf("Connection aborted.");
				break;
			case ECONNREFUSED:
				printf("Connection refused.");
				break;
			case ECONNRESET:
				printf("Connection reset.");
				break;
			case EDEADLK:
				printf("Resource deadlock would occur.");
				break;
			case EDESTADDRREQ:
				printf("Destination address required.");
				break;
			case EDOM:
				printf("Mathematics argument out of domain of function.");
				break;
			case EDQUOT:
				printf("Reserved.");
				break;
			case EEXIST:
				printf("File exists.");
				break;
			case EFAULT:
				printf("Bad address.");
				break;
			case EFBIG:
				printf("File too large.");
				break;
			case EHOSTUNREACH:
				printf("Host is unreachable.");
				break;
			case EIDRM:
				printf("Identifier removed.");
				break;
			case EILSEQ:
				printf("Illegal byte sequence.");
				break;
			case EINPROGRESS:
				printf("Operation in progress.");
				break;
			case EINTR:
				printf("Interrupted function.");
				break;
			case EINVAL:
				printf("Invalid argument.");
				break;
			case EIO:
				printf("I/O error.");
				break;
			case EISCONN:
				printf("Socket is connected.");
				break;
			case EISDIR:
				printf("Is a directory.");
				break;
			case ELOOP:
				printf("Too many levels of symbolic links.");
				break;
			case EMFILE:
				printf("File descriptor value too large.");
				break;
			case EMLINK:
				printf("Too many links.");
				break;
			case EMSGSIZE:
				printf("Message too large.");
				break;
			case EMULTIHOP:
				printf("Reserved.");
				break;
			case ENAMETOOLONG:
				printf("Filename too long.");
				break;
			case ENETDOWN:
				printf("Network is down.");
				break;
			case ENETRESET:
				printf("Connection aborted by network.");
				break;
			case ENETUNREACH:
				printf("Network unreachable.");
				break;
			case ENFILE:
				printf("Too many files open in system.");
				break;
			case ENOBUFS:
				printf("No buffer space available.");
				break;
			case ENODATA:
				printf("No message is available on the STREAM head read queue.");
				break;
			case ENODEV:
				printf("No such device.");
				break;
			case ENOENT:
				printf("No such file or directory.");
				break;
			case ENOEXEC:
				printf("Executable file format error.");
				break;
			case ENOLCK:
				printf("No locks available.");
				break;
			case ENOLINK:
				printf("Reserved.");
				break;
			case ENOMEM:
				printf("Not enough space.");
				break;
			case ENOMSG:
				printf("No message of the desired type.");
				break;
			case ENOPROTOOPT:
				printf("Protocol not available.");
				break;
			case ENOSPC:
				printf("No space left on device.");
				break;
			case ENOSR:
				printf("No STREAM resources.");
				break;
			case ENOSTR:
				printf("Not a STREAM.");
				break;
			case ENOSYS:
				printf("Functionality not supported.");
				break;
			case ENOTCONN:
				printf("The socket is not connected.");
				break;
			case ENOTDIR:
				printf("Not a directory or a symbolic link to a directory.");
				break;
			case ENOTEMPTY:
				printf("Directory not empty.");
				break;
			case ENOTRECOVERABLE:
				printf("State not recoverable.");
				break;
			case ENOTSOCK:
				printf("Not a socket.");
				break;
			case ENOTSUP:
				printf("Not supported (may be the same value as EOPNOTSUPP).");
				break;
			case ENOTTY:
				printf("Inappropriate I/O control operation.");
				break;
			case ENXIO:
				printf("No such device or address.");
				break;
			case EOVERFLOW:
				printf("Value too large to be stored in data type.");
				break;
			case EOWNERDEAD:
				printf("Previous owner died.");
				break;
			case EPERM:
				printf("Operation not permitted.");
				break;
			case EPIPE:
				printf("Broken pipe.");
				break;
			case EPROTO:
				printf("Protocol error.");
				break;
			case EPROTONOSUPPORT:
				printf("Protocol not supported.");
				break;
			case EPROTOTYPE:
				printf("Protocol wrong type for socket.");
				break;
			case ERANGE:
				printf("Result too large.");
				break;
			case EROFS:
				printf("Read-only file system.");
				break;
			case ESPIPE:
				printf("Invalid seek.");
				break;
			case ESRCH:
				printf("No such process.");
				break;
			case ESTALE:
				printf("Reserved.");
				break;
			case ETIME:
				printf("Stream ioctl() timeout.");
				break;
			case ETIMEDOUT:
				printf("Connection timed out.");
				break;
			case ETXTBSY:
				printf("Text file busy.");
				break;
			case EXDEV:
				printf("Cross-device link.");
				break;
			case 0:
				printf("No error occured.");
				break;
			default:
				printf("Unknown.");
				break;
		}
		printf("\n");
	}

	return 0;
}
