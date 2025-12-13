AUTOMAKE_OPTIONS = foreign

# Библиотека
lib_LTLIBRARIES = libnumbergame.la
libnumbergame_la_SOURCES = roman.c
libnumbergame_la_LDFLAGS = -version-info 1:0:0

# Программа
bin_PROGRAMS = number-game
number_game_SOURCES = number_game.c
number_game_LDADD = libnumbergame.la $(LIBINTL)
