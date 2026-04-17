#ifndef BOARD_H__
#define BOARD_H__

#include <stdbool.h>

#include "config.h"
#include "piece.h"

typedef struct {
	int state[BOARD_CELLS][BOARD_CELLS];
	PieceColour turn;
} Board;

Board board_init();
Board board_init_game();
void board_register_pieces(Board* b, const PieceArray* arr);

bool board_register_move(Board* b, Point from, Point to);
void board_next_turn(Board* b);

bool board_move_valid(const Board* b, Point from, Point to);

bool board_blocked_pawn(const Board* b, Point from, Point to);
bool board_blocked_rook(const Board* b, Point from, Point to);
bool board_blocked_bishop(const Board* b, Point from, Point to);
bool board_blocked_queen(const Board* b, Point from, Point to);

bool board_can_capture(const Board* b, Point from, Point to);

bool board_mouse_over(float x, float y);
Point board_mouse_coords(float x, float y);
bool board_select_valid(const Board* b, Point clicked);

#endif //BOARD_H__