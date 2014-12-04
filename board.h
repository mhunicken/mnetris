#ifndef MNETRIS_BOARD_H
#define MNETRIS_BOARD_H

#include <stdbool.h>

#include "block.h"

struct board_s {
    int sizey, sizex;
    int **cells;        // Status of each cell. -1 if empty
};                      // type of respective block otherwise

typedef struct board_s *board_t;

/*
 *  Returns new board, with bitmap initialized to -1
 */
board_t board_new(int sizey, int sizex);

/*
 *  Destroys board p
 */
void board_destroy(board_t p);

/*
 *  Set bitmap status of block b in board p.
 */
void board_updateblock(board_t p, block_t b, int s);

/*
 *  Finds full lines of board p and erases them, compacting down.
 *  Returns number of full lines found.
 */
int board_checkfulllines(board_t p);

/*
 *  Returns true if there is a block in top of board p.
 */
bool board_isfull(board_t p);

#endif
