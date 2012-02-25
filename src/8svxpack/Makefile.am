AM_CPPFLAGS = -DHAVE_GETOPT_H=$(HAVE_GETOPT_H)

bin_PROGRAMS = 8svxpack
noinst_HEADERS = pack.h

8svxpack_SOURCES = main.c pack.c
8svxpack_LDADD = ../lib8svx/lib8svx.la
8svxpack_CFLAGS = -I../lib8svx $(LIBIFF_CFLAGS)
