#include "raylib.h"
#include <stdio.h>

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Chess in C");

	Image im = LoadImage("C:/Dev/C/chess_v1/resources/white-knight.png");
	ImageResize(&im, im.width / 2, im.height / 2);
	if (IsImageValid(im))
	{
		printf("Image is valid");
	}
	else
	{
		printf("Image is invalid");
	}
	Texture2D rook_white = LoadTextureFromImage(im);
	UnloadImage(im);


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawTexture(rook_white, screenWidth / 2 - rook_white.width / 2, screenHeight / 2 - rook_white.height / 2, WHITE);
		}
		EndDrawing();
	}
	UnloadTexture(rook_white);


	CloseWindow();
	return 0;
}