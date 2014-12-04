#include <assert.h>

#include <ncurses.h>

#include "block.h"
#include "board.h"

#define CHAR_BLOCK ((char)219)

WINDOW *boardw, *nextblockw;

void output_initialize(int sizey, int sizex){
    initscr();
    keypad(stdscr, true);
    cbreak();
    noecho();
    timeout(50);
    refresh();

    if(has_colors()){
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_WHITE);
        init_pair(2, COLOR_WHITE, COLOR_RED);
        init_pair(3, COLOR_WHITE, COLOR_YELLOW);
        init_pair(4, COLOR_WHITE, COLOR_CYAN);
        init_pair(5, COLOR_WHITE, COLOR_GREEN);
        init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(7, COLOR_WHITE, COLOR_BLUE);
    }

    WINDOW *borderw = newwin(sizey + 2, 2*sizex + 2, 2, 2);
    assert(!box(borderw, 0, 0));
    assert(!wrefresh(borderw));
    delwin(borderw);

    boardw = newwin(sizey, 2*sizex, 3, 3);
    assert(boardw != NULL);

    assert(!wrefresh(boardw));

    nextblockw = newwin(MAXBLOCKSIZE, 2 * MAXBLOCKSIZE, 4, 2*sizex + 8);
    assert(!wrefresh(nextblockw));

    int ctrl_basey = 4 + MAXBLOCKSIZE + 6, ctrl_basex = 2 * sizex + 8;
    mvprintw(ctrl_basey, ctrl_basex,     "up:         rotate");
    mvprintw(ctrl_basey + 2, ctrl_basex, "down:       drop");
    mvprintw(ctrl_basey + 4, ctrl_basex, "left/right: move");

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

void output_drawnextblock(block_t b){
    int i,j;
    werase(nextblockw);
    wattrset(nextblockw, COLOR_PAIR(b->type + 1));
    for(i = 0; i < b->sizey; ++i){
        for(j = 0; j < b->sizex; ++j){
            if(b->bitmap[i][j]){
                mvwprintw(nextblockw, i, 2 * j, "  ");
            }
        }
    }
    wrefresh(nextblockw);
    move(0, 0);
}

void output_finalize(){
    delwin(boardw);
    delwin(nextblockw);
    endwin();
}
