#ifndef BOARD_H__
#define BOARD_H__

#include "config.h"
#include "piece.h"

typedef struct {
	int state[BOARD_CELLS][BOARD_CELLS];
} Board;

Board board_init();
void board_register_pieces(const Board* b, const PieceArray* arr);

#endif //BOARD_H__