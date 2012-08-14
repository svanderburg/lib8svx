check_PROGRAMS = writesimple8svx readsimple8svx

noinst_HEADERS = simple8svxdata.h

writesimple8svx_SOURCES = simple8svxdata.c writesimple8svx.c
writesimple8svx_LDADD = -lm ../src/lib8svx/lib8svx.la $(LIBIFF_LIBS)
writesimple8svx_CFLAGS = -I../src/lib8svx $(LIBIFF_CFLAGS)

readsimple8svx_SOURCES = simple8svxdata.c readsimple8svx.c
readsimple8svx_LDADD = -lm ../src/lib8svx/lib8svx.la $(LIBIFF_LIBS)
readsimple8svx_CFLAGS = -I../src/lib8svx $(LIBIFF_CFLAGS)

TESTS = writesimple8svx readsimple8svx
