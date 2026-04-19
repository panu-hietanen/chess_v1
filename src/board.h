#ifndef BOARD_H__
#define BOARD_H__

#include <stdbool.h>

#include "config.h"
#include "piece.h"

typedef enum { 
	STATE_DEFAULT,
	STATE_PIECE_MOVING,
	STATE_PROMOTION_SELECTION,
	STATE_WHITE_WON,
	STATE_BLACK_WON
} GameState;

typedef enum { MOVE_OK, MOVE_PROMOTE, MOVE_WHITE_IN_CHECK, MOVE_BLACK_IN_CHECK } MoveResult;

typedef struct {
	int state[BOARD_CELLS][BOARD_CELLS];
	PieceColour turn;
} Board;

Board board_init();
Board board_init_game();

MoveResult board_register_move(Board* b, Point from, Point to);
void board_next_turn(Board* b);
void board_pawn_promote(Board* b, Point from, PieceType type);

bool board_move_valid(const Board* b, Point from, Point to);

bool board_in_check(const Board* b, PieceColour colourToCheck);
bool board_is_mate(const Board* b, PieceColour colourToCheck);

bool board_blocked_pawn(const Board* b, Point from, Point to);
bool board_blocked_rook(const Board* b, Point from, Point to);
bool board_blocked_bishop(const Board* b, Point from, Point to);

bool board_can_capture(const Board* b, Point from, Point to);

bool board_mouse_over(float x, float y);
Point board_mouse_coords(float x, float y);
bool board_select_valid(const Board* b, Point clicked);

#endif //BOARD_H__