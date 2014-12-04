#ifndef MNETRIS_OUTPUT_H
#define MNETRIS_OUTPUT_H

#include "board.h"

void output_initialize(int sizey, int sizex);

void output_refreshboard(board_t board);

void output_finalize();

#endif
