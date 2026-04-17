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

Board board_init_game()
{
	Board b;
	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		for (int j = 2; j < BOARD_CELLS - 2; ++j)
		{
			b.state[i][j] = -1;
		}
	}

	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		b.state[i][1] = PIECE_PAWN;
	}
	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		b.state[i][6] = PIECE_PAWN + NUM_PIECE_TYPES;
	}
	b.state[0][0] = PIECE_ROOK;
	b.state[1][0] = PIECE_KNIGHT;
	b.state[2][0] = PIECE_BISHOP;
	b.state[3][0] = PIECE_QUEEN;
	b.state[4][0] = PIECE_KING;
	b.state[5][0] = PIECE_BISHOP;
	b.state[6][0] = PIECE_KNIGHT;
	b.state[7][0] = PIECE_ROOK;

	b.state[0][7] = PIECE_ROOK   + NUM_PIECE_TYPES;
	b.state[1][7] = PIECE_KNIGHT + NUM_PIECE_TYPES;
	b.state[2][7] = PIECE_BISHOP + NUM_PIECE_TYPES;
	b.state[3][7] = PIECE_QUEEN  + NUM_PIECE_TYPES;
	b.state[4][7] = PIECE_KING   + NUM_PIECE_TYPES;
	b.state[5][7] = PIECE_BISHOP + NUM_PIECE_TYPES;
	b.state[6][7] = PIECE_KNIGHT + NUM_PIECE_TYPES;
	b.state[7][7] = PIECE_ROOK   + NUM_PIECE_TYPES;
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
