#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

#include "config.h"
#include "utils.h"
#include "piece.h"
#include "render.h"
#include "board.h"

Point vec2point(Vector2 v)
{
	return (Point) { .x = v.x, .y = v.y };
}

int main() {
	InitWindow(SCREEN_W, SCREEN_H, "Chess in C");
	PieceTextures pt;
	piece_textures_load(&pt);

	Board b = board_init_game();
	Point selectedPiece = point_invalid();
	bool clickedState = false;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 mouseCoords = GetMousePosition();
			float x = mouseCoords.x;
			float y = mouseCoords.y;
			if (board_mouse_over(x, y))
			{
				Point newSelection = board_mouse_coords(x, y);
				if (clickedState)
				{
					if (board_move_valid(&b, selectedPiece, newSelection))
					{
						board_register_move(&b, selectedPiece, newSelection);
						board_next_turn(&b);
						selectedPiece = point_invalid();
						clickedState = false;
					}
					else
					{
						clickedState = false;
						selectedPiece = point_invalid();
					}
				}
				else
				{
					if (board_select_valid(&b, newSelection))
					{
						clickedState = true;
						selectedPiece = newSelection;
					}
					else
					{
						clickedState = false;
						selectedPiece = point_invalid();
					}
				}
			}
			else
			{
				clickedState = false;
				selectedPiece = (Point){.x = -1, .y = -1};
			}
		}
		BeginDrawing();
		{
			ClearBackground(BLACK);
			board_draw();
			board_state_draw(&b, &pt);
			board_draw_clicked(&b, &pt, selectedPiece);
		}
		EndDrawing();
	}
	piece_textures_unload(&pt);

	CloseWindow();
	return 0;
}