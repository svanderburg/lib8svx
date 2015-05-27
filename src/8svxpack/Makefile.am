8svxpack.1: main.c
	$(HELP2MAN) --output=$@ --no-info --name 'Compress or decompress 8SVX instruments inside an IFF file' --libtool ./8svxpack

AM_CPPFLAGS = -DHAVE_GETOPT_H=$(HAVE_GETOPT_H)

bin_PROGRAMS = 8svxpack
noinst_HEADERS = pack.h

8svxpack_SOURCES = main.c pack.c
8svxpack_LDADD = ../lib8svx/lib8svx.la
8svxpack_CFLAGS = -I../lib8svx $(LIBIFF_CFLAGS)

man1_MANS = 8svxpack.1
EXTRA_DIST = 8svxpack.1
