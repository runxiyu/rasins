# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

***Project Documentation***

- [Main page](README.md)

- [Compile fases](COMPILE.md)

- [Mirrors](MIRRORS.md)

## Status

The `fases` project is still incomplete as some utilities are missing, here's 
what `fases` currently provides:

(n: not implemented, i: implemented)

`ls`:

- [i] Lists files.

- [i] `-a`

- [i] `-A`

- [i] `-C`

- [i] `-1`

- [i] `-R`

- [n] Other options.

`head`:

- [i] Prints file until a specific line.

- [i] Defaults to 10.

- [i] `-n NUMBER`

`cat`:

- [i] Prints file to stdout.

- [n] `-u`. 

`yes`:

- [i] Spams 'y'.

- [i] Spams any other string specified by the user.

`date`:

- [i] Shows date by default.

- [n] Formats date.

`mkdir`:

- [i] creates directories

- [n] `-p`

- [n] `-m MODE`

Other utilities are still in the making. Help is greatly appreciated.

## Known bugs

The `fases` project is still a Work-in-progress and as such, there are bugs.
Please do report bugs to me, via IRC, email, or even by using Notabug.org 
issues.

| Bug                                          | Affected utility-ies |
|-------------------------------------------------------------|-------|
| Weird characters at the end of the output                   | `cat` |
| When running `cat file -`, it outputs file's contents twice | `cat` |

