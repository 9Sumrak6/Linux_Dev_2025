check_PROGRAMS = test_gmb
test_gmb_SOURCES = test_gmb.c

AM_CPPFLAGS = -I$(top_srcdir)/src

test_gmb_LDADD = $(top_builddir)/src/libgmb.la

TESTS = $(check_PROGRAMS)

test_gmb_LDADD += $(CHECK_LIBS)
AM_CFLAGS = $(CHECK_CFLAGS)