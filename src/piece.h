#ifndef PIECE_H__
#define PIECE_H__

#include <stddef.h>

typedef enum {
	PIECE_PAWN,
	PIECE_ROOK,
	PIECE_KNIGHT,
	PIECE_BISHOP,
	PIECE_QUEEN,
	PIECE_KING,
} PieceType;

typedef enum { PIECE_WHITE, PIECE_BLACK } PieceColour;

typedef struct {
	int x, y;
} Point;

typedef struct {
	int x, y;
	PieceType type;
	PieceColour colour;
	int active;
} Piece;

typedef struct {
	Piece* data;
	size_t len;
	size_t cap;
} PieceArray;

PieceArray piece_array_init     (size_t capacity);
PieceArray piece_array_init_game(PieceColour colour);
void       piece_array_push     (PieceArray* arr, const Piece b);
void       piece_array_pop      (PieceArray* arr);
void       piece_array_free     (PieceArray* arr);

#endif //PIECE_H__