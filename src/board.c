#include "board.h"
#include "piece.h"

Board board_init()
{
	Board b;
	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		for (int j = 0; j < BOARD_CELLS; ++j)
		{
			b.state[i][j] = -1;
		}
	}
	return b;
}

void board_register_pieces(Board* b, const PieceArray* arr)
{
	for (int i = 0; i < arr->len; ++i)
	{
		Piece p = arr->data[i];
		b->state[p.x][p.y] = p.type + NUM_PIECE_TYPES * p.colour;
	}
}

int board_register_move(Board* b, Point from, Point to)
{
	int piece = b->state[from.x][from.y];
	if (piece < 0) return 1;

	b->state[from.x][from.y] = -1;
	b->state[to.x][to.y] = piece;
	return 0;
}
