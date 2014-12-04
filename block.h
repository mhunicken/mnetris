#ifndef MNETRIS_BLOCK_H
#define MNETRIS_BLOCK_H

#define NBLOCKTYPE 7
#define MAXBLOCKSIZE 4

#include <stdbool.h>

typedef struct board_s *board_t;

/*
 *  block struct
 */
struct block_s {
    int type;          // Type of block (respective index in block_*) 
    int sizey, sizex;
    int posy, posx;    // Position in board (x: leftmost cell, y: highest cell)
    bool bitmap[MAXBLOCKSIZE][MAXBLOCKSIZE];  // Bitmap of block
    board_t board;     // Respective board
};

typedef struct block_s *block_t;

/*
 *  Returns new block of type t.
 *  If t is non valid (negative or >= NBLOCKTYPE), returns block of random type
 */
block_t block_new(int t);

/*
 *  Destroys block b.
 */
void block_destroy(block_t b);

/*
 *  Sets board to p
 */
void block_setboard(block_t b, board_t p);

/*
 *  Initialize position of block.
 *  Draws block.
 *  pre: board is set
 */
void block_initpos(block_t b);

/*
 *  Attempts to rotate block b clockwise. 
 *  On success, redraws block
 *  pre: initpos was called
 */
void block_rotate(block_t b);

/*
 *  Tries to drop block b 1 cell.
 *  Returns true on succeed, false otherwise
 *  On success, redraws block
 *  pre: initpos was called
 */
bool block_drop1(block_t b);

/*
 *  Tries to move block b left (dir==-1) or right (dir==1)
 *  On success, redraws block
 *  pre: initpos was called
 */
void block_latmove(block_t b, int dir);

#endif
