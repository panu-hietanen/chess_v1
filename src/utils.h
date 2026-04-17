#ifndef UTILS_H__
#define UTILS_H__

#include "config.h"
#include "piece.h"

void get_piece_path(char* name, const Piece* p);
PieceColour get_piece_colour(int p);
PieceType get_piece_type(int p);

#endif //UTILS_H__