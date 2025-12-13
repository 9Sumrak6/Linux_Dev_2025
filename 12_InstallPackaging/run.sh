./autogen.sh
./configure --prefix=$PWD/.local
mkdir -p po/ru/LC_MESSAGES/
msgfmt -o po/ru/LC_MESSAGES/number-game.mo po/ru.po
make
make check
make install
export PATH=$PWD/.local/bin:$PATH
scripts/build.sh