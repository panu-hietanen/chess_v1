#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

#include "config.h"
#include "utils.h"
#include "piece.h"
#include "render.h"
#include "board.h"
#include "ui.h"

typedef enum { STATE_DEFAULT, STATE_PIECE_MOVING, STATE_PROMOTION_SELECTION } GameState;

int main() {
	InitWindow(SCREEN_W, SCREEN_H, "Chess in C");

	GameState gameState = STATE_DEFAULT;

	PieceTextures pt;
	piece_textures_load(&pt, PIECE_W, PIECE_H);

	PieceTextures pt_promote;
	piece_textures_load(&pt_promote, PIECE_W / 2, PIECE_H / 2);

	Board b = board_init_game();
	Point selectedPiece = point_invalid();

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
		select: ;
			Vector2 mouseCoords = GetMousePosition();
			float x = mouseCoords.x;
			float y = mouseCoords.y;
			switch (gameState)
			{
			case STATE_DEFAULT:
				if (board_mouse_over(x, y))
				{
					Point newSelection = board_mouse_coords(x, y);
					if (board_select_valid(&b, newSelection))
					{
						gameState = STATE_PIECE_MOVING;
						selectedPiece = newSelection;
					}
					else
					{
						gameState = STATE_DEFAULT;
						selectedPiece = point_invalid();
					}
				}
				else if (restart_mouse_over(x, y))
				{
					b = board_init_game();
					selectedPiece = point_invalid();
					gameState = STATE_DEFAULT;
				}
				break;
			case STATE_PIECE_MOVING:
				if (board_mouse_over(x, y))
				{
					gameState = STATE_DEFAULT;
					Point newSelection = board_mouse_coords(x, y);
					if (board_move_valid(&b, selectedPiece, newSelection))
					{
						board_register_move(&b, selectedPiece, newSelection);
						board_next_turn(&b);
						selectedPiece = point_invalid();
					}
					else
					{
						gameState = STATE_DEFAULT;
						selectedPiece = point_invalid();
						if (board_select_valid(&b, newSelection)) goto select;
					}
				}
				else if (restart_mouse_over(x, y))
				{
					b = board_init_game();
					selectedPiece = point_invalid();
					gameState = STATE_DEFAULT;
				}
				else
				{
					gameState = STATE_DEFAULT;
					selectedPiece = point_invalid();
				}
				break;
			case STATE_PROMOTION_SELECTION:
				break;
			}
		}
		BeginDrawing();
		{
			ClearBackground(BACKGROUND_COLOUR);
			ui_draw(&b);
			board_draw();
			board_state_draw(&b, &pt);
			board_draw_clicked(&b, &pt, selectedPiece);
			if (gameState == STATE_PIECE_MOVING) board_draw_moves(&b, selectedPiece);
		}
		EndDrawing();
	}
	piece_textures_unload(&pt);
	piece_textures_unload(&pt_promote);

	CloseWindow();
	return 0;
}