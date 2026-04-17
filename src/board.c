#include <stdlib.h>
#include <math.h>

#include "board.h"
#include "piece.h"
#include "utils.h"

Board board_init()
{
	Board b = { .clicked = (Point) {.x = -1,.y = -1} , .whiteTurn = true };
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
	Board b = board_init();

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

bool board_register_move(Board* b, Point from, Point to)
{
	int piece = b->state[from.x][from.y];
	if (piece < 0) return false;

	b->state[from.x][from.y] = -1;
	b->state[to.x][to.y] = piece;
	return true;
}

bool board_move_valid(const Board* b, Point from, Point to)
{
	if (from.x == to.x && from.y == to.y) return false;

	int piece = b->state[from.x][from.y];
	if (piece < 0) return false;
	if (b->state[from.x][from.y] < 0) return false; // Piece capture logic

	PieceColour colour = get_piece_colour(piece);
	PieceType type = get_piece_type(piece);

	switch (type)
	{
	case PIECE_PAWN:
		if (!move_valid_pawn(from, to)) return false;
		break;
	case PIECE_ROOK:
		if (!move_valid_rook(from, to)) return false;
		break;
	case PIECE_KNIGHT:
		if (!move_valid_knight(from, to)) return false;
		break;
	case PIECE_BISHOP:
		if (!move_valid_bishop(from, to)) return false;
		break;
	case PIECE_QUEEN:
		if (!move_valid_queen(from, to)) return false;
		break;
	case PIECE_KING:
		if (!move_valid_king(from, to)) return false;
		break;
	}

	return true;
}

bool board_mouse_over(float x, float y)
{
	if (x > BOARD_OFFSET_X && x < BOARD_OFFSET_X + BOARD_PX &&
		y > BOARD_OFFSET_Y && y < BOARD_OFFSET_Y + BOARD_PX) 
	{
		return true;
	}
	return false;
}

Point board_mouse_coords(float x, float y)
{
	int i, j;

	float xdiff = x - BOARD_OFFSET_X;
	float ydiff = SCREEN_H - BOARD_OFFSET_Y - y;

	i = (int)xdiff / (int)CELL_SIZE;
	j = (int)ydiff / (int)CELL_SIZE;

	return (Point) { .x = i, .y = j };
}

bool board_click_valid(const Board* b)
{
	int x = b->clicked.x;
	int y = b->clicked.y;

	if (x < 0 || y < 0) return false;

	if (b->state[x][y] < 0) return false;
	return true;
}
