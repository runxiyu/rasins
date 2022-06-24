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

`ls`:

- [i] Lists files.

- [i] `-a`

- [i] `-A`

- [i] `-C`

- [n] Other options.

`head`:

- [i] Prints file until a specific line.

- [i] Defaults to 10.

- [i] `-n NUMBER`

`cat`:

- [i] Prints file to stdin.

- [n] `-u`. 

`yes`:

- [i] Spams 'y'.

- [i] Spams any other string specified by the user.

`date`:

- [i] Shows date by default.

- [n] Formats date.

Other utilities are still in the making. Help is greatly appreciated.

## Chat

The `fases` project has 2 IRC channels hosted on 2 IRC Networks:

- `#fases` on `LibreIRC`:

server: `irc.andrewyu.org` ;

ssl: `6697` (recommended) ;

plain: `6667`.

- `##fases` on `Libera.Chat`:

server: `irc.libera.chat` ;

ssl: `6697` (recommended) ;

plain: `6667`.

Both of these channels are linked so all messages sent in one of them 
is sent on the other Network.

## Known bugs

The `fases` project is still a Work-in-progress and as such, there are bugs.
Please do report bugs to me, via IRC, email, or even by using Notabug.org 
issues.

| Bug | Affected utility/utilities |
|-----|----------------------------|
| Weird characters at the end of the output | `cat` |

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

## Mirrors

Development of fases is done on git.vitali64.duckdns.org but there are 
mirrors made by other people:

- [Notabug mirror made by me](https://notabug.org/vitali64/fases) ;

- [git.andrewyu.org mirror made by 
Andrew Yu](git://git.andrewyu.org/fases.git).

If you made a mirror too, be sure to let me know so I can add it on this 
section too!

## Thank you!

I would like to thank a few people there, mainly:

- Andrew Yu, for making a mirror on their git server at git.andrewyu.org, and 
linking the ##fases libera.chat channel to LibreIRC and for testing fases on
OpenBSD.

- Leah Rowe, for adding lots of improvements on her 
[git repo](https://notabug.org/vimuser/fases) and for testing fases on OpenBSD.

- Other people I forgot to add there. If I forgot to add you there, do send 
a patch or just tell me :D.

Contributions are very welcome, even if you're not a programmer. You can help 
this project by:

- Testing utilities and reporting bugs ;

- Talking about fases ;

- Giving me recommendations.

Help is greatly appreciated, thanks!
