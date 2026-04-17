#include "raylib.h"
#include <stdio.h>

#include "config.h"
#include "utils.h"
#include "piece.h"
#include "render.h"
#include "board.h"

int main() {
	PieceTextures pt;
	piece_textures_load(&pt);

	Board b = board_init_game();

	InitWindow(SCREEN_W, SCREEN_H, "Chess in C");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(BLACK);
			board_draw();
			board_state_draw(&b, &pt);
			//piece_array_draw(&whiteArr, &pt);
			//piece_array_draw(&blackArr, &pt);
		}
		EndDrawing();
	}
	piece_textures_unload(&pt);

	CloseWindow();
	return 0;
}