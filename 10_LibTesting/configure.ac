AC_INIT([gmb], [1.0])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC
AC_CONFIG_MACRO_DIRS([m4])
LT_INIT

PKG_CHECK_MODULES([CHECK], [check >= 0.9.4], [have_check=yes], [have_check=no])
AM_CONDITIONAL([HAVE_CHECK], [test "x$have_check" = "xyes"])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT