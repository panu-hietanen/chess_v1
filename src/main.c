#include "raylib.h"
#include <stdio.h>

#include "config.h"
#include "utils.h"
#include "piece.h"
#include "render.h"

int main() {
	InitWindow(SCREEN_W, SCREEN_H, "Chess in C");

	PieceTextures pt;

	piece_textures_load(&pt);

	PieceArray whiteArr = piece_array_init_game(PIECE_WHITE);
	PieceArray blackArr = piece_array_init_game(PIECE_BLACK);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(BLACK);
			board_draw();
			piece_array_draw(&whiteArr, &pt);
			piece_array_draw(&blackArr, &pt);
		}
		EndDrawing();
	}
	piece_textures_unload(&pt);

	CloseWindow();
	return 0;
}