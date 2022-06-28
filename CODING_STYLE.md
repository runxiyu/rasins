# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](README.md)

## Coding Style

The programming language used is ***POSIX C99*** and all code must be written 
in ***POSIX C99***, no extensions are used.

The coding style is as follows:

### General

1. The code shall be as simple to understand as possible, add comments if 
necessary ;

2. For indentation, the code shall use tab characters ;

3. The code shall avoid using GNU-specific functions (as that would make 
the program less portable) ;

4. Each line shall not exceed 79 characters ;

5. Utilities shall only implement POSIX-compliant options, the only 
exception is the `-h` option, which shall print a help text ;

6. Utilities shall only use the **standard C library and POSIX libraries** ;

7. For comments, instead of using `//` (as in `// Comment`), the code shall 
use `/*` and `*/` (as in `/* Comment */`).

8. **Variable names** shall describe the variable's purpose ;

### Blocks

9. In a block, do not use `{` and `}` if there's only one instruction inside ;

	for (int i; i != 3; i++)
		printf("%d\n", i);

10. When using `{` and `}`, `{` shall not be on it's own line ;

	if (i) {
		printf("%d", i);
		i = 3;
	}

11. The block shall only use 1 line if there's only one instruction ran and 
that shall not exceed 79 characters ;

	if (foo[1] == 'a') foo[1] = 'b';

### Functions

12. The function type shall be on the same line as the function name and `{` ;

	int main() {
		printf("Hello World.\n");
	}

13. Function names shall describe the function's intended purpose ;

14. When exiting, the function shall use `return` instead of `exit()` ;

	int calculate(int i) {
		int result;
		if (i != 0)
			result = 30 / 1;
			return 0;
		else
			return 1;
	}

15. Variable declarations shall be at the top of the function ;

	int main() {
		int i, result;
		char foo;
		bool bar;
	}

### Switch

16. In `switch (foo)`, `case` shall be indented ;

	switch (foo) {
		case 'b':
			break;
		case 'a':
			printf("bar\n");
		default:
		return 0;
	}

### Preprocessor statements

17. The `#define` preprocessor statement shall only be used for setting 
constant values ;

	#define FOO 80

18. Preprocessor statements shall not be indented.
