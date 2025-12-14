AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libnumbergame.la
libnumbergame_la_SOURCES = roman.c
libnumbergame_la_LDFLAGS = -version-info 1:0:0

bin_PROGRAMS = number-game
number_game_SOURCES = number_game.c
number_game_LDADD = libnumbergame.la $(LIBINTL)
