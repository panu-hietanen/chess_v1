#include <stdlib.h>

#include "piece.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// BALLARRAY
///////////////////////////////////////////////////////////////////////////////////////////////////

PieceArray piece_array_init(size_t capacity)
{
	Piece* new_array = malloc(sizeof(Piece) * capacity);
	return (PieceArray) {
		.data = new_array,
		.len = 0,
		.cap = capacity,
	};
}

PieceArray piece_array_init_game(PieceColour colour)
{
	PieceArray arr = piece_array_init(16);

	int y;
	switch (colour)
	{
	case PIECE_WHITE:
		y = 1;
		break;
	case PIECE_BLACK:
		y = 6;
		break;
	}
	for (int i = 0; i < 8; ++i)
	{
		piece_array_push(&arr, (Piece) {
			.x = i,
			.y = y,
			.type = PIECE_PAWN,
			.colour = colour,
			.active = 1
		});
	}

	switch (colour)
	{
	case PIECE_WHITE:
		y = 0;
		break;
	case PIECE_BLACK:
		y = 7;
		break;
	}
	piece_array_push(&arr, (Piece) { .x = 0, .y = y, .type = PIECE_ROOK  , .colour = colour, .active = 1 });
	piece_array_push(&arr, (Piece) { .x = 1, .y = y, .type = PIECE_KNIGHT, .colour = colour, .active = 1 });
	piece_array_push(&arr, (Piece) { .x = 2, .y = y, .type = PIECE_BISHOP, .colour = colour, .active = 1 });
	piece_array_push(&arr, (Piece) { .x = 3, .y = y, .type = PIECE_QUEEN , .colour = colour, .active = 1 });
	piece_array_push(&arr, (Piece) { .x = 4, .y = y, .type = PIECE_KING  , .colour = colour, .active = 1 });
	piece_array_push(&arr, (Piece) { .x = 5, .y = y, .type = PIECE_BISHOP, .colour = colour, .active = 1 });
	piece_array_push(&arr, (Piece) { .x = 6, .y = y, .type = PIECE_KNIGHT, .colour = colour, .active = 1 });
	piece_array_push(&arr, (Piece) { .x = 7, .y = y, .type = PIECE_ROOK  , .colour = colour, .active = 1 });

	return arr;
}

void piece_array_push(PieceArray* arr, const Piece b)
{
	if (arr->cap == arr->len)
	{
		arr->cap = (arr->cap == 0) ? 1 : arr->cap * 2;
		arr->data = realloc(arr->data, sizeof(Piece) * arr->cap);
	}
	arr->data[arr->len++] = b;
}

void piece_array_pop(PieceArray* arr)
{
	if (arr->len == 0) return;
	arr->len--;
}

void piece_array_free(PieceArray* arr)
{
	free(arr->data);
	arr->data = NULL;
	arr->len = 0;
	arr->cap = 0;
}