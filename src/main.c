#include "raylib.h"
#include <stdio.h>

#include "config.h"
#include "utils.h"
#include "piece.h"

int main() {
	InitWindow(SCREEN_W, SCREEN_H, "Chess in C");

	Piece p = { .x = 0, .y = 0, .type = PIECE_PAWN, .colour = PIECE_WHITE };

	char name[MAX_PATH_LENGTH];
	get_piece_path(name, &p);
	Image im = LoadImage(name);
	ImageResize(&im, im.width / 2, im.height / 2);
	Texture2D rook_white = LoadTextureFromImage(im);
	UnloadImage(im);


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawTexture(rook_white, SCREEN_W / 2 - rook_white.width / 2, SCREEN_H / 2 - rook_white.height / 2, WHITE);
		}
		EndDrawing();
	}
	UnloadTexture(rook_white);


	CloseWindow();
	return 0;
}