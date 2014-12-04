#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Needed for getch
#include <ncurses.h>

#include "block.h"
#include "board.h"
#include "helpers.h"
#include "output.h"

#define DEFAULTBOARDW 10
#define DEFAULTBOARDH 22

#define DEFAULTSPEED 200

int main(int argc, char *argv[]){
    srand(time(NULL) + get_miliseconds());
    output_initialize(DEFAULTBOARDH, DEFAULTBOARDW);

    board_t board = board_new(DEFAULTBOARDH, DEFAULTBOARDW);
    output_refreshboard(board);

    block_t current_block = block_new(-1);
    block_setboard(current_block, board);
    block_initpos(current_block);

    bool playing = true;
    int c, score = 0, speed = DEFAULTSPEED;
    uint64_t firstdrop, lastdrop;
    firstdrop = lastdrop = get_miliseconds();
    while(playing){
        bool change = false, drop = false;
        c = getch();
        switch(c){
            case KEY_LEFT:
                block_latmove(current_block, -1);
                change = true;
                break;
            case KEY_RIGHT:
                block_latmove(current_block, 1);
                change = true;
                break;
            case KEY_UP:
                block_rotate(current_block);
                change = true;
                break;
            case KEY_DOWN:
                drop = true;
                firstdrop = get_miliseconds();
                break;
        }
        uint64_t t = get_miliseconds();
        drop = drop || (lastdrop-firstdrop) / speed < (t-firstdrop) / speed;
        if(drop){
            change = true;
            lastdrop = get_miliseconds();
            if(!block_drop1(current_block)){
                if(board_isfull(board)){
                    playing = false;
                }
                else {
                    score += board_checkfulllines(board);
                }
                block_destroy(current_block);
                current_block = block_new(-1);
                block_setboard(current_block, board);
                block_initpos(current_block);
            }
        }
        if(change){
            output_refreshboard(board);
        }
    }

    getch();
    output_finalize();
    printf("score: %d\n", score);
    return 0;
}
