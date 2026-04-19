#include <stdlib.h>
#include <math.h>

#include "board.h"
#include "utils.h"

Board board_init()
{
	Board b = (Board){ .turn = PIECE_WHITE };
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

MoveResult board_register_move(Board* b, Point from, Point to)
{
	int piece = b->state[from.x][from.y];
	b->state[from.x][from.y] = -1;
	b->state[to.x][to.y] = piece;
	PieceColour colourToCheck = (b->turn == PIECE_WHITE) ? PIECE_BLACK : PIECE_WHITE;

	if (board_in_check(b, colourToCheck))
		return (colourToCheck == PIECE_WHITE) ? MOVE_WHITE_IN_CHECK : MOVE_BLACK_IN_CHECK;

	PieceType type = get_piece_type(piece);
	if (type == PIECE_PAWN && (to.y == 00 || to.y == 7))
		return MOVE_PROMOTE;
	return MOVE_OK;
}

void board_next_turn(Board* b)
{
	b->turn = (b->turn == PIECE_WHITE) ? PIECE_BLACK : PIECE_WHITE;
}

void board_pawn_promote(Board* b, Point from, PieceType type)
{
	int x = from.x;
	int step = (b->turn == PIECE_WHITE) ? 1 : -1;
	int y = from.y + step;

	PieceColour colour = b->turn;

	int id = get_piece_id(type, colour);

	b->state[x][y] = id;
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
		bool canMove = move_valid_pawn(from, to, b->turn);
		bool canCapture = move_valid_pawn_capture(from, to, b->turn);

		if (!canMove && !canCapture) return false;
		if (!canCapture && board_blocked_pawn(b, from, to)) return false;
		if (!canMove && b->state[to.x][to.y] < 0) return false;
		break;
	case PIECE_ROOK:
		if (!move_valid_rook(from, to)) return false;
		if (board_blocked_rook(b, from, to)) return false;
		break;
	case PIECE_KNIGHT:
		if (!move_valid_knight(from, to)) return false;
		break;
	case PIECE_BISHOP:
		if (!move_valid_bishop(from, to)) return false;
		if (board_blocked_bishop(b, from, to)) return false;
		break;
	case PIECE_QUEEN:
		if (!move_valid_queen(from, to)) return false;
		if (move_valid_rook(from, to) && board_blocked_rook(b, from, to)) return false;
		if (move_valid_bishop(from, to) && board_blocked_bishop(b, from, to)) return false;
		break;
	case PIECE_KING:
		if (!move_valid_king(from, to)) return false;
		break;
	}

	if (!board_can_capture(b, from, to)) return false;

	if (get_piece_type(b->state[to.x][to.y]) != PIECE_KING)
	{
		Board b_copy = *b;
		board_next_turn(&b_copy);
		board_register_move(&b_copy, from, to);
		if (board_in_check(&b_copy, b->turn)) return false;
	}

	return true;
}

bool board_in_check(const Board* b, PieceColour colourToCheck)
{
	int kingx = -1;
	int kingy = -1;
	int searchStartIdx, searchStep;
	if (colourToCheck == PIECE_WHITE)
	{
		for (int j = 0; j < BOARD_CELLS; ++j)
		{
			for (int i = 0; i < BOARD_CELLS; ++i)
			{
				int piece = b->state[i][j];
				PieceColour c = get_piece_colour(piece);
				PieceType t = get_piece_type(piece);

				if (t == PIECE_KING && c == colourToCheck)
				{
					kingx = i;
					kingy = j;
				}
			}
		}
	}
	else
	{
		for (int j = 7; j >= 0; --j)
		{
			for (int i = 0; i < BOARD_CELLS; ++i)
			{
				int piece = b->state[i][j];
				PieceColour c = get_piece_colour(piece);
				PieceType t = get_piece_type(piece);

				if (t == PIECE_KING && c == colourToCheck)
				{
					kingx = i;
					kingy = j;
					goto foundKing;
				}
			}
		}
	}
foundKing:
	if (kingx < 0 || kingy < 0) return false;

	Point to = { .x = kingx, .y = kingy };

	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		for (int j = 0; j < BOARD_CELLS; ++j)
		{
			int piece = b->state[i][j];
			if (piece < 0) continue;
			PieceColour c = get_piece_colour(piece);
			PieceType t = get_piece_type(piece);
			if (c == colourToCheck) continue;

			Point from = { .x = i, .y = j};
			if (board_move_valid(b, from, to)) return true;
		}
	}

	return false;
}

bool board_is_mate(const Board* b, PieceColour colourToCheck)
{
	Board b_copy = *b;
	b_copy.turn = colourToCheck;
	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		for (int j = 0; j < BOARD_CELLS; ++j)
		{
			int piece = b->state[i][j];
			if (piece < 0) continue;
			PieceColour c = get_piece_colour(piece);
			PieceType t = get_piece_type(piece);
			if (c != colourToCheck) continue;
			for (int ii = 0; ii < BOARD_CELLS; ++ii)
			{
				for (int jj = 0; jj < BOARD_CELLS; ++jj)
				{
					Point from = { .x = i, .y = j };
					Point to = { .x = ii, .y = jj };
					//Board b_copy = *b;
					if (board_move_valid(&b_copy, from, to)) 
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool board_blocked_pawn(const Board* b, Point from, Point to)
{
	bool firstMove = false;
	switch (b->turn) {
	case PIECE_WHITE:
		firstMove = from.y == 1 && b->state[from.x][from.y + 2] >= 0;
		return (firstMove || b->state[from.x][from.y + 1] >= 0);
	case PIECE_BLACK:
		firstMove = from.y == 6 && b->state[from.x][from.y - 2] >= 0;
		return (firstMove || b->state[from.x][from.y - 1] >= 0);
	}
}

bool board_blocked_rook(const Board* b, Point from, Point to)
{
	if (from.x == to.x)
	{
		int step = (to.y > from.y) ? 1 : -1;
		for (int y = from.y + step; y != to.y; y += step)
			if (b->state[from.x][y] >= 0) return true;
	}
	else
	{
		int step = (to.x > from.x) ? 1 : -1;
		for (int x = from.x + step; x != to.x; x += step)
			if (b->state[x][from.y] >= 0) return true;
	}
	return false;
}

bool board_blocked_bishop(const Board* b, Point from, Point to)
{
	int xstep = (to.x > from.x) ? 1 : -1;
	int ystep = (to.y > from.y) ? 1 : -1;

	int x = from.x + xstep;
	int y = from.y + ystep;

	while (x != to.x)   // stops before reaching destination
	{
		if (b->state[x][y] >= 0) return true;
		x += xstep;
		y += ystep;
	}
	return false;
}

bool board_can_capture(const Board* b, Point from, Point to)
{
	int capturePiece = b->state[to.x][to.y];
	if (capturePiece < 0) return true;
	if (get_piece_colour(capturePiece) == b->turn) return false;
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

bool board_select_valid(const Board* b, Point clicked)
{
	int x = clicked.x;
	int y = clicked.y;

	if (x < 0 || y < 0) return false;

	if (b->state[x][y] < 0) return false;

	int piece = b->state[x][y];
	if (get_piece_colour(piece) != b->turn) return false;

	return true;
}


