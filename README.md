ptee
====
**ptee** *program* [*argument* ...]

Copies standard input to standard output and a second program,
unlike regular [tee](http://man.openbsd.org/tee) which copies to files.

Examples
--------
Display a fortune cookie and its word count:

    fortune | ptee wc

Display and email build output,
taking care to include standard error:

    make 2>&1 | ptee mail john@example.com

Running
-------
Should work on most Unix systems, including Linux, BSD, and macOS.

    make
    make install   [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]
    make uninstall [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]

Author
------
Sijmen J. Mulder (ik@sjmulder.nl)
