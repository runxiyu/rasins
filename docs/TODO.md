# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](/README.md)

## TODO list

- Test on lots of unix/unix-like operating systems

- Add lots of utils

### chmod.c

- support "a+rwx" and such and -R

### chown.c

- fix

### date.c

- support dates as operands

### ln.c

- support -L/-P

- support this: `$ ln [-fs] [-L|-P] src target_dir`

### ls.c

- broken permissions, -l follows symlinks

### mkdir.c

- implement -p

### more.c

- implement more options

### printf.c

- fix string formatting

### rm.c

- implement all options, rm -R doesn't recursively
remove directories

