AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0], [example@example.com])
AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC

# Проверка pkg-config
AC_PATH_PROG([PKG_CONFIG], [pkg-config], [no])
if test "$PKG_CONFIG" = "no"; then
  AC_MSG_ERROR([pkg-config is required])
fi

# Проверка librhash
PKG_CHECK_MODULES([RHASH], [librhash >= 1.3.9], , AC_MSG_ERROR([librhash not found]))

# Проверка readline (опционально)
PKG_CHECK_MODULES([READLINE], [readline], HAVE_READLINE=yes, HAVE_READLINE=no)
AM_CONDITIONAL([USE_READLINE], [test "$HAVE_READLINE" = yes])

# только READLINE используется, RHASH — нет
AC_SUBST(READLINE_CFLAGS)
AC_SUBST(READLINE_LIBS)

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
