bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c

rhasher_CFLAGS =
rhasher_LDADD = -lrhash

if USE_READLINE
rhasher_CFLAGS += @READLINE_CFLAGS@ -DUSE_READLINE
rhasher_LDADD  += @READLINE_LIBS@
endif

CLEANFILES = rhasher *.o *.lo *.la
