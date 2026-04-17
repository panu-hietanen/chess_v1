#ifndef BOARD_H__
#define BOARD_H__

#include <stdbool.h>

#include "config.h"
#include "piece.h"

typedef struct {
	int state[BOARD_CELLS][BOARD_CELLS];
} Board;

Board board_init();
Board board_init_game();
void board_register_pieces(const Board* b, const PieceArray* arr);

bool board_register_move(Board* b, Point from, Point to);

bool board_move_valid(const Board* b, Point from, Point to);

bool board_mouse_over(float x, float y);
Point board_mouse_coords(float x, float y);
bool board_click_valid(const Board* b, const Point clicked);

#endif //BOARD_H__