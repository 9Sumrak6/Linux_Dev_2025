#!/bin/sh
set -e

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

autoreconf --force --install

echo "Autotools files generated."
echo "Run ./configure next."
