.PHONY: all distdir dist clean

CC=gcc
CFLAGS=-Wall -O2
VERSION=1.0

all: clipboard-daemon

clipboard-daemon: main.o clipboard-daemon.o selection-data-list.o
	$(CC) $(CFLAGS) main.o clipboard-daemon.o selection-data-list.o -o clipboard-daemon `pkg-config --libs gtk+-2.0`

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o `pkg-config --cflags gtk+-2.0`

clipboard-daemon.o: clipboard-daemon.c clipboard-daemon.h
	$(CC) $(CFLAGS) -c clipboard-daemon.c -o clipboard-daemon.o `pkg-config --cflags gtk+-2.0`

selection-data-list.o: selection-data-list.c selection-data-list.h
	$(CC) $(CFLAGS) -c selection-data-list.c -o selection-data-list.o `pkg-config --cflags gtk+-2.0`

distdir:
	rm -rf clipboard-daemon-$(VERSION)
	mkdir clipboard-daemon-$(VERSION)
	cp main.c clipboard-daemon.c clipboard-daemon.h selection-data-list.c selection-data-list.h Makefile clipboard-daemon-$(VERSION)/

dist: distdir
	rm -f clipboard-daemon-$(VERSION).tar.bz2
	tar -cf clipboard-daemon-$(VERSION).tar clipboard-daemon-$(VERSION)
	bzip2 -9 clipboard-daemon-$(VERSION).tar
	rm -rf clipboard-daemon-$(VERSION)

clean:
	rm -f *.o test clipboard-daemon
