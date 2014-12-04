#include <stdlib.h>
#include <string.h>

#include "board.h"

board_t board_new(int sizey, int sizex){
    int i, j;
    board_t r = malloc(sizeof(struct board_s));

    r->sizey = sizey;
    r->sizex = sizex;

    r->cells = malloc(sizey * sizeof(int*));
    for(i = 0; i < sizey; i++){
        r->cells[i] = malloc(sizex * sizeof(int));
        for(j = 0; j < sizex; j++){
            r->cells[i][j] = -1;
        }
    }

    return r;
}

void board_destroy(board_t p){
    int i;
    for(i = 0; i < p->sizey; i++){
        free(p->cells[i]);
    }
    free(p->cells);
    free(p);
}

void board_updateblock(board_t p, block_t b, int s){
    int i,j;
    for(i = 0; i < b->sizey; i++){
        for(j = 0; j < b->sizex; j++){
            if(b->bitmap[i][j] && b->posy + i >= 0){
                p->cells[b->posy + i][b->posx + j] = s;
            }
        }
    }
}

int board_checkfulllines(board_t p){
    int i, j, r=0, c;  // c: line to move to
    bool w;
    for(i = c = p->sizey - 1; i >= 0; i--){
        w=true;
        for(j = 0; w && j < p->sizex; j++){
            w = p->cells[i][j] != -1;
        }
        if(w){
            r++;
            memset(p->cells[i], -1, p->sizex * sizeof(int));
        }
        else {
            if(i != c){
                memcpy(p->cells[c], p->cells[i], p->sizex * sizeof(int));
                memset(p->cells[i], -1, p->sizex * sizeof(int));
            }
            c--;
        }
    }
    return r;
}

bool board_isfull(board_t p){
    int i;
    for(i = 0; i < p->sizex; ++i){
        if(p->cells[0][i] != -1)return true;
    }
    return false;
}
