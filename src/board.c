#include <stdlib.h>

#include "board.h"
#include "piece.h"
#include "utils.h"

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

int board_move_valid(const Board* b, Point from, Point to)
{
	if (from.x == to.x && from.y == to.y) return 1;

	int piece = b->state[from.x][from.y];
	if (piece < 0) return 1;
	if (b->state[from.x][from.y] < 0) return 1; // Piece capture logic

	PieceColour colour = get_piece_colour(piece);
	PieceType type = get_piece_type(piece);

	switch (type)
	{
	case PIECE_PAWN:
		if (!move_valid_pawn(from, to)) return 1;
		break;
	case PIECE_ROOK:
		if (!move_valid_rook(from, to)) return 1;
		break;
	case PIECE_KNIGHT:
		if (!move_valid_knight(from, to)) return 1;
		break;
	case PIECE_BISHOP:
		if (!move_valid_bishop(from, to)) return 1;
		break;
	case PIECE_QUEEN:
		if (!move_valid_queen(from, to)) return 1;
		break;
	case PIECE_KING:
		if (!move_valid_king(from, to)) return 1;
		break;
	}

	return 0;
}
