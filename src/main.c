#include "raylib.h"
#include <stdio.h>

#include "config.h"
#include "utils.h"
#include "piece.h"
#include "render.h"
#include "board.h"

int main() {
	InitWindow(SCREEN_W, SCREEN_H, "Chess in C");

	PieceTextures pt;

	piece_textures_load(&pt);

	//PieceArray whiteArr = piece_array_init_game(PIECE_WHITE);
	//PieceArray blackArr = piece_array_init_game(PIECE_BLACK);

	Board b = board_init_game();
	//board_register_pieces(&b, &whiteArr);
	//board_register_pieces(&b, &blackArr);

	//board_register_move(&b, (Point) { .x = 0, .y = 0 }, (Point) { .x = 2, .y = 2 });

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