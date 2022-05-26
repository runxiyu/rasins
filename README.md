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

- `cat`

  - [i] Prints file to stdin.
  
  - [n] `-u`.

- `yes`
  
  - [i] Spams 'y'.
  
  - [i] Spams any other string specified by the user.

Other utilities are still in the making. Help is greatly appreciated.

## Compile

You have to compile each utility separately, for example to compile `cat`:

	$ cd src/core/cat
	$ make

And to install it, you have to run:

	Run only one of the two commands! 
	$ doas make install 
	$ doas make install-alongside

## Documentation

Documentation can be found inside the `man/` directory; run `man` to render 
them.


