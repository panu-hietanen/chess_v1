#include "render.h"
#include "config.h"
#include "utils.h"

#include "piece.h"

void create_texture(Texture2D* t, const Piece* p)
{
	char name[MAX_PATH_LENGTH];
	get_piece_path(name, p);

	Image im = LoadImage(name);
	ImageResize(&im, PIECE_W, PIECE_H);
	
	*t = LoadTextureFromImage(im);
	UnloadImage(im);
}

void board_draw()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			Color c = ((i + j) % 2 == 0) ? BOARD_COLOUR_LIGHT : BOARD_COLOUR_DARK;
			DrawRectangle(
				BOARD_OFFSET_X + j * CELL_SIZE,
				BOARD_OFFSET_Y + i * CELL_SIZE,
				CELL_SIZE, CELL_SIZE,
				c
			);
		}
	}
}

void piece_textures_load(PieceTextures* pt)
{
	for (int colour = 0; colour < 2; ++colour)
	{
		for (int type = 0; type < 6; ++type)
		{
			Piece p = { .colour = colour, .type = type };
			create_texture(&pt->data[colour][type], &p);
		}
	}
}

void piece_textures_unload(PieceTextures* pt)
{
	for (int colour = 0; colour < 2; ++colour)
	{
		for (int type = 0; type < 6; ++type)
		{
			UnloadTexture(pt->data[colour][type]);
		}
	}
}

void piece_array_draw(const PieceArray* arr, const PieceTextures* pt)
{
	for (int i = 0; i < arr->len; ++i)
	{
		Piece p = arr->data[i];
		if (!p.active) continue;

		int sx = BOARD_OFFSET_X + p.x * CELL_SIZE;
		int sy = BOARD_OFFSET_Y + p.y * CELL_SIZE;
		DrawTexture(pt->data[p.colour][p.type], sx, sy, WHITE);
	}
}
