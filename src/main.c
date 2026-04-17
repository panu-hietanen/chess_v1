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
	bool click_state = false;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 mouse_coords = GetMousePosition();
			float x = mouse_coords.x;
			float y = mouse_coords.y;
			if (board_mouse_over(x, y))
			{
				b.clicked = board_mouse_coords(x, y);
				if (board_click_valid(&b)) 
				{
					click_state = true;
					//board_register_move(&b, clicked, (Point) { .x = 2, .y = 3 });
				}
				else
				{
					click_state = false;
					b.clicked = (Point){ .x = -1, .y = -1 };
				}
			}
			else
			{
				b.clicked = (Point){ .x = -1, .y = -1 };
			}
		}
		BeginDrawing();
		{
			ClearBackground(BLACK);
			board_draw();
			board_state_draw(&b, &pt);
			board_draw_clicked(&b, &pt);
		}
		EndDrawing();
	}
	piece_textures_unload(&pt);

	CloseWindow();
	return 0;
}