#include <string.h>
#include <stdio.h>

#include "utils.h"

void get_piece_path(char* name, const Piece* p)
{
	char colour[6];
	if (p->colour == PIECE_WHITE)
	{
		strcpy(colour, "white");
	}
	else
	{
		strcpy(colour, "black");
	}

	char piece[11];
	switch (p->type)
	{
	case PIECE_PAWN:
		strcpy(piece, "pawn.png");
		break;
	case PIECE_ROOK:
		strcpy(piece, "rook.png");
		break;
	case PIECE_BISHOP:
		strcpy(piece, "bishop.png");
		break;
	case PIECE_KNIGHT:
		strcpy(piece, "knight.png");
		break;
	case PIECE_QUEEN:
		strcpy(piece, "queen.png");
		break;
	case PIECE_KING:
		strcpy(piece, "king.png");
		break;
	}
	sprintf(name, "%s%s-%s", RESOURCES_PATH, colour, piece);
}
