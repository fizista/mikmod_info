CC=gcc
LD=$(CC)

LIBMIKMOD_CONFIG=libmikmod-config
LIBMIKMOD_CFLAGS=$(shell $(LIBMIKMOD_CONFIG) --cflags)
LIBMIKMOD_LIBS  =$(shell $(LIBMIKMOD_CONFIG) --libs)

CFLAGS=-Wall -g $(LIBMIKMOD_CFLAGS)
LDFLAGS=$(LIBMIKMOD_LIBS)

PROG=mikmod_info

OBJS=mikmod_info.o

ifeq ($(strip $(PREFIX)),)
	PREFIX := /usr/local
endif

.PHONY : clean install

all: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(PROG)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.deb $(PROG)

install:
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 655 $(PROG) $(DESTDIR)$(PREFIX)/bin/

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROG)

deb:
	checkinstall --install=no --fstrans=yes --requires libmikmod3 --pkgname mikmod-info --pkgversion 0.1 --pkgrelease 1 --pkglicense MIT --maintainer fizista+mikmod@gmail.com --nodoc
