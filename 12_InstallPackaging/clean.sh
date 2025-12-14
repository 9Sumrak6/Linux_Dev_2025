rm aclocal* compile config.* configure~ depcomp configure install-* ltmain* missing Makefile Makefile.in test-driver ABOUT* libtool 
rm src/Makefile src/lib* src/Makefile.in src/*.o src/*.lo src/number-game
rm tests/Makefile tests/Makefile.in tests/number_game_test tests/*.log tests/*.trs tests/*.o  

rm -r autom4* m4 po/ru src/.* .local doc/html doc/latex doc/man tests/.deps tests/.libs

find po/ -maxdepth 1 ! -name "ru.po" ! -name "." -type f -exec rm -f {} \; 