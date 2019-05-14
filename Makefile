DESTDIR   ?=
PREFIX    ?= /usr/local
MANPREFIX ?= $(PREFIX)/man

CFLAGS += -Wall -Wextra

all: ptee

clean:
	rm -f ptee

install: ptee
	install -d $(DESTDIR)$(PREFIX)/bin
	install -d $(DESTDIR)$(MANPREFIX)/man1
	install -m 755 ptee   $(DESTDIR)$(PREFIX)/bin/
	install -m 644 ptee.1 $(DESTDIR)$(MANPREFIX)/man1/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/ptee
	rm -f $(DESTDIR)$(MANPREFIX)/man1/ptee.1

.PHONY:
	all clean install uninstall
