#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

#include "config.h"
#include "utils.h"
#include "piece.h"
#include "render.h"
#include "board.h"

int main() {
	InitWindow(SCREEN_W, SCREEN_H, "Chess in C");
	PieceTextures pt;
	piece_textures_load(&pt);

	Board b = board_init_game();
	Point selectedPiece = point_invalid();
	bool pieceHasBeenSelected = false;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
		select: ;
			Vector2 mouseCoords = GetMousePosition();
			float x = mouseCoords.x;
			float y = mouseCoords.y;
			if (board_mouse_over(x, y))
			{
				Point newSelection = board_mouse_coords(x, y);
				if (pieceHasBeenSelected)
				{
					if (board_move_valid(&b, selectedPiece, newSelection))
					{
						board_register_move(&b, selectedPiece, newSelection);
						board_next_turn(&b);
						selectedPiece = point_invalid();
						pieceHasBeenSelected = false;
					}
					else
					{
						pieceHasBeenSelected = false;
						selectedPiece = point_invalid();
						if (board_select_valid(&b, newSelection)) goto select;
					}
				}
				else
				{
					if (board_select_valid(&b, newSelection))
					{
						pieceHasBeenSelected = true;
						selectedPiece = newSelection;
					}
					else
					{
						pieceHasBeenSelected = false;
						selectedPiece = point_invalid();
					}
				}
			}
			else
			{
				pieceHasBeenSelected = false;
				selectedPiece = (Point){.x = -1, .y = -1};
			}
		}
		BeginDrawing();
		{
			ClearBackground(DARKBROWN);
			Color turnColour = (b.turn == PIECE_WHITE) ? WHITE : BLACK;
			DrawRectangle(BOARD_OFFSET_X / 2, SCREEN_H / 2, 50, 50, turnColour);
			board_draw();
			board_state_draw(&b, &pt);
			board_draw_clicked(&b, &pt, selectedPiece);
			if (pieceHasBeenSelected) board_draw_moves(&b, selectedPiece);
		}
		EndDrawing();
	}
	piece_textures_unload(&pt);

	CloseWindow();
	return 0;
}