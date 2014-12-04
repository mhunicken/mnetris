#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "board.h"


/*
 *  Arrays describing types of blocks
 */

bool block_bitmaps[NBLOCKTYPE][MAXBLOCKSIZE][MAXBLOCKSIZE] = {
    {
        {1,1},
        {1,1}
    },
    {
        {1,1,1,1}
    },
    {
        {1,1,1},
        {1,0,0}
    },
    {
        {1,1,1},
        {0,0,1}
    },
    {
        {1,1,1},
        {0,1,0}
    },
    {
        {1,1,0},
        {0,1,1}
    },
    {
        {0,1,1},
        {1,1,0}
    }
};

int block_sizesx[NBLOCKTYPE] = {2,4,3,3,3,3,3};
int block_sizesy[NBLOCKTYPE] = {2,1,2,2,2,2,2};

/*
 *  Block functions
 */

block_t block_new(int t){
    block_t r;
    if(t < 0 || t >= NBLOCKTYPE){
        t = rand() % NBLOCKTYPE;
    }
    r = malloc(sizeof(struct block_s));
    r->type = t;
    r->sizex = block_sizesx[t];
    r->sizey = block_sizesy[t];
    r->posx = r->posy = -1;
    memcpy(r->bitmap, block_bitmaps[t], sizeof(r->bitmap));
    r->board = NULL;
    return r;
}

void block_destroy(block_t b){
    free(b);
}

void block_setboard(block_t b, board_t p){
    b->board = p;
}

void block_initpos(block_t b){
    int minx = 0, maxx = b->board->sizex - b->sizex;
    b->posx = minx + (rand() % (maxx-minx+1));
    b->posy = 1 - b->sizey;

    board_updateblock(b->board, b, b->type);
}

void block_rotate(block_t b){
    bool r = true;
    int i, j;
    bool newbm[MAXBLOCKSIZE][MAXBLOCKSIZE];
    int newsy, newsx;

    if(b->posx + b->sizey > b->board->sizex){
        return;
    }

    for(i = 0; i < b->sizey; i++){
        for(j = 0; j < b->sizex; j++){
            newbm[j][b->sizey - i - 1] = b->bitmap[i][j];
        }
    }
    newsy = b->sizex;
    newsx = b->sizey;

    board_updateblock(b->board, b, -1);
    for(i = 0; r && i < newsy; i++){
        for(j = 0; r && j < newsx; j++){
            if(b->posy + j >= 0 && newbm[i][j]){
                r = b->board->cells[b->posy + i][b->posx + j] < 0;
            }
        }
    }
    if(r){
        b->sizex = newsx;
        b->sizey = newsy;

        for(i = 0; i < b->sizey; i++){
            for(j = 0; j < b->sizex; j++){
                b->bitmap[i][j] = newbm[i][j];
            }
        }
    }

    board_updateblock(b->board, b, b->type);
}

bool block_drop1(block_t b){
    bool r = true;
    int i, j;

    if(b->posy + b->sizey >= b->board->sizey){
        return false;
    }

    board_updateblock(b->board, b, -1);

    for(i = 0; r && i < b->sizey; i++){
        for(j = 0; r && j < b->sizex; j++){
            if(b->posy + i >= 0 && b->bitmap[i][j]){
                r = b->board->cells[b->posy + i + 1][b->posx + j] < 0;
            }
        }
    }
    if(r){
        b->posy++;
    }
    board_updateblock(b->board, b, b->type);
    return r;
}

void block_latmove(block_t b, int dir){
    bool r = true;
    int i, j;

    if(b->posx + dir < 0 || b->posx + b->sizex + dir > b->board->sizex){
        return;
    }

    board_updateblock(b->board, b, -1);
    for(i = 0; r && i < b->sizey; i++){
        for(j = 0; r && j < b->sizex; j++){
            if(b->posy + i >= 0 && b->bitmap[i][j]){
                r = b->board->cells[b->posy + i][b->posx + j + dir] < 0;
            }
        }
    }
    if(r){
        b->posx += dir;
    }
    board_updateblock(b->board, b, b->type);
}
