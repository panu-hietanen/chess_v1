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