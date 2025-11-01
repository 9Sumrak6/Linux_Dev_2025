#!/bin/sh
set -e

# ---------------------------------------------------------
#  Safe autogen.sh — совместимый с automake и не зацикливает make
# ---------------------------------------------------------

# Полная очистка — вручную удаляем только автогенерируемое
if [ "$1" = "--clean" ]; then
    echo "Cleaning autotools files..."

    rm -rf \
        aclocal.m4 autom4te.cache \
        configure config.log config.status \
        Makefile.in */Makefile.in \
        compile config.guess config.sub depcomp \
        install-sh ltmain.sh missing \
        libtool

    echo "Done."
    exit 0
fi

echo "Running autoreconf..."

# ТОЛЬКО autoreconf — без лишних вызовов
autoreconf --force --install

echo "Autotools files generated."
echo "Run ./configure next."
