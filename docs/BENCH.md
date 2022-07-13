# fases - Ferass' Base System

*Simple coreutils for a fully functionnal UNIX-like system*

[« Go back](/README.md)

## Benchmarks

Because of `fases` being very small, the utilities are essentially faster 
than their GNU counterparts. Still not convinced? Here are some benchmarks.

These benchmarks were made on the ***10th of July 2022***.

Note: Only finished utilities are compared with their GNU conterparts.

Note: This was tested with musl-gcc.

### cat

Concatenating a file with only one line.

```
file.txt:
----------------
This is a file.
```

```
$ cat /tmp/file.txt
```

GNU cat:

```
This is a file.

real    0m0.003s
user    0m0.003s
sys 0m0.001s
```

`fases` cat without optimizations:

```
This is a file.

real    0m0.002s
user    0m0.002s
sys 0m0.000s
```

`fases` cat with optimizations (`O3`):

```
This is a file.

real    0m0.001s
user    0m0.001s
sys 0m0.000s
```

### ls

Listing directories inside the git repo.

```
$ ls <fases repo>
```


GNU ls:

```
BENCH.md  box.c  box_tmp          COMPILE.md  COPYING  extras    man         
README.md  TODO.md
box       box.o  CODING_STYLE.md  config.mk   core     Makefile  MIRRORS.md  
STATUS.md

real    0m0.009s
user    0m0.009s
sys 0m0.001s
```

`fases` ls without optimizations:

```
STATUS.md box.c COMPILE.md config.mk BENCH.md box.o extras core box_tmp 
README.md CODING_STYLE.md MIRRORS.md box Makefile TODO.md man COPYING

real    0m0.002s
user    0m0.002s
sys 0m0.001s
```

`fases` ls with optimizations (`O3`):

```
STATUS.md box.c COMPILE.md config.mk BENCH.md box.o extras core box_tmp 
README.md CODING_STYLE.md MIRRORS.md box Makefile TODO.md man COPYING

real    0m0.001s
user    0m0.001s
sys 0m0.001s
```

### uname

Running uname without any arguments.

```
$ uname
```

GNU uname:

```
Linux

real    0m0.002s
user    0m0.001s
sys 0m0.001s
```

`fases` uname without optimizations:

```
Linux

real    0m0.001s
user    0m0.001s
sys 0m0.001s
```

`fases` uname with optimizations (`O3`):

```
Linux

real    0m0.001s
user    0m0.001s
sys 0m0.001s
```

### sleep

Suspending execution for one second.

```
$ sleep 1
```

GNU sleep:

```
real    0m1.003s
user    0m0.003s
sys 0m0.001s
```

`fases` sleep without optimizations:

```
real    0m1.002s
user    0m0.002s
sys 0m0.000s
```

`fases` sleep with optimizations (`O3`):

```
real    0m1.002s
user    0m0.001s
sys 0m0.001s
```
