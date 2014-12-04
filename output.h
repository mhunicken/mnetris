#ifndef MNETRIS_OUTPUT_H
#define MNETRIS_OUTPUT_H

#include "block.h"
#include "board.h"

void output_initialize(int sizey, int sizex);

void output_refreshboard(board_t p);

void output_drawnextblock(block_t b);

void output_finalize();

#endif
