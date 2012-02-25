AM_CPPFLAGS = -DHAVE_GETOPT_H=$(HAVE_GETOPT_H)

bin_PROGRAMS = 8svxpp
noinst_HEADERS = pp.h

8svxpp_SOURCES = main.c pp.c
8svxpp_LDADD = ../lib8svx/lib8svx.la
8svxpp_CFLAGS = -I../lib8svx $(LIBIFF_CFLAGS)
