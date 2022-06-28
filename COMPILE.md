# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](README.md)

## Compile

You have 2 choices:

- compile each utility separately;

- compile only fasesiab which includes all utilities in a single binary.

Modify the `config.mk` file to fit your needs in both cases.

## Compiling each utility separately

For example to compile `cat`, you have to run the following:

	$ make cat

## Compiling fasesiab

Fasesiab stands for Ferass' Base System in a box. It includes the entire 
coreutils in a single and tiny binary.

Before compiling, you have to prepare `fasesiab`.
Run the following:

	$ make prepbox

Now you're ready to compile! Run `make` and get a binary!

	$ make box

