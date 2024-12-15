#include "menu.h"
#include <ncurses.h>

int interactive_menu(char **results, int result_count) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int choice = 0;
    int ch;
    while (1) {
        clear();
        for (int i = 0; i < result_count; i++) {
            if (i == choice) attron(A_REVERSE);
            mvprintw(i, 0, "%s", results[i]);
            if (i == choice) attroff(A_REVERSE);
        }

        ch = getch();
        if (ch == KEY_UP && choice > 0) {
            choice--;
        } else if (ch == KEY_DOWN && choice < result_count - 1) {
            choice++;
        } else if (ch == '\n') {
            break;
        }
    }

    endwin();
    return choice;
}
