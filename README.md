# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

## Goal

The `fases` project tries to provide friendly, functionnal and simple core 
utilities for a fully functionnal UNIX-like Operating System. It tries to 
be entirely portable and working on any UNIX-like Operating System and kernel 
such as OpenBSD and Linux. It also tries to be completly modular and as such 
one utility should **not** depend on another in order to work. The coreutils 
are still a work-in-progress.

## Status

The `fases` project is still incomplete as some utilities are missing, here's 
what `fases` currently provides:

(n: not implemented, i: implemented)

- `ls`
  
  - [i] Lists files.
  
  - [n] Other options.

- `head`

  - [i] Prints file until a specific line.
  
  - [i] Defaults to 10.
  
  - [i] `-n NUMBER`

- `cat`

  - [i] Prints file to stdin.
  
  - [n] `-u`. 

- `yes`
  
  - [i] Spams 'y'.
  
  - [i] Spams any other string specified by the user.

Other utilities are still in the making. Help is greatly appreciated.

## Compile

You have 2 choices:

- compile each utility separately;

- compile only fasesiab which includes all utilities in a single binary.

Modify the `config.mk` file to fit your needs in both cases.

### Compiling each utility separately

For example to compile `cat`, you have to run the following:

	$ cd src/cat
	$ make

And to install it, you have to run one of the 2 commands:

	Run only one of the two commands! 
	$ doas make install # Install as /usr/bin/cat
	$ doas make install-alongside # Install as /usr/bin/cat-fases

### Compiling fasesiab

Fasesiab stands for Ferass' Base System in a box. It includes the entire 
coreutils in a single and tiny binary.

First, go into the `src/fasesiab` folder:

	$ cd src/fasesiab

Before compiling, you have to generate the main.c file which, prior to 
the generation, contains nothing.

Run the following to generate the file:

	$ make gen

Then verify if it all went successfully by opening the file, the file should 
now have actual code along with a comment containing the date of generation.

Now you're ready to compile! Run `make` and get a binary!

	$ make

## Documentation

Documentation can be found inside the `man/` directory; run `man` to render 
them. Documentation isn't complete yet though, but most utilities are 
POSIX-compliant so they should work the same (if the utility is fully 
implemented of course).
