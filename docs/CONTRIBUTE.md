# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](/README.md)

## Contributions

Want to contribute to `fases`? Great! Here are some recommendations to 
make sure your patch can be accepted.

1. Write useful commit names

This is important. Many people write commit names that aren't serious.
Here are examples of commit names you should **not** use:

* "jenius fix" ;
* "Update cat.c" ;
* "aaa" ;
* "replace horrible head with okay head".

There are many other bad commit names you shouldn't use.
Here are examples of commit names you **should** use:

* "core/wc: Error handling." ;
* "Makefile: Fix bugs in the test suite" ;
* "sh: Move error handling to parseCommand()".

Commit descriptions can also be added, but they're not needed:

* "sh: Add support for comments" ;

```
Example:
$ echo 'Hello World' # Hello World
This is now possible.
```

* "docs/: Finally add a license"

```
The license used is a slightly-modified version of the FreeBSD Documentation
permissive License, compatible with the GNU Free Documentation License.
```

2. The coding style

See [docs/CODING_STYLE.md](CODING_STYLE.md)

3. Use `git send-email`

`fases` is mirrored on lots of Git forges, including some that support 
"Pull Requests". The usual, prefered way of sending patches is to use 
`git send-email`. Please do prefix the repo you want to patch 
('[PATCH fases.git]').

See [git-send-email.io](https://git-send-email.io)

4. Sign-off your commits

Signing-off your commits means that you agree to the coding style and that 
you should be nice to people when responding to feedback.
We require you to sign-off your commits, like so:

```
$ git commit -s # -s means "sign-off"
```

If your patch fully complies with what was said before then send it! If
you're not sure your patch complies with all that then send it anyway. We 
do want to see your patch!
