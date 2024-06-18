# rasins – simple core utilities

The rasins project is a fork of the
[fases](https://utils.vitali64.duckdns.org) project. Most of the work is
done in the upstream fases project maintained by Ferass El Hafidi.

Please note that both this fork and the upstream project are work in
progress and have strange behavior. Do not use this in any production
environment.

These projects try to provide friendly, functioning, and simple core
utilities for a UNIX-like Operating System. They try to be entirely
portable and should work on any UNIX-like Operating System and kernel
such as OpenBSD and Linux. They also try to be completly modular and as
such one utility should **not** depend on another in order to work. The
coreutils are still a work-in-progress.

The fases utilities are currently tested on Artix, Alpine, OpenBSD,
macOS, and FreeBSD. We expect all utilities to work on all systems
implementing POSIX due to us using only POSIX-compliant functions.
The rasins fork hasn't been tested that much.
