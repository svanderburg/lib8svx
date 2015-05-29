8svxpp.1: main.c
	$(HELP2MAN) --output=$@ --no-info --name 'Displays a textual representation of an IFF/8SVX file on the standard output' --libtool ./8svxpp

AM_CPPFLAGS = -DHAVE_GETOPT_H=$(HAVE_GETOPT_H)

bin_PROGRAMS = 8svxpp
noinst_HEADERS = pp.h
man1_MANS = 8svxpp.1

8svxpp_SOURCES = main.c pp.c
8svxpp_LDADD = ../lib8svx/lib8svx.la
8svxpp_CFLAGS = -I../lib8svx $(LIBIFF_CFLAGS)

EXTRA_DIST = 8svxpp.1
