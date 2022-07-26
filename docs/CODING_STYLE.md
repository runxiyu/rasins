# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](/README.md)

## Coding Style

The programming language used is ***POSIX C99*** and all code must be written 
in ***POSIX C99***, no extensions are used.

The coding style is as follows:

### General

- The code shall be as simple to understand as possible, add comments if 
necessary ;

- For indentation, the code shall use tab characters ;

- The code shall avoid using GNU-specific functions (as that would make 
the program less portable) ;

- Each line shall not exceed 79 characters ;

- Utilities shall only implement POSIX-compliant options, if the utility 
supports options, and the specified option is invalid, the utility shall 
print a help text (this applies only to coreutils) ;

- Utilities shall only use the **standard C library and POSIX libraries** ;

- For comments, instead of using `//` (as in `// Comment`), the code shall 
use `/*` and `*/` (as in `/* Comment */`) ;

- For commenting code, use `//` (as in `// printf("broken code")`) ;

- **Variable names** shall describe the variable's purpose ;

### Blocks

- In a block, do not use `{` and `}` if there's only one instruction inside ;

```
for (int i; i != 3; i++)
	printf("%d\n", i);
```

- When using `{` and `}`, `{` shall not be on it's own line ;

```
if (i) {
	printf("%d", i);
	i = 3;
}
```

- The block shall only use 1 line if there's only one instruction ran and 
that shall not exceed 79 characters ;

```
if (foo[1] == 'a') foo[1] = 'b';
```

### Functions

- The function type shall be on the same line as the function name and `{` ;

```
int main() {
	printf("Hello World.\n");
}
```

- Function names shall describe the function's intended purpose ;

- When exiting, the function shall use `return` instead of `exit()` ;
	
```
int calculate(int i) {
	int result;
	if (i != 0)
		result = 30 / 1;
		return 0;
	else
		return 1;
}
```

- Variable declarations shall be at the top of the function ;

```
int main() {
	int i, result;
	char foo;
	bool bar;
}
```

### Switch

- In `switch (foo)`, `case` shall be indented ;

```
switch (foo) {
	case 'b':
		break;
	case 'a':
		printf("bar\n");
	default:
		return 0;
}
```

### Preprocessor statements

- The `#define` preprocessor statement shall only be used for setting 
constant values ;

```
#define FOO 80
```

- Preprocessor statements shall not be indented.
