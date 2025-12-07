all:
	$(MAKE) translate
	gcc -Wall -Wextra -o number-game src/number_game.c
	$(MAKE) install-man
	$(MAKE) docs

translate:
	mkdir -p po/ru/LC_MESSAGES
	msgfmt po/ru.po -o po/ru/LC_MESSAGES/number_game.mo

docs:
	scripts/build.sh

install-man:
	install -Dm644 doc/number-game.6 ./local/share/man/man6/number-game.6

clean:
	-rm number-game po/*.pot
	-rm -r po/ru/
	-rm -r local
	-rm -rf doc/latex doc/html doc/man
	-rm doc/usage.md
