#include "ui.h"

bool restart_mouse_over(float x, float y)
{
	if (x > RESTART_OFFSET_X && x < RESTART_OFFSET_X + RESTART_W &&
		y > RESTART_OFFSET_Y && y < RESTART_OFFSET_Y + RESTART_H)
	{
		return true;
	}
	return false;
}

bool promote_mouse_over(float x, float y)
{
	if (x > PROMOTE_OFFSET_X && x < PROMOTE_OFFSET_X + PROMOTE_BOX_W &&
		y > PROMOTE_OFFSET_Y && y < PROMOTE_OFFSET_Y + PROMOTE_H)
	{
		return true;
	}
	return false;
}

PieceType promote_mouse_selection(float x, float y)
{
	float xdiff = PROMOTE_OFFSET_X - x;

	int idx = (int)xdiff / (int)(PROMOTE_W);

	switch (idx)
	{
	case 0:
		return PIECE_QUEEN;
	case 1:
		return PIECE_ROOK;
	case 2:
		return PIECE_BISHOP;
	case 3:
		return PIECE_KNIGHT;
	}
	return -1;
}
