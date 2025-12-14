# Number Game

Interactive number guessing game with Roman numeral support.

- Build system: Autotools
- Library: libnumbergame.so
- Localization: gettext (ru/LC_MESSAGES/number_game.mo)
- Documentation: Doxygen, manpage

Usage:
First of all you should run
```sh
./run.sh
```
to build program.
Then number-game will be installed in
```sh
$PWD/.local/bin/number-game
```
To play you should run ```./number-game.sh``` script similar to simple program run or run:
```sh
LANGUAGE=<locale>.UTF-8 .local/bin/number-game [OPTIONS]
```
