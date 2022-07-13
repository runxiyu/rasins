# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](/README.md)

## Compile

You have 2 choices:

- compile each utility separately;

- compile only fasesiab which includes all utilities in a single binary.

Modify the `config.mk` file to fit your needs in both cases.

## Compiling each utility separately

For example to compile `cat`, you have to run the following:

	$ cd core/
	$ make cat

And to compile a non-POSIX utility such as `yes`, you have to run the 
following:

	$ cd extras/
	$ make yes

## Compiling fasesiab

Fasesiab stands for Ferass' Base System in a box. It includes the entire 
coreutils in a single and tiny binary.

Before compiling, you have to prepare `fasesiab`.
The `box.c` file should already contain some code but it may be outdated 
so it's recommended to regenerate it:

	$ make genbox

Next, run the following:

	$ make prepbox

Now you're ready to compile! Run `make` and get a binary!

	$ make box

## Installation

For now, you can only install fasesiab and no manpages are being installed. 
To install, simply run the following:

	$ doas make install

Or, if using `sudo`:

	$ sudo make install

Then, you should have a binary called `box`. Make sure `/usr/local/bin/` or 
whatever `DESTDIR` and `PREFIX` you set is in your `$PATH`.
