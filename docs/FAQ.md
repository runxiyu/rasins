# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](../README.md)

## FAQ

Here are questions someone could ask. Read it! It could answer some of your 
questions.

Q: Why another coreutils? There's already GNU, Busybox, OpenBSD's, and some more.

A: Most coreutils are either non-POSIX or use non-portable functions not 
specified by POSIX. The `fases` project separates POSIX and non-POSIX 
utilities while others do not. Some have also quite complex code, making it 
harder to study the code.

[We're not trying to trash other coreutils. A lot of them 
(Busybox, OpenBSD, ...) are actually really good]

Q: Is fases going to work on <insert UNIX-like operating system name here>?

A: Well, it depends on the system itself. If your system implements POSIX 
functions in its libc, then it'll work. Utilities are currently tested on 
- OpenBSD ;

- FreeBSD ;

- OS X/Mac OS X/MacOS (just a little) ;

- Artix Linux and Arch Linux ;

- Alpine Linux.

No. `fases` will never work on Microsoft Windows.

---

More coming soon.
