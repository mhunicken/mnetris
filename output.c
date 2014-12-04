#include <assert.h>

#include <ncurses.h>

#include "board.h"

#define CHAR_BLOCK ((char)219)

WINDOW *boardw;

void output_initialize(int sizey, int sizex){
    initscr();
    keypad(stdscr, true);
    cbreak();
    echo();
    timeout(50);
    refresh();

    if(has_colors()){
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_RED);
        init_pair(2, COLOR_WHITE, COLOR_GREEN);
        init_pair(3, COLOR_WHITE, COLOR_YELLOW);
        init_pair(4, COLOR_WHITE, COLOR_BLUE);
        init_pair(5, COLOR_WHITE, COLOR_CYAN);
        init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(7, COLOR_WHITE, COLOR_WHITE);
    }

    WINDOW *borderw = newwin(sizey + 2, 2*sizex + 2, 2, 2);
    assert(!box(borderw, 0, 0));
    assert(!wrefresh(borderw));
    delwin(borderw);

    boardw = newwin(sizey, 2*sizex, 3, 3);
    assert(boardw != NULL);

    assert(!wrefresh(boardw));
    refresh();
}

void output_refreshboard(board_t p){
    int i,j;
    for(i = 0; i < p->sizey; ++i){
        for(j = 0; j < p->sizex; ++j){
            wattrset(boardw, COLOR_PAIR(p->cells[i][j] + 1));
            mvwprintw(boardw, i, 2 * j, "  ");
        }
    }
    wrefresh(boardw);
    move(0, 0);
}

void output_finalize(){
    delwin(boardw);
    endwin();
}
