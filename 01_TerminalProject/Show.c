#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define ESC 27


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error occured while opening the file %s", argv[0]);
        return 1;
    }

    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    WINDOW *win = newwin(rows, cols, 0, 0);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, " %s ", argv[1]);
    wrefresh(win);

    WINDOW *frame = derwin(win, rows - 2, cols - 2, 1, 1);
    scrollok(frame, TRUE);

    char line[1024];
    int key;

    int lines_shown = 0;
    while (lines_shown < rows - 2 && fgets(line, sizeof(line), file)) {
        line[cols - 3] = '\0';
        wprintw(frame, "%s", line);
        ++lines_shown;
    }

    wrefresh(frame);

    while ((key = wgetch(win)) != ESC) {
        if (key == ' ') { // пробел = скролл на 1 строку
            if (fgets(line, sizeof(line), file)) {
                line[cols - 3] = '\0';
                wscrl(frame, 1);
                wprintw(frame, "%s", line);
                wrefresh(frame);
            }
        }
    }

    delwin(win);
    delwin(frame);
    endwin();

    fclose(file);

    return 0;
}